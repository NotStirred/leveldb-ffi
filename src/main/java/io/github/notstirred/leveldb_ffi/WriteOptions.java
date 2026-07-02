package io.github.notstirred.leveldb_ffi;

import io.github.notstirred.leveldb_ffi.ffi.c_h;

import java.lang.foreign.Arena;
import java.lang.foreign.MemorySegment;

import static io.github.notstirred.leveldb_ffi.ffi.c_h.leveldb_writeoptions_create;
import static io.github.notstirred.leveldb_ffi.ffi.c_h.leveldb_writeoptions_set_sync;

public class WriteOptions extends Scoped {
    MemorySegment seg;

    private WriteOptions(MemorySegment optionsSeg) {
        super(optionsSeg);
    }

    public static WriteOptions create() {
        return create(FFI.AUTO_ARENA);
    }

    public static WriteOptions create(Arena arena) {
        MemorySegment memorySegment = leveldb_writeoptions_create().reinterpret(arena, c_h::leveldb_writeoptions_destroy);
        return new WriteOptions(memorySegment);
    }

    public void setSync(boolean sync) {
        this.alive();
        leveldb_writeoptions_set_sync(this.seg, (byte) (sync ? 1 : 0));
    }
}
