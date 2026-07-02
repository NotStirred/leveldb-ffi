package io.github.notstirred.leveldb_ffi;

import io.github.notstirred.leveldb_ffi.ffi.c_h;

import java.lang.foreign.Arena;
import java.lang.foreign.MemorySegment;

import static io.github.notstirred.leveldb_ffi.ffi.c_h.*;

public class Options extends Scoped {
    private Options(MemorySegment optionsSeg) {
        super(optionsSeg);
    }

    public static Options create() {
        return create(FFI.AUTO_ARENA);
    }

    public static Options create(Arena arena) {
        MemorySegment memorySegment = leveldb_options_create().reinterpret(arena, c_h::leveldb_options_destroy);
        return new Options(memorySegment);
    }

    public void setCreateIfMissing(boolean createIfMissing) {
        this.alive();
        leveldb_options_set_create_if_missing(this.seg, (byte) (createIfMissing ? 1 : 0));
    }

    public void setErrorIfExists(boolean errorIfExists) {
        this.alive();
        leveldb_options_set_error_if_exists(this.seg, (byte) (errorIfExists ? 1 : 0));
    }

    public void setParanoidChecks(boolean paranoidChecks) {
        leveldb_options_set_paranoid_checks(this.seg, (byte) (paranoidChecks ? 1 : 0));
    }

    //FIXME
//    public void setEnv(Env env) {
//
//    }
    //FIXME
//    public void setInfoLog(Logger logger) {
//
//    }

    public void setWriteBufferSize(long writeBufferSize) {
        this.alive();
        leveldb_options_set_write_buffer_size(this.seg, writeBufferSize);
    }

    public void setMaxOpenFiles(int maxOpenFiles) {
        this.alive();
        leveldb_options_set_max_open_files(this.seg, maxOpenFiles);
    }
    //FIXME
//    public void setCache(Cache cache) {
//
//    }

    public void setBlockSize(long blockSize) {
        this.alive();
        leveldb_options_set_block_size(this.seg, blockSize);
    }

    public void setBlockRestartInterval(int blockRestartInterval) {
        this.alive();
        leveldb_options_set_block_restart_interval(this.seg, blockRestartInterval);
    }

    public void setCompression(Compressor compressor) {
        this.alive();
        int c = switch (compressor) {
            case NONE -> leveldb_no_compression();
            case SNAPPY -> leveldb_snappy_compression();
            case ZLIB_RAW -> leveldb_zlib_raw_compression();
        };
        leveldb_options_set_compression(this.seg, c);
    }
}
