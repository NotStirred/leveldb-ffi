package io.github.notstirred.leveldb_ffi;

import io.github.notstirred.leveldb_ffi.ffi.c_h;

import java.lang.foreign.Arena;
import java.lang.foreign.MemorySegment;
import java.lang.foreign.ValueLayout;
import java.nio.ByteBuffer;
import java.util.Optional;

import static io.github.notstirred.leveldb_ffi.ffi.c_h.*;

public class LevelDB extends Scoped implements AutoCloseable {
    /**
     * The values <u>inside</u> {@link Options} must outlive the db, so just hold onto it.
     */
    @SuppressWarnings({"FieldCanBeLocal", "unused"})
    private final Options options;

    private LevelDB(MemorySegment dbSeg, Options options) {
        super(dbSeg);
        this.options = options;
    }

    public static int majorVersion() {
        return leveldb_ffi_major_version();
    }

    public static int minorVersion() {
        return leveldb_ffi_minor_version();
    }

    /**
     *
     * @param arena   The arena in which to allocate the DB, <b>must</b> outlive closure of the returned db.
     * @param options The db options, which <b>must</b> outlive the closure of the returned db.
     * @param name    The path to the db
     * @return The opened db
     * @throws LevelDBException
     */
    public static LevelDB open(Arena arena, Options options, String name) throws LevelDBException {
        try (Arena tempArena = Arena.ofConfined()) {
            MemorySegment errSeg = tempArena.allocate(ValueLayout.ADDRESS);

            MemorySegment db = leveldb_ffi_open(options.seg, tempArena.allocateFrom(name), errSeg)
                    .reinterpret(arena, c_h::leveldb_ffi_close);

            throwErrorIfPresent(tempArena, errSeg);
            // no error, return the db
            return new LevelDB(db, options);
        }
    }

    public LevelDBIterator createIterator(ReadOptions options) {
        this.alive();
        LevelDBIterator iter = LevelDBIterator.create(leveldb_ffi_create_iterator(this.seg, options.seg));
        iter.seekToFirst0();
        return iter;
    }

    public void put(WriteOptions options, String key, String val) throws LevelDBException {
        this.alive();
        try (Arena tempArena = Arena.ofConfined()) {
            MemorySegment keySeg = tempArena.allocateFrom(key);
            MemorySegment valSeg = tempArena.allocateFrom(val);
            MemorySegment errSeg = tempArena.allocate(ValueLayout.ADDRESS);

            leveldb_ffi_put(this.seg, options.seg, keySeg, keySeg.byteSize(), valSeg, valSeg.byteSize(), errSeg);

            throwErrorIfPresent(tempArena, errSeg);
        }
    }

    public Optional<byte[]> get(ReadOptions options, byte[] key) throws LevelDBException {
        this.alive();
        try (Arena tempArena = Arena.ofConfined()) {
            MemorySegment keySeg = tempArena.allocateFrom(ValueLayout.JAVA_BYTE, key);
            MemorySegment valLenSeg = tempArena.allocate(ValueLayout.JAVA_LONG);
            MemorySegment errSeg = tempArena.allocate(ValueLayout.ADDRESS);

            MemorySegment valSeg = leveldb_ffi_get(this.seg, options.seg, keySeg, keySeg.byteSize(), valLenSeg, errSeg);
            if (valSeg.address() == 0) {
                throwErrorIfPresent(tempArena, errSeg);
                return Optional.empty();
            }
            valSeg = valSeg.reinterpret(valLenSeg.get(ValueLayout.JAVA_LONG, 0), tempArena, c_h::leveldb_ffi_free);

            throwErrorIfPresent(tempArena, errSeg);

            ByteBuffer valBuf = valSeg.asByteBuffer();
            byte[] val = new byte[valBuf.remaining()];
            valBuf.get(val);

            return Optional.of(val);
        }
    }

    /**
     * @param errSeg Must be a char** pointing to an error message string.
     * @throws LevelDBException
     */
    private static void throwErrorIfPresent(Arena arena, MemorySegment errSeg) throws LevelDBException {
        MemorySegment errStr = errSeg.get(ValueLayout.ADDRESS, 0);
        if (errStr.address() != 0) { // error exists, throw
            // Null terminated string, so we read until \0, hence Long.MAX_VALUE
            errStr = errStr.reinterpret(Long.MAX_VALUE, arena, c_h::leveldb_ffi_free);
            String string = errStr.getString(0);
            throw new LevelDBException(string);
        }
    }

    @Override
    public void close() {
        leveldb_ffi_close(this.seg);
    }
}
