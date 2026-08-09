#ifndef LOCALIZATION_TEST_ARDUINO_H
#define LOCALIZATION_TEST_ARDUINO_H

#include <cstddef>
#include <cstring>
#include <string>

class String {
  public:
    String() = default;
    String(const char *value) : value_(value ? value : "") {}
    String(const std::string &value) : value_(value) {}

    size_t length() const { return value_.length(); }
    bool isEmpty() const { return value_.empty(); }
    const char *c_str() const { return value_.c_str(); }

    int indexOf(const char *needle, size_t from = 0) const {
        if (!needle || from > value_.length()) return -1;
        const size_t found = value_.find(needle, from);
        return found == std::string::npos ? -1 : static_cast<int>(found);
    }

    String substring(size_t from) const {
        return from >= value_.length() ? String() : String(value_.substr(from));
    }

    String substring(size_t from, size_t to) const {
        if (from >= value_.length() || to <= from) return String();
        return String(value_.substr(from, to - from));
    }

    bool startsWith(const char *prefix) const {
        return prefix && value_.compare(0, std::strlen(prefix), prefix) == 0;
    }

    bool startsWith(const String &prefix) const { return startsWith(prefix.c_str()); }

    String &operator+=(const String &other) {
        value_ += other.value_;
        return *this;
    }

    String &operator+=(const char *other) {
        value_ += other ? other : "";
        return *this;
    }

    bool operator==(const String &other) const { return value_ == other.value_; }
    bool operator==(const char *other) const { return value_ == (other ? other : ""); }
    bool operator!=(const String &other) const { return !(*this == other); }
    bool operator!=(const char *other) const { return !(*this == other); }

  private:
    std::string value_;
};

inline bool operator==(const char *left, const String &right) { return right == left; }
inline bool operator!=(const char *left, const String &right) { return right != left; }
inline String operator+(const String &left, const String &right) {
    String result(left);
    result += right;
    return result;
}
inline String operator+(const String &left, const char *right) {
    String result(left);
    result += right;
    return result;
}
inline String operator+(const char *left, const String &right) {
    String result(left);
    result += right;
    return result;
}

#endif
