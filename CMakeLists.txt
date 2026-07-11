cmake_minimum_required(VERSION 3.13)

project(leveldb_ffi LANGUAGES C CXX)

if (UNIX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif ()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(ZLIB_BUILD_EXAMPLES OFF)

set(LEVELDB_BUILD_UTILS OFF CACHE BOOL "" FORCE)
set(LEVELDB_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(LEVELDB_BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)
set(LEVELDB_INSTALL OFF CACHE BOOL "" FORCE)
set(LEVELDB_DISABLE_EXCEPTIONS OFF CACHE BOOL "" FORCE)
set(LEVELDB_DISABLE_RTTI OFF CACHE BOOL "" FORCE)

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
