// Copyright satoren
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include <cassert>
#include "kaguya/config.hpp"

namespace kaguya {
/// @addtogroup optional
///  @{

struct bad_optional_access : std::exception {};
struct nullopt_t {};

/// @brief self implement for std::optional(C++17 feature).
template <class T> class optional {
  typedef void (optional::*bool_type)() const;
  void this_type_does_not_support_comparisons() const {}

public:
  optional() : value_(0){};
  optional(nullopt_t) : value_(0){};
  optional(const optional &other) : value_(0) {
    if (other) {
      value_ = new (&storage_) T(other.value());
    }
  }
  optional(const T &value) { value_ = new (&storage_) T(value); }

  ~optional() { destruct(); }
  optional &operator=(nullopt_t) {
    destruct();
    return *this;
  }
  optional &operator=(const optional &other) {
    if (other) {
      *this = other.value();
    } else {
      destruct();
    }
    return *this;
  }
  optional &operator=(const T &value) {
    if (value_) {
      *value_ = value;
    } else {
      value_ = new (&storage_) T(value);
    }
    return *this;
  }

#if KAGUYA_USE_CPP11
  optional(optional &&other) : value_(0) {
    if (other) {
      value_ = new (&storage_) T(std::move(other.value()));
    }
  }
  optional(T &&value) { value_ = new (&storage_) T(std::move(value)); }
  optional &operator=(optional &&other) {
    if (other) {
      *this = std::move(other.value());
    } else {
      destruct();
    }
    return *this;
  }
  optional &operator=(T &&value) {
    if (value_) {
      *value_ = std::move(value);
    } else {
      value_ = new (&storage_) T(std::move(value));
    }
    return *this;
  }
#endif

  operator bool_type() const {
    this_type_does_not_support_comparisons();
    return value_ != 0 ? &optional::this_type_does_not_support_comparisons : 0;
  }
  T &value() {
    if (value_) {
      return *value_;
    }
    throw bad_optional_access();
  }
  const T &value() const {
    if (value_) {
      return *value_;
    }
    throw bad_optional_access();
  }

#if KAGUYA_USE_CPP11
  template <class U> T value_or(U &&default_value) const {
    if (value_) {
      return *value_;
    }
    return default_value;
  }
#else
  template <class U> T value_or(const U &default_value) const {
    if (value_) {
      return *value_;
    }
    return default_value;
  }
#endif
  const T *operator->() const {
    assert(value_);
    return value_;
  }
  T *operator->() {
    assert(value_);
    return value_;
  }
  const T &operator*() const {
    assert(value_);
    return *value_;
  }
  T &operator*() {
    assert(value_);
    return *value_;
  }

private:
  void destruct() {
    if (value_) {
      value_->~T();
      value_ = 0;
    }
  }

  typename standard::aligned_storage<
      sizeof(T), standard::alignment_of<T>::value>::type storage_;

  T *value_;
};

/// @brief specialize optional for reference.
/// sizeof(optional<T&>) == sizeof(T*)
template <class T> class optional<T &> {
  typedef void (optional::*bool_type)() const;
  void this_type_does_not_support_comparisons() const {}

public:
  optional() : value_(0){};
  optional(nullopt_t) : value_(0){};

  optional(const optional &other) : value_(other.value_) {}
  optional(T &value) : value_(&value) {}

  ~optional() {}
  optional &operator=(nullopt_t) {
    value_ = 0;
    return *this;
  }
  optional &operator=(const optional &other) {
    value_ = other.value_;
    return *this;
  }
  optional &operator=(T &value) {
    value_ = &value;
    return *this;
  }
  operator bool_type() const {
    this_type_does_not_support_comparisons();
    return value_ != 0 ? &optional::this_type_does_not_support_comparisons : 0;
  }
  T &value() {
    if (value_) {
      return *value_;
    }
    throw bad_optional_access();
  }
  const T &value() const {
    if (value_) {
      return *value_;
    }
    throw bad_optional_access();
  }

#if KAGUYA_USE_CPP11
  T &value_or(T &default_value) const {
    if (value_) {
      return *value_;
    }
    return default_value;
  }
#else
  T &value_or(T &default_value) const {
    if (value_) {
      return *value_;
    }
    return default_value;
  }
#endif

  const T *operator->() const {
    assert(value_);
    return value_;
  }
  T *operator->() {
    assert(value_);
    return value_;
  }
  const T &operator*() const {
    assert(value_);
    return *value_;
  }
  T &operator*() {
    assert(value_);
    return *value_;
  }

private:
  T *value_;
};

/// @name relational operators
/// @brief
///@{
template <class T>
bool operator==(const optional<T> &lhs, const optional<T> &rhs) {
  if (bool(lhs) != bool(rhs)) {
    return false;
  }
  if (bool(lhs) == false) {
    return true;
  }
  return lhs.value() == rhs.value();
}
template <class T>
bool operator!=(const optional<T> &lhs, const optional<T> &rhs) {
  return !(lhs == rhs);
}
template <class T>
bool operator<(const optional<T> &lhs, const optional<T> &rhs) {
  if (!bool(rhs)) {
    return false;
  }
  if (!bool(lhs)) {
    return true;
  }
  return lhs.value() < rhs.value();
}
template <class T>
bool operator<=(const optional<T> &lhs, const optional<T> &rhs) {
  return !(rhs < lhs);
}
template <class T>
bool operator>(const optional<T> &lhs, const optional<T> &rhs) {
  return rhs < lhs;
}
template <class T>
bool operator>=(const optional<T> &lhs, const optional<T> &rhs) {
  return !(lhs < rhs);
}
/// @}

/// @}
}
