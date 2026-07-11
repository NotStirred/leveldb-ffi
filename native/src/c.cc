
#include <atomic>
#include <leveldb/c.h>
#include <leveldb_ffi/c.h>
#include <leveldb_ffi/no_throw.h>

const char *EXCEPTION_THROWN_MESSAGE =
    "An exception was thrown in LevelDB. The FFI has disabled itself in an attempt to save the DB";

/// Once an exception is thrown all methods in the ABI will do nothing, or return a default value.
/// LevelDB does not throw or handle exceptions in any way, as such the DB will be in an unknown state after any throw.
std::atomic_bool exception_thrown{false};

FFI_EXPORT leveldb_t *leveldb_ffi_open(const leveldb_options_t *options, const char *name, char **errptr) {
  RET_NOTHROW_ERR(leveldb_open(options, name, errptr), nullptr);
}

FFI_EXPORT void leveldb_ffi_close(leveldb_t *db) { NO_THROW(leveldb_close(db)); }

FFI_EXPORT void leveldb_ffi_put(leveldb_t *db, const leveldb_writeoptions_t *options, const char *key, size_t keylen,
                                const char *val, size_t vallen, char **errptr) {
  NO_THROW_ERR(leveldb_put(db, options, key, keylen, val, vallen, errptr));
}

FFI_EXPORT void leveldb_ffi_delete(leveldb_t *db, const leveldb_writeoptions_t *options, const char *key, size_t keylen,
                                   char **errptr) {
  NO_THROW_ERR(leveldb_delete(db, options, key, keylen, errptr));
}

FFI_EXPORT void leveldb_ffi_write(leveldb_t *db, const leveldb_writeoptions_t *options, leveldb_writebatch_t *batch,
                                  char **errptr) {
  NO_THROW_ERR(leveldb_write(db, options, batch, errptr));
}

FFI_EXPORT char *leveldb_ffi_get(leveldb_t *db, const leveldb_readoptions_t *options, const char *key, size_t keylen,
                                 size_t *vallen, char **errptr) {
  RET_NOTHROW_ERR(leveldb_get(db, options, key, keylen, vallen, errptr), nullptr);
}

FFI_EXPORT leveldb_iterator_t *leveldb_ffi_create_iterator(leveldb_t *db, const leveldb_readoptions_t *options) {
  RET_NOTHROW(leveldb_create_iterator(db, options), nullptr);
}

FFI_EXPORT const leveldb_snapshot_t *leveldb_ffi_create_snapshot(leveldb_t *db) {
  RET_NOTHROW(leveldb_create_snapshot(db), nullptr);
}

FFI_EXPORT void leveldb_ffi_release_snapshot(leveldb_t *db, const leveldb_snapshot_t *snapshot) {
  NO_THROW(leveldb_release_snapshot(db, snapshot));
}

FFI_EXPORT char *leveldb_ffi_property_value(leveldb_t *db, const char *propname) {
  RET_NOTHROW(leveldb_property_value(db, propname), nullptr);
}

FFI_EXPORT void leveldb_ffi_approximate_sizes(leveldb_t *db, int num_ranges, const char *const *range_start_key,
                                              const size_t *range_start_key_len, const char *const *range_limit_key,
                                              const size_t *range_limit_key_len, uint64_t *sizes) {
  NO_THROW(leveldb_approximate_sizes(db, num_ranges, range_start_key, range_start_key_len, range_limit_key,
                                     range_limit_key_len, sizes));
}

FFI_EXPORT void leveldb_ffi_compact_range(leveldb_t *db, const char *start_key, size_t start_key_len,
                                          const char *limit_key, size_t limit_key_len) {
  NO_THROW(leveldb_compact_range(db, start_key, start_key_len, limit_key, limit_key_len));
}

FFI_EXPORT void leveldb_ffi_destroy_db(const leveldb_options_t *options, const char *name, char **errptr) {
  NO_THROW_ERR(leveldb_destroy_db(options, name, errptr));
}

FFI_EXPORT void leveldb_ffi_repair_db(const leveldb_options_t *options, const char *name, char **errptr) {
  NO_THROW_ERR(leveldb_repair_db(options, name, errptr));
}

FFI_EXPORT void leveldb_ffi_iter_destroy(leveldb_iterator_t *iterator) { NO_THROW(leveldb_iter_destroy(iterator)); }
FFI_EXPORT uint8_t leveldb_ffi_iter_valid(const leveldb_iterator_t *iterator) {
  RET_NOTHROW(leveldb_iter_valid(iterator), 0);
}
FFI_EXPORT void leveldb_ffi_iter_seek_to_first(leveldb_iterator_t *iterator) {
  NO_THROW(leveldb_iter_seek_to_first(iterator));
}
FFI_EXPORT void leveldb_ffi_iter_seek_to_last(leveldb_iterator_t *iterator) {
  NO_THROW(leveldb_iter_seek_to_last(iterator));
}
FFI_EXPORT void leveldb_ffi_iter_seek(leveldb_iterator_t *iterator, const char *k, size_t klen) {
  NO_THROW(leveldb_iter_seek(iterator, k, klen));
}
FFI_EXPORT void leveldb_ffi_iter_next(leveldb_iterator_t *iterator) { NO_THROW(leveldb_iter_next(iterator)); }
FFI_EXPORT void leveldb_ffi_iter_prev(leveldb_iterator_t *iterator) { NO_THROW(leveldb_iter_prev(iterator)); }
FFI_EXPORT const char *leveldb_ffi_iter_key(const leveldb_iterator_t *iterator, size_t *klen) {
  RET_NOTHROW(leveldb_iter_key(iterator, klen), nullptr);
}
FFI_EXPORT const char *leveldb_ffi_iter_value(const leveldb_iterator_t *iterator, size_t *vlen) {
  RET_NOTHROW(leveldb_iter_value(iterator, vlen), nullptr);
}
FFI_EXPORT void leveldb_ffi_iter_get_error(const leveldb_iterator_t *iterator, char **errptr) {
  NO_THROW_ERR(leveldb_iter_get_error(iterator, errptr));
}

FFI_EXPORT leveldb_writebatch_t *leveldb_ffi_writebatch_create() { RET_NOTHROW(leveldb_writebatch_create(), nullptr); }
FFI_EXPORT void leveldb_ffi_writebatch_destroy(leveldb_writebatch_t *writebatch) {
  NO_THROW(leveldb_writebatch_destroy(writebatch));
}
FFI_EXPORT void leveldb_ffi_writebatch_clear(leveldb_writebatch_t *writebatch) {
  NO_THROW(leveldb_writebatch_clear(writebatch));
}
FFI_EXPORT void leveldb_ffi_writebatch_put(leveldb_writebatch_t *writebatch, const char *key, size_t klen,
                                           const char *val, size_t vlen) {
  NO_THROW(leveldb_writebatch_put(writebatch, key, klen, val, vlen));
}
FFI_EXPORT void leveldb_ffi_writebatch_delete(leveldb_writebatch_t *writebatch, const char *key, size_t klen) {
  NO_THROW(leveldb_writebatch_delete(writebatch, key, klen));
}
FFI_EXPORT void leveldb_ffi_writebatch_iterate(const leveldb_writebatch_t *writebatch, void *state,
                                               void (*put)(void *, const char *k, size_t klen, const char *v,
                                                           size_t vlen),
                                               void (*deleted)(void *, const char *k, size_t klen)) {
  NO_THROW(leveldb_writebatch_iterate(writebatch, state, put, deleted));
}
FFI_EXPORT void leveldb_ffi_writebatch_append(leveldb_writebatch_t *destination, const leveldb_writebatch_t *source) {
  NO_THROW(leveldb_writebatch_append(destination, source));
}

FFI_EXPORT leveldb_options_t *leveldb_ffi_options_create() { RET_NOTHROW(leveldb_options_create(), nullptr); }
FFI_EXPORT void leveldb_ffi_options_destroy(leveldb_options_t *options) { NO_THROW(leveldb_options_destroy(options)); }
FFI_EXPORT void leveldb_ffi_options_set_comparator(leveldb_options_t *options, leveldb_comparator_t *comparator) {
  NO_THROW(leveldb_options_set_comparator(options, comparator));
}
FFI_EXPORT void leveldb_ffi_options_set_filter_policy(leveldb_options_t *options,
                                                      leveldb_filterpolicy_t *filterpolicy) {
  NO_THROW(leveldb_options_set_filter_policy(options, filterpolicy));
}
FFI_EXPORT void leveldb_ffi_options_set_create_if_missing(leveldb_options_t *options, uint8_t create_if_missing) {
  NO_THROW(leveldb_options_set_create_if_missing(options, create_if_missing));
}
FFI_EXPORT void leveldb_ffi_options_set_error_if_exists(leveldb_options_t *options, uint8_t error_if_exists) {
  NO_THROW(leveldb_options_set_error_if_exists(options, error_if_exists));
}
FFI_EXPORT void leveldb_ffi_options_set_paranoid_checks(leveldb_options_t *options, uint8_t paranoid_checks) {
  NO_THROW(leveldb_options_set_paranoid_checks(options, paranoid_checks));
}
FFI_EXPORT void leveldb_ffi_options_set_env(leveldb_options_t *options, leveldb_env_t *env) {
  NO_THROW(leveldb_options_set_env(options, env));
}
FFI_EXPORT void leveldb_ffi_options_set_info_log(leveldb_options_t *options, leveldb_logger_t *logger) {
  NO_THROW(leveldb_options_set_info_log(options, logger));
}
FFI_EXPORT void leveldb_ffi_options_set_write_buffer_size(leveldb_options_t *options, size_t write_buffer_size) {
  NO_THROW(leveldb_options_set_write_buffer_size(options, write_buffer_size));
}
FFI_EXPORT void leveldb_ffi_options_set_max_open_files(leveldb_options_t *options, int max_open_files) {
  NO_THROW(leveldb_options_set_max_open_files(options, max_open_files));
}
FFI_EXPORT void leveldb_ffi_options_set_cache(leveldb_options_t *options, leveldb_cache_t *cache) {
  NO_THROW(leveldb_options_set_cache(options, cache));
}
FFI_EXPORT void leveldb_ffi_options_set_block_size(leveldb_options_t *options, size_t block_size) {
  NO_THROW(leveldb_options_set_block_size(options, block_size));
}
FFI_EXPORT void leveldb_ffi_options_set_block_restart_interval(leveldb_options_t *options, int block_restart_interval) {
  NO_THROW(leveldb_options_set_block_restart_interval(options, block_restart_interval));
}
FFI_EXPORT void leveldb_ffi_options_set_max_file_size(leveldb_options_t *options, size_t max_file_size) {
  NO_THROW(leveldb_options_set_max_file_size(options, max_file_size));
}
FFI_EXPORT void leveldb_ffi_options_set_disable_seek_autocompaction(leveldb_options_t *options,
                                                                    uint8_t disable_seek_autocompaction) {
  NO_THROW(leveldb_options_set_disable_seek_autocompaction(options, disable_seek_autocompaction));
}
FFI_EXPORT void leveldb_ffi_options_set_compression(leveldb_options_t *options, int compression) {
  NO_THROW(leveldb_options_set_compression(options, compression));
}

FFI_EXPORT leveldb_comparator_t *leveldb_ffi_comparator_create(void *state, void (*destructor)(void *),
                                                               int (*compare)(void *, const char *a, size_t alen,
                                                                              const char *b, size_t blen),
                                                               const char *(*name)(void *)) {
  RET_NOTHROW(leveldb_comparator_create(state, destructor, compare, name), nullptr);
}
FFI_EXPORT void leveldb_ffi_comparator_destroy(leveldb_comparator_t *comparator) {
  NO_THROW(leveldb_comparator_destroy(comparator));
}

FFI_EXPORT leveldb_filterpolicy_t *leveldb_ffi_filterpolicy_create(
    void *state, void (*destructor)(void *),
    char *(*create_filter)(void *, const char *const *key_array, const size_t *key_length_array, int num_keys,
                           size_t *filter_length),
    uint8_t (*key_may_match)(void *, const char *key, size_t length, const char *filter, size_t filter_length),
    const char *(*name)(void *)) {
  RET_NOTHROW(leveldb_filterpolicy_create(state, destructor, create_filter, key_may_match, name), nullptr);
}
FFI_EXPORT void leveldb_ffi_filterpolicy_destroy(leveldb_filterpolicy_t *filterpolicy) {
  NO_THROW(leveldb_filterpolicy_destroy(filterpolicy));
}
FFI_EXPORT leveldb_filterpolicy_t *leveldb_ffi_filterpolicy_create_bloom(int bits_per_key) {
  RET_NOTHROW(leveldb_filterpolicy_create_bloom(bits_per_key), nullptr);
}

FFI_EXPORT leveldb_readoptions_t *leveldb_ffi_readoptions_create() {
  RET_NOTHROW(leveldb_readoptions_create(), nullptr);
}
FFI_EXPORT void leveldb_ffi_readoptions_destroy(leveldb_readoptions_t *readoptions) {
  NO_THROW(leveldb_readoptions_destroy(readoptions));
}
FFI_EXPORT void leveldb_ffi_readoptions_set_verify_checksums(leveldb_readoptions_t *readoptions,
                                                             uint8_t verify_checksums) {
  NO_THROW(leveldb_readoptions_set_verify_checksums(readoptions, verify_checksums));
}
FFI_EXPORT void leveldb_ffi_readoptions_set_fill_cache(leveldb_readoptions_t *readoptions, uint8_t fill_cache) {
  NO_THROW(leveldb_readoptions_set_fill_cache(readoptions, fill_cache));
}
FFI_EXPORT void leveldb_ffi_readoptions_set_snapshot(leveldb_readoptions_t *readoptions,
                                                     const leveldb_snapshot_t *snapshot) {
  NO_THROW(leveldb_readoptions_set_snapshot(readoptions, snapshot));
}

FFI_EXPORT leveldb_writeoptions_t *leveldb_ffi_writeoptions_create() {
  RET_NOTHROW(leveldb_writeoptions_create(), nullptr);
}
FFI_EXPORT void leveldb_ffi_writeoptions_destroy(leveldb_writeoptions_t *writeoptions) {
  NO_THROW(leveldb_writeoptions_destroy(writeoptions));
}
FFI_EXPORT void leveldb_ffi_writeoptions_set_sync(leveldb_writeoptions_t *options, uint8_t sync) {
  NO_THROW(leveldb_writeoptions_set_sync(options, sync));
}

FFI_EXPORT leveldb_cache_t *leveldb_ffi_cache_create_lru(size_t capacity) {
  RET_NOTHROW(leveldb_cache_create_lru(capacity), nullptr);
}
FFI_EXPORT void leveldb_ffi_cache_destroy(leveldb_cache_t *cache) { NO_THROW(leveldb_cache_destroy(cache)); }

FFI_EXPORT leveldb_env_t *leveldb_ffi_create_default_env() { RET_NOTHROW(leveldb_create_default_env(), nullptr); }
FFI_EXPORT void leveldb_ffi_env_destroy(leveldb_env_t *env) { NO_THROW(leveldb_env_destroy(env)); }

FFI_EXPORT char *leveldb_ffi_env_get_test_directory(leveldb_env_t *env) {
  RET_NOTHROW(leveldb_env_get_test_directory(env), nullptr);
}

FFI_EXPORT void leveldb_ffi_free(void *ptr) { NO_THROW(leveldb_free(ptr)); }

FFI_EXPORT int leveldb_ffi_major_version() { RET_NOTHROW(leveldb_major_version(), 0); }

FFI_EXPORT int leveldb_ffi_minor_version() { RET_NOTHROW(leveldb_minor_version(), 0); }
