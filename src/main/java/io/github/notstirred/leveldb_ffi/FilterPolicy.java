package io.github.notstirred.leveldb_ffi;

import io.github.notstirred.leveldb_ffi.ffi.c_h;

import java.lang.foreign.Arena;
import java.lang.foreign.MemorySegment;

// TODO: custom filter policies?
public class FilterPolicy extends Scoped {
    private FilterPolicy(MemorySegment memorySegment) {
        super(memorySegment);
    }

    public static FilterPolicy newBloomFilterPolicy(Arena arena, int bitsPerKey) {
        MemorySegment memorySegment = c_h.leveldb_ffi_filterpolicy_create_bloom(bitsPerKey).reinterpret(arena, c_h::leveldb_ffi_readoptions_destroy);
        return new FilterPolicy(memorySegment);
    }
}
