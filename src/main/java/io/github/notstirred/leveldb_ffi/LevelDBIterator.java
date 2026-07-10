package io.github.notstirred.leveldb_ffi;

import io.github.notstirred.leveldb_ffi.ffi.c_h;

import java.lang.foreign.Arena;
import java.lang.foreign.MemorySegment;
import java.lang.foreign.ValueLayout;
import java.util.Iterator;
import java.util.Map;
import java.util.Optional;

import static io.github.notstirred.leveldb_ffi.ffi.c_h.*;

public class LevelDBIterator extends Scoped implements AutoCloseable, Iterator<Map.Entry<byte[], byte[]>> {
    private LevelDBIterator(MemorySegment iteratorSegment) {
        super(iteratorSegment);
    }

    protected static LevelDBIterator create(MemorySegment iteratorSegment) {
        return new LevelDBIterator(iteratorSegment);
    }

    @Override
    public boolean hasNext() {
        return valid0();
    }

    @Override
    public Map.Entry<byte[], byte[]> next() {
        byte[] key = this.key0();
        byte[] value = this.value0();

        this.next0();

        return Map.entry(key, value);
    }

    public boolean valid0() {
        this.alive();
        return leveldb_ffi_iter_valid(this.seg) != 0;
    }

    public void seekToFirst0() {
        this.alive();
        leveldb_ffi_iter_seek_to_first(this.seg);
    }

    public void seekToLast0() {
        this.alive();
        leveldb_ffi_iter_seek_to_last(this.seg);
    }

    public void seek0(String key) {
        this.alive();
        try (Arena arena = Arena.ofConfined()) {
            MemorySegment keySeg = arena.allocateFrom(key);
            leveldb_ffi_iter_seek(this.seg, keySeg, keySeg.byteSize());
        }
    }

    public void next0() {
        this.alive();
        leveldb_ffi_iter_next(this.seg);
    }

    public void prev0() {
        this.alive();
        leveldb_ffi_iter_prev(this.seg);
    }

    public byte[] key0() {
        this.alive();
        try (Arena arena = Arena.ofConfined()) {
            MemorySegment sizeSeg = arena.allocate(ValueLayout.ADDRESS);
            MemorySegment keySeg = leveldb_ffi_iter_key(this.seg, sizeSeg);

            return keySeg.reinterpret(sizeSeg.get(ValueLayout.JAVA_LONG, 0))
                    .toArray(ValueLayout.JAVA_BYTE);
        }
    }

    public byte[] value0() {
        this.alive();
        try (Arena arena = Arena.ofConfined()) {
            MemorySegment sizeSeg = arena.allocate(ValueLayout.ADDRESS);
            MemorySegment keySeg = leveldb_ffi_iter_value(this.seg, sizeSeg);

            return keySeg.reinterpret(sizeSeg.get(ValueLayout.JAVA_LONG, 0))
                    .toArray(ValueLayout.JAVA_BYTE);
        }
    }

    public Optional<String> getError() {
        this.alive();
        try (Arena arena = Arena.ofConfined()) {
            MemorySegment errPtr = arena.allocate(ValueLayout.ADDRESS);

            leveldb_ffi_iter_get_error(this.seg, errPtr);

            MemorySegment errStr = errPtr.get(ValueLayout.ADDRESS, 0);
            if (errStr.address() == 0) { // no error, return the db
                return Optional.empty();
            } else { // error exists, throw
                // Null terminated string, so we read until \0, hence Long.MAX_VALUE
                errStr = errStr.reinterpret(Long.MAX_VALUE, arena, c_h::leveldb_ffi_free);
                return Optional.of(errStr.getString(0));
            }
        }
    }

    @Override
    public void close() {
        this.alive();
        leveldb_ffi_iter_destroy(this.seg);
    }
}
