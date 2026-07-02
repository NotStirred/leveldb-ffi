package io.github.notstirred.leveldb_ffi;

import java.lang.foreign.MemorySegment;

public class Scoped {
    protected MemorySegment seg;

    protected Scoped(MemorySegment seg) {
        this.seg = seg;
    }

    public final void alive() {
        if (!seg.scope().isAlive()) {
            throw new RuntimeException("Backing memory of Scoped segment was freed");
        }
    }
}
