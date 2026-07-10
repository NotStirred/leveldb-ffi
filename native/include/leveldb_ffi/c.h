#pragma once

#if !defined(FFI_EXPORT)

#if defined(_WIN32)
#define FFI_EXPORT __declspec(dllexport)
#else // defined(_WIN32)
#define FFI_EXPORT
#endif

#endif // !defined(FFI_EXPORT)

#include <stddef.h> // NOLINT(*-deprecated-headers)
#include <stdint.h> // NOLINT(*-deprecated-headers)

typedef struct leveldb_t leveldb_t;
typedef struct leveldb_cache_t leveldb_cache_t;
typedef struct leveldb_comparator_t leveldb_comparator_t;
typedef struct leveldb_env_t leveldb_env_t;
typedef struct leveldb_filelock_t leveldb_filelock_t;
typedef struct leveldb_filterpolicy_t leveldb_filterpolicy_t;
typedef struct leveldb_iterator_t leveldb_iterator_t;
typedef struct leveldb_logger_t leveldb_logger_t;
typedef struct leveldb_options_t leveldb_options_t;
typedef struct leveldb_randomfile_t leveldb_randomfile_t;
typedef struct leveldb_readoptions_t leveldb_readoptions_t;
typedef struct leveldb_seqfile_t leveldb_seqfile_t;
typedef struct leveldb_snapshot_t leveldb_snapshot_t;
typedef struct leveldb_writablefile_t leveldb_writablefile_t;
typedef struct leveldb_writebatch_t leveldb_writebatch_t;
typedef struct leveldb_writeoptions_t leveldb_writeoptions_t;

#ifdef __cplusplus
extern "C" {
#endif

FFI_EXPORT leveldb_t *leveldb_ffi_open(const leveldb_options_t *options, const char *name, char **errptr);

FFI_EXPORT void leveldb_ffi_close(leveldb_t *db);

FFI_EXPORT void leveldb_ffi_put(leveldb_t *db, const leveldb_writeoptions_t *options, const char *key, size_t keylen,
                                const char *val, size_t vallen, char **errptr);

FFI_EXPORT void leveldb_ffi_delete(leveldb_t *db, const leveldb_writeoptions_t *options, const char *key, size_t keylen,
                                   char **errptr);

FFI_EXPORT void leveldb_ffi_write(leveldb_t *db, const leveldb_writeoptions_t *options, leveldb_writebatch_t *batch,
                                  char **errptr);

FFI_EXPORT char *leveldb_ffi_get(leveldb_t *db, const leveldb_readoptions_t *options, const char *key, size_t keylen,
                                 size_t *vallen, char **errptr);

FFI_EXPORT leveldb_iterator_t *leveldb_ffi_create_iterator(leveldb_t *db, const leveldb_readoptions_t *options);

FFI_EXPORT const leveldb_snapshot_t *leveldb_ffi_create_snapshot(leveldb_t *db);

FFI_EXPORT void leveldb_ffi_release_snapshot(leveldb_t *db, const leveldb_snapshot_t *snapshot);

FFI_EXPORT char *leveldb_ffi_property_value(leveldb_t *db, const char *propname);

FFI_EXPORT void leveldb_ffi_approximate_sizes(leveldb_t *db, int num_ranges, const char *const *range_start_key,
                                              const size_t *range_start_key_len, const char *const *range_limit_key,
                                              const size_t *range_limit_key_len, uint64_t *sizes);

FFI_EXPORT void leveldb_ffi_compact_range(leveldb_t *db, const char *start_key, size_t start_key_len,
                                          const char *limit_key, size_t limit_key_len);

FFI_EXPORT void leveldb_ffi_destroy_db(const leveldb_options_t *options, const char *name, char **errptr);

FFI_EXPORT void leveldb_ffi_repair_db(const leveldb_options_t *options, const char *name, char **errptr);

FFI_EXPORT void leveldb_ffi_iter_destroy(leveldb_iterator_t *);
FFI_EXPORT uint8_t leveldb_ffi_iter_valid(const leveldb_iterator_t *);
FFI_EXPORT void leveldb_ffi_iter_seek_to_first(leveldb_iterator_t *);
FFI_EXPORT void leveldb_ffi_iter_seek_to_last(leveldb_iterator_t *);
FFI_EXPORT void leveldb_ffi_iter_seek(leveldb_iterator_t *, const char *k, size_t klen);
FFI_EXPORT void leveldb_ffi_iter_next(leveldb_iterator_t *);
FFI_EXPORT void leveldb_ffi_iter_prev(leveldb_iterator_t *);
FFI_EXPORT const char *leveldb_ffi_iter_key(const leveldb_iterator_t *, size_t *klen);
FFI_EXPORT const char *leveldb_ffi_iter_value(const leveldb_iterator_t *, size_t *vlen);
FFI_EXPORT void leveldb_ffi_iter_get_error(const leveldb_iterator_t *, char **errptr);

FFI_EXPORT leveldb_writebatch_t *leveldb_ffi_writebatch_create(void);
FFI_EXPORT void leveldb_ffi_writebatch_destroy(leveldb_writebatch_t *);
FFI_EXPORT void leveldb_ffi_writebatch_clear(leveldb_writebatch_t *);
FFI_EXPORT void leveldb_ffi_writebatch_put(leveldb_writebatch_t *, const char *key, size_t klen, const char *val,
                                           size_t vlen);
FFI_EXPORT void leveldb_ffi_writebatch_delete(leveldb_writebatch_t *, const char *key, size_t klen);
FFI_EXPORT void leveldb_ffi_writebatch_iterate(const leveldb_writebatch_t *, void *state,
                                               void (*put)(void *, const char *k, size_t klen, const char *v,
                                                           size_t vlen),
                                               void (*deleted)(void *, const char *k, size_t klen));
FFI_EXPORT void leveldb_ffi_writebatch_append(leveldb_writebatch_t *destination, const leveldb_writebatch_t *source);

FFI_EXPORT leveldb_options_t *leveldb_ffi_options_create(void);
FFI_EXPORT void leveldb_ffi_options_destroy(leveldb_options_t *);
FFI_EXPORT void leveldb_ffi_options_set_comparator(leveldb_options_t *, leveldb_comparator_t *);
FFI_EXPORT void leveldb_ffi_options_set_filter_policy(leveldb_options_t *, leveldb_filterpolicy_t *);
FFI_EXPORT void leveldb_ffi_options_set_create_if_missing(leveldb_options_t *, uint8_t);
FFI_EXPORT void leveldb_ffi_options_set_error_if_exists(leveldb_options_t *, uint8_t);
FFI_EXPORT void leveldb_ffi_options_set_paranoid_checks(leveldb_options_t *, uint8_t);
FFI_EXPORT void leveldb_ffi_options_set_env(leveldb_options_t *, leveldb_env_t *);
FFI_EXPORT void leveldb_ffi_options_set_info_log(leveldb_options_t *, leveldb_logger_t *);
FFI_EXPORT void leveldb_ffi_options_set_write_buffer_size(leveldb_options_t *, size_t);
FFI_EXPORT void leveldb_ffi_options_set_max_open_files(leveldb_options_t *, int);
FFI_EXPORT void leveldb_ffi_options_set_cache(leveldb_options_t *, leveldb_cache_t *);
FFI_EXPORT void leveldb_ffi_options_set_block_size(leveldb_options_t *, size_t);
FFI_EXPORT void leveldb_ffi_options_set_block_restart_interval(leveldb_options_t *, int);
FFI_EXPORT void leveldb_ffi_options_set_max_file_size(leveldb_options_t *, size_t);
FFI_EXPORT void leveldb_ffi_options_set_disable_seek_autocompaction(leveldb_options_t *, uint8_t);
enum { leveldb_ffi_no_compression = 0, leveldb_ffi_snappy_compression = 1, leveldb_ffi_zlib_raw_compression = 4 };
FFI_EXPORT void leveldb_ffi_options_set_compression(leveldb_options_t *, int);

FFI_EXPORT leveldb_comparator_t *leveldb_ffi_comparator_create(void *state, void (*destructor)(void *),
                                                               int (*compare)(void *, const char *a, size_t alen,
                                                                              const char *b, size_t blen),
                                                               const char *(*name)(void *));
FFI_EXPORT void leveldb_ffi_comparator_destroy(leveldb_comparator_t *);

FFI_EXPORT leveldb_filterpolicy_t *leveldb_ffi_filterpolicy_create(
    void *state, void (*destructor)(void *),
    char *(*create_filter)(void *, const char *const *key_array, const size_t *key_length_array, int num_keys,
                           size_t *filter_length),
    uint8_t (*key_may_match)(void *, const char *key, size_t length, const char *filter, size_t filter_length),
    const char *(*name)(void *));
FFI_EXPORT void leveldb_ffi_filterpolicy_destroy(leveldb_filterpolicy_t *);

FFI_EXPORT leveldb_filterpolicy_t *leveldb_ffi_filterpolicy_create_bloom(int bits_per_key);

FFI_EXPORT leveldb_readoptions_t *leveldb_ffi_readoptions_create(void);
FFI_EXPORT void leveldb_ffi_readoptions_destroy(leveldb_readoptions_t *);
FFI_EXPORT void leveldb_ffi_readoptions_set_verify_checksums(leveldb_readoptions_t *, uint8_t);
FFI_EXPORT void leveldb_ffi_readoptions_set_fill_cache(leveldb_readoptions_t *, uint8_t);
FFI_EXPORT void leveldb_ffi_readoptions_set_snapshot(leveldb_readoptions_t *, const leveldb_snapshot_t *);

FFI_EXPORT leveldb_writeoptions_t *leveldb_ffi_writeoptions_create(void);
FFI_EXPORT void leveldb_ffi_writeoptions_destroy(leveldb_writeoptions_t *);
FFI_EXPORT void leveldb_ffi_writeoptions_set_sync(leveldb_writeoptions_t *, uint8_t);

FFI_EXPORT leveldb_cache_t *leveldb_ffi_cache_create_lru(size_t capacity);
FFI_EXPORT void leveldb_ffi_cache_destroy(leveldb_cache_t *cache);

FFI_EXPORT leveldb_env_t *leveldb_ffi_create_default_env(void);
FFI_EXPORT void leveldb_ffi_env_destroy(leveldb_env_t *);

FFI_EXPORT char *leveldb_ffi_env_get_test_directory(leveldb_env_t *);

FFI_EXPORT void leveldb_ffi_free(void *ptr);

FFI_EXPORT int leveldb_ffi_major_version(void);

FFI_EXPORT int leveldb_ffi_minor_version(void);

#ifdef __cplusplus
} /* end extern "C" */
#endif
