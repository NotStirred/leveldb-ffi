package io.github.notstirred.leveldb_ffi;

public class SystemInfo {
    public static final Architecture ARCH;
    public static final OperatingSystem OS;

    static {

        String arch = System.getProperty("os.arch", "").toLowerCase().replaceAll("[^a-z0-9]+", "");
        switch (arch) {
            case "x64":
            case "x86_64":
            case "amd64":
            case "em64t":
            case "universal":
                ARCH = Architecture.x86_64;
                break;
            case "x86":
            case "x86_32":
            case "x32":
            case "i386":
            case "i486":
            case "i586":
            case "i686":
            case "pentium":
                ARCH = Architecture.x86;
                break;
            case "arm":
            case "arm32":
                ARCH = Architecture.ARM;
                break;
            case "aarch64":
                ARCH = Architecture.AARCH64;
                break;
            default:
                ARCH = Architecture.UNKNOWN;
        }

        String osName = System.getProperty("os.name", "").toLowerCase();
        if (osName.contains("linux")) {
            OS = OperatingSystem.Linux;
        } else if (osName.contains("freebsd")) {
            OS = OperatingSystem.FreeBSD;
        } else if (osName.contains("openbsd")) {
            OS = OperatingSystem.OpenBSD;
        } else if (osName.contains("netbsd")) {
            OS = OperatingSystem.NetBSD;
        } else if (osName.contains("windows")) {
            OS = OperatingSystem.Windows;
        } else if (osName.contains("mac os")) {
            OS = OperatingSystem.MAC;
        } else {
            OS = OperatingSystem.UNKNOWN;
        }
    }

    public enum OperatingSystem {
        Linux("linux", "lib", ".so"),
        FreeBSD("freebsd", "lib", ".so"),
        OpenBSD("openbsd", "lib", ".so"),
        NetBSD("netbsd", "lib", ".so"),
        Windows("windows", "", ".dll"),
        MAC("mac", "lib", ".dylib"),
        UNKNOWN("", "", "");

        public final String osName;
        public final String libPrefix;
        public final String libSuffix;

        OperatingSystem(String name, String libPrefix, String libSuffix) {
            this.osName = name;
            this.libPrefix = libPrefix;
            this.libSuffix = libSuffix;
        }

        public String getLibraryName(String name) {
            return this.libPrefix + name + this.libSuffix;
        }
    }

    public enum Architecture {
        x86("x86"),
        x86_64("x86_64"),
        ARM("arm"),
        AARCH64("aarch64"),
        UNKNOWN("");

        public final String archName;

        Architecture(String name) {
            this.archName = name;
        }
    }
}
