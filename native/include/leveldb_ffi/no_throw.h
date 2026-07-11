#pragma once
#include <cstring>

#define NO_THROW(action)                                                                                               \
  try {                                                                                                                \
    if (!exception_thrown) {                                                                                           \
      action;                                                                                                          \
    }                                                                                                                  \
  } catch (...) {                                                                                                      \
    exception_thrown = true;                                                                                           \
  }

#define NO_THROW_ERR(action)                                                                                           \
  try {                                                                                                                \
    if (!exception_thrown) {                                                                                           \
      action;                                                                                                          \
    }                                                                                                                  \
  } catch (...) {                                                                                                      \
    exception_thrown = true;                                                                                           \
    if (*errptr == nullptr) {                                                                                          \
      *errptr = strdup(EXCEPTION_THROWN_MESSAGE);                                                                      \
    }                                                                                                                  \
  }

#define RET_NOTHROW(action, default_return)                                                                            \
  try {                                                                                                                \
    if (!exception_thrown) {                                                                                           \
      return action;                                                                                                   \
    }                                                                                                                  \
  } catch (...) {                                                                                                      \
    exception_thrown = true;                                                                                           \
  }                                                                                                                    \
  return default_return;

#define RET_NOTHROW_ERR(action, default_return)                                                                        \
  try {                                                                                                                \
    if (!exception_thrown) {                                                                                           \
      return action;                                                                                                   \
    }                                                                                                                  \
  } catch (...) {                                                                                                      \
    exception_thrown = true;                                                                                           \
  }                                                                                                                    \
  if (*errptr == nullptr) {                                                                                            \
    *errptr = strdup(EXCEPTION_THROWN_MESSAGE);                                                                        \
  }                                                                                                                    \
  return default_return;
