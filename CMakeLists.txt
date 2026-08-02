cmake_minimum_required(VERSION 3.13)

project(leveldb_ffi LANGUAGES C CXX)

if (UNIX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif ()

include(CheckIPOSupported)
check_ipo_supported(RESULT lto_supported OUTPUT lto_error)
if (lto_supported)
    message(STATUS "LTO enabled.")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else ()
    message(WARNING "LTO is not supported by compiler: ${lto_error}")
endif ()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(ZLIB_BUILD_EXAMPLES OFF)

set(LEVELDB_BUILD_UTILS OFF CACHE BOOL "" FORCE)
set(LEVELDB_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(LEVELDB_BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)
set(LEVELDB_INSTALL OFF CACHE BOOL "" FORCE)
set(LEVELDB_DISABLE_EXCEPTIONS OFF CACHE BOOL "" FORCE)
set(LEVELDB_DISABLE_RTTI ON CACHE BOOL "" FORCE)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if (LEVELDB_DISABLE_RTTI)
        add_compile_options(/GR-) # Disable RTTI.
    endif (LEVELDB_DISABLE_RTTI)
else (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if (LEVELDB_DISABLE_RTTI)
        add_compile_options(-fno-rtti) # Disable RTTI.
    endif (LEVELDB_DISABLE_RTTI)
endif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")


include(FetchContent)
FetchContent_Declare(
        leveldb
        GIT_REPOSITORY https://github.com/Amulet-Team/leveldb.git
        GIT_TAG 1352243bb27d287b27be94f7591218dddb3ef900
)
FetchContent_MakeAvailable(leveldb)

set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

add_library(leveldb_ffi SHARED
        native/include/leveldb_ffi/c.h
        native/include/leveldb_ffi/no_throw.h
        native/src/c.cc
)
set_target_properties(leveldb_ffi PROPERTIES LINKER_LANGUAGE C)

target_include_directories(leveldb_ffi PUBLIC
        native/include
)
target_link_libraries(leveldb_ffi PRIVATE zlibstatic)
target_link_libraries(leveldb_ffi PUBLIC leveldb)

# Compile a fat binary.
if (MSVC)
    target_link_options(leveldb_ffi PUBLIC "/WHOLEARCHIVE:$<TARGET_FILE:leveldb>")
elseif (APPLE)
    target_link_options(leveldb_ffi PUBLIC "-Wl,-force_load,$<TARGET_FILE:leveldb>")
else () # Linux / GCC / Clang
    target_link_options(leveldb_ffi PUBLIC "SHELL:-Wl,--whole-archive $<TARGET_FILE:leveldb> -Wl,--no-whole-archive")
endif ()

message(STATUS "C++ Flags (Release): ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "C++ Flags (Debug):   ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "C++ Flags:           ${CMAKE_CXX_FLAGS}")

message(STATUS "C Flags (Release):   ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "C Flags (Debug):     ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "C Flags:             ${CMAKE_C_FLAGS}")
