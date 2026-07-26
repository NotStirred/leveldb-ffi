package io.github.notstirred.leveldb_ffi;

import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;

public class LevelDBLib {
    private static boolean attempted;
    private static boolean is_success;

    private static final String[] LIBRARIES = {
            "leveldb_ffi",
    };

    /**
     * Must be called before interacting with anything else in leveldb-ffi
     *
     * @return Whether initialization was successful.
     */
    public static boolean init() {
        if (attempted) {
            return is_success;
        }
        attempted = true;

        boolean success = false;
        try {
            Path tempDir = Files.createTempDirectory("leveldb-ffi-natives");
            for (String library : LIBRARIES) {
                String libResource = "natives/" + SystemInfo.OS.osName + "/" + SystemInfo.ARCH.archName + "/" + SystemInfo.OS.getLibraryName(library);
                Path libFile = tempDir.resolve(SystemInfo.OS.getLibraryName(library)).toAbsolutePath();

                try (InputStream in = LevelDBLib.class.getResourceAsStream(libResource)) {
                    assert in != null;
                    Files.copy(in, libFile);
                }
                System.load(libFile.toString());
                deleteIgnoreFail(libFile);
            }
            success = true;

            deleteIgnoreFail(tempDir);
        } catch (Throwable t) {
            System.err.println("Failed to load leveldb native libraries.");
            t.printStackTrace(System.err);
        } finally {
            is_success = success;
        }

        return is_success;
    }

    private static void deleteIgnoreFail(Path libFile) {
        try {
            Files.delete(libFile);
        } catch (Throwable _) {
            // ignored
        }
    }
}
