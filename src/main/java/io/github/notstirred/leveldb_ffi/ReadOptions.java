package io.github.notstirred.leveldb_ffi;

import io.github.notstirred.leveldb_ffi.ffi.c_h;

import java.lang.foreign.Arena;
import java.lang.foreign.MemorySegment;

import static io.github.notstirred.leveldb_ffi.ffi.c_h.*;

public class ReadOptions extends Scoped {
    private ReadOptions(MemorySegment optionsSeg) {
        super(optionsSeg);
    }

    public static ReadOptions create(Arena arena) {
        MemorySegment memorySegment = leveldb_ffi_readoptions_create().reinterpret(arena, c_h::leveldb_ffi_readoptions_destroy);
        return new ReadOptions(memorySegment);
    }

    public void setVerifyChecksums(boolean verifyChecksums) {
        this.alive();
        leveldb_ffi_readoptions_set_verify_checksums(this.seg, (byte) (verifyChecksums ? 1 : 0));
    }

    public void setFillCache(boolean fillCache) {
        this.alive();
        leveldb_ffi_readoptions_set_fill_cache(this.seg, (byte) (fillCache ? 1 : 0));
    }

    //FIXME
//    public void setSnapshot(Snapshot snapshot) {}
}
