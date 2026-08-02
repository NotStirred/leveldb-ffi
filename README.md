A Java wrapper for LevelDB with `ZLIB_RAW` support

Generally methods follow the same contract as the leveldb

## Usage

Add the dependency:

```groovy
dependencies {
    implementation 'io.github.notstirred:leveldb-ffi:0.1.0-SNAPSHOT'
}
```

A simple java 25 example:

```java
void main() {
    boolean loadedSuccessfully = LevelDBLib.init();

    if (!loadedSuccessfully) {
        throw new RuntimeException("LevelDB not supported on this platform");
    }

    try (Arena arena = Arena.ofShared()) {
        Options options = Options.create(arena);
        options.setCreateIfMissing(true);
        options.setCompression(Compressor.ZLIB_RAW);
        LevelDB db = LevelDB.open(arena, options, "/etc/database/");

        ReadOptions readOptions = ReadOptions.create(arena);

        byte[] bytes = "dbkey".getBytes();
        Optional<byte[]> value = db.get(readOptions, bytes);

        IO.println(value);
    } catch (LevelDBException e) {
        throw new RuntimeException(e);
    }
}

```

## License

`SPDX-License-Identifier: Apache-2.0`
