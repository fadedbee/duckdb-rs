/*
Copyright 2018-2022 Stichting DuckDB Foundation

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#define DUCKDB_AMALGAMATION 1
#define DUCKDB_SOURCE_ID "7c111322d"
#define DUCKDB_VERSION "v0.5.1"
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/connection.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/profiler_format.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/constants.hpp
//
//
//===----------------------------------------------------------------------===//



#include <memory>
#include <cstdint>
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/string.hpp
//
//
//===----------------------------------------------------------------------===//



#include <string>
#include <sstream>

namespace duckdb {
using std::string;
}

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/winapi.hpp
//
//
//===----------------------------------------------------------------------===//



#ifndef DUCKDB_API
#ifdef _WIN32
#if defined(DUCKDB_BUILD_LIBRARY) && !defined(DUCKDB_BUILD_LOADABLE_EXTENSION)
#define DUCKDB_API __declspec(dllexport)
#else
#define DUCKDB_API __declspec(dllimport)
#endif
#else
#define DUCKDB_API
#endif
#endif

#ifndef DUCKDB_EXTENSION_API
#ifdef _WIN32
#ifdef DUCKDB_BUILD_LOADABLE_EXTENSION
#define DUCKDB_EXTENSION_API __declspec(dllexport)
#else
#define DUCKDB_EXTENSION_API
#endif
#else
#define DUCKDB_EXTENSION_API __attribute__((visibility("default")))
#endif
#endif


namespace duckdb {

// API versions
// if no explicit API version is defined, the latest API version is used
// Note that using older API versions (i.e. not using DUCKDB_API_LATEST) is deprecated.
// These will not be supported long-term, and will be removed in future versions.

#ifndef DUCKDB_API_0_3_1
#define DUCKDB_API_0_3_1 1
#endif
#ifndef DUCKDB_API_0_3_2
#define DUCKDB_API_0_3_2 2
#endif
#ifndef DUCKDB_API_LATEST
#define DUCKDB_API_LATEST DUCKDB_API_0_3_2
#endif

#ifndef DUCKDB_API_VERSION
#define DUCKDB_API_VERSION DUCKDB_API_LATEST
#endif

//! inline std directives that we use frequently
using std::move;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using data_ptr = unique_ptr<char[]>;
using std::make_shared;

// NOTE: there is a copy of this in the Postgres' parser grammar (gram.y)
#define DEFAULT_SCHEMA "main"
#define TEMP_SCHEMA    "temp"
#define INVALID_SCHEMA ""

//! a saner size_t for loop indices etc
typedef uint64_t idx_t;

//! The type used for row identifiers
typedef int64_t row_t;

//! The type used for hashes
typedef uint64_t hash_t;

//! data pointers
typedef uint8_t data_t;
typedef data_t *data_ptr_t;
typedef const data_t *const_data_ptr_t;

//! Type used for the selection vector
typedef uint32_t sel_t;
//! Type used for transaction timestamps
typedef idx_t transaction_t;

//! Type used for column identifiers
typedef idx_t column_t;
//! Type used for storage (column) identifiers
typedef idx_t storage_t;
//! Special value used to signify the ROW ID of a table
DUCKDB_API extern const column_t COLUMN_IDENTIFIER_ROW_ID;
DUCKDB_API bool IsRowIdColumnId(column_t column_id);

//! The maximum row identifier used in tables
extern const row_t MAX_ROW_ID;

extern const transaction_t TRANSACTION_ID_START;
extern const transaction_t MAX_TRANSACTION_ID;
extern const transaction_t MAXIMUM_QUERY_ID;
extern const transaction_t NOT_DELETED_ID;

extern const double PI;

struct DConstants {
	//! The value used to signify an invalid index entry
	static constexpr const idx_t INVALID_INDEX = idx_t(-1);
};

struct Storage {
	//! The size of a hard disk sector, only really needed for Direct IO
	constexpr static int SECTOR_SIZE = 4096;
	//! Block header size for blocks written to the storage
	constexpr static int BLOCK_HEADER_SIZE = sizeof(uint64_t);
	// Size of a memory slot managed by the StorageManager. This is the quantum of allocation for Blocks on DuckDB. We
	// default to 256KB. (1 << 18)
	constexpr static int BLOCK_ALLOC_SIZE = 262144;
	//! The actual memory space that is available within the blocks
	constexpr static int BLOCK_SIZE = BLOCK_ALLOC_SIZE - BLOCK_HEADER_SIZE;
	//! The size of the headers. This should be small and written more or less atomically by the hard disk. We default
	//! to the page size, which is 4KB. (1 << 12)
	constexpr static int FILE_HEADER_SIZE = 4096;
};

uint64_t NextPowerOfTwo(uint64_t v);

} // namespace duckdb


namespace duckdb {

enum class ProfilerPrintFormat : uint8_t { QUERY_TREE, JSON, QUERY_TREE_OPTIMIZER };

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/serializer/buffered_file_writer.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/serializer.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/common.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/helper.hpp
//
//
//===----------------------------------------------------------------------===//




#include <string.h>

#ifdef _MSC_VER
#define suint64_t int64_t
#endif

#if defined(_WIN32) || defined(_WIN64)
#define DUCKDB_WINDOWS
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#define DUCKDB_POSIX
#endif

namespace duckdb {

// explicit fallthrough for switch_statementss
#ifndef __has_cpp_attribute // For backwards compatibility
#define __has_cpp_attribute(x) 0
#endif
#if __has_cpp_attribute(clang::fallthrough)
#define DUCKDB_EXPLICIT_FALLTHROUGH [[clang::fallthrough]]
#elif __has_cpp_attribute(gnu::fallthrough)
#define DUCKDB_EXPLICIT_FALLTHROUGH [[gnu::fallthrough]]
#else
#define DUCKDB_EXPLICIT_FALLTHROUGH
#endif

#if !defined(_MSC_VER) && (__cplusplus < 201402L)
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args &&... args) {
	return unique_ptr<T>(new T(std::forward<Args>(args)...));
}
#else // Visual Studio has make_unique
using std::make_unique;
#endif
template <typename S, typename T, typename... Args>
unique_ptr<S> make_unique_base(Args &&... args) {
	return unique_ptr<S>(new T(std::forward<Args>(args)...));
}

template <typename T, typename S>
unique_ptr<S> unique_ptr_cast(unique_ptr<T> src) {
	return unique_ptr<S>(static_cast<S *>(src.release()));
}

struct SharedConstructor {
	template <class T, typename... ARGS>
	static shared_ptr<T> Create(ARGS &&...args) {
		return make_shared<T>(std::forward<ARGS>(args)...);
	}
};

struct UniqueConstructor {
	template <class T, typename... ARGS>
	static unique_ptr<T> Create(ARGS &&...args) {
		return make_unique<T>(std::forward<ARGS>(args)...);
	}
};

template <typename T>
T MaxValue(T a, T b) {
	return a > b ? a : b;
}

template <typename T>
T MinValue(T a, T b) {
	return a < b ? a : b;
}

template <typename T>
T AbsValue(T a) {
	return a < 0 ? -a : a;
}

template<class T, T val=8>
static inline T AlignValue(T n) {
	return ((n + (val - 1)) / val) * val;
}

template<class T, T val=8>
static inline bool ValueIsAligned(T n) {
	return (n % val) == 0;
}

template <typename T>
T SignValue(T a) {
	return a < 0 ? -1 : 1;
}

template <typename T>
const T Load(const_data_ptr_t ptr) {
	T ret;
	memcpy(&ret, ptr, sizeof(ret));
	return ret;
}

template <typename T>
void Store(const T val, data_ptr_t ptr) {
	memcpy(ptr, (void *)&val, sizeof(val));
}

//! This assigns a shared pointer, but ONLY assigns if "target" is not equal to "source"
//! If this is often the case, this manner of assignment is significantly faster (~20X faster)
//! Since it avoids the need of an atomic incref/decref at the cost of a single pointer comparison
//! Benchmark: https://gist.github.com/Mytherin/4db3faa8e233c4a9b874b21f62bb4b96
//! If the shared pointers are not the same, the penalty is very low (on the order of 1%~ slower)
//! This method should always be preferred if there is a (reasonable) chance that the pointers are the same
template<class T>
void AssignSharedPointer(shared_ptr<T> &target, const shared_ptr<T> &source) {
	if (target.get() != source.get()) {
		target = source;
	}
}

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/exception.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/assert.hpp
//
//
//===----------------------------------------------------------------------===//





#if (defined(DUCKDB_USE_STANDARD_ASSERT) || !defined(DEBUG)) && !defined(DUCKDB_FORCE_ASSERT)

#include <assert.h>
#define D_ASSERT assert
#else
namespace duckdb {
DUCKDB_API void DuckDBAssertInternal(bool condition, const char *condition_name, const char *file, int linenr);
}

#define D_ASSERT(condition) duckdb::DuckDBAssertInternal(bool(condition), #condition, __FILE__, __LINE__)

#endif


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/exception_format_value.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/single_thread_ptr.hpp
//
//
//===----------------------------------------------------------------------===//



class RefCounter {
public:
	uint32_t pn;
	RefCounter() : pn(1) {
	}
	void inc() {
		++pn;
	}
	void dec() {
		--pn;
	}
	uint32_t getPn() const {
		return pn;
	}
	virtual ~RefCounter() {
	}
};

namespace duckdb {
template <typename T>
class single_thread_ptr {
public:
	T *ptr;                // contained pointer
	RefCounter *ref_count; // reference counter

public:
	// Default constructor, constructs an empty single_thread_ptr.
	constexpr single_thread_ptr() : ptr(nullptr), ref_count(nullptr) {
	}
	// Construct empty single_thread_ptr.
	constexpr single_thread_ptr(std::nullptr_t) : ptr(nullptr), ref_count(nullptr) {
	}
	// Construct a single_thread_ptr that wraps raw pointer.

	single_thread_ptr(RefCounter *r, T *p) {
		ptr = p;
		ref_count = r;
	}

	template <class U>
	single_thread_ptr(RefCounter *r, U *p) {
		ptr = p;
		ref_count = r;
	}

	// Copy  constructor.
	single_thread_ptr(const single_thread_ptr &sp) : ptr(nullptr), ref_count(nullptr) {
		if (sp.ptr) {
			ptr = sp.ptr;
			ref_count = sp.ref_count;
			ref_count->inc();
		}
	}

	// Conversion constructor.
	template <typename U>
	single_thread_ptr(const single_thread_ptr<U> &sp) : ptr(nullptr), ref_count(nullptr) {
		if (sp.ptr) {
			ptr = sp.ptr;
			ref_count = sp.ref_count;
			ref_count->inc();
		}
	}

	// move  constructor.
	single_thread_ptr(single_thread_ptr &&sp) noexcept : ptr {sp.ptr}, ref_count {sp.ref_count} {
		sp.ptr = nullptr;
		sp.ref_count = nullptr;
	}

	// move  constructor.
	template <class U>
	single_thread_ptr(single_thread_ptr<U> &&sp) noexcept : ptr {sp.ptr}, ref_count {sp.ref_count} {
		sp.ptr = nullptr;
		sp.ref_count = nullptr;
	}

	// No effect if single_thread_ptr is empty or use_count() > 1, otherwise release the resources.
	~single_thread_ptr() {
		release();
	}

	void release() {
		if (ptr && ref_count) {
			ref_count->dec();
			if ((ref_count->getPn()) == 0) {
				delete ref_count;
			}
		}
		ref_count = nullptr;
		ptr = nullptr;
	}

	// Copy assignment.
	single_thread_ptr &operator=(single_thread_ptr sp) noexcept {
		std::swap(this->ptr, sp.ptr);
		std::swap(this->ref_count, sp.ref_count);
		return *this;
	}

	// Dereference pointer to managed object.
	T &operator*() const noexcept {
		return *ptr;
	}
	T *operator->() const noexcept {
		return ptr;
	}

	// Return the contained pointer.
	T *get() const noexcept {
		return ptr;
	}

	// Return use count (use count == 0 if single_thread_ptr is empty).
	long use_count() const noexcept {
		if (ptr)
			return ref_count->getPn();
		else
			return 0;
	}

	// Check if there is an associated managed object.
	explicit operator bool() const noexcept {
		return (ptr);
	}

	// Resets single_thread_ptr to empty.
	void reset() noexcept {
		release();
	}
};

template <class T>
struct _object_and_block : public RefCounter {
	T object;

	template <class... Args>
	explicit _object_and_block(Args &&... args) : object(std::forward<Args>(args)...) {
	}
};

// Operator overloading.
template <typename T, typename U>
inline bool operator==(const single_thread_ptr<T> &sp1, const single_thread_ptr<U> &sp2) {
	return sp1.get() == sp2.get();
}

template <typename T>
inline bool operator==(const single_thread_ptr<T> &sp, std::nullptr_t) noexcept {
	return !sp;
}

template <typename T, typename U>
inline bool operator!=(const single_thread_ptr<T> &sp1, const single_thread_ptr<U> &sp2) {
	return sp1.get() != sp2.get();
}

template <typename T>
inline bool operator!=(const single_thread_ptr<T> &sp, std::nullptr_t) noexcept {
	return sp.get();
}

template <typename T>
inline bool operator!=(std::nullptr_t, const single_thread_ptr<T> &sp) noexcept {
	return sp.get();
}

template <class T, class... Args>
single_thread_ptr<T> single_thread_make_shared(Args &&... args) {
	auto tmp_object = new _object_and_block<T>(std::forward<Args>(args)...);
	return single_thread_ptr<T>(tmp_object, &(tmp_object->object));
}
} // namespace duckdb
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/vector.hpp
//
//
//===----------------------------------------------------------------------===//



#include <vector>

namespace duckdb {
using std::vector;
}


#include <limits>

namespace duckdb {

class Serializer;
class Deserializer;
class Value;
class TypeCatalogEntry;
class Vector;
class ClientContext;
//! Type used to represent dates (days since 1970-01-01)
struct date_t { // NOLINT
	int32_t days;

	date_t() = default;
	explicit inline date_t(int32_t days_p) : days(days_p) {}

	// explicit conversion
	explicit inline operator int32_t() const {return days;}

	// comparison operators
	inline bool operator==(const date_t &rhs) const {return days == rhs.days;};
	inline bool operator!=(const date_t &rhs) const {return days != rhs.days;};
	inline bool operator<=(const date_t &rhs) const {return days <= rhs.days;};
	inline bool operator<(const date_t &rhs) const {return days < rhs.days;};
	inline bool operator>(const date_t &rhs) const {return days > rhs.days;};
	inline bool operator>=(const date_t &rhs) const {return days >= rhs.days;};

	// arithmetic operators
	inline date_t operator+(const int32_t &days) const {return date_t(this->days + days);};
	inline date_t operator-(const int32_t &days) const {return date_t(this->days - days);};

	// in-place operators
	inline date_t &operator+=(const int32_t &days) {this->days += days; return *this;};
	inline date_t &operator-=(const int32_t &days) {this->days -= days; return *this;};

	// special values
	static inline date_t infinity() {return date_t(std::numeric_limits<int32_t>::max()); } // NOLINT
	static inline date_t ninfinity() {return date_t(-std::numeric_limits<int32_t>::max()); } // NOLINT
	static inline date_t epoch() {return date_t(0); } // NOLINT
};

//! Type used to represent time (microseconds)
struct dtime_t { // NOLINT
	int64_t micros;

	dtime_t() = default;
	explicit inline dtime_t(int64_t micros_p) : micros(micros_p) {}
	inline dtime_t& operator=(int64_t micros_p) {micros = micros_p; return *this;}

	// explicit conversion
	explicit inline operator int64_t() const {return micros;}
	explicit inline operator double() const {return micros;}

	// comparison operators
	inline bool operator==(const dtime_t &rhs) const {return micros == rhs.micros;};
	inline bool operator!=(const dtime_t &rhs) const {return micros != rhs.micros;};
	inline bool operator<=(const dtime_t &rhs) const {return micros <= rhs.micros;};
	inline bool operator<(const dtime_t &rhs) const {return micros < rhs.micros;};
	inline bool operator>(const dtime_t &rhs) const {return micros > rhs.micros;};
	inline bool operator>=(const dtime_t &rhs) const {return micros >= rhs.micros;};

	// arithmetic operators
	inline dtime_t operator+(const int64_t &micros) const {return dtime_t(this->micros + micros);};
	inline dtime_t operator+(const double &micros) const {return dtime_t(this->micros + int64_t(micros));};
	inline dtime_t operator-(const int64_t &micros) const {return dtime_t(this->micros - micros);};
	inline dtime_t operator*(const idx_t &copies) const {return dtime_t(this->micros * copies);};
	inline dtime_t operator/(const idx_t &copies) const {return dtime_t(this->micros / copies);};
	inline int64_t operator-(const dtime_t &other) const {return this->micros - other.micros;};

	// in-place operators
	inline dtime_t &operator+=(const int64_t &micros) {this->micros += micros; return *this;};
	inline dtime_t &operator-=(const int64_t &micros) {this->micros -= micros; return *this;};
	inline dtime_t &operator+=(const dtime_t &other) {this->micros += other.micros; return *this;};

	// special values
	static inline dtime_t allballs() {return dtime_t(0); } // NOLINT
};

struct dtime_tz_t : public dtime_t {};

//! Type used to represent timestamps (seconds,microseconds,milliseconds or nanoseconds since 1970-01-01)
struct timestamp_t { // NOLINT
	int64_t value;

	timestamp_t() = default;
	explicit inline timestamp_t(int64_t value_p) : value(value_p) {}
	inline timestamp_t& operator=(int64_t value_p) {value = value_p; return *this;}

	// explicit conversion
	explicit inline operator int64_t() const {return value;}

	// comparison operators
	inline bool operator==(const timestamp_t &rhs) const {return value == rhs.value;};
	inline bool operator!=(const timestamp_t &rhs) const {return value != rhs.value;};
	inline bool operator<=(const timestamp_t &rhs) const {return value <= rhs.value;};
	inline bool operator<(const timestamp_t &rhs) const {return value < rhs.value;};
	inline bool operator>(const timestamp_t &rhs) const {return value > rhs.value;};
	inline bool operator>=(const timestamp_t &rhs) const {return value >= rhs.value;};

	// arithmetic operators
	inline timestamp_t operator+(const double &value) const {return timestamp_t(this->value + int64_t(value));};
	inline int64_t operator-(const timestamp_t &other) const {return this->value - other.value;};

	// in-place operators
	inline timestamp_t &operator+=(const int64_t &value) {this->value += value; return *this;};
	inline timestamp_t &operator-=(const int64_t &value) {this->value -= value; return *this;};

	// special values
	static inline timestamp_t infinity() {return timestamp_t(std::numeric_limits<int64_t>::max()); } // NOLINT
	static inline timestamp_t ninfinity() {return timestamp_t(-std::numeric_limits<int64_t>::max()); } // NOLINT
	static inline timestamp_t epoch() {return timestamp_t(0); } // NOLINT
};

struct timestamp_tz_t : public timestamp_t {};
struct timestamp_ns_t : public timestamp_t {};
struct timestamp_ms_t : public timestamp_t {};
struct timestamp_sec_t : public timestamp_t {};

struct interval_t {
	int32_t months;
	int32_t days;
	int64_t micros;

	inline bool operator==(const interval_t &rhs) const {
		return this->days == rhs.days && this->months == rhs.months && this->micros == rhs.micros;
	}
};

struct hugeint_t {
public:
	uint64_t lower;
	int64_t upper;

public:
	DUCKDB_API hugeint_t() = default;
	DUCKDB_API hugeint_t(int64_t value); // NOLINT: Allow implicit conversion from `int64_t`
	DUCKDB_API hugeint_t(const hugeint_t &rhs) = default;
	DUCKDB_API hugeint_t(hugeint_t &&rhs) = default;
	DUCKDB_API hugeint_t &operator=(const hugeint_t &rhs) = default;
	DUCKDB_API hugeint_t &operator=(hugeint_t &&rhs) = default;

	DUCKDB_API string ToString() const;

	// comparison operators
	DUCKDB_API bool operator==(const hugeint_t &rhs) const;
	DUCKDB_API bool operator!=(const hugeint_t &rhs) const;
	DUCKDB_API bool operator<=(const hugeint_t &rhs) const;
	DUCKDB_API bool operator<(const hugeint_t &rhs) const;
	DUCKDB_API bool operator>(const hugeint_t &rhs) const;
	DUCKDB_API bool operator>=(const hugeint_t &rhs) const;

	// arithmetic operators
	DUCKDB_API hugeint_t operator+(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator-(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator*(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator/(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator%(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator-() const;

	// bitwise operators
	DUCKDB_API hugeint_t operator>>(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator<<(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator&(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator|(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator^(const hugeint_t &rhs) const;
	DUCKDB_API hugeint_t operator~() const;

	// in-place operators
	DUCKDB_API hugeint_t &operator+=(const hugeint_t &rhs);
	DUCKDB_API hugeint_t &operator-=(const hugeint_t &rhs);
	DUCKDB_API hugeint_t &operator*=(const hugeint_t &rhs);
	DUCKDB_API hugeint_t &operator/=(const hugeint_t &rhs);
	DUCKDB_API hugeint_t &operator%=(const hugeint_t &rhs);
	DUCKDB_API hugeint_t &operator>>=(const hugeint_t &rhs);
	DUCKDB_API hugeint_t &operator<<=(const hugeint_t &rhs);
	DUCKDB_API hugeint_t &operator&=(const hugeint_t &rhs);
	DUCKDB_API hugeint_t &operator|=(const hugeint_t &rhs);
	DUCKDB_API hugeint_t &operator^=(const hugeint_t &rhs);
};

struct string_t;

template <class T>
using child_list_t = std::vector<std::pair<std::string, T>>;
//! FIXME: this should be a single_thread_ptr
template <class T>
using buffer_ptr = shared_ptr<T>;

template <class T, typename... Args>
buffer_ptr<T> make_buffer(Args &&...args) {
	return make_shared<T>(std::forward<Args>(args)...);
}

struct list_entry_t {
	list_entry_t() = default;
	list_entry_t(uint64_t offset, uint64_t length) : offset(offset), length(length) {
	}

	uint64_t offset;
	uint64_t length;
};

//===--------------------------------------------------------------------===//
// Internal Types
//===--------------------------------------------------------------------===//

// taken from arrow's type.h
enum class PhysicalType : uint8_t {
	///// A NULL type having no physical storage
	//NA = 0,

	/// Boolean as 8 bit "bool" value
	BOOL = 1,

	/// Unsigned 8-bit little-endian integer
	UINT8 = 2,

	/// Signed 8-bit little-endian integer
	INT8 = 3,

	/// Unsigned 16-bit little-endian integer
	UINT16 = 4,

	/// Signed 16-bit little-endian integer
	INT16 = 5,

	/// Unsigned 32-bit little-endian integer
	UINT32 = 6,

	/// Signed 32-bit little-endian integer
	INT32 = 7,

	/// Unsigned 64-bit little-endian integer
	UINT64 = 8,

	/// Signed 64-bit little-endian integer
	INT64 = 9,

	///// 2-byte floating point value
	//HALF_FLOAT = 10,

	/// 4-byte floating point value
	FLOAT = 11,

	/// 8-byte floating point value
	DOUBLE = 12,

	///// UTF8 variable-length string as List<Char>
	//STRING = 13,

	///// Variable-length bytes (no guarantee of UTF8-ness)
	//BINARY = 14,

	///// Fixed-size binary. Each value occupies the same number of bytes
	//FIXED_SIZE_BINARY = 15,

	///// int32_t days since the UNIX epoch
	//DATE32 = 16,

	///// int64_t milliseconds since the UNIX epoch
	//DATE64 = 17,

	///// Exact timestamp encoded with int64 since UNIX epoch
	///// Default unit millisecond
	//TIMESTAMP = 18,

	///// Time as signed 32-bit integer, representing either seconds or
	///// milliseconds since midnight
	//TIME32 = 19,

	///// Time as signed 64-bit integer, representing either microseconds or
	///// nanoseconds since midnight
	//TIME64 = 20,

	/// YEAR_MONTH or DAY_TIME interval in SQL style
	INTERVAL = 21,

	/// Precision- and scale-based decimal type. Storage type depends on the
	/// parameters.
	// DECIMAL = 22,

	/// A list of some logical data type
	LIST = 23,

	/// Struct of logical types
	STRUCT = 24,

	///// Unions of logical types
	//UNION = 25,

	///// Dictionary-encoded type, also called "categorical" or "factor"
	///// in other programming languages. Holds the dictionary value
	///// type but not the dictionary itself, which is part of the
	///// ArrayData struct
	//DICTIONARY = 26,

	/// Map, a repeated struct logical type
	MAP = 27,

	///// Custom data type, implemented by user
	//EXTENSION = 28,

	///// Fixed size list of some logical type
	//FIXED_SIZE_LIST = 29,

	///// Measure of elapsed time in either seconds, milliseconds, microseconds
	///// or nanoseconds.
	//DURATION = 30,

	///// Like STRING, but with 64-bit offsets
	//LARGE_STRING = 31,

	///// Like BINARY, but with 64-bit offsets
	//LARGE_BINARY = 32,

	///// Like LIST, but with 64-bit offsets
	//LARGE_LIST = 33,

	/// DuckDB Extensions
	VARCHAR = 200, // our own string representation, different from STRING and LARGE_STRING above
	INT128 = 204, // 128-bit integers
	UNKNOWN = 205, // Unknown physical type of user defined types
	/// Boolean as 1 bit, LSB bit-packed ordering
	BIT = 206,

	INVALID = 255
};

//===--------------------------------------------------------------------===//
// SQL Types
//===--------------------------------------------------------------------===//
enum class LogicalTypeId : uint8_t {
	INVALID = 0,
	SQLNULL = 1, /* NULL type, used for constant NULL */
	UNKNOWN = 2, /* unknown type, used for parameter expressions */
	ANY = 3,     /* ANY type, used for functions that accept any type as parameter */
	USER = 4, /* A User Defined Type (e.g., ENUMs before the binder) */
	BOOLEAN = 10,
	TINYINT = 11,
	SMALLINT = 12,
	INTEGER = 13,
	BIGINT = 14,
	DATE = 15,
	TIME = 16,
	TIMESTAMP_SEC = 17,
	TIMESTAMP_MS = 18,
	TIMESTAMP = 19, //! us
	TIMESTAMP_NS = 20,
	DECIMAL = 21,
	FLOAT = 22,
	DOUBLE = 23,
	CHAR = 24,
	VARCHAR = 25,
	BLOB = 26,
	INTERVAL = 27,
	UTINYINT = 28,
	USMALLINT = 29,
	UINTEGER = 30,
	UBIGINT = 31,
	TIMESTAMP_TZ = 32,
	TIME_TZ = 34,
	JSON = 35,

	HUGEINT = 50,
	POINTER = 51,
	// HASH = 52, // deprecated, uses UBIGINT instead
	VALIDITY = 53,
	UUID = 54,

	STRUCT = 100,
	LIST = 101,
	MAP = 102,
	TABLE = 103,
	ENUM = 104,
	AGGREGATE_STATE = 105,
	LAMBDA = 106
};

struct ExtraTypeInfo;


struct aggregate_state_t;

struct LogicalType {
	DUCKDB_API LogicalType();
	DUCKDB_API LogicalType(LogicalTypeId id); // NOLINT: Allow implicit conversion from `LogicalTypeId`
	DUCKDB_API LogicalType(LogicalTypeId id, shared_ptr<ExtraTypeInfo> type_info);
	DUCKDB_API LogicalType(const LogicalType &other);
	DUCKDB_API LogicalType(LogicalType &&other) noexcept;

	DUCKDB_API ~LogicalType();

	inline LogicalTypeId id() const {
		return id_;
	}
	inline PhysicalType InternalType() const {
		return physical_type_;
	}
	inline const ExtraTypeInfo *AuxInfo() const {
		return type_info_.get();
	}
	inline void CopyAuxInfo(const LogicalType& other) {
		type_info_ = other.type_info_;
	}
	bool EqualTypeInfo(const LogicalType& rhs) const;

	// copy assignment
	inline LogicalType& operator=(const LogicalType &other) {
		id_ = other.id_;
		physical_type_ = other.physical_type_;
		type_info_ = other.type_info_;
		return *this;
	}
	// move assignment
	inline LogicalType& operator=(LogicalType&& other) noexcept {
		id_ = other.id_;
		physical_type_ = other.physical_type_;
		type_info_ = move(other.type_info_);
		return *this;
	}

	DUCKDB_API bool operator==(const LogicalType &rhs) const;
	inline bool operator!=(const LogicalType &rhs) const {
		return !(*this == rhs);
	}

	//! Serializes a LogicalType to a stand-alone binary blob
	DUCKDB_API void Serialize(Serializer &serializer) const;
	//! Deserializes a blob back into an LogicalType
	DUCKDB_API static LogicalType Deserialize(Deserializer &source);

	DUCKDB_API static bool TypeIsTimestamp(LogicalTypeId id) {
		return (id == LogicalTypeId::TIMESTAMP ||
				id == LogicalTypeId::TIMESTAMP_MS ||
				id == LogicalTypeId::TIMESTAMP_NS ||
				id == LogicalTypeId::TIMESTAMP_SEC ||
				id == LogicalTypeId::TIMESTAMP_TZ);
	}
	DUCKDB_API static bool TypeIsTimestamp(const LogicalType& type) {
		return TypeIsTimestamp(type.id());
	}
	DUCKDB_API string ToString() const;
	DUCKDB_API bool IsIntegral() const;
	DUCKDB_API bool IsNumeric() const;
	DUCKDB_API hash_t Hash() const;
	DUCKDB_API void SetAlias(string alias);
	DUCKDB_API bool HasAlias() const;
	DUCKDB_API string GetAlias() const;

	DUCKDB_API static LogicalType MaxLogicalType(const LogicalType &left, const LogicalType &right);
	DUCKDB_API static void SetCatalog(LogicalType &type, TypeCatalogEntry* catalog_entry);
	DUCKDB_API static TypeCatalogEntry* GetCatalog(const LogicalType &type);

	//! Gets the decimal properties of a numeric type. Fails if the type is not numeric.
	DUCKDB_API bool GetDecimalProperties(uint8_t &width, uint8_t &scale) const;

	DUCKDB_API void Verify() const;

	DUCKDB_API bool IsValid() const;

private:
	LogicalTypeId id_;
	PhysicalType physical_type_;
	shared_ptr<ExtraTypeInfo> type_info_;

private:
	PhysicalType GetInternalType();

public:
	static constexpr const LogicalTypeId SQLNULL = LogicalTypeId::SQLNULL;
	static constexpr const LogicalTypeId UNKNOWN = LogicalTypeId::UNKNOWN;
	static constexpr const LogicalTypeId BOOLEAN = LogicalTypeId::BOOLEAN;
	static constexpr const LogicalTypeId TINYINT = LogicalTypeId::TINYINT;
	static constexpr const LogicalTypeId UTINYINT = LogicalTypeId::UTINYINT;
	static constexpr const LogicalTypeId SMALLINT = LogicalTypeId::SMALLINT;
	static constexpr const LogicalTypeId USMALLINT = LogicalTypeId::USMALLINT;
	static constexpr const LogicalTypeId INTEGER = LogicalTypeId::INTEGER;
	static constexpr const LogicalTypeId UINTEGER = LogicalTypeId::UINTEGER;
	static constexpr const LogicalTypeId BIGINT = LogicalTypeId::BIGINT;
	static constexpr const LogicalTypeId UBIGINT = LogicalTypeId::UBIGINT;
	static constexpr const LogicalTypeId FLOAT = LogicalTypeId::FLOAT;
	static constexpr const LogicalTypeId DOUBLE = LogicalTypeId::DOUBLE;
	static constexpr const LogicalTypeId DATE = LogicalTypeId::DATE;
	static constexpr const LogicalTypeId TIMESTAMP = LogicalTypeId::TIMESTAMP;
	static constexpr const LogicalTypeId TIMESTAMP_S = LogicalTypeId::TIMESTAMP_SEC;
	static constexpr const LogicalTypeId TIMESTAMP_MS = LogicalTypeId::TIMESTAMP_MS;
	static constexpr const LogicalTypeId TIMESTAMP_NS = LogicalTypeId::TIMESTAMP_NS;
	static constexpr const LogicalTypeId TIME = LogicalTypeId::TIME;
	static constexpr const LogicalTypeId TIMESTAMP_TZ = LogicalTypeId::TIMESTAMP_TZ;
	static constexpr const LogicalTypeId TIME_TZ = LogicalTypeId::TIME_TZ;
	static constexpr const LogicalTypeId VARCHAR = LogicalTypeId::VARCHAR;
	static constexpr const LogicalTypeId ANY = LogicalTypeId::ANY;
	static constexpr const LogicalTypeId BLOB = LogicalTypeId::BLOB;
	static constexpr const LogicalTypeId INTERVAL = LogicalTypeId::INTERVAL;
	static constexpr const LogicalTypeId HUGEINT = LogicalTypeId::HUGEINT;
	static constexpr const LogicalTypeId UUID = LogicalTypeId::UUID;
	static constexpr const LogicalTypeId HASH = LogicalTypeId::UBIGINT;
	static constexpr const LogicalTypeId POINTER = LogicalTypeId::POINTER;
	static constexpr const LogicalTypeId TABLE = LogicalTypeId::TABLE;
	static constexpr const LogicalTypeId LAMBDA = LogicalTypeId::LAMBDA;
	static constexpr const LogicalTypeId INVALID = LogicalTypeId::INVALID;
	static constexpr const LogicalTypeId JSON = LogicalTypeId::JSON;
	static constexpr const LogicalTypeId ROW_TYPE = LogicalTypeId::BIGINT;

	// explicitly allowing these functions to be capitalized to be in-line with the remaining functions
	DUCKDB_API static LogicalType DECIMAL(int width, int scale);                 // NOLINT
	DUCKDB_API static LogicalType VARCHAR_COLLATION(string collation);           // NOLINT
	DUCKDB_API static LogicalType LIST( LogicalType child);                       // NOLINT
	DUCKDB_API static LogicalType STRUCT( child_list_t<LogicalType> children);    // NOLINT
	DUCKDB_API static LogicalType AGGREGATE_STATE(aggregate_state_t state_type);    // NOLINT
	DUCKDB_API static LogicalType MAP( child_list_t<LogicalType> children);       // NOLINT
	DUCKDB_API static LogicalType MAP(LogicalType key, LogicalType value); // NOLINT
	DUCKDB_API static LogicalType ENUM(const string &enum_name, Vector &ordered_data, idx_t size); // NOLINT
	DUCKDB_API static LogicalType DEDUP_POINTER_ENUM(); // NOLINT
	DUCKDB_API static LogicalType USER(const string &user_type_name); // NOLINT
	//! A list of all NUMERIC types (integral and floating point types)
	DUCKDB_API static const vector<LogicalType> Numeric();
	//! A list of all INTEGRAL types
	DUCKDB_API static const vector<LogicalType> Integral();
	//! A list of ALL SQL types
	DUCKDB_API static const vector<LogicalType> AllTypes();
};

struct DecimalType {
	DUCKDB_API static uint8_t GetWidth(const LogicalType &type);
	DUCKDB_API static uint8_t GetScale(const LogicalType &type);
	DUCKDB_API static uint8_t MaxWidth();
};

struct StringType {
	DUCKDB_API static string GetCollation(const LogicalType &type);
};

struct ListType {
	DUCKDB_API static const LogicalType &GetChildType(const LogicalType &type);
};

struct UserType{
	DUCKDB_API static const string &GetTypeName(const LogicalType &type);
};

struct EnumType{
	DUCKDB_API static const string &GetTypeName(const LogicalType &type);
	DUCKDB_API static int64_t GetPos(const LogicalType &type, const string& key);
	DUCKDB_API static Vector &GetValuesInsertOrder(const LogicalType &type);
	DUCKDB_API static idx_t GetSize(const LogicalType &type);
	DUCKDB_API static const string GetValue(const Value &val);
	DUCKDB_API static void SetCatalog(LogicalType &type, TypeCatalogEntry* catalog_entry);
	DUCKDB_API static TypeCatalogEntry* GetCatalog(const LogicalType &type);
	DUCKDB_API static PhysicalType GetPhysicalType(const LogicalType &type);
};

struct StructType {
	DUCKDB_API static const child_list_t<LogicalType> &GetChildTypes(const LogicalType &type);
	DUCKDB_API static const LogicalType &GetChildType(const LogicalType &type, idx_t index);
	DUCKDB_API static const string &GetChildName(const LogicalType &type, idx_t index);
	DUCKDB_API static idx_t GetChildCount(const LogicalType &type);
};

struct MapType {
	DUCKDB_API static const LogicalType &KeyType(const LogicalType &type);
	DUCKDB_API static const LogicalType &ValueType(const LogicalType &type);
};

struct AggregateStateType {
	DUCKDB_API static const string GetTypeName(const LogicalType &type);
	DUCKDB_API static const aggregate_state_t &GetStateType(const LogicalType &type);
};


DUCKDB_API string LogicalTypeIdToString(LogicalTypeId type);

DUCKDB_API LogicalTypeId TransformStringToLogicalTypeId(const string &str);

DUCKDB_API LogicalType TransformStringToLogicalType(const string &str);

//! Returns the PhysicalType for the given type
template <class T>
PhysicalType GetTypeId() {
	if (std::is_same<T, bool>()) {
		return PhysicalType::BOOL;
	} else if (std::is_same<T, int8_t>()) {
		return PhysicalType::INT8;
	} else if (std::is_same<T, int16_t>()) {
		return PhysicalType::INT16;
	} else if (std::is_same<T, int32_t>()) {
		return PhysicalType::INT32;
	} else if (std::is_same<T, int64_t>()) {
		return PhysicalType::INT64;
	} else if (std::is_same<T, uint8_t>()) {
		return PhysicalType::UINT8;
	} else if (std::is_same<T, uint16_t>()) {
		return PhysicalType::UINT16;
	} else if (std::is_same<T, uint32_t>()) {
		return PhysicalType::UINT32;
	} else if (std::is_same<T, uint64_t>()) {
		return PhysicalType::UINT64;
	} else if (std::is_same<T, hugeint_t>()) {
		return PhysicalType::INT128;
	} else if (std::is_same<T, date_t>()) {
		return PhysicalType::INT32;
	} else if (std::is_same<T, dtime_t>()) {
		return PhysicalType::INT64;
	} else if (std::is_same<T, timestamp_t>()) {
		return PhysicalType::INT64;
	} else if (std::is_same<T, float>()) {
		return PhysicalType::FLOAT;
	} else if (std::is_same<T, double>()) {
		return PhysicalType::DOUBLE;
	} else if (std::is_same<T, const char *>() || std::is_same<T, char *>() || std::is_same<T, string_t>()) {
		return PhysicalType::VARCHAR;
	} else if (std::is_same<T, interval_t>()) {
		return PhysicalType::INTERVAL;
	} else {
		return PhysicalType::INVALID;
	}
}

template<class T>
bool TypeIsNumber() {
	return std::is_integral<T>() || std::is_floating_point<T>() || std::is_same<T, hugeint_t>();
}

template <class T>
bool IsValidType() {
	return GetTypeId<T>() != PhysicalType::INVALID;
}

//! The PhysicalType used by the row identifiers column
extern const PhysicalType ROW_TYPE;

DUCKDB_API string TypeIdToString(PhysicalType type);
idx_t GetTypeIdSize(PhysicalType type);
bool TypeIsConstantSize(PhysicalType type);
bool TypeIsIntegral(PhysicalType type);
bool TypeIsNumeric(PhysicalType type);
bool TypeIsInteger(PhysicalType type);

template <class T>
bool IsIntegerType() {
	return TypeIsIntegral(GetTypeId<T>());
}

bool ApproxEqual(float l, float r);
bool ApproxEqual(double l, double r);

struct aggregate_state_t {
	aggregate_state_t(string function_name_p, LogicalType return_type_p, vector<LogicalType> bound_argument_types_p) : function_name(move(function_name_p)), return_type(move(return_type_p)), bound_argument_types(move(bound_argument_types_p)) {
	}

	string function_name;
	LogicalType return_type;
	vector<LogicalType> bound_argument_types;
};

} // namespace duckdb

namespace std {

	//! Date
	template <>
	struct hash<duckdb::date_t>
	{
		std::size_t operator()(const duckdb::date_t& k) const
		{
			using std::hash;
			return hash<int32_t>()((int32_t)k);
		}
	};

	//! Time
	template <>
	struct hash<duckdb::dtime_t>
	{
		std::size_t operator()(const duckdb::dtime_t& k) const
		{
			using std::hash;
			return hash<int64_t>()((int64_t)k);
		}
	};
	template <>
	struct hash<duckdb::dtime_tz_t>
	{
		std::size_t operator()(const duckdb::dtime_tz_t& k) const
		{
			using std::hash;
			return hash<int64_t>()((int64_t)k);
		}
	};

	//! Timestamp
	template <>
	struct hash<duckdb::timestamp_t>
	{
		std::size_t operator()(const duckdb::timestamp_t& k) const
		{
			using std::hash;
			return hash<int64_t>()((int64_t)k);
		}
	};
	template <>
	struct hash<duckdb::timestamp_ms_t>
	{
		std::size_t operator()(const duckdb::timestamp_ms_t& k) const
		{
			using std::hash;
			return hash<int64_t>()((int64_t)k);
		}
	};
	template <>
	struct hash<duckdb::timestamp_ns_t>
	{
		std::size_t operator()(const duckdb::timestamp_ns_t& k) const
		{
			using std::hash;
			return hash<int64_t>()((int64_t)k);
		}
	};
	template <>
	struct hash<duckdb::timestamp_sec_t>
	{
		std::size_t operator()(const duckdb::timestamp_sec_t& k) const
		{
			using std::hash;
			return hash<int64_t>()((int64_t)k);
		}
	};
	template <>
	struct hash<duckdb::timestamp_tz_t>
	{
		std::size_t operator()(const duckdb::timestamp_tz_t& k) const
		{
			using std::hash;
			return hash<int64_t>()((int64_t)k);
		}
	};
}


namespace duckdb {

enum class ExceptionFormatValueType : uint8_t {
	FORMAT_VALUE_TYPE_DOUBLE,
	FORMAT_VALUE_TYPE_INTEGER,
	FORMAT_VALUE_TYPE_STRING
};

struct ExceptionFormatValue {
	DUCKDB_API ExceptionFormatValue(double dbl_val);   // NOLINT
	DUCKDB_API ExceptionFormatValue(int64_t int_val);  // NOLINT
	DUCKDB_API ExceptionFormatValue(string str_val);   // NOLINT
	DUCKDB_API ExceptionFormatValue(hugeint_t hg_val); // NOLINT

	ExceptionFormatValueType type;

	double dbl_val = 0;
	int64_t int_val = 0;
	string str_val;

public:
	template <class T>
	static ExceptionFormatValue CreateFormatValue(T value) {
		return int64_t(value);
	}
	static string Format(const string &msg, vector<ExceptionFormatValue> &values);
};

template <>
DUCKDB_API ExceptionFormatValue ExceptionFormatValue::CreateFormatValue(PhysicalType value);
template <>
DUCKDB_API ExceptionFormatValue ExceptionFormatValue::CreateFormatValue(LogicalType value);
template <>
DUCKDB_API ExceptionFormatValue ExceptionFormatValue::CreateFormatValue(float value);
template <>
DUCKDB_API ExceptionFormatValue ExceptionFormatValue::CreateFormatValue(double value);
template <>
DUCKDB_API ExceptionFormatValue ExceptionFormatValue::CreateFormatValue(string value);
template <>
DUCKDB_API ExceptionFormatValue ExceptionFormatValue::CreateFormatValue(const char *value);
template <>
DUCKDB_API ExceptionFormatValue ExceptionFormatValue::CreateFormatValue(char *value);
template <>
DUCKDB_API ExceptionFormatValue ExceptionFormatValue::CreateFormatValue(hugeint_t value);

} // namespace duckdb



#include <stdexcept>

namespace duckdb {
enum class PhysicalType : uint8_t;
struct LogicalType;
struct hugeint_t;

inline void assert_restrict_function(void *left_start, void *left_end, void *right_start, void *right_end,
                                     const char *fname, int linenr) {
	// assert that the two pointers do not overlap
#ifdef DEBUG
	if (!(left_end <= right_start || right_end <= left_start)) {
		printf("ASSERT RESTRICT FAILED: %s:%d\n", fname, linenr);
		D_ASSERT(0);
	}
#endif
}

#define ASSERT_RESTRICT(left_start, left_end, right_start, right_end)                                                  \
	assert_restrict_function(left_start, left_end, right_start, right_end, __FILE__, __LINE__)

//===--------------------------------------------------------------------===//
// Exception Types
//===--------------------------------------------------------------------===//

enum class ExceptionType {
	INVALID = 0,          // invalid type
	OUT_OF_RANGE = 1,     // value out of range error
	CONVERSION = 2,       // conversion/casting error
	UNKNOWN_TYPE = 3,     // unknown type
	DECIMAL = 4,          // decimal related
	MISMATCH_TYPE = 5,    // type mismatch
	DIVIDE_BY_ZERO = 6,   // divide by 0
	OBJECT_SIZE = 7,      // object size exceeded
	INVALID_TYPE = 8,     // incompatible for operation
	SERIALIZATION = 9,    // serialization
	TRANSACTION = 10,     // transaction management
	NOT_IMPLEMENTED = 11, // method not implemented
	EXPRESSION = 12,      // expression parsing
	CATALOG = 13,         // catalog related
	PARSER = 14,          // parser related
	PLANNER = 15,         // planner related
	SCHEDULER = 16,       // scheduler related
	EXECUTOR = 17,        // executor related
	CONSTRAINT = 18,      // constraint related
	INDEX = 19,           // index related
	STAT = 20,            // stat related
	CONNECTION = 21,      // connection related
	SYNTAX = 22,          // syntax related
	SETTINGS = 23,        // settings related
	BINDER = 24,          // binder related
	NETWORK = 25,         // network related
	OPTIMIZER = 26,       // optimizer related
	NULL_POINTER = 27,    // nullptr exception
	IO = 28,              // IO exception
	INTERRUPT = 29,       // interrupt
	FATAL = 30,           // Fatal exceptions are non-recoverable, and render the entire DB in an unusable state
	INTERNAL = 31,        // Internal exceptions indicate something went wrong internally (i.e. bug in the code base)
	INVALID_INPUT = 32,   // Input or arguments error
	OUT_OF_MEMORY = 33,   // out of memory
	PERMISSION = 34,      // insufficient permissions
	PARAMETER_NOT_RESOLVED = 35, // parameter types could not be resolved
	PARAMETER_NOT_ALLOWED = 36   // parameter types not allowed
};

class Exception : public std::exception {
public:
	DUCKDB_API explicit Exception(const string &msg);
	DUCKDB_API Exception(ExceptionType exception_type, const string &message);

	ExceptionType type;

public:
	DUCKDB_API const char *what() const noexcept override;
	DUCKDB_API const string &RawMessage() const;

	DUCKDB_API static string ExceptionTypeToString(ExceptionType type);
	[[noreturn]] DUCKDB_API static void ThrowAsTypeWithMessage(ExceptionType type, const string &message);

	template <typename... Args>
	static string ConstructMessage(const string &msg, Args... params) {
		vector<ExceptionFormatValue> values;
		return ConstructMessageRecursive(msg, values, params...);
	}

	DUCKDB_API static string ConstructMessageRecursive(const string &msg, vector<ExceptionFormatValue> &values);

	template <class T, typename... Args>
	static string ConstructMessageRecursive(const string &msg, vector<ExceptionFormatValue> &values, T param,
	                                        Args... params) {
		values.push_back(ExceptionFormatValue::CreateFormatValue<T>(param));
		return ConstructMessageRecursive(msg, values, params...);
	}

	DUCKDB_API static bool UncaughtException();

private:
	string exception_message_;
	string raw_message_;
};

//===--------------------------------------------------------------------===//
// Exception derived classes
//===--------------------------------------------------------------------===//

//! Exceptions that are StandardExceptions do NOT invalidate the current transaction when thrown
class StandardException : public Exception {
public:
	DUCKDB_API StandardException(ExceptionType exception_type, const string &message);
};

class CatalogException : public StandardException {
public:
	DUCKDB_API explicit CatalogException(const string &msg);

	template <typename... Args>
	explicit CatalogException(const string &msg, Args... params) : CatalogException(ConstructMessage(msg, params...)) {
	}
};

class ConnectionException : public StandardException {
public:
	DUCKDB_API explicit ConnectionException(const string &msg);

	template <typename... Args>
	explicit ConnectionException(const string &msg, Args... params)
	    : ConnectionException(ConstructMessage(msg, params...)) {
	}
};

class ParserException : public StandardException {
public:
	DUCKDB_API explicit ParserException(const string &msg);

	template <typename... Args>
	explicit ParserException(const string &msg, Args... params) : ParserException(ConstructMessage(msg, params...)) {
	}
};

class PermissionException : public StandardException {
public:
	DUCKDB_API explicit PermissionException(const string &msg);

	template <typename... Args>
	explicit PermissionException(const string &msg, Args... params)
	    : PermissionException(ConstructMessage(msg, params...)) {
	}
};

class BinderException : public StandardException {
public:
	DUCKDB_API explicit BinderException(const string &msg);

	template <typename... Args>
	explicit BinderException(const string &msg, Args... params) : BinderException(ConstructMessage(msg, params...)) {
	}
};

class ConversionException : public Exception {
public:
	DUCKDB_API explicit ConversionException(const string &msg);

	template <typename... Args>
	explicit ConversionException(const string &msg, Args... params)
	    : ConversionException(ConstructMessage(msg, params...)) {
	}
};

class TransactionException : public Exception {
public:
	DUCKDB_API explicit TransactionException(const string &msg);

	template <typename... Args>
	explicit TransactionException(const string &msg, Args... params)
	    : TransactionException(ConstructMessage(msg, params...)) {
	}
};

class NotImplementedException : public Exception {
public:
	DUCKDB_API explicit NotImplementedException(const string &msg);

	template <typename... Args>
	explicit NotImplementedException(const string &msg, Args... params)
	    : NotImplementedException(ConstructMessage(msg, params...)) {
	}
};

class OutOfRangeException : public Exception {
public:
	DUCKDB_API explicit OutOfRangeException(const string &msg);

	template <typename... Args>
	explicit OutOfRangeException(const string &msg, Args... params)
	    : OutOfRangeException(ConstructMessage(msg, params...)) {
	}
};

class OutOfMemoryException : public Exception {
public:
	DUCKDB_API explicit OutOfMemoryException(const string &msg);

	template <typename... Args>
	explicit OutOfMemoryException(const string &msg, Args... params)
	    : OutOfMemoryException(ConstructMessage(msg, params...)) {
	}
};

class SyntaxException : public Exception {
public:
	DUCKDB_API explicit SyntaxException(const string &msg);

	template <typename... Args>
	explicit SyntaxException(const string &msg, Args... params) : SyntaxException(ConstructMessage(msg, params...)) {
	}
};

class ConstraintException : public Exception {
public:
	DUCKDB_API explicit ConstraintException(const string &msg);

	template <typename... Args>
	explicit ConstraintException(const string &msg, Args... params)
	    : ConstraintException(ConstructMessage(msg, params...)) {
	}
};

class IOException : public Exception {
public:
	DUCKDB_API explicit IOException(const string &msg);

	template <typename... Args>
	explicit IOException(const string &msg, Args... params) : IOException(ConstructMessage(msg, params...)) {
	}
};

class SerializationException : public Exception {
public:
	DUCKDB_API explicit SerializationException(const string &msg);

	template <typename... Args>
	explicit SerializationException(const string &msg, Args... params)
	    : SerializationException(ConstructMessage(msg, params...)) {
	}
};

class SequenceException : public Exception {
public:
	DUCKDB_API explicit SequenceException(const string &msg);

	template <typename... Args>
	explicit SequenceException(const string &msg, Args... params)
	    : SequenceException(ConstructMessage(msg, params...)) {
	}
};

class InterruptException : public Exception {
public:
	DUCKDB_API InterruptException();
};

class FatalException : public Exception {
public:
	DUCKDB_API explicit FatalException(const string &msg) : FatalException(ExceptionType::FATAL, msg) {
	}
	template <typename... Args>
	explicit FatalException(const string &msg, Args... params) : FatalException(ConstructMessage(msg, params...)) {
	}

protected:
	DUCKDB_API explicit FatalException(ExceptionType type, const string &msg);
	template <typename... Args>
	explicit FatalException(ExceptionType type, const string &msg, Args... params)
	    : FatalException(type, ConstructMessage(msg, params...)) {
	}
};

class InternalException : public FatalException {
public:
	DUCKDB_API explicit InternalException(const string &msg);

	template <typename... Args>
	explicit InternalException(const string &msg, Args... params)
	    : InternalException(ConstructMessage(msg, params...)) {
	}
};

class InvalidInputException : public Exception {
public:
	DUCKDB_API explicit InvalidInputException(const string &msg);

	template <typename... Args>
	explicit InvalidInputException(const string &msg, Args... params)
	    : InvalidInputException(ConstructMessage(msg, params...)) {
	}
};

class CastException : public Exception {
public:
	DUCKDB_API CastException(const PhysicalType origType, const PhysicalType newType);
	DUCKDB_API CastException(const LogicalType &origType, const LogicalType &newType);
	DUCKDB_API
	CastException(const string &msg); //! Needed to be able to recreate the exception after it's been serialized
};

class InvalidTypeException : public Exception {
public:
	DUCKDB_API InvalidTypeException(PhysicalType type, const string &msg);
	DUCKDB_API InvalidTypeException(const LogicalType &type, const string &msg);
	DUCKDB_API
	InvalidTypeException(const string &msg); //! Needed to be able to recreate the exception after it's been serialized
};

class TypeMismatchException : public Exception {
public:
	DUCKDB_API TypeMismatchException(const PhysicalType type_1, const PhysicalType type_2, const string &msg);
	DUCKDB_API TypeMismatchException(const LogicalType &type_1, const LogicalType &type_2, const string &msg);
	DUCKDB_API
	TypeMismatchException(const string &msg); //! Needed to be able to recreate the exception after it's been serialized
};

class ValueOutOfRangeException : public Exception {
public:
	DUCKDB_API ValueOutOfRangeException(const int64_t value, const PhysicalType origType, const PhysicalType newType);
	DUCKDB_API ValueOutOfRangeException(const hugeint_t value, const PhysicalType origType, const PhysicalType newType);
	DUCKDB_API ValueOutOfRangeException(const double value, const PhysicalType origType, const PhysicalType newType);
	DUCKDB_API ValueOutOfRangeException(const PhysicalType varType, const idx_t length);
	DUCKDB_API ValueOutOfRangeException(
	    const string &msg); //! Needed to be able to recreate the exception after it's been serialized
};

class ParameterNotAllowedException : public StandardException {
public:
	DUCKDB_API explicit ParameterNotAllowedException(const string &msg);

	template <typename... Args>
	explicit ParameterNotAllowedException(const string &msg, Args... params)
	    : ParameterNotAllowedException(ConstructMessage(msg, params...)) {
	}
};

//! Special exception that should be thrown in the binder if parameter types could not be resolved
//! This will cause prepared statements to be forcibly rebound with the actual parameter values
//! This exception is fatal if thrown outside of the binder (i.e. it should never be thrown outside of the binder)
class ParameterNotResolvedException : public Exception {
public:
	DUCKDB_API explicit ParameterNotResolvedException();
};

} // namespace duckdb


#include <type_traits>

namespace duckdb {

//! The Serialize class is a base class that can be used to serializing objects into a binary buffer
class Serializer {
private:
	uint64_t version = 0L;

public:
	virtual ~Serializer() {
	}

	//! Sets the version of the serialization that writers are expected to use
	//! The version is mostly the most recent one, unless modifying old data or streaming to
	//! an older version
	void SetVersion(uint64_t v) {
		D_ASSERT(this->version == 0); // version can only be set once
		this->version = v;
	}

	//! Returns the version of serialization that writers are expected to use
	uint64_t GetVersion() {
		return version;
	}

	virtual void WriteData(const_data_ptr_t buffer, idx_t write_size) = 0;

	template <class T>
	void Write(T element) {
		static_assert(std::is_trivially_destructible<T>(), "Write element must be trivially destructible");

		WriteData((const_data_ptr_t)&element, sizeof(T));
	}

	//! Write data from a string buffer directly (without length prefix)
	void WriteBufferData(const string &str) {
		WriteData((const_data_ptr_t)str.c_str(), str.size());
	}
	//! Write a string with a length prefix
	void WriteString(const string &val) {
		WriteStringLen((const_data_ptr_t)val.c_str(), val.size());
	}
	void WriteStringLen(const_data_ptr_t val, idx_t len) {
		Write<uint32_t>((uint32_t)len);
		if (len > 0) {
			WriteData(val, len);
		}
	}

	template <class T>
	void WriteList(const vector<unique_ptr<T>> &list) {
		Write<uint32_t>((uint32_t)list.size());
		for (auto &child : list) {
			child->Serialize(*this);
		}
	}

	void WriteStringVector(const vector<string> &list) {
		Write<uint32_t>((uint32_t)list.size());
		for (auto &child : list) {
			WriteString(child);
		}
	}

	template <class T>
	void WriteOptional(const unique_ptr<T> &element) {
		Write<bool>(element ? true : false);
		if (element) {
			element->Serialize(*this);
		}
	}
};

//! The Deserializer class assists in deserializing a binary blob back into an
//! object
class Deserializer {
private:
	uint64_t version = 0L;

public:
	virtual ~Deserializer() {
	}

	//! Sets the version of the serialization that readers are expected to use
	//! The version is mostly the most recent one, unless reading old data or streaming from
	//! an older version
	void SetVersion(uint64_t v) {
		D_ASSERT(this->version == 0); // version can only be set once
		this->version = v;
	}

	//! Returns the version of serialization that readers are expected to use
	uint64_t GetVersion() {
		return version;
	}

	//! Reads [read_size] bytes into the buffer
	virtual void ReadData(data_ptr_t buffer, idx_t read_size) = 0;

	template <class T>
	T Read() {
		T value;
		ReadData((data_ptr_t)&value, sizeof(T));
		return value;
	}

	template <class T, typename... ARGS>
	void ReadList(vector<unique_ptr<T>> &list, ARGS &&...args) {
		auto select_count = Read<uint32_t>();
		for (uint32_t i = 0; i < select_count; i++) {
			auto child = T::Deserialize(*this, std::forward<ARGS>(args)...);
			list.push_back(move(child));
		}
	}

	template <class T, class RETURN_TYPE = T, typename... ARGS>
	unique_ptr<RETURN_TYPE> ReadOptional(ARGS &&...args) {
		auto has_entry = Read<bool>();
		if (has_entry) {
			return T::Deserialize(*this, std::forward<ARGS>(args)...);
		}
		return nullptr;
	}

	void ReadStringVector(vector<string> &list);
};

template <>
DUCKDB_API string Deserializer::Read();

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/file_system.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/file_buffer.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {
class Allocator;
struct FileHandle;

enum class FileBufferType : uint8_t { BLOCK = 1, MANAGED_BUFFER = 2 };

//! The FileBuffer represents a buffer that can be read or written to a Direct IO FileHandle.
class FileBuffer {
public:
	//! Allocates a buffer of the specified size that is sector-aligned. bufsiz must be a multiple of
	//! FileSystemConstants::FILE_BUFFER_BLOCK_SIZE. The content in this buffer can be written to FileHandles that have
	//! been opened with DIRECT_IO on all operating systems, however, the entire buffer must be written to the file.
	//! Note that the returned size is 8 bytes less than the allocation size to account for the checksum.
	FileBuffer(Allocator &allocator, FileBufferType type, uint64_t bufsiz);
	FileBuffer(FileBuffer &source, FileBufferType type);

	virtual ~FileBuffer();

	Allocator &allocator;
	//! The type of the buffer
	FileBufferType type;
	//! The buffer that users can write to
	data_ptr_t buffer;
	//! The size of the portion that users can write to, this is equivalent to internal_size - BLOCK_HEADER_SIZE
	uint64_t size;

public:
	//! Read into the FileBuffer from the specified location.
	void Read(FileHandle &handle, uint64_t location);
	//! Read into the FileBuffer from the specified location. Automatically verifies the checksum, and throws an
	//! exception if the checksum does not match correctly.
	void ReadAndChecksum(FileHandle &handle, uint64_t location);
	//! Write the contents of the FileBuffer to the specified location.
	void Write(FileHandle &handle, uint64_t location);
	//! Write the contents of the FileBuffer to the specified location. Automatically adds a checksum of the contents of
	//! the filebuffer in front of the written data.
	void ChecksumAndWrite(FileHandle &handle, uint64_t location);

	void Clear();

	void Resize(uint64_t bufsiz);

	uint64_t AllocSize() {
		return internal_size;
	}

protected:
	//! The pointer to the internal buffer that will be read or written, including the buffer header
	data_ptr_t internal_buffer;
	//! The aligned size as passed to the constructor. This is the size that is read or written to disk.
	uint64_t internal_size;

private:
	//! The buffer that was actually malloc'd, i.e. the pointer that must be freed when the FileBuffer is destroyed
	data_ptr_t malloced_buffer;
	uint64_t malloced_size;

protected:
	uint64_t GetMallocedSize() {
		return malloced_size;
	}
	//! Sets malloced_size given the requested buffer size
	void SetMallocedSize(uint64_t &bufsiz);
	//! Constructs the Filebuffer object
	void Construct(uint64_t bufsiz);
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/unordered_map.hpp
//
//
//===----------------------------------------------------------------------===//



#include <unordered_map>

namespace duckdb {
using std::unordered_map;
}


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/file_compression_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class FileCompressionType : uint8_t { AUTO_DETECT = 0, UNCOMPRESSED = 1, GZIP = 2, ZSTD = 3 };

FileCompressionType FileCompressionTypeFromString(const string &input);

} // namespace duckdb


#include <functional>

#undef CreateDirectory
#undef MoveFile
#undef RemoveDirectory

namespace duckdb {
class ClientContext;
class DatabaseInstance;
class FileOpener;
class FileSystem;

enum class FileType {
	//! Regular file
	FILE_TYPE_REGULAR,
	//! Directory
	FILE_TYPE_DIR,
	//! FIFO named pipe
	FILE_TYPE_FIFO,
	//! Socket
	FILE_TYPE_SOCKET,
	//! Symbolic link
	FILE_TYPE_LINK,
	//! Block device
	FILE_TYPE_BLOCKDEV,
	//! Character device
	FILE_TYPE_CHARDEV,
	//! Unknown or invalid file handle
	FILE_TYPE_INVALID,
};

struct FileHandle {
public:
	DUCKDB_API FileHandle(FileSystem &file_system, string path);
	FileHandle(const FileHandle &) = delete;
	DUCKDB_API virtual ~FileHandle();

	DUCKDB_API int64_t Read(void *buffer, idx_t nr_bytes);
	DUCKDB_API int64_t Write(void *buffer, idx_t nr_bytes);
	DUCKDB_API void Read(void *buffer, idx_t nr_bytes, idx_t location);
	DUCKDB_API void Write(void *buffer, idx_t nr_bytes, idx_t location);
	DUCKDB_API void Seek(idx_t location);
	DUCKDB_API void Reset();
	DUCKDB_API idx_t SeekPosition();
	DUCKDB_API void Sync();
	DUCKDB_API void Truncate(int64_t new_size);
	DUCKDB_API string ReadLine();

	DUCKDB_API bool CanSeek();
	DUCKDB_API bool OnDiskFile();
	DUCKDB_API idx_t GetFileSize();
	DUCKDB_API FileType GetType();

	//! Closes the file handle.
	DUCKDB_API virtual void Close() = 0;

public:
	FileSystem &file_system;
	string path;
};

enum class FileLockType : uint8_t { NO_LOCK = 0, READ_LOCK = 1, WRITE_LOCK = 2 };

class FileFlags {
public:
	//! Open file with read access
	static constexpr uint8_t FILE_FLAGS_READ = 1 << 0;
	//! Open file with write access
	static constexpr uint8_t FILE_FLAGS_WRITE = 1 << 1;
	//! Use direct IO when reading/writing to the file
	static constexpr uint8_t FILE_FLAGS_DIRECT_IO = 1 << 2;
	//! Create file if not exists, can only be used together with WRITE
	static constexpr uint8_t FILE_FLAGS_FILE_CREATE = 1 << 3;
	//! Always create a new file. If a file exists, the file is truncated. Cannot be used together with CREATE.
	static constexpr uint8_t FILE_FLAGS_FILE_CREATE_NEW = 1 << 4;
	//! Open file in append mode
	static constexpr uint8_t FILE_FLAGS_APPEND = 1 << 5;
};

class FileSystem {
public:
	DUCKDB_API virtual ~FileSystem();

public:
	DUCKDB_API static constexpr FileLockType DEFAULT_LOCK = FileLockType::NO_LOCK;
	DUCKDB_API static constexpr FileCompressionType DEFAULT_COMPRESSION = FileCompressionType::UNCOMPRESSED;
	DUCKDB_API static FileSystem &GetFileSystem(ClientContext &context);
	DUCKDB_API static FileSystem &GetFileSystem(DatabaseInstance &db);
	DUCKDB_API static FileOpener *GetFileOpener(ClientContext &context);

	DUCKDB_API virtual unique_ptr<FileHandle> OpenFile(const string &path, uint8_t flags,
	                                                   FileLockType lock = DEFAULT_LOCK,
	                                                   FileCompressionType compression = DEFAULT_COMPRESSION,
	                                                   FileOpener *opener = nullptr);

	//! Read exactly nr_bytes from the specified location in the file. Fails if nr_bytes could not be read. This is
	//! equivalent to calling SetFilePointer(location) followed by calling Read().
	DUCKDB_API virtual void Read(FileHandle &handle, void *buffer, int64_t nr_bytes, idx_t location);
	//! Write exactly nr_bytes to the specified location in the file. Fails if nr_bytes could not be read. This is
	//! equivalent to calling SetFilePointer(location) followed by calling Write().
	DUCKDB_API virtual void Write(FileHandle &handle, void *buffer, int64_t nr_bytes, idx_t location);
	//! Read nr_bytes from the specified file into the buffer, moving the file pointer forward by nr_bytes. Returns the
	//! amount of bytes read.
	DUCKDB_API virtual int64_t Read(FileHandle &handle, void *buffer, int64_t nr_bytes);
	//! Write nr_bytes from the buffer into the file, moving the file pointer forward by nr_bytes.
	DUCKDB_API virtual int64_t Write(FileHandle &handle, void *buffer, int64_t nr_bytes);

	//! Returns the file size of a file handle, returns -1 on error
	DUCKDB_API virtual int64_t GetFileSize(FileHandle &handle);
	//! Returns the file last modified time of a file handle, returns timespec with zero on all attributes on error
	DUCKDB_API virtual time_t GetLastModifiedTime(FileHandle &handle);
	//! Returns the file last modified time of a file handle, returns timespec with zero on all attributes on error
	DUCKDB_API virtual FileType GetFileType(FileHandle &handle);
	//! Truncate a file to a maximum size of new_size, new_size should be smaller than or equal to the current size of
	//! the file
	DUCKDB_API virtual void Truncate(FileHandle &handle, int64_t new_size);

	//! Check if a directory exists
	DUCKDB_API virtual bool DirectoryExists(const string &directory);
	//! Create a directory if it does not exist
	DUCKDB_API virtual void CreateDirectory(const string &directory);
	//! Recursively remove a directory and all files in it
	DUCKDB_API virtual void RemoveDirectory(const string &directory);
	//! List files in a directory, invoking the callback method for each one with (filename, is_dir)
	DUCKDB_API virtual bool ListFiles(const string &directory,
	                                  const std::function<void(const string &, bool)> &callback);
	//! Move a file from source path to the target, StorageManager relies on this being an atomic action for ACID
	//! properties
	DUCKDB_API virtual void MoveFile(const string &source, const string &target);
	//! Check if a file exists
	DUCKDB_API virtual bool FileExists(const string &filename);
	//! Check if path is pipe
	DUCKDB_API virtual bool IsPipe(const string &filename);
	//! Remove a file from disk
	DUCKDB_API virtual void RemoveFile(const string &filename);
	//! Sync a file handle to disk
	DUCKDB_API virtual void FileSync(FileHandle &handle);
	//! Sets the working directory
	DUCKDB_API static void SetWorkingDirectory(const string &path);
	//! Gets the working directory
	DUCKDB_API static string GetWorkingDirectory();
	//! Gets the users home directory
	DUCKDB_API static string GetHomeDirectory(FileOpener *opener);
	//! Expands a given path, including e.g. expanding the home directory of the user
	DUCKDB_API static string ExpandPath(const string &path, FileOpener *opener);
	//! Returns the system-available memory in bytes. Returns DConstants::INVALID_INDEX if the system function fails.
	DUCKDB_API static idx_t GetAvailableMemory();
	//! Path separator for the current file system
	DUCKDB_API static string PathSeparator();
	//! Join two paths together
	DUCKDB_API static string JoinPath(const string &a, const string &path);
	//! Convert separators in a path to the local separators (e.g. convert "/" into \\ on windows)
	DUCKDB_API static string ConvertSeparators(const string &path);
	//! Extract the base name of a file (e.g. if the input is lib/example.dll the base name is example)
	DUCKDB_API static string ExtractBaseName(const string &path);

	//! Runs a glob on the file system, returning a list of matching files
	DUCKDB_API virtual vector<string> Glob(const string &path, FileOpener *opener = nullptr);
	DUCKDB_API virtual vector<string> Glob(const string &path, ClientContext &context);

	//! registers a sub-file system to handle certain file name prefixes, e.g. http:// etc.
	DUCKDB_API virtual void RegisterSubSystem(unique_ptr<FileSystem> sub_fs);
	DUCKDB_API virtual void RegisterSubSystem(FileCompressionType compression_type, unique_ptr<FileSystem> fs);

	//! Whether or not a sub-system can handle a specific file path
	DUCKDB_API virtual bool CanHandleFile(const string &fpath);

	//! Set the file pointer of a file handle to a specified location. Reads and writes will happen from this location
	DUCKDB_API virtual void Seek(FileHandle &handle, idx_t location);
	//! Reset a file to the beginning (equivalent to Seek(handle, 0) for simple files)
	DUCKDB_API virtual void Reset(FileHandle &handle);
	DUCKDB_API virtual idx_t SeekPosition(FileHandle &handle);

	//! Whether or not we can seek into the file
	DUCKDB_API virtual bool CanSeek();
	//! Whether or not the FS handles plain files on disk. This is relevant for certain optimizations, as random reads
	//! in a file on-disk are much cheaper than e.g. random reads in a file over the network
	DUCKDB_API virtual bool OnDiskFile(FileHandle &handle);

	DUCKDB_API virtual unique_ptr<FileHandle> OpenCompressedFile(unique_ptr<FileHandle> handle, bool write);

	//! Create a LocalFileSystem.
	DUCKDB_API static unique_ptr<FileSystem> CreateLocal();

protected:
	//! Return the name of the filesytem. Used for forming diagnosis messages.
	DUCKDB_API virtual std::string GetName() const = 0;
};

} // namespace duckdb


namespace duckdb {

#define FILE_BUFFER_SIZE 4096

class BufferedFileWriter : public Serializer {
public:
	static constexpr uint8_t DEFAULT_OPEN_FLAGS = FileFlags::FILE_FLAGS_WRITE | FileFlags::FILE_FLAGS_FILE_CREATE;

	//! Serializes to a buffer allocated by the serializer, will expand when
	//! writing past the initial threshold
	DUCKDB_API BufferedFileWriter(FileSystem &fs, const string &path, uint8_t open_flags = DEFAULT_OPEN_FLAGS,
	                              FileOpener *opener = nullptr);

	FileSystem &fs;
	string path;
	unique_ptr<data_t[]> data;
	idx_t offset;
	idx_t total_written;
	unique_ptr<FileHandle> handle;

public:
	DUCKDB_API void WriteData(const_data_ptr_t buffer, uint64_t write_size) override;
	//! Flush the buffer to disk and sync the file to ensure writing is completed
	DUCKDB_API void Sync();
	//! Flush the buffer to the file (without sync)
	DUCKDB_API void Flush();
	//! Returns the current size of the file
	DUCKDB_API int64_t GetFileSize();
	//! Truncate the size to a previous size (given that size <= GetFileSize())
	DUCKDB_API void Truncate(int64_t size);

	DUCKDB_API idx_t GetTotalWritten();
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/udf_function.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/scalar_function.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/vector_operations/binary_executor.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/vector.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/bitset.hpp
//
//
//===----------------------------------------------------------------------===//



#include <bitset>

namespace duckdb {
using std::bitset;
}


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/vector_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class VectorType : uint8_t {
	FLAT_VECTOR,       // Flat vectors represent a standard uncompressed vector
	CONSTANT_VECTOR,   // Constant vector represents a single constant
	DICTIONARY_VECTOR, // Dictionary vector represents a selection vector on top of another vector
	SEQUENCE_VECTOR    // Sequence vector represents a sequence with a start point and an increment
};

string VectorTypeToString(VectorType type);

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/selection_vector.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/vector_size.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//! The vector size used in the execution engine
#ifndef STANDARD_VECTOR_SIZE
#define STANDARD_VECTOR_SIZE 1024
#endif

#if ((STANDARD_VECTOR_SIZE & (STANDARD_VECTOR_SIZE - 1)) != 0)
#error Vector size should be a power of two
#endif

//! Zero selection vector: completely filled with the value 0 [READ ONLY]
extern const sel_t ZERO_VECTOR[STANDARD_VECTOR_SIZE];

} // namespace duckdb


namespace duckdb {
class VectorBuffer;

struct SelectionData {
	DUCKDB_API explicit SelectionData(idx_t count);

	unique_ptr<sel_t[]> owned_data;
};

struct SelectionVector {
	SelectionVector() : sel_vector(nullptr) {
	}
	explicit SelectionVector(sel_t *sel) {
		Initialize(sel);
	}
	explicit SelectionVector(idx_t count) {
		Initialize(count);
	}
	SelectionVector(idx_t start, idx_t count) {
		Initialize(STANDARD_VECTOR_SIZE);
		for (idx_t i = 0; i < count; i++) {
			set_index(i, start + i);
		}
	}
	SelectionVector(const SelectionVector &sel_vector) {
		Initialize(sel_vector);
	}
	explicit SelectionVector(buffer_ptr<SelectionData> data) {
		Initialize(move(data));
	}

public:
	void Initialize(sel_t *sel) {
		selection_data.reset();
		sel_vector = sel;
	}
	void Initialize(idx_t count = STANDARD_VECTOR_SIZE) {
		selection_data = make_buffer<SelectionData>(count);
		sel_vector = selection_data->owned_data.get();
	}
	void Initialize(buffer_ptr<SelectionData> data) {
		selection_data = move(data);
		sel_vector = selection_data->owned_data.get();
	}
	void Initialize(const SelectionVector &other) {
		selection_data = other.selection_data;
		sel_vector = other.sel_vector;
	}

	inline void set_index(idx_t idx, idx_t loc) {
		sel_vector[idx] = loc;
	}
	inline void swap(idx_t i, idx_t j) {
		sel_t tmp = sel_vector[i];
		sel_vector[i] = sel_vector[j];
		sel_vector[j] = tmp;
	}
	inline idx_t get_index(idx_t idx) const {
		return sel_vector ? sel_vector[idx] : idx;
	}
	sel_t *data() {
		return sel_vector;
	}
	const sel_t *data() const {
		return sel_vector;
	}
	buffer_ptr<SelectionData> sel_data() {
		return selection_data;
	}
	buffer_ptr<SelectionData> Slice(const SelectionVector &sel, idx_t count) const;

	string ToString(idx_t count = 0) const;
	void Print(idx_t count = 0) const;

	inline sel_t &operator[](idx_t index) const {
		return sel_vector[index];
	}

private:
	sel_t *sel_vector;
	buffer_ptr<SelectionData> selection_data;
};

class OptionalSelection {
public:
	explicit inline OptionalSelection(SelectionVector *sel_p) : sel(sel_p) {

		if (sel) {
			vec.Initialize(sel->data());
			sel = &vec;
		}
	}

	inline operator SelectionVector *() {
		return sel;
	}

	inline void Append(idx_t &count, const idx_t idx) {
		if (sel) {
			sel->set_index(count, idx);
		}
		++count;
	}

	inline void Advance(idx_t completed) {
		if (sel) {
			sel->Initialize(sel->data() + completed);
		}
	}

private:
	SelectionVector *sel;
	SelectionVector vec;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/validity_mask.hpp
//
//
//===----------------------------------------------------------------------===//






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/to_string.hpp
//
//
//===----------------------------------------------------------------------===//



namespace duckdb {
using std::to_string;
}


namespace duckdb {
struct ValidityMask;

template <typename V>
struct TemplatedValidityData {
	static constexpr const int BITS_PER_VALUE = sizeof(V) * 8;
	static constexpr const V MAX_ENTRY = ~V(0);

public:
	inline explicit TemplatedValidityData(idx_t count) {
		auto entry_count = EntryCount(count);
		owned_data = unique_ptr<V[]>(new V[entry_count]);
		for (idx_t entry_idx = 0; entry_idx < entry_count; entry_idx++) {
			owned_data[entry_idx] = MAX_ENTRY;
		}
	}
	inline TemplatedValidityData(const V *validity_mask, idx_t count) {
		D_ASSERT(validity_mask);
		auto entry_count = EntryCount(count);
		owned_data = unique_ptr<V[]>(new V[entry_count]);
		for (idx_t entry_idx = 0; entry_idx < entry_count; entry_idx++) {
			owned_data[entry_idx] = validity_mask[entry_idx];
		}
	}

	unique_ptr<V[]> owned_data;

public:
	static inline idx_t EntryCount(idx_t count) {
		return (count + (BITS_PER_VALUE - 1)) / BITS_PER_VALUE;
	}
};

using validity_t = uint64_t;

struct ValidityData : TemplatedValidityData<validity_t> {
public:
	DUCKDB_API explicit ValidityData(idx_t count);
	DUCKDB_API ValidityData(const ValidityMask &original, idx_t count);
};

//! Type used for validity masks
template <typename V>
struct TemplatedValidityMask {
	using ValidityBuffer = TemplatedValidityData<V>;

public:
	static constexpr const int BITS_PER_VALUE = ValidityBuffer::BITS_PER_VALUE;
	static constexpr const int STANDARD_ENTRY_COUNT = (STANDARD_VECTOR_SIZE + (BITS_PER_VALUE - 1)) / BITS_PER_VALUE;
	static constexpr const int STANDARD_MASK_SIZE = STANDARD_ENTRY_COUNT * sizeof(validity_t);

public:
	inline TemplatedValidityMask() : validity_mask(nullptr) {
	}
	inline explicit TemplatedValidityMask(idx_t max_count) {
		Initialize(max_count);
	}
	inline explicit TemplatedValidityMask(V *ptr) : validity_mask(ptr) {
	}
	inline TemplatedValidityMask(const TemplatedValidityMask &original, idx_t count) {
		Copy(original, count);
	}

	static inline idx_t ValidityMaskSize(idx_t count = STANDARD_VECTOR_SIZE) {
		return ValidityBuffer::EntryCount(count) * sizeof(V);
	}
	inline bool AllValid() const {
		return !validity_mask;
	}
	inline bool CheckAllValid(idx_t count) const {
		if (AllValid()) {
			return true;
		}
		idx_t entry_count = ValidityBuffer::EntryCount(count);
		idx_t valid_count = 0;
		for (idx_t i = 0; i < entry_count; i++) {
			valid_count += validity_mask[i] == ValidityBuffer::MAX_ENTRY;
		}
		return valid_count == entry_count;
	}

	inline bool CheckAllValid(idx_t to, idx_t from) const {
		if (AllValid()) {
			return true;
		}
		for (idx_t i = from; i < to; i++) {
			if (!RowIsValid(i)) {
				return false;
			}
		}
		return true;
	}

	idx_t CountValid(const idx_t count) const {
		if (AllValid() || count == 0) {
			return count;
		}

		idx_t valid = 0;
		const auto entry_count = EntryCount(count);
		for (idx_t entry_idx = 0; entry_idx < entry_count;) {
			auto entry = GetValidityEntry(entry_idx++);
			// Handle ragged end
			if (entry_idx == entry_count) {
				idx_t idx_in_entry;
				GetEntryIndex(count, entry_idx, idx_in_entry);
				for (idx_t i = 0; i < idx_in_entry; ++i) {
					valid += idx_t(RowIsValid(entry, i));
				}
				break;
			}

			// Handle all set
			if (AllValid(entry)) {
				valid += BITS_PER_VALUE;
				continue;
			}

			// Count partial entry (Kernighan's algorithm)
			while (entry) {
				entry &= (entry - 1);
				++valid;
			}
		}

		return valid;
	}

	inline V *GetData() const {
		return validity_mask;
	}
	inline void Reset() {
		validity_mask = nullptr;
		validity_data.reset();
	}

	static inline idx_t EntryCount(idx_t count) {
		return ValidityBuffer::EntryCount(count);
	}
	inline V GetValidityEntry(idx_t entry_idx) const {
		if (!validity_mask) {
			return ValidityBuffer::MAX_ENTRY;
		}
		return validity_mask[entry_idx];
	}
	static inline bool AllValid(V entry) {
		return entry == ValidityBuffer::MAX_ENTRY;
	}
	static inline bool NoneValid(V entry) {
		return entry == 0;
	}
	static inline bool RowIsValid(V entry, idx_t idx_in_entry) {
		return entry & (V(1) << V(idx_in_entry));
	}
	static inline void GetEntryIndex(idx_t row_idx, idx_t &entry_idx, idx_t &idx_in_entry) {
		entry_idx = row_idx / BITS_PER_VALUE;
		idx_in_entry = row_idx % BITS_PER_VALUE;
	}
	//! Get an entry that has first-n bits set as valid and rest set as invalid
	static inline V EntryWithValidBits(idx_t n) {
		if (n == 0) {
			return V(0);
		}
		return ValidityBuffer::MAX_ENTRY >> (BITS_PER_VALUE - n);
	}

	//! RowIsValidUnsafe should only be used if AllValid() is false: it achieves the same as RowIsValid but skips a
	//! not-null check
	inline bool RowIsValidUnsafe(idx_t row_idx) const {
		D_ASSERT(validity_mask);
		idx_t entry_idx, idx_in_entry;
		GetEntryIndex(row_idx, entry_idx, idx_in_entry);
		auto entry = GetValidityEntry(entry_idx);
		return RowIsValid(entry, idx_in_entry);
	}

	//! Returns true if a row is valid (i.e. not null), false otherwise
	inline bool RowIsValid(idx_t row_idx) const {
		if (!validity_mask) {
			return true;
		}
		return RowIsValidUnsafe(row_idx);
	}

	//! Same as SetValid, but skips a null check on validity_mask
	inline void SetValidUnsafe(idx_t row_idx) {
		D_ASSERT(validity_mask);
		idx_t entry_idx, idx_in_entry;
		GetEntryIndex(row_idx, entry_idx, idx_in_entry);
		validity_mask[entry_idx] |= (V(1) << V(idx_in_entry));
	}

	//! Marks the entry at the specified row index as valid (i.e. not-null)
	inline void SetValid(idx_t row_idx) {
		if (!validity_mask) {
			// if AllValid() we don't need to do anything
			// the row is already valid
			return;
		}
		SetValidUnsafe(row_idx);
	}

	//! Marks the bit at the specified entry as invalid (i.e. null)
	inline void SetInvalidUnsafe(idx_t entry_idx, idx_t idx_in_entry) {
		D_ASSERT(validity_mask);
		validity_mask[entry_idx] &= ~(V(1) << V(idx_in_entry));
	}

	//! Marks the bit at the specified row index as invalid (i.e. null)
	inline void SetInvalidUnsafe(idx_t row_idx) {
		idx_t entry_idx, idx_in_entry;
		GetEntryIndex(row_idx, entry_idx, idx_in_entry);
		SetInvalidUnsafe(entry_idx, idx_in_entry);
	}

	//! Marks the entry at the specified row index as invalid (i.e. null)
	inline void SetInvalid(idx_t row_idx) {
		if (!validity_mask) {
			D_ASSERT(row_idx <= STANDARD_VECTOR_SIZE);
			Initialize(STANDARD_VECTOR_SIZE);
		}
		SetInvalidUnsafe(row_idx);
	}

	//! Mark the entry at the specified index as either valid or invalid (non-null or null)
	inline void Set(idx_t row_idx, bool valid) {
		if (valid) {
			SetValid(row_idx);
		} else {
			SetInvalid(row_idx);
		}
	}

	//! Ensure the validity mask is writable, allocating space if it is not initialized
	inline void EnsureWritable() {
		if (!validity_mask) {
			Initialize();
		}
	}

	//! Marks exactly "count" bits in the validity mask as invalid (null)
	inline void SetAllInvalid(idx_t count) {
		EnsureWritable();
		if (count == 0) {
			return;
		}
		auto last_entry_index = ValidityBuffer::EntryCount(count) - 1;
		for (idx_t i = 0; i < last_entry_index; i++) {
			validity_mask[i] = 0;
		}
		auto last_entry_bits = count % static_cast<idx_t>(BITS_PER_VALUE);
		validity_mask[last_entry_index] = (last_entry_bits == 0) ? 0 : (ValidityBuffer::MAX_ENTRY << (last_entry_bits));
	}

	//! Marks exactly "count" bits in the validity mask as valid (not null)
	inline void SetAllValid(idx_t count) {
		EnsureWritable();
		if (count == 0) {
			return;
		}
		auto last_entry_index = ValidityBuffer::EntryCount(count) - 1;
		for (idx_t i = 0; i < last_entry_index; i++) {
			validity_mask[i] = ValidityBuffer::MAX_ENTRY;
		}
		auto last_entry_bits = count % static_cast<idx_t>(BITS_PER_VALUE);
		validity_mask[last_entry_index] |=
		    (last_entry_bits == 0) ? ValidityBuffer::MAX_ENTRY : ~(ValidityBuffer::MAX_ENTRY << (last_entry_bits));
	}

	inline bool IsMaskSet() const {
		if (validity_mask) {
			return true;
		}
		return false;
	}

public:
	inline void Initialize(validity_t *validity) {
		validity_data.reset();
		validity_mask = validity;
	}
	inline void Initialize(const TemplatedValidityMask &other) {
		validity_mask = other.validity_mask;
		validity_data = other.validity_data;
	}
	inline void Initialize(idx_t count = STANDARD_VECTOR_SIZE) {
		validity_data = make_buffer<ValidityBuffer>(count);
		validity_mask = validity_data->owned_data.get();
	}
	inline void Copy(const TemplatedValidityMask &other, idx_t count) {
		if (other.AllValid()) {
			validity_data = nullptr;
			validity_mask = nullptr;
		} else {
			validity_data = make_buffer<ValidityBuffer>(other.validity_mask, count);
			validity_mask = validity_data->owned_data.get();
		}
	}

protected:
	V *validity_mask;
	buffer_ptr<ValidityBuffer> validity_data;
};

struct ValidityMask : public TemplatedValidityMask<validity_t> {
public:
	inline ValidityMask() : TemplatedValidityMask(nullptr) {
	}
	inline explicit ValidityMask(idx_t max_count) : TemplatedValidityMask(max_count) {
	}
	inline explicit ValidityMask(validity_t *ptr) : TemplatedValidityMask(ptr) {
	}
	inline ValidityMask(const ValidityMask &original, idx_t count) : TemplatedValidityMask(original, count) {
	}

public:
	DUCKDB_API void Resize(idx_t old_size, idx_t new_size);

	DUCKDB_API void Slice(const ValidityMask &other, idx_t offset);
	DUCKDB_API void Combine(const ValidityMask &other, idx_t count);
	DUCKDB_API string ToString(idx_t count) const;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/value.hpp
//
//
//===----------------------------------------------------------------------===//








namespace duckdb {

class Deserializer;
class Serializer;

//! The Value object holds a single arbitrary value of any type that can be
//! stored in the database.
class Value {
	friend struct StringValue;
	friend struct StructValue;
	friend struct ListValue;

public:
	//! Create an empty NULL value of the specified type
	DUCKDB_API explicit Value(LogicalType type = LogicalType::SQLNULL);
	//! Create an INTEGER value
	DUCKDB_API Value(int32_t val); // NOLINT: Allow implicit conversion from `int32_t`
	//! Create a BIGINT value
	DUCKDB_API Value(int64_t val); // NOLINT: Allow implicit conversion from `int64_t`
	//! Create a FLOAT value
	DUCKDB_API Value(float val); // NOLINT: Allow implicit conversion from `float`
	//! Create a DOUBLE value
	DUCKDB_API Value(double val); // NOLINT: Allow implicit conversion from `double`
	//! Create a VARCHAR value
	DUCKDB_API Value(const char *val); // NOLINT: Allow implicit conversion from `const char *`
	//! Create a NULL value
	DUCKDB_API Value(std::nullptr_t val); // NOLINT: Allow implicit conversion from `nullptr_t`
	//! Create a VARCHAR value
	DUCKDB_API Value(string_t val); // NOLINT: Allow implicit conversion from `string_t`
	//! Create a VARCHAR value
	DUCKDB_API Value(string val); // NOLINT: Allow implicit conversion from `string`
	//! Copy constructor
	DUCKDB_API Value(const Value &other);
	//! Move constructor
	DUCKDB_API Value(Value &&other) noexcept;
	//! Destructor
	DUCKDB_API ~Value();

	// copy assignment
	DUCKDB_API Value &operator=(const Value &other);
	// move assignment
	DUCKDB_API Value &operator=(Value &&other) noexcept;

	inline LogicalType &type() {
		return type_;
	}
	inline const LogicalType &type() const {
		return type_;
	}
	inline bool IsNull() const {
		return is_null;
	}

	//! Create the lowest possible value of a given type (numeric only)
	DUCKDB_API static Value MinimumValue(const LogicalType &type);
	//! Create the highest possible value of a given type (numeric only)
	DUCKDB_API static Value MaximumValue(const LogicalType &type);
	//! Create a Numeric value of the specified type with the specified value
	DUCKDB_API static Value Numeric(const LogicalType &type, int64_t value);
	DUCKDB_API static Value Numeric(const LogicalType &type, hugeint_t value);

	//! Create a tinyint Value from a specified value
	DUCKDB_API static Value BOOLEAN(int8_t value);
	//! Create a tinyint Value from a specified value
	DUCKDB_API static Value TINYINT(int8_t value);
	//! Create a smallint Value from a specified value
	DUCKDB_API static Value SMALLINT(int16_t value);
	//! Create an integer Value from a specified value
	DUCKDB_API static Value INTEGER(int32_t value);
	//! Create a bigint Value from a specified value
	DUCKDB_API static Value BIGINT(int64_t value);
	//! Create an unsigned tinyint Value from a specified value
	DUCKDB_API static Value UTINYINT(uint8_t value);
	//! Create an unsigned smallint Value from a specified value
	DUCKDB_API static Value USMALLINT(uint16_t value);
	//! Create an unsigned integer Value from a specified value
	DUCKDB_API static Value UINTEGER(uint32_t value);
	//! Create an unsigned bigint Value from a specified value
	DUCKDB_API static Value UBIGINT(uint64_t value);
	//! Create a hugeint Value from a specified value
	DUCKDB_API static Value HUGEINT(hugeint_t value);
	//! Create a uuid Value from a specified value
	DUCKDB_API static Value UUID(const string &value);
	//! Create a uuid Value from a specified value
	DUCKDB_API static Value UUID(hugeint_t value);
	//! Create a hash Value from a specified value
	DUCKDB_API static Value HASH(hash_t value);
	//! Create a pointer Value from a specified value
	DUCKDB_API static Value POINTER(uintptr_t value);
	//! Create a date Value from a specified date
	DUCKDB_API static Value DATE(date_t date);
	//! Create a date Value from a specified date
	DUCKDB_API static Value DATE(int32_t year, int32_t month, int32_t day);
	//! Create a time Value from a specified time
	DUCKDB_API static Value TIME(dtime_t time);
	DUCKDB_API static Value TIMETZ(dtime_t time);
	//! Create a time Value from a specified time
	DUCKDB_API static Value TIME(int32_t hour, int32_t min, int32_t sec, int32_t micros);
	//! Create a timestamp Value from a specified date/time combination
	DUCKDB_API static Value TIMESTAMP(date_t date, dtime_t time);
	//! Create a timestamp Value from a specified timestamp
	DUCKDB_API static Value TIMESTAMP(timestamp_t timestamp);
	DUCKDB_API static Value TIMESTAMPNS(timestamp_t timestamp);
	DUCKDB_API static Value TIMESTAMPMS(timestamp_t timestamp);
	DUCKDB_API static Value TIMESTAMPSEC(timestamp_t timestamp);
	DUCKDB_API static Value TIMESTAMPTZ(timestamp_t timestamp);
	//! Create a timestamp Value from a specified timestamp in separate values
	DUCKDB_API static Value TIMESTAMP(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t min, int32_t sec,
	                                  int32_t micros);
	DUCKDB_API static Value INTERVAL(int32_t months, int32_t days, int64_t micros);
	DUCKDB_API static Value INTERVAL(interval_t interval);
	//! Creates a JSON Value
	DUCKDB_API static Value JSON(const char *val);
	DUCKDB_API static Value JSON(string_t val);
	DUCKDB_API static Value JSON(string val);

	// Create a enum Value from a specified uint value
	DUCKDB_API static Value ENUM(uint64_t value, const LogicalType &original_type);

	// Decimal values
	DUCKDB_API static Value DECIMAL(int16_t value, uint8_t width, uint8_t scale);
	DUCKDB_API static Value DECIMAL(int32_t value, uint8_t width, uint8_t scale);
	DUCKDB_API static Value DECIMAL(int64_t value, uint8_t width, uint8_t scale);
	DUCKDB_API static Value DECIMAL(hugeint_t value, uint8_t width, uint8_t scale);
	//! Create a float Value from a specified value
	DUCKDB_API static Value FLOAT(float value);
	//! Create a double Value from a specified value
	DUCKDB_API static Value DOUBLE(double value);
	//! Create a struct value with given list of entries
	DUCKDB_API static Value STRUCT(child_list_t<Value> values);
	//! Create a list value with the given entries, list type is inferred from children
	//! Cannot be called with an empty list, use either EMPTYLIST or LIST with a type instead
	DUCKDB_API static Value LIST(vector<Value> values);
	//! Create a list value with the given entries
	DUCKDB_API static Value LIST(LogicalType child_type, vector<Value> values);
	//! Create an empty list with the specified child-type
	DUCKDB_API static Value EMPTYLIST(LogicalType child_type);
	//! Create a map value from a (key, value) pair
	DUCKDB_API static Value MAP(Value key, Value value);

	//! Create a blob Value from a data pointer and a length: no bytes are interpreted
	DUCKDB_API static Value BLOB(const_data_ptr_t data, idx_t len);
	DUCKDB_API static Value BLOB_RAW(const string &data) {
		return Value::BLOB((const_data_ptr_t)data.c_str(), data.size());
	}
	//! Creates a blob by casting a specified string to a blob (i.e. interpreting \x characters)
	DUCKDB_API static Value BLOB(const string &data);

	template <class T>
	T GetValue() const {
		throw InternalException("Unimplemented template type for Value::GetValue");
	}
	template <class T>
	static Value CreateValue(T value) {
		throw InternalException("Unimplemented template type for Value::CreateValue");
	}
	// Returns the internal value. Unlike GetValue(), this method does not perform casting, and assumes T matches the
	// type of the value. Only use this if you know what you are doing.
	template <class T>
	T GetValueUnsafe() const {
		throw InternalException("Unimplemented template type for Value::GetValueUnsafe");
	}
	//! Returns a reference to the internal value. This can only be used for primitive types.
	template <class T>
	T &GetReferenceUnsafe() {
		throw InternalException("Unimplemented template type for Value::GetReferenceUnsafe");
	}

	//! Return a copy of this value
	Value Copy() const {
		return Value(*this);
	}

	//! Hashes the Value
	DUCKDB_API hash_t Hash() const;
	//! Convert this value to a string
	DUCKDB_API string ToString() const;
	//! Convert this value to a SQL-parseable string
	DUCKDB_API string ToSQLString() const;

	DUCKDB_API uintptr_t GetPointer() const;

	//! Cast this value to another type, throws exception if its not possible
	DUCKDB_API Value CastAs(const LogicalType &target_type, bool strict = false) const;
	//! Tries to cast this value to another type, and stores the result in "new_value"
	DUCKDB_API bool TryCastAs(const LogicalType &target_type, Value &new_value, string *error_message,
	                          bool strict = false) const;
	//! Tries to cast this value to another type, and stores the result in THIS value again
	DUCKDB_API bool TryCastAs(const LogicalType &target_type, bool strict = false);

	//! Serializes a Value to a stand-alone binary blob
	DUCKDB_API void Serialize(Serializer &serializer) const;
	//! Deserializes a Value from a blob
	DUCKDB_API static Value Deserialize(Deserializer &source);

	//===--------------------------------------------------------------------===//
	// Comparison Operators
	//===--------------------------------------------------------------------===//
	DUCKDB_API bool operator==(const Value &rhs) const;
	DUCKDB_API bool operator!=(const Value &rhs) const;
	DUCKDB_API bool operator<(const Value &rhs) const;
	DUCKDB_API bool operator>(const Value &rhs) const;
	DUCKDB_API bool operator<=(const Value &rhs) const;
	DUCKDB_API bool operator>=(const Value &rhs) const;

	DUCKDB_API bool operator==(const int64_t &rhs) const;
	DUCKDB_API bool operator!=(const int64_t &rhs) const;
	DUCKDB_API bool operator<(const int64_t &rhs) const;
	DUCKDB_API bool operator>(const int64_t &rhs) const;
	DUCKDB_API bool operator<=(const int64_t &rhs) const;
	DUCKDB_API bool operator>=(const int64_t &rhs) const;

	DUCKDB_API static bool FloatIsFinite(float value);
	DUCKDB_API static bool DoubleIsFinite(double value);
	template <class T>
	static bool IsNan(T value) {
		throw InternalException("Unimplemented template type for Value::IsNan");
	}
	template <class T>
	static bool IsFinite(T value) {
		return true;
	}
	DUCKDB_API static bool StringIsValid(const char *str, idx_t length);
	static bool StringIsValid(const string &str) {
		return StringIsValid(str.c_str(), str.size());
	}

	//! Returns true if the values are (approximately) equivalent. Note this is NOT the SQL equivalence. For this
	//! function, NULL values are equivalent and floating point values that are close are equivalent.
	DUCKDB_API static bool ValuesAreEqual(const Value &result_value, const Value &value);
	//! Returns true if the values are not distinct from each other, following SQL semantics for NOT DISTINCT FROM.
	DUCKDB_API static bool NotDistinctFrom(const Value &lvalue, const Value &rvalue);

	friend std::ostream &operator<<(std::ostream &out, const Value &val) {
		out << val.ToString();
		return out;
	}
	DUCKDB_API void Print() const;

private:
	//! The logical of the value
	LogicalType type_;

#if DUCKDB_API_VERSION < DUCKDB_API_0_3_2
public:
#endif
	//! Whether or not the value is NULL
	bool is_null;

	//! The value of the object, if it is of a constant size Type
	union Val {
		int8_t boolean;
		int8_t tinyint;
		int16_t smallint;
		int32_t integer;
		int64_t bigint;
		uint8_t utinyint;
		uint16_t usmallint;
		uint32_t uinteger;
		uint64_t ubigint;
		hugeint_t hugeint;
		float float_;
		double double_;
		uintptr_t pointer;
		uint64_t hash;
		date_t date;
		dtime_t time;
		timestamp_t timestamp;
		interval_t interval;
	} value_;

	//! The value of the object, if it is of a variable size type
	string str_value;

	vector<Value> struct_value;
	vector<Value> list_value;

private:
	template <class T>
	T GetValueInternal() const;
};

//===--------------------------------------------------------------------===//
// Type-specific getters
//===--------------------------------------------------------------------===//
// Note that these are equivalent to calling GetValueUnsafe<X>, meaning no cast will be performed
// instead, an assertion will be triggered if the value is not of the correct type
struct BooleanValue {
	DUCKDB_API static bool Get(const Value &value);
};

struct TinyIntValue {
	DUCKDB_API static int8_t Get(const Value &value);
};

struct SmallIntValue {
	DUCKDB_API static int16_t Get(const Value &value);
};

struct IntegerValue {
	DUCKDB_API static int32_t Get(const Value &value);
};

struct BigIntValue {
	DUCKDB_API static int64_t Get(const Value &value);
};

struct HugeIntValue {
	DUCKDB_API static hugeint_t Get(const Value &value);
};

struct UTinyIntValue {
	DUCKDB_API static uint8_t Get(const Value &value);
};

struct USmallIntValue {
	DUCKDB_API static uint16_t Get(const Value &value);
};

struct UIntegerValue {
	DUCKDB_API static uint32_t Get(const Value &value);
};

struct UBigIntValue {
	DUCKDB_API static uint64_t Get(const Value &value);
};

struct FloatValue {
	DUCKDB_API static float Get(const Value &value);
};

struct DoubleValue {
	DUCKDB_API static double Get(const Value &value);
};

struct StringValue {
	DUCKDB_API static const string &Get(const Value &value);
};

struct DateValue {
	DUCKDB_API static date_t Get(const Value &value);
};

struct TimeValue {
	DUCKDB_API static dtime_t Get(const Value &value);
};

struct TimestampValue {
	DUCKDB_API static timestamp_t Get(const Value &value);
};

struct IntervalValue {
	DUCKDB_API static interval_t Get(const Value &value);
};

struct StructValue {
	DUCKDB_API static const vector<Value> &GetChildren(const Value &value);
};

struct ListValue {
	DUCKDB_API static const vector<Value> &GetChildren(const Value &value);
};

//! Return the internal integral value for any type that is stored as an integral value internally
//! This can be used on values of type integer, uinteger, but also date, timestamp, decimal, etc
struct IntegralValue {
	static hugeint_t Get(const Value &value);
};

template <>
Value DUCKDB_API Value::CreateValue(bool value);
template <>
Value DUCKDB_API Value::CreateValue(uint8_t value);
template <>
Value DUCKDB_API Value::CreateValue(uint16_t value);
template <>
Value DUCKDB_API Value::CreateValue(uint32_t value);
template <>
Value DUCKDB_API Value::CreateValue(uint64_t value);
template <>
Value DUCKDB_API Value::CreateValue(int8_t value);
template <>
Value DUCKDB_API Value::CreateValue(int16_t value);
template <>
Value DUCKDB_API Value::CreateValue(int32_t value);
template <>
Value DUCKDB_API Value::CreateValue(int64_t value);
template <>
Value DUCKDB_API Value::CreateValue(hugeint_t value);
template <>
Value DUCKDB_API Value::CreateValue(date_t value);
template <>
Value DUCKDB_API Value::CreateValue(dtime_t value);
template <>
Value DUCKDB_API Value::CreateValue(dtime_tz_t value);
template <>
Value DUCKDB_API Value::CreateValue(timestamp_t value);
template <>
Value DUCKDB_API Value::CreateValue(timestamp_sec_t value);
template <>
Value DUCKDB_API Value::CreateValue(timestamp_ms_t value);
template <>
Value DUCKDB_API Value::CreateValue(timestamp_ns_t value);
template <>
Value DUCKDB_API Value::CreateValue(timestamp_tz_t value);
template <>
Value DUCKDB_API Value::CreateValue(const char *value);
template <>
Value DUCKDB_API Value::CreateValue(string value);
template <>
Value DUCKDB_API Value::CreateValue(string_t value);
template <>
Value DUCKDB_API Value::CreateValue(float value);
template <>
Value DUCKDB_API Value::CreateValue(double value);
template <>
Value DUCKDB_API Value::CreateValue(interval_t value);
template <>
Value DUCKDB_API Value::CreateValue(Value value);

template <>
DUCKDB_API bool Value::GetValue() const;
template <>
DUCKDB_API int8_t Value::GetValue() const;
template <>
DUCKDB_API int16_t Value::GetValue() const;
template <>
DUCKDB_API int32_t Value::GetValue() const;
template <>
DUCKDB_API int64_t Value::GetValue() const;
template <>
DUCKDB_API uint8_t Value::GetValue() const;
template <>
DUCKDB_API uint16_t Value::GetValue() const;
template <>
DUCKDB_API uint32_t Value::GetValue() const;
template <>
DUCKDB_API uint64_t Value::GetValue() const;
template <>
DUCKDB_API hugeint_t Value::GetValue() const;
template <>
DUCKDB_API string Value::GetValue() const;
template <>
DUCKDB_API float Value::GetValue() const;
template <>
DUCKDB_API double Value::GetValue() const;
template <>
DUCKDB_API date_t Value::GetValue() const;
template <>
DUCKDB_API dtime_t Value::GetValue() const;
template <>
DUCKDB_API timestamp_t Value::GetValue() const;
template <>
DUCKDB_API interval_t Value::GetValue() const;
template <>
DUCKDB_API Value Value::GetValue() const;

template <>
DUCKDB_API bool Value::GetValueUnsafe() const;
template <>
DUCKDB_API int8_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API int16_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API int32_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API int64_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API hugeint_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API uint8_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API uint16_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API uint32_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API uint64_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API string Value::GetValueUnsafe() const;
template <>
DUCKDB_API string_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API float Value::GetValueUnsafe() const;
template <>
DUCKDB_API double Value::GetValueUnsafe() const;
template <>
DUCKDB_API date_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API dtime_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API timestamp_t Value::GetValueUnsafe() const;
template <>
DUCKDB_API interval_t Value::GetValueUnsafe() const;

template <>
DUCKDB_API int8_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API int16_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API int32_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API int64_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API hugeint_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API uint8_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API uint16_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API uint32_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API uint64_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API float &Value::GetReferenceUnsafe();
template <>
DUCKDB_API double &Value::GetReferenceUnsafe();
template <>
DUCKDB_API date_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API dtime_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API timestamp_t &Value::GetReferenceUnsafe();
template <>
DUCKDB_API interval_t &Value::GetReferenceUnsafe();

template <>
DUCKDB_API bool Value::IsNan(float input);
template <>
DUCKDB_API bool Value::IsNan(double input);

template <>
DUCKDB_API bool Value::IsFinite(float input);
template <>
DUCKDB_API bool Value::IsFinite(double input);
template <>
DUCKDB_API bool Value::IsFinite(date_t input);
template <>
DUCKDB_API bool Value::IsFinite(timestamp_t input);

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/vector_buffer.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/string_heap.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/storage/arena_allocator.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/allocator.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {
class Allocator;
class ClientContext;
class DatabaseInstance;
class ExecutionContext;
class ThreadContext;

struct AllocatorDebugInfo;

struct PrivateAllocatorData {
	PrivateAllocatorData();
	virtual ~PrivateAllocatorData();

	unique_ptr<AllocatorDebugInfo> debug_info;
};

typedef data_ptr_t (*allocate_function_ptr_t)(PrivateAllocatorData *private_data, idx_t size);
typedef void (*free_function_ptr_t)(PrivateAllocatorData *private_data, data_ptr_t pointer, idx_t size);
typedef data_ptr_t (*reallocate_function_ptr_t)(PrivateAllocatorData *private_data, data_ptr_t pointer, idx_t old_size,
                                                idx_t size);

class AllocatedData {
public:
	DUCKDB_API AllocatedData();
	DUCKDB_API AllocatedData(Allocator &allocator, data_ptr_t pointer, idx_t allocated_size);
	DUCKDB_API ~AllocatedData();
	// disable copy constructors
	AllocatedData(const AllocatedData &other) = delete;
	AllocatedData &operator=(const AllocatedData &) = delete;
	//! enable move constructors
	DUCKDB_API AllocatedData(AllocatedData &&other) noexcept;
	DUCKDB_API AllocatedData &operator=(AllocatedData &&) noexcept;

	data_ptr_t get() {
		return pointer;
	}
	const_data_ptr_t get() const {
		return pointer;
	}
	idx_t GetSize() const {
		return allocated_size;
	}
	void Reset();

private:
	Allocator *allocator;
	data_ptr_t pointer;
	idx_t allocated_size;
};

class Allocator {
public:
	DUCKDB_API Allocator();
	DUCKDB_API Allocator(allocate_function_ptr_t allocate_function_p, free_function_ptr_t free_function_p,
	                     reallocate_function_ptr_t reallocate_function_p,
	                     unique_ptr<PrivateAllocatorData> private_data);
	Allocator &operator=(Allocator &&allocator) noexcept = delete;
	DUCKDB_API ~Allocator();

	DUCKDB_API data_ptr_t AllocateData(idx_t size);
	DUCKDB_API void FreeData(data_ptr_t pointer, idx_t size);
	DUCKDB_API data_ptr_t ReallocateData(data_ptr_t pointer, idx_t old_size, idx_t new_size);

	AllocatedData Allocate(idx_t size) {
		return AllocatedData(*this, AllocateData(size), size);
	}

	static data_ptr_t DefaultAllocate(PrivateAllocatorData *private_data, idx_t size) {
		return (data_ptr_t)malloc(size);
	}
	static void DefaultFree(PrivateAllocatorData *private_data, data_ptr_t pointer, idx_t size) {
		free(pointer);
	}
	static data_ptr_t DefaultReallocate(PrivateAllocatorData *private_data, data_ptr_t pointer, idx_t old_size,
	                                    idx_t size) {
		return (data_ptr_t)realloc(pointer, size);
	}
	static Allocator &Get(ClientContext &context);
	static Allocator &Get(DatabaseInstance &db);

	PrivateAllocatorData *GetPrivateData() {
		return private_data.get();
	}

	static Allocator &DefaultAllocator();

private:
	allocate_function_ptr_t allocate_function;
	free_function_ptr_t free_function;
	reallocate_function_ptr_t reallocate_function;

	unique_ptr<PrivateAllocatorData> private_data;
};

//! The BufferAllocator is a wrapper around the global allocator class that sends any allocations made through the
//! buffer manager. This makes the buffer manager aware of the memory usage, allowing it to potentially free
//! other blocks to make space in memory.
//! Note that there is a cost to doing so (several atomic operations will be performed on allocation/free).
//! As such this class should be used primarily for larger allocations.
struct BufferAllocator {
	DUCKDB_API static Allocator &Get(ClientContext &context);
};

} // namespace duckdb


namespace duckdb {

struct ArenaChunk {
	ArenaChunk(Allocator &allocator, idx_t size);
	~ArenaChunk();

	AllocatedData data;
	idx_t current_position;
	idx_t maximum_size;
	unique_ptr<ArenaChunk> next;
	ArenaChunk *prev;
};

class ArenaAllocator {
	static constexpr const idx_t ARENA_ALLOCATOR_INITIAL_CAPACITY = 2048;

public:
	ArenaAllocator(Allocator &allocator, idx_t initial_capacity = ARENA_ALLOCATOR_INITIAL_CAPACITY);
	~ArenaAllocator();

	data_ptr_t Allocate(idx_t size);
	void Destroy();
	void Move(ArenaAllocator &allocator);

	ArenaChunk *GetHead();
	ArenaChunk *GetTail();

	bool IsEmpty();

private:
	//! Internal allocator that is used by the arena allocator
	Allocator &allocator;
	idx_t current_capacity;
	unique_ptr<ArenaChunk> head;
	ArenaChunk *tail;
};

} // namespace duckdb


namespace duckdb {
//! A string heap is the owner of a set of strings, strings can be inserted into
//! it On every insert, a pointer to the inserted string is returned The
//! returned pointer will remain valid until the StringHeap is destroyed
class StringHeap {
public:
	StringHeap();

	void Destroy();
	void Move(StringHeap &other);

	//! Add a string to the string heap, returns a pointer to the string
	string_t AddString(const char *data, idx_t len);
	//! Add a string to the string heap, returns a pointer to the string
	string_t AddString(const char *data);
	//! Add a string to the string heap, returns a pointer to the string
	string_t AddString(const string &data);
	//! Add a string to the string heap, returns a pointer to the string
	string_t AddString(const string_t &data);
	//! Add a blob to the string heap; blobs can be non-valid UTF8
	string_t AddBlob(const string_t &data);
	//! Add a blob to the string heap; blobs can be non-valid UTF8
	string_t AddBlob(const char *data, idx_t len);
	//! Allocates space for an empty string of size "len" on the heap
	string_t EmptyString(idx_t len);

private:
	ArenaAllocator allocator;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/string_type.hpp
//
//
//===----------------------------------------------------------------------===//






#include <cstring>

namespace duckdb {

struct string_t {
	friend struct StringComparisonOperators;
	friend class StringSegment;

public:
	static constexpr idx_t PREFIX_LENGTH = 4 * sizeof(char);
	static constexpr idx_t INLINE_LENGTH = 12;

	string_t() = default;
	explicit string_t(uint32_t len) {
		value.inlined.length = len;
	}
	string_t(const char *data, uint32_t len) {
		value.inlined.length = len;
		D_ASSERT(data || GetSize() == 0);
		if (IsInlined()) {
			// zero initialize the prefix first
			// this makes sure that strings with length smaller than 4 still have an equal prefix
			memset(value.inlined.inlined, 0, INLINE_LENGTH);
			if (GetSize() == 0) {
				return;
			}
			// small string: inlined
			memcpy(value.inlined.inlined, data, GetSize());
		} else {
			// large string: store pointer
			memcpy(value.pointer.prefix, data, PREFIX_LENGTH);
			value.pointer.ptr = (char *)data;
		}
	}
	string_t(const char *data) : string_t(data, strlen(data)) { // NOLINT: Allow implicit conversion from `const char*`
	}
	string_t(const string &value)
	    : string_t(value.c_str(), value.size()) { // NOLINT: Allow implicit conversion from `const char*`
	}

	bool IsInlined() const {
		return GetSize() <= INLINE_LENGTH;
	}

	//! this is unsafe since the string will not be terminated at the end
	const char *GetDataUnsafe() const {
		return IsInlined() ? (const char *)value.inlined.inlined : value.pointer.ptr;
	}

	char *GetDataWriteable() const {
		return IsInlined() ? (char *)value.inlined.inlined : value.pointer.ptr;
	}

	const char *GetPrefix() const {
		return value.pointer.prefix;
	}

	idx_t GetSize() const {
		return value.inlined.length;
	}

	string GetString() const {
		return string(GetDataUnsafe(), GetSize());
	}

	explicit operator string() const {
		return GetString();
	}

	void Finalize() {
		// set trailing NULL byte
		auto dataptr = (char *)GetDataUnsafe();
		if (GetSize() <= INLINE_LENGTH) {
			// fill prefix with zeros if the length is smaller than the prefix length
			for (idx_t i = GetSize(); i < INLINE_LENGTH; i++) {
				value.inlined.inlined[i] = '\0';
			}
		} else {
			// copy the data into the prefix
			memcpy(value.pointer.prefix, dataptr, PREFIX_LENGTH);
		}
	}

	void Verify() const;
	void VerifyNull() const;
	bool operator<(const string_t &r) const {
		auto this_str = this->GetString();
		auto r_str = r.GetString();
		return this_str < r_str;
	}

private:
	union {
		struct {
			uint32_t length;
			char prefix[4];
			char *ptr;
		} pointer;
		struct {
			uint32_t length;
			char inlined[12];
		} inlined;
	} value;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/storage/buffer/buffer_handle.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/storage/storage_info.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {
class Serializer;
class Deserializer;
struct FileHandle;

//! The version number of the database storage format
extern const uint64_t VERSION_NUMBER;

using block_id_t = int64_t;

#define INVALID_BLOCK (-1)

// maximum block id, 2^62
#define MAXIMUM_BLOCK 4611686018427388000LL

//! The MainHeader is the first header in the storage file. The MainHeader is typically written only once for a database
//! file.
struct MainHeader {
	static constexpr idx_t MAGIC_BYTE_SIZE = 4;
	static constexpr idx_t MAGIC_BYTE_OFFSET = sizeof(uint64_t);
	static constexpr idx_t FLAG_COUNT = 4;
	// the magic bytes in front of the file
	// should be "DUCK"
	static const char MAGIC_BYTES[];
	//! The version of the database
	uint64_t version_number;
	//! The set of flags used by the database
	uint64_t flags[FLAG_COUNT];

	static void CheckMagicBytes(FileHandle &handle);

	void Serialize(Serializer &ser);
	static MainHeader Deserialize(Deserializer &source);
};

//! The DatabaseHeader contains information about the current state of the database. Every storage file has two
//! DatabaseHeaders. On startup, the DatabaseHeader with the highest iteration count is used as the active header. When
//! a checkpoint is performed, the active DatabaseHeader is switched by increasing the iteration count of the
//! DatabaseHeader.
struct DatabaseHeader {
	//! The iteration count, increases by 1 every time the storage is checkpointed.
	uint64_t iteration;
	//! A pointer to the initial meta block
	block_id_t meta_block;
	//! A pointer to the block containing the free list
	block_id_t free_list;
	//! The number of blocks that is in the file as of this database header. If the file is larger than BLOCK_SIZE *
	//! block_count any blocks appearing AFTER block_count are implicitly part of the free_list.
	uint64_t block_count;

	void Serialize(Serializer &ser);
	static DatabaseHeader Deserialize(Deserializer &source);
};

} // namespace duckdb


namespace duckdb {
class BlockHandle;
class FileBuffer;

class BufferHandle {
public:
	DUCKDB_API BufferHandle();
	DUCKDB_API BufferHandle(shared_ptr<BlockHandle> handle, FileBuffer *node);
	DUCKDB_API ~BufferHandle();
	// disable copy constructors
	BufferHandle(const BufferHandle &other) = delete;
	BufferHandle &operator=(const BufferHandle &) = delete;
	//! enable move constructors
	DUCKDB_API BufferHandle(BufferHandle &&other) noexcept;
	DUCKDB_API BufferHandle &operator=(BufferHandle &&) noexcept;

public:
	//! Returns whether or not the BufferHandle is valid.
	DUCKDB_API bool IsValid() const;
	//! Returns a pointer to the buffer data. Handle must be valid.
	DUCKDB_API data_ptr_t Ptr() const;
	//! Returns a pointer to the buffer data. Handle must be valid.
	DUCKDB_API data_ptr_t Ptr();
	//! Gets the block id of the underlying block. Handle must be valid.
	DUCKDB_API block_id_t GetBlockId() const;
	//! Gets the underlying file buffer. Handle must be valid.
	DUCKDB_API FileBuffer &GetFileBuffer();
	//! Destroys the buffer handle
	DUCKDB_API void Destroy();

private:
	//! The block handle
	shared_ptr<BlockHandle> handle;
	//! The managed buffer node
	FileBuffer *node;
};

} // namespace duckdb


namespace duckdb {

class BufferHandle;
class VectorBuffer;
class Vector;

enum class VectorBufferType : uint8_t {
	STANDARD_BUFFER,     // standard buffer, holds a single array of data
	DICTIONARY_BUFFER,   // dictionary buffer, holds a selection vector
	VECTOR_CHILD_BUFFER, // vector child buffer: holds another vector
	STRING_BUFFER,       // string buffer, holds a string heap
	STRUCT_BUFFER,       // struct buffer, holds a ordered mapping from name to child vector
	LIST_BUFFER,         // list buffer, holds a single flatvector child
	MANAGED_BUFFER,      // managed buffer, holds a buffer managed by the buffermanager
	OPAQUE_BUFFER        // opaque buffer, can be created for example by the parquet reader
};

enum class VectorAuxiliaryDataType : uint8_t {
	ARROW_AUXILIARY // Holds Arrow Chunks that this vector depends on
};

struct VectorAuxiliaryData {
	explicit VectorAuxiliaryData(VectorAuxiliaryDataType type_p)
	    : type(type_p) {

	      };
	VectorAuxiliaryDataType type;

	virtual ~VectorAuxiliaryData() {
	}
};

//! The VectorBuffer is a class used by the vector to hold its data
class VectorBuffer {
public:
	explicit VectorBuffer(VectorBufferType type) : buffer_type(type) {
	}
	explicit VectorBuffer(idx_t data_size) : buffer_type(VectorBufferType::STANDARD_BUFFER) {
		if (data_size > 0) {
			data = unique_ptr<data_t[]>(new data_t[data_size]);
		}
	}
	explicit VectorBuffer(unique_ptr<data_t[]> data_p)
	    : buffer_type(VectorBufferType::STANDARD_BUFFER), data(move(data_p)) {
	}
	virtual ~VectorBuffer() {
	}
	VectorBuffer() {
	}

public:
	data_ptr_t GetData() {
		return data.get();
	}

	void SetData(unique_ptr<data_t[]> new_data) {
		data = move(new_data);
	}

	VectorAuxiliaryData *GetAuxiliaryData() {
		return aux_data.get();
	}

	void SetAuxiliaryData(unique_ptr<VectorAuxiliaryData> aux_data_p) {
		aux_data = move(aux_data_p);
	}

	static buffer_ptr<VectorBuffer> CreateStandardVector(PhysicalType type, idx_t capacity = STANDARD_VECTOR_SIZE);
	static buffer_ptr<VectorBuffer> CreateConstantVector(PhysicalType type);
	static buffer_ptr<VectorBuffer> CreateConstantVector(const LogicalType &logical_type);
	static buffer_ptr<VectorBuffer> CreateStandardVector(const LogicalType &logical_type,
	                                                     idx_t capacity = STANDARD_VECTOR_SIZE);

	inline VectorBufferType GetBufferType() const {
		return buffer_type;
	}

	inline VectorAuxiliaryDataType GetAuxiliaryDataType() const {
		return aux_data->type;
	}

protected:
	VectorBufferType buffer_type;
	unique_ptr<VectorAuxiliaryData> aux_data;
	unique_ptr<data_t[]> data;
};

//! The DictionaryBuffer holds a selection vector
class DictionaryBuffer : public VectorBuffer {
public:
	explicit DictionaryBuffer(const SelectionVector &sel)
	    : VectorBuffer(VectorBufferType::DICTIONARY_BUFFER), sel_vector(sel) {
	}
	explicit DictionaryBuffer(buffer_ptr<SelectionData> data)
	    : VectorBuffer(VectorBufferType::DICTIONARY_BUFFER), sel_vector(move(data)) {
	}
	explicit DictionaryBuffer(idx_t count = STANDARD_VECTOR_SIZE)
	    : VectorBuffer(VectorBufferType::DICTIONARY_BUFFER), sel_vector(count) {
	}

public:
	const SelectionVector &GetSelVector() const {
		return sel_vector;
	}
	SelectionVector &GetSelVector() {
		return sel_vector;
	}
	void SetSelVector(const SelectionVector &vector) {
		this->sel_vector.Initialize(vector);
	}

private:
	SelectionVector sel_vector;
};

class VectorStringBuffer : public VectorBuffer {
public:
	VectorStringBuffer();

public:
	string_t AddString(const char *data, idx_t len) {
		return heap.AddString(data, len);
	}
	string_t AddString(string_t data) {
		return heap.AddString(data);
	}
	string_t AddBlob(string_t data) {
		return heap.AddBlob(data.GetDataUnsafe(), data.GetSize());
	}
	string_t EmptyString(idx_t len) {
		return heap.EmptyString(len);
	}

	void AddHeapReference(buffer_ptr<VectorBuffer> heap) {
		references.push_back(move(heap));
	}

private:
	//! The string heap of this buffer
	StringHeap heap;
	// References to additional vector buffers referenced by this string buffer
	vector<buffer_ptr<VectorBuffer>> references;
};

class VectorStructBuffer : public VectorBuffer {
public:
	VectorStructBuffer();
	VectorStructBuffer(const LogicalType &struct_type, idx_t capacity = STANDARD_VECTOR_SIZE);
	VectorStructBuffer(Vector &other, const SelectionVector &sel, idx_t count);
	~VectorStructBuffer() override;

public:
	const vector<unique_ptr<Vector>> &GetChildren() const {
		return children;
	}
	vector<unique_ptr<Vector>> &GetChildren() {
		return children;
	}

private:
	//! child vectors used for nested data
	vector<unique_ptr<Vector>> children;
};

class VectorListBuffer : public VectorBuffer {
public:
	VectorListBuffer(unique_ptr<Vector> vector, idx_t initial_capacity = STANDARD_VECTOR_SIZE);
	VectorListBuffer(const LogicalType &list_type, idx_t initial_capacity = STANDARD_VECTOR_SIZE);
	~VectorListBuffer() override;

public:
	Vector &GetChild() {
		return *child;
	}
	void Reserve(idx_t to_reserve);

	void Append(const Vector &to_append, idx_t to_append_size, idx_t source_offset = 0);
	void Append(const Vector &to_append, const SelectionVector &sel, idx_t to_append_size, idx_t source_offset = 0);

	void PushBack(const Value &insert);

	idx_t capacity = 0;
	idx_t size = 0;

private:
	//! child vectors used for nested data
	unique_ptr<Vector> child;
};

//! The ManagedVectorBuffer holds a buffer handle
class ManagedVectorBuffer : public VectorBuffer {
public:
	explicit ManagedVectorBuffer(BufferHandle handle);
	~ManagedVectorBuffer() override;

private:
	BufferHandle handle;
};

} // namespace duckdb



namespace duckdb {

struct UnifiedVectorFormat {
	const SelectionVector *sel;
	data_ptr_t data;
	ValidityMask validity;
	SelectionVector owned_sel;
};

class VectorCache;
class VectorStructBuffer;
class VectorListBuffer;

struct SelCache;

//!  Vector of values of a specified PhysicalType.
class Vector {
	friend struct ConstantVector;
	friend struct DictionaryVector;
	friend struct FlatVector;
	friend struct ListVector;
	friend struct StringVector;
	friend struct StructVector;
	friend struct SequenceVector;

	friend class DataChunk;
	friend class VectorCacheBuffer;

public:
	//! Create a vector that references the other vector
	DUCKDB_API explicit Vector(Vector &other);
	//! Create a vector that slices another vector
	DUCKDB_API explicit Vector(Vector &other, const SelectionVector &sel, idx_t count);
	//! Create a vector that slices another vector starting from a specific offset
	DUCKDB_API explicit Vector(Vector &other, idx_t offset);
	//! Create a vector of size one holding the passed on value
	DUCKDB_API explicit Vector(const Value &value);
	//! Create a vector of size tuple_count (non-standard)
	DUCKDB_API explicit Vector(LogicalType type, idx_t capacity = STANDARD_VECTOR_SIZE);
	//! Create an empty standard vector with a type, equivalent to calling Vector(type, true, false)
	DUCKDB_API explicit Vector(const VectorCache &cache);
	//! Create a non-owning vector that references the specified data
	DUCKDB_API Vector(LogicalType type, data_ptr_t dataptr);
	//! Create an owning vector that holds at most STANDARD_VECTOR_SIZE entries.
	/*!
	    Create a new vector
	    If create_data is true, the vector will be an owning empty vector.
	    If zero_data is true, the allocated data will be zero-initialized.
	*/
	DUCKDB_API Vector(LogicalType type, bool create_data, bool zero_data, idx_t capacity = STANDARD_VECTOR_SIZE);
	// implicit copying of Vectors is not allowed
	Vector(const Vector &) = delete;
	// but moving of vectors is allowed
	DUCKDB_API Vector(Vector &&other) noexcept;

public:
	//! Create a vector that references the specified value.
	DUCKDB_API void Reference(const Value &value);
	//! Causes this vector to reference the data held by the other vector.
	//! The type of the "other" vector should match the type of this vector
	DUCKDB_API void Reference(Vector &other);
	//! Reinterpret the data of the other vector as the type of this vector
	//! Note that this takes the data of the other vector as-is and places it in this vector
	//! Without changing the type of this vector
	DUCKDB_API void Reinterpret(Vector &other);

	//! Causes this vector to reference the data held by the other vector, changes the type if required.
	DUCKDB_API void ReferenceAndSetType(Vector &other);

	//! Resets a vector from a vector cache.
	//! This turns the vector back into an empty FlatVector with STANDARD_VECTOR_SIZE entries.
	//! The VectorCache is used so this can be done without requiring any allocations.
	DUCKDB_API void ResetFromCache(const VectorCache &cache);

	//! Creates a reference to a slice of the other vector
	DUCKDB_API void Slice(Vector &other, idx_t offset);
	//! Creates a reference to a slice of the other vector
	DUCKDB_API void Slice(Vector &other, const SelectionVector &sel, idx_t count);
	//! Turns the vector into a dictionary vector with the specified dictionary
	DUCKDB_API void Slice(const SelectionVector &sel, idx_t count);
	//! Slice the vector, keeping the result around in a cache or potentially using the cache instead of slicing
	DUCKDB_API void Slice(const SelectionVector &sel, idx_t count, SelCache &cache);

	//! Creates the data of this vector with the specified type. Any data that
	//! is currently in the vector is destroyed.
	DUCKDB_API void Initialize(bool zero_data = false, idx_t capacity = STANDARD_VECTOR_SIZE);

	//! Converts this Vector to a printable string representation
	DUCKDB_API string ToString(idx_t count) const;
	DUCKDB_API void Print(idx_t count);

	DUCKDB_API string ToString() const;
	DUCKDB_API void Print();

	//! Flatten the vector, removing any compression and turning it into a FLAT_VECTOR
	DUCKDB_API void Flatten(idx_t count);
	DUCKDB_API void Flatten(const SelectionVector &sel, idx_t count);
	//! Creates a UnifiedVectorFormat of a vector
	//! The UnifiedVectorFormat allows efficient reading of vectors regardless of their vector type
	//! It contains (1) a data pointer, (2) a validity mask, and (3) a selection vector
	//! Access to the individual vector elements can be performed through data_pointer[sel_idx[i]]/validity[sel_idx[i]]
	//! The most common vector types (flat, constant & dictionary) can be converted to the canonical format "for free"
	//! ToUnifiedFormat was originally called Orrify, as a tribute to Orri Erling who came up with it
	DUCKDB_API void ToUnifiedFormat(idx_t count, UnifiedVectorFormat &data);

	//! Turn the vector into a sequence vector
	DUCKDB_API void Sequence(int64_t start, int64_t increment);

	//! Verify that the Vector is in a consistent, not corrupt state. DEBUG
	//! FUNCTION ONLY!
	DUCKDB_API void Verify(idx_t count);
	//! Asserts that the CheckMapValidity returns MapInvalidReason::VALID
	DUCKDB_API static void VerifyMap(Vector &map, const SelectionVector &sel, idx_t count);
	DUCKDB_API static void Verify(Vector &vector, const SelectionVector &sel, idx_t count);
	DUCKDB_API void UTFVerify(idx_t count);
	DUCKDB_API void UTFVerify(const SelectionVector &sel, idx_t count);

	//! Returns the [index] element of the Vector as a Value.
	DUCKDB_API Value GetValue(idx_t index) const;
	//! Sets the [index] element of the Vector to the specified Value.
	DUCKDB_API void SetValue(idx_t index, const Value &val);

	inline void SetAuxiliary(buffer_ptr<VectorBuffer> new_buffer) {
		auxiliary = std::move(new_buffer);
	};

	//! This functions resizes the vector
	DUCKDB_API void Resize(idx_t cur_size, idx_t new_size);

	//! Serializes a Vector to a stand-alone binary blob
	DUCKDB_API void Serialize(idx_t count, Serializer &serializer);
	//! Deserializes a blob back into a Vector
	DUCKDB_API void Deserialize(idx_t count, Deserializer &source);

	// Getters
	inline VectorType GetVectorType() const {
		return vector_type;
	}
	inline const LogicalType &GetType() const {
		return type;
	}
	inline data_ptr_t GetData() {
		return data;
	}

	inline buffer_ptr<VectorBuffer> GetAuxiliary() {
		return auxiliary;
	}

	inline buffer_ptr<VectorBuffer> GetBuffer() {
		return buffer;
	}

	// Setters
	DUCKDB_API void SetVectorType(VectorType vector_type);

private:
	//! Returns the [index] element of the Vector as a Value.
	static Value GetValue(const Vector &v, idx_t index);
	//! Returns the [index] element of the Vector as a Value.
	static Value GetValueInternal(const Vector &v, idx_t index);

protected:
	//! The vector type specifies how the data of the vector is physically stored (i.e. if it is a single repeated
	//! constant, if it is compressed)
	VectorType vector_type;
	//! The type of the elements stored in the vector (e.g. integer, float)
	LogicalType type;
	//! A pointer to the data.
	data_ptr_t data;
	//! The validity mask of the vector
	ValidityMask validity;
	//! The main buffer holding the data of the vector
	buffer_ptr<VectorBuffer> buffer;
	//! The buffer holding auxiliary data of the vector
	//! e.g. a string vector uses this to store strings
	buffer_ptr<VectorBuffer> auxiliary;
};

//! The DictionaryBuffer holds a selection vector
class VectorChildBuffer : public VectorBuffer {
public:
	VectorChildBuffer(Vector vector) : VectorBuffer(VectorBufferType::VECTOR_CHILD_BUFFER), data(move(vector)) {
	}

public:
	Vector data;
};

struct ConstantVector {
	static inline const_data_ptr_t GetData(const Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::CONSTANT_VECTOR ||
		         vector.GetVectorType() == VectorType::FLAT_VECTOR);
		return vector.data;
	}
	static inline data_ptr_t GetData(Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::CONSTANT_VECTOR ||
		         vector.GetVectorType() == VectorType::FLAT_VECTOR);
		return vector.data;
	}
	template <class T>
	static inline const T *GetData(const Vector &vector) {
		return (const T *)ConstantVector::GetData(vector);
	}
	template <class T>
	static inline T *GetData(Vector &vector) {
		return (T *)ConstantVector::GetData(vector);
	}
	static inline bool IsNull(const Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::CONSTANT_VECTOR);
		return !vector.validity.RowIsValid(0);
	}
	DUCKDB_API static void SetNull(Vector &vector, bool is_null);
	static inline ValidityMask &Validity(Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::CONSTANT_VECTOR);
		return vector.validity;
	}
	DUCKDB_API static const SelectionVector *ZeroSelectionVector(idx_t count, SelectionVector &owned_sel);
	DUCKDB_API static const SelectionVector *ZeroSelectionVector();
	//! Turns "vector" into a constant vector by referencing a value within the source vector
	DUCKDB_API static void Reference(Vector &vector, Vector &source, idx_t position, idx_t count);

	static const sel_t ZERO_VECTOR[STANDARD_VECTOR_SIZE];
};

struct DictionaryVector {
	static inline const SelectionVector &SelVector(const Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::DICTIONARY_VECTOR);
		return ((const DictionaryBuffer &)*vector.buffer).GetSelVector();
	}
	static inline SelectionVector &SelVector(Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::DICTIONARY_VECTOR);
		return ((DictionaryBuffer &)*vector.buffer).GetSelVector();
	}
	static inline const Vector &Child(const Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::DICTIONARY_VECTOR);
		return ((const VectorChildBuffer &)*vector.auxiliary).data;
	}
	static inline Vector &Child(Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::DICTIONARY_VECTOR);
		return ((VectorChildBuffer &)*vector.auxiliary).data;
	}
};

struct FlatVector {
	static inline data_ptr_t GetData(Vector &vector) {
		return ConstantVector::GetData(vector);
	}
	template <class T>
	static inline const T *GetData(const Vector &vector) {
		return ConstantVector::GetData<T>(vector);
	}
	template <class T>
	static inline T *GetData(Vector &vector) {
		return ConstantVector::GetData<T>(vector);
	}
	static inline void SetData(Vector &vector, data_ptr_t data) {
		D_ASSERT(vector.GetVectorType() == VectorType::FLAT_VECTOR);
		vector.data = data;
	}
	template <class T>
	static inline T GetValue(Vector &vector, idx_t idx) {
		D_ASSERT(vector.GetVectorType() == VectorType::FLAT_VECTOR);
		return FlatVector::GetData<T>(vector)[idx];
	}
	static inline const ValidityMask &Validity(const Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::FLAT_VECTOR);
		return vector.validity;
	}
	static inline ValidityMask &Validity(Vector &vector) {
		D_ASSERT(vector.GetVectorType() == VectorType::FLAT_VECTOR);
		return vector.validity;
	}
	static inline void SetValidity(Vector &vector, ValidityMask &new_validity) {
		D_ASSERT(vector.GetVectorType() == VectorType::FLAT_VECTOR);
		vector.validity.Initialize(new_validity);
	}
	DUCKDB_API static void SetNull(Vector &vector, idx_t idx, bool is_null);
	static inline bool IsNull(const Vector &vector, idx_t idx) {
		D_ASSERT(vector.GetVectorType() == VectorType::FLAT_VECTOR);
		return !vector.validity.RowIsValid(idx);
	}
	DUCKDB_API static const SelectionVector *IncrementalSelectionVector();
};

struct ListVector {
	static inline list_entry_t *GetData(Vector &v) {
		if (v.GetVectorType() == VectorType::DICTIONARY_VECTOR) {
			auto &child = DictionaryVector::Child(v);
			return GetData(child);
		}
		return FlatVector::GetData<list_entry_t>(v);
	}
	//! Gets a reference to the underlying child-vector of a list
	DUCKDB_API static const Vector &GetEntry(const Vector &vector);
	//! Gets a reference to the underlying child-vector of a list
	DUCKDB_API static Vector &GetEntry(Vector &vector);
	//! Gets the total size of the underlying child-vector of a list
	DUCKDB_API static idx_t GetListSize(const Vector &vector);
	//! Sets the total size of the underlying child-vector of a list
	DUCKDB_API static void SetListSize(Vector &vec, idx_t size);
	DUCKDB_API static void Reserve(Vector &vec, idx_t required_capacity);
	DUCKDB_API static void Append(Vector &target, const Vector &source, idx_t source_size, idx_t source_offset = 0);
	DUCKDB_API static void Append(Vector &target, const Vector &source, const SelectionVector &sel, idx_t source_size,
	                              idx_t source_offset = 0);
	DUCKDB_API static void PushBack(Vector &target, const Value &insert);
	DUCKDB_API static vector<idx_t> Search(Vector &list, const Value &key, idx_t row);
	DUCKDB_API static Value GetValuesFromOffsets(Vector &list, vector<idx_t> &offsets);
	//! Share the entry of the other list vector
	DUCKDB_API static void ReferenceEntry(Vector &vector, Vector &other);
};

struct StringVector {
	//! Add a string to the string heap of the vector (auxiliary data)
	DUCKDB_API static string_t AddString(Vector &vector, const char *data, idx_t len);
	//! Add a string or a blob to the string heap of the vector (auxiliary data)
	//! This function is the same as ::AddString, except the added data does not need to be valid UTF8
	DUCKDB_API static string_t AddStringOrBlob(Vector &vector, const char *data, idx_t len);
	//! Add a string to the string heap of the vector (auxiliary data)
	DUCKDB_API static string_t AddString(Vector &vector, const char *data);
	//! Add a string to the string heap of the vector (auxiliary data)
	DUCKDB_API static string_t AddString(Vector &vector, string_t data);
	//! Add a string to the string heap of the vector (auxiliary data)
	DUCKDB_API static string_t AddString(Vector &vector, const string &data);
	//! Add a string or a blob to the string heap of the vector (auxiliary data)
	//! This function is the same as ::AddString, except the added data does not need to be valid UTF8
	DUCKDB_API static string_t AddStringOrBlob(Vector &vector, string_t data);
	//! Allocates an empty string of the specified size, and returns a writable pointer that can be used to store the
	//! result of an operation
	DUCKDB_API static string_t EmptyString(Vector &vector, idx_t len);
	//! Adds a reference to a handle that stores strings of this vector
	DUCKDB_API static void AddHandle(Vector &vector, BufferHandle handle);
	//! Adds a reference to an unspecified vector buffer that stores strings of this vector
	DUCKDB_API static void AddBuffer(Vector &vector, buffer_ptr<VectorBuffer> buffer);
	//! Add a reference from this vector to the string heap of the provided vector
	DUCKDB_API static void AddHeapReference(Vector &vector, Vector &other);
};

struct MapVector {
	DUCKDB_API static const Vector &GetKeys(const Vector &vector);
	DUCKDB_API static const Vector &GetValues(const Vector &vector);
	DUCKDB_API static Vector &GetKeys(Vector &vector);
	DUCKDB_API static Vector &GetValues(Vector &vector);
};

struct StructVector {
	DUCKDB_API static const vector<unique_ptr<Vector>> &GetEntries(const Vector &vector);
	DUCKDB_API static vector<unique_ptr<Vector>> &GetEntries(Vector &vector);
};

struct SequenceVector {
	static void GetSequence(const Vector &vector, int64_t &start, int64_t &increment) {
		D_ASSERT(vector.GetVectorType() == VectorType::SEQUENCE_VECTOR);
		auto data = (int64_t *)vector.buffer->GetData();
		start = data[0];
		increment = data[1];
	}
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/vector_operations/vector_operations.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/data_chunk.hpp
//
//
//===----------------------------------------------------------------------===//







//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/arrow/arrow_wrapper.hpp
//
//
//===----------------------------------------------------------------------===//


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/arrow/arrow.hpp
//
//
//===----------------------------------------------------------------------===//

#ifndef ARROW_FLAG_DICTIONARY_ORDERED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ARROW_C_DATA_INTERFACE
#define ARROW_C_DATA_INTERFACE

#define ARROW_FLAG_DICTIONARY_ORDERED 1
#define ARROW_FLAG_NULLABLE           2
#define ARROW_FLAG_MAP_KEYS_SORTED    4

struct ArrowSchema {
	// Array type description
	const char *format;
	const char *name;
	const char *metadata;
	int64_t flags;
	int64_t n_children;
	struct ArrowSchema **children;
	struct ArrowSchema *dictionary;

	// Release callback
	void (*release)(struct ArrowSchema *);
	// Opaque producer-specific data
	void *private_data;
};

struct ArrowArray {
	// Array data description
	int64_t length;
	int64_t null_count;
	int64_t offset;
	int64_t n_buffers;
	int64_t n_children;
	const void **buffers;
	struct ArrowArray **children;
	struct ArrowArray *dictionary;

	// Release callback
	void (*release)(struct ArrowArray *);
	// Opaque producer-specific data
	void *private_data;
};
#endif

#ifndef ARROW_C_STREAM_INTERFACE
#define ARROW_C_STREAM_INTERFACE
// EXPERIMENTAL
struct ArrowArrayStream {
	// Callback to get the stream type
	// (will be the same for all arrays in the stream).
	// Return value: 0 if successful, an `errno`-compatible error code otherwise.
	int (*get_schema)(struct ArrowArrayStream *, struct ArrowSchema *out);
	// Callback to get the next array
	// (if no error and the array is released, the stream has ended)
	// Return value: 0 if successful, an `errno`-compatible error code otherwise.
	int (*get_next)(struct ArrowArrayStream *, struct ArrowArray *out);

	// Callback to get optional detailed error information.
	// This must only be called if the last stream operation failed
	// with a non-0 return code.  The returned pointer is only valid until
	// the next operation on this stream (including release).
	// If unavailable, NULL is returned.
	const char *(*get_last_error)(struct ArrowArrayStream *);

	// Release callback: release the stream's own resources.
	// Note that arrays returned by `get_next` must be individually released.
	void (*release)(struct ArrowArrayStream *);
	// Opaque producer-specific data
	void *private_data;
};
#endif

#ifdef __cplusplus
}
#endif

#endif


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/preserved_error.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

class PreservedError {
public:
	//! Not initialized, default constructor
	DUCKDB_API PreservedError();
	//! From std::exception
	DUCKDB_API explicit PreservedError(const std::exception &exception);
	//! From a raw string
	DUCKDB_API explicit PreservedError(const string &raw_message);
	//! From an Exception
	DUCKDB_API PreservedError(const Exception &exception);

public:
	//! Throw the error
	[[noreturn]] DUCKDB_API void Throw(const string &prepended_message = "") const;
	//! Get the internal exception type of the error
	DUCKDB_API const ExceptionType &Type() const;
	//! Allows adding addition information to the message
	DUCKDB_API PreservedError &AddToMessage(const string &prepended_message);
	//! Used in clients like C-API, creates the final message and returns a reference to it
	DUCKDB_API const string &Message();
	//! Let's us do things like 'if (error)'
	operator bool() const;
	bool operator==(const PreservedError &other) const;

private:
	//! Whether this PreservedError contains an exception or not
	bool initialized;
	//! The ExceptionType of the preserved exception
	ExceptionType type;
	//! The message the exception was constructed with (does not contain the Exception Type)
	string raw_message;
	//! The final message (stored in the preserved error for compatibility reasons with C-API)
	string final_message;
};

} // namespace duckdb


//! Here we have the internal duckdb classes that interact with Arrow's Internal Header (i.e., duckdb/commons/arrow.hpp)
namespace duckdb {
class QueryResult;
class DataChunk;

class ArrowSchemaWrapper {
public:
	ArrowSchema arrow_schema;

	ArrowSchemaWrapper() {
		arrow_schema.release = nullptr;
	}

	~ArrowSchemaWrapper();
};
class ArrowArrayWrapper {
public:
	ArrowArray arrow_array;
	ArrowArrayWrapper() {
		arrow_array.length = 0;
		arrow_array.release = nullptr;
	}
	~ArrowArrayWrapper();
};

class ArrowArrayStreamWrapper {
public:
	ArrowArrayStream arrow_array_stream;
	int64_t number_of_rows;

public:
	void GetSchema(ArrowSchemaWrapper &schema);

	shared_ptr<ArrowArrayWrapper> GetNextChunk();

	const char *GetError();

	~ArrowArrayStreamWrapper();
	ArrowArrayStreamWrapper() {
		arrow_array_stream.release = nullptr;
	}
};

class ArrowUtil {
public:
	static bool TryFetchChunk(QueryResult *result, idx_t chunk_size, ArrowArray *out, idx_t &result_count,
	                          PreservedError &error);
	static idx_t FetchChunk(QueryResult *result, idx_t chunk_size, ArrowArray *out);

private:
	static bool TryFetchNext(QueryResult &result, unique_ptr<DataChunk> &out, PreservedError &error);
};
} // namespace duckdb


struct ArrowArray;

namespace duckdb {
class Allocator;
class ClientContext;
class ExecutionContext;
class VectorCache;

//!  A Data Chunk represents a set of vectors.
/*!
    The data chunk class is the intermediate representation used by the
   execution engine of DuckDB. It effectively represents a subset of a relation.
   It holds a set of vectors that all have the same length.

    DataChunk is initialized using the DataChunk::Initialize function by
   providing it with a vector of TypeIds for the Vector members. By default,
   this function will also allocate a chunk of memory in the DataChunk for the
   vectors and all the vectors will be referencing vectors to the data owned by
   the chunk. The reason for this behavior is that the underlying vectors can
   become referencing vectors to other chunks as well (i.e. in the case an
   operator does not alter the data, such as a Filter operator which only adds a
   selection vector).

    In addition to holding the data of the vectors, the DataChunk also owns the
   selection vector that underlying vectors can point to.
*/
class DataChunk {
public:
	//! Creates an empty DataChunk
	DUCKDB_API DataChunk();
	DUCKDB_API ~DataChunk();

	//! The vectors owned by the DataChunk.
	vector<Vector> data;

public:
	inline idx_t size() const { // NOLINT
		return count;
	}
	inline idx_t ColumnCount() const {
		return data.size();
	}
	inline void SetCardinality(idx_t count_p) {
		D_ASSERT(count_p <= capacity);
		this->count = count_p;
	}
	inline void SetCardinality(const DataChunk &other) {
		this->count = other.size();
	}
	inline void SetCapacity(const DataChunk &other) {
		this->capacity = other.capacity;
	}

	DUCKDB_API Value GetValue(idx_t col_idx, idx_t index) const;
	DUCKDB_API void SetValue(idx_t col_idx, idx_t index, const Value &val);

	//! Returns true if all vectors in the DataChunk are constant
	DUCKDB_API bool AllConstant() const;

	//! Set the DataChunk to reference another data chunk
	DUCKDB_API void Reference(DataChunk &chunk);
	//! Set the DataChunk to own the data of data chunk, destroying the other chunk in the process
	DUCKDB_API void Move(DataChunk &chunk);

	//! Initializes the DataChunk with the specified types to an empty DataChunk
	//! This will create one vector of the specified type for each LogicalType in the
	//! types list. The vector will be referencing vector to the data owned by
	//! the DataChunk.
	DUCKDB_API void Initialize(Allocator &allocator, const vector<LogicalType> &types);
	DUCKDB_API void Initialize(ClientContext &context, const vector<LogicalType> &types);
	//! Initializes an empty DataChunk with the given types. The vectors will *not* have any data allocated for them.
	DUCKDB_API void InitializeEmpty(const vector<LogicalType> &types);
	//! Append the other DataChunk to this one. The column count and types of
	//! the two DataChunks have to match exactly. Throws an exception if there
	//! is not enough space in the chunk and resize is not allowed.
	DUCKDB_API void Append(const DataChunk &other, bool resize = false, SelectionVector *sel = nullptr,
	                       idx_t count = 0);

	//! Destroy all data and columns owned by this DataChunk
	DUCKDB_API void Destroy();

	//! Copies the data from this vector to another vector.
	DUCKDB_API void Copy(DataChunk &other, idx_t offset = 0) const;
	DUCKDB_API void Copy(DataChunk &other, const SelectionVector &sel, const idx_t source_count,
	                     const idx_t offset = 0) const;

	//! Splits the DataChunk in two
	DUCKDB_API void Split(DataChunk &other, idx_t split_idx);

	//! Fuses a DataChunk onto the right of this one, and destroys the other. Inverse of Split.
	DUCKDB_API void Fuse(DataChunk &other);

	//! Makes this DataChunk reference the specified columns in the other DataChunk
	DUCKDB_API void ReferenceColumns(DataChunk &other, vector<column_t> column_ids);

	//! Turn all the vectors from the chunk into flat vectors
	DUCKDB_API void Flatten();

	DUCKDB_API unique_ptr<UnifiedVectorFormat[]> ToUnifiedFormat();

	DUCKDB_API void Slice(const SelectionVector &sel_vector, idx_t count);

	//! Slice all Vectors from other.data[i] to data[i + 'col_offset']
	//! Turning all Vectors into Dictionary Vectors, using 'sel'
	DUCKDB_API void Slice(DataChunk &other, const SelectionVector &sel, idx_t count, idx_t col_offset = 0);

	//! Resets the DataChunk to its state right after the DataChunk::Initialize
	//! function was called. This sets the count to 0, and resets each member
	//! Vector to point back to the data owned by this DataChunk.
	DUCKDB_API void Reset();

	//! Serializes a DataChunk to a stand-alone binary blob
	DUCKDB_API void Serialize(Serializer &serializer);
	//! Deserializes a blob back into a DataChunk
	DUCKDB_API void Deserialize(Deserializer &source);

	//! Hashes the DataChunk to the target vector
	DUCKDB_API void Hash(Vector &result);

	//! Returns a list of types of the vectors of this data chunk
	DUCKDB_API vector<LogicalType> GetTypes();

	//! Converts this DataChunk to a printable string representation
	DUCKDB_API string ToString() const;
	DUCKDB_API void Print();

	DataChunk(const DataChunk &) = delete;

	//! Verify that the DataChunk is in a consistent, not corrupt state. DEBUG
	//! FUNCTION ONLY!
	DUCKDB_API void Verify();

private:
	//! The amount of tuples stored in the data chunk
	idx_t count;
	//! The amount of tuples that can be stored in the data chunk
	idx_t capacity;
	//! Vector caches, used to store data when ::Initialize is called
	vector<VectorCache> vector_caches;
};
} // namespace duckdb



#include <functional>

namespace duckdb {

// VectorOperations contains a set of operations that operate on sets of
// vectors. In general, the operators must all have the same type, otherwise an
// exception is thrown. Note that the functions underneath use restrict
// pointers, hence the data that the vectors point to (and hence the vector
// themselves) should not be equal! For example, if you call the function Add(A,
// B, A) then ASSERT_RESTRICT will be triggered. Instead call AddInPlace(A, B)
// or Add(A, B, C)
struct VectorOperations {
	//===--------------------------------------------------------------------===//
	// In-Place Operators
	//===--------------------------------------------------------------------===//
	//! left += delta
	static void AddInPlace(Vector &left, int64_t delta, idx_t count);

	//===--------------------------------------------------------------------===//
	// NULL Operators
	//===--------------------------------------------------------------------===//
	//! result = IS NOT NULL(input)
	static void IsNotNull(Vector &arg, Vector &result, idx_t count);
	//! result = IS NULL (input)
	static void IsNull(Vector &input, Vector &result, idx_t count);
	// Returns whether or not arg vector has a NULL value
	static bool HasNull(Vector &input, idx_t count);
	static bool HasNotNull(Vector &input, idx_t count);
	//! Count the number of not-NULL values.
	static idx_t CountNotNull(Vector &input, const idx_t count);

	//===--------------------------------------------------------------------===//
	// Boolean Operations
	//===--------------------------------------------------------------------===//
	// result = left && right
	static void And(Vector &left, Vector &right, Vector &result, idx_t count);
	// result = left || right
	static void Or(Vector &left, Vector &right, Vector &result, idx_t count);
	// result = NOT(left)
	static void Not(Vector &left, Vector &result, idx_t count);

	//===--------------------------------------------------------------------===//
	// Comparison Operations
	//===--------------------------------------------------------------------===//
	// result = left == right
	static void Equals(Vector &left, Vector &right, Vector &result, idx_t count);
	// result = left != right
	static void NotEquals(Vector &left, Vector &right, Vector &result, idx_t count);
	// result = left > right
	static void GreaterThan(Vector &left, Vector &right, Vector &result, idx_t count);
	// result = left >= right
	static void GreaterThanEquals(Vector &left, Vector &right, Vector &result, idx_t count);
	// result = left < right
	static void LessThan(Vector &left, Vector &right, Vector &result, idx_t count);
	// result = left <= right
	static void LessThanEquals(Vector &left, Vector &right, Vector &result, idx_t count);

	// result = A != B with nulls being equal
	static void DistinctFrom(Vector &left, Vector &right, Vector &result, idx_t count);
	// result := A == B with nulls being equal
	static void NotDistinctFrom(Vector &left, Vector &right, Vector &result, idx_t count);
	// result := A > B with nulls being maximal
	static void DistinctGreaterThan(Vector &left, Vector &right, Vector &result, idx_t count);
	// result := A >= B with nulls being maximal
	static void DistinctGreaterThanEquals(Vector &left, Vector &right, Vector &result, idx_t count);
	// result := A < B with nulls being maximal
	static void DistinctLessThan(Vector &left, Vector &right, Vector &result, idx_t count);
	// result := A <= B with nulls being maximal
	static void DistinctLessThanEquals(Vector &left, Vector &right, Vector &result, idx_t count);

	//===--------------------------------------------------------------------===//
	// Select Comparisons
	//===--------------------------------------------------------------------===//
	static idx_t Equals(Vector &left, Vector &right, const SelectionVector *sel, idx_t count, SelectionVector *true_sel,
	                    SelectionVector *false_sel);
	static idx_t NotEquals(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                       SelectionVector *true_sel, SelectionVector *false_sel);
	static idx_t GreaterThan(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                         SelectionVector *true_sel, SelectionVector *false_sel);
	static idx_t GreaterThanEquals(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                               SelectionVector *true_sel, SelectionVector *false_sel);
	static idx_t LessThan(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                      SelectionVector *true_sel, SelectionVector *false_sel);
	static idx_t LessThanEquals(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                            SelectionVector *true_sel, SelectionVector *false_sel);

	// true := A != B with nulls being equal
	static idx_t DistinctFrom(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                          SelectionVector *true_sel, SelectionVector *false_sel);
	// true := A == B with nulls being equal
	static idx_t NotDistinctFrom(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                             SelectionVector *true_sel, SelectionVector *false_sel);
	// true := A > B with nulls being maximal
	static idx_t DistinctGreaterThan(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                                 SelectionVector *true_sel, SelectionVector *false_sel);
	// true := A >= B with nulls being maximal
	static idx_t DistinctGreaterThanEquals(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                                       SelectionVector *true_sel, SelectionVector *false_sel);
	// true := A < B with nulls being maximal
	static idx_t DistinctLessThan(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                              SelectionVector *true_sel, SelectionVector *false_sel);
	// true := A <= B with nulls being maximal
	static idx_t DistinctLessThanEquals(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                                    SelectionVector *true_sel, SelectionVector *false_sel);

	// true := A > B with nulls being minimal
	static idx_t DistinctGreaterThanNullsFirst(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                                           SelectionVector *true_sel, SelectionVector *false_sel);
	// true := A < B with nulls being minimal
	static idx_t DistinctLessThanNullsFirst(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                                        SelectionVector *true_sel, SelectionVector *false_sel);

	//===--------------------------------------------------------------------===//
	// Nested Comparisons
	//===--------------------------------------------------------------------===//
	// true := A != B with nulls being equal
	static idx_t NestedNotEquals(Vector &left, Vector &right, const SelectionVector &sel, idx_t count,
	                             SelectionVector *true_sel, SelectionVector *false_sel);
	// true := A == B with nulls being equal
	static idx_t NestedEquals(Vector &left, Vector &right, const SelectionVector &sel, idx_t count,
	                          SelectionVector *true_sel, SelectionVector *false_sel);

	//===--------------------------------------------------------------------===//
	// Hash functions
	//===--------------------------------------------------------------------===//
	// hashes = HASH(input)
	static void Hash(Vector &input, Vector &hashes, idx_t count);
	static void Hash(Vector &input, Vector &hashes, const SelectionVector &rsel, idx_t count);
	// hashes ^= HASH(input)
	static void CombineHash(Vector &hashes, Vector &input, idx_t count);
	static void CombineHash(Vector &hashes, Vector &input, const SelectionVector &rsel, idx_t count);

	//===--------------------------------------------------------------------===//
	// Generate functions
	//===--------------------------------------------------------------------===//
	static void GenerateSequence(Vector &result, idx_t count, int64_t start = 0, int64_t increment = 1);
	static void GenerateSequence(Vector &result, idx_t count, const SelectionVector &sel, int64_t start = 0,
	                             int64_t increment = 1);
	//===--------------------------------------------------------------------===//
	// Helpers
	//===--------------------------------------------------------------------===//
	//! Cast the data from the source type to the target type. Any elements that could not be converted are turned into
	//! NULLs. If any elements cannot be converted, returns false and fills in the error_message. If no error message is
	//! provided, an exception is thrown instead.
	DUCKDB_API static bool TryCast(Vector &source, Vector &result, idx_t count, string *error_message,
	                               bool strict = false);
	//! Cast the data from the source type to the target type. Throws an exception if the cast fails.
	DUCKDB_API static void Cast(Vector &source, Vector &result, idx_t count, bool strict = false);

	// Copy the data of <source> to the target vector
	static void Copy(const Vector &source, Vector &target, idx_t source_count, idx_t source_offset,
	                 idx_t target_offset);
	static void Copy(const Vector &source, Vector &target, const SelectionVector &sel, idx_t source_count,
	                 idx_t source_offset, idx_t target_offset);

	// Copy the data of <source> to the target location, setting null values to
	// NullValue<T>. Used to store data without separate NULL mask.
	static void WriteToStorage(Vector &source, idx_t count, data_ptr_t target);
	// Reads the data of <source> to the target vector, setting the nullmask
	// for any NullValue<T> of source. Used to go back from storage to a proper vector
	static void ReadFromStorage(data_ptr_t source, idx_t count, Vector &result);
};
} // namespace duckdb


#include <functional>

namespace duckdb {

struct DefaultNullCheckOperator {
	template <class LEFT_TYPE, class RIGHT_TYPE>
	static inline bool Operation(LEFT_TYPE left, RIGHT_TYPE right) {
		return false;
	}
};

struct BinaryStandardOperatorWrapper {
	template <class FUNC, class OP, class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(FUNC fun, LEFT_TYPE left, RIGHT_TYPE right, ValidityMask &mask, idx_t idx) {
		return OP::template Operation<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE>(left, right);
	}

	static bool AddsNulls() {
		return false;
	}
};

struct BinarySingleArgumentOperatorWrapper {
	template <class FUNC, class OP, class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(FUNC fun, LEFT_TYPE left, RIGHT_TYPE right, ValidityMask &mask, idx_t idx) {
		return OP::template Operation<LEFT_TYPE>(left, right);
	}

	static bool AddsNulls() {
		return false;
	}
};

struct BinaryLambdaWrapper {
	template <class FUNC, class OP, class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(FUNC fun, LEFT_TYPE left, RIGHT_TYPE right, ValidityMask &mask, idx_t idx) {
		return fun(left, right);
	}

	static bool AddsNulls() {
		return false;
	}
};

struct BinaryLambdaWrapperWithNulls {
	template <class FUNC, class OP, class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(FUNC fun, LEFT_TYPE left, RIGHT_TYPE right, ValidityMask &mask, idx_t idx) {
		return fun(left, right, mask, idx);
	}

	static bool AddsNulls() {
		return true;
	}
};

struct BinaryExecutor {
	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE, class OPWRAPPER, class OP, class FUNC,
	          bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
	static void ExecuteFlatLoop(LEFT_TYPE *__restrict ldata, RIGHT_TYPE *__restrict rdata,
	                            RESULT_TYPE *__restrict result_data, idx_t count, ValidityMask &mask, FUNC fun) {
		if (!LEFT_CONSTANT) {
			ASSERT_RESTRICT(ldata, ldata + count, result_data, result_data + count);
		}
		if (!RIGHT_CONSTANT) {
			ASSERT_RESTRICT(rdata, rdata + count, result_data, result_data + count);
		}

		if (!mask.AllValid()) {
			idx_t base_idx = 0;
			auto entry_count = ValidityMask::EntryCount(count);
			for (idx_t entry_idx = 0; entry_idx < entry_count; entry_idx++) {
				auto validity_entry = mask.GetValidityEntry(entry_idx);
				idx_t next = MinValue<idx_t>(base_idx + ValidityMask::BITS_PER_VALUE, count);
				if (ValidityMask::AllValid(validity_entry)) {
					// all valid: perform operation
					for (; base_idx < next; base_idx++) {
						auto lentry = ldata[LEFT_CONSTANT ? 0 : base_idx];
						auto rentry = rdata[RIGHT_CONSTANT ? 0 : base_idx];
						result_data[base_idx] =
						    OPWRAPPER::template Operation<FUNC, OP, LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE>(
						        fun, lentry, rentry, mask, base_idx);
					}
				} else if (ValidityMask::NoneValid(validity_entry)) {
					// nothing valid: skip all
					base_idx = next;
					continue;
				} else {
					// partially valid: need to check individual elements for validity
					idx_t start = base_idx;
					for (; base_idx < next; base_idx++) {
						if (ValidityMask::RowIsValid(validity_entry, base_idx - start)) {
							auto lentry = ldata[LEFT_CONSTANT ? 0 : base_idx];
							auto rentry = rdata[RIGHT_CONSTANT ? 0 : base_idx];
							result_data[base_idx] =
							    OPWRAPPER::template Operation<FUNC, OP, LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE>(
							        fun, lentry, rentry, mask, base_idx);
						}
					}
				}
			}
		} else {
			for (idx_t i = 0; i < count; i++) {
				auto lentry = ldata[LEFT_CONSTANT ? 0 : i];
				auto rentry = rdata[RIGHT_CONSTANT ? 0 : i];
				result_data[i] = OPWRAPPER::template Operation<FUNC, OP, LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE>(
				    fun, lentry, rentry, mask, i);
			}
		}
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE, class OPWRAPPER, class OP, class FUNC>
	static void ExecuteConstant(Vector &left, Vector &right, Vector &result, FUNC fun) {
		result.SetVectorType(VectorType::CONSTANT_VECTOR);

		auto ldata = ConstantVector::GetData<LEFT_TYPE>(left);
		auto rdata = ConstantVector::GetData<RIGHT_TYPE>(right);
		auto result_data = ConstantVector::GetData<RESULT_TYPE>(result);

		if (ConstantVector::IsNull(left) || ConstantVector::IsNull(right)) {
			ConstantVector::SetNull(result, true);
			return;
		}
		*result_data = OPWRAPPER::template Operation<FUNC, OP, LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE>(
		    fun, *ldata, *rdata, ConstantVector::Validity(result), 0);
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE, class OPWRAPPER, class OP, class FUNC,
	          bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
	static void ExecuteFlat(Vector &left, Vector &right, Vector &result, idx_t count, FUNC fun) {
		auto ldata = FlatVector::GetData<LEFT_TYPE>(left);
		auto rdata = FlatVector::GetData<RIGHT_TYPE>(right);

		if ((LEFT_CONSTANT && ConstantVector::IsNull(left)) || (RIGHT_CONSTANT && ConstantVector::IsNull(right))) {
			// either left or right is constant NULL: result is constant NULL
			result.SetVectorType(VectorType::CONSTANT_VECTOR);
			ConstantVector::SetNull(result, true);
			return;
		}

		result.SetVectorType(VectorType::FLAT_VECTOR);
		auto result_data = FlatVector::GetData<RESULT_TYPE>(result);
		auto &result_validity = FlatVector::Validity(result);
		if (LEFT_CONSTANT) {
			if (OPWRAPPER::AddsNulls()) {
				result_validity.Copy(FlatVector::Validity(right), count);
			} else {
				FlatVector::SetValidity(result, FlatVector::Validity(right));
			}
		} else if (RIGHT_CONSTANT) {
			if (OPWRAPPER::AddsNulls()) {
				result_validity.Copy(FlatVector::Validity(left), count);
			} else {
				FlatVector::SetValidity(result, FlatVector::Validity(left));
			}
		} else {
			if (OPWRAPPER::AddsNulls()) {
				result_validity.Copy(FlatVector::Validity(left), count);
				if (result_validity.AllValid()) {
					result_validity.Copy(FlatVector::Validity(right), count);
				} else {
					result_validity.Combine(FlatVector::Validity(right), count);
				}
			} else {
				FlatVector::SetValidity(result, FlatVector::Validity(left));
				result_validity.Combine(FlatVector::Validity(right), count);
			}
		}
		ExecuteFlatLoop<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, OPWRAPPER, OP, FUNC, LEFT_CONSTANT, RIGHT_CONSTANT>(
		    ldata, rdata, result_data, count, result_validity, fun);
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE, class OPWRAPPER, class OP, class FUNC>
	static void ExecuteGenericLoop(LEFT_TYPE *__restrict ldata, RIGHT_TYPE *__restrict rdata,
	                               RESULT_TYPE *__restrict result_data, const SelectionVector *__restrict lsel,
	                               const SelectionVector *__restrict rsel, idx_t count, ValidityMask &lvalidity,
	                               ValidityMask &rvalidity, ValidityMask &result_validity, FUNC fun) {
		if (!lvalidity.AllValid() || !rvalidity.AllValid()) {
			for (idx_t i = 0; i < count; i++) {
				auto lindex = lsel->get_index(i);
				auto rindex = rsel->get_index(i);
				if (lvalidity.RowIsValid(lindex) && rvalidity.RowIsValid(rindex)) {
					auto lentry = ldata[lindex];
					auto rentry = rdata[rindex];
					result_data[i] = OPWRAPPER::template Operation<FUNC, OP, LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE>(
					    fun, lentry, rentry, result_validity, i);
				} else {
					result_validity.SetInvalid(i);
				}
			}
		} else {
			for (idx_t i = 0; i < count; i++) {
				auto lentry = ldata[lsel->get_index(i)];
				auto rentry = rdata[rsel->get_index(i)];
				result_data[i] = OPWRAPPER::template Operation<FUNC, OP, LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE>(
				    fun, lentry, rentry, result_validity, i);
			}
		}
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE, class OPWRAPPER, class OP, class FUNC>
	static void ExecuteGeneric(Vector &left, Vector &right, Vector &result, idx_t count, FUNC fun) {
		UnifiedVectorFormat ldata, rdata;

		left.ToUnifiedFormat(count, ldata);
		right.ToUnifiedFormat(count, rdata);

		result.SetVectorType(VectorType::FLAT_VECTOR);
		auto result_data = FlatVector::GetData<RESULT_TYPE>(result);
		ExecuteGenericLoop<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, OPWRAPPER, OP, FUNC>(
		    (LEFT_TYPE *)ldata.data, (RIGHT_TYPE *)rdata.data, result_data, ldata.sel, rdata.sel, count, ldata.validity,
		    rdata.validity, FlatVector::Validity(result), fun);
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE, class OPWRAPPER, class OP, class FUNC>
	static void ExecuteSwitch(Vector &left, Vector &right, Vector &result, idx_t count, FUNC fun) {
		auto left_vector_type = left.GetVectorType();
		auto right_vector_type = right.GetVectorType();
		if (left_vector_type == VectorType::CONSTANT_VECTOR && right_vector_type == VectorType::CONSTANT_VECTOR) {
			ExecuteConstant<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, OPWRAPPER, OP, FUNC>(left, right, result, fun);
		} else if (left_vector_type == VectorType::FLAT_VECTOR && right_vector_type == VectorType::CONSTANT_VECTOR) {
			ExecuteFlat<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, OPWRAPPER, OP, FUNC, false, true>(left, right, result,
			                                                                                  count, fun);
		} else if (left_vector_type == VectorType::CONSTANT_VECTOR && right_vector_type == VectorType::FLAT_VECTOR) {
			ExecuteFlat<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, OPWRAPPER, OP, FUNC, true, false>(left, right, result,
			                                                                                  count, fun);
		} else if (left_vector_type == VectorType::FLAT_VECTOR && right_vector_type == VectorType::FLAT_VECTOR) {
			ExecuteFlat<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, OPWRAPPER, OP, FUNC, false, false>(left, right, result,
			                                                                                   count, fun);
		} else {
			ExecuteGeneric<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, OPWRAPPER, OP, FUNC>(left, right, result, count, fun);
		}
	}

public:
	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE,
	          class FUNC = std::function<RESULT_TYPE(LEFT_TYPE, RIGHT_TYPE)>>
	static void Execute(Vector &left, Vector &right, Vector &result, idx_t count, FUNC fun) {
		ExecuteSwitch<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, BinaryLambdaWrapper, bool, FUNC>(left, right, result, count,
		                                                                                   fun);
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE, class OP,
	          class OPWRAPPER = BinarySingleArgumentOperatorWrapper>
	static void Execute(Vector &left, Vector &right, Vector &result, idx_t count) {
		ExecuteSwitch<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, OPWRAPPER, OP, bool>(left, right, result, count, false);
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE, class OP>
	static void ExecuteStandard(Vector &left, Vector &right, Vector &result, idx_t count) {
		ExecuteSwitch<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, BinaryStandardOperatorWrapper, OP, bool>(left, right, result,
		                                                                                           count, false);
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class RESULT_TYPE,
	          class FUNC = std::function<RESULT_TYPE(LEFT_TYPE, RIGHT_TYPE, ValidityMask &, idx_t)>>
	static void ExecuteWithNulls(Vector &left, Vector &right, Vector &result, idx_t count, FUNC fun) {
		ExecuteSwitch<LEFT_TYPE, RIGHT_TYPE, RESULT_TYPE, BinaryLambdaWrapperWithNulls, bool, FUNC>(left, right, result,
		                                                                                            count, fun);
	}

public:
	template <class LEFT_TYPE, class RIGHT_TYPE, class OP>
	static idx_t SelectConstant(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                            SelectionVector *true_sel, SelectionVector *false_sel) {
		auto ldata = ConstantVector::GetData<LEFT_TYPE>(left);
		auto rdata = ConstantVector::GetData<RIGHT_TYPE>(right);

		// both sides are constant, return either 0 or the count
		// in this case we do not fill in the result selection vector at all
		if (ConstantVector::IsNull(left) || ConstantVector::IsNull(right) || !OP::Operation(*ldata, *rdata)) {
			if (false_sel) {
				for (idx_t i = 0; i < count; i++) {
					false_sel->set_index(i, sel->get_index(i));
				}
			}
			return 0;
		} else {
			if (true_sel) {
				for (idx_t i = 0; i < count; i++) {
					true_sel->set_index(i, sel->get_index(i));
				}
			}
			return count;
		}
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class OP, bool LEFT_CONSTANT, bool RIGHT_CONSTANT, bool HAS_TRUE_SEL,
	          bool HAS_FALSE_SEL>
	static inline idx_t SelectFlatLoop(LEFT_TYPE *__restrict ldata, RIGHT_TYPE *__restrict rdata,
	                                   const SelectionVector *sel, idx_t count, ValidityMask &validity_mask,
	                                   SelectionVector *true_sel, SelectionVector *false_sel) {
		idx_t true_count = 0, false_count = 0;
		idx_t base_idx = 0;
		auto entry_count = ValidityMask::EntryCount(count);
		for (idx_t entry_idx = 0; entry_idx < entry_count; entry_idx++) {
			auto validity_entry = validity_mask.GetValidityEntry(entry_idx);
			idx_t next = MinValue<idx_t>(base_idx + ValidityMask::BITS_PER_VALUE, count);
			if (ValidityMask::AllValid(validity_entry)) {
				// all valid: perform operation
				for (; base_idx < next; base_idx++) {
					idx_t result_idx = sel->get_index(base_idx);
					idx_t lidx = LEFT_CONSTANT ? 0 : base_idx;
					idx_t ridx = RIGHT_CONSTANT ? 0 : base_idx;
					bool comparison_result = OP::Operation(ldata[lidx], rdata[ridx]);
					if (HAS_TRUE_SEL) {
						true_sel->set_index(true_count, result_idx);
						true_count += comparison_result;
					}
					if (HAS_FALSE_SEL) {
						false_sel->set_index(false_count, result_idx);
						false_count += !comparison_result;
					}
				}
			} else if (ValidityMask::NoneValid(validity_entry)) {
				// nothing valid: skip all
				if (HAS_FALSE_SEL) {
					for (; base_idx < next; base_idx++) {
						idx_t result_idx = sel->get_index(base_idx);
						false_sel->set_index(false_count, result_idx);
						false_count++;
					}
				}
				base_idx = next;
				continue;
			} else {
				// partially valid: need to check individual elements for validity
				idx_t start = base_idx;
				for (; base_idx < next; base_idx++) {
					idx_t result_idx = sel->get_index(base_idx);
					idx_t lidx = LEFT_CONSTANT ? 0 : base_idx;
					idx_t ridx = RIGHT_CONSTANT ? 0 : base_idx;
					bool comparison_result = ValidityMask::RowIsValid(validity_entry, base_idx - start) &&
					                         OP::Operation(ldata[lidx], rdata[ridx]);
					if (HAS_TRUE_SEL) {
						true_sel->set_index(true_count, result_idx);
						true_count += comparison_result;
					}
					if (HAS_FALSE_SEL) {
						false_sel->set_index(false_count, result_idx);
						false_count += !comparison_result;
					}
				}
			}
		}
		if (HAS_TRUE_SEL) {
			return true_count;
		} else {
			return count - false_count;
		}
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class OP, bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
	static inline idx_t SelectFlatLoopSwitch(LEFT_TYPE *__restrict ldata, RIGHT_TYPE *__restrict rdata,
	                                         const SelectionVector *sel, idx_t count, ValidityMask &mask,
	                                         SelectionVector *true_sel, SelectionVector *false_sel) {
		if (true_sel && false_sel) {
			return SelectFlatLoop<LEFT_TYPE, RIGHT_TYPE, OP, LEFT_CONSTANT, RIGHT_CONSTANT, true, true>(
			    ldata, rdata, sel, count, mask, true_sel, false_sel);
		} else if (true_sel) {
			return SelectFlatLoop<LEFT_TYPE, RIGHT_TYPE, OP, LEFT_CONSTANT, RIGHT_CONSTANT, true, false>(
			    ldata, rdata, sel, count, mask, true_sel, false_sel);
		} else {
			D_ASSERT(false_sel);
			return SelectFlatLoop<LEFT_TYPE, RIGHT_TYPE, OP, LEFT_CONSTANT, RIGHT_CONSTANT, false, true>(
			    ldata, rdata, sel, count, mask, true_sel, false_sel);
		}
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class OP, bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
	static idx_t SelectFlat(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                        SelectionVector *true_sel, SelectionVector *false_sel) {
		auto ldata = FlatVector::GetData<LEFT_TYPE>(left);
		auto rdata = FlatVector::GetData<RIGHT_TYPE>(right);

		if (LEFT_CONSTANT && ConstantVector::IsNull(left)) {
			if (false_sel) {
				for (idx_t i = 0; i < count; i++) {
					false_sel->set_index(i, sel->get_index(i));
				}
			}
			return 0;
		}
		if (RIGHT_CONSTANT && ConstantVector::IsNull(right)) {
			if (false_sel) {
				for (idx_t i = 0; i < count; i++) {
					false_sel->set_index(i, sel->get_index(i));
				}
			}
			return 0;
		}

		if (LEFT_CONSTANT) {
			return SelectFlatLoopSwitch<LEFT_TYPE, RIGHT_TYPE, OP, LEFT_CONSTANT, RIGHT_CONSTANT>(
			    ldata, rdata, sel, count, FlatVector::Validity(right), true_sel, false_sel);
		} else if (RIGHT_CONSTANT) {
			return SelectFlatLoopSwitch<LEFT_TYPE, RIGHT_TYPE, OP, LEFT_CONSTANT, RIGHT_CONSTANT>(
			    ldata, rdata, sel, count, FlatVector::Validity(left), true_sel, false_sel);
		} else {
			ValidityMask combined_mask = FlatVector::Validity(left);
			combined_mask.Combine(FlatVector::Validity(right), count);
			return SelectFlatLoopSwitch<LEFT_TYPE, RIGHT_TYPE, OP, LEFT_CONSTANT, RIGHT_CONSTANT>(
			    ldata, rdata, sel, count, combined_mask, true_sel, false_sel);
		}
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class OP, bool NO_NULL, bool HAS_TRUE_SEL, bool HAS_FALSE_SEL>
	static inline idx_t
	SelectGenericLoop(LEFT_TYPE *__restrict ldata, RIGHT_TYPE *__restrict rdata, const SelectionVector *__restrict lsel,
	                  const SelectionVector *__restrict rsel, const SelectionVector *__restrict result_sel, idx_t count,
	                  ValidityMask &lvalidity, ValidityMask &rvalidity, SelectionVector *true_sel,
	                  SelectionVector *false_sel) {
		idx_t true_count = 0, false_count = 0;
		for (idx_t i = 0; i < count; i++) {
			auto result_idx = result_sel->get_index(i);
			auto lindex = lsel->get_index(i);
			auto rindex = rsel->get_index(i);
			if ((NO_NULL || (lvalidity.RowIsValid(lindex) && rvalidity.RowIsValid(rindex))) &&
			    OP::Operation(ldata[lindex], rdata[rindex])) {
				if (HAS_TRUE_SEL) {
					true_sel->set_index(true_count++, result_idx);
				}
			} else {
				if (HAS_FALSE_SEL) {
					false_sel->set_index(false_count++, result_idx);
				}
			}
		}
		if (HAS_TRUE_SEL) {
			return true_count;
		} else {
			return count - false_count;
		}
	}
	template <class LEFT_TYPE, class RIGHT_TYPE, class OP, bool NO_NULL>
	static inline idx_t
	SelectGenericLoopSelSwitch(LEFT_TYPE *__restrict ldata, RIGHT_TYPE *__restrict rdata,
	                           const SelectionVector *__restrict lsel, const SelectionVector *__restrict rsel,
	                           const SelectionVector *__restrict result_sel, idx_t count, ValidityMask &lvalidity,
	                           ValidityMask &rvalidity, SelectionVector *true_sel, SelectionVector *false_sel) {
		if (true_sel && false_sel) {
			return SelectGenericLoop<LEFT_TYPE, RIGHT_TYPE, OP, NO_NULL, true, true>(
			    ldata, rdata, lsel, rsel, result_sel, count, lvalidity, rvalidity, true_sel, false_sel);
		} else if (true_sel) {
			return SelectGenericLoop<LEFT_TYPE, RIGHT_TYPE, OP, NO_NULL, true, false>(
			    ldata, rdata, lsel, rsel, result_sel, count, lvalidity, rvalidity, true_sel, false_sel);
		} else {
			D_ASSERT(false_sel);
			return SelectGenericLoop<LEFT_TYPE, RIGHT_TYPE, OP, NO_NULL, false, true>(
			    ldata, rdata, lsel, rsel, result_sel, count, lvalidity, rvalidity, true_sel, false_sel);
		}
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class OP>
	static inline idx_t
	SelectGenericLoopSwitch(LEFT_TYPE *__restrict ldata, RIGHT_TYPE *__restrict rdata,
	                        const SelectionVector *__restrict lsel, const SelectionVector *__restrict rsel,
	                        const SelectionVector *__restrict result_sel, idx_t count, ValidityMask &lvalidity,
	                        ValidityMask &rvalidity, SelectionVector *true_sel, SelectionVector *false_sel) {
		if (!lvalidity.AllValid() || !rvalidity.AllValid()) {
			return SelectGenericLoopSelSwitch<LEFT_TYPE, RIGHT_TYPE, OP, false>(
			    ldata, rdata, lsel, rsel, result_sel, count, lvalidity, rvalidity, true_sel, false_sel);
		} else {
			return SelectGenericLoopSelSwitch<LEFT_TYPE, RIGHT_TYPE, OP, true>(
			    ldata, rdata, lsel, rsel, result_sel, count, lvalidity, rvalidity, true_sel, false_sel);
		}
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class OP>
	static idx_t SelectGeneric(Vector &left, Vector &right, const SelectionVector *sel, idx_t count,
	                           SelectionVector *true_sel, SelectionVector *false_sel) {
		UnifiedVectorFormat ldata, rdata;

		left.ToUnifiedFormat(count, ldata);
		right.ToUnifiedFormat(count, rdata);

		return SelectGenericLoopSwitch<LEFT_TYPE, RIGHT_TYPE, OP>((LEFT_TYPE *)ldata.data, (RIGHT_TYPE *)rdata.data,
		                                                          ldata.sel, rdata.sel, sel, count, ldata.validity,
		                                                          rdata.validity, true_sel, false_sel);
	}

	template <class LEFT_TYPE, class RIGHT_TYPE, class OP>
	static idx_t Select(Vector &left, Vector &right, const SelectionVector *sel, idx_t count, SelectionVector *true_sel,
	                    SelectionVector *false_sel) {
		if (!sel) {
			sel = FlatVector::IncrementalSelectionVector();
		}
		if (left.GetVectorType() == VectorType::CONSTANT_VECTOR &&
		    right.GetVectorType() == VectorType::CONSTANT_VECTOR) {
			return SelectConstant<LEFT_TYPE, RIGHT_TYPE, OP>(left, right, sel, count, true_sel, false_sel);
		} else if (left.GetVectorType() == VectorType::CONSTANT_VECTOR &&
		           right.GetVectorType() == VectorType::FLAT_VECTOR) {
			return SelectFlat<LEFT_TYPE, RIGHT_TYPE, OP, true, false>(left, right, sel, count, true_sel, false_sel);
		} else if (left.GetVectorType() == VectorType::FLAT_VECTOR &&
		           right.GetVectorType() == VectorType::CONSTANT_VECTOR) {
			return SelectFlat<LEFT_TYPE, RIGHT_TYPE, OP, false, true>(left, right, sel, count, true_sel, false_sel);
		} else if (left.GetVectorType() == VectorType::FLAT_VECTOR &&
		           right.GetVectorType() == VectorType::FLAT_VECTOR) {
			return SelectFlat<LEFT_TYPE, RIGHT_TYPE, OP, false, false>(left, right, sel, count, true_sel, false_sel);
		} else {
			return SelectGeneric<LEFT_TYPE, RIGHT_TYPE, OP>(left, right, sel, count, true_sel, false_sel);
		}
	}
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/vector_operations/ternary_executor.hpp
//
//
//===----------------------------------------------------------------------===//







#include <functional>

namespace duckdb {

struct TernaryLambdaWrapper {
	template <class FUN, class A_TYPE, class B_TYPE, class C_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(FUN fun, A_TYPE a, B_TYPE b, C_TYPE c, ValidityMask &mask, idx_t idx) {
		return fun(a, b, c);
	}
};

struct TernaryLambdaWrapperWithNulls {
	template <class FUN, class A_TYPE, class B_TYPE, class C_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(FUN fun, A_TYPE a, B_TYPE b, C_TYPE c, ValidityMask &mask, idx_t idx) {
		return fun(a, b, c, mask, idx);
	}
};

struct TernaryExecutor {
private:
	template <class A_TYPE, class B_TYPE, class C_TYPE, class RESULT_TYPE, class OPWRAPPER, class FUN>
	static inline void ExecuteLoop(A_TYPE *__restrict adata, B_TYPE *__restrict bdata, C_TYPE *__restrict cdata,
	                               RESULT_TYPE *__restrict result_data, idx_t count, const SelectionVector &asel,
	                               const SelectionVector &bsel, const SelectionVector &csel, ValidityMask &avalidity,
	                               ValidityMask &bvalidity, ValidityMask &cvalidity, ValidityMask &result_validity,
	                               FUN fun) {
		if (!avalidity.AllValid() || !bvalidity.AllValid() || !cvalidity.AllValid()) {
			for (idx_t i = 0; i < count; i++) {
				auto aidx = asel.get_index(i);
				auto bidx = bsel.get_index(i);
				auto cidx = csel.get_index(i);
				if (avalidity.RowIsValid(aidx) && bvalidity.RowIsValid(bidx) && cvalidity.RowIsValid(cidx)) {
					result_data[i] = OPWRAPPER::template Operation<FUN, A_TYPE, B_TYPE, C_TYPE, RESULT_TYPE>(
					    fun, adata[aidx], bdata[bidx], cdata[cidx], result_validity, i);
				} else {
					result_validity.SetInvalid(i);
				}
			}
		} else {
			for (idx_t i = 0; i < count; i++) {
				auto aidx = asel.get_index(i);
				auto bidx = bsel.get_index(i);
				auto cidx = csel.get_index(i);
				result_data[i] = OPWRAPPER::template Operation<FUN, A_TYPE, B_TYPE, C_TYPE, RESULT_TYPE>(
				    fun, adata[aidx], bdata[bidx], cdata[cidx], result_validity, i);
			}
		}
	}

public:
	template <class A_TYPE, class B_TYPE, class C_TYPE, class RESULT_TYPE, class OPWRAPPER, class FUN>
	static void ExecuteGeneric(Vector &a, Vector &b, Vector &c, Vector &result, idx_t count, FUN fun) {
		if (a.GetVectorType() == VectorType::CONSTANT_VECTOR && b.GetVectorType() == VectorType::CONSTANT_VECTOR &&
		    c.GetVectorType() == VectorType::CONSTANT_VECTOR) {
			result.SetVectorType(VectorType::CONSTANT_VECTOR);
			if (ConstantVector::IsNull(a) || ConstantVector::IsNull(b) || ConstantVector::IsNull(c)) {
				ConstantVector::SetNull(result, true);
			} else {
				auto adata = ConstantVector::GetData<A_TYPE>(a);
				auto bdata = ConstantVector::GetData<B_TYPE>(b);
				auto cdata = ConstantVector::GetData<C_TYPE>(c);
				auto result_data = ConstantVector::GetData<RESULT_TYPE>(result);
				auto &result_validity = ConstantVector::Validity(result);
				result_data[0] = OPWRAPPER::template Operation<FUN, A_TYPE, B_TYPE, C_TYPE, RESULT_TYPE>(
				    fun, adata[0], bdata[0], cdata[0], result_validity, 0);
			}
		} else {
			result.SetVectorType(VectorType::FLAT_VECTOR);

			UnifiedVectorFormat adata, bdata, cdata;
			a.ToUnifiedFormat(count, adata);
			b.ToUnifiedFormat(count, bdata);
			c.ToUnifiedFormat(count, cdata);

			ExecuteLoop<A_TYPE, B_TYPE, C_TYPE, RESULT_TYPE, OPWRAPPER>(
			    (A_TYPE *)adata.data, (B_TYPE *)bdata.data, (C_TYPE *)cdata.data,
			    FlatVector::GetData<RESULT_TYPE>(result), count, *adata.sel, *bdata.sel, *cdata.sel, adata.validity,
			    bdata.validity, cdata.validity, FlatVector::Validity(result), fun);
		}
	}

	template <class A_TYPE, class B_TYPE, class C_TYPE, class RESULT_TYPE,
	          class FUN = std::function<RESULT_TYPE(A_TYPE, B_TYPE, C_TYPE)>>
	static void Execute(Vector &a, Vector &b, Vector &c, Vector &result, idx_t count, FUN fun) {
		ExecuteGeneric<A_TYPE, B_TYPE, C_TYPE, RESULT_TYPE, TernaryLambdaWrapper, FUN>(a, b, c, result, count, fun);
	}

	template <class A_TYPE, class B_TYPE, class C_TYPE, class RESULT_TYPE,
	          class FUN = std::function<RESULT_TYPE(A_TYPE, B_TYPE, C_TYPE, ValidityMask &, idx_t)>>
	static void ExecuteWithNulls(Vector &a, Vector &b, Vector &c, Vector &result, idx_t count, FUN fun) {
		ExecuteGeneric<A_TYPE, B_TYPE, C_TYPE, RESULT_TYPE, TernaryLambdaWrapperWithNulls, FUN>(a, b, c, result, count,
		                                                                                        fun);
	}

private:
	template <class A_TYPE, class B_TYPE, class C_TYPE, class OP, bool NO_NULL, bool HAS_TRUE_SEL, bool HAS_FALSE_SEL>
	static inline idx_t SelectLoop(A_TYPE *__restrict adata, B_TYPE *__restrict bdata, C_TYPE *__restrict cdata,
	                               const SelectionVector *result_sel, idx_t count, const SelectionVector &asel,
	                               const SelectionVector &bsel, const SelectionVector &csel, ValidityMask &avalidity,
	                               ValidityMask &bvalidity, ValidityMask &cvalidity, SelectionVector *true_sel,
	                               SelectionVector *false_sel) {
		idx_t true_count = 0, false_count = 0;
		for (idx_t i = 0; i < count; i++) {
			auto result_idx = result_sel->get_index(i);
			auto aidx = asel.get_index(i);
			auto bidx = bsel.get_index(i);
			auto cidx = csel.get_index(i);
			bool comparison_result =
			    (NO_NULL || (avalidity.RowIsValid(aidx) && bvalidity.RowIsValid(bidx) && cvalidity.RowIsValid(cidx))) &&
			    OP::Operation(adata[aidx], bdata[bidx], cdata[cidx]);
			if (HAS_TRUE_SEL) {
				true_sel->set_index(true_count, result_idx);
				true_count += comparison_result;
			}
			if (HAS_FALSE_SEL) {
				false_sel->set_index(false_count, result_idx);
				false_count += !comparison_result;
			}
		}
		if (HAS_TRUE_SEL) {
			return true_count;
		} else {
			return count - false_count;
		}
	}

	template <class A_TYPE, class B_TYPE, class C_TYPE, class OP, bool NO_NULL>
	static inline idx_t SelectLoopSelSwitch(UnifiedVectorFormat &adata, UnifiedVectorFormat &bdata,
	                                        UnifiedVectorFormat &cdata, const SelectionVector *sel, idx_t count,
	                                        SelectionVector *true_sel, SelectionVector *false_sel) {
		if (true_sel && false_sel) {
			return SelectLoop<A_TYPE, B_TYPE, C_TYPE, OP, NO_NULL, true, true>(
			    (A_TYPE *)adata.data, (B_TYPE *)bdata.data, (C_TYPE *)cdata.data, sel, count, *adata.sel, *bdata.sel,
			    *cdata.sel, adata.validity, bdata.validity, cdata.validity, true_sel, false_sel);
		} else if (true_sel) {
			return SelectLoop<A_TYPE, B_TYPE, C_TYPE, OP, NO_NULL, true, false>(
			    (A_TYPE *)adata.data, (B_TYPE *)bdata.data, (C_TYPE *)cdata.data, sel, count, *adata.sel, *bdata.sel,
			    *cdata.sel, adata.validity, bdata.validity, cdata.validity, true_sel, false_sel);
		} else {
			D_ASSERT(false_sel);
			return SelectLoop<A_TYPE, B_TYPE, C_TYPE, OP, NO_NULL, false, true>(
			    (A_TYPE *)adata.data, (B_TYPE *)bdata.data, (C_TYPE *)cdata.data, sel, count, *adata.sel, *bdata.sel,
			    *cdata.sel, adata.validity, bdata.validity, cdata.validity, true_sel, false_sel);
		}
	}

	template <class A_TYPE, class B_TYPE, class C_TYPE, class OP>
	static inline idx_t SelectLoopSwitch(UnifiedVectorFormat &adata, UnifiedVectorFormat &bdata,
	                                     UnifiedVectorFormat &cdata, const SelectionVector *sel, idx_t count,
	                                     SelectionVector *true_sel, SelectionVector *false_sel) {
		if (!adata.validity.AllValid() || !bdata.validity.AllValid() || !cdata.validity.AllValid()) {
			return SelectLoopSelSwitch<A_TYPE, B_TYPE, C_TYPE, OP, false>(adata, bdata, cdata, sel, count, true_sel,
			                                                              false_sel);
		} else {
			return SelectLoopSelSwitch<A_TYPE, B_TYPE, C_TYPE, OP, true>(adata, bdata, cdata, sel, count, true_sel,
			                                                             false_sel);
		}
	}

public:
	template <class A_TYPE, class B_TYPE, class C_TYPE, class OP>
	static idx_t Select(Vector &a, Vector &b, Vector &c, const SelectionVector *sel, idx_t count,
	                    SelectionVector *true_sel, SelectionVector *false_sel) {
		if (!sel) {
			sel = FlatVector::IncrementalSelectionVector();
		}
		UnifiedVectorFormat adata, bdata, cdata;
		a.ToUnifiedFormat(count, adata);
		b.ToUnifiedFormat(count, bdata);
		c.ToUnifiedFormat(count, cdata);

		return SelectLoopSwitch<A_TYPE, B_TYPE, C_TYPE, OP>(adata, bdata, cdata, sel, count, true_sel, false_sel);
	}
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/vector_operations/unary_executor.hpp
//
//
//===----------------------------------------------------------------------===//







#include <functional>

namespace duckdb {

struct UnaryOperatorWrapper {
	template <class OP, class INPUT_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(INPUT_TYPE input, ValidityMask &mask, idx_t idx, void *dataptr) {
		return OP::template Operation<INPUT_TYPE, RESULT_TYPE>(input);
	}
};

struct UnaryLambdaWrapper {
	template <class FUNC, class INPUT_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(INPUT_TYPE input, ValidityMask &mask, idx_t idx, void *dataptr) {
		auto fun = (FUNC *)dataptr;
		return (*fun)(input);
	}
};

struct GenericUnaryWrapper {
	template <class OP, class INPUT_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(INPUT_TYPE input, ValidityMask &mask, idx_t idx, void *dataptr) {
		return OP::template Operation<INPUT_TYPE, RESULT_TYPE>(input, mask, idx, dataptr);
	}
};

struct UnaryLambdaWrapperWithNulls {
	template <class FUNC, class INPUT_TYPE, class RESULT_TYPE>
	static inline RESULT_TYPE Operation(INPUT_TYPE input, ValidityMask &mask, idx_t idx, void *dataptr) {
		auto fun = (FUNC *)dataptr;
		return (*fun)(input, mask, idx);
	}
};

template <class OP>
struct UnaryStringOperator {
	template <class INPUT_TYPE, class RESULT_TYPE>
	static RESULT_TYPE Operation(INPUT_TYPE input, ValidityMask &mask, idx_t idx, void *dataptr) {
		auto vector = (Vector *)dataptr;
		return OP::template Operation<INPUT_TYPE, RESULT_TYPE>(input, *vector);
	}
};

struct UnaryExecutor {
private:
	template <class INPUT_TYPE, class RESULT_TYPE, class OPWRAPPER, class OP>
	static inline void ExecuteLoop(INPUT_TYPE *__restrict ldata, RESULT_TYPE *__restrict result_data, idx_t count,
	                               const SelectionVector *__restrict sel_vector, ValidityMask &mask,
	                               ValidityMask &result_mask, void *dataptr, bool adds_nulls) {
#ifdef DEBUG
		// ldata may point to a compressed dictionary buffer which can be smaller than ldata + count
		idx_t max_index = 0;
		for (idx_t i = 0; i < count; i++) {
			auto idx = sel_vector->get_index(i);
			max_index = MaxValue(max_index, idx);
		}
		ASSERT_RESTRICT(ldata, ldata + max_index, result_data, result_data + count);
#endif

		if (!mask.AllValid()) {
			result_mask.EnsureWritable();
			for (idx_t i = 0; i < count; i++) {
				auto idx = sel_vector->get_index(i);
				if (mask.RowIsValidUnsafe(idx)) {
					result_data[i] =
					    OPWRAPPER::template Operation<OP, INPUT_TYPE, RESULT_TYPE>(ldata[idx], result_mask, i, dataptr);
				} else {
					result_mask.SetInvalid(i);
				}
			}
		} else {
			if (adds_nulls) {
				result_mask.EnsureWritable();
			}
			for (idx_t i = 0; i < count; i++) {
				auto idx = sel_vector->get_index(i);
				result_data[i] =
				    OPWRAPPER::template Operation<OP, INPUT_TYPE, RESULT_TYPE>(ldata[idx], result_mask, i, dataptr);
			}
		}
	}

	template <class INPUT_TYPE, class RESULT_TYPE, class OPWRAPPER, class OP>
	static inline void ExecuteFlat(INPUT_TYPE *__restrict ldata, RESULT_TYPE *__restrict result_data, idx_t count,
	                               ValidityMask &mask, ValidityMask &result_mask, void *dataptr, bool adds_nulls) {
		ASSERT_RESTRICT(ldata, ldata + count, result_data, result_data + count);

		if (!mask.AllValid()) {
			if (!adds_nulls) {
				result_mask.Initialize(mask);
			} else {
				result_mask.Copy(mask, count);
			}
			idx_t base_idx = 0;
			auto entry_count = ValidityMask::EntryCount(count);
			for (idx_t entry_idx = 0; entry_idx < entry_count; entry_idx++) {
				auto validity_entry = mask.GetValidityEntry(entry_idx);
				idx_t next = MinValue<idx_t>(base_idx + ValidityMask::BITS_PER_VALUE, count);
				if (ValidityMask::AllValid(validity_entry)) {
					// all valid: perform operation
					for (; base_idx < next; base_idx++) {
						result_data[base_idx] = OPWRAPPER::template Operation<OP, INPUT_TYPE, RESULT_TYPE>(
						    ldata[base_idx], result_mask, base_idx, dataptr);
					}
				} else if (ValidityMask::NoneValid(validity_entry)) {
					// nothing valid: skip all
					base_idx = next;
					continue;
				} else {
					// partially valid: need to check individual elements for validity
					idx_t start = base_idx;
					for (; base_idx < next; base_idx++) {
						if (ValidityMask::RowIsValid(validity_entry, base_idx - start)) {
							D_ASSERT(mask.RowIsValid(base_idx));
							result_data[base_idx] = OPWRAPPER::template Operation<OP, INPUT_TYPE, RESULT_TYPE>(
							    ldata[base_idx], result_mask, base_idx, dataptr);
						}
					}
				}
			}
		} else {
			if (adds_nulls) {
				result_mask.EnsureWritable();
			}
			for (idx_t i = 0; i < count; i++) {
				result_data[i] =
				    OPWRAPPER::template Operation<OP, INPUT_TYPE, RESULT_TYPE>(ldata[i], result_mask, i, dataptr);
			}
		}
	}

	template <class INPUT_TYPE, class RESULT_TYPE, class OPWRAPPER, class OP>
	static inline void ExecuteStandard(Vector &input, Vector &result, idx_t count, void *dataptr, bool adds_nulls) {
		switch (input.GetVectorType()) {
		case VectorType::CONSTANT_VECTOR: {
			result.SetVectorType(VectorType::CONSTANT_VECTOR);
			auto result_data = ConstantVector::GetData<RESULT_TYPE>(result);
			auto ldata = ConstantVector::GetData<INPUT_TYPE>(input);

			if (ConstantVector::IsNull(input)) {
				ConstantVector::SetNull(result, true);
			} else {
				ConstantVector::SetNull(result, false);
				*result_data = OPWRAPPER::template Operation<OP, INPUT_TYPE, RESULT_TYPE>(
				    *ldata, ConstantVector::Validity(result), 0, dataptr);
			}
			break;
		}
		case VectorType::FLAT_VECTOR: {
			result.SetVectorType(VectorType::FLAT_VECTOR);
			auto result_data = FlatVector::GetData<RESULT_TYPE>(result);
			auto ldata = FlatVector::GetData<INPUT_TYPE>(input);

			ExecuteFlat<INPUT_TYPE, RESULT_TYPE, OPWRAPPER, OP>(ldata, result_data, count, FlatVector::Validity(input),
			                                                    FlatVector::Validity(result), dataptr, adds_nulls);
			break;
		}
		default: {
			UnifiedVectorFormat vdata;
			input.ToUnifiedFormat(count, vdata);

			result.SetVectorType(VectorType::FLAT_VECTOR);
			auto result_data = FlatVector::GetData<RESULT_TYPE>(result);
			auto ldata = (INPUT_TYPE *)vdata.data;

			ExecuteLoop<INPUT_TYPE, RESULT_TYPE, OPWRAPPER, OP>(ldata, result_data, count, vdata.sel, vdata.validity,
			                                                    FlatVector::Validity(result), dataptr, adds_nulls);
			break;
		}
		}
	}

public:
	template <class INPUT_TYPE, class RESULT_TYPE, class OP>
	static void Execute(Vector &input, Vector &result, idx_t count) {
		ExecuteStandard<INPUT_TYPE, RESULT_TYPE, UnaryOperatorWrapper, OP>(input, result, count, nullptr, false);
	}

	template <class INPUT_TYPE, class RESULT_TYPE, class FUNC = std::function<RESULT_TYPE(INPUT_TYPE)>>
	static void Execute(Vector &input, Vector &result, idx_t count, FUNC fun) {
		ExecuteStandard<INPUT_TYPE, RESULT_TYPE, UnaryLambdaWrapper, FUNC>(input, result, count, (void *)&fun, false);
	}

	template <class INPUT_TYPE, class RESULT_TYPE, class OP>
	static void GenericExecute(Vector &input, Vector &result, idx_t count, void *dataptr, bool adds_nulls = false) {
		ExecuteStandard<INPUT_TYPE, RESULT_TYPE, GenericUnaryWrapper, OP>(input, result, count, dataptr, adds_nulls);
	}

	template <class INPUT_TYPE, class RESULT_TYPE,
	          class FUNC = std::function<RESULT_TYPE(INPUT_TYPE, ValidityMask &, idx_t)>>
	static void ExecuteWithNulls(Vector &input, Vector &result, idx_t count, FUNC fun) {
		ExecuteStandard<INPUT_TYPE, RESULT_TYPE, UnaryLambdaWrapperWithNulls, FUNC>(input, result, count, (void *)&fun,
		                                                                            true);
	}

	template <class INPUT_TYPE, class RESULT_TYPE, class OP>
	static void ExecuteString(Vector &input, Vector &result, idx_t count) {
		UnaryExecutor::GenericExecute<string_t, string_t, UnaryStringOperator<OP>>(input, result, count,
		                                                                           (void *)&result);
	}
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/expression_executor_state.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/cycle_counter.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/chrono.hpp
//
//
//===----------------------------------------------------------------------===//



#include <chrono>

namespace duckdb {
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::system_clock;
using std::chrono::time_point;
} // namespace duckdb


namespace duckdb {

//! The cycle counter can be used to measure elapsed cycles for a function, expression and ...
//! Optimized by sampling mechanism. Once per 100 times.
//! //Todo Can be optimized further by calling RDTSC once per sample
class CycleCounter {
	friend struct ExpressionInfo;
	friend struct ExpressionRootInfo;
	static constexpr int SAMPLING_RATE = 50;

public:
	CycleCounter() {
	}
	// Next_sample determines if a sample needs to be taken, if so start the profiler
	void BeginSample() {
		if (current_count >= next_sample) {
			tmp = Tick();
		}
	}

	// End the sample
	void EndSample(int chunk_size) {
		if (current_count >= next_sample) {
			time += Tick() - tmp;
		}
		if (current_count >= next_sample) {
			next_sample = SAMPLING_RATE;
			++sample_count;
			sample_tuples_count += chunk_size;
			current_count = 0;
		} else {
			++current_count;
		}
		tuples_count += chunk_size;
	}

private:
	uint64_t Tick() const;
	// current number on RDT register
	uint64_t tmp;
	// Elapsed cycles
	uint64_t time = 0;
	//! Count the number of time the executor called since last sampling
	uint64_t current_count = 0;
	//! Show the next sample
	uint64_t next_sample = 0;
	//! Count the number of samples
	uint64_t sample_count = 0;
	//! Count the number of tuples sampled
	uint64_t sample_tuples_count = 0;
	//! Count the number of ALL tuples
	uint64_t tuples_count = 0;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/function.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/named_parameter_map.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/case_insensitive_map.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/unordered_set.hpp
//
//
//===----------------------------------------------------------------------===//



#include <unordered_set>

namespace duckdb {
using std::unordered_set;
}


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/string_util.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {
/**
 * String Utility Functions
 * Note that these are not the most efficient implementations (i.e., they copy
 * memory) and therefore they should only be used for debug messages and other
 * such things.
 */
class StringUtil {
public:
	DUCKDB_API static bool CharacterIsSpace(char c) {
		return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
	}
	DUCKDB_API static bool CharacterIsNewline(char c) {
		return c == '\n' || c == '\r';
	}
	DUCKDB_API static bool CharacterIsDigit(char c) {
		return c >= '0' && c <= '9';
	}
	DUCKDB_API static char CharacterToLower(char c) {
		if (c >= 'A' && c <= 'Z') {
			return c - ('A' - 'a');
		}
		return c;
	}
	DUCKDB_API static char CharacterIsAlpha(char c) {
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}

	//! Returns true if the needle string exists in the haystack
	DUCKDB_API static bool Contains(const string &haystack, const string &needle);

	//! Returns true if the target string starts with the given prefix
	DUCKDB_API static bool StartsWith(string str, string prefix);

	//! Returns true if the target string <b>ends</b> with the given suffix.
	DUCKDB_API static bool EndsWith(const string &str, const string &suffix);

	//! Repeat a string multiple times
	DUCKDB_API static string Repeat(const string &str, const idx_t n);

	//! Split the input string based on newline char
	DUCKDB_API static vector<string> Split(const string &str, char delimiter);

	//! Split the input string allong a quote. Note that any escaping is NOT supported.
	DUCKDB_API static vector<string> SplitWithQuote(const string &str, char delimiter = ',', char quote = '"');

	//! Join multiple strings into one string. Components are concatenated by the given separator
	DUCKDB_API static string Join(const vector<string> &input, const string &separator);

	template <class T>
	static string ToString(const vector<T> &input, const string &separator) {
		vector<string> input_list;
		for (auto &i : input) {
			input_list.push_back(i.ToString());
		}
		return StringUtil::Join(input_list, separator);
	}

	//! Join multiple items of container with given size, transformed to string
	//! using function, into one string using the given separator
	template <typename C, typename S, typename Func>
	static string Join(const C &input, S count, const string &separator, Func f) {
		// The result
		std::string result;

		// If the input isn't empty, append the first element. We do this so we
		// don't need to introduce an if into the loop.
		if (count > 0) {
			result += f(input[0]);
		}

		// Append the remaining input components, after the first
		for (size_t i = 1; i < count; i++) {
			result += separator + f(input[i]);
		}

		return result;
	}

	//! Return a string that formats the give number of bytes
	DUCKDB_API static string BytesToHumanReadableString(idx_t bytes);

	//! Convert a string to uppercase
	DUCKDB_API static string Upper(const string &str);

	//! Convert a string to lowercase
	DUCKDB_API static string Lower(const string &str);

	//! Format a string using printf semantics
	template <typename... Args>
	static string Format(const string fmt_str, Args... params) {
		return Exception::ConstructMessage(fmt_str, params...);
	}

	//! Split the input string into a vector of strings based on the split string
	DUCKDB_API static vector<string> Split(const string &input, const string &split);

	//! Remove the whitespace char in the left end of the string
	DUCKDB_API static void LTrim(string &str);
	//! Remove the whitespace char in the right end of the string
	DUCKDB_API static void RTrim(string &str);
	//! Remove the whitespace char in the left and right end of the string
	DUCKDB_API static void Trim(string &str);

	DUCKDB_API static string Replace(string source, const string &from, const string &to);

	//! Get the levenshtein distance from two strings
	DUCKDB_API static idx_t LevenshteinDistance(const string &s1, const string &s2);

	//! Get the top-n strings (sorted by the given score distance) from a set of scores.
	//! At least one entry is returned (if there is one).
	//! Strings are only returned if they have a score less than the threshold.
	DUCKDB_API static vector<string> TopNStrings(vector<std::pair<string, idx_t>> scores, idx_t n = 5,
	                                             idx_t threshold = 5);
	//! Computes the levenshtein distance of each string in strings, and compares it to target, then returns TopNStrings
	//! with the given params.
	DUCKDB_API static vector<string> TopNLevenshtein(const vector<string> &strings, const string &target, idx_t n = 5,
	                                                 idx_t threshold = 5);
	DUCKDB_API static string CandidatesMessage(const vector<string> &candidates,
	                                           const string &candidate = "Candidate bindings");

	//! Generate an error message in the form of "{message_prefix}: nearest_string, nearest_string2, ...
	//! Equivalent to calling TopNLevenshtein followed by CandidatesMessage
	DUCKDB_API static string CandidatesErrorMessage(const vector<string> &strings, const string &target,
	                                                const string &message_prefix, idx_t n = 5);
};

} // namespace duckdb


namespace duckdb {

struct CaseInsensitiveStringHashFunction {
	uint64_t operator()(const string &str) const {
		std::hash<string> hasher;
		return hasher(StringUtil::Lower(str));
	}
};

struct CaseInsensitiveStringEquality {
	bool operator()(const string &a, const string &b) const {
		return StringUtil::Lower(a) == StringUtil::Lower(b);
	}
};

template <typename T>
using case_insensitive_map_t =
    unordered_map<string, T, CaseInsensitiveStringHashFunction, CaseInsensitiveStringEquality>;

using case_insensitive_set_t = unordered_set<string, CaseInsensitiveStringHashFunction, CaseInsensitiveStringEquality>;

} // namespace duckdb


namespace duckdb {

using named_parameter_type_map_t = case_insensitive_map_t<LogicalType>;
using named_parameter_map_t = case_insensitive_map_t<Value>;

} // namespace duckdb



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/external_dependencies.hpp
//
//
//===----------------------------------------------------------------------===//



namespace duckdb {

enum ExternalDependenciesType { PYTHON_DEPENDENCY };
class ExternalDependency {
public:
	explicit ExternalDependency(ExternalDependenciesType type_p) : type(type_p) {};
	virtual ~ExternalDependency() {};
	ExternalDependenciesType type;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/column_definition.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_expression.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/base_expression.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/expression_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//===--------------------------------------------------------------------===//
// Predicate Expression Operation Types
//===--------------------------------------------------------------------===//
enum class ExpressionType : uint8_t {
	INVALID = 0,

	// explicitly cast left as right (right is integer in ValueType enum)
	OPERATOR_CAST = 12,
	// logical not operator
	OPERATOR_NOT = 13,
	// is null operator
	OPERATOR_IS_NULL = 14,
	// is not null operator
	OPERATOR_IS_NOT_NULL = 15,

	// -----------------------------
	// Comparison Operators
	// -----------------------------
	// equal operator between left and right
	COMPARE_EQUAL = 25,
	// compare initial boundary
	COMPARE_BOUNDARY_START = COMPARE_EQUAL,
	// inequal operator between left and right
	COMPARE_NOTEQUAL = 26,
	// less than operator between left and right
	COMPARE_LESSTHAN = 27,
	// greater than operator between left and right
	COMPARE_GREATERTHAN = 28,
	// less than equal operator between left and right
	COMPARE_LESSTHANOREQUALTO = 29,
	// greater than equal operator between left and right
	COMPARE_GREATERTHANOREQUALTO = 30,
	// IN operator [left IN (right1, right2, ...)]
	COMPARE_IN = 35,
	// NOT IN operator [left NOT IN (right1, right2, ...)]
	COMPARE_NOT_IN = 36,
	// IS DISTINCT FROM operator
	COMPARE_DISTINCT_FROM = 37,

	COMPARE_BETWEEN = 38,
	COMPARE_NOT_BETWEEN = 39,
	// IS NOT DISTINCT FROM operator
	COMPARE_NOT_DISTINCT_FROM = 40,
	// compare final boundary
	COMPARE_BOUNDARY_END = COMPARE_NOT_DISTINCT_FROM,

	// -----------------------------
	// Conjunction Operators
	// -----------------------------
	CONJUNCTION_AND = 50,
	CONJUNCTION_OR = 51,

	// -----------------------------
	// Values
	// -----------------------------
	VALUE_CONSTANT = 75,
	VALUE_PARAMETER = 76,
	VALUE_TUPLE = 77,
	VALUE_TUPLE_ADDRESS = 78,
	VALUE_NULL = 79,
	VALUE_VECTOR = 80,
	VALUE_SCALAR = 81,
	VALUE_DEFAULT = 82,

	// -----------------------------
	// Aggregates
	// -----------------------------
	AGGREGATE = 100,
	BOUND_AGGREGATE = 101,
	GROUPING_FUNCTION = 102,

	// -----------------------------
	// Window Functions
	// -----------------------------
	WINDOW_AGGREGATE = 110,

	WINDOW_RANK = 120,
	WINDOW_RANK_DENSE = 121,
	WINDOW_NTILE = 122,
	WINDOW_PERCENT_RANK = 123,
	WINDOW_CUME_DIST = 124,
	WINDOW_ROW_NUMBER = 125,

	WINDOW_FIRST_VALUE = 130,
	WINDOW_LAST_VALUE = 131,
	WINDOW_LEAD = 132,
	WINDOW_LAG = 133,
	WINDOW_NTH_VALUE = 134,

	// -----------------------------
	// Functions
	// -----------------------------
	FUNCTION = 140,
	BOUND_FUNCTION = 141,

	// -----------------------------
	// Operators
	// -----------------------------
	CASE_EXPR = 150,
	OPERATOR_NULLIF = 151,
	OPERATOR_COALESCE = 152,
	ARRAY_EXTRACT = 153,
	ARRAY_SLICE = 154,
	STRUCT_EXTRACT = 155,
	ARRAY_CONSTRUCTOR = 156,
	ARROW = 157,

	// -----------------------------
	// Subquery IN/EXISTS
	// -----------------------------
	SUBQUERY = 175,

	// -----------------------------
	// Parser
	// -----------------------------
	STAR = 200,
	TABLE_STAR = 201,
	PLACEHOLDER = 202,
	COLUMN_REF = 203,
	FUNCTION_REF = 204,
	TABLE_REF = 205,

	// -----------------------------
	// Miscellaneous
	// -----------------------------
	CAST = 225,
	BOUND_REF = 227,
	BOUND_COLUMN_REF = 228,
	BOUND_UNNEST = 229,
	COLLATE = 230,
	LAMBDA = 231,
	POSITIONAL_REFERENCE = 232
};

//===--------------------------------------------------------------------===//
// Expression Class
//===--------------------------------------------------------------------===//
enum class ExpressionClass : uint8_t {
	INVALID = 0,
	//===--------------------------------------------------------------------===//
	// Parsed Expressions
	//===--------------------------------------------------------------------===//
	AGGREGATE = 1,
	CASE = 2,
	CAST = 3,
	COLUMN_REF = 4,
	COMPARISON = 5,
	CONJUNCTION = 6,
	CONSTANT = 7,
	DEFAULT = 8,
	FUNCTION = 9,
	OPERATOR = 10,
	STAR = 11,
	SUBQUERY = 13,
	WINDOW = 14,
	PARAMETER = 15,
	COLLATE = 16,
	LAMBDA = 17,
	POSITIONAL_REFERENCE = 18,
	BETWEEN = 19,
	//===--------------------------------------------------------------------===//
	// Bound Expressions
	//===--------------------------------------------------------------------===//
	BOUND_AGGREGATE = 25,
	BOUND_CASE = 26,
	BOUND_CAST = 27,
	BOUND_COLUMN_REF = 28,
	BOUND_COMPARISON = 29,
	BOUND_CONJUNCTION = 30,
	BOUND_CONSTANT = 31,
	BOUND_DEFAULT = 32,
	BOUND_FUNCTION = 33,
	BOUND_OPERATOR = 34,
	BOUND_PARAMETER = 35,
	BOUND_REF = 36,
	BOUND_SUBQUERY = 37,
	BOUND_WINDOW = 38,
	BOUND_BETWEEN = 39,
	BOUND_UNNEST = 40,
	BOUND_LAMBDA = 41,
	//===--------------------------------------------------------------------===//
	// Miscellaneous
	//===--------------------------------------------------------------------===//
	BOUND_EXPRESSION = 50
};

DUCKDB_API string ExpressionTypeToString(ExpressionType type);
string ExpressionTypeToOperator(ExpressionType type);

// Operator String to ExpressionType (e.g. + => OPERATOR_ADD)
ExpressionType OperatorToExpressionType(const string &op);

//! Negate a comparison expression, turning e.g. = into !=, or < into >=
ExpressionType NegateComparisionExpression(ExpressionType type);
//! Flip a comparison expression, turning e.g. < into >, or = into =
ExpressionType FlipComparisionExpression(ExpressionType type);

DUCKDB_API string ExpressionClassToString(ExpressionClass type);

} // namespace duckdb


namespace duckdb {

//!  The BaseExpression class is a base class that can represent any expression
//!  part of a SQL statement.
class BaseExpression {
public:
	//! Create an Expression
	BaseExpression(ExpressionType type, ExpressionClass expression_class)
	    : type(type), expression_class(expression_class) {
	}
	virtual ~BaseExpression() {
	}

	//! Returns the type of the expression
	ExpressionType GetExpressionType() const {
		return type;
	}
	//! Returns the class of the expression
	ExpressionClass GetExpressionClass() const {
		return expression_class;
	}

	//! Type of the expression
	ExpressionType type;
	//! The expression class of the node
	ExpressionClass expression_class;
	//! The alias of the expression,
	string alias;

public:
	//! Returns true if this expression is an aggregate or not.
	/*!
	 Examples:

	 (1) SUM(a) + 1 -- True

	 (2) a + 1 -- False
	 */
	virtual bool IsAggregate() const = 0;
	//! Returns true if the expression has a window function or not
	virtual bool IsWindow() const = 0;
	//! Returns true if the query contains a subquery
	virtual bool HasSubquery() const = 0;
	//! Returns true if expression does not contain a group ref or col ref or parameter
	virtual bool IsScalar() const = 0;
	//! Returns true if the expression has a parameter
	virtual bool HasParameter() const = 0;

	//! Get the name of the expression
	virtual string GetName() const;
	//! Convert the Expression to a String
	virtual string ToString() const = 0;
	//! Print the expression to stdout
	void Print() const;

	//! Creates a hash value of this expression. It is important that if two expressions are identical (i.e.
	//! Expression::Equals() returns true), that their hash value is identical as well.
	virtual hash_t Hash() const = 0;
	//! Returns true if this expression is equal to another expression
	virtual bool Equals(const BaseExpression *other) const;

	static bool Equals(BaseExpression *left, BaseExpression *right) {
		if (left == right) {
			return true;
		}
		if (!left || !right) {
			return false;
		}
		return left->Equals(right);
	}
	bool operator==(const BaseExpression &rhs) {
		return this->Equals(&rhs);
	}

	virtual void Verify() const;
};

} // namespace duckdb



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/qualified_name.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/keyword_helper.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

class KeywordHelper {
public:
	//! Returns true if the given text matches a keyword of the parser
	static bool IsKeyword(const string &text);

	//! Returns true if the given string needs to be quoted when written as an identifier
	static bool RequiresQuotes(const string &text);

	//! Writes a string that is optionally quoted + escaped so it can be used as an identifier
	static string WriteOptionallyQuoted(const string &text, char quote = '"');
};

} // namespace duckdb



namespace duckdb {

struct QualifiedName {
	string schema;
	string name;

	//! Parse the (optional) schema and a name from a string in the format of e.g. "schema"."table"; if there is no dot
	//! the schema will be set to INVALID_SCHEMA
	static QualifiedName Parse(const string &input) {
		string schema;
		string name;
		idx_t idx = 0;
		vector<string> entries;
		string entry;
	normal:
		//! quote
		for (; idx < input.size(); idx++) {
			if (input[idx] == '"') {
				idx++;
				goto quoted;
			} else if (input[idx] == '.') {
				goto separator;
			}
			entry += input[idx];
		}
		goto end;
	separator:
		entries.push_back(entry);
		entry = "";
		idx++;
		goto normal;
	quoted:
		//! look for another quote
		for (; idx < input.size(); idx++) {
			if (input[idx] == '"') {
				//! unquote
				idx++;
				goto normal;
			}
			entry += input[idx];
		}
		throw ParserException("Unterminated quote in qualified name!");
	end:
		if (entries.empty()) {
			schema = INVALID_SCHEMA;
			name = entry;
		} else if (entries.size() == 1) {
			schema = entries[0];
			name = entry;
		} else {
			throw ParserException("Expected schema.entry or entry: too many entries found");
		}
		return QualifiedName {schema, name};
	}
};

struct QualifiedColumnName {
	QualifiedColumnName() {
	}
	QualifiedColumnName(string table_p, string column_p) : table(move(table_p)), column(move(column_p)) {
	}

	string schema;
	string table;
	string column;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/expression_util.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {
class ParsedExpression;
class Expression;

class ExpressionUtil {
public:
	//! ListEquals: check if a list of two expressions is equal (order is important)
	static bool ListEquals(const vector<unique_ptr<ParsedExpression>> &a,
	                       const vector<unique_ptr<ParsedExpression>> &b);
	static bool ListEquals(const vector<unique_ptr<Expression>> &a, const vector<unique_ptr<Expression>> &b);
	//! SetEquals: check if two sets of expressions are equal (order is not important)
	static bool SetEquals(const vector<unique_ptr<ParsedExpression>> &a, const vector<unique_ptr<ParsedExpression>> &b);
	static bool SetEquals(const vector<unique_ptr<Expression>> &a, const vector<unique_ptr<Expression>> &b);

private:
	template <class T>
	static bool ExpressionListEquals(const vector<unique_ptr<T>> &a, const vector<unique_ptr<T>> &b);
	template <class T>
	static bool ExpressionSetEquals(const vector<unique_ptr<T>> &a, const vector<unique_ptr<T>> &b);
};

} // namespace duckdb


namespace duckdb {
class Serializer;
class Deserializer;
class FieldWriter;
class FieldReader;

//!  The ParsedExpression class is a base class that can represent any expression
//!  part of a SQL statement.
/*!
 The ParsedExpression class is a base class that can represent any expression
 part of a SQL statement. This is, for example, a column reference in a SELECT
 clause, but also operators, aggregates or filters. The Expression is emitted by the parser and does not contain any
 information about bindings to the catalog or to the types. ParsedExpressions are transformed into regular Expressions
 in the Binder.
 */
class ParsedExpression : public BaseExpression {
public:
	//! Create an Expression
	ParsedExpression(ExpressionType type, ExpressionClass expression_class) : BaseExpression(type, expression_class) {
	}

	//! The location in the query (if any)
	idx_t query_location = DConstants::INVALID_INDEX;

public:
	bool IsAggregate() const override;
	bool IsWindow() const override;
	bool HasSubquery() const override;
	bool IsScalar() const override;
	bool HasParameter() const override;

	bool Equals(const BaseExpression *other) const override;
	hash_t Hash() const override;

	//! Create a copy of this expression
	virtual unique_ptr<ParsedExpression> Copy() const = 0;

	//! Serializes an Expression to a stand-alone binary blob
	void Serialize(Serializer &serializer) const;
	//! Serializes an Expression to a stand-alone binary blob
	virtual void Serialize(FieldWriter &writer) const = 0;

	//! Deserializes a blob back into an Expression [CAN THROW:
	//! SerializationException]
	static unique_ptr<ParsedExpression> Deserialize(Deserializer &source);

protected:
	//! Copy base Expression properties from another expression to this one,
	//! used in Copy method
	void CopyProperties(const ParsedExpression &other) {
		type = other.type;
		expression_class = other.expression_class;
		alias = other.alias;
	}
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/compression_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class CompressionType : uint8_t {
	COMPRESSION_AUTO = 0,
	COMPRESSION_UNCOMPRESSED = 1,
	COMPRESSION_CONSTANT = 2,
	COMPRESSION_RLE = 3,
	COMPRESSION_DICTIONARY = 4,
	COMPRESSION_PFOR_DELTA = 5,
	COMPRESSION_BITPACKING = 6,
	COMPRESSION_FSST = 7
};

CompressionType CompressionTypeFromString(const string &str);
string CompressionTypeToString(CompressionType type);

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_entry/table_column_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class TableColumnType : uint8_t { STANDARD = 0, GENERATED = 1 };

} // namespace duckdb



namespace duckdb {

struct RenameColumnInfo;
struct RenameTableInfo;

class ColumnDefinition;

//! A column of a table.
class ColumnDefinition {
public:
	DUCKDB_API ColumnDefinition(string name, LogicalType type);
	DUCKDB_API ColumnDefinition(string name, LogicalType type, unique_ptr<ParsedExpression> expression,
	                            TableColumnType category);

	//! The default value of the column (if any)
	unique_ptr<ParsedExpression> default_value;

public:
	//! default_value
	const unique_ptr<ParsedExpression> &DefaultValue() const;
	void SetDefaultValue(unique_ptr<ParsedExpression> default_value);

	//! type
	DUCKDB_API const LogicalType &Type() const;
	LogicalType &TypeMutable();
	void SetType(const LogicalType &type);

	//! name
	DUCKDB_API const string &Name() const;
	void SetName(const string &name);

	//! compression_type
	const duckdb::CompressionType &CompressionType() const;
	void SetCompressionType(duckdb::CompressionType compression_type);

	//! storage_oid
	const storage_t &StorageOid() const;
	void SetStorageOid(storage_t storage_oid);

	//! oid
	const column_t &Oid() const;
	void SetOid(column_t oid);

	//! category
	const TableColumnType &Category() const;
	//! Whether this column is a Generated Column
	bool Generated() const;
	DUCKDB_API ColumnDefinition Copy() const;

	DUCKDB_API void Serialize(Serializer &serializer) const;
	DUCKDB_API static ColumnDefinition Deserialize(Deserializer &source);

	//===--------------------------------------------------------------------===//
	// Generated Columns (VIRTUAL)
	//===--------------------------------------------------------------------===//

	ParsedExpression &GeneratedExpressionMutable();
	const ParsedExpression &GeneratedExpression() const;
	void SetGeneratedExpression(unique_ptr<ParsedExpression> expression);
	void ChangeGeneratedExpressionType(const LogicalType &type);
	void GetListOfDependencies(vector<string> &dependencies) const;

	string GetName();

	LogicalType GetType();

private:
	//! The name of the entry
	string name;
	//! The type of the column
	LogicalType type;
	//! Compression Type used for this column
	duckdb::CompressionType compression_type = duckdb::CompressionType::COMPRESSION_AUTO;
	//! The index of the column in the storage of the table
	storage_t storage_oid;
	//! The index of the column in the table
	idx_t oid;
	//! The category of the column
	TableColumnType category = TableColumnType::STANDARD;
	//! Used by Generated Columns
	unique_ptr<ParsedExpression> generated_expression;
};

} // namespace duckdb


namespace duckdb {
class CatalogEntry;
class Catalog;
class ClientContext;
class Expression;
class ExpressionExecutor;
class Transaction;

class AggregateFunction;
class AggregateFunctionSet;
class CopyFunction;
class PragmaFunction;
class PragmaFunctionSet;
class ScalarFunctionSet;
class ScalarFunction;
class TableFunctionSet;
class TableFunction;
class SimpleFunction;

struct PragmaInfo;

//! The default null handling is NULL in, NULL out
enum class FunctionNullHandling : uint8_t { DEFAULT_NULL_HANDLING = 0, SPECIAL_HANDLING = 1 };
enum class FunctionSideEffects : uint8_t { NO_SIDE_EFFECTS = 0, HAS_SIDE_EFFECTS = 1 };

struct FunctionData {
	DUCKDB_API virtual ~FunctionData();

	DUCKDB_API virtual unique_ptr<FunctionData> Copy() const = 0;
	DUCKDB_API virtual bool Equals(const FunctionData &other) const = 0;
	DUCKDB_API static bool Equals(const FunctionData *left, const FunctionData *right);
};

struct TableFunctionData : public FunctionData {
	// used to pass on projections to table functions that support them. NB, can contain COLUMN_IDENTIFIER_ROW_ID
	vector<idx_t> column_ids;

	DUCKDB_API virtual ~TableFunctionData();

	DUCKDB_API unique_ptr<FunctionData> Copy() const override;
	DUCKDB_API bool Equals(const FunctionData &other) const override;
};

struct PyTableFunctionData : public TableFunctionData {
	//! External dependencies of this table function
	unique_ptr<ExternalDependency> external_dependency;
};

struct FunctionParameters {
	vector<Value> values;
	named_parameter_map_t named_parameters;
};

//! Function is the base class used for any type of function (scalar, aggregate or simple function)
class Function {
public:
	DUCKDB_API explicit Function(string name);
	DUCKDB_API virtual ~Function();

	//! The name of the function
	string name;

public:
	//! Returns the formatted string name(arg1, arg2, ...)
	DUCKDB_API static string CallToString(const string &name, const vector<LogicalType> &arguments);
	//! Returns the formatted string name(arg1, arg2..) -> return_type
	DUCKDB_API static string CallToString(const string &name, const vector<LogicalType> &arguments,
	                                      const LogicalType &return_type);
	//! Returns the formatted string name(arg1, arg2.., np1=a, np2=b, ...)
	DUCKDB_API static string CallToString(const string &name, const vector<LogicalType> &arguments,
	                                      const named_parameter_type_map_t &named_parameters);

	//! Bind a scalar function from the set of functions and input arguments. Returns the index of the chosen function,
	//! returns DConstants::INVALID_INDEX and sets error if none could be found
	DUCKDB_API static idx_t BindFunction(const string &name, ScalarFunctionSet &functions,
	                                     const vector<LogicalType> &arguments, string &error);
	DUCKDB_API static idx_t BindFunction(const string &name, ScalarFunctionSet &functions,
	                                     vector<unique_ptr<Expression>> &arguments, string &error);
	//! Bind an aggregate function from the set of functions and input arguments. Returns the index of the chosen
	//! function, returns DConstants::INVALID_INDEX and sets error if none could be found
	DUCKDB_API static idx_t BindFunction(const string &name, AggregateFunctionSet &functions,
	                                     const vector<LogicalType> &arguments, string &error);
	DUCKDB_API static idx_t BindFunction(const string &name, AggregateFunctionSet &functions,
	                                     vector<unique_ptr<Expression>> &arguments, string &error);
	//! Bind a table function from the set of functions and input arguments. Returns the index of the chosen
	//! function, returns DConstants::INVALID_INDEX and sets error if none could be found
	DUCKDB_API static idx_t BindFunction(const string &name, TableFunctionSet &functions,
	                                     const vector<LogicalType> &arguments, string &error);
	DUCKDB_API static idx_t BindFunction(const string &name, TableFunctionSet &functions,
	                                     vector<unique_ptr<Expression>> &arguments, string &error);
	//! Bind a pragma function from the set of functions and input arguments
	DUCKDB_API static idx_t BindFunction(const string &name, PragmaFunctionSet &functions, PragmaInfo &info,
	                                     string &error);

	//! Used in the bind to erase an argument from a function
	DUCKDB_API static void EraseArgument(SimpleFunction &bound_function, vector<unique_ptr<Expression>> &arguments,
	                                     idx_t argument_index);
};

class SimpleFunction : public Function {
public:
	DUCKDB_API SimpleFunction(string name, vector<LogicalType> arguments,
	                          LogicalType varargs = LogicalType(LogicalTypeId::INVALID));
	DUCKDB_API ~SimpleFunction() override;

	//! The set of arguments of the function
	vector<LogicalType> arguments;
	//! The set of original arguments of the function - only set if Function::EraseArgument is called
	//! Used for (de)serialization purposes
	vector<LogicalType> original_arguments;
	//! The type of varargs to support, or LogicalTypeId::INVALID if the function does not accept variable length
	//! arguments
	LogicalType varargs;

public:
	DUCKDB_API virtual string ToString();

	DUCKDB_API bool HasVarArgs() const;
};

class SimpleNamedParameterFunction : public SimpleFunction {
public:
	DUCKDB_API SimpleNamedParameterFunction(string name, vector<LogicalType> arguments,
	                                        LogicalType varargs = LogicalType(LogicalTypeId::INVALID));
	DUCKDB_API ~SimpleNamedParameterFunction() override;

	//! The named parameters of the function
	named_parameter_type_map_t named_parameters;

public:
	DUCKDB_API string ToString() override;
	DUCKDB_API bool HasNamedParameters();
};

class BaseScalarFunction : public SimpleFunction {
public:
	DUCKDB_API BaseScalarFunction(string name, vector<LogicalType> arguments, LogicalType return_type,
	                              FunctionSideEffects side_effects,
	                              LogicalType varargs = LogicalType(LogicalTypeId::INVALID),
	                              FunctionNullHandling null_handling = FunctionNullHandling::DEFAULT_NULL_HANDLING);
	DUCKDB_API ~BaseScalarFunction() override;

	//! Return type of the function
	LogicalType return_type;
	//! Whether or not the function has side effects (e.g. sequence increments, random() functions, NOW()). Functions
	//! with side-effects cannot be constant-folded.
	FunctionSideEffects side_effects;
	//! How this function handles NULL values
	FunctionNullHandling null_handling;

public:
	DUCKDB_API hash_t Hash() const;

	//! Cast a set of expressions to the arguments of this function
	DUCKDB_API void CastToFunctionArguments(vector<unique_ptr<Expression>> &children);

	DUCKDB_API string ToString() override;
};

class BuiltinFunctions {
public:
	BuiltinFunctions(ClientContext &transaction, Catalog &catalog);

	//! Initialize a catalog with all built-in functions
	void Initialize();

public:
	void AddFunction(AggregateFunctionSet set);
	void AddFunction(AggregateFunction function);
	void AddFunction(ScalarFunctionSet set);
	void AddFunction(PragmaFunction function);
	void AddFunction(const string &name, PragmaFunctionSet functions);
	void AddFunction(ScalarFunction function);
	void AddFunction(const vector<string> &names, ScalarFunction function);
	void AddFunction(TableFunctionSet set);
	void AddFunction(TableFunction function);
	void AddFunction(CopyFunction function);

	void AddCollation(string name, ScalarFunction function, bool combinable = false,
	                  bool not_required_for_equality = false);

private:
	ClientContext &context;
	Catalog &catalog;

private:
	template <class T>
	void Register() {
		T::RegisterFunction(*this);
	}

	// table-producing functions
	void RegisterTableScanFunctions();
	void RegisterSQLiteFunctions();
	void RegisterReadFunctions();
	void RegisterTableFunctions();
	void RegisterArrowFunctions();

	// aggregates
	void RegisterAlgebraicAggregates();
	void RegisterDistributiveAggregates();
	void RegisterNestedAggregates();
	void RegisterHolisticAggregates();
	void RegisterRegressiveAggregates();

	// scalar functions
	void RegisterDateFunctions();
	void RegisterEnumFunctions();
	void RegisterGenericFunctions();
	void RegisterMathFunctions();
	void RegisterOperators();
	void RegisterStringFunctions();
	void RegisterNestedFunctions();
	void RegisterSequenceFunctions();
	void RegisterTrigonometricsFunctions();

	// pragmas
	void RegisterPragmaFunctions();
};

} // namespace duckdb


namespace duckdb {
class Expression;
class ExpressionExecutor;
struct ExpressionExecutorState;
struct FunctionLocalState;

struct ExpressionState {
	ExpressionState(const Expression &expr, ExpressionExecutorState &root);
	virtual ~ExpressionState() {
	}

	const Expression &expr;
	ExpressionExecutorState &root;
	vector<unique_ptr<ExpressionState>> child_states;
	vector<LogicalType> types;
	DataChunk intermediate_chunk;
	string name;
	CycleCounter profiler;

public:
	void AddChild(Expression *expr);
	void Finalize();
};

struct ExecuteFunctionState : public ExpressionState {
	ExecuteFunctionState(const Expression &expr, ExpressionExecutorState &root);
	~ExecuteFunctionState();

	unique_ptr<FunctionLocalState> local_state;

public:
	static FunctionLocalState *GetFunctionState(ExpressionState &state) {
		return ((ExecuteFunctionState &)state).local_state.get();
	}
};

struct ExpressionExecutorState {
	explicit ExpressionExecutorState(const string &name);
	unique_ptr<ExpressionState> root_state;
	ExpressionExecutor *executor;
	CycleCounter profiler;
	string name;
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/storage/statistics/base_statistics.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/operator/comparison_operators.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/hugeint.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/limits.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

template <class T>
struct NumericLimits {
	DUCKDB_API static T Minimum();
	DUCKDB_API static T Maximum();
	DUCKDB_API static bool IsSigned();
	DUCKDB_API static idx_t Digits();
};

template <>
struct NumericLimits<int8_t> {
	DUCKDB_API static int8_t Minimum();
	DUCKDB_API static int8_t Maximum();
	DUCKDB_API static bool IsSigned() {
		return true;
	}
	DUCKDB_API static idx_t Digits() {
		return 3;
	}
};
template <>
struct NumericLimits<int16_t> {
	DUCKDB_API static int16_t Minimum();
	DUCKDB_API static int16_t Maximum();
	DUCKDB_API static bool IsSigned() {
		return true;
	}
	DUCKDB_API static idx_t Digits() {
		return 5;
	}
};
template <>
struct NumericLimits<int32_t> {
	DUCKDB_API static int32_t Minimum();
	DUCKDB_API static int32_t Maximum();
	DUCKDB_API static bool IsSigned() {
		return true;
	}
	DUCKDB_API static idx_t Digits() {
		return 10;
	}
};
template <>
struct NumericLimits<int64_t> {
	DUCKDB_API static int64_t Minimum();
	DUCKDB_API static int64_t Maximum();
	DUCKDB_API static bool IsSigned() {
		return true;
	}
	DUCKDB_API static idx_t Digits() {
		return 19;
	}
};
template <>
struct NumericLimits<hugeint_t> {
	DUCKDB_API static hugeint_t Minimum();
	DUCKDB_API static hugeint_t Maximum();
	DUCKDB_API static bool IsSigned() {
		return true;
	}
	DUCKDB_API static idx_t Digits() {
		return 39;
	}
};
template <>
struct NumericLimits<uint8_t> {
	DUCKDB_API static uint8_t Minimum();
	DUCKDB_API static uint8_t Maximum();
	DUCKDB_API static bool IsSigned() {
		return false;
	}
	DUCKDB_API static idx_t Digits() {
		return 3;
	}
};
template <>
struct NumericLimits<uint16_t> {
	DUCKDB_API static uint16_t Minimum();
	DUCKDB_API static uint16_t Maximum();
	DUCKDB_API static bool IsSigned() {
		return false;
	}
	DUCKDB_API static idx_t Digits() {
		return 5;
	}
};
template <>
struct NumericLimits<uint32_t> {
	DUCKDB_API static uint32_t Minimum();
	DUCKDB_API static uint32_t Maximum();
	DUCKDB_API static bool IsSigned() {
		return false;
	}
	DUCKDB_API static idx_t Digits() {
		return 10;
	}
};
template <>
struct NumericLimits<uint64_t> {
	DUCKDB_API static uint64_t Minimum();
	DUCKDB_API static uint64_t Maximum();
	DUCKDB_API static bool IsSigned() {
		return false;
	}
	DUCKDB_API static idx_t Digits() {
		return 20;
	}
};
template <>
struct NumericLimits<float> {
	DUCKDB_API static float Minimum();
	DUCKDB_API static float Maximum();
	DUCKDB_API static bool IsSigned() {
		return true;
	}
	DUCKDB_API static idx_t Digits() {
		return 127;
	}
};
template <>
struct NumericLimits<double> {
	DUCKDB_API static double Minimum();
	DUCKDB_API static double Maximum();
	DUCKDB_API static bool IsSigned() {
		return true;
	}
	DUCKDB_API static idx_t Digits() {
		return 250;
	}
};

} // namespace duckdb



namespace duckdb {

//! The Hugeint class contains static operations for the INT128 type
class Hugeint {
public:
	//! Convert a hugeint object to a string
	static string ToString(hugeint_t input);

	template <class T>
	DUCKDB_API static bool TryCast(hugeint_t input, T &result);

	template <class T>
	static T Cast(hugeint_t input) {
		T value;
		TryCast(input, value);
		return value;
	}

	template <class T>
	static bool TryConvert(T value, hugeint_t &result);

	template <class T>
	static hugeint_t Convert(T value) {
		hugeint_t result;
		if (!TryConvert(value, result)) { // LCOV_EXCL_START
			throw ValueOutOfRangeException(double(value), GetTypeId<T>(), GetTypeId<hugeint_t>());
		} // LCOV_EXCL_STOP
		return result;
	}

	static void NegateInPlace(hugeint_t &input) {
		if (input.upper == NumericLimits<int64_t>::Minimum() && input.lower == 0) {
			throw OutOfRangeException("HUGEINT is out of range");
		}
		input.lower = NumericLimits<uint64_t>::Maximum() - input.lower + 1;
		input.upper = -1 - input.upper + (input.lower == 0);
	}
	static hugeint_t Negate(hugeint_t input) {
		NegateInPlace(input);
		return input;
	}

	static bool TryMultiply(hugeint_t lhs, hugeint_t rhs, hugeint_t &result);

	static hugeint_t Add(hugeint_t lhs, hugeint_t rhs);
	static hugeint_t Subtract(hugeint_t lhs, hugeint_t rhs);
	static hugeint_t Multiply(hugeint_t lhs, hugeint_t rhs);
	static hugeint_t Divide(hugeint_t lhs, hugeint_t rhs);
	static hugeint_t Modulo(hugeint_t lhs, hugeint_t rhs);

	// DivMod -> returns the result of the division (lhs / rhs), and fills up the remainder
	static hugeint_t DivMod(hugeint_t lhs, hugeint_t rhs, hugeint_t &remainder);
	// DivMod but lhs MUST be positive, and rhs is a uint64_t
	static hugeint_t DivModPositive(hugeint_t lhs, uint64_t rhs, uint64_t &remainder);

	static bool AddInPlace(hugeint_t &lhs, hugeint_t rhs);
	static bool SubtractInPlace(hugeint_t &lhs, hugeint_t rhs);

	// comparison operators
	// note that everywhere here we intentionally use bitwise ops
	// this is because they seem to be consistently much faster (benchmarked on a Macbook Pro)
	static bool Equals(hugeint_t lhs, hugeint_t rhs) {
		int lower_equals = lhs.lower == rhs.lower;
		int upper_equals = lhs.upper == rhs.upper;
		return lower_equals & upper_equals;
	}
	static bool NotEquals(hugeint_t lhs, hugeint_t rhs) {
		int lower_not_equals = lhs.lower != rhs.lower;
		int upper_not_equals = lhs.upper != rhs.upper;
		return lower_not_equals | upper_not_equals;
	}
	static bool GreaterThan(hugeint_t lhs, hugeint_t rhs) {
		int upper_bigger = lhs.upper > rhs.upper;
		int upper_equal = lhs.upper == rhs.upper;
		int lower_bigger = lhs.lower > rhs.lower;
		return upper_bigger | (upper_equal & lower_bigger);
	}
	static bool GreaterThanEquals(hugeint_t lhs, hugeint_t rhs) {
		int upper_bigger = lhs.upper > rhs.upper;
		int upper_equal = lhs.upper == rhs.upper;
		int lower_bigger_equals = lhs.lower >= rhs.lower;
		return upper_bigger | (upper_equal & lower_bigger_equals);
	}
	static bool LessThan(hugeint_t lhs, hugeint_t rhs) {
		int upper_smaller = lhs.upper < rhs.upper;
		int upper_equal = lhs.upper == rhs.upper;
		int lower_smaller = lhs.lower < rhs.lower;
		return upper_smaller | (upper_equal & lower_smaller);
	}
	static bool LessThanEquals(hugeint_t lhs, hugeint_t rhs) {
		int upper_smaller = lhs.upper < rhs.upper;
		int upper_equal = lhs.upper == rhs.upper;
		int lower_smaller_equals = lhs.lower <= rhs.lower;
		return upper_smaller | (upper_equal & lower_smaller_equals);
	}
	static const hugeint_t POWERS_OF_TEN[40];
};

template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, int8_t &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, int16_t &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, int32_t &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, int64_t &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, uint8_t &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, uint16_t &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, uint32_t &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, uint64_t &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, hugeint_t &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, float &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, double &result);
template <>
DUCKDB_API bool Hugeint::TryCast(hugeint_t input, long double &result);

template <>
bool Hugeint::TryConvert(int8_t value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(int16_t value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(int32_t value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(int64_t value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(uint8_t value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(uint16_t value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(uint32_t value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(uint64_t value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(float value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(double value, hugeint_t &result);
template <>
bool Hugeint::TryConvert(long double value, hugeint_t &result);

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/interval.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//! The Interval class is a static class that holds helper functions for the Interval
//! type.
class Interval {
public:
	static constexpr const int32_t MONTHS_PER_MILLENIUM = 12000;
	static constexpr const int32_t MONTHS_PER_CENTURY = 1200;
	static constexpr const int32_t MONTHS_PER_DECADE = 120;
	static constexpr const int32_t MONTHS_PER_YEAR = 12;
	static constexpr const int32_t MONTHS_PER_QUARTER = 3;
	static constexpr const int32_t DAYS_PER_WEEK = 7;
	//! only used for interval comparison/ordering purposes, in which case a month counts as 30 days
	static constexpr const int64_t DAYS_PER_MONTH = 30;
	static constexpr const int64_t DAYS_PER_YEAR = 365;
	static constexpr const int64_t MSECS_PER_SEC = 1000;
	static constexpr const int32_t SECS_PER_MINUTE = 60;
	static constexpr const int32_t MINS_PER_HOUR = 60;
	static constexpr const int32_t HOURS_PER_DAY = 24;
	static constexpr const int32_t SECS_PER_HOUR = SECS_PER_MINUTE * MINS_PER_HOUR;
	static constexpr const int32_t SECS_PER_DAY = SECS_PER_HOUR * HOURS_PER_DAY;
	static constexpr const int32_t SECS_PER_WEEK = SECS_PER_DAY * DAYS_PER_WEEK;

	static constexpr const int64_t MICROS_PER_MSEC = 1000;
	static constexpr const int64_t MICROS_PER_SEC = MICROS_PER_MSEC * MSECS_PER_SEC;
	static constexpr const int64_t MICROS_PER_MINUTE = MICROS_PER_SEC * SECS_PER_MINUTE;
	static constexpr const int64_t MICROS_PER_HOUR = MICROS_PER_MINUTE * MINS_PER_HOUR;
	static constexpr const int64_t MICROS_PER_DAY = MICROS_PER_HOUR * HOURS_PER_DAY;
	static constexpr const int64_t MICROS_PER_WEEK = MICROS_PER_DAY * DAYS_PER_WEEK;
	static constexpr const int64_t MICROS_PER_MONTH = MICROS_PER_DAY * DAYS_PER_MONTH;

	static constexpr const int64_t NANOS_PER_MICRO = 1000;
	static constexpr const int64_t NANOS_PER_MSEC = NANOS_PER_MICRO * MICROS_PER_MSEC;
	static constexpr const int64_t NANOS_PER_SEC = NANOS_PER_MSEC * MSECS_PER_SEC;
	static constexpr const int64_t NANOS_PER_MINUTE = NANOS_PER_SEC * SECS_PER_MINUTE;
	static constexpr const int64_t NANOS_PER_HOUR = NANOS_PER_MINUTE * MINS_PER_HOUR;
	static constexpr const int64_t NANOS_PER_DAY = NANOS_PER_HOUR * HOURS_PER_DAY;
	static constexpr const int64_t NANOS_PER_WEEK = NANOS_PER_DAY * DAYS_PER_WEEK;

public:
	//! Convert a string to an interval object
	static bool FromString(const string &str, interval_t &result);
	//! Convert a string to an interval object
	static bool FromCString(const char *str, idx_t len, interval_t &result, string *error_message, bool strict);
	//! Convert an interval object to a string
	static string ToString(const interval_t &val);

	//! Convert milliseconds to a normalised interval
	DUCKDB_API static interval_t FromMicro(int64_t micros);

	//! Get Interval in milliseconds
	static int64_t GetMilli(const interval_t &val);

	//! Get Interval in microseconds
	static int64_t GetMicro(const interval_t &val);

	//! Get Interval in Nanoseconds
	static int64_t GetNanoseconds(const interval_t &val);

	//! Returns the age between two timestamps (including 30 day months)
	static interval_t GetAge(timestamp_t timestamp_1, timestamp_t timestamp_2);

	//! Returns the exact difference between two timestamps (days and seconds)
	static interval_t GetDifference(timestamp_t timestamp_1, timestamp_t timestamp_2);

	//! Returns the inverted interval
	static interval_t Invert(interval_t interval);

	//! Add an interval to a date
	static date_t Add(date_t left, interval_t right);
	//! Add an interval to a timestamp
	static timestamp_t Add(timestamp_t left, interval_t right);
	//! Add an interval to a time. In case the time overflows or underflows, modify the date by the overflow.
	//! For example if we go from 23:00 to 02:00, we add a day to the date
	static dtime_t Add(dtime_t left, interval_t right, date_t &date);

	//! Comparison operators
	static bool Equals(interval_t left, interval_t right);
	static bool GreaterThan(interval_t left, interval_t right);
	static bool GreaterThanEquals(interval_t left, interval_t right);
};
} // namespace duckdb



#include <cstring>

namespace duckdb {

//===--------------------------------------------------------------------===//
// Comparison Operations
//===--------------------------------------------------------------------===//
struct Equals {
	template <class T>
	DUCKDB_API static inline bool Operation(T left, T right) {
		return left == right;
	}
};
struct NotEquals {
	template <class T>
	DUCKDB_API static inline bool Operation(T left, T right) {
		return !Equals::Operation(left, right);
	}
};

struct GreaterThan {
	template <class T>
	DUCKDB_API static inline bool Operation(T left, T right) {
		return left > right;
	}
};

struct GreaterThanEquals {
	template <class T>
	DUCKDB_API static inline bool Operation(T left, T right) {
		return left >= right;
	}
};

struct LessThan {
	template <class T>
	DUCKDB_API static inline bool Operation(T left, T right) {
		return GreaterThan::Operation(right, left);
	}
};

struct LessThanEquals {
	template <class T>
	DUCKDB_API static inline bool Operation(T left, T right) {
		return GreaterThanEquals::Operation(right, left);
	}
};

template <>
DUCKDB_API bool Equals::Operation(float left, float right);
template <>
DUCKDB_API bool Equals::Operation(double left, double right);

template <>
DUCKDB_API bool GreaterThan::Operation(float left, float right);
template <>
DUCKDB_API bool GreaterThan::Operation(double left, double right);

template <>
DUCKDB_API bool GreaterThanEquals::Operation(float left, float right);
template <>
DUCKDB_API bool GreaterThanEquals::Operation(double left, double right);

// Distinct semantics are from Postgres record sorting. NULL = NULL and not-NULL < NULL
// Deferring to the non-distinct operations removes the need for further specialisation.
// TODO: To reverse the semantics, swap left_null and right_null for comparisons
struct DistinctFrom {
	template <class T>
	static inline bool Operation(T left, T right, bool left_null, bool right_null) {
		return (left_null != right_null) || (!left_null && !right_null && NotEquals::Operation(left, right));
	}
};

struct NotDistinctFrom {
	template <class T>
	static inline bool Operation(T left, T right, bool left_null, bool right_null) {
		return (left_null && right_null) || (!left_null && !right_null && Equals::Operation(left, right));
	}
};

struct DistinctGreaterThan {
	template <class T>
	static inline bool Operation(T left, T right, bool left_null, bool right_null) {
		return GreaterThan::Operation(left_null, right_null) ||
		       (!left_null && !right_null && GreaterThan::Operation(left, right));
	}
};

struct DistinctGreaterThanNullsFirst {
	template <class T>
	static inline bool Operation(T left, T right, bool left_null, bool right_null) {
		return GreaterThan::Operation(right_null, left_null) ||
		       (!left_null && !right_null && GreaterThan::Operation(left, right));
	}
};

struct DistinctGreaterThanEquals {
	template <class T>
	static inline bool Operation(T left, T right, bool left_null, bool right_null) {
		return left_null || (!left_null && !right_null && GreaterThanEquals::Operation(left, right));
	}
};

struct DistinctLessThan {
	template <class T>
	static inline bool Operation(T left, T right, bool left_null, bool right_null) {
		return LessThan::Operation(left_null, right_null) ||
		       (!left_null && !right_null && LessThan::Operation(left, right));
	}
};

struct DistinctLessThanNullsFirst {
	template <class T>
	static inline bool Operation(T left, T right, bool left_null, bool right_null) {
		return LessThan::Operation(right_null, left_null) ||
		       (!left_null && !right_null && LessThan::Operation(left, right));
	}
};

struct DistinctLessThanEquals {
	template <class T>
	static inline bool Operation(T left, T right, bool left_null, bool right_null) {
		return right_null || (!left_null && !right_null && LessThanEquals::Operation(left, right));
	}
};

//===--------------------------------------------------------------------===//
// Specialized Boolean Comparison Operators
//===--------------------------------------------------------------------===//
template <>
inline bool GreaterThan::Operation(bool left, bool right) {
	return !right && left;
}
template <>
inline bool LessThan::Operation(bool left, bool right) {
	return !left && right;
}
//===--------------------------------------------------------------------===//
// Specialized String Comparison Operations
//===--------------------------------------------------------------------===//
struct StringComparisonOperators {
	template <bool INVERSE>
	static inline bool EqualsOrNot(const string_t a, const string_t b) {
		if (a.IsInlined()) {
			// small string: compare entire string
			if (memcmp(&a, &b, sizeof(string_t)) == 0) {
				// entire string is equal
				return INVERSE ? false : true;
			}
		} else {
			// large string: first check prefix and length
			if (memcmp(&a, &b, sizeof(uint32_t) + string_t::PREFIX_LENGTH) == 0) {
				// prefix and length are equal: check main string
				if (memcmp(a.value.pointer.ptr, b.value.pointer.ptr, a.GetSize()) == 0) {
					// entire string is equal
					return INVERSE ? false : true;
				}
			}
		}
		// not equal
		return INVERSE ? true : false;
	}
};

template <>
inline bool Equals::Operation(string_t left, string_t right) {
	return StringComparisonOperators::EqualsOrNot<false>(left, right);
}
template <>
inline bool NotEquals::Operation(string_t left, string_t right) {
	return StringComparisonOperators::EqualsOrNot<true>(left, right);
}

template <>
inline bool NotDistinctFrom::Operation(string_t left, string_t right, bool left_null, bool right_null) {
	return (left_null && right_null) ||
	       (!left_null && !right_null && StringComparisonOperators::EqualsOrNot<false>(left, right));
}
template <>
inline bool DistinctFrom::Operation(string_t left, string_t right, bool left_null, bool right_null) {
	return (left_null != right_null) ||
	       (!left_null && !right_null && StringComparisonOperators::EqualsOrNot<true>(left, right));
}

// compare up to shared length. if still the same, compare lengths
template <class OP>
static bool templated_string_compare_op(string_t left, string_t right) {
	auto memcmp_res =
	    memcmp(left.GetDataUnsafe(), right.GetDataUnsafe(), MinValue<idx_t>(left.GetSize(), right.GetSize()));
	auto final_res = memcmp_res == 0 ? OP::Operation(left.GetSize(), right.GetSize()) : OP::Operation(memcmp_res, 0);
	return final_res;
}

template <>
inline bool GreaterThan::Operation(string_t left, string_t right) {
	return templated_string_compare_op<GreaterThan>(left, right);
}

template <>
inline bool GreaterThanEquals::Operation(string_t left, string_t right) {
	return templated_string_compare_op<GreaterThanEquals>(left, right);
}

template <>
inline bool LessThan::Operation(string_t left, string_t right) {
	return templated_string_compare_op<LessThan>(left, right);
}

template <>
inline bool LessThanEquals::Operation(string_t left, string_t right) {
	return templated_string_compare_op<LessThanEquals>(left, right);
}
//===--------------------------------------------------------------------===//
// Specialized Interval Comparison Operators
//===--------------------------------------------------------------------===//
template <>
inline bool Equals::Operation(interval_t left, interval_t right) {
	return Interval::Equals(left, right);
}
template <>
inline bool NotEquals::Operation(interval_t left, interval_t right) {
	return !Equals::Operation(left, right);
}
template <>
inline bool GreaterThan::Operation(interval_t left, interval_t right) {
	return Interval::GreaterThan(left, right);
}
template <>
inline bool GreaterThanEquals::Operation(interval_t left, interval_t right) {
	return Interval::GreaterThanEquals(left, right);
}
template <>
inline bool LessThan::Operation(interval_t left, interval_t right) {
	return GreaterThan::Operation(right, left);
}
template <>
inline bool LessThanEquals::Operation(interval_t left, interval_t right) {
	return GreaterThanEquals::Operation(right, left);
}

template <>
inline bool NotDistinctFrom::Operation(interval_t left, interval_t right, bool left_null, bool right_null) {
	return (left_null && right_null) || (!left_null && !right_null && Interval::Equals(left, right));
}
template <>
inline bool DistinctFrom::Operation(interval_t left, interval_t right, bool left_null, bool right_null) {
	return (left_null != right_null) || (!left_null && !right_null && !Equals::Operation(left, right));
}
inline bool operator<(const interval_t &lhs, const interval_t &rhs) {
	return LessThan::Operation(lhs, rhs);
}

//===--------------------------------------------------------------------===//
// Specialized Hugeint Comparison Operators
//===--------------------------------------------------------------------===//
template <>
inline bool Equals::Operation(hugeint_t left, hugeint_t right) {
	return Hugeint::Equals(left, right);
}
template <>
inline bool NotEquals::Operation(hugeint_t left, hugeint_t right) {
	return Hugeint::NotEquals(left, right);
}
template <>
inline bool GreaterThan::Operation(hugeint_t left, hugeint_t right) {
	return Hugeint::GreaterThan(left, right);
}
template <>
inline bool GreaterThanEquals::Operation(hugeint_t left, hugeint_t right) {
	return Hugeint::GreaterThanEquals(left, right);
}
template <>
inline bool LessThan::Operation(hugeint_t left, hugeint_t right) {
	return Hugeint::LessThan(left, right);
}
template <>
inline bool LessThanEquals::Operation(hugeint_t left, hugeint_t right) {
	return Hugeint::LessThanEquals(left, right);
}
} // namespace duckdb




namespace duckdb {
struct SelectionVector;

class Serializer;
class Deserializer;
class FieldWriter;
class FieldReader;
class Vector;
class ValidityStatistics;
class DistinctStatistics;
struct UnifiedVectorFormat;

enum StatisticsType { LOCAL_STATS = 0, GLOBAL_STATS = 1 };

class BaseStatistics {
public:
	BaseStatistics(LogicalType type, StatisticsType stats_type);
	virtual ~BaseStatistics();

	//! The type of the logical segment
	LogicalType type;
	//! The validity stats of the column (if any)
	unique_ptr<BaseStatistics> validity_stats;
	//! The approximate count distinct stats of the column (if any)
	unique_ptr<BaseStatistics> distinct_stats;
	//! Whether these are 'global' stats, i.e., over a whole table, or just over a segment
	//! Some statistics are more expensive to keep, therefore we only keep them globally
	StatisticsType stats_type;

public:
	static unique_ptr<BaseStatistics> CreateEmpty(LogicalType type, StatisticsType stats_type);

	bool CanHaveNull() const;
	bool CanHaveNoNull() const;

	void UpdateDistinctStatistics(Vector &v, idx_t count);

	virtual bool IsConstant() const {
		return false;
	}

	virtual void Merge(const BaseStatistics &other);

	virtual unique_ptr<BaseStatistics> Copy() const;
	void CopyBase(const BaseStatistics &orig);

	virtual void Serialize(Serializer &serializer) const;
	virtual void Serialize(FieldWriter &writer) const;

	idx_t GetDistinctCount();

	static unique_ptr<BaseStatistics> Deserialize(Deserializer &source, LogicalType type);

	//! Verify that a vector does not violate the statistics
	virtual void Verify(Vector &vector, const SelectionVector &sel, idx_t count) const;
	void Verify(Vector &vector, idx_t count) const;

	virtual string ToString() const;

protected:
	void InitializeBase();
};

} // namespace duckdb


namespace duckdb {

struct FunctionLocalState {
	DUCKDB_API virtual ~FunctionLocalState();
};

class Binder;
class BoundFunctionExpression;
class ScalarFunctionCatalogEntry;

struct FunctionStatisticsInput {
	FunctionStatisticsInput(BoundFunctionExpression &expr_p, FunctionData *bind_data_p,
	                        vector<unique_ptr<BaseStatistics>> &child_stats_p, unique_ptr<Expression> *expr_ptr_p)
	    : expr(expr_p), bind_data(bind_data_p), child_stats(child_stats_p), expr_ptr(expr_ptr_p) {
	}

	BoundFunctionExpression &expr;
	FunctionData *bind_data;
	vector<unique_ptr<BaseStatistics>> &child_stats;
	unique_ptr<Expression> *expr_ptr;
};

//! The type used for scalar functions
typedef std::function<void(DataChunk &, ExpressionState &, Vector &)> scalar_function_t;
//! Binds the scalar function and creates the function data
typedef unique_ptr<FunctionData> (*bind_scalar_function_t)(ClientContext &context, ScalarFunction &bound_function,
                                                           vector<unique_ptr<Expression>> &arguments);
typedef unique_ptr<FunctionLocalState> (*init_local_state_t)(const BoundFunctionExpression &expr,
                                                             FunctionData *bind_data);
typedef unique_ptr<BaseStatistics> (*function_statistics_t)(ClientContext &context, FunctionStatisticsInput &input);
//! Adds the dependencies of this BoundFunctionExpression to the set of dependencies
typedef void (*dependency_function_t)(BoundFunctionExpression &expr, unordered_set<CatalogEntry *> &dependencies);

typedef void (*function_serialize_t)(FieldWriter &writer, const FunctionData *bind_data,
                                     const ScalarFunction &function);
typedef unique_ptr<FunctionData> (*function_deserialize_t)(ClientContext &context, FieldReader &reader,
                                                           ScalarFunction &function);

class ScalarFunction : public BaseScalarFunction {
public:
	DUCKDB_API ScalarFunction(string name, vector<LogicalType> arguments, LogicalType return_type,
	                          scalar_function_t function, bind_scalar_function_t bind = nullptr,
	                          dependency_function_t dependency = nullptr, function_statistics_t statistics = nullptr,
	                          init_local_state_t init_local_state = nullptr,
	                          LogicalType varargs = LogicalType(LogicalTypeId::INVALID),
	                          FunctionSideEffects side_effects = FunctionSideEffects::NO_SIDE_EFFECTS,
	                          FunctionNullHandling null_handling = FunctionNullHandling::DEFAULT_NULL_HANDLING);

	DUCKDB_API ScalarFunction(vector<LogicalType> arguments, LogicalType return_type, scalar_function_t function,
	                          bind_scalar_function_t bind = nullptr, dependency_function_t dependency = nullptr,
	                          function_statistics_t statistics = nullptr, init_local_state_t init_local_state = nullptr,
	                          LogicalType varargs = LogicalType(LogicalTypeId::INVALID),
	                          FunctionSideEffects side_effects = FunctionSideEffects::NO_SIDE_EFFECTS,
	                          FunctionNullHandling null_handling = FunctionNullHandling::DEFAULT_NULL_HANDLING);

	//! The main scalar function to execute
	scalar_function_t function;
	//! The bind function (if any)
	bind_scalar_function_t bind;
	//! Init thread local state for the function (if any)
	init_local_state_t init_local_state;
	//! The dependency function (if any)
	dependency_function_t dependency;
	//! The statistics propagation function (if any)
	function_statistics_t statistics;

	function_serialize_t serialize;
	function_deserialize_t deserialize;

	DUCKDB_API static unique_ptr<Expression> BindScalarFunction(ClientContext &context, const string &schema,
	                                                            const string &name,
	                                                            vector<unique_ptr<Expression>> children, string &error,
	                                                            bool is_operator = false, Binder *binder = nullptr);
	DUCKDB_API static unique_ptr<Expression> BindScalarFunction(ClientContext &context,
	                                                            ScalarFunctionCatalogEntry &function,
	                                                            vector<unique_ptr<Expression>> children, string &error,
	                                                            bool is_operator = false, Binder *binder = nullptr);

	DUCKDB_API static unique_ptr<BoundFunctionExpression> BindScalarFunction(ClientContext &context,
	                                                                         ScalarFunction bound_function,
	                                                                         vector<unique_ptr<Expression>> children,
	                                                                         bool is_operator = false);

	DUCKDB_API bool operator==(const ScalarFunction &rhs) const;
	DUCKDB_API bool operator!=(const ScalarFunction &rhs) const;

	DUCKDB_API bool Equal(const ScalarFunction &rhs) const;

private:
	bool CompareScalarFunctionT(const scalar_function_t &other) const;

public:
	DUCKDB_API static void NopFunction(DataChunk &input, ExpressionState &state, Vector &result);

	template <class TA, class TR, class OP>
	static void UnaryFunction(DataChunk &input, ExpressionState &state, Vector &result) {
		D_ASSERT(input.ColumnCount() >= 1);
		UnaryExecutor::Execute<TA, TR, OP>(input.data[0], result, input.size());
	}

	template <class TA, class TB, class TR, class OP>
	static void BinaryFunction(DataChunk &input, ExpressionState &state, Vector &result) {
		D_ASSERT(input.ColumnCount() == 2);
		BinaryExecutor::ExecuteStandard<TA, TB, TR, OP>(input.data[0], input.data[1], result, input.size());
	}

public:
	template <class OP>
	static scalar_function_t GetScalarUnaryFunction(LogicalType type) {
		scalar_function_t function;
		switch (type.id()) {
		case LogicalTypeId::TINYINT:
			function = &ScalarFunction::UnaryFunction<int8_t, int8_t, OP>;
			break;
		case LogicalTypeId::SMALLINT:
			function = &ScalarFunction::UnaryFunction<int16_t, int16_t, OP>;
			break;
		case LogicalTypeId::INTEGER:
			function = &ScalarFunction::UnaryFunction<int32_t, int32_t, OP>;
			break;
		case LogicalTypeId::BIGINT:
			function = &ScalarFunction::UnaryFunction<int64_t, int64_t, OP>;
			break;
		case LogicalTypeId::UTINYINT:
			function = &ScalarFunction::UnaryFunction<uint8_t, uint8_t, OP>;
			break;
		case LogicalTypeId::USMALLINT:
			function = &ScalarFunction::UnaryFunction<uint16_t, uint16_t, OP>;
			break;
		case LogicalTypeId::UINTEGER:
			function = &ScalarFunction::UnaryFunction<uint32_t, uint32_t, OP>;
			break;
		case LogicalTypeId::UBIGINT:
			function = &ScalarFunction::UnaryFunction<uint64_t, uint64_t, OP>;
			break;
		case LogicalTypeId::HUGEINT:
			function = &ScalarFunction::UnaryFunction<hugeint_t, hugeint_t, OP>;
			break;
		case LogicalTypeId::FLOAT:
			function = &ScalarFunction::UnaryFunction<float, float, OP>;
			break;
		case LogicalTypeId::DOUBLE:
			function = &ScalarFunction::UnaryFunction<double, double, OP>;
			break;
		default:
			throw InternalException("Unimplemented type for GetScalarUnaryFunction");
		}
		return function;
	}

	template <class TR, class OP>
	static scalar_function_t GetScalarUnaryFunctionFixedReturn(LogicalType type) {
		scalar_function_t function;
		switch (type.id()) {
		case LogicalTypeId::TINYINT:
			function = &ScalarFunction::UnaryFunction<int8_t, TR, OP>;
			break;
		case LogicalTypeId::SMALLINT:
			function = &ScalarFunction::UnaryFunction<int16_t, TR, OP>;
			break;
		case LogicalTypeId::INTEGER:
			function = &ScalarFunction::UnaryFunction<int32_t, TR, OP>;
			break;
		case LogicalTypeId::BIGINT:
			function = &ScalarFunction::UnaryFunction<int64_t, TR, OP>;
			break;
		case LogicalTypeId::UTINYINT:
			function = &ScalarFunction::UnaryFunction<uint8_t, TR, OP>;
			break;
		case LogicalTypeId::USMALLINT:
			function = &ScalarFunction::UnaryFunction<uint16_t, TR, OP>;
			break;
		case LogicalTypeId::UINTEGER:
			function = &ScalarFunction::UnaryFunction<uint32_t, TR, OP>;
			break;
		case LogicalTypeId::UBIGINT:
			function = &ScalarFunction::UnaryFunction<uint64_t, TR, OP>;
			break;
		case LogicalTypeId::HUGEINT:
			function = &ScalarFunction::UnaryFunction<hugeint_t, TR, OP>;
			break;
		case LogicalTypeId::FLOAT:
			function = &ScalarFunction::UnaryFunction<float, TR, OP>;
			break;
		case LogicalTypeId::DOUBLE:
			function = &ScalarFunction::UnaryFunction<double, TR, OP>;
			break;
		default:
			throw InternalException("Unimplemented type for GetScalarUnaryFunctionFixedReturn");
		}
		return function;
	}
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/aggregate_function.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/storage/statistics/node_statistics.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

class NodeStatistics {
public:
	NodeStatistics() : has_estimated_cardinality(false), has_max_cardinality(false) {
	}
	explicit NodeStatistics(idx_t estimated_cardinality)
	    : has_estimated_cardinality(true), estimated_cardinality(estimated_cardinality), has_max_cardinality(false) {
	}
	NodeStatistics(idx_t estimated_cardinality, idx_t max_cardinality)
	    : has_estimated_cardinality(true), estimated_cardinality(estimated_cardinality), has_max_cardinality(true),
	      max_cardinality(max_cardinality) {
	}

	//! Whether or not the node has an estimated cardinality specified
	bool has_estimated_cardinality;
	//! The estimated cardinality at the specified node
	idx_t estimated_cardinality;
	//! Whether or not the node has a maximum cardinality specified
	bool has_max_cardinality;
	//! The max possible cardinality at the specified node
	idx_t max_cardinality;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/bound_result_modifier.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/result_modifier.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/order_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class OrderType : uint8_t { INVALID = 0, ORDER_DEFAULT = 1, ASCENDING = 2, DESCENDING = 3 };
enum class OrderByNullType : uint8_t { INVALID = 0, ORDER_DEFAULT = 1, NULLS_FIRST = 2, NULLS_LAST = 3 };

} // namespace duckdb



namespace duckdb {
class FieldWriter;
class FieldReader;

enum ResultModifierType : uint8_t {
	LIMIT_MODIFIER = 1,
	ORDER_MODIFIER = 2,
	DISTINCT_MODIFIER = 3,
	LIMIT_PERCENT_MODIFIER = 4
};

//! A ResultModifier
class ResultModifier {
public:
	explicit ResultModifier(ResultModifierType type) : type(type) {
	}
	virtual ~ResultModifier() {
	}

	ResultModifierType type;

public:
	//! Returns true if the two result modifiers are equivalent
	virtual bool Equals(const ResultModifier *other) const;

	//! Create a copy of this ResultModifier
	virtual unique_ptr<ResultModifier> Copy() const = 0;
	//! Serializes a ResultModifier to a stand-alone binary blob
	void Serialize(Serializer &serializer) const;
	//! Serializes a ResultModifier to a stand-alone binary blob
	virtual void Serialize(FieldWriter &writer) const = 0;
	//! Deserializes a blob back into a ResultModifier
	static unique_ptr<ResultModifier> Deserialize(Deserializer &source);
};

//! Single node in ORDER BY statement
struct OrderByNode {
	OrderByNode(OrderType type, OrderByNullType null_order, unique_ptr<ParsedExpression> expression)
	    : type(type), null_order(null_order), expression(move(expression)) {
	}

	//! Sort order, ASC or DESC
	OrderType type;
	//! The NULL sort order, NULLS_FIRST or NULLS_LAST
	OrderByNullType null_order;
	//! Expression to order by
	unique_ptr<ParsedExpression> expression;

public:
	void Serialize(Serializer &serializer) const;
	string ToString() const;
	static OrderByNode Deserialize(Deserializer &source);
};

class LimitModifier : public ResultModifier {
public:
	LimitModifier() : ResultModifier(ResultModifierType::LIMIT_MODIFIER) {
	}

	//! LIMIT count
	unique_ptr<ParsedExpression> limit;
	//! OFFSET
	unique_ptr<ParsedExpression> offset;

public:
	bool Equals(const ResultModifier *other) const override;
	unique_ptr<ResultModifier> Copy() const override;
	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<ResultModifier> Deserialize(FieldReader &reader);
};

class OrderModifier : public ResultModifier {
public:
	OrderModifier() : ResultModifier(ResultModifierType::ORDER_MODIFIER) {
	}

	//! List of order nodes
	vector<OrderByNode> orders;

public:
	bool Equals(const ResultModifier *other) const override;
	unique_ptr<ResultModifier> Copy() const override;
	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<ResultModifier> Deserialize(FieldReader &reader);
};

class DistinctModifier : public ResultModifier {
public:
	DistinctModifier() : ResultModifier(ResultModifierType::DISTINCT_MODIFIER) {
	}

	//! list of distinct on targets (if any)
	vector<unique_ptr<ParsedExpression>> distinct_on_targets;

public:
	bool Equals(const ResultModifier *other) const override;
	unique_ptr<ResultModifier> Copy() const override;
	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<ResultModifier> Deserialize(FieldReader &reader);
};

class LimitPercentModifier : public ResultModifier {
public:
	LimitPercentModifier() : ResultModifier(ResultModifierType::LIMIT_PERCENT_MODIFIER) {
	}

	//! LIMIT %
	unique_ptr<ParsedExpression> limit;
	//! OFFSET
	unique_ptr<ParsedExpression> offset;

public:
	bool Equals(const ResultModifier *other) const override;
	unique_ptr<ResultModifier> Copy() const override;
	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<ResultModifier> Deserialize(FieldReader &reader);
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/bound_statement.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/logical_operator.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_entry.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/catalog_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//===--------------------------------------------------------------------===//
// Catalog Types
//===--------------------------------------------------------------------===//
enum class CatalogType : uint8_t {
	INVALID = 0,
	TABLE_ENTRY = 1,
	SCHEMA_ENTRY = 2,
	VIEW_ENTRY = 3,
	INDEX_ENTRY = 4,
	PREPARED_STATEMENT = 5,
	SEQUENCE_ENTRY = 6,
	COLLATION_ENTRY = 7,
	TYPE_ENTRY = 8,

	// functions
	TABLE_FUNCTION_ENTRY = 25,
	SCALAR_FUNCTION_ENTRY = 26,
	AGGREGATE_FUNCTION_ENTRY = 27,
	PRAGMA_FUNCTION_ENTRY = 28,
	COPY_FUNCTION_ENTRY = 29,
	MACRO_ENTRY = 30,
	TABLE_MACRO_ENTRY = 31,

	// version info
	UPDATED_ENTRY = 50,
	DELETED_ENTRY = 51,
};

DUCKDB_API string CatalogTypeToString(CatalogType type);

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/atomic.hpp
//
//
//===----------------------------------------------------------------------===//



#include <atomic>

namespace duckdb {
using std::atomic;
}


#include <memory>

namespace duckdb {
struct AlterInfo;
class Catalog;
class CatalogSet;
class ClientContext;

//! Abstract base class of an entry in the catalog
class CatalogEntry {
public:
	CatalogEntry(CatalogType type, Catalog *catalog, string name);
	virtual ~CatalogEntry();

	//! The oid of the entry
	idx_t oid;
	//! The type of this catalog entry
	CatalogType type;
	//! Reference to the catalog this entry belongs to
	Catalog *catalog;
	//! Reference to the catalog set this entry is stored in
	CatalogSet *set;
	//! The name of the entry
	string name;
	//! Whether or not the object is deleted
	bool deleted;
	//! Whether or not the object is temporary and should not be added to the WAL
	bool temporary;
	//! Whether or not the entry is an internal entry (cannot be deleted, not dumped, etc)
	bool internal;
	//! Timestamp at which the catalog entry was created
	atomic<transaction_t> timestamp;
	//! Child entry
	unique_ptr<CatalogEntry> child;
	//! Parent entry (the node that dependents_map this node)
	CatalogEntry *parent;

public:
	virtual unique_ptr<CatalogEntry> AlterEntry(ClientContext &context, AlterInfo *info);

	virtual unique_ptr<CatalogEntry> Copy(ClientContext &context);

	//! Sets the CatalogEntry as the new root entry (i.e. the newest entry)
	// this is called on a rollback to an AlterEntry
	virtual void SetAsRoot();

	//! Convert the catalog entry to a SQL string that can be used to re-construct the catalog entry
	virtual string ToSQL();
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/mutex.hpp
//
//
//===----------------------------------------------------------------------===//



#include <mutex>

namespace duckdb {
using std::lock_guard;
using std::mutex;
using std::unique_lock;
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/query_error_context.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {
class SQLStatement;

class QueryErrorContext {
public:
	explicit QueryErrorContext(SQLStatement *statement_ = nullptr, idx_t query_location_ = DConstants::INVALID_INDEX)
	    : statement(statement_), query_location(query_location_) {
	}

	//! The query statement
	SQLStatement *statement;
	//! The location in which the error should be thrown
	idx_t query_location;

public:
	static string Format(const string &query, const string &error_message, int error_location);

	string FormatErrorRecursive(const string &msg, vector<ExceptionFormatValue> &values);
	template <class T, typename... Args>
	string FormatErrorRecursive(const string &msg, vector<ExceptionFormatValue> &values, T param, Args... params) {
		values.push_back(ExceptionFormatValue::CreateFormatValue<T>(param));
		return FormatErrorRecursive(msg, values, params...);
	}

	template <typename... Args>
	string FormatError(const string &msg, Args... params) {
		vector<ExceptionFormatValue> values;
		return FormatErrorRecursive(msg, values, params...);
	}
};

} // namespace duckdb


#include <functional>


namespace duckdb {
struct CreateSchemaInfo;
struct DropInfo;
struct BoundCreateTableInfo;
struct AlterTableInfo;
struct CreateTableFunctionInfo;
struct CreateCopyFunctionInfo;
struct CreatePragmaFunctionInfo;
struct CreateFunctionInfo;
struct CreateViewInfo;
struct CreateSequenceInfo;
struct CreateCollationInfo;
struct CreateTypeInfo;
struct CreateTableInfo;

class ClientContext;
class Transaction;

class AggregateFunctionCatalogEntry;
class CollateCatalogEntry;
class SchemaCatalogEntry;
class TableCatalogEntry;
class ViewCatalogEntry;
class SequenceCatalogEntry;
class TableFunctionCatalogEntry;
class CopyFunctionCatalogEntry;
class PragmaFunctionCatalogEntry;
class CatalogSet;
class DatabaseInstance;
class DependencyManager;

//! Return value of Catalog::LookupEntry
struct CatalogEntryLookup {
	SchemaCatalogEntry *schema;
	CatalogEntry *entry;

	DUCKDB_API bool Found() const {
		return entry;
	}
};

//! Return value of SimilarEntryInSchemas
struct SimilarCatalogEntry {
	//! The entry name. Empty if absent
	string name;
	//! The distance to the given name.
	idx_t distance;
	//! The schema of the entry.
	SchemaCatalogEntry *schema;

	DUCKDB_API bool Found() const {
		return !name.empty();
	}

	DUCKDB_API string GetQualifiedName() const;
};

//! The Catalog object represents the catalog of the database.
class Catalog {
public:
	explicit Catalog(DatabaseInstance &db);
	~Catalog();

	//! Reference to the database
	DatabaseInstance &db;
	//! The catalog set holding the schemas
	unique_ptr<CatalogSet> schemas;
	//! The DependencyManager manages dependencies between different catalog objects
	unique_ptr<DependencyManager> dependency_manager;
	//! Write lock for the catalog
	mutex write_lock;

public:
	//! Get the Catalog from the ClientContext
	DUCKDB_API static Catalog &GetCatalog(ClientContext &context);
	//! Get the Catalog from the DatabaseInstance
	DUCKDB_API static Catalog &GetCatalog(DatabaseInstance &db);

	DUCKDB_API DependencyManager &GetDependencyManager() {
		return *dependency_manager;
	}

	//! Returns the current version of the catalog (incremented whenever anything changes, not stored between restarts)
	DUCKDB_API idx_t GetCatalogVersion();
	//! Trigger a modification in the catalog, increasing the catalog version and returning the previous version
	DUCKDB_API idx_t ModifyCatalog();

	//! Creates a schema in the catalog.
	DUCKDB_API CatalogEntry *CreateSchema(ClientContext &context, CreateSchemaInfo *info);
	//! Creates a table in the catalog.
	DUCKDB_API CatalogEntry *CreateTable(ClientContext &context, BoundCreateTableInfo *info);
	//! Creates a table in the catalog.
	DUCKDB_API CatalogEntry *CreateTable(ClientContext &context, unique_ptr<CreateTableInfo> info);
	//! Create a table function in the catalog
	DUCKDB_API CatalogEntry *CreateTableFunction(ClientContext &context, CreateTableFunctionInfo *info);
	//! Create a copy function in the catalog
	DUCKDB_API CatalogEntry *CreateCopyFunction(ClientContext &context, CreateCopyFunctionInfo *info);
	//! Create a pragma function in the catalog
	DUCKDB_API CatalogEntry *CreatePragmaFunction(ClientContext &context, CreatePragmaFunctionInfo *info);
	//! Create a scalar or aggregate function in the catalog
	DUCKDB_API CatalogEntry *CreateFunction(ClientContext &context, CreateFunctionInfo *info);
	//! Creates a table in the catalog.
	DUCKDB_API CatalogEntry *CreateView(ClientContext &context, CreateViewInfo *info);
	//! Creates a sequence in the catalog.
	DUCKDB_API CatalogEntry *CreateSequence(ClientContext &context, CreateSequenceInfo *info);
	//! Creates a Enum in the catalog.
	DUCKDB_API CatalogEntry *CreateType(ClientContext &context, CreateTypeInfo *info);
	//! Creates a collation in the catalog
	DUCKDB_API CatalogEntry *CreateCollation(ClientContext &context, CreateCollationInfo *info);

	//! Creates a table in the catalog.
	DUCKDB_API CatalogEntry *CreateTable(ClientContext &context, SchemaCatalogEntry *schema,
	                                     BoundCreateTableInfo *info);
	//! Create a table function in the catalog
	DUCKDB_API CatalogEntry *CreateTableFunction(ClientContext &context, SchemaCatalogEntry *schema,
	                                             CreateTableFunctionInfo *info);
	//! Create a copy function in the catalog
	DUCKDB_API CatalogEntry *CreateCopyFunction(ClientContext &context, SchemaCatalogEntry *schema,
	                                            CreateCopyFunctionInfo *info);
	//! Create a pragma function in the catalog
	DUCKDB_API CatalogEntry *CreatePragmaFunction(ClientContext &context, SchemaCatalogEntry *schema,
	                                              CreatePragmaFunctionInfo *info);
	//! Create a scalar or aggregate function in the catalog
	DUCKDB_API CatalogEntry *CreateFunction(ClientContext &context, SchemaCatalogEntry *schema,
	                                        CreateFunctionInfo *info);
	//! Creates a table in the catalog.
	DUCKDB_API CatalogEntry *CreateView(ClientContext &context, SchemaCatalogEntry *schema, CreateViewInfo *info);
	//! Creates a table in the catalog.
	DUCKDB_API CatalogEntry *CreateSequence(ClientContext &context, SchemaCatalogEntry *schema,
	                                        CreateSequenceInfo *info);
	//! Creates a enum in the catalog.
	DUCKDB_API CatalogEntry *CreateType(ClientContext &context, SchemaCatalogEntry *schema, CreateTypeInfo *info);
	//! Creates a collation in the catalog
	DUCKDB_API CatalogEntry *CreateCollation(ClientContext &context, SchemaCatalogEntry *schema,
	                                         CreateCollationInfo *info);

	//! Drops an entry from the catalog
	DUCKDB_API void DropEntry(ClientContext &context, DropInfo *info);

	//! Returns the schema object with the specified name, or throws an exception if it does not exist
	DUCKDB_API SchemaCatalogEntry *GetSchema(ClientContext &context, const string &name = DEFAULT_SCHEMA,
	                                         bool if_exists = false,
	                                         QueryErrorContext error_context = QueryErrorContext());
	//! Scans all the schemas in the system one-by-one, invoking the callback for each entry
	DUCKDB_API void ScanSchemas(ClientContext &context, std::function<void(CatalogEntry *)> callback);
	//! Gets the "schema.name" entry of the specified type, if if_exists=true returns nullptr if entry does not
	//! exist, otherwise an exception is thrown
	DUCKDB_API CatalogEntry *GetEntry(ClientContext &context, CatalogType type, const string &schema,
	                                  const string &name, bool if_exists = false,
	                                  QueryErrorContext error_context = QueryErrorContext());

	//! Gets the "schema.name" entry without a specified type, if entry does not exist an exception is thrown
	DUCKDB_API CatalogEntry *GetEntry(ClientContext &context, const string &schema, const string &name);

	//! Fetches a logical type from the catalog
	DUCKDB_API LogicalType GetType(ClientContext &context, const string &schema, const string &name);

	template <class T>
	T *GetEntry(ClientContext &context, const string &schema_name, const string &name, bool if_exists = false,
	            QueryErrorContext error_context = QueryErrorContext());

	//! Append a scalar or aggregate function to the catalog
	DUCKDB_API CatalogEntry *AddFunction(ClientContext &context, CreateFunctionInfo *info);
	//! Append a scalar or aggregate function to the catalog
	DUCKDB_API CatalogEntry *AddFunction(ClientContext &context, SchemaCatalogEntry *schema, CreateFunctionInfo *info);

	//! Alter an existing entry in the catalog.
	DUCKDB_API void Alter(ClientContext &context, AlterInfo *info);

private:
	//! The catalog version, incremented whenever anything changes in the catalog
	atomic<idx_t> catalog_version;

private:
	//! A variation of GetEntry that returns an associated schema as well.
	CatalogEntryLookup LookupEntry(ClientContext &context, CatalogType type, const string &schema, const string &name,
	                               bool if_exists = false, QueryErrorContext error_context = QueryErrorContext());

	//! Return an exception with did-you-mean suggestion.
	CatalogException CreateMissingEntryException(ClientContext &context, const string &entry_name, CatalogType type,
	                                             const vector<SchemaCatalogEntry *> &schemas,
	                                             QueryErrorContext error_context);

	//! Return the close entry name, the distance and the belonging schema.
	SimilarCatalogEntry SimilarEntryInSchemas(ClientContext &context, const string &entry_name, CatalogType type,
	                                          const vector<SchemaCatalogEntry *> &schemas);

	void DropSchema(ClientContext &context, DropInfo *info);
};

template <>
DUCKDB_API TableCatalogEntry *Catalog::GetEntry(ClientContext &context, const string &schema_name, const string &name,
                                                bool if_exists, QueryErrorContext error_context);
template <>
DUCKDB_API SequenceCatalogEntry *Catalog::GetEntry(ClientContext &context, const string &schema_name,
                                                   const string &name, bool if_exists, QueryErrorContext error_context);
template <>
DUCKDB_API TableFunctionCatalogEntry *Catalog::GetEntry(ClientContext &context, const string &schema_name,
                                                        const string &name, bool if_exists,
                                                        QueryErrorContext error_context);
template <>
DUCKDB_API CopyFunctionCatalogEntry *Catalog::GetEntry(ClientContext &context, const string &schema_name,
                                                       const string &name, bool if_exists,
                                                       QueryErrorContext error_context);
template <>
DUCKDB_API PragmaFunctionCatalogEntry *Catalog::GetEntry(ClientContext &context, const string &schema_name,
                                                         const string &name, bool if_exists,
                                                         QueryErrorContext error_context);
template <>
DUCKDB_API AggregateFunctionCatalogEntry *Catalog::GetEntry(ClientContext &context, const string &schema_name,
                                                            const string &name, bool if_exists,
                                                            QueryErrorContext error_context);
template <>
DUCKDB_API CollateCatalogEntry *Catalog::GetEntry(ClientContext &context, const string &schema_name, const string &name,
                                                  bool if_exists, QueryErrorContext error_context);
template <>
DUCKDB_API TypeCatalogEntry *Catalog::GetEntry(ClientContext &context, const string &schema_name, const string &name,
                                               bool if_exists, QueryErrorContext error_context);

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/optimizer/estimated_properties.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/optimizer/join_order/join_relation.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {
class LogicalOperator;

//! Represents a single relation and any metadata accompanying that relation
struct SingleJoinRelation {
	LogicalOperator *op;
	LogicalOperator *parent;

	SingleJoinRelation() {
	}
	SingleJoinRelation(LogicalOperator *op, LogicalOperator *parent) : op(op), parent(parent) {
	}
};

//! Set of relations, used in the join graph.
struct JoinRelationSet {
	JoinRelationSet(unique_ptr<idx_t[]> relations, idx_t count) : relations(move(relations)), count(count) {
	}

	string ToString() const;

	unique_ptr<idx_t[]> relations;
	idx_t count;

	static bool IsSubset(JoinRelationSet *super, JoinRelationSet *sub);
};

//! The JoinRelationTree is a structure holding all the created JoinRelationSet objects and allowing fast lookup on to
//! them
class JoinRelationSetManager {
public:
	//! Contains a node with a JoinRelationSet and child relations
	// FIXME: this structure is inefficient, could use a bitmap for lookup instead (todo: profile)
	struct JoinRelationTreeNode {
		unique_ptr<JoinRelationSet> relation;
		unordered_map<idx_t, unique_ptr<JoinRelationTreeNode>> children;
	};

public:
	//! Create or get a JoinRelationSet from a single node with the given index
	JoinRelationSet *GetJoinRelation(idx_t index);
	//! Create or get a JoinRelationSet from a set of relation bindings
	JoinRelationSet *GetJoinRelation(unordered_set<idx_t> &bindings);
	//! Create or get a JoinRelationSet from a (sorted, duplicate-free!) list of relations
	JoinRelationSet *GetJoinRelation(unique_ptr<idx_t[]> relations, idx_t count);
	//! Union two sets of relations together and create a new relation set
	JoinRelationSet *Union(JoinRelationSet *left, JoinRelationSet *right);
	// //! Create the set difference of left \ right (i.e. all elements in left that are not in right)
	// JoinRelationSet *Difference(JoinRelationSet *left, JoinRelationSet *right);

private:
	JoinRelationTreeNode root;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/expression_map.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {
class Expression;

struct ExpressionHashFunction {
	uint64_t operator()(const BaseExpression *const &expr) const {
		return (uint64_t)expr->Hash();
	}
};

struct ExpressionEquality {
	bool operator()(const BaseExpression *const &a, const BaseExpression *const &b) const {
		return a->Equals(b);
	}
};

template <typename T>
using expression_map_t = unordered_map<BaseExpression *, T, ExpressionHashFunction, ExpressionEquality>;

using expression_set_t = unordered_set<BaseExpression *, ExpressionHashFunction, ExpressionEquality>;

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/logical_operator_visitor.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/bound_tokens.hpp
//
//
//===----------------------------------------------------------------------===//



namespace duckdb {

//===--------------------------------------------------------------------===//
// Query Node
//===--------------------------------------------------------------------===//
class BoundQueryNode;
class BoundSelectNode;
class BoundSetOperationNode;
class BoundRecursiveCTENode;

//===--------------------------------------------------------------------===//
// Expressions
//===--------------------------------------------------------------------===//
class Expression;

class BoundAggregateExpression;
class BoundBetweenExpression;
class BoundCaseExpression;
class BoundCastExpression;
class BoundColumnRefExpression;
class BoundComparisonExpression;
class BoundConjunctionExpression;
class BoundConstantExpression;
class BoundDefaultExpression;
class BoundFunctionExpression;
class BoundOperatorExpression;
class BoundParameterExpression;
class BoundReferenceExpression;
class BoundSubqueryExpression;
class BoundUnnestExpression;
class BoundWindowExpression;

//===--------------------------------------------------------------------===//
// TableRefs
//===--------------------------------------------------------------------===//
class BoundTableRef;

class BoundBaseTableRef;
class BoundCrossProductRef;
class BoundJoinRef;
class BoundSubqueryRef;
class BoundTableFunction;
class BoundEmptyTableRef;
class BoundExpressionListRef;
class BoundCTERef;

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/logical_tokens.hpp
//
//
//===----------------------------------------------------------------------===//



namespace duckdb {

class LogicalOperator;

class LogicalAggregate;
class LogicalAnyJoin;
class LogicalColumnDataGet;
class LogicalComparisonJoin;
class LogicalCopyToFile;
class LogicalCreate;
class LogicalCreateTable;
class LogicalCreateIndex;
class LogicalCreateTable;
class LogicalCrossProduct;
class LogicalCTERef;
class LogicalDelete;
class LogicalDelimGet;
class LogicalDelimJoin;
class LogicalDistinct;
class LogicalDummyScan;
class LogicalEmptyResult;
class LogicalExecute;
class LogicalExplain;
class LogicalExport;
class LogicalExpressionGet;
class LogicalFilter;
class LogicalGet;
class LogicalInsert;
class LogicalJoin;
class LogicalLimit;
class LogicalOrder;
class LogicalPragma;
class LogicalPrepare;
class LogicalProjection;
class LogicalRecursiveCTE;
class LogicalSetOperation;
class LogicalSample;
class LogicalShow;
class LogicalSimple;
class LogicalSet;
class LogicalTopN;
class LogicalUnnest;
class LogicalUpdate;
class LogicalWindow;

} // namespace duckdb


#include <functional>

namespace duckdb {
//! The LogicalOperatorVisitor is an abstract base class that implements the
//! Visitor pattern on LogicalOperator.
class LogicalOperatorVisitor {
public:
	virtual ~LogicalOperatorVisitor() {};

	virtual void VisitOperator(LogicalOperator &op);
	virtual void VisitExpression(unique_ptr<Expression> *expression);

	static void EnumerateExpressions(LogicalOperator &op,
	                                 const std::function<void(unique_ptr<Expression> *child)> &callback);

protected:
	//! Automatically calls the Visit method for LogicalOperator children of the current operator. Can be overloaded to
	//! change this behavior.
	void VisitOperatorChildren(LogicalOperator &op);
	//! Automatically calls the Visit method for Expression children of the current operator. Can be overloaded to
	//! change this behavior.
	void VisitOperatorExpressions(LogicalOperator &op);

	// The VisitExpressionChildren method is called at the end of every call to VisitExpression to recursively visit all
	// expressions in an expression tree. It can be overloaded to prevent automatically visiting the entire tree.
	virtual void VisitExpressionChildren(Expression &expression);

	virtual unique_ptr<Expression> VisitReplace(BoundAggregateExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundBetweenExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundCaseExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundCastExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundColumnRefExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundComparisonExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundConjunctionExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundConstantExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundDefaultExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundFunctionExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundOperatorExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundReferenceExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundSubqueryExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundParameterExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundWindowExpression &expr, unique_ptr<Expression> *expr_ptr);
	virtual unique_ptr<Expression> VisitReplace(BoundUnnestExpression &expr, unique_ptr<Expression> *expr_ptr);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/storage/statistics/distinct_statistics.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/hyperloglog.hpp
//
//
//===----------------------------------------------------------------------===//







// LICENSE_CHANGE_BEGIN
// The following code up to LICENSE_CHANGE_END is subject to THIRD PARTY LICENSE #1
// See the end of this file for a list

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// third_party/hyperloglog/hyperloglog.hpp
//
//
//===----------------------------------------------------------------------===//



#include <stdint.h>
#include <string.h>

namespace duckdb_hll {

/* Error codes */
#define HLL_C_OK  0
#define HLL_C_ERR -1

typedef struct {
	void *ptr;
} robj;

//! Create a new empty HyperLogLog object
robj *hll_create(void);
//! Convert hll from sparse to dense
int hllSparseToDense(robj *o);
//! Destroy the specified HyperLogLog object
void hll_destroy(robj *obj);
//! Add an element with the specified amount of bytes to the HyperLogLog. Returns C_ERR on failure, otherwise returns 0
//! if the cardinality did not change, and 1 otherwise.
int hll_add(robj *o, unsigned char *ele, size_t elesize);
//! Returns the estimated amount of unique elements seen by the HyperLogLog. Returns C_OK on success, or C_ERR on
//! failure.
int hll_count(robj *o, size_t *result);
//! Merge hll_count HyperLogLog objects into a single one. Returns NULL on failure, or the new HLL object on success.
robj *hll_merge(robj **hlls, size_t hll_count);
//! Get size (in bytes) of the HLL
uint64_t get_size();

uint64_t MurmurHash64A(const void *key, int len, unsigned int seed);

} // namespace duckdb_hll

namespace duckdb {

void AddToLogsInternal(UnifiedVectorFormat &vdata, idx_t count, uint64_t indices[], uint8_t counts[], void ***logs[],
                       const SelectionVector *log_sel);

void AddToSingleLogInternal(UnifiedVectorFormat &vdata, idx_t count, uint64_t indices[], uint8_t counts[], void *log);

} // namespace duckdb


// LICENSE_CHANGE_END


namespace duckdb {

enum class HLLStorageType { UNCOMPRESSED = 1 };

class FieldWriter;
class FieldReader;

//! The HyperLogLog class holds a HyperLogLog counter for approximate cardinality counting
class HyperLogLog {
public:
	HyperLogLog();
	~HyperLogLog();
	// implicit copying of HyperLogLog is not allowed
	HyperLogLog(const HyperLogLog &) = delete;

	//! Adds an element of the specified size to the HyperLogLog counter
	void Add(data_ptr_t element, idx_t size);
	//! Return the count of this HyperLogLog counter
	idx_t Count() const;
	//! Merge this HyperLogLog counter with another counter to create a new one
	unique_ptr<HyperLogLog> Merge(HyperLogLog &other);
	HyperLogLog *MergePointer(HyperLogLog &other);
	//! Merge a set of HyperLogLogs to create one big one
	static unique_ptr<HyperLogLog> Merge(HyperLogLog logs[], idx_t count);
	//! Get the size (in bytes) of a HLL
	static idx_t GetSize();
	//! Get pointer to the HLL
	data_ptr_t GetPtr() const;
	//! Get copy of the HLL
	unique_ptr<HyperLogLog> Copy();
	//! (De)Serialize the HLL
	void Serialize(FieldWriter &writer) const;
	static unique_ptr<HyperLogLog> Deserialize(FieldReader &reader);

public:
	//! Compute HLL hashes over vdata, and store them in 'hashes'
	//! Then, compute register indices and prefix lengths, and also store them in 'hashes' as a pair of uint32_t
	static void ProcessEntries(UnifiedVectorFormat &vdata, const LogicalType &type, uint64_t hashes[], uint8_t counts[],
	                           idx_t count);
	//! Add the indices and counts to the logs
	static void AddToLogs(UnifiedVectorFormat &vdata, idx_t count, uint64_t indices[], uint8_t counts[],
	                      HyperLogLog **logs[], const SelectionVector *log_sel);
	//! Add the indices and counts to THIS log
	void AddToLog(UnifiedVectorFormat &vdata, idx_t count, uint64_t indices[], uint8_t counts[]);

private:
	explicit HyperLogLog(void *hll);

	void *hll;
	mutex lock;
};
} // namespace duckdb



namespace duckdb {
class Serializer;
class Deserializer;
class Vector;

class DistinctStatistics : public BaseStatistics {
public:
	DistinctStatistics();
	explicit DistinctStatistics(unique_ptr<HyperLogLog> log, idx_t sample_count, idx_t total_count);

	//! The HLL of the table
	unique_ptr<HyperLogLog> log;
	//! How many values have been sampled into the HLL
	atomic<idx_t> sample_count;
	//! How many values have been inserted (before sampling)
	atomic<idx_t> total_count;

public:
	void Merge(const BaseStatistics &other) override;

	unique_ptr<BaseStatistics> Copy() const override;

	void Serialize(Serializer &serializer) const override;
	void Serialize(FieldWriter &writer) const override;

	static unique_ptr<DistinctStatistics> Deserialize(Deserializer &source);
	static unique_ptr<DistinctStatistics> Deserialize(FieldReader &reader);

	void Update(Vector &update, idx_t count, bool sample = true);
	void Update(UnifiedVectorFormat &update_data, const LogicalType &ptype, idx_t count, bool sample = true);

	string ToString() const override;
	idx_t GetCount() const;

private:
	//! For distinct statistics we sample the input to speed up insertions
	static constexpr const double SAMPLE_RATE = 0.1;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/table_filter.hpp
//
//
//===----------------------------------------------------------------------===//






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/filter_propagate_result.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class FilterPropagateResult : uint8_t {
	NO_PRUNING_POSSIBLE = 0,
	FILTER_ALWAYS_TRUE = 1,
	FILTER_ALWAYS_FALSE = 2,
	FILTER_TRUE_OR_NULL = 3,
	FILTER_FALSE_OR_NULL = 4
};

} // namespace duckdb


namespace duckdb {
class BaseStatistics;
class FieldWriter;
class FieldReader;

enum class TableFilterType : uint8_t {
	CONSTANT_COMPARISON = 0, // constant comparison (e.g. =C, >C, >=C, <C, <=C)
	IS_NULL = 1,
	IS_NOT_NULL = 2,
	CONJUNCTION_OR = 3,
	CONJUNCTION_AND = 4
};

//! TableFilter represents a filter pushed down into the table scan.
class TableFilter {
public:
	TableFilter(TableFilterType filter_type_p) : filter_type(filter_type_p) {
	}
	virtual ~TableFilter() {
	}

	TableFilterType filter_type;

public:
	//! Returns true if the statistics indicate that the segment can contain values that satisfy that filter
	virtual FilterPropagateResult CheckStatistics(BaseStatistics &stats) = 0;
	virtual string ToString(const string &column_name) = 0;
	virtual bool Equals(const TableFilter &other) const {
		return filter_type != other.filter_type;
	}

	void Serialize(Serializer &serializer) const;
	virtual void Serialize(FieldWriter &writer) const = 0;
	static unique_ptr<TableFilter> Deserialize(Deserializer &source);
};

class TableFilterSet {
public:
	unordered_map<idx_t, unique_ptr<TableFilter>> filters;

public:
	void PushFilter(idx_t table_index, unique_ptr<TableFilter> filter);

	bool Equals(TableFilterSet &other) {
		if (filters.size() != other.filters.size()) {
			return false;
		}
		for (auto &entry : filters) {
			auto other_entry = other.filters.find(entry.first);
			if (other_entry == other.filters.end()) {
				return false;
			}
			if (!entry.second->Equals(*other_entry->second)) {
				return false;
			}
		}
		return true;
	}
	static bool Equals(TableFilterSet *left, TableFilterSet *right) {
		if (left == right) {
			return true;
		}
		if (!left || !right) {
			return false;
		}
		return left->Equals(*right);
	}

	void Serialize(Serializer &serializer) const;
	static unique_ptr<TableFilterSet> Deserialize(Deserializer &source);
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_entry/table_catalog_entry.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/standard_entry.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {
class SchemaCatalogEntry;

//! A StandardEntry is a catalog entry that is a member of a schema
class StandardEntry : public CatalogEntry {
public:
	StandardEntry(CatalogType type, SchemaCatalogEntry *schema, Catalog *catalog, string name)
	    : CatalogEntry(type, catalog, name), schema(schema) {
	}
	~StandardEntry() override {
	}

	//! The schema the entry belongs to
	SchemaCatalogEntry *schema;
};
} // namespace duckdb



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/constraint.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

class Serializer;
class Deserializer;
class FieldWriter;
class FieldReader;

//===--------------------------------------------------------------------===//
// Constraint Types
//===--------------------------------------------------------------------===//
enum class ConstraintType : uint8_t {
	INVALID = 0,     // invalid constraint type
	NOT_NULL = 1,    // NOT NULL constraint
	CHECK = 2,       // CHECK constraint
	UNIQUE = 3,      // UNIQUE constraint
	FOREIGN_KEY = 4, // FOREIGN KEY constraint
};

enum class ForeignKeyType : uint8_t {
	FK_TYPE_PRIMARY_KEY_TABLE = 0,   // main table
	FK_TYPE_FOREIGN_KEY_TABLE = 1,   // referencing table
	FK_TYPE_SELF_REFERENCE_TABLE = 2 // self refrencing table
};

struct ForeignKeyInfo {
	ForeignKeyType type;
	string schema;
	//! if type is FK_TYPE_FOREIGN_KEY_TABLE, means main key table, if type is FK_TYPE_PRIMARY_KEY_TABLE, means foreign
	//! key table
	string table;
	//! The set of main key table's column's index
	vector<storage_t> pk_keys;
	//! The set of foreign key table's column's index
	vector<idx_t> fk_keys;
};

//! Constraint is the base class of any type of table constraint.
class Constraint {
public:
	DUCKDB_API explicit Constraint(ConstraintType type);
	DUCKDB_API virtual ~Constraint();

	ConstraintType type;

public:
	DUCKDB_API virtual string ToString() const = 0;
	DUCKDB_API void Print() const;

	DUCKDB_API virtual unique_ptr<Constraint> Copy() const = 0;
	//! Serializes a Constraint to a stand-alone binary blob
	DUCKDB_API void Serialize(Serializer &serializer) const;
	//! Serializes a Constraint to a stand-alone binary blob
	DUCKDB_API virtual void Serialize(FieldWriter &writer) const = 0;
	//! Deserializes a blob back into a Constraint
	DUCKDB_API static unique_ptr<Constraint> Deserialize(Deserializer &source);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/bound_constraint.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {
//! Bound equivalent of Constraint
class BoundConstraint {
public:
	explicit BoundConstraint(ConstraintType type) : type(type) {};
	virtual ~BoundConstraint() {
	}

	void Serialize(Serializer &serializer) const {
		serializer.Write(type);
	}

	static unique_ptr<BoundConstraint> Deserialize(Deserializer &source) {
		return make_unique<BoundConstraint>(source.Read<ConstraintType>());
	}

	ConstraintType type;
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/plan_serialization.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/logical_operator_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//===--------------------------------------------------------------------===//
// Logical Operator Types
//===--------------------------------------------------------------------===//
enum class LogicalOperatorType : uint8_t {
	LOGICAL_INVALID = 0,
	LOGICAL_PROJECTION = 1,
	LOGICAL_FILTER = 2,
	LOGICAL_AGGREGATE_AND_GROUP_BY = 3,
	LOGICAL_WINDOW = 4,
	LOGICAL_UNNEST = 5,
	LOGICAL_LIMIT = 6,
	LOGICAL_ORDER_BY = 7,
	LOGICAL_TOP_N = 8,
	LOGICAL_COPY_TO_FILE = 10,
	LOGICAL_DISTINCT = 11,
	LOGICAL_SAMPLE = 12,
	LOGICAL_LIMIT_PERCENT = 13,

	// -----------------------------
	// Data sources
	// -----------------------------
	LOGICAL_GET = 25,
	LOGICAL_CHUNK_GET = 26,
	LOGICAL_DELIM_GET = 27,
	LOGICAL_EXPRESSION_GET = 28,
	LOGICAL_DUMMY_SCAN = 29,
	LOGICAL_EMPTY_RESULT = 30,
	LOGICAL_CTE_REF = 31,
	// -----------------------------
	// Joins
	// -----------------------------
	LOGICAL_JOIN = 50,
	LOGICAL_DELIM_JOIN = 51,
	LOGICAL_COMPARISON_JOIN = 52,
	LOGICAL_ANY_JOIN = 53,
	LOGICAL_CROSS_PRODUCT = 54,
	// -----------------------------
	// SetOps
	// -----------------------------
	LOGICAL_UNION = 75,
	LOGICAL_EXCEPT = 76,
	LOGICAL_INTERSECT = 77,
	LOGICAL_RECURSIVE_CTE = 78,

	// -----------------------------
	// Updates
	// -----------------------------
	LOGICAL_INSERT = 100,
	LOGICAL_DELETE = 101,
	LOGICAL_UPDATE = 102,

	// -----------------------------
	// Schema
	// -----------------------------
	LOGICAL_ALTER = 125,
	LOGICAL_CREATE_TABLE = 126,
	LOGICAL_CREATE_INDEX = 127,
	LOGICAL_CREATE_SEQUENCE = 128,
	LOGICAL_CREATE_VIEW = 129,
	LOGICAL_CREATE_SCHEMA = 130,
	LOGICAL_CREATE_MACRO = 131,
	LOGICAL_DROP = 132,
	LOGICAL_PRAGMA = 133,
	LOGICAL_TRANSACTION = 134,
	LOGICAL_CREATE_TYPE = 135,

	// -----------------------------
	// Explain
	// -----------------------------
	LOGICAL_EXPLAIN = 150,

	// -----------------------------
	// Show
	// -----------------------------
	LOGICAL_SHOW = 160,

	// -----------------------------
	// Helpers
	// -----------------------------
	LOGICAL_PREPARE = 175,
	LOGICAL_EXECUTE = 176,
	LOGICAL_EXPORT = 177,
	LOGICAL_VACUUM = 178,
	LOGICAL_SET = 179,
	LOGICAL_LOAD = 180
};

DUCKDB_API string LogicalOperatorToString(LogicalOperatorType type);

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/bound_parameter_map.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

struct BoundParameterData;

using bound_parameter_map_t = unordered_map<idx_t, shared_ptr<BoundParameterData>>;

} // namespace duckdb


namespace duckdb {
class ClientContext;
class LogicalOperator;
struct BoundParameterData;

struct PlanDeserializationState {
	PlanDeserializationState(ClientContext &context);
	~PlanDeserializationState();

	ClientContext &context;
	bound_parameter_map_t parameter_data;
};

struct LogicalDeserializationState {
	LogicalDeserializationState(PlanDeserializationState &gstate, LogicalOperatorType type,
	                            vector<unique_ptr<LogicalOperator>> &children);

	PlanDeserializationState &gstate;
	LogicalOperatorType type;
	vector<unique_ptr<LogicalOperator>> &children;
};

struct ExpressionDeserializationState {
	ExpressionDeserializationState(PlanDeserializationState &gstate, ExpressionType type);

	PlanDeserializationState &gstate;
	ExpressionType type;
};

} // namespace duckdb


namespace duckdb {
class BaseStatistics;
class FieldWriter;
class FieldReader;
class ClientContext;

//!  The Expression class represents a bound Expression with a return type
class Expression : public BaseExpression {
public:
	Expression(ExpressionType type, ExpressionClass expression_class, LogicalType return_type);
	~Expression() override;

	//! The return type of the expression
	LogicalType return_type;
	//! Expression statistics (if any) - ONLY USED FOR VERIFICATION
	unique_ptr<BaseStatistics> verification_stats;

public:
	bool IsAggregate() const override;
	bool IsWindow() const override;
	bool HasSubquery() const override;
	bool IsScalar() const override;
	bool HasParameter() const override;
	virtual bool HasSideEffects() const;
	virtual bool PropagatesNullValues() const;
	virtual bool IsFoldable() const;

	hash_t Hash() const override;

	bool Equals(const BaseExpression *other) const override {
		if (!BaseExpression::Equals(other)) {
			return false;
		}
		return return_type == ((Expression *)other)->return_type;
	}

	static bool Equals(Expression *left, Expression *right) {
		return BaseExpression::Equals((BaseExpression *)left, (BaseExpression *)right);
	}
	//! Create a copy of this expression
	virtual unique_ptr<Expression> Copy() = 0;

	//! Serializes an Expression to a stand-alone binary blob
	void Serialize(Serializer &serializer) const;
	//! Serializes an Expression to a stand-alone binary blob
	virtual void Serialize(FieldWriter &writer) const = 0;

	//! Deserializes a blob back into an Expression [CAN THROW:
	//! SerializationException]
	static unique_ptr<Expression> Deserialize(Deserializer &source, PlanDeserializationState &state);

protected:
	//! Copy base Expression properties from another expression to this one,
	//! used in Copy method
	void CopyProperties(Expression &other) {
		type = other.type;
		expression_class = other.expression_class;
		alias = other.alias;
		return_type = other.return_type;
	}
};

} // namespace duckdb



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_entry/column_dependency_manager.hpp
//
//
//===----------------------------------------------------------------------===//






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/set.hpp
//
//
//===----------------------------------------------------------------------===//



#include <set>

namespace duckdb {
using std::set;
}

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/stack.hpp
//
//
//===----------------------------------------------------------------------===//



#include <stack>

namespace duckdb {
using std::stack;
}


namespace duckdb {

//! Dependency Manager local to a table, responsible for keeping track of generated column dependencies

class ColumnDependencyManager {
public:
	DUCKDB_API ColumnDependencyManager();
	DUCKDB_API ~ColumnDependencyManager();
	DUCKDB_API ColumnDependencyManager(ColumnDependencyManager &&other) = default;
	ColumnDependencyManager(const ColumnDependencyManager &other) = delete;

public:
	//! Get the bind order that ensures dependencies are resolved before dependents are
	stack<column_t> GetBindOrder(const vector<ColumnDefinition> &columns);

	//! Adds a connection between the dependent and its dependencies
	void AddGeneratedColumn(column_t index, const vector<column_t> &indices, bool root = true);
	//! Add a generated column from a column definition
	void AddGeneratedColumn(const ColumnDefinition &column, const case_insensitive_map_t<column_t> &name_map);

	//! Removes the column(s) and outputs the new column indices
	vector<column_t> RemoveColumn(column_t index, column_t column_amount);

	bool IsDependencyOf(column_t dependent, column_t dependency) const;
	bool HasDependencies(column_t index) const;
	const unordered_set<column_t> &GetDependencies(column_t index) const;

	bool HasDependents(column_t index) const;
	const unordered_set<column_t> &GetDependents(column_t index) const;

private:
	void RemoveStandardColumn(column_t index);
	void RemoveGeneratedColumn(column_t index);

	void AdjustSingle(column_t idx, idx_t offset);
	// Clean up the gaps created by a Remove operation
	vector<column_t> CleanupInternals(column_t column_amount);

private:
	//! A map of column dependency to generated column(s)
	unordered_map<column_t, unordered_set<column_t>> dependencies_map;
	//! A map of generated column name to (potentially generated)column dependencies
	unordered_map<column_t, unordered_set<column_t>> dependents_map;
	//! For resolve-order purposes, keep track of the 'direct' (not inherited) dependencies of a generated column
	unordered_map<column_t, unordered_set<column_t>> direct_dependencies;
	set<column_t> deleted_columns;
};

} // namespace duckdb


namespace duckdb {

class DataTable;
struct CreateTableInfo;
struct BoundCreateTableInfo;

struct RenameColumnInfo;
struct AddColumnInfo;
struct RemoveColumnInfo;
struct SetDefaultInfo;
struct ChangeColumnTypeInfo;
struct AlterForeignKeyInfo;
struct SetNotNullInfo;
struct DropNotNullInfo;

//! A table catalog entry
class TableCatalogEntry : public StandardEntry {
public:
	//! Create a real TableCatalogEntry and initialize storage for it
	TableCatalogEntry(Catalog *catalog, SchemaCatalogEntry *schema, BoundCreateTableInfo *info,
	                  std::shared_ptr<DataTable> inherited_storage = nullptr);

	//! A reference to the underlying storage unit used for this table
	std::shared_ptr<DataTable> storage;
	//! A list of columns that are part of this table
	vector<ColumnDefinition> columns;
	//! A list of constraints that are part of this table
	vector<unique_ptr<Constraint>> constraints;
	//! A list of constraints that are part of this table
	vector<unique_ptr<BoundConstraint>> bound_constraints;
	ColumnDependencyManager column_dependency_manager;
	//! A map of column name to column index
	case_insensitive_map_t<column_t> name_map;

public:
	//! For debugging purposes, count how many columns are STANDARD
	idx_t StandardColumnCount() const;
	unique_ptr<CatalogEntry> AlterEntry(ClientContext &context, AlterInfo *info) override;
	//! Returns whether or not a column with the given name exists
	DUCKDB_API bool ColumnExists(const string &name);
	//! Returns a reference to the column of the specified name. Throws an
	//! exception if the column does not exist.
	ColumnDefinition &GetColumn(const string &name);
	//! Returns a list of types of the table, excluding generated columns
	vector<LogicalType> GetTypes();
	string ToSQL() override;

	//! Get statistics of a column (physical or virtual) within the table
	unique_ptr<BaseStatistics> GetStatistics(ClientContext &context, column_t column_id);

	//! Serialize the meta information of the TableCatalogEntry a serializer
	virtual void Serialize(Serializer &serializer);
	//! Deserializes to a CreateTableInfo
	static unique_ptr<CreateTableInfo> Deserialize(Deserializer &source, ClientContext &context);

	unique_ptr<CatalogEntry> Copy(ClientContext &context) override;

	void SetAsRoot() override;

	void CommitAlter(AlterInfo &info);
	void CommitDrop();

	//! Returns the column index of the specified column name.
	//! If the column does not exist:
	//! If if_column_exists is true, returns DConstants::INVALID_INDEX
	//! If if_column_exists is false, throws an exception
	column_t GetColumnIndex(string &name, bool if_exists = false);

private:
	const string &GetColumnName(column_t index);
	unique_ptr<CatalogEntry> RenameColumn(ClientContext &context, RenameColumnInfo &info);
	unique_ptr<CatalogEntry> AddColumn(ClientContext &context, AddColumnInfo &info);
	unique_ptr<CatalogEntry> RemoveColumn(ClientContext &context, RemoveColumnInfo &info);
	unique_ptr<CatalogEntry> SetDefault(ClientContext &context, SetDefaultInfo &info);
	unique_ptr<CatalogEntry> ChangeColumnType(ClientContext &context, ChangeColumnTypeInfo &info);
	unique_ptr<CatalogEntry> SetNotNull(ClientContext &context, SetNotNullInfo &info);
	unique_ptr<CatalogEntry> DropNotNull(ClientContext &context, DropNotNullInfo &info);
	unique_ptr<CatalogEntry> AddForeignKeyConstraint(ClientContext &context, AlterForeignKeyInfo &info);
	unique_ptr<CatalogEntry> DropForeignKeyConstraint(ClientContext &context, AlterForeignKeyInfo &info);
};
} // namespace duckdb


namespace duckdb {

class EstimatedProperties {
public:
	EstimatedProperties(double cardinality, double cost) : cardinality(cardinality), cost(cost) {};
	EstimatedProperties() : cardinality(0), cost(0) {};

	double GetCardinality();
	double GetCost();
	void SetCost(double new_cost);
	void SetCardinality(double cardinality);

private:
	double cardinality;
	double cost;

public:
	unique_ptr<EstimatedProperties> Copy();
};
} // namespace duckdb





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/column_binding.hpp
//
//
//===----------------------------------------------------------------------===//




#include <functional>

namespace duckdb {

struct ColumnBinding {
	idx_t table_index;
	idx_t column_index;

	ColumnBinding() : table_index(DConstants::INVALID_INDEX), column_index(DConstants::INVALID_INDEX) {
	}
	ColumnBinding(idx_t table, idx_t column) : table_index(table), column_index(column) {
	}

	bool operator==(const ColumnBinding &rhs) const {
		return table_index == rhs.table_index && column_index == rhs.column_index;
	}
};

} // namespace duckdb



#include <functional>
#include <algorithm>

namespace duckdb {

class FieldWriter;
class FieldReader;

//! The current version of the plan serialization format. Exposed via by @Serializer & @Deserializer
//! to be used by various Operator to know what format to read and write.
extern const uint64_t PLAN_SERIALIZATION_VERSION;

//! LogicalOperator is the base class of the logical operators present in the
//! logical query tree
class LogicalOperator {
public:
	explicit LogicalOperator(LogicalOperatorType type);
	LogicalOperator(LogicalOperatorType type, vector<unique_ptr<Expression>> expressions);
	virtual ~LogicalOperator();

	//! The type of the logical operator
	LogicalOperatorType type;
	//! The set of children of the operator
	vector<unique_ptr<LogicalOperator>> children;
	//! The set of expressions contained within the operator, if any
	vector<unique_ptr<Expression>> expressions;
	//! The types returned by this logical operator. Set by calling LogicalOperator::ResolveTypes.
	vector<LogicalType> types;
	//! Estimated Cardinality
	idx_t estimated_cardinality;
	bool has_estimated_cardinality;

	unique_ptr<EstimatedProperties> estimated_props;

public:
	virtual vector<ColumnBinding> GetColumnBindings();
	static vector<ColumnBinding> GenerateColumnBindings(idx_t table_idx, idx_t column_count);
	static vector<LogicalType> MapTypes(const vector<LogicalType> &types, const vector<idx_t> &projection_map);
	static vector<ColumnBinding> MapBindings(const vector<ColumnBinding> &types, const vector<idx_t> &projection_map);

	//! Resolve the types of the logical operator and its children
	void ResolveOperatorTypes();

	virtual string GetName() const;
	virtual string ParamsToString() const;
	virtual string ToString() const;
	DUCKDB_API void Print();
	//! Debug method: verify that the integrity of expressions & child nodes are maintained
	virtual void Verify(ClientContext &context);

	void AddChild(unique_ptr<LogicalOperator> child);
	virtual idx_t EstimateCardinality(ClientContext &context);

	//! Serializes a LogicalOperator to a stand-alone binary blob
	void Serialize(Serializer &serializer) const;
	//! Serializes an LogicalOperator to a stand-alone binary blob
	virtual void Serialize(FieldWriter &writer) const = 0;

	static unique_ptr<LogicalOperator> Deserialize(Deserializer &deserializer, PlanDeserializationState &state);

	virtual bool RequireOptimizer() const {
		return true;
	}

protected:
	//! Resolve types for this specific operator
	virtual void ResolveTypes() = 0;
};
} // namespace duckdb


namespace duckdb {

struct BoundStatement {
	unique_ptr<LogicalOperator> plan;
	vector<LogicalType> types;
	vector<string> names;
};

} // namespace duckdb




namespace duckdb {

//! A ResultModifier
class BoundResultModifier {
public:
	explicit BoundResultModifier(ResultModifierType type);
	virtual ~BoundResultModifier();

	ResultModifierType type;
};

struct BoundOrderByNode {
public:
	BoundOrderByNode(OrderType type, OrderByNullType null_order, unique_ptr<Expression> expression);
	BoundOrderByNode(OrderType type, OrderByNullType null_order, unique_ptr<Expression> expression,
	                 unique_ptr<BaseStatistics> stats);

	OrderType type;
	OrderByNullType null_order;
	unique_ptr<Expression> expression;
	unique_ptr<BaseStatistics> stats;

public:
	BoundOrderByNode Copy() const;
	string ToString() const;

	void Serialize(Serializer &serializer) const;
	static BoundOrderByNode Deserialize(Deserializer &source, PlanDeserializationState &state);
};

class BoundLimitModifier : public BoundResultModifier {
public:
	BoundLimitModifier();

	//! LIMIT
	int64_t limit_val = NumericLimits<int64_t>::Maximum();
	//! OFFSET
	int64_t offset_val = 0;
	//! Expression in case limit is not constant
	unique_ptr<Expression> limit;
	//! Expression in case limit is not constant
	unique_ptr<Expression> offset;
};

class BoundOrderModifier : public BoundResultModifier {
public:
	BoundOrderModifier();

	//! List of order nodes
	vector<BoundOrderByNode> orders;
};

class BoundDistinctModifier : public BoundResultModifier {
public:
	BoundDistinctModifier();

	//! list of distinct on targets (if any)
	vector<unique_ptr<Expression>> target_distincts;
};

class BoundLimitPercentModifier : public BoundResultModifier {
public:
	BoundLimitPercentModifier();

	//! LIMIT %
	double limit_percent = 100.0;
	//! OFFSET
	int64_t offset_val = 0;
	//! Expression in case limit is not constant
	unique_ptr<Expression> limit;
	//! Expression in case limit is not constant
	unique_ptr<Expression> offset;
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/vector_operations/aggregate_executor.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {

struct AggregateInputData;

typedef std::pair<idx_t, idx_t> FrameBounds;

class AggregateExecutor {
private:
	template <class STATE_TYPE, class OP>
	static inline void NullaryFlatLoop(STATE_TYPE **__restrict states, AggregateInputData &aggr_input_data,
	                                   idx_t count) {
		for (idx_t i = 0; i < count; i++) {
			OP::template Operation<STATE_TYPE, OP>(states[i], aggr_input_data, i);
		}
	}

	template <class STATE_TYPE, class OP>
	static inline void NullaryScatterLoop(STATE_TYPE **__restrict states, AggregateInputData &aggr_input_data,
	                                      const SelectionVector &ssel, idx_t count) {

		for (idx_t i = 0; i < count; i++) {
			auto sidx = ssel.get_index(i);
			OP::template Operation<STATE_TYPE, OP>(states[sidx], aggr_input_data, sidx);
		}
	}

	template <class STATE_TYPE, class INPUT_TYPE, class OP>
	static inline void UnaryFlatLoop(INPUT_TYPE *__restrict idata, AggregateInputData &aggr_input_data,
	                                 STATE_TYPE **__restrict states, ValidityMask &mask, idx_t count) {
		if (!mask.AllValid()) {
			idx_t base_idx = 0;
			auto entry_count = ValidityMask::EntryCount(count);
			for (idx_t entry_idx = 0; entry_idx < entry_count; entry_idx++) {
				auto validity_entry = mask.GetValidityEntry(entry_idx);
				idx_t next = MinValue<idx_t>(base_idx + ValidityMask::BITS_PER_VALUE, count);
				if (!OP::IgnoreNull() || ValidityMask::AllValid(validity_entry)) {
					// all valid: perform operation
					for (; base_idx < next; base_idx++) {
						OP::template Operation<INPUT_TYPE, STATE_TYPE, OP>(states[base_idx], aggr_input_data, idata,
						                                                   mask, base_idx);
					}
				} else if (ValidityMask::NoneValid(validity_entry)) {
					// nothing valid: skip all
					base_idx = next;
					continue;
				} else {
					// partially valid: need to check individual elements for validity
					idx_t start = base_idx;
					for (; base_idx < next; base_idx++) {
						if (ValidityMask::RowIsValid(validity_entry, base_idx - start)) {
							OP::template Operation<INPUT_TYPE, STATE_TYPE, OP>(states[base_idx], aggr_input_data, idata,
							                                                   mask, base_idx);
						}
					}
				}
			}
		} else {
			for (idx_t i = 0; i < count; i++) {
				OP::template Operation<INPUT_TYPE, STATE_TYPE, OP>(states[i], aggr_input_data, idata, mask, i);
			}
		}
	}

	template <class STATE_TYPE, class INPUT_TYPE, class OP>
	static inline void UnaryScatterLoop(INPUT_TYPE *__restrict idata, AggregateInputData &aggr_input_data,
	                                    STATE_TYPE **__restrict states, const SelectionVector &isel,
	                                    const SelectionVector &ssel, ValidityMask &mask, idx_t count) {
		if (OP::IgnoreNull() && !mask.AllValid()) {
			// potential NULL values and NULL values are ignored
			for (idx_t i = 0; i < count; i++) {
				auto idx = isel.get_index(i);
				auto sidx = ssel.get_index(i);
				if (mask.RowIsValid(idx)) {
					OP::template Operation<INPUT_TYPE, STATE_TYPE, OP>(states[sidx], aggr_input_data, idata, mask, idx);
				}
			}
		} else {
			// quick path: no NULL values or NULL values are not ignored
			for (idx_t i = 0; i < count; i++) {
				auto idx = isel.get_index(i);
				auto sidx = ssel.get_index(i);
				OP::template Operation<INPUT_TYPE, STATE_TYPE, OP>(states[sidx], aggr_input_data, idata, mask, idx);
			}
		}
	}

	template <class STATE_TYPE, class INPUT_TYPE, class OP>
	static inline void UnaryFlatUpdateLoop(INPUT_TYPE *__restrict idata, AggregateInputData &aggr_input_data,
	                                       STATE_TYPE *__restrict state, idx_t count, ValidityMask &mask) {
		idx_t base_idx = 0;
		auto entry_count = ValidityMask::EntryCount(count);
		for (idx_t entry_idx = 0; entry_idx < entry_count; entry_idx++) {
			auto validity_entry = mask.GetValidityEntry(entry_idx);
			idx_t next = MinValue<idx_t>(base_idx + ValidityMask::BITS_PER_VALUE, count);
			if (!OP::IgnoreNull() || ValidityMask::AllValid(validity_entry)) {
				// all valid: perform operation
				for (; base_idx < next; base_idx++) {
					OP::template Operation<INPUT_TYPE, STATE_TYPE, OP>(state, aggr_input_data, idata, mask, base_idx);
				}
			} else if (ValidityMask::NoneValid(validity_entry)) {
				// nothing valid: skip all
				base_idx = next;
				continue;
			} else {
				// partially valid: need to check individual elements for validity
				idx_t start = base_idx;
				for (; base_idx < next; base_idx++) {
					if (ValidityMask::RowIsValid(validity_entry, base_idx - start)) {
						OP::template Operation<INPUT_TYPE, STATE_TYPE, OP>(state, aggr_input_data, idata, mask,
						                                                   base_idx);
					}
				}
			}
		}
	}

	template <class STATE_TYPE, class INPUT_TYPE, class OP>
	static inline void UnaryUpdateLoop(INPUT_TYPE *__restrict idata, AggregateInputData &aggr_input_data,
	                                   STATE_TYPE *__restrict state, idx_t count, ValidityMask &mask,
	                                   const SelectionVector &__restrict sel_vector) {
		if (OP::IgnoreNull() && !mask.AllValid()) {
			// potential NULL values and NULL values are ignored
			for (idx_t i = 0; i < count; i++) {
				auto idx = sel_vector.get_index(i);
				if (mask.RowIsValid(idx)) {
					OP::template Operation<INPUT_TYPE, STATE_TYPE, OP>(state, aggr_input_data, idata, mask, idx);
				}
			}
		} else {
			// quick path: no NULL values or NULL values are not ignored
			for (idx_t i = 0; i < count; i++) {
				auto idx = sel_vector.get_index(i);
				OP::template Operation<INPUT_TYPE, STATE_TYPE, OP>(state, aggr_input_data, idata, mask, idx);
			}
		}
	}

	template <class STATE_TYPE, class A_TYPE, class B_TYPE, class OP>
	static inline void BinaryScatterLoop(A_TYPE *__restrict adata, AggregateInputData &aggr_input_data,
	                                     B_TYPE *__restrict bdata, STATE_TYPE **__restrict states, idx_t count,
	                                     const SelectionVector &asel, const SelectionVector &bsel,
	                                     const SelectionVector &ssel, ValidityMask &avalidity,
	                                     ValidityMask &bvalidity) {
		if (OP::IgnoreNull() && (!avalidity.AllValid() || !bvalidity.AllValid())) {
			// potential NULL values and NULL values are ignored
			for (idx_t i = 0; i < count; i++) {
				auto aidx = asel.get_index(i);
				auto bidx = bsel.get_index(i);
				auto sidx = ssel.get_index(i);
				if (avalidity.RowIsValid(aidx) && bvalidity.RowIsValid(bidx)) {
					OP::template Operation<A_TYPE, B_TYPE, STATE_TYPE, OP>(states[sidx], aggr_input_data, adata, bdata,
					                                                       avalidity, bvalidity, aidx, bidx);
				}
			}
		} else {
			// quick path: no NULL values or NULL values are not ignored
			for (idx_t i = 0; i < count; i++) {
				auto aidx = asel.get_index(i);
				auto bidx = bsel.get_index(i);
				auto sidx = ssel.get_index(i);
				OP::template Operation<A_TYPE, B_TYPE, STATE_TYPE, OP>(states[sidx], aggr_input_data, adata, bdata,
				                                                       avalidity, bvalidity, aidx, bidx);
			}
		}
	}

	template <class STATE_TYPE, class A_TYPE, class B_TYPE, class OP>
	static inline void BinaryUpdateLoop(A_TYPE *__restrict adata, AggregateInputData &aggr_input_data,
	                                    B_TYPE *__restrict bdata, STATE_TYPE *__restrict state, idx_t count,
	                                    const SelectionVector &asel, const SelectionVector &bsel,
	                                    ValidityMask &avalidity, ValidityMask &bvalidity) {
		if (OP::IgnoreNull() && (!avalidity.AllValid() || !bvalidity.AllValid())) {
			// potential NULL values and NULL values are ignored
			for (idx_t i = 0; i < count; i++) {
				auto aidx = asel.get_index(i);
				auto bidx = bsel.get_index(i);
				if (avalidity.RowIsValid(aidx) && bvalidity.RowIsValid(bidx)) {
					OP::template Operation<A_TYPE, B_TYPE, STATE_TYPE, OP>(state, aggr_input_data, adata, bdata,
					                                                       avalidity, bvalidity, aidx, bidx);
				}
			}
		} else {
			// quick path: no NULL values or NULL values are not ignored
			for (idx_t i = 0; i < count; i++) {
				auto aidx = asel.get_index(i);
				auto bidx = bsel.get_index(i);
				OP::template Operation<A_TYPE, B_TYPE, STATE_TYPE, OP>(state, aggr_input_data, adata, bdata, avalidity,
				                                                       bvalidity, aidx, bidx);
			}
		}
	}

public:
	template <class STATE_TYPE, class OP>
	static void NullaryScatter(Vector &states, AggregateInputData &aggr_input_data, idx_t count) {
		if (states.GetVectorType() == VectorType::CONSTANT_VECTOR) {
			auto sdata = ConstantVector::GetData<STATE_TYPE *>(states);
			OP::template ConstantOperation<STATE_TYPE, OP>(*sdata, aggr_input_data, count);
		} else if (states.GetVectorType() == VectorType::FLAT_VECTOR) {
			auto sdata = FlatVector::GetData<STATE_TYPE *>(states);
			NullaryFlatLoop<STATE_TYPE, OP>(sdata, aggr_input_data, count);
		} else {
			UnifiedVectorFormat sdata;
			states.ToUnifiedFormat(count, sdata);
			NullaryScatterLoop<STATE_TYPE, OP>((STATE_TYPE **)sdata.data, aggr_input_data, *sdata.sel, count);
		}
	}

	template <class STATE_TYPE, class OP>
	static void NullaryUpdate(data_ptr_t state, AggregateInputData &aggr_input_data, idx_t count) {
		OP::template ConstantOperation<STATE_TYPE, OP>((STATE_TYPE *)state, aggr_input_data, count);
	}

	template <class STATE_TYPE, class INPUT_TYPE, class OP>
	static void UnaryScatter(Vector &input, Vector &states, AggregateInputData &aggr_input_data, idx_t count) {
		if (input.GetVectorType() == VectorType::CONSTANT_VECTOR &&
		    states.GetVectorType() == VectorType::CONSTANT_VECTOR) {
			if (OP::IgnoreNull() && ConstantVector::IsNull(input)) {
				// constant NULL input in function that ignores NULL values
				return;
			}
			// regular constant: get first state
			auto idata = ConstantVector::GetData<INPUT_TYPE>(input);
			auto sdata = ConstantVector::GetData<STATE_TYPE *>(states);
			OP::template ConstantOperation<INPUT_TYPE, STATE_TYPE, OP>(*sdata, aggr_input_data, idata,
			                                                           ConstantVector::Validity(input), count);
		} else if (input.GetVectorType() == VectorType::FLAT_VECTOR &&
		           states.GetVectorType() == VectorType::FLAT_VECTOR) {
			auto idata = FlatVector::GetData<INPUT_TYPE>(input);
			auto sdata = FlatVector::GetData<STATE_TYPE *>(states);
			UnaryFlatLoop<STATE_TYPE, INPUT_TYPE, OP>(idata, aggr_input_data, sdata, FlatVector::Validity(input),
			                                          count);
		} else {
			UnifiedVectorFormat idata, sdata;
			input.ToUnifiedFormat(count, idata);
			states.ToUnifiedFormat(count, sdata);
			UnaryScatterLoop<STATE_TYPE, INPUT_TYPE, OP>((INPUT_TYPE *)idata.data, aggr_input_data,
			                                             (STATE_TYPE **)sdata.data, *idata.sel, *sdata.sel,
			                                             idata.validity, count);
		}
	}

	template <class STATE_TYPE, class INPUT_TYPE, class OP>
	static void UnaryUpdate(Vector &input, AggregateInputData &aggr_input_data, data_ptr_t state, idx_t count) {
		switch (input.GetVectorType()) {
		case VectorType::CONSTANT_VECTOR: {
			if (OP::IgnoreNull() && ConstantVector::IsNull(input)) {
				return;
			}
			auto idata = ConstantVector::GetData<INPUT_TYPE>(input);
			OP::template ConstantOperation<INPUT_TYPE, STATE_TYPE, OP>((STATE_TYPE *)state, aggr_input_data, idata,
			                                                           ConstantVector::Validity(input), count);
			break;
		}
		case VectorType::FLAT_VECTOR: {
			auto idata = FlatVector::GetData<INPUT_TYPE>(input);
			UnaryFlatUpdateLoop<STATE_TYPE, INPUT_TYPE, OP>(idata, aggr_input_data, (STATE_TYPE *)state, count,
			                                                FlatVector::Validity(input));
			break;
		}
		default: {
			UnifiedVectorFormat idata;
			input.ToUnifiedFormat(count, idata);
			UnaryUpdateLoop<STATE_TYPE, INPUT_TYPE, OP>((INPUT_TYPE *)idata.data, aggr_input_data, (STATE_TYPE *)state,
			                                            count, idata.validity, *idata.sel);
			break;
		}
		}
	}

	template <class STATE_TYPE, class A_TYPE, class B_TYPE, class OP>
	static void BinaryScatter(AggregateInputData &aggr_input_data, Vector &a, Vector &b, Vector &states, idx_t count) {
		UnifiedVectorFormat adata, bdata, sdata;

		a.ToUnifiedFormat(count, adata);
		b.ToUnifiedFormat(count, bdata);
		states.ToUnifiedFormat(count, sdata);

		BinaryScatterLoop<STATE_TYPE, A_TYPE, B_TYPE, OP>((A_TYPE *)adata.data, aggr_input_data, (B_TYPE *)bdata.data,
		                                                  (STATE_TYPE **)sdata.data, count, *adata.sel, *bdata.sel,
		                                                  *sdata.sel, adata.validity, bdata.validity);
	}

	template <class STATE_TYPE, class A_TYPE, class B_TYPE, class OP>
	static void BinaryUpdate(AggregateInputData &aggr_input_data, Vector &a, Vector &b, data_ptr_t state, idx_t count) {
		UnifiedVectorFormat adata, bdata;

		a.ToUnifiedFormat(count, adata);
		b.ToUnifiedFormat(count, bdata);

		BinaryUpdateLoop<STATE_TYPE, A_TYPE, B_TYPE, OP>((A_TYPE *)adata.data, aggr_input_data, (B_TYPE *)bdata.data,
		                                                 (STATE_TYPE *)state, count, *adata.sel, *bdata.sel,
		                                                 adata.validity, bdata.validity);
	}

	template <class STATE_TYPE, class OP>
	static void Combine(Vector &source, Vector &target, AggregateInputData &aggr_input_data, idx_t count) {
		D_ASSERT(source.GetType().id() == LogicalTypeId::POINTER && target.GetType().id() == LogicalTypeId::POINTER);
		auto sdata = FlatVector::GetData<const STATE_TYPE *>(source);
		auto tdata = FlatVector::GetData<STATE_TYPE *>(target);

		for (idx_t i = 0; i < count; i++) {
			OP::template Combine<STATE_TYPE, OP>(*sdata[i], tdata[i], aggr_input_data);
		}
	}

	template <class STATE_TYPE, class RESULT_TYPE, class OP>
	static void Finalize(Vector &states, AggregateInputData &aggr_input_data, Vector &result, idx_t count,
	                     idx_t offset) {
		if (states.GetVectorType() == VectorType::CONSTANT_VECTOR) {
			result.SetVectorType(VectorType::CONSTANT_VECTOR);

			auto sdata = ConstantVector::GetData<STATE_TYPE *>(states);
			auto rdata = ConstantVector::GetData<RESULT_TYPE>(result);
			OP::template Finalize<RESULT_TYPE, STATE_TYPE>(result, aggr_input_data, *sdata, rdata,
			                                               ConstantVector::Validity(result), 0);
		} else {
			D_ASSERT(states.GetVectorType() == VectorType::FLAT_VECTOR);
			result.SetVectorType(VectorType::FLAT_VECTOR);

			auto sdata = FlatVector::GetData<STATE_TYPE *>(states);
			auto rdata = FlatVector::GetData<RESULT_TYPE>(result);
			for (idx_t i = 0; i < count; i++) {
				OP::template Finalize<RESULT_TYPE, STATE_TYPE>(result, aggr_input_data, sdata[i], rdata,
				                                               FlatVector::Validity(result), i + offset);
			}
		}
	}

	template <class STATE, class INPUT_TYPE, class RESULT_TYPE, class OP>
	static void UnaryWindow(Vector &input, const ValidityMask &ifilter, AggregateInputData &aggr_input_data,
	                        data_ptr_t state, const FrameBounds &frame, const FrameBounds &prev, Vector &result,
	                        idx_t rid, idx_t bias) {

		auto idata = FlatVector::GetData<const INPUT_TYPE>(input) - bias;
		const auto &ivalid = FlatVector::Validity(input);
		OP::template Window<STATE, INPUT_TYPE, RESULT_TYPE>(idata, ifilter, ivalid, aggr_input_data, (STATE *)state,
		                                                    frame, prev, result, rid, bias);
	}

	template <class STATE_TYPE, class OP>
	static void Destroy(Vector &states, idx_t count) {
		auto sdata = FlatVector::GetData<STATE_TYPE *>(states);
		for (idx_t i = 0; i < count; i++) {
			OP::template Destroy<STATE_TYPE>(sdata[i]);
		}
	}
};

} // namespace duckdb


namespace duckdb {

class BoundAggregateExpression;

struct AggregateInputData {
	AggregateInputData(FunctionData *bind_data_p, Allocator &allocator_p)
	    : bind_data(bind_data_p), allocator(allocator_p) {};
	FunctionData *bind_data;
	Allocator &allocator;
};

//! The type used for sizing hashed aggregate function states
typedef idx_t (*aggregate_size_t)();
//! The type used for initializing hashed aggregate function states
typedef void (*aggregate_initialize_t)(data_ptr_t state);
//! The type used for updating hashed aggregate functions
typedef void (*aggregate_update_t)(Vector inputs[], AggregateInputData &aggr_input_data, idx_t input_count,
                                   Vector &state, idx_t count);
//! The type used for combining hashed aggregate states
typedef void (*aggregate_combine_t)(Vector &state, Vector &combined, AggregateInputData &aggr_input_data, idx_t count);
//! The type used for finalizing hashed aggregate function payloads
typedef void (*aggregate_finalize_t)(Vector &state, AggregateInputData &aggr_input_data, Vector &result, idx_t count,
                                     idx_t offset);
//! The type used for propagating statistics in aggregate functions (optional)
typedef unique_ptr<BaseStatistics> (*aggregate_statistics_t)(ClientContext &context, BoundAggregateExpression &expr,
                                                             FunctionData *bind_data,
                                                             vector<unique_ptr<BaseStatistics>> &child_stats,
                                                             NodeStatistics *node_stats);
//! Binds the scalar function and creates the function data
typedef unique_ptr<FunctionData> (*bind_aggregate_function_t)(ClientContext &context, AggregateFunction &function,
                                                              vector<unique_ptr<Expression>> &arguments);
//! The type used for the aggregate destructor method. NOTE: this method is used in destructors and MAY NOT throw.
typedef void (*aggregate_destructor_t)(Vector &state, idx_t count);

//! The type used for updating simple (non-grouped) aggregate functions
typedef void (*aggregate_simple_update_t)(Vector inputs[], AggregateInputData &aggr_input_data, idx_t input_count,
                                          data_ptr_t state, idx_t count);

//! The type used for updating complex windowed aggregate functions (optional)
typedef std::pair<idx_t, idx_t> FrameBounds;
typedef void (*aggregate_window_t)(Vector inputs[], const ValidityMask &filter_mask,
                                   AggregateInputData &aggr_input_data, idx_t input_count, data_ptr_t state,
                                   const FrameBounds &frame, const FrameBounds &prev, Vector &result, idx_t rid,
                                   idx_t bias);

typedef void (*aggregate_serialize_t)(FieldWriter &writer, const FunctionData *bind_data,
                                      const AggregateFunction &function);
typedef unique_ptr<FunctionData> (*aggregate_deserialize_t)(ClientContext &context, FieldReader &reader,
                                                            AggregateFunction &function);

class AggregateFunction : public BaseScalarFunction {
public:
	DUCKDB_API
	AggregateFunction(const string &name, const vector<LogicalType> &arguments, const LogicalType &return_type,
	                  aggregate_size_t state_size, aggregate_initialize_t initialize, aggregate_update_t update,
	                  aggregate_combine_t combine, aggregate_finalize_t finalize,
	                  FunctionNullHandling null_handling = FunctionNullHandling::DEFAULT_NULL_HANDLING,
	                  aggregate_simple_update_t simple_update = nullptr, bind_aggregate_function_t bind = nullptr,
	                  aggregate_destructor_t destructor = nullptr, aggregate_statistics_t statistics = nullptr,
	                  aggregate_window_t window = nullptr, aggregate_serialize_t serialize = nullptr,
	                  aggregate_deserialize_t deserialize = nullptr)
	    : BaseScalarFunction(name, arguments, return_type, FunctionSideEffects::NO_SIDE_EFFECTS,
	                         LogicalType(LogicalTypeId::INVALID), null_handling),
	      state_size(state_size), initialize(initialize), update(update), combine(combine), finalize(finalize),
	      simple_update(simple_update), window(window), bind(bind), destructor(destructor), statistics(statistics),
	      serialize(serialize), deserialize(deserialize) {
	}

	DUCKDB_API
	AggregateFunction(const string &name, const vector<LogicalType> &arguments, const LogicalType &return_type,
	                  aggregate_size_t state_size, aggregate_initialize_t initialize, aggregate_update_t update,
	                  aggregate_combine_t combine, aggregate_finalize_t finalize,
	                  aggregate_simple_update_t simple_update = nullptr, bind_aggregate_function_t bind = nullptr,
	                  aggregate_destructor_t destructor = nullptr, aggregate_statistics_t statistics = nullptr,
	                  aggregate_window_t window = nullptr, aggregate_serialize_t serialize = nullptr,
	                  aggregate_deserialize_t deserialize = nullptr)
	    : BaseScalarFunction(name, arguments, return_type, FunctionSideEffects::NO_SIDE_EFFECTS,
	                         LogicalType(LogicalTypeId::INVALID)),
	      state_size(state_size), initialize(initialize), update(update), combine(combine), finalize(finalize),
	      simple_update(simple_update), window(window), bind(bind), destructor(destructor), statistics(statistics),
	      serialize(serialize), deserialize(deserialize) {
	}

	DUCKDB_API AggregateFunction(const vector<LogicalType> &arguments, const LogicalType &return_type,
	                             aggregate_size_t state_size, aggregate_initialize_t initialize,
	                             aggregate_update_t update, aggregate_combine_t combine, aggregate_finalize_t finalize,
	                             FunctionNullHandling null_handling = FunctionNullHandling::DEFAULT_NULL_HANDLING,
	                             aggregate_simple_update_t simple_update = nullptr,
	                             bind_aggregate_function_t bind = nullptr, aggregate_destructor_t destructor = nullptr,
	                             aggregate_statistics_t statistics = nullptr, aggregate_window_t window = nullptr,
	                             aggregate_serialize_t serialize = nullptr,
	                             aggregate_deserialize_t deserialize = nullptr)
	    : AggregateFunction(string(), arguments, return_type, state_size, initialize, update, combine, finalize,
	                        null_handling, simple_update, bind, destructor, statistics, window, serialize,
	                        deserialize) {
	}

	DUCKDB_API
	AggregateFunction(const vector<LogicalType> &arguments, const LogicalType &return_type, aggregate_size_t state_size,
	                  aggregate_initialize_t initialize, aggregate_update_t update, aggregate_combine_t combine,
	                  aggregate_finalize_t finalize, aggregate_simple_update_t simple_update = nullptr,
	                  bind_aggregate_function_t bind = nullptr, aggregate_destructor_t destructor = nullptr,
	                  aggregate_statistics_t statistics = nullptr, aggregate_window_t window = nullptr,
	                  aggregate_serialize_t serialize = nullptr, aggregate_deserialize_t deserialize = nullptr)
	    : AggregateFunction(string(), arguments, return_type, state_size, initialize, update, combine, finalize,
	                        FunctionNullHandling::DEFAULT_NULL_HANDLING, simple_update, bind, destructor, statistics,
	                        window, serialize, deserialize) {
	}
	//! The hashed aggregate state sizing function
	aggregate_size_t state_size;
	//! The hashed aggregate state initialization function
	aggregate_initialize_t initialize;
	//! The hashed aggregate update state function
	aggregate_update_t update;
	//! The hashed aggregate combine states function
	aggregate_combine_t combine;
	//! The hashed aggregate finalization function
	aggregate_finalize_t finalize;
	//! The simple aggregate update function (may be null)
	aggregate_simple_update_t simple_update;
	//! The windowed aggregate frame update function (may be null)
	aggregate_window_t window;

	//! The bind function (may be null)
	bind_aggregate_function_t bind;
	//! The destructor method (may be null)
	aggregate_destructor_t destructor;

	//! The statistics propagation function (may be null)
	aggregate_statistics_t statistics;

	aggregate_serialize_t serialize;
	aggregate_deserialize_t deserialize;

	DUCKDB_API bool operator==(const AggregateFunction &rhs) const {
		return state_size == rhs.state_size && initialize == rhs.initialize && update == rhs.update &&
		       combine == rhs.combine && finalize == rhs.finalize && window == rhs.window;
	}
	DUCKDB_API bool operator!=(const AggregateFunction &rhs) const {
		return !(*this == rhs);
	}

	DUCKDB_API static unique_ptr<BoundAggregateExpression>
	BindAggregateFunction(ClientContext &context, AggregateFunction bound_function,
	                      vector<unique_ptr<Expression>> children, unique_ptr<Expression> filter = nullptr,
	                      bool is_distinct = false, unique_ptr<BoundOrderModifier> order_bys = nullptr);

	DUCKDB_API static unique_ptr<FunctionData> BindSortedAggregate(AggregateFunction &bound_function,
	                                                               vector<unique_ptr<Expression>> &children,
	                                                               unique_ptr<FunctionData> bind_info,
	                                                               unique_ptr<BoundOrderModifier> order_bys);

public:
	template <class STATE, class RESULT_TYPE, class OP>
	static AggregateFunction NullaryAggregate(LogicalType return_type) {
		return AggregateFunction(
		    {}, return_type, AggregateFunction::StateSize<STATE>, AggregateFunction::StateInitialize<STATE, OP>,
		    AggregateFunction::NullaryScatterUpdate<STATE, OP>, AggregateFunction::StateCombine<STATE, OP>,
		    AggregateFunction::StateFinalize<STATE, RESULT_TYPE, OP>, AggregateFunction::NullaryUpdate<STATE, OP>);
	}

	template <class STATE, class INPUT_TYPE, class RESULT_TYPE, class OP>
	static AggregateFunction
	UnaryAggregate(const LogicalType &input_type, LogicalType return_type,
	               FunctionNullHandling null_handling = FunctionNullHandling::DEFAULT_NULL_HANDLING) {
		return AggregateFunction(
		    {input_type}, return_type, AggregateFunction::StateSize<STATE>,
		    AggregateFunction::StateInitialize<STATE, OP>, AggregateFunction::UnaryScatterUpdate<STATE, INPUT_TYPE, OP>,
		    AggregateFunction::StateCombine<STATE, OP>, AggregateFunction::StateFinalize<STATE, RESULT_TYPE, OP>,
		    null_handling, AggregateFunction::UnaryUpdate<STATE, INPUT_TYPE, OP>);
	}

	template <class STATE, class INPUT_TYPE, class RESULT_TYPE, class OP>
	static AggregateFunction UnaryAggregateDestructor(LogicalType input_type, LogicalType return_type) {
		auto aggregate = UnaryAggregate<STATE, INPUT_TYPE, RESULT_TYPE, OP>(input_type, return_type);
		aggregate.destructor = AggregateFunction::StateDestroy<STATE, OP>;
		return aggregate;
	}

	template <class STATE, class A_TYPE, class B_TYPE, class RESULT_TYPE, class OP>
	static AggregateFunction BinaryAggregate(const LogicalType &a_type, const LogicalType &b_type,
	                                         LogicalType return_type) {
		return AggregateFunction({a_type, b_type}, return_type, AggregateFunction::StateSize<STATE>,
		                         AggregateFunction::StateInitialize<STATE, OP>,
		                         AggregateFunction::BinaryScatterUpdate<STATE, A_TYPE, B_TYPE, OP>,
		                         AggregateFunction::StateCombine<STATE, OP>,
		                         AggregateFunction::StateFinalize<STATE, RESULT_TYPE, OP>,
		                         AggregateFunction::BinaryUpdate<STATE, A_TYPE, B_TYPE, OP>);
	}

public:
	template <class STATE>
	static idx_t StateSize() {
		return sizeof(STATE);
	}

	template <class STATE, class OP>
	static void StateInitialize(data_ptr_t state) {
		OP::Initialize((STATE *)state);
	}

	template <class STATE, class OP>
	static void NullaryScatterUpdate(Vector inputs[], AggregateInputData &aggr_input_data, idx_t input_count,
	                                 Vector &states, idx_t count) {
		D_ASSERT(input_count == 0);
		AggregateExecutor::NullaryScatter<STATE, OP>(states, aggr_input_data, count);
	}

	template <class STATE, class OP>
	static void NullaryUpdate(Vector inputs[], AggregateInputData &aggr_input_data, idx_t input_count, data_ptr_t state,
	                          idx_t count) {
		D_ASSERT(input_count == 0);
		AggregateExecutor::NullaryUpdate<STATE, OP>(state, aggr_input_data, count);
	}

	template <class STATE, class T, class OP>
	static void UnaryScatterUpdate(Vector inputs[], AggregateInputData &aggr_input_data, idx_t input_count,
	                               Vector &states, idx_t count) {
		D_ASSERT(input_count == 1);
		AggregateExecutor::UnaryScatter<STATE, T, OP>(inputs[0], states, aggr_input_data, count);
	}

	template <class STATE, class INPUT_TYPE, class OP>
	static void UnaryUpdate(Vector inputs[], AggregateInputData &aggr_input_data, idx_t input_count, data_ptr_t state,
	                        idx_t count) {
		D_ASSERT(input_count == 1);
		AggregateExecutor::UnaryUpdate<STATE, INPUT_TYPE, OP>(inputs[0], aggr_input_data, state, count);
	}

	template <class STATE, class INPUT_TYPE, class RESULT_TYPE, class OP>
	static void UnaryWindow(Vector inputs[], const ValidityMask &filter_mask, AggregateInputData &aggr_input_data,
	                        idx_t input_count, data_ptr_t state, const FrameBounds &frame, const FrameBounds &prev,
	                        Vector &result, idx_t rid, idx_t bias) {
		D_ASSERT(input_count == 1);
		AggregateExecutor::UnaryWindow<STATE, INPUT_TYPE, RESULT_TYPE, OP>(inputs[0], filter_mask, aggr_input_data,
		                                                                   state, frame, prev, result, rid, bias);
	}

	template <class STATE, class A_TYPE, class B_TYPE, class OP>
	static void BinaryScatterUpdate(Vector inputs[], AggregateInputData &aggr_input_data, idx_t input_count,
	                                Vector &states, idx_t count) {
		D_ASSERT(input_count == 2);
		AggregateExecutor::BinaryScatter<STATE, A_TYPE, B_TYPE, OP>(aggr_input_data, inputs[0], inputs[1], states,
		                                                            count);
	}

	template <class STATE, class A_TYPE, class B_TYPE, class OP>
	static void BinaryUpdate(Vector inputs[], AggregateInputData &aggr_input_data, idx_t input_count, data_ptr_t state,
	                         idx_t count) {
		D_ASSERT(input_count == 2);
		AggregateExecutor::BinaryUpdate<STATE, A_TYPE, B_TYPE, OP>(aggr_input_data, inputs[0], inputs[1], state, count);
	}

	template <class STATE, class OP>
	static void StateCombine(Vector &source, Vector &target, AggregateInputData &aggr_input_data, idx_t count) {
		AggregateExecutor::Combine<STATE, OP>(source, target, aggr_input_data, count);
	}

	template <class STATE, class RESULT_TYPE, class OP>
	static void StateFinalize(Vector &states, AggregateInputData &aggr_input_data, Vector &result, idx_t count,
	                          idx_t offset) {
		AggregateExecutor::Finalize<STATE, RESULT_TYPE, OP>(states, aggr_input_data, result, count, offset);
	}

	template <class STATE, class OP>
	static void StateDestroy(Vector &states, idx_t count) {
		AggregateExecutor::Destroy<STATE, OP>(states, count);
	}
};

} // namespace duckdb


namespace duckdb {

struct UDFWrapper {
public:
	template <typename TR, typename... Args>
	static scalar_function_t CreateScalarFunction(const string &name, TR (*udf_func)(Args...)) {
		const std::size_t num_template_argc = sizeof...(Args);
		switch (num_template_argc) {
		case 1:
			return CreateUnaryFunction<TR, Args...>(name, udf_func);
		case 2:
			return CreateBinaryFunction<TR, Args...>(name, udf_func);
		case 3:
			return CreateTernaryFunction<TR, Args...>(name, udf_func);
		default: // LCOV_EXCL_START
			throw std::runtime_error("UDF function only supported until ternary!");
		} // LCOV_EXCL_STOP
	}

	template <typename TR, typename... Args>
	static scalar_function_t CreateScalarFunction(const string &name, vector<LogicalType> args, LogicalType ret_type,
	                                              TR (*udf_func)(Args...)) {
		if (!TypesMatch<TR>(ret_type)) { // LCOV_EXCL_START
			throw std::runtime_error("Return type doesn't match with the first template type.");
		} // LCOV_EXCL_STOP

		const std::size_t num_template_types = sizeof...(Args);
		if (num_template_types != args.size()) { // LCOV_EXCL_START
			throw std::runtime_error(
			    "The number of templated types should be the same quantity of the LogicalType arguments.");
		} // LCOV_EXCL_STOP

		switch (num_template_types) {
		case 1:
			return CreateUnaryFunction<TR, Args...>(name, args, ret_type, udf_func);
		case 2:
			return CreateBinaryFunction<TR, Args...>(name, args, ret_type, udf_func);
		case 3:
			return CreateTernaryFunction<TR, Args...>(name, args, ret_type, udf_func);
		default: // LCOV_EXCL_START
			throw std::runtime_error("UDF function only supported until ternary!");
		} // LCOV_EXCL_STOP
	}

	template <typename TR, typename... Args>
	static void RegisterFunction(const string &name, scalar_function_t udf_function, ClientContext &context,
	                             LogicalType varargs = LogicalType(LogicalTypeId::INVALID)) {
		vector<LogicalType> arguments;
		GetArgumentTypesRecursive<Args...>(arguments);

		LogicalType ret_type = GetArgumentType<TR>();

		RegisterFunction(name, arguments, ret_type, udf_function, context, varargs);
	}

	DUCKDB_API static void RegisterFunction(string name, vector<LogicalType> args, LogicalType ret_type,
	                                        scalar_function_t udf_function, ClientContext &context,
	                                        LogicalType varargs = LogicalType(LogicalTypeId::INVALID));

	//--------------------------------- Aggregate UDFs ------------------------------------//
	template <typename UDF_OP, typename STATE, typename TR, typename TA>
	static AggregateFunction CreateAggregateFunction(const string &name) {
		return CreateUnaryAggregateFunction<UDF_OP, STATE, TR, TA>(name);
	}

	template <typename UDF_OP, typename STATE, typename TR, typename TA, typename TB>
	static AggregateFunction CreateAggregateFunction(const string &name) {
		return CreateBinaryAggregateFunction<UDF_OP, STATE, TR, TA, TB>(name);
	}

	template <typename UDF_OP, typename STATE, typename TR, typename TA>
	static AggregateFunction CreateAggregateFunction(const string &name, LogicalType ret_type, LogicalType input_type) {
		if (!TypesMatch<TR>(ret_type)) { // LCOV_EXCL_START
			throw std::runtime_error("The return argument don't match!");
		} // LCOV_EXCL_STOP

		if (!TypesMatch<TA>(input_type)) { // LCOV_EXCL_START
			throw std::runtime_error("The input argument don't match!");
		} // LCOV_EXCL_STOP

		return CreateUnaryAggregateFunction<UDF_OP, STATE, TR, TA>(name, ret_type, input_type);
	}

	template <typename UDF_OP, typename STATE, typename TR, typename TA, typename TB>
	static AggregateFunction CreateAggregateFunction(const string &name, LogicalType ret_type, LogicalType input_typeA,
	                                                 LogicalType input_typeB) {
		if (!TypesMatch<TR>(ret_type)) { // LCOV_EXCL_START
			throw std::runtime_error("The return argument don't match!");
		}

		if (!TypesMatch<TA>(input_typeA)) {
			throw std::runtime_error("The first input argument don't match!");
		}

		if (!TypesMatch<TB>(input_typeB)) {
			throw std::runtime_error("The second input argument don't match!");
		} // LCOV_EXCL_STOP

		return CreateBinaryAggregateFunction<UDF_OP, STATE, TR, TA, TB>(name, ret_type, input_typeA, input_typeB);
	}

	//! A generic CreateAggregateFunction ---------------------------------------------------------------------------//
	static AggregateFunction CreateAggregateFunction(string name, vector<LogicalType> arguments,
	                                                 LogicalType return_type, aggregate_size_t state_size,
	                                                 aggregate_initialize_t initialize, aggregate_update_t update,
	                                                 aggregate_combine_t combine, aggregate_finalize_t finalize,
	                                                 aggregate_simple_update_t simple_update = nullptr,
	                                                 bind_aggregate_function_t bind = nullptr,
	                                                 aggregate_destructor_t destructor = nullptr) {

		AggregateFunction aggr_function(move(name), move(arguments), move(return_type), state_size, initialize, update,
		                                combine, finalize, simple_update, bind, destructor);
		aggr_function.null_handling = FunctionNullHandling::SPECIAL_HANDLING;
		return aggr_function;
	}

	DUCKDB_API static void RegisterAggrFunction(AggregateFunction aggr_function, ClientContext &context,
	                                            LogicalType varargs = LogicalType(LogicalTypeId::INVALID));

private:
	//-------------------------------- Templated functions --------------------------------//
	struct UnaryUDFExecutor {
		template <class INPUT_TYPE, class RESULT_TYPE>
		static RESULT_TYPE Operation(INPUT_TYPE input, ValidityMask &mask, idx_t idx, void *dataptr) {
			typedef RESULT_TYPE (*unary_function_t)(INPUT_TYPE);
			auto udf = (unary_function_t)dataptr;
			return udf(input);
		}
	};

	template <typename TR, typename TA>
	static scalar_function_t CreateUnaryFunction(const string &name, TR (*udf_func)(TA)) {
		scalar_function_t udf_function = [=](DataChunk &input, ExpressionState &state, Vector &result) -> void {
			UnaryExecutor::GenericExecute<TA, TR, UnaryUDFExecutor>(input.data[0], result, input.size(),
			                                                        (void *)udf_func);
		};
		return udf_function;
	}

	template <typename TR, typename TA, typename TB>
	static scalar_function_t CreateBinaryFunction(const string &name, TR (*udf_func)(TA, TB)) {
		scalar_function_t udf_function = [=](DataChunk &input, ExpressionState &state, Vector &result) -> void {
			BinaryExecutor::Execute<TA, TB, TR>(input.data[0], input.data[1], result, input.size(), udf_func);
		};
		return udf_function;
	}

	template <typename TR, typename TA, typename TB, typename TC>
	static scalar_function_t CreateTernaryFunction(const string &name, TR (*udf_func)(TA, TB, TC)) {
		scalar_function_t udf_function = [=](DataChunk &input, ExpressionState &state, Vector &result) -> void {
			TernaryExecutor::Execute<TA, TB, TC, TR>(input.data[0], input.data[1], input.data[2], result, input.size(),
			                                         udf_func);
		};
		return udf_function;
	}

	template <typename TR, typename... Args>
	static scalar_function_t CreateUnaryFunction(const string &name, TR (*udf_func)(Args...)) { // LCOV_EXCL_START
		throw std::runtime_error("Incorrect number of arguments for unary function");
	} // LCOV_EXCL_STOP

	template <typename TR, typename... Args>
	static scalar_function_t CreateBinaryFunction(const string &name, TR (*udf_func)(Args...)) { // LCOV_EXCL_START
		throw std::runtime_error("Incorrect number of arguments for binary function");
	} // LCOV_EXCL_STOP

	template <typename TR, typename... Args>
	static scalar_function_t CreateTernaryFunction(const string &name, TR (*udf_func)(Args...)) { // LCOV_EXCL_START
		throw std::runtime_error("Incorrect number of arguments for ternary function");
	} // LCOV_EXCL_STOP

	template <typename T>
	static LogicalType GetArgumentType() {
		if (std::is_same<T, bool>()) {
			return LogicalType(LogicalTypeId::BOOLEAN);
		} else if (std::is_same<T, int8_t>()) {
			return LogicalType(LogicalTypeId::TINYINT);
		} else if (std::is_same<T, int16_t>()) {
			return LogicalType(LogicalTypeId::SMALLINT);
		} else if (std::is_same<T, int32_t>()) {
			return LogicalType(LogicalTypeId::INTEGER);
		} else if (std::is_same<T, int64_t>()) {
			return LogicalType(LogicalTypeId::BIGINT);
		} else if (std::is_same<T, float>()) {
			return LogicalType(LogicalTypeId::FLOAT);
		} else if (std::is_same<T, double>()) {
			return LogicalType(LogicalTypeId::DOUBLE);
		} else if (std::is_same<T, string_t>()) {
			return LogicalType(LogicalTypeId::VARCHAR);
		} else { // LCOV_EXCL_START
			throw std::runtime_error("Unrecognized type!");
		} // LCOV_EXCL_STOP
	}

	template <typename TA, typename TB, typename... Args>
	static void GetArgumentTypesRecursive(vector<LogicalType> &arguments) {
		arguments.push_back(GetArgumentType<TA>());
		GetArgumentTypesRecursive<TB, Args...>(arguments);
	}

	template <typename TA>
	static void GetArgumentTypesRecursive(vector<LogicalType> &arguments) {
		arguments.push_back(GetArgumentType<TA>());
	}

private:
	//-------------------------------- Argumented functions --------------------------------//

	template <typename TR, typename... Args>
	static scalar_function_t CreateUnaryFunction(const string &name, vector<LogicalType> args, LogicalType ret_type,
	                                             TR (*udf_func)(Args...)) { // LCOV_EXCL_START
		throw std::runtime_error("Incorrect number of arguments for unary function");
	} // LCOV_EXCL_STOP

	template <typename TR, typename TA>
	static scalar_function_t CreateUnaryFunction(const string &name, vector<LogicalType> args, LogicalType ret_type,
	                                             TR (*udf_func)(TA)) {
		if (args.size() != 1) { // LCOV_EXCL_START
			throw std::runtime_error("The number of LogicalType arguments (\"args\") should be 1!");
		}
		if (!TypesMatch<TA>(args[0])) {
			throw std::runtime_error("The first arguments don't match!");
		} // LCOV_EXCL_STOP

		scalar_function_t udf_function = [=](DataChunk &input, ExpressionState &state, Vector &result) -> void {
			UnaryExecutor::GenericExecute<TA, TR, UnaryUDFExecutor>(input.data[0], result, input.size(),
			                                                        (void *)udf_func);
		};
		return udf_function;
	}

	template <typename TR, typename... Args>
	static scalar_function_t CreateBinaryFunction(const string &name, vector<LogicalType> args, LogicalType ret_type,
	                                              TR (*udf_func)(Args...)) { // LCOV_EXCL_START
		throw std::runtime_error("Incorrect number of arguments for binary function");
	} // LCOV_EXCL_STOP

	template <typename TR, typename TA, typename TB>
	static scalar_function_t CreateBinaryFunction(const string &name, vector<LogicalType> args, LogicalType ret_type,
	                                              TR (*udf_func)(TA, TB)) {
		if (args.size() != 2) { // LCOV_EXCL_START
			throw std::runtime_error("The number of LogicalType arguments (\"args\") should be 2!");
		}
		if (!TypesMatch<TA>(args[0])) {
			throw std::runtime_error("The first arguments don't match!");
		}
		if (!TypesMatch<TB>(args[1])) {
			throw std::runtime_error("The second arguments don't match!");
		} // LCOV_EXCL_STOP

		scalar_function_t udf_function = [=](DataChunk &input, ExpressionState &state, Vector &result) {
			BinaryExecutor::Execute<TA, TB, TR>(input.data[0], input.data[1], result, input.size(), udf_func);
		};
		return udf_function;
	}

	template <typename TR, typename... Args>
	static scalar_function_t CreateTernaryFunction(const string &name, vector<LogicalType> args, LogicalType ret_type,
	                                               TR (*udf_func)(Args...)) { // LCOV_EXCL_START
		throw std::runtime_error("Incorrect number of arguments for ternary function");
	} // LCOV_EXCL_STOP

	template <typename TR, typename TA, typename TB, typename TC>
	static scalar_function_t CreateTernaryFunction(const string &name, vector<LogicalType> args, LogicalType ret_type,
	                                               TR (*udf_func)(TA, TB, TC)) {
		if (args.size() != 3) { // LCOV_EXCL_START
			throw std::runtime_error("The number of LogicalType arguments (\"args\") should be 3!");
		}
		if (!TypesMatch<TA>(args[0])) {
			throw std::runtime_error("The first arguments don't match!");
		}
		if (!TypesMatch<TB>(args[1])) {
			throw std::runtime_error("The second arguments don't match!");
		}
		if (!TypesMatch<TC>(args[2])) {
			throw std::runtime_error("The second arguments don't match!");
		} // LCOV_EXCL_STOP

		scalar_function_t udf_function = [=](DataChunk &input, ExpressionState &state, Vector &result) -> void {
			TernaryExecutor::Execute<TA, TB, TC, TR>(input.data[0], input.data[1], input.data[2], result, input.size(),
			                                         udf_func);
		};
		return udf_function;
	}

	template <typename T>
	static bool TypesMatch(const LogicalType &sql_type) {
		switch (sql_type.id()) {
		case LogicalTypeId::BOOLEAN:
			return std::is_same<T, bool>();
		case LogicalTypeId::TINYINT:
			return std::is_same<T, int8_t>();
		case LogicalTypeId::SMALLINT:
			return std::is_same<T, int16_t>();
		case LogicalTypeId::INTEGER:
			return std::is_same<T, int32_t>();
		case LogicalTypeId::BIGINT:
			return std::is_same<T, int64_t>();
		case LogicalTypeId::DATE:
			return std::is_same<T, date_t>();
		case LogicalTypeId::TIME:
		case LogicalTypeId::TIME_TZ:
			return std::is_same<T, dtime_t>();
		case LogicalTypeId::TIMESTAMP:
		case LogicalTypeId::TIMESTAMP_MS:
		case LogicalTypeId::TIMESTAMP_NS:
		case LogicalTypeId::TIMESTAMP_SEC:
		case LogicalTypeId::TIMESTAMP_TZ:
			return std::is_same<T, timestamp_t>();
		case LogicalTypeId::FLOAT:
			return std::is_same<T, float>();
		case LogicalTypeId::DOUBLE:
			return std::is_same<T, double>();
		case LogicalTypeId::VARCHAR:
		case LogicalTypeId::CHAR:
		case LogicalTypeId::BLOB:
			return std::is_same<T, string_t>();
		default: // LCOV_EXCL_START
			throw std::runtime_error("Type is not supported!");
		} // LCOV_EXCL_STOP
	}

private:
	//-------------------------------- Aggregate functions --------------------------------//
	template <typename UDF_OP, typename STATE, typename TR, typename TA>
	static AggregateFunction CreateUnaryAggregateFunction(const string &name) {
		LogicalType return_type = GetArgumentType<TR>();
		LogicalType input_type = GetArgumentType<TA>();
		return CreateUnaryAggregateFunction<UDF_OP, STATE, TR, TA>(name, return_type, input_type);
	}

	template <typename UDF_OP, typename STATE, typename TR, typename TA>
	static AggregateFunction CreateUnaryAggregateFunction(const string &name, LogicalType ret_type,
	                                                      LogicalType input_type) {
		AggregateFunction aggr_function =
		    AggregateFunction::UnaryAggregate<STATE, TR, TA, UDF_OP>(input_type, ret_type);
		aggr_function.name = name;
		return aggr_function;
	}

	template <typename UDF_OP, typename STATE, typename TR, typename TA, typename TB>
	static AggregateFunction CreateBinaryAggregateFunction(const string &name) {
		LogicalType return_type = GetArgumentType<TR>();
		LogicalType input_typeA = GetArgumentType<TA>();
		LogicalType input_typeB = GetArgumentType<TB>();
		return CreateBinaryAggregateFunction<UDF_OP, STATE, TR, TA, TB>(name, return_type, input_typeA, input_typeB);
	}

	template <typename UDF_OP, typename STATE, typename TR, typename TA, typename TB>
	static AggregateFunction CreateBinaryAggregateFunction(const string &name, LogicalType ret_type,
	                                                       LogicalType input_typeA, LogicalType input_typeB) {
		AggregateFunction aggr_function =
		    AggregateFunction::BinaryAggregate<STATE, TR, TA, TB, UDF_OP>(input_typeA, input_typeB, ret_type);
		aggr_function.name = name;
		return aggr_function;
	}
}; // end UDFWrapper

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/materialized_query_result.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/column_data_collection.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/column_data_collection_iterators.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/column_data_scan_states.hpp
//
//
//===----------------------------------------------------------------------===//








namespace duckdb {

enum class ColumnDataAllocatorType : uint8_t {
	//! Use a buffer manager to allocate large chunks of memory that vectors then use
	BUFFER_MANAGER_ALLOCATOR,
	//! Use an in-memory allocator, allocating data for every chunk
	//! This causes the column data collection to behave similar to the old chunk collection
	IN_MEMORY_ALLOCATOR
};

enum class ColumnDataScanProperties : uint8_t {
	INVALID,
	//! Allow zero copy scans - this introduces a dependency on the resulting vector on the scan state of the column
	//! data collection, which means vectors might not be valid anymore after the next chunk is scanned.
	ALLOW_ZERO_COPY,
	//! Disallow zero-copy scans, always copying data into the target vector
	//! As a result, data scanned will be valid even after the column data collection is destroyed
	DISALLOW_ZERO_COPY
};

struct ChunkManagementState {
	unordered_map<idx_t, BufferHandle> handles;
	ColumnDataScanProperties properties = ColumnDataScanProperties::INVALID;
};

struct ColumnDataAppendState {
	ChunkManagementState current_chunk_state;
	vector<UnifiedVectorFormat> vector_data;
};

struct ColumnDataScanState {
	ChunkManagementState current_chunk_state;
	idx_t segment_index;
	idx_t chunk_index;
	idx_t current_row_index;
	idx_t next_row_index;
	ColumnDataScanProperties properties;
	vector<column_t> column_ids;
};

struct ColumnDataParallelScanState {
	ColumnDataScanState scan_state;
	mutex lock;
};

struct ColumnDataLocalScanState {
	ChunkManagementState current_chunk_state;
	idx_t current_segment_index = DConstants::INVALID_INDEX;
	idx_t current_row_index;
};

class ColumnDataRow {
public:
	ColumnDataRow(DataChunk &chunk, idx_t row_index, idx_t base_index);

	DataChunk &chunk;
	idx_t row_index;
	idx_t base_index;

public:
	Value GetValue(idx_t column_index) const;
	idx_t RowIndex() const;
};

} // namespace duckdb


namespace duckdb {
class ColumnDataCollection;

class ColumnDataChunkIterationHelper {
public:
	DUCKDB_API ColumnDataChunkIterationHelper(const ColumnDataCollection &collection, vector<column_t> column_ids);

private:
	const ColumnDataCollection &collection;
	vector<column_t> column_ids;

private:
	class ColumnDataChunkIterator;

	class ColumnDataChunkIterator {
	public:
		DUCKDB_API explicit ColumnDataChunkIterator(const ColumnDataCollection *collection_p,
		                                            vector<column_t> column_ids);

		const ColumnDataCollection *collection;
		ColumnDataScanState scan_state;
		shared_ptr<DataChunk> scan_chunk;
		idx_t row_index;

	public:
		DUCKDB_API void Next();

		DUCKDB_API ColumnDataChunkIterator &operator++();
		DUCKDB_API bool operator!=(const ColumnDataChunkIterator &other) const;
		DUCKDB_API DataChunk &operator*() const;
	};

public:
	DUCKDB_API ColumnDataChunkIterator begin() {
		return ColumnDataChunkIterator(&collection, column_ids);
	}
	DUCKDB_API ColumnDataChunkIterator end() {
		return ColumnDataChunkIterator(nullptr, vector<column_t>());
	}
};

class ColumnDataRowIterationHelper {
public:
	DUCKDB_API ColumnDataRowIterationHelper(const ColumnDataCollection &collection);

private:
	const ColumnDataCollection &collection;

private:
	class ColumnDataRowIterator;

	class ColumnDataRowIterator {
	public:
		DUCKDB_API explicit ColumnDataRowIterator(const ColumnDataCollection *collection_p);

		const ColumnDataCollection *collection;
		ColumnDataScanState scan_state;
		shared_ptr<DataChunk> scan_chunk;
		ColumnDataRow current_row;

	public:
		void Next();

		DUCKDB_API ColumnDataRowIterator &operator++();
		DUCKDB_API bool operator!=(const ColumnDataRowIterator &other) const;
		DUCKDB_API const ColumnDataRow &operator*() const;
	};

public:
	DUCKDB_API ColumnDataRowIterator begin();
	DUCKDB_API ColumnDataRowIterator end();
};

} // namespace duckdb


namespace duckdb {
class BufferManager;
class BlockHandle;
class ClientContext;
struct ColumnDataCopyFunction;
class ColumnDataAllocator;
class ColumnDataCollection;
class ColumnDataCollectionSegment;
class ColumnDataRowCollection;

//! The ColumnDataCollection represents a set of (buffer-managed) data stored in columnar format
//! It is efficient to read and scan
class ColumnDataCollection {
public:
	//! Constructs an in-memory column data collection from an allocator
	DUCKDB_API ColumnDataCollection(Allocator &allocator, vector<LogicalType> types);
	//! Constructs an empty (but valid) in-memory column data collection from an allocator
	DUCKDB_API ColumnDataCollection(Allocator &allocator);
	//! Constructs a buffer-managed column data collection
	DUCKDB_API ColumnDataCollection(BufferManager &buffer_manager, vector<LogicalType> types);
	//! Constructs either an in-memory or a buffer-managed column data collection
	DUCKDB_API ColumnDataCollection(ClientContext &context, vector<LogicalType> types,
	                                ColumnDataAllocatorType type = ColumnDataAllocatorType::BUFFER_MANAGER_ALLOCATOR);
	//! Creates a column data collection that inherits the blocks to write to. This allows blocks to be shared
	//! between multiple column data collections and prevents wasting space.
	//! Note that after one CDC inherits blocks from another, the other
	//! cannot be written to anymore (i.e. we take ownership of the half-written blocks).
	DUCKDB_API ColumnDataCollection(ColumnDataCollection &parent);
	DUCKDB_API ColumnDataCollection(shared_ptr<ColumnDataAllocator> allocator, vector<LogicalType> types);
	DUCKDB_API ~ColumnDataCollection();

public:
	DUCKDB_API vector<LogicalType> &Types() {
		return types;
	}
	DUCKDB_API const vector<LogicalType> &Types() const {
		return types;
	}

	//! The amount of rows in the ColumnDataCollection
	DUCKDB_API const idx_t &Count() const {
		return count;
	}

	//! The amount of columns in the ColumnDataCollection
	DUCKDB_API idx_t ColumnCount() const {
		return types.size();
	}

	//! Initializes an Append state - useful for optimizing many appends made to the same column data collection
	DUCKDB_API void InitializeAppend(ColumnDataAppendState &state);
	//! Append a DataChunk to this ColumnDataCollection using the specified append state
	DUCKDB_API void Append(ColumnDataAppendState &state, DataChunk &new_chunk);

	//! Initializes a chunk with the correct types that can be used to call Scan
	DUCKDB_API void InitializeScanChunk(DataChunk &chunk) const;
	//! Initializes a chunk with the correct types for a given scan state
	DUCKDB_API void InitializeScanChunk(ColumnDataScanState &state, DataChunk &chunk) const;
	//! Initializes a Scan state for scanning all columns
	DUCKDB_API void
	InitializeScan(ColumnDataScanState &state,
	               ColumnDataScanProperties properties = ColumnDataScanProperties::ALLOW_ZERO_COPY) const;
	//! Initializes a Scan state for scanning a subset of the columns
	DUCKDB_API void
	InitializeScan(ColumnDataScanState &state, vector<column_t> column_ids,
	               ColumnDataScanProperties properties = ColumnDataScanProperties::ALLOW_ZERO_COPY) const;
	//! Initialize a parallel scan over the column data collection over all columns
	DUCKDB_API void
	InitializeScan(ColumnDataParallelScanState &state,
	               ColumnDataScanProperties properties = ColumnDataScanProperties::ALLOW_ZERO_COPY) const;
	//! Initialize a parallel scan over the column data collection over a subset of the columns
	DUCKDB_API void
	InitializeScan(ColumnDataParallelScanState &state, vector<column_t> column_ids,
	               ColumnDataScanProperties properties = ColumnDataScanProperties::ALLOW_ZERO_COPY) const;
	//! Scans a DataChunk from the ColumnDataCollection
	DUCKDB_API bool Scan(ColumnDataScanState &state, DataChunk &result) const;
	//! Scans a DataChunk from the ColumnDataCollection
	DUCKDB_API bool Scan(ColumnDataParallelScanState &state, ColumnDataLocalScanState &lstate, DataChunk &result) const;

	//! Append a DataChunk directly to this ColumnDataCollection - calls InitializeAppend and Append internally
	DUCKDB_API void Append(DataChunk &new_chunk);

	//! Appends the other ColumnDataCollection to this, destroying the other data collection
	DUCKDB_API void Combine(ColumnDataCollection &other);

	DUCKDB_API void Verify();

	DUCKDB_API string ToString() const;
	DUCKDB_API void Print() const;

	DUCKDB_API void Reset();

	//! Returns the number of data chunks present in the ColumnDataCollection
	DUCKDB_API idx_t ChunkCount() const;
	//! Fetch an individual chunk from the ColumnDataCollection
	DUCKDB_API void FetchChunk(idx_t chunk_idx, DataChunk &result) const;

	//! Constructs a class that can be iterated over to fetch individual chunks
	//! Iterating over this is syntactic sugar over just calling Scan
	DUCKDB_API ColumnDataChunkIterationHelper Chunks() const;
	//! Constructs a class that can be iterated over to fetch individual chunks
	//! Only the column indexes specified in the column_ids list are scanned
	DUCKDB_API ColumnDataChunkIterationHelper Chunks(vector<column_t> column_ids) const;

	//! Constructs a class that can be iterated over to fetch individual rows
	//! Note that row iteration is slow, and the `.Chunks()` method should be used instead
	DUCKDB_API ColumnDataRowIterationHelper Rows() const;

	//! Returns a materialized set of all of the rows in the column data collection
	//! Note that usage of this is slow - avoid using this unless the amount of rows is small, or if you do not care
	//! about performance
	DUCKDB_API ColumnDataRowCollection GetRows() const;

	//! Compare two column data collections to another. If they are equal according to result equality rules,
	//! return true. That means null values are equal, and approx equality is used for floating point values.
	//! If they are not equal, return false and fill in the error message.
	static bool ResultEquals(const ColumnDataCollection &left, const ColumnDataCollection &right,
	                         string &error_message);

	//! Obtains the next scan index to scan from
	bool NextScanIndex(ColumnDataScanState &state, idx_t &chunk_index, idx_t &segment_index, idx_t &row_index) const;
	//! Scans at the indices (obtained from NextScanIndex)
	void ScanAtIndex(ColumnDataParallelScanState &state, ColumnDataLocalScanState &lstate, DataChunk &result,
	                 idx_t chunk_index, idx_t segment_index, idx_t row_index) const;

private:
	//! Initialize the column data collection
	void Initialize(vector<LogicalType> types);

	//! Creates a new segment within the ColumnDataCollection
	void CreateSegment();

	static ColumnDataCopyFunction GetCopyFunction(const LogicalType &type);

private:
	//! The Column Data Allocator
	buffer_ptr<ColumnDataAllocator> allocator;
	//! The types of the stored entries
	vector<LogicalType> types;
	//! The number of entries stored in the column data collection
	idx_t count;
	//! The data segments of the column data collection
	vector<unique_ptr<ColumnDataCollectionSegment>> segments;
	//! The set of copy functions
	vector<ColumnDataCopyFunction> copy_functions;
	//! When the column data collection is marked as finished - new tuples can no longer be appended to it
	bool finished_append;
};

//! The ColumnDataRowCollection represents a set of materialized rows, as obtained from the ColumnDataCollection
class ColumnDataRowCollection {
public:
	DUCKDB_API ColumnDataRowCollection(const ColumnDataCollection &collection);

public:
	DUCKDB_API Value GetValue(idx_t column, idx_t index) const;

public:
	// container API
	DUCKDB_API bool empty() const {
		return rows.empty();
	}
	DUCKDB_API idx_t size() const {
		return rows.size();
	}

	DUCKDB_API ColumnDataRow &operator[](idx_t i);
	DUCKDB_API const ColumnDataRow &operator[](idx_t i) const;

	DUCKDB_API vector<ColumnDataRow>::iterator begin() {
		return rows.begin();
	}
	DUCKDB_API vector<ColumnDataRow>::iterator end() {
		return rows.end();
	}
	DUCKDB_API vector<ColumnDataRow>::const_iterator cbegin() const {
		return rows.cbegin();
	}
	DUCKDB_API vector<ColumnDataRow>::const_iterator cend() const {
		return rows.cend();
	}
	DUCKDB_API vector<ColumnDataRow>::const_iterator begin() const {
		return rows.begin();
	}
	DUCKDB_API vector<ColumnDataRow>::const_iterator end() const {
		return rows.end();
	}

private:
	vector<ColumnDataRow> rows;
	vector<unique_ptr<DataChunk>> chunks;
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/query_result.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/statement_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//===--------------------------------------------------------------------===//
// Statement Types
//===--------------------------------------------------------------------===//
enum class StatementType : uint8_t {
	INVALID_STATEMENT,      // invalid statement type
	SELECT_STATEMENT,       // select statement type
	INSERT_STATEMENT,       // insert statement type
	UPDATE_STATEMENT,       // update statement type
	CREATE_STATEMENT,       // create statement type
	DELETE_STATEMENT,       // delete statement type
	PREPARE_STATEMENT,      // prepare statement type
	EXECUTE_STATEMENT,      // execute statement type
	ALTER_STATEMENT,        // alter statement type
	TRANSACTION_STATEMENT,  // transaction statement type,
	COPY_STATEMENT,         // copy type
	ANALYZE_STATEMENT,      // analyze type
	VARIABLE_SET_STATEMENT, // variable set statement type
	CREATE_FUNC_STATEMENT,  // create func statement type
	EXPLAIN_STATEMENT,      // explain statement type
	DROP_STATEMENT,         // DROP statement type
	EXPORT_STATEMENT,       // EXPORT statement type
	PRAGMA_STATEMENT,       // PRAGMA statement type
	SHOW_STATEMENT,         // SHOW statement type
	VACUUM_STATEMENT,       // VACUUM statement type
	CALL_STATEMENT,         // CALL statement type
	SET_STATEMENT,          // SET statement type
	LOAD_STATEMENT,         // LOAD statement type
	RELATION_STATEMENT,
	EXTENSION_STATEMENT,
	LOGICAL_PLAN_STATEMENT

};

string StatementTypeToString(StatementType type);

enum class StatementReturnType : uint8_t {
	QUERY_RESULT, // the statement returns a query result (e.g. for display to the user)
	CHANGED_ROWS, // the statement returns a single row containing the number of changed rows (e.g. an insert stmt)
	NOTHING       // the statement returns nothing
};

string StatementReturnTypeToString(StatementReturnType type);

//! A struct containing various properties of a SQL statement
struct StatementProperties {
	StatementProperties()
	    : read_only(true), requires_valid_transaction(true), allow_stream_result(false), bound_all_parameters(true),
	      return_type(StatementReturnType::QUERY_RESULT), parameter_count(0) {
	}

	//! Whether or not the statement is a read-only statement, or whether it can result in changes to the database
	bool read_only;
	//! Whether or not the statement requires a valid transaction. Almost all statements require this, with the
	//! exception of
	bool requires_valid_transaction;
	//! Whether or not the result can be streamed to the client
	bool allow_stream_result;
	//! Whether or not all parameters have successfully had their types determined
	bool bound_all_parameters;
	//! What type of data the statement returns
	StatementReturnType return_type;
	//! The number of prepared statement parameters
	idx_t parameter_count;
};

} // namespace duckdb





namespace duckdb {

enum class QueryResultType : uint8_t { MATERIALIZED_RESULT, STREAM_RESULT, PENDING_RESULT };

//! A set of properties from the client context that can be used to interpret the query result
struct ClientProperties {
	string timezone;
};

class BaseQueryResult {
public:
	//! Creates a successful query result with the specified names and types
	DUCKDB_API BaseQueryResult(QueryResultType type, StatementType statement_type, StatementProperties properties,
	                           vector<LogicalType> types, vector<string> names);
	//! Creates an unsuccessful query result with error condition
	DUCKDB_API BaseQueryResult(QueryResultType type, PreservedError error);
	DUCKDB_API virtual ~BaseQueryResult();

	//! The type of the result (MATERIALIZED or STREAMING)
	QueryResultType type;
	//! The type of the statement that created this result
	StatementType statement_type;
	//! Properties of the statement
	StatementProperties properties;
	//! The SQL types of the result
	vector<LogicalType> types;
	//! The names of the result
	vector<string> names;

public:
	DUCKDB_API void ThrowError(const string &prepended_message = "") const;
	DUCKDB_API void SetError(PreservedError error);
	DUCKDB_API bool HasError() const;
	DUCKDB_API const ExceptionType &GetErrorType() const;
	DUCKDB_API const std::string &GetError();
	DUCKDB_API PreservedError &GetErrorObject();
	DUCKDB_API idx_t ColumnCount();

protected:
	//! Whether or not execution was successful
	bool success;
	//! The error (in case execution was not successful)
	PreservedError error;
};

//! The QueryResult object holds the result of a query. It can either be a MaterializedQueryResult, in which case the
//! result contains the entire result set, or a StreamQueryResult in which case the Fetch method can be called to
//! incrementally fetch data from the database.
class QueryResult : public BaseQueryResult {
public:
	//! Creates a successful query result with the specified names and types
	DUCKDB_API QueryResult(QueryResultType type, StatementType statement_type, StatementProperties properties,
	                       vector<LogicalType> types, vector<string> names, ClientProperties client_properties);
	//! Creates an unsuccessful query result with error condition
	DUCKDB_API QueryResult(QueryResultType type, PreservedError error);
	DUCKDB_API virtual ~QueryResult() override;

	//! Properties from the client context
	ClientProperties client_properties;
	//! The next result (if any)
	unique_ptr<QueryResult> next;

public:
	//! Fetches a DataChunk of normalized (flat) vectors from the query result.
	//! Returns nullptr if there are no more results to fetch.
	DUCKDB_API virtual unique_ptr<DataChunk> Fetch();
	//! Fetches a DataChunk from the query result. The vectors are not normalized and hence any vector types can be
	//! returned.
	DUCKDB_API virtual unique_ptr<DataChunk> FetchRaw() = 0;
	//! Converts the QueryResult to a string
	DUCKDB_API virtual string ToString() = 0;
	//! Prints the QueryResult to the console
	DUCKDB_API void Print();
	//! Returns true if the two results are identical; false otherwise. Note that this method is destructive; it calls
	//! Fetch() until both results are exhausted. The data in the results will be lost.
	DUCKDB_API bool Equals(QueryResult &other);

	DUCKDB_API bool TryFetch(unique_ptr<DataChunk> &result, PreservedError &error) {
		try {
			result = Fetch();
			return success;
		} catch (const Exception &ex) {
			error = PreservedError(ex);
			return false;
		} catch (std::exception &ex) {
			error = PreservedError(ex);
			return false;
		} catch (...) {
			error = PreservedError("Unknown error in Fetch");
			return false;
		}
	}

	static string GetConfigTimezone(QueryResult &query_result);

private:
	class QueryResultIterator;
	class QueryResultRow {
	public:
		explicit QueryResultRow(QueryResultIterator &iterator_p, idx_t row_idx) : iterator(iterator_p), row(0) {
		}

		QueryResultIterator &iterator;
		idx_t row;

		template <class T>
		T GetValue(idx_t col_idx) const {
			return iterator.chunk->GetValue(col_idx, row).GetValue<T>();
		}
	};
	//! The row-based query result iterator. Invoking the
	class QueryResultIterator {
	public:
		explicit QueryResultIterator(QueryResult *result) : current_row(*this, 0), result(result), base_row(0) {
			if (result) {
				chunk = shared_ptr<DataChunk>(result->Fetch().release());
			}
		}

		QueryResultRow current_row;
		shared_ptr<DataChunk> chunk;
		QueryResult *result;
		idx_t base_row;

	public:
		void Next() {
			if (!chunk) {
				return;
			}
			current_row.row++;
			if (current_row.row >= chunk->size()) {
				base_row += chunk->size();
				chunk = result->Fetch();
				current_row.row = 0;
				if (!chunk || chunk->size() == 0) {
					// exhausted all rows
					base_row = 0;
					result = nullptr;
					chunk.reset();
				}
			}
		}

		QueryResultIterator &operator++() {
			Next();
			return *this;
		}
		bool operator!=(const QueryResultIterator &other) const {
			return result != other.result || base_row != other.base_row || current_row.row != other.current_row.row;
		}
		const QueryResultRow &operator*() const {
			return current_row;
		}
	};

public:
	DUCKDB_API QueryResultIterator begin() {
		return QueryResultIterator(this);
	}
	DUCKDB_API QueryResultIterator end() {
		return QueryResultIterator(nullptr);
	}

protected:
	DUCKDB_API string HeaderToString();

private:
	QueryResult(const QueryResult &) = delete;
};

} // namespace duckdb


namespace duckdb {

class ClientContext;

class MaterializedQueryResult : public QueryResult {
public:
	friend class ClientContext;
	//! Creates a successful query result with the specified names and types
	DUCKDB_API MaterializedQueryResult(StatementType statement_type, StatementProperties properties,
	                                   vector<string> names, unique_ptr<ColumnDataCollection> collection,
	                                   ClientProperties client_properties);
	//! Creates an unsuccessful query result with error condition
	DUCKDB_API explicit MaterializedQueryResult(PreservedError error);

public:
	//! Fetches a DataChunk from the query result.
	//! This will consume the result (i.e. the result can only be scanned once with this function)
	DUCKDB_API unique_ptr<DataChunk> Fetch() override;
	DUCKDB_API unique_ptr<DataChunk> FetchRaw() override;
	//! Converts the QueryResult to a string
	DUCKDB_API string ToString() override;

	//! Gets the (index) value of the (column index) column.
	//! Note: this is very slow. Scanning over the underlying collection is much faster.
	DUCKDB_API Value GetValue(idx_t column, idx_t index);

	template <class T>
	T GetValue(idx_t column, idx_t index) {
		auto value = GetValue(column, index);
		return (T)value.GetValue<int64_t>();
	}

	DUCKDB_API idx_t RowCount() const;

	//! Returns a reference to the underlying column data collection
	ColumnDataCollection &Collection();

private:
	unique_ptr<ColumnDataCollection> collection;
	//! Row collection, only created if GetValue is called
	unique_ptr<ColumnDataRowCollection> row_collection;
	//! Scan state for Fetch calls
	ColumnDataScanState scan_state;
	bool scan_initialized;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/pending_query_result.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/pending_execution_result.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class PendingExecutionResult : uint8_t { RESULT_READY, RESULT_NOT_READY, EXECUTION_ERROR };

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/executor.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parallel/pipeline.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/physical_operator.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/optimizer/join_node.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/optimizer/join_order/query_graph.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/pair.hpp
//
//
//===----------------------------------------------------------------------===//



#include <utility>

namespace duckdb {
using std::make_pair;
using std::pair;
} // namespace duckdb







#include <functional>

namespace duckdb {
class Expression;
class LogicalOperator;

struct FilterInfo {
	idx_t filter_index;
	JoinRelationSet *left_set = nullptr;
	JoinRelationSet *right_set = nullptr;
	ColumnBinding left_binding;
	ColumnBinding right_binding;
	JoinRelationSet *set = nullptr;
};

struct FilterNode {
	vector<FilterInfo *> filters;
	unordered_map<idx_t, unique_ptr<FilterNode>> children;
};

struct NeighborInfo {
	JoinRelationSet *neighbor;
	vector<FilterInfo *> filters;
};

//! The QueryGraph contains edges between relations and allows edges to be created/queried
class QueryGraph {
public:
	//! Contains a node with info about neighboring relations and child edge infos
	struct QueryEdge {
		vector<unique_ptr<NeighborInfo>> neighbors;
		unordered_map<idx_t, unique_ptr<QueryEdge>> children;
	};

public:
	string ToString() const;
	void Print();

	//! Create an edge in the edge_set
	void CreateEdge(JoinRelationSet *left, JoinRelationSet *right, FilterInfo *info);
	//! Returns a connection if there is an edge that connects these two sets, or nullptr otherwise
	vector<NeighborInfo *> GetConnections(JoinRelationSet *node, JoinRelationSet *other);
	//! Enumerate the neighbors of a specific node that do not belong to any of the exclusion_set. Note that if a
	//! neighbor has multiple nodes, this function will return the lowest entry in that set.
	vector<idx_t> GetNeighbors(JoinRelationSet *node, unordered_set<idx_t> &exclusion_set);
	//! Enumerate all neighbors of a given JoinRelationSet node
	void EnumerateNeighbors(JoinRelationSet *node, const std::function<bool(NeighborInfo *)> &callback);

private:
	//! Get the QueryEdge of a specific node
	QueryEdge *GetQueryEdge(JoinRelationSet *left);

	QueryEdge root;
};

} // namespace duckdb









namespace duckdb {

class JoinOrderOptimizer;

class JoinNode {
public:
	//! Represents a node in the join plan
	JoinRelationSet *set;
	NeighborInfo *info;
	//! If the JoinNode is a base table, then base_cardinality is the cardinality before filters
	//! estimated_props.cardinality will be the cardinality after filters. With no filters, the two are equal
	bool has_filter;
	JoinNode *left;
	JoinNode *right;

	unique_ptr<EstimatedProperties> estimated_props;

	//! Create a leaf node in the join tree
	//! set cost to 0 for leaf nodes
	//! cost will be the cost to *produce* an intermediate table
	JoinNode(JoinRelationSet *set, const double base_cardinality);

	//! Create an intermediate node in the join tree. base_cardinality = estimated_props.cardinality
	JoinNode(JoinRelationSet *set, NeighborInfo *info, JoinNode *left, JoinNode *right, const double base_cardinality,
	         double cost);

	bool operator==(const JoinNode &other) {
		return other.set->ToString().compare(set->ToString()) == 0;
	}

private:
	double base_cardinality;

public:
	double GetCardinality() const;
	double GetCost();
	void SetCost(double cost);
	double GetBaseTableCardinality();
	void SetBaseTableCardinality(double base_card);
	void SetEstimatedCardinality(double estimated_card);
	void PrintJoinNode();
	string ToString();
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/physical_operator_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//===--------------------------------------------------------------------===//
// Physical Operator Types
//===--------------------------------------------------------------------===//
enum class PhysicalOperatorType : uint8_t {
	INVALID,
	ORDER_BY,
	LIMIT,
	STREAMING_LIMIT,
	LIMIT_PERCENT,
	TOP_N,
	WINDOW,
	UNNEST,
	UNGROUPED_AGGREGATE,
	HASH_GROUP_BY,
	PERFECT_HASH_GROUP_BY,
	FILTER,
	PROJECTION,
	COPY_TO_FILE,
	RESERVOIR_SAMPLE,
	STREAMING_SAMPLE,
	STREAMING_WINDOW,
	// -----------------------------
	// Scans
	// -----------------------------
	TABLE_SCAN,
	DUMMY_SCAN,
	COLUMN_DATA_SCAN,
	CHUNK_SCAN,
	RECURSIVE_CTE_SCAN,
	DELIM_SCAN,
	EXPRESSION_SCAN,
	// -----------------------------
	// Joins
	// -----------------------------
	BLOCKWISE_NL_JOIN,
	NESTED_LOOP_JOIN,
	HASH_JOIN,
	CROSS_PRODUCT,
	PIECEWISE_MERGE_JOIN,
	IE_JOIN,
	DELIM_JOIN,
	INDEX_JOIN,
	// -----------------------------
	// SetOps
	// -----------------------------
	UNION,
	RECURSIVE_CTE,

	// -----------------------------
	// Updates
	// -----------------------------
	INSERT,
	DELETE_OPERATOR,
	UPDATE,

	// -----------------------------
	// Schema
	// -----------------------------
	CREATE_TABLE,
	CREATE_TABLE_AS,
	CREATE_INDEX,
	ALTER,
	CREATE_SEQUENCE,
	CREATE_VIEW,
	CREATE_SCHEMA,
	CREATE_MACRO,
	DROP,
	PRAGMA,
	TRANSACTION,
	CREATE_TYPE,

	// -----------------------------
	// Helpers
	// -----------------------------
	EXPLAIN,
	EXPLAIN_ANALYZE,
	EMPTY_RESULT,
	EXECUTE,
	PREPARE,
	VACUUM,
	EXPORT,
	SET,
	LOAD,
	INOUT_FUNCTION,
	RESULT_COLLECTOR
};

string PhysicalOperatorToString(PhysicalOperatorType type);

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/execution_context.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {
class ClientContext;
class ThreadContext;

class ExecutionContext {
public:
	ExecutionContext(ClientContext &client_p, ThreadContext &thread_p) : client(client_p), thread(thread_p) {
	}

	//! The client-global context; caution needs to be taken when used in parallel situations
	ClientContext &client;
	//! The thread-local context for this execution
	ThreadContext &thread;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/operator_result_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//! The OperatorResultType is used to indicate how data should flow around a regular (i.e. non-sink and non-source)
//! physical operator
//! There are three possible results:
//! NEED_MORE_INPUT means the operator is done with the current input and can consume more input if available
//! If there is more input the operator will be called with more input, otherwise the operator will not be called again.
//! HAVE_MORE_OUTPUT means the operator is not finished yet with the current input.
//! The operator will be called again with the same input.
//! FINISHED means the operator has finished the entire pipeline and no more processing is necessary.
//! The operator will not be called again, and neither will any other operators in this pipeline.
enum class OperatorResultType : uint8_t { NEED_MORE_INPUT, HAVE_MORE_OUTPUT, FINISHED };

//! The SinkResultType is used to indicate the result of data flowing into a sink
//! There are two possible results:
//! NEED_MORE_INPUT means the sink needs more input
//! FINISHED means the sink is finished executing, and more input will not change the result any further
enum class SinkResultType : uint8_t { NEED_MORE_INPUT, FINISHED };

//! The SinkFinalizeType is used to indicate the result of a Finalize call on a sink
//! There are two possible results:
//! READY means the sink is ready for further processing
//! NO_OUTPUT_POSSIBLE means the sink will never provide output, and any pipelines involving the sink can be skipped
enum class SinkFinalizeType : uint8_t { READY, NO_OUTPUT_POSSIBLE };

} // namespace duckdb


namespace duckdb {
class Event;
class Executor;
class PhysicalOperator;
class Pipeline;
class PipelineBuildState;

// LCOV_EXCL_START
class OperatorState {
public:
	virtual ~OperatorState() {
	}

	virtual void Finalize(PhysicalOperator *op, ExecutionContext &context) {
	}
};

class GlobalOperatorState {
public:
	virtual ~GlobalOperatorState() {
	}
};

class GlobalSinkState {
public:
	GlobalSinkState() : state(SinkFinalizeType::READY) {
	}
	virtual ~GlobalSinkState() {
	}

	SinkFinalizeType state;
};

class LocalSinkState {
public:
	virtual ~LocalSinkState() {
	}

	//! The current batch index
	//! This is only set in case RequiresBatchIndex() is true, and the source has support for it (SupportsBatchIndex())
	//! Otherwise this is left on INVALID_INDEX
	//! The batch index is a globally unique, increasing index that should be used to maintain insertion order
	//! //! in conjunction with parallelism
	idx_t batch_index = DConstants::INVALID_INDEX;
};

class GlobalSourceState {
public:
	virtual ~GlobalSourceState() {
	}

	virtual idx_t MaxThreads() {
		return 1;
	}
};

class LocalSourceState {
public:
	virtual ~LocalSourceState() {
	}
};

// LCOV_EXCL_STOP

//! PhysicalOperator is the base class of the physical operators present in the
//! execution plan
class PhysicalOperator {
public:
	PhysicalOperator(PhysicalOperatorType type, vector<LogicalType> types, idx_t estimated_cardinality)
	    : type(type), types(std::move(types)), estimated_cardinality(estimated_cardinality) {
		estimated_props = make_unique<EstimatedProperties>(estimated_cardinality, 0);
	}

	virtual ~PhysicalOperator() {
	}

	//! The physical operator type
	PhysicalOperatorType type;
	//! The set of children of the operator
	vector<unique_ptr<PhysicalOperator>> children;
	//! The types returned by this physical operator
	vector<LogicalType> types;
	//! The estimated cardinality of this physical operator
	idx_t estimated_cardinality;
	unique_ptr<EstimatedProperties> estimated_props;

	//! The global sink state of this operator
	unique_ptr<GlobalSinkState> sink_state;
	//! The global state of this operator
	unique_ptr<GlobalOperatorState> op_state;

public:
	virtual string GetName() const;
	virtual string ParamsToString() const {
		return "";
	}
	virtual string ToString() const;
	void Print() const;
	virtual vector<PhysicalOperator *> GetChildren() const;

	//! Return a vector of the types that will be returned by this operator
	const vector<LogicalType> &GetTypes() const {
		return types;
	}

	virtual bool Equals(const PhysicalOperator &other) const {
		return false;
	}

	virtual void Verify();

	//! Whether or not the operator depends on the order of the input chunks
	//! If this is set to true, we cannot do things like caching intermediate vectors
	virtual bool IsOrderDependent() const {
		return false;
	}

public:
	// Operator interface
	virtual unique_ptr<OperatorState> GetOperatorState(ExecutionContext &context) const;
	virtual unique_ptr<GlobalOperatorState> GetGlobalOperatorState(ClientContext &context) const;
	virtual OperatorResultType Execute(ExecutionContext &context, DataChunk &input, DataChunk &chunk,
	                                   GlobalOperatorState &gstate, OperatorState &state) const;

	virtual bool ParallelOperator() const {
		return false;
	}

	virtual bool RequiresCache() const {
		return false;
	}

public:
	// Source interface
	virtual unique_ptr<LocalSourceState> GetLocalSourceState(ExecutionContext &context,
	                                                         GlobalSourceState &gstate) const;
	virtual unique_ptr<GlobalSourceState> GetGlobalSourceState(ClientContext &context) const;
	virtual void GetData(ExecutionContext &context, DataChunk &chunk, GlobalSourceState &gstate,
	                     LocalSourceState &lstate) const;
	virtual idx_t GetBatchIndex(ExecutionContext &context, DataChunk &chunk, GlobalSourceState &gstate,
	                            LocalSourceState &lstate) const;

	virtual bool IsSource() const {
		return false;
	}

	virtual bool ParallelSource() const {
		return false;
	}

	virtual bool SupportsBatchIndex() const {
		return false;
	}

	virtual bool IsOrderPreserving() const {
		return true;
	}

	//! Returns the current progress percentage, or a negative value if progress bars are not supported
	virtual double GetProgress(ClientContext &context, GlobalSourceState &gstate) const;

public:
	// Sink interface

	//! The sink method is called constantly with new input, as long as new input is available. Note that this method
	//! CAN be called in parallel, proper locking is needed when accessing data inside the GlobalSinkState.
	virtual SinkResultType Sink(ExecutionContext &context, GlobalSinkState &gstate, LocalSinkState &lstate,
	                            DataChunk &input) const;
	// The combine is called when a single thread has completed execution of its part of the pipeline, it is the final
	// time that a specific LocalSinkState is accessible. This method can be called in parallel while other Sink() or
	// Combine() calls are active on the same GlobalSinkState.
	virtual void Combine(ExecutionContext &context, GlobalSinkState &gstate, LocalSinkState &lstate) const;
	//! The finalize is called when ALL threads are finished execution. It is called only once per pipeline, and is
	//! entirely single threaded.
	//! If Finalize returns SinkResultType::FINISHED, the sink is marked as finished
	virtual SinkFinalizeType Finalize(Pipeline &pipeline, Event &event, ClientContext &context,
	                                  GlobalSinkState &gstate) const;

	virtual unique_ptr<LocalSinkState> GetLocalSinkState(ExecutionContext &context) const;
	virtual unique_ptr<GlobalSinkState> GetGlobalSinkState(ClientContext &context) const;

	//! The maximum amount of memory the operator should use per thread.
	static idx_t GetMaxThreadMemory(ClientContext &context);

	virtual bool IsSink() const {
		return false;
	}

	virtual bool ParallelSink() const {
		return false;
	}

	virtual bool RequiresBatchIndex() const {
		return false;
	}

public:
	// Pipeline construction
	virtual vector<const PhysicalOperator *> GetSources() const;
	bool AllSourcesSupportBatchIndex() const;
	bool AllOperatorsPreserveOrder() const;

	void AddPipeline(Executor &executor, shared_ptr<Pipeline> current, PipelineBuildState &state);
	virtual void BuildPipelines(Executor &executor, Pipeline &current, PipelineBuildState &state);
	void BuildChildPipeline(Executor &executor, Pipeline &current, PipelineBuildState &state,
	                        PhysicalOperator *pipeline_child);
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/table_function.hpp
//
//
//===----------------------------------------------------------------------===//








#include <functional>

namespace duckdb {

class BaseStatistics;
class LogicalGet;
class TableFilterSet;

struct TableFunctionInfo {
	DUCKDB_API virtual ~TableFunctionInfo();
};

struct GlobalTableFunctionState {
public:
	// value returned from MaxThreads when as many threads as possible should be used
	constexpr static const int64_t MAX_THREADS = 999999999;

public:
	DUCKDB_API virtual ~GlobalTableFunctionState();

	DUCKDB_API virtual idx_t MaxThreads() const {
		return 1;
	}
};

struct LocalTableFunctionState {
	DUCKDB_API virtual ~LocalTableFunctionState();
};

struct TableFunctionBindInput {
	TableFunctionBindInput(vector<Value> &inputs, named_parameter_map_t &named_parameters,
	                       vector<LogicalType> &input_table_types, vector<string> &input_table_names,
	                       TableFunctionInfo *info)
	    : inputs(inputs), named_parameters(named_parameters), input_table_types(input_table_types),
	      input_table_names(input_table_names), info(info) {
	}

	vector<Value> &inputs;
	named_parameter_map_t &named_parameters;
	vector<LogicalType> &input_table_types;
	vector<string> &input_table_names;
	TableFunctionInfo *info;
};

struct TableFunctionInitInput {
	TableFunctionInitInput(const FunctionData *bind_data_p, const vector<column_t> &column_ids_p,
	                       TableFilterSet *filters_p)
	    : bind_data(bind_data_p), column_ids(column_ids_p), filters(filters_p) {
	}

	const FunctionData *bind_data;
	const vector<column_t> &column_ids;
	TableFilterSet *filters;
};

struct TableFunctionInput {
	TableFunctionInput(const FunctionData *bind_data_p, LocalTableFunctionState *local_state_p,
	                   GlobalTableFunctionState *global_state_p)
	    : bind_data(bind_data_p), local_state(local_state_p), global_state(global_state_p) {
	}

	const FunctionData *bind_data;
	LocalTableFunctionState *local_state;
	GlobalTableFunctionState *global_state;
};

typedef unique_ptr<FunctionData> (*table_function_bind_t)(ClientContext &context, TableFunctionBindInput &input,
                                                          vector<LogicalType> &return_types, vector<string> &names);
typedef unique_ptr<GlobalTableFunctionState> (*table_function_init_global_t)(ClientContext &context,
                                                                             TableFunctionInitInput &input);
typedef unique_ptr<LocalTableFunctionState> (*table_function_init_local_t)(ExecutionContext &context,
                                                                           TableFunctionInitInput &input,
                                                                           GlobalTableFunctionState *global_state);
typedef unique_ptr<BaseStatistics> (*table_statistics_t)(ClientContext &context, const FunctionData *bind_data,
                                                         column_t column_index);
typedef void (*table_function_t)(ClientContext &context, TableFunctionInput &data, DataChunk &output);

typedef OperatorResultType (*table_in_out_function_t)(ExecutionContext &context, TableFunctionInput &data,
                                                      DataChunk &input, DataChunk &output);
typedef idx_t (*table_function_get_batch_index_t)(ClientContext &context, const FunctionData *bind_data,
                                                  LocalTableFunctionState *local_state,
                                                  GlobalTableFunctionState *global_state);
typedef double (*table_function_progress_t)(ClientContext &context, const FunctionData *bind_data,
                                            const GlobalTableFunctionState *global_state);
typedef void (*table_function_dependency_t)(unordered_set<CatalogEntry *> &dependencies, const FunctionData *bind_data);
typedef unique_ptr<NodeStatistics> (*table_function_cardinality_t)(ClientContext &context,
                                                                   const FunctionData *bind_data);
typedef void (*table_function_pushdown_complex_filter_t)(ClientContext &context, LogicalGet &get,
                                                         FunctionData *bind_data,
                                                         vector<unique_ptr<Expression>> &filters);
typedef string (*table_function_to_string_t)(const FunctionData *bind_data);

typedef void (*table_function_serialize_t)(FieldWriter &writer, const FunctionData *bind_data,
                                           const TableFunction &function);
typedef unique_ptr<FunctionData> (*table_function_deserialize_t)(ClientContext &context, FieldReader &reader,
                                                                 TableFunction &function);

class TableFunction : public SimpleNamedParameterFunction {
public:
	DUCKDB_API
	TableFunction(string name, vector<LogicalType> arguments, table_function_t function,
	              table_function_bind_t bind = nullptr, table_function_init_global_t init_global = nullptr,
	              table_function_init_local_t init_local = nullptr);
	DUCKDB_API
	TableFunction(const vector<LogicalType> &arguments, table_function_t function, table_function_bind_t bind = nullptr,
	              table_function_init_global_t init_global = nullptr, table_function_init_local_t init_local = nullptr);
	DUCKDB_API TableFunction();

	//! Bind function
	//! This function is used for determining the return type of a table producing function and returning bind data
	//! The returned FunctionData object should be constant and should not be changed during execution.
	table_function_bind_t bind;
	//! (Optional) global init function
	//! Initialize the global operator state of the function.
	//! The global operator state is used to keep track of the progress in the table function and is shared between
	//! all threads working on the table function.
	table_function_init_global_t init_global;
	//! (Optional) local init function
	//! Initialize the local operator state of the function.
	//! The local operator state is used to keep track of the progress in the table function and is thread-local.
	table_function_init_local_t init_local;
	//! The main function
	table_function_t function;
	//! The table in-out function (if this is an in-out function)
	table_in_out_function_t in_out_function;
	//! (Optional) statistics function
	//! Returns the statistics of a specified column
	table_statistics_t statistics;
	//! (Optional) dependency function
	//! Sets up which catalog entries this table function depend on
	table_function_dependency_t dependency;
	//! (Optional) cardinality function
	//! Returns the expected cardinality of this scan
	table_function_cardinality_t cardinality;
	//! (Optional) pushdown a set of arbitrary filter expressions, rather than only simple comparisons with a constant
	//! Any functions remaining in the expression list will be pushed as a regular filter after the scan
	table_function_pushdown_complex_filter_t pushdown_complex_filter;
	//! (Optional) function for rendering the operator to a string in profiling output
	table_function_to_string_t to_string;
	//! (Optional) return how much of the table we have scanned up to this point (% of the data)
	table_function_progress_t table_scan_progress;
	//! (Optional) returns the current batch index of the current scan operator
	table_function_get_batch_index_t get_batch_index;

	table_function_serialize_t serialize;
	table_function_deserialize_t deserialize;

	//! Whether or not the table function supports projection pushdown. If not supported a projection will be added
	//! that filters out unused columns.
	bool projection_pushdown;
	//! Whether or not the table function supports filter pushdown. If not supported a filter will be added
	//! that applies the table filter directly.
	bool filter_pushdown;
	//! Additional function info, passed to the bind
	shared_ptr<TableFunctionInfo> function_info;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parallel/task_scheduler.hpp
//
//
//===----------------------------------------------------------------------===//






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parallel/task.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {
class ClientContext;
class Executor;

enum class TaskExecutionMode : uint8_t { PROCESS_ALL, PROCESS_PARTIAL };

enum class TaskExecutionResult : uint8_t { TASK_FINISHED, TASK_NOT_FINISHED, TASK_ERROR };

//! Generic parallel task
class Task {
public:
	virtual ~Task() {
	}

	//! Execute the task in the specified execution mode
	//! If mode is PROCESS_ALL, Execute should always finish processing and return TASK_FINISHED
	//! If mode is PROCESS_PARTIAL, Execute can return TASK_NOT_FINISHED, in which case Execute will be called again
	//! In case of an error, TASK_ERROR is returned
	virtual TaskExecutionResult Execute(TaskExecutionMode mode) = 0;
};

//! Execute a task within an executor, including exception handling
//! This should be used within queries
class ExecutorTask : public Task {
public:
	ExecutorTask(Executor &executor);
	ExecutorTask(ClientContext &context);
	virtual ~ExecutorTask();

	Executor &executor;

public:
	virtual TaskExecutionResult ExecuteTask(TaskExecutionMode mode) = 0;
	TaskExecutionResult Execute(TaskExecutionMode mode) override;
};

} // namespace duckdb



namespace duckdb {

struct ConcurrentQueue;
struct QueueProducerToken;
class ClientContext;
class DatabaseInstance;
class TaskScheduler;

struct SchedulerThread;

struct ProducerToken {
	ProducerToken(TaskScheduler &scheduler, unique_ptr<QueueProducerToken> token);
	~ProducerToken();

	TaskScheduler &scheduler;
	unique_ptr<QueueProducerToken> token;
	mutex producer_lock;
};

//! The TaskScheduler is responsible for managing tasks and threads
class TaskScheduler {
	// timeout for semaphore wait, default 5ms
	constexpr static int64_t TASK_TIMEOUT_USECS = 5000;

public:
	TaskScheduler(DatabaseInstance &db);
	~TaskScheduler();

	static TaskScheduler &GetScheduler(ClientContext &context);
	static TaskScheduler &GetScheduler(DatabaseInstance &db);

	unique_ptr<ProducerToken> CreateProducer();
	//! Schedule a task to be executed by the task scheduler
	void ScheduleTask(ProducerToken &producer, unique_ptr<Task> task);
	//! Fetches a task from a specific producer, returns true if successful or false if no tasks were available
	bool GetTaskFromProducer(ProducerToken &token, unique_ptr<Task> &task);
	//! Run tasks forever until "marker" is set to false, "marker" must remain valid until the thread is joined
	void ExecuteForever(atomic<bool> *marker);
	//! Run tasks until `marker` is set to false, `max_tasks` have been completed, or until there are no more tasks
	//! available. Returns the number of tasks that were completed.
	idx_t ExecuteTasks(atomic<bool> *marker, idx_t max_tasks);
	//! Run tasks until `max_tasks` have been completed, or until there are no more tasks available
	void ExecuteTasks(idx_t max_tasks);

	//! Sets the amount of active threads executing tasks for the system; n-1 background threads will be launched.
	//! The main thread will also be used for execution
	void SetThreads(int32_t n);
	//! Returns the number of threads
	int32_t NumberOfThreads();

	//! Send signals to n threads, signalling for them to wake up and attempt to execute a task
	void Signal(idx_t n);

private:
	void SetThreadsInternal(int32_t n);

private:
	DatabaseInstance &db;
	//! The task queue
	unique_ptr<ConcurrentQueue> queue;
	//! The active background threads of the task scheduler
	vector<unique_ptr<SchedulerThread>> threads;
	//! Markers used by the various threads, if the markers are set to "false" the thread execution is stopped
	vector<unique_ptr<atomic<bool>>> markers;
};

} // namespace duckdb



namespace duckdb {
class Executor;
class Event;

class PipelineBuildState {
public:
	//! How much to increment batch indexes when multiple pipelines share the same source
	constexpr static idx_t BATCH_INCREMENT = 10000000000000;

public:
	//! The current recursive CTE node (if any)
	PhysicalOperator *recursive_cte = nullptr;

	//! Duplicate eliminated join scan dependencies
	unordered_map<PhysicalOperator *, Pipeline *> delim_join_dependencies;

	//! The number of pipelines that have each specific sink as their sink
	unordered_map<PhysicalOperator *, idx_t> sink_pipeline_count;

public:
	void SetPipelineSource(Pipeline &pipeline, PhysicalOperator *op);
	void SetPipelineSink(Pipeline &pipeline, PhysicalOperator *op);
	void SetPipelineOperators(Pipeline &pipeline, vector<PhysicalOperator *> operators);
	void AddPipelineOperator(Pipeline &pipeline, PhysicalOperator *op);
	void AddPipeline(Executor &executor, shared_ptr<Pipeline> pipeline);
	void AddChildPipeline(Executor &executor, Pipeline &pipeline);

	unordered_map<Pipeline *, vector<shared_ptr<Pipeline>>> &GetUnionPipelines(Executor &executor);
	unordered_map<Pipeline *, vector<shared_ptr<Pipeline>>> &GetChildPipelines(Executor &executor);

	PhysicalOperator *GetPipelineSource(Pipeline &pipeline);
	PhysicalOperator *GetPipelineSink(Pipeline &pipeline);
	vector<PhysicalOperator *> GetPipelineOperators(Pipeline &pipeline);
};

//! The Pipeline class represents an execution pipeline
class Pipeline : public std::enable_shared_from_this<Pipeline> {
	friend class Executor;
	friend class PipelineExecutor;
	friend class PipelineEvent;
	friend class PipelineFinishEvent;
	friend class PipelineBuildState;

public:
	explicit Pipeline(Executor &execution_context);

	Executor &executor;

public:
	ClientContext &GetClientContext();

	void AddDependency(shared_ptr<Pipeline> &pipeline);

	void Ready();
	void Reset();
	void ResetSource();
	void Schedule(shared_ptr<Event> &event);

	//! Finalize this pipeline
	void Finalize(Event &event);

	string ToString() const;
	void Print() const;

	//! Returns query progress
	bool GetProgress(double &current_percentage, idx_t &estimated_cardinality);

	//! Returns a list of all operators (including source and sink) involved in this pipeline
	vector<PhysicalOperator *> GetOperators() const;

	PhysicalOperator *GetSink() {
		return sink;
	}

	//! Returns whether any of the operators in the pipeline care about preserving insertion order
	bool IsOrderDependent() const;

private:
	//! Whether or not the pipeline has been readied
	bool ready;
	//! Whether or not the pipeline has been initialized
	atomic<bool> initialized;
	//! The source of this pipeline
	PhysicalOperator *source;
	//! The chain of intermediate operators
	vector<PhysicalOperator *> operators;
	//! The sink (i.e. destination) for data; this is e.g. a hash table to-be-built
	PhysicalOperator *sink;

	//! The global source state
	unique_ptr<GlobalSourceState> source_state;

	//! The parent pipelines (i.e. pipelines that are dependent on this pipeline to finish)
	vector<weak_ptr<Pipeline>> parents;
	//! The dependencies of this pipeline
	vector<weak_ptr<Pipeline>> dependencies;

	//! The base batch index of this pipeline
	idx_t base_batch_index = 0;

private:
	void ScheduleSequentialTask(shared_ptr<Event> &event);
	bool LaunchScanTasks(shared_ptr<Event> &event, idx_t max_threads);

	bool ScheduleParallel(shared_ptr<Event> &event);
};

} // namespace duckdb





namespace duckdb {
class ClientContext;
class DataChunk;
class PhysicalOperator;
class PipelineExecutor;
class OperatorState;
class QueryProfiler;
class ThreadContext;
class Task;

struct PipelineEventStack;
struct ProducerToken;
struct ScheduleEventData;

class Executor {
	friend class Pipeline;
	friend class PipelineTask;
	friend class PipelineBuildState;

public:
	explicit Executor(ClientContext &context);
	~Executor();

	ClientContext &context;

public:
	static Executor &Get(ClientContext &context);

	void Initialize(PhysicalOperator *physical_plan);
	void Initialize(unique_ptr<PhysicalOperator> physical_plan);

	void CancelTasks();
	PendingExecutionResult ExecuteTask();

	void Reset();

	vector<LogicalType> GetTypes();

	unique_ptr<DataChunk> FetchChunk();

	//! Push a new error
	void PushError(PreservedError exception);

	//! True if an error has been thrown
	bool HasError();
	//! Throw the exception that was pushed using PushError.
	//! Should only be called if HasError returns true
	void ThrowException();

	//! Work on tasks for this specific executor, until there are no tasks remaining
	void WorkOnTasks();

	//! Flush a thread context into the client context
	void Flush(ThreadContext &context);

	//! Returns the progress of the pipelines
	bool GetPipelinesProgress(double &current_progress);

	void CompletePipeline() {
		completed_pipelines++;
	}
	ProducerToken &GetToken() {
		return *producer;
	}
	void AddEvent(shared_ptr<Event> event);

	void ReschedulePipelines(const vector<shared_ptr<Pipeline>> &pipelines, vector<shared_ptr<Event>> &events);

	//! Whether or not the root of the pipeline is a result collector object
	bool HasResultCollector();
	//! Returns the query result - can only be used if `HasResultCollector` returns true
	unique_ptr<QueryResult> GetResult();

private:
	void InitializeInternal(PhysicalOperator *physical_plan);

	void ScheduleEvents();
	static void ScheduleEventsInternal(ScheduleEventData &event_data);

	static void SchedulePipeline(const shared_ptr<Pipeline> &pipeline, ScheduleEventData &event_data,
	                             vector<Pipeline *> &scheduled_pipelines);
	static void ScheduleChildPipeline(Pipeline *parent, const shared_ptr<Pipeline> &pipeline,
	                                  ScheduleEventData &event_data);
	void ExtractPipelines(shared_ptr<Pipeline> &pipeline, vector<shared_ptr<Pipeline>> &result);
	bool NextExecutor();

	void AddChildPipeline(Pipeline *current);

	void VerifyPipeline(Pipeline &pipeline);
	void VerifyPipelines();

private:
	PhysicalOperator *physical_plan;
	unique_ptr<PhysicalOperator> owned_plan;

	mutex executor_lock;
	mutex error_lock;
	//! The pipelines of the current query
	vector<shared_ptr<Pipeline>> pipelines;
	//! The root pipeline of the query
	vector<shared_ptr<Pipeline>> root_pipelines;
	//! The pipeline executor for the root pipeline
	unique_ptr<PipelineExecutor> root_executor;
	//! The current root pipeline index
	idx_t root_pipeline_idx;
	//! The producer of this query
	unique_ptr<ProducerToken> producer;
	//! Exceptions that occurred during the execution of the current query
	vector<PreservedError> exceptions;
	//! List of events
	vector<shared_ptr<Event>> events;
	//! The query profiler
	shared_ptr<QueryProfiler> profiler;

	//! The amount of completed pipelines of the query
	atomic<idx_t> completed_pipelines;
	//! The total amount of pipelines in the query
	idx_t total_pipelines;
	//! Whether or not execution is cancelled
	bool cancelled;

	//! The adjacent union pipelines of each pipeline
	//! Union pipelines have the same sink, but can be run concurrently along with this pipeline
	unordered_map<Pipeline *, vector<shared_ptr<Pipeline>>> union_pipelines;
	//! Child pipelines of this pipeline
	//! Like union pipelines, child pipelines share the same sink
	//! Unlike union pipelines, child pipelines should be run AFTER their dependencies are completed
	//! i.e. they should be run after the dependencies are completed, but before finalize is called on the sink
	unordered_map<Pipeline *, vector<shared_ptr<Pipeline>>> child_pipelines;

	//! The last pending execution result (if any)
	PendingExecutionResult execution_result;
	//! The current task in process (if any)
	unique_ptr<Task> task;
};
} // namespace duckdb


namespace duckdb {
class ClientContext;
class ClientContextLock;
class PreparedStatementData;

class PendingQueryResult : public BaseQueryResult {
	friend class ClientContext;

public:
	DUCKDB_API PendingQueryResult(shared_ptr<ClientContext> context, PreparedStatementData &statement,
	                              vector<LogicalType> types, bool allow_stream_result);
	DUCKDB_API explicit PendingQueryResult(PreservedError error_message);
	DUCKDB_API ~PendingQueryResult();

public:
	//! Executes a single task within the query, returning whether or not the query is ready.
	//! If this returns RESULT_READY, the Execute function can be called to obtain a pointer to the result.
	//! If this returns RESULT_NOT_READY, the ExecuteTask function should be called again.
	//! If this returns EXECUTION_ERROR, an error occurred during execution.
	//! The error message can be obtained by calling GetError() on the PendingQueryResult.
	DUCKDB_API PendingExecutionResult ExecuteTask();

	//! Returns the result of the query as an actual query result.
	//! This returns (mostly) instantly if ExecuteTask has been called until RESULT_READY was returned.
	DUCKDB_API unique_ptr<QueryResult> Execute();

	DUCKDB_API void Close();

private:
	shared_ptr<ClientContext> context;
	bool allow_stream_result;

private:
	void CheckExecutableInternal(ClientContextLock &lock);

	PendingExecutionResult ExecuteTaskInternal(ClientContextLock &lock);
	unique_ptr<QueryResult> ExecuteInternal(ClientContextLock &lock);
	unique_ptr<ClientContextLock> LockContext();
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/prepared_statement.hpp
//
//
//===----------------------------------------------------------------------===//








namespace duckdb {
class ClientContext;
class PreparedStatementData;

//! A prepared statement
class PreparedStatement {
public:
	//! Create a successfully prepared prepared statement object with the given name
	DUCKDB_API PreparedStatement(shared_ptr<ClientContext> context, shared_ptr<PreparedStatementData> data,
	                             string query, idx_t n_param);
	//! Create a prepared statement that was not successfully prepared
	DUCKDB_API explicit PreparedStatement(PreservedError error);

	DUCKDB_API ~PreparedStatement();

public:
	//! The client context this prepared statement belongs to
	shared_ptr<ClientContext> context;
	//! The prepared statement data
	shared_ptr<PreparedStatementData> data;
	//! The query that is being prepared
	string query;
	//! Whether or not the statement was successfully prepared
	bool success;
	//! The error message (if success = false)
	PreservedError error;
	//! The amount of bound parameters
	idx_t n_param;

public:
	//! Returns the stored error message
	const string &GetError();
	//! Returns whether or not an error occurred
	bool HasError() const;
	//! Returns the number of columns in the result
	idx_t ColumnCount();
	//! Returns the statement type of the underlying prepared statement object
	StatementType GetStatementType();
	//! Returns the underlying statement properties
	StatementProperties GetStatementProperties();
	//! Returns the result SQL types of the prepared statement
	const vector<LogicalType> &GetTypes();
	//! Returns the result names of the prepared statement
	const vector<string> &GetNames();

	//! Create a pending query result of the prepared statement with the given set of arguments
	template <typename... Args>
	unique_ptr<PendingQueryResult> PendingQuery(Args... args) {
		vector<Value> values;
		return PendingQueryRecursive(values, args...);
	}

	//! Execute the prepared statement with the given set of arguments
	template <typename... Args>
	unique_ptr<QueryResult> Execute(Args... args) {
		vector<Value> values;
		return ExecuteRecursive(values, args...);
	}

	//! Create a pending query result of the prepared statement with the given set of arguments
	DUCKDB_API unique_ptr<PendingQueryResult> PendingQuery(vector<Value> &values, bool allow_stream_result = true);

	//! Execute the prepared statement with the given set of values
	DUCKDB_API unique_ptr<QueryResult> Execute(vector<Value> &values, bool allow_stream_result = true);

private:
	unique_ptr<PendingQueryResult> PendingQueryRecursive(vector<Value> &values) {
		return PendingQuery(values);
	}

	template <typename T, typename... Args>
	unique_ptr<PendingQueryResult> PendingQueryRecursive(vector<Value> &values, T value, Args... args) {
		values.push_back(Value::CreateValue<T>(value));
		return PendingQueryRecursive(values, args...);
	}

	unique_ptr<QueryResult> ExecuteRecursive(vector<Value> &values) {
		return Execute(values);
	}

	template <typename T, typename... Args>
	unique_ptr<QueryResult> ExecuteRecursive(vector<Value> &values, T value, Args... args) {
		values.push_back(Value::CreateValue<T>(value));
		return ExecuteRecursive(values, args...);
	}
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/relation.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/join_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//===--------------------------------------------------------------------===//
// Join Types
//===--------------------------------------------------------------------===//
enum class JoinType : uint8_t {
	INVALID = 0, // invalid join type
	LEFT = 1,    // left
	RIGHT = 2,   // right
	INNER = 3,   // inner
	OUTER = 4,   // outer
	SEMI = 5,    // SEMI join returns left side row ONLY if it has a join partner, no duplicates
	ANTI = 6,    // ANTI join returns left side row ONLY if it has NO join partner, no duplicates
	MARK = 7,    // MARK join returns marker indicating whether or not there is a join partner (true), there is no join
	             // partner (false)
	SINGLE = 8   // SINGLE join is like LEFT OUTER JOIN, BUT returns at most one join partner per entry on the LEFT side
	             // (and NULL if no partner is found)
};

//! Convert join type to string
DUCKDB_API string JoinTypeToString(JoinType type);

//! True if join is left or full outer join
bool IsLeftOuterJoin(JoinType type);

//! True if join is rght or full outer join
bool IsRightOuterJoin(JoinType type);

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/relation_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//===--------------------------------------------------------------------===//
// Catalog Types
//===--------------------------------------------------------------------===//
enum class RelationType : uint8_t {
	INVALID_RELATION,
	TABLE_RELATION,
	PROJECTION_RELATION,
	FILTER_RELATION,
	EXPLAIN_RELATION,
	CROSS_PRODUCT_RELATION,
	JOIN_RELATION,
	AGGREGATE_RELATION,
	SET_OPERATION_RELATION,
	DISTINCT_RELATION,
	LIMIT_RELATION,
	ORDER_RELATION,
	CREATE_VIEW_RELATION,
	CREATE_TABLE_RELATION,
	INSERT_RELATION,
	VALUE_LIST_RELATION,
	DELETE_RELATION,
	UPDATE_RELATION,
	WRITE_CSV_RELATION,
	READ_CSV_RELATION,
	SUBQUERY_RELATION,
	TABLE_FUNCTION_RELATION,
	VIEW_RELATION,
	QUERY_RELATION
};

string RelationTypeToString(RelationType type);

} // namespace duckdb





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/client_context.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_entry/schema_catalog_entry.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_set.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/default/default_generator.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {
class ClientContext;

class DefaultGenerator {
public:
	explicit DefaultGenerator(Catalog &catalog) : catalog(catalog), created_all_entries(false) {
	}
	virtual ~DefaultGenerator() {
	}

	Catalog &catalog;
	atomic<bool> created_all_entries;

public:
	//! Creates a default entry with the specified name, or returns nullptr if no such entry can be generated
	virtual unique_ptr<CatalogEntry> CreateDefaultEntry(ClientContext &context, const string &entry_name) = 0;
	//! Get a list of all default entries in the generator
	virtual vector<string> GetDefaultEntries() = 0;
};

} // namespace duckdb








//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_entry/sequence_catalog_entry.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/create_sequence_info.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/create_info.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/field_writer.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/serializer/buffered_serializer.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

#define SERIALIZER_DEFAULT_SIZE 1024

struct BinaryData {
	unique_ptr<data_t[]> data;
	idx_t size;
};

class BufferedSerializer : public Serializer {
public:
	//! Serializes to a buffer allocated by the serializer, will expand when
	//! writing past the initial threshold
	DUCKDB_API explicit BufferedSerializer(idx_t maximum_size = SERIALIZER_DEFAULT_SIZE);
	//! Serializes to a provided (owned) data pointer
	BufferedSerializer(unique_ptr<data_t[]> data, idx_t size);
	BufferedSerializer(data_ptr_t data, idx_t size);

	idx_t maximum_size;
	data_ptr_t data;

	BinaryData blob;

public:
	void WriteData(const_data_ptr_t buffer, uint64_t write_size) override;

	//! Retrieves the data after the writing has been completed
	BinaryData GetData() {
		return std::move(blob);
	}

	void Reset() {
		blob.size = 0;
	}
};

} // namespace duckdb

#include <type_traits>

namespace duckdb {
class BufferedSerializer;

class FieldWriter {
public:
	DUCKDB_API FieldWriter(Serializer &serializer);
	DUCKDB_API ~FieldWriter();

public:
	template <class T>
	void WriteField(const T &element) {
		static_assert(std::is_trivially_destructible<T>(), "WriteField object must be trivially destructible");

		AddField();
		WriteData((const_data_ptr_t)&element, sizeof(T));
	}

	//! Write a string with a length prefix
	void WriteString(const string &val) {
		WriteStringLen((const_data_ptr_t)val.c_str(), val.size());
	}
	void WriteStringLen(const_data_ptr_t val, idx_t len) {
		AddField();
		Write<uint32_t>((uint32_t)len);
		if (len > 0) {
			WriteData(val, len);
		}
	}
	void WriteBlob(const_data_ptr_t val, idx_t len) {
		AddField();
		if (len > 0) {
			WriteData(val, len);
		}
	}

	template <class T, class CONTAINER_TYPE = vector<T>>
	void WriteList(const CONTAINER_TYPE &elements) {
		AddField();
		Write<uint32_t>(elements.size());
		for (auto &element : elements) {
			Write<T>(element);
		}
	}

	// vector<bool> yay
	template <class T, class CONTAINER_TYPE = vector<T>>
	void WriteListNoReference(const CONTAINER_TYPE &elements) {
		AddField();
		Write<uint32_t>(elements.size());
		for (auto element : elements) {
			Write<T>(element);
		}
	}

	template <class T>
	void WriteSerializable(const T &element) {
		AddField();
		element.Serialize(*buffer);
	}

	template <class T>
	void WriteSerializableList(const vector<unique_ptr<T>> &elements) {
		AddField();
		Write<uint32_t>(elements.size());
		for (idx_t i = 0; i < elements.size(); i++) {
			elements[i]->Serialize(*buffer);
		}
	}

	template <class T>
	void WriteRegularSerializableList(const vector<T> &elements) {
		AddField();
		Write<uint32_t>(elements.size());
		for (idx_t i = 0; i < elements.size(); i++) {
			elements[i].Serialize(*buffer);
		}
	}

	template <class T>
	void WriteOptional(const unique_ptr<T> &element) {
		AddField();
		Write<bool>(element ? true : false);
		if (element) {
			element->Serialize(*buffer);
		}
	}

	// Called after all fields have been written. Should always be called.
	DUCKDB_API void Finalize();

	Serializer &GetSerializer() {
		return *buffer;
	}

private:
	void AddField() {
		field_count++;
	}

	template <class T>
	void Write(const T &element) {
		WriteData((const_data_ptr_t)&element, sizeof(T));
	}

	DUCKDB_API void WriteData(const_data_ptr_t buffer, idx_t write_size);

private:
	Serializer &serializer;
	unique_ptr<BufferedSerializer> buffer;
	idx_t field_count;
	bool finalized;
};

template <>
DUCKDB_API void FieldWriter::Write(const string &val);

class FieldDeserializer : public Deserializer {
public:
	FieldDeserializer(Deserializer &root);

public:
	void ReadData(data_ptr_t buffer, idx_t read_size) override;

	void SetRemainingData(idx_t remaining_data);
	idx_t RemainingData();
	Deserializer &GetRoot() {
		return root;
	}

private:
	Deserializer &root;
	idx_t remaining_data;
};

class FieldReader {
public:
	DUCKDB_API FieldReader(Deserializer &source);
	DUCKDB_API ~FieldReader();

public:
	template <class T>
	T ReadRequired() {
		if (field_count >= max_field_count) {
			// field is not there, throw an exception
			throw SerializationException("Attempting to read a required field, but field is missing");
		}
		// field is there, read the actual value
		AddField();
		return source.Read<T>();
	}

	template <class T>
	T ReadField(T default_value) {
		if (field_count >= max_field_count) {
			// field is not there, read the default value
			return default_value;
		}
		// field is there, read the actual value
		AddField();
		return source.Read<T>();
	}

	template <class T>
	vector<T> ReadRequiredList() {
		if (field_count >= max_field_count) {
			// field is not there, throw an exception
			throw SerializationException("Attempting to read a required field, but field is missing");
		}
		AddField();
		auto result_count = source.Read<uint32_t>();
		vector<T> result;
		result.reserve(result_count);
		for (idx_t i = 0; i < result_count; i++) {
			result.push_back(source.Read<T>());
		}
		return result;
	}

	template <class T>
	set<T> ReadRequiredSet() {
		if (field_count >= max_field_count) {
			// field is not there, throw an exception
			throw SerializationException("Attempting to read a required field, but field is missing");
		}
		AddField();
		auto result_count = source.Read<uint32_t>();
		set<T> result;
		for (idx_t i = 0; i < result_count; i++) {
			result.insert(source.Read<T>());
		}
		return result;
	}

	template <class T, typename... ARGS>
	unique_ptr<T> ReadOptional(unique_ptr<T> default_value, ARGS &&...args) {
		if (field_count >= max_field_count) {
			// field is not there, read the default value
			return default_value;
		}
		// field is there, read the actual value
		AddField();
		return source.template ReadOptional<T>(std::forward<ARGS>(args)...);
	}

	template <class T, class RETURN_TYPE = unique_ptr<T>>
	RETURN_TYPE ReadSerializable(RETURN_TYPE default_value) {
		if (field_count >= max_field_count) {
			// field is not there, read the default value
			return default_value;
		}
		// field is there, read the actual value
		AddField();
		return T::Deserialize(source);
	}

	template <class T, class RETURN_TYPE = unique_ptr<T>, typename... ARGS>
	RETURN_TYPE ReadSerializable(RETURN_TYPE default_value, ARGS &&...args) {
		if (field_count >= max_field_count) {
			// field is not there, read the default value
			return default_value;
		}
		// field is there, read the actual value
		AddField();
		return T::Deserialize(source, std::forward<ARGS>(args)...);
	}

	template <class T, class RETURN_TYPE = unique_ptr<T>>
	RETURN_TYPE ReadRequiredSerializable() {
		if (field_count >= max_field_count) {
			// field is not there, throw an exception
			throw SerializationException("Attempting to read mandatory field, but field is missing");
		}
		// field is there, read the actual value
		AddField();
		return T::Deserialize(source);
	}

	template <class T, class RETURN_TYPE = unique_ptr<T>, typename... ARGS>
	RETURN_TYPE ReadRequiredSerializable(ARGS &&...args) {
		if (field_count >= max_field_count) {
			// field is not there, throw an exception
			throw SerializationException("Attempting to read mandatory field, but field is missing");
		}
		// field is there, read the actual value
		AddField();
		return T::Deserialize(source, std::forward<ARGS>(args)...);
	}

	template <class T, class RETURN_TYPE = unique_ptr<T>, typename... ARGS>
	vector<RETURN_TYPE> ReadRequiredSerializableList(ARGS &&...args) {
		if (field_count >= max_field_count) {
			// field is not there, throw an exception
			throw SerializationException("Attempting to read mandatory field, but field is missing");
		}
		// field is there, read the actual value
		AddField();
		auto result_count = source.Read<uint32_t>();

		vector<RETURN_TYPE> result;
		for (idx_t i = 0; i < result_count; i++) {
			result.push_back(T::Deserialize(source, std::forward<ARGS>(args)...));
		}
		return result;
	}

	void ReadBlob(data_ptr_t result, idx_t read_size) {
		if (field_count >= max_field_count) {
			// field is not there, throw an exception
			throw SerializationException("Attempting to read a required field, but field is missing");
		}
		// field is there, read the actual value
		AddField();
		source.ReadData(result, read_size);
	}

	//! Called after all fields have been read. Should always be called.
	DUCKDB_API void Finalize();

	Deserializer &GetSource() {
		return source;
	}

private:
	void AddField() {
		field_count++;
	}

private:
	FieldDeserializer source;
	idx_t field_count;
	idx_t max_field_count;
	idx_t total_size;
	bool finalized;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/parse_info.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

struct ParseInfo {
	virtual ~ParseInfo() {
	}
};

} // namespace duckdb


namespace duckdb {

enum class OnCreateConflict : uint8_t {
	// Standard: throw error
	ERROR_ON_CONFLICT,
	// CREATE IF NOT EXISTS, silently do nothing on conflict
	IGNORE_ON_CONFLICT,
	// CREATE OR REPLACE
	REPLACE_ON_CONFLICT
};

struct CreateInfo : public ParseInfo {
	explicit CreateInfo(CatalogType type, string schema = DEFAULT_SCHEMA)
	    : type(type), schema(schema), on_conflict(OnCreateConflict::ERROR_ON_CONFLICT), temporary(false),
	      internal(false) {
	}
	~CreateInfo() override {
	}

	//! The to-be-created catalog type
	CatalogType type;
	//! The schema name of the entry
	string schema;
	//! What to do on create conflict
	OnCreateConflict on_conflict;
	//! Whether or not the entry is temporary
	bool temporary;
	//! Whether or not the entry is an internal entry
	bool internal;
	//! The SQL string of the CREATE statement
	string sql;

protected:
	virtual void SerializeInternal(Serializer &) const = 0;

	void DeserializeBase(Deserializer &deserializer);

public:
	void Serialize(Serializer &serializer) const;

	static unique_ptr<CreateInfo> Deserialize(Deserializer &deserializer);

	virtual unique_ptr<CreateInfo> Copy() const = 0;

	DUCKDB_API void CopyProperties(CreateInfo &other) const;
};

} // namespace duckdb



namespace duckdb {

enum class SequenceInfo : uint8_t {
	// Sequence start
	SEQ_START,
	// Sequence increment
	SEQ_INC,
	// Sequence minimum value
	SEQ_MIN,
	// Sequence maximum value
	SEQ_MAX,
	// Sequence cycle option
	SEQ_CYCLE,
	// Sequence owner table
	SEQ_OWN
};

struct CreateSequenceInfo : public CreateInfo {
	CreateSequenceInfo()
	    : CreateInfo(CatalogType::SEQUENCE_ENTRY, INVALID_SCHEMA), name(string()), usage_count(0), increment(1),
	      min_value(1), max_value(NumericLimits<int64_t>::Maximum()), start_value(1), cycle(false) {
	}

	//! Sequence name to create
	string name;
	//! Usage count of the sequence
	uint64_t usage_count;
	//! The increment value
	int64_t increment;
	//! The minimum value of the sequence
	int64_t min_value;
	//! The maximum value of the sequence
	int64_t max_value;
	//! The start value of the sequence
	int64_t start_value;
	//! Whether or not the sequence cycles
	bool cycle;

public:
	unique_ptr<CreateInfo> Copy() const override {
		auto result = make_unique<CreateSequenceInfo>();
		CopyProperties(*result);
		result->name = name;
		result->schema = schema;
		result->usage_count = usage_count;
		result->increment = increment;
		result->min_value = min_value;
		result->max_value = max_value;
		result->start_value = start_value;
		result->cycle = cycle;
		return move(result);
	}

protected:
	void SerializeInternal(Serializer &) const override {
		throw NotImplementedException("Cannot serialize '%s'", CatalogTypeToString(type));
	}
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/alter_table_info.hpp
//
//
//===----------------------------------------------------------------------===//








namespace duckdb {

enum class AlterType : uint8_t {
	INVALID = 0,
	ALTER_TABLE = 1,
	ALTER_VIEW = 2,
	ALTER_SEQUENCE = 3,
	CHANGE_OWNERSHIP = 4
};

enum AlterForeignKeyType : uint8_t { AFT_ADD = 0, AFT_DELETE = 1 };

struct AlterInfo : public ParseInfo {
	AlterInfo(AlterType type, string schema, string name, bool if_exists);
	~AlterInfo() override;

	AlterType type;
	//! if exists
	bool if_exists;
	//! Schema name to alter
	string schema;
	//! Entry name to alter
	string name;

public:
	virtual CatalogType GetCatalogType() const = 0;
	virtual unique_ptr<AlterInfo> Copy() const = 0;
	void Serialize(Serializer &serializer) const;
	virtual void Serialize(FieldWriter &writer) const = 0;
	static unique_ptr<AlterInfo> Deserialize(Deserializer &source);
};

//===--------------------------------------------------------------------===//
// Change Ownership
//===--------------------------------------------------------------------===//
struct ChangeOwnershipInfo : public AlterInfo {
	ChangeOwnershipInfo(CatalogType entry_catalog_type, string entry_schema, string entry_name, string owner_schema,
	                    string owner_name, bool if_exists);

	// Catalog type refers to the entry type, since this struct is usually built from an
	// ALTER <TYPE> <schema>.<name> OWNED BY <owner_schema>.<owner_name> statement
	// here it is only possible to know the type of who is to be owned
	CatalogType entry_catalog_type;

	string owner_schema;
	string owner_name;

public:
	CatalogType GetCatalogType() const override;
	unique_ptr<AlterInfo> Copy() const override;
	void Serialize(FieldWriter &writer) const override;
};

//===--------------------------------------------------------------------===//
// Alter Table
//===--------------------------------------------------------------------===//
enum class AlterTableType : uint8_t {
	INVALID = 0,
	RENAME_COLUMN = 1,
	RENAME_TABLE = 2,
	ADD_COLUMN = 3,
	REMOVE_COLUMN = 4,
	ALTER_COLUMN_TYPE = 5,
	SET_DEFAULT = 6,
	FOREIGN_KEY_CONSTRAINT = 7,
	SET_NOT_NULL = 8,
	DROP_NOT_NULL = 9
};

struct AlterTableInfo : public AlterInfo {
	AlterTableInfo(AlterTableType type, string schema, string table, bool if_exists);
	~AlterTableInfo() override;

	AlterTableType alter_table_type;

public:
	CatalogType GetCatalogType() const override;
	void Serialize(FieldWriter &writer) const override;
	virtual void SerializeAlterTable(FieldWriter &writer) const = 0;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader);
};

//===--------------------------------------------------------------------===//
// RenameColumnInfo
//===--------------------------------------------------------------------===//
struct RenameColumnInfo : public AlterTableInfo {
	RenameColumnInfo(string schema, string table, bool if_exists, string old_name_p, string new_name_p);
	~RenameColumnInfo() override;

	//! Column old name
	string old_name;
	//! Column new name
	string new_name;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterTable(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string table, bool if_exists);
};

//===--------------------------------------------------------------------===//
// RenameTableInfo
//===--------------------------------------------------------------------===//
struct RenameTableInfo : public AlterTableInfo {
	RenameTableInfo(string schema, string table, bool if_exists, string new_name);
	~RenameTableInfo() override;

	//! Relation new name
	string new_table_name;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterTable(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string table, bool if_exists);
};

//===--------------------------------------------------------------------===//
// AddColumnInfo
//===--------------------------------------------------------------------===//
struct AddColumnInfo : public AlterTableInfo {
	AddColumnInfo(string schema, string table, bool if_exists, ColumnDefinition new_column, bool if_column_not_exists);
	~AddColumnInfo() override;

	//! New column
	ColumnDefinition new_column;
	//! Whether or not an error should be thrown if the column exist
	bool if_column_not_exists;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterTable(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string table, bool if_exists);
};

//===--------------------------------------------------------------------===//
// RemoveColumnInfo
//===--------------------------------------------------------------------===//
struct RemoveColumnInfo : public AlterTableInfo {
	RemoveColumnInfo(string schema, string table, bool if_exists, string removed_column, bool if_column_exists,
	                 bool cascade);
	~RemoveColumnInfo() override;

	//! The column to remove
	string removed_column;
	//! Whether or not an error should be thrown if the column does not exist
	bool if_column_exists;
	//! Whether or not the column should be removed if a dependency conflict arises (used by GENERATED columns)
	bool cascade;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterTable(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string table, bool if_exists);
};

//===--------------------------------------------------------------------===//
// ChangeColumnTypeInfo
//===--------------------------------------------------------------------===//
struct ChangeColumnTypeInfo : public AlterTableInfo {
	ChangeColumnTypeInfo(string schema, string table, bool if_exists, string column_name, LogicalType target_type,
	                     unique_ptr<ParsedExpression> expression);
	~ChangeColumnTypeInfo() override;

	//! The column name to alter
	string column_name;
	//! The target type of the column
	LogicalType target_type;
	//! The expression used for data conversion
	unique_ptr<ParsedExpression> expression;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterTable(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string table, bool if_exists);
};

//===--------------------------------------------------------------------===//
// SetDefaultInfo
//===--------------------------------------------------------------------===//
struct SetDefaultInfo : public AlterTableInfo {
	SetDefaultInfo(string schema, string table, bool if_exists, string column_name,
	               unique_ptr<ParsedExpression> new_default);
	~SetDefaultInfo() override;

	//! The column name to alter
	string column_name;
	//! The expression used for data conversion
	unique_ptr<ParsedExpression> expression;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterTable(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string table, bool if_exists);
};

//===--------------------------------------------------------------------===//
// AlterForeignKeyInfo
//===--------------------------------------------------------------------===//
struct AlterForeignKeyInfo : public AlterTableInfo {
	AlterForeignKeyInfo(string schema, string table, bool if_exists, string fk_table, vector<string> pk_columns,
	                    vector<string> fk_columns, vector<idx_t> pk_keys, vector<idx_t> fk_keys,
	                    AlterForeignKeyType type);
	~AlterForeignKeyInfo() override;

	string fk_table;
	vector<string> pk_columns;
	vector<string> fk_columns;
	vector<idx_t> pk_keys;
	vector<idx_t> fk_keys;
	AlterForeignKeyType type;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterTable(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string table, bool if_exists);
};

//===--------------------------------------------------------------------===//
// Alter View
//===--------------------------------------------------------------------===//
enum class AlterViewType : uint8_t { INVALID = 0, RENAME_VIEW = 1 };

struct AlterViewInfo : public AlterInfo {
	AlterViewInfo(AlterViewType type, string schema, string view, bool if_exists);
	~AlterViewInfo() override;

	AlterViewType alter_view_type;

public:
	CatalogType GetCatalogType() const override;
	void Serialize(FieldWriter &writer) const override;
	virtual void SerializeAlterView(FieldWriter &writer) const = 0;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader);
};

//===--------------------------------------------------------------------===//
// RenameViewInfo
//===--------------------------------------------------------------------===//
struct RenameViewInfo : public AlterViewInfo {
	RenameViewInfo(string schema, string view, bool if_exists, string new_name);
	~RenameViewInfo() override;

	//! Relation new name
	string new_view_name;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterView(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string view, bool if_exists);
};

//===--------------------------------------------------------------------===//
// SetNotNullInfo
//===--------------------------------------------------------------------===//
struct SetNotNullInfo : public AlterTableInfo {
	SetNotNullInfo(string schema, string table, bool if_exists, string column_name);
	~SetNotNullInfo() override;

	//! The column name to alter
	string column_name;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterTable(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string table, bool if_exists);
};

//===--------------------------------------------------------------------===//
// DropNotNullInfo
//===--------------------------------------------------------------------===//
struct DropNotNullInfo : public AlterTableInfo {
	DropNotNullInfo(string schema, string table, bool if_exists, string column_name);
	~DropNotNullInfo() override;

	//! The column name to alter
	string column_name;

public:
	unique_ptr<AlterInfo> Copy() const override;
	void SerializeAlterTable(FieldWriter &writer) const override;
	static unique_ptr<AlterInfo> Deserialize(FieldReader &reader, string schema, string table, bool if_exists);
};

} // namespace duckdb


namespace duckdb {
class Serializer;
class Deserializer;

struct SequenceValue {
	SequenceValue() : usage_count(0), counter(-1) {
	}
	SequenceValue(uint64_t usage_count, int64_t counter) : usage_count(usage_count), counter(counter) {
	}

	uint64_t usage_count;
	int64_t counter;
};

//! A sequence catalog entry
class SequenceCatalogEntry : public StandardEntry {
public:
	//! Create a real TableCatalogEntry and initialize storage for it
	SequenceCatalogEntry(Catalog *catalog, SchemaCatalogEntry *schema, CreateSequenceInfo *info);

	//! Lock for getting a value on the sequence
	mutex lock;
	//! The amount of times the sequence has been used
	uint64_t usage_count;
	//! The sequence counter
	int64_t counter;
	//! The most recently returned value
	int64_t last_value;
	//! The increment value
	int64_t increment;
	//! The minimum value of the sequence
	int64_t start_value;
	//! The minimum value of the sequence
	int64_t min_value;
	//! The maximum value of the sequence
	int64_t max_value;
	//! Whether or not the sequence cycles
	bool cycle;

public:
	//! Serialize the meta information of the SequenceCatalogEntry a serializer
	virtual void Serialize(Serializer &serializer);
	//! Deserializes to a CreateTableInfo
	static unique_ptr<CreateSequenceInfo> Deserialize(Deserializer &source);

	string ToSQL() override;

	CatalogEntry *AlterOwnership(ClientContext &context, AlterInfo *info);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/transaction/transaction.hpp
//
//
//===----------------------------------------------------------------------===//






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/transaction/undo_buffer.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/undo_flags.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class UndoFlags : uint32_t { // far too big but aligned (TM)
	EMPTY_ENTRY = 0,
	CATALOG_ENTRY = 1,
	INSERT_TUPLE = 2,
	DELETE_TUPLE = 3,
	UPDATE_TUPLE = 4
};

} // namespace duckdb



namespace duckdb {

class WriteAheadLog;

//! The undo buffer of a transaction is used to hold previous versions of tuples
//! that might be required in the future (because of rollbacks or previous
//! transactions accessing them)
class UndoBuffer {
public:
	struct IteratorState {
		ArenaChunk *current;
		data_ptr_t start;
		data_ptr_t end;
	};

public:
	UndoBuffer(const shared_ptr<ClientContext> &context);

	//! Reserve space for an entry of the specified type and length in the undo
	//! buffer
	data_ptr_t CreateEntry(UndoFlags type, idx_t len);

	bool ChangesMade();
	idx_t EstimatedSize();

	//! Cleanup the undo buffer
	void Cleanup();
	//! Commit the changes made in the UndoBuffer: should be called on commit
	void Commit(UndoBuffer::IteratorState &iterator_state, WriteAheadLog *log, transaction_t commit_id);
	//! Revert committed changes made in the UndoBuffer up until the currently committed state
	void RevertCommit(UndoBuffer::IteratorState &iterator_state, transaction_t transaction_id);
	//! Rollback the changes made in this UndoBuffer: should be called on
	//! rollback
	void Rollback() noexcept;

private:
	ClientContext &context;
	ArenaAllocator allocator;

private:
	template <class T>
	void IterateEntries(UndoBuffer::IteratorState &state, T &&callback);
	template <class T>
	void IterateEntries(UndoBuffer::IteratorState &state, UndoBuffer::IteratorState &end_state, T &&callback);
	template <class T>
	void ReverseIterateEntries(T &&callback);
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/transaction/local_storage.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/chunk_collection.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {
class Allocator;
class ClientContext;

//!  A ChunkCollection represents a set of DataChunks that all have the same
//!  types
/*!
    A ChunkCollection represents a set of DataChunks concatenated together in a
   list. Individual values of the collection can be iterated over using the
   iterator. It is also possible to iterate directly over the chunks for more
   direct access.
*/
class ChunkCollection {
public:
	ChunkCollection(Allocator &allocator);
	ChunkCollection(ClientContext &context);

	//! The amount of columns in the ChunkCollection
	DUCKDB_API vector<LogicalType> &Types() {
		return types;
	}
	const vector<LogicalType> &Types() const {
		return types;
	}

	//! The amount of rows in the ChunkCollection
	DUCKDB_API const idx_t &Count() const {
		return count;
	}

	//! The amount of columns in the ChunkCollection
	DUCKDB_API idx_t ColumnCount() const {
		return types.size();
	}

	//! Append a new DataChunk directly to this ChunkCollection
	DUCKDB_API void Append(DataChunk &new_chunk);

	//! Append a new DataChunk directly to this ChunkCollection
	DUCKDB_API void Append(unique_ptr<DataChunk> new_chunk);

	//! Append another ChunkCollection directly to this ChunkCollection
	DUCKDB_API void Append(ChunkCollection &other);

	//! Merge is like Append but messes up the order and destroys the other collection
	DUCKDB_API void Merge(ChunkCollection &other);

	//! Fuse adds new columns to the right of the collection
	DUCKDB_API void Fuse(ChunkCollection &other);

	DUCKDB_API void Verify();

	//! Gets the value of the column at the specified index
	DUCKDB_API Value GetValue(idx_t column, idx_t index);
	//! Sets the value of the column at the specified index
	DUCKDB_API void SetValue(idx_t column, idx_t index, const Value &value);

	//! Copy a single cell to a target vector
	DUCKDB_API void CopyCell(idx_t column, idx_t index, Vector &target, idx_t target_offset);

	DUCKDB_API string ToString() const;
	DUCKDB_API void Print() const;

	//! Gets a reference to the chunk at the given index
	DUCKDB_API DataChunk &GetChunkForRow(idx_t row_index) {
		return *chunks[LocateChunk(row_index)];
	}

	//! Gets a reference to the chunk at the given index
	DUCKDB_API DataChunk &GetChunk(idx_t chunk_index) {
		D_ASSERT(chunk_index < chunks.size());
		return *chunks[chunk_index];
	}
	const DataChunk &GetChunk(idx_t chunk_index) const {
		D_ASSERT(chunk_index < chunks.size());
		return *chunks[chunk_index];
	}

	DUCKDB_API const vector<unique_ptr<DataChunk>> &Chunks() {
		return chunks;
	}

	DUCKDB_API idx_t ChunkCount() const {
		return chunks.size();
	}

	DUCKDB_API void Reset() {
		count = 0;
		chunks.clear();
		types.clear();
	}

	DUCKDB_API unique_ptr<DataChunk> Fetch() {
		if (ChunkCount() == 0) {
			return nullptr;
		}

		auto res = move(chunks[0]);
		chunks.erase(chunks.begin() + 0);
		return res;
	}

	DUCKDB_API void Sort(vector<OrderType> &desc, vector<OrderByNullType> &null_order, idx_t result[]);
	//! Reorders the rows in the collection according to the given indices.
	DUCKDB_API void Reorder(idx_t order[]);

	//! Returns true if the ChunkCollections are equivalent
	DUCKDB_API bool Equals(ChunkCollection &other);

	//! Locates the chunk that belongs to the specific index
	DUCKDB_API idx_t LocateChunk(idx_t index) {
		idx_t result = index / STANDARD_VECTOR_SIZE;
		D_ASSERT(result < chunks.size());
		return result;
	}

	Allocator &GetAllocator() {
		return allocator;
	}

private:
	Allocator &allocator;
	//! The total amount of elements in the collection
	idx_t count;
	//! The set of data chunks in the collection
	vector<unique_ptr<DataChunk>> chunks;
	//! The types of the ChunkCollection
	vector<LogicalType> types;
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/storage/table/scan_state.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/storage/storage_lock.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {
class StorageLock;

enum class StorageLockType { SHARED = 0, EXCLUSIVE = 1 };

class StorageLockKey {
public:
	StorageLockKey(StorageLock &lock, StorageLockType type);
	~StorageLockKey();

private:
	StorageLock &lock;
	StorageLockType type;
};

class StorageLock {
	friend class StorageLockKey;

public:
	StorageLock();

	//! Get an exclusive lock
	unique_ptr<StorageLockKey> GetExclusiveLock();
	//! Get a shared lock
	unique_ptr<StorageLockKey> GetSharedLock();

private:
	mutex exclusive_lock;
	atomic<idx_t> read_count;

private:
	//! Release an exclusive lock
	void ReleaseExclusiveLock();
	//! Release a shared lock
	void ReleaseSharedLock();
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/adaptive_filter.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_aggregate_expression.hpp
//
//
//===----------------------------------------------------------------------===//





#include <memory>

namespace duckdb {
class BoundAggregateExpression : public Expression {
public:
	BoundAggregateExpression(AggregateFunction function, vector<unique_ptr<Expression>> children,
	                         unique_ptr<Expression> filter, unique_ptr<FunctionData> bind_info, bool distinct);

	//! The bound function expression
	AggregateFunction function;
	//! List of arguments to the function
	vector<unique_ptr<Expression>> children;
	//! The bound function data (if any)
	unique_ptr<FunctionData> bind_info;
	//! True to aggregate on distinct values
	bool distinct;

	//! Filter for this aggregate
	unique_ptr<Expression> filter;

public:
	bool IsAggregate() const override {
		return true;
	}
	bool IsFoldable() const override {
		return false;
	}
	bool PropagatesNullValues() const override;

	string ToString() const override;

	hash_t Hash() const override;
	bool Equals(const BaseExpression *other) const override;
	unique_ptr<Expression> Copy() override;
	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_between_expression.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

class BoundBetweenExpression : public Expression {
public:
	BoundBetweenExpression(unique_ptr<Expression> input, unique_ptr<Expression> lower, unique_ptr<Expression> upper,
	                       bool lower_inclusive, bool upper_inclusive);

	unique_ptr<Expression> input;
	unique_ptr<Expression> lower;
	unique_ptr<Expression> upper;
	bool lower_inclusive;
	bool upper_inclusive;

public:
	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;
	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);

public:
	ExpressionType LowerComparisonType() {
		return lower_inclusive ? ExpressionType::COMPARE_GREATERTHANOREQUALTO : ExpressionType::COMPARE_GREATERTHAN;
	}
	ExpressionType UpperComparisonType() {
		return upper_inclusive ? ExpressionType::COMPARE_LESSTHANOREQUALTO : ExpressionType::COMPARE_LESSTHAN;
	}
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_case_expression.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

struct BoundCaseCheck {
	unique_ptr<Expression> when_expr;
	unique_ptr<Expression> then_expr;

	void Serialize(Serializer &serializer) const;
	static BoundCaseCheck Deserialize(Deserializer &source, PlanDeserializationState &state);
};

class BoundCaseExpression : public Expression {
public:
	BoundCaseExpression(LogicalType type);
	BoundCaseExpression(unique_ptr<Expression> when_expr, unique_ptr<Expression> then_expr,
	                    unique_ptr<Expression> else_expr);

	vector<BoundCaseCheck> case_checks;
	unique_ptr<Expression> else_expr;

public:
	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_cast_expression.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

class BoundCastExpression : public Expression {
public:
	BoundCastExpression(unique_ptr<Expression> child, LogicalType target_type, bool try_cast = false);

	//! The child type
	unique_ptr<Expression> child;
	//! Whether to use try_cast or not. try_cast converts cast failures into NULLs instead of throwing an error.
	bool try_cast;

public:
	LogicalType source_type() {
		D_ASSERT(child->return_type.IsValid());
		return child->return_type;
	}

	//! Cast an expression to the specified SQL type if required
	static unique_ptr<Expression> AddCastToType(unique_ptr<Expression> expr, const LogicalType &target_type,
	                                            bool try_cast = false);
	//! Returns true if a cast is invertible (i.e. CAST(s -> t -> s) = s for all values of s). This is not true for e.g.
	//! boolean casts, because that can be e.g. -1 -> TRUE -> 1. This is necessary to prevent some optimizer bugs.
	static bool CastIsInvertible(const LogicalType &source_type, const LogicalType &target_type);

	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_columnref_expression.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

class FieldReader;
class FieldWriter;

//! A BoundColumnRef expression represents a ColumnRef expression that was bound to an actual table and column index. It
//! is not yet executable, however. The ColumnBindingResolver transforms the BoundColumnRefExpressions into
//! BoundExpressions, which refer to indexes into the physical chunks that pass through the executor.
class BoundColumnRefExpression : public Expression {
public:
	BoundColumnRefExpression(LogicalType type, ColumnBinding binding, idx_t depth = 0);
	BoundColumnRefExpression(string alias, LogicalType type, ColumnBinding binding, idx_t depth = 0);

	//! Column index set by the binder, used to generate the final BoundExpression
	ColumnBinding binding;
	//! The subquery depth (i.e. depth 0 = current query, depth 1 = parent query, depth 2 = parent of parent, etc...).
	//! This is only non-zero for correlated expressions inside subqueries.
	idx_t depth;

public:
	bool IsScalar() const override {
		return false;
	}
	bool IsFoldable() const override {
		return false;
	}

	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;
	hash_t Hash() const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_comparison_expression.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

class BoundComparisonExpression : public Expression {
public:
	BoundComparisonExpression(ExpressionType type, unique_ptr<Expression> left, unique_ptr<Expression> right);

	unique_ptr<Expression> left;
	unique_ptr<Expression> right;

public:
	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;
	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);

public:
	static LogicalType BindComparison(LogicalType left_type, LogicalType right_type);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_conjunction_expression.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

class BoundConjunctionExpression : public Expression {
public:
	explicit BoundConjunctionExpression(ExpressionType type);
	BoundConjunctionExpression(ExpressionType type, unique_ptr<Expression> left, unique_ptr<Expression> right);

	vector<unique_ptr<Expression>> children;

public:
	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;

	bool PropagatesNullValues() const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_constant_expression.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

class BoundConstantExpression : public Expression {
public:
	explicit BoundConstantExpression(Value value);

	Value value;

public:
	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;
	hash_t Hash() const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_default_expression.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

class BoundDefaultExpression : public Expression {
public:
	explicit BoundDefaultExpression(LogicalType type = LogicalType())
	    : Expression(ExpressionType::VALUE_DEFAULT, ExpressionClass::BOUND_DEFAULT, type) {
	}

public:
	bool IsScalar() const override {
		return false;
	}
	bool IsFoldable() const override {
		return false;
	}

	string ToString() const override {
		return "DEFAULT";
	}

	unique_ptr<Expression> Copy() override {
		return make_unique<BoundDefaultExpression>(return_type);
	}

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_function_expression.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {
class ScalarFunctionCatalogEntry;

//! Represents a function call that has been bound to a base function
class BoundFunctionExpression : public Expression {
public:
	BoundFunctionExpression(LogicalType return_type, ScalarFunction bound_function,
	                        vector<unique_ptr<Expression>> arguments, unique_ptr<FunctionData> bind_info,
	                        bool is_operator = false);

	//! The bound function expression
	ScalarFunction function;
	//! List of child-expressions of the function
	vector<unique_ptr<Expression>> children;
	//! The bound function data (if any)
	unique_ptr<FunctionData> bind_info;
	//! Whether or not the function is an operator, only used for rendering
	bool is_operator;

public:
	bool HasSideEffects() const override;
	bool IsFoldable() const override;
	string ToString() const override;
	bool PropagatesNullValues() const override;
	hash_t Hash() const override;
	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;
	void Verify() const override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_lambda_expression.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/expression/lambda_expression.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

//! LambdaExpression represents either:
//!  1. A lambda operator that can be used for e.g. mapping an expression to a list
//!  2. An OperatorExpression with the "->" operator
//! Lambda expressions are written in the form of "params -> expr", e.g. "x -> x + 1"
class LambdaExpression : public ParsedExpression {
public:
	LambdaExpression(unique_ptr<ParsedExpression> lhs, unique_ptr<ParsedExpression> expr);

	// we need the context to determine if this is a list of column references or an expression (for JSON)
	unique_ptr<ParsedExpression> lhs;

	vector<unique_ptr<ParsedExpression>> params;
	unique_ptr<ParsedExpression> expr;

public:
	string ToString() const override;

	static bool Equals(const LambdaExpression *a, const LambdaExpression *b);
	hash_t Hash() const override;

	unique_ptr<ParsedExpression> Copy() const override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<ParsedExpression> Deserialize(ExpressionType type, FieldReader &source);
};

} // namespace duckdb


namespace duckdb {

class BoundLambdaExpression : public Expression {
public:
	BoundLambdaExpression(ExpressionType type_p, LogicalType return_type_p, unique_ptr<Expression> lambda_expr_p,
	                      idx_t parameter_count_p);

	unique_ptr<Expression> lambda_expr;
	vector<unique_ptr<Expression>> captures;
	idx_t parameter_count;

public:
	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_operator_expression.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

class BoundOperatorExpression : public Expression {
public:
	BoundOperatorExpression(ExpressionType type, LogicalType return_type);

	vector<unique_ptr<Expression>> children;

public:
	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_parameter_expression.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_parameter_data.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {

struct BoundParameterData {
	BoundParameterData() {
	}
	BoundParameterData(Value val) : value(move(val)), return_type(value.type()) {
	}

	Value value;
	LogicalType return_type;

public:
	void Serialize(Serializer &serializer) const {
		FieldWriter writer(serializer);
		value.Serialize(writer.GetSerializer());
		writer.WriteSerializable(return_type);
		writer.Finalize();
	}

	static shared_ptr<BoundParameterData> Deserialize(Deserializer &source) {
		FieldReader reader(source);
		auto value = Value::Deserialize(reader.GetSource());
		auto result = make_shared<BoundParameterData>(move(value));
		result->return_type = reader.ReadRequiredSerializable<LogicalType, LogicalType>();
		reader.Finalize();
		return result;
	}
};

struct BoundParameterMap {
	BoundParameterMap(vector<BoundParameterData> &parameter_data) : parameter_data(parameter_data) {
	}

	bound_parameter_map_t parameters;
	vector<BoundParameterData> &parameter_data;

	LogicalType GetReturnType(idx_t index) {
		if (index >= parameter_data.size()) {
			return LogicalTypeId::UNKNOWN;
		}
		return parameter_data[index].return_type;
	}
};

} // namespace duckdb


namespace duckdb {

class BoundParameterExpression : public Expression {
public:
	explicit BoundParameterExpression(idx_t parameter_nr);

	idx_t parameter_nr;
	shared_ptr<BoundParameterData> parameter_data;

public:
	//! Invalidate a bound parameter expression - forcing a rebind on any subsequent filters
	DUCKDB_API static void Invalidate(Expression &expr);
	//! Invalidate all parameters within an expression
	DUCKDB_API static void InvalidateRecursive(Expression &expr);

	bool IsScalar() const override;
	bool HasParameter() const override;
	bool IsFoldable() const override;

	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;
	hash_t Hash() const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_reference_expression.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//! A BoundReferenceExpression represents a physical index into a DataChunk
class BoundReferenceExpression : public Expression {
public:
	BoundReferenceExpression(string alias, LogicalType type, idx_t index);
	BoundReferenceExpression(LogicalType type, storage_t index);

	//! Index used to access data in the chunks
	storage_t index;

public:
	bool IsScalar() const override {
		return false;
	}
	bool IsFoldable() const override {
		return false;
	}

	string ToString() const override;

	hash_t Hash() const override;
	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_subquery_expression.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/subquery_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//===--------------------------------------------------------------------===//
// Subquery Types
//===--------------------------------------------------------------------===//
enum class SubqueryType : uint8_t {
	INVALID = 0,
	SCALAR = 1,     // Regular scalar subquery
	EXISTS = 2,     // EXISTS (SELECT...)
	NOT_EXISTS = 3, // NOT EXISTS(SELECT...)
	ANY = 4,        // x = ANY(SELECT...) OR x IN (SELECT...)
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/binder.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/tokens.hpp
//
//
//===----------------------------------------------------------------------===//



namespace duckdb {

//===--------------------------------------------------------------------===//
// Statements
//===--------------------------------------------------------------------===//
class SQLStatement;

class AlterStatement;
class CallStatement;
class CopyStatement;
class CreateStatement;
class DeleteStatement;
class DropStatement;
class ExtensionStatement;
class InsertStatement;
class SelectStatement;
class TransactionStatement;
class UpdateStatement;
class PrepareStatement;
class ExecuteStatement;
class PragmaStatement;
class ShowStatement;
class ExplainStatement;
class ExportStatement;
class VacuumStatement;
class RelationStatement;
class SetStatement;
class LoadStatement;
class LogicalPlanStatement;

//===--------------------------------------------------------------------===//
// Query Node
//===--------------------------------------------------------------------===//
class QueryNode;
class SelectNode;
class SetOperationNode;
class RecursiveCTENode;

//===--------------------------------------------------------------------===//
// Expressions
//===--------------------------------------------------------------------===//
class ParsedExpression;

class BetweenExpression;
class CaseExpression;
class CastExpression;
class CollateExpression;
class ColumnRefExpression;
class ComparisonExpression;
class ConjunctionExpression;
class ConstantExpression;
class DefaultExpression;
class FunctionExpression;
class LambdaExpression;
class OperatorExpression;
class ParameterExpression;
class PositionalReferenceExpression;
class StarExpression;
class SubqueryExpression;
class WindowExpression;

//===--------------------------------------------------------------------===//
// Constraints
//===--------------------------------------------------------------------===//
class Constraint;

class NotNullConstraint;
class CheckConstraint;
class UniqueConstraint;
class ForeignKeyConstraint;

//===--------------------------------------------------------------------===//
// TableRefs
//===--------------------------------------------------------------------===//
class TableRef;

class BaseTableRef;
class CrossProductRef;
class JoinRef;
class SubqueryRef;
class TableFunctionRef;
class EmptyTableRef;
class ExpressionListRef;

//===--------------------------------------------------------------------===//
// Other
//===--------------------------------------------------------------------===//
struct SampleOptions;

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/bind_context.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_entry/table_function_catalog_entry.hpp
//
//
//===----------------------------------------------------------------------===//






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/function_set.hpp
//
//
//===----------------------------------------------------------------------===//






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/pragma_function.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/pragma_info.hpp
//
//
//===----------------------------------------------------------------------===//








namespace duckdb {

enum class PragmaType : uint8_t { PRAGMA_STATEMENT, PRAGMA_CALL };

struct PragmaInfo : public ParseInfo {
	//! Name of the PRAGMA statement
	string name;
	//! Parameter list (if any)
	vector<Value> parameters;
	//! Named parameter list (if any)
	named_parameter_map_t named_parameters;

public:
	unique_ptr<PragmaInfo> Copy() const {
		auto result = make_unique<PragmaInfo>();
		result->name = name;
		result->parameters = parameters;
		result->named_parameters = named_parameters;
		return result;
	}
};

} // namespace duckdb



namespace duckdb {
class ClientContext;

//! Return a substitute query to execute instead of this pragma statement
typedef string (*pragma_query_t)(ClientContext &context, const FunctionParameters &parameters);
//! Execute the main pragma function
typedef void (*pragma_function_t)(ClientContext &context, const FunctionParameters &parameters);

//! Pragma functions are invoked by calling PRAGMA x
//! Pragma functions come in three types:
//! * Call: function call, e.g. PRAGMA table_info('tbl')
//!   -> call statements can take multiple parameters
//! * Statement: statement without parameters, e.g. PRAGMA show_tables
//!   -> this is similar to a call pragma but without parameters
//! Pragma functions can either return a new query to execute (pragma_query_t)
//! or they can
class PragmaFunction : public SimpleNamedParameterFunction {
public:
	// Call
	DUCKDB_API static PragmaFunction PragmaCall(const string &name, pragma_query_t query, vector<LogicalType> arguments,
	                                            LogicalType varargs = LogicalType::INVALID);
	DUCKDB_API static PragmaFunction PragmaCall(const string &name, pragma_function_t function,
	                                            vector<LogicalType> arguments,
	                                            LogicalType varargs = LogicalType::INVALID);
	// Statement
	DUCKDB_API static PragmaFunction PragmaStatement(const string &name, pragma_query_t query);
	DUCKDB_API static PragmaFunction PragmaStatement(const string &name, pragma_function_t function);

	DUCKDB_API string ToString() override;

public:
	PragmaType type;

	pragma_query_t query;
	pragma_function_t function;
	named_parameter_type_map_t named_parameters;

private:
	PragmaFunction(string name, PragmaType pragma_type, pragma_query_t query, pragma_function_t function,
	               vector<LogicalType> arguments, LogicalType varargs);
};

} // namespace duckdb


namespace duckdb {

template <class T>
class FunctionSet {
public:
	explicit FunctionSet(string name) : name(name) {
	}

	//! The name of the function set
	string name;
	//! The set of functions.
	vector<T> functions;

public:
	void AddFunction(T function) {
		functions.push_back(move(function));
	}
	idx_t Size() {
		return functions.size();
	}
	T GetFunctionByOffset(idx_t offset) {
		return functions[offset];
	}
	T &GetFunctionReferenceByOffset(idx_t offset) {
		return functions[offset];
	}
	bool MergeFunctionSet(FunctionSet<T> new_functions) {
		D_ASSERT(!new_functions.functions.empty());
		bool need_rewrite_entry = false;
		for (auto &new_func : new_functions.functions) {
			bool can_add = true;
			for (auto &func : functions) {
				if (new_func.Equal(func)) {
					can_add = false;
					break;
				}
			}
			if (can_add) {
				functions.push_back(new_func);
				need_rewrite_entry = true;
			}
		}
		return need_rewrite_entry;
	}
};

class ScalarFunctionSet : public FunctionSet<ScalarFunction> {
public:
	DUCKDB_API explicit ScalarFunctionSet(string name);

	DUCKDB_API ScalarFunction GetFunctionByArguments(const vector<LogicalType> &arguments);
};

class AggregateFunctionSet : public FunctionSet<AggregateFunction> {
public:
	DUCKDB_API explicit AggregateFunctionSet(string name);

	DUCKDB_API AggregateFunction GetFunctionByArguments(const vector<LogicalType> &arguments);
};

class TableFunctionSet : public FunctionSet<TableFunction> {
public:
	DUCKDB_API explicit TableFunctionSet(string name);

	TableFunction GetFunctionByArguments(const vector<LogicalType> &arguments);
};

class PragmaFunctionSet : public FunctionSet<PragmaFunction> {
public:
	explicit PragmaFunctionSet(string name) : FunctionSet(move(name)) {
	}
};

} // namespace duckdb


namespace duckdb {

class Catalog;
class Constraint;

struct CreateTableFunctionInfo;

//! A table function in the catalog
class TableFunctionCatalogEntry : public StandardEntry {
public:
	TableFunctionCatalogEntry(Catalog *catalog, SchemaCatalogEntry *schema, CreateTableFunctionInfo *info);

	//! The table function
	TableFunctionSet functions;
};
} // namespace duckdb




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/expression/columnref_expression.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

//! Represents a reference to a column from either the FROM clause or from an
//! alias
class ColumnRefExpression : public ParsedExpression {
public:
	//! Specify both the column and table name
	ColumnRefExpression(string column_name, string table_name);
	//! Only specify the column name, the table name will be derived later
	explicit ColumnRefExpression(string column_name);
	//! Specify a set of names
	explicit ColumnRefExpression(vector<string> column_names);

	//! The stack of names in order of which they appear (column_names[0].column_names[1].column_names[2]....)
	vector<string> column_names;

public:
	bool IsQualified() const;
	const string &GetColumnName() const;
	const string &GetTableName() const;
	bool IsScalar() const override {
		return false;
	}

	string GetName() const override;
	string ToString() const override;

	static bool Equals(const ColumnRefExpression *a, const ColumnRefExpression *b);
	hash_t Hash() const override;

	unique_ptr<ParsedExpression> Copy() const override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<ParsedExpression> Deserialize(ExpressionType type, FieldReader &source);
};
} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/qualified_name_set.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/hash.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

struct string_t;

// efficient hash function that maximizes the avalanche effect and minimizes
// bias
// see: https://nullprogram.com/blog/2018/07/31/

inline hash_t murmurhash64(uint64_t x) {
	x ^= x >> 32;
	x *= 0xd6e8feb86659fd93U;
	x ^= x >> 32;
	x *= 0xd6e8feb86659fd93U;
	x ^= x >> 32;
	return x;
}

inline hash_t murmurhash32(uint32_t x) {
	return murmurhash64(x);
}

template <class T>
hash_t Hash(T value) {
	return murmurhash32(value);
}

//! Combine two hashes by XORing them
inline hash_t CombineHash(hash_t left, hash_t right) {
	return left ^ right;
}

template <>
DUCKDB_API hash_t Hash(uint64_t val);
template <>
DUCKDB_API hash_t Hash(int64_t val);
template <>
DUCKDB_API hash_t Hash(hugeint_t val);
template <>
DUCKDB_API hash_t Hash(float val);
template <>
DUCKDB_API hash_t Hash(double val);
template <>
DUCKDB_API hash_t Hash(const char *val);
template <>
DUCKDB_API hash_t Hash(char *val);
template <>
DUCKDB_API hash_t Hash(string_t val);
template <>
DUCKDB_API hash_t Hash(interval_t val);
DUCKDB_API hash_t Hash(const char *val, size_t size);
DUCKDB_API hash_t Hash(uint8_t *val, size_t size);

} // namespace duckdb



namespace duckdb {

struct QualifiedColumnHashFunction {
	uint64_t operator()(const QualifiedColumnName &a) const {
		std::hash<std::string> str_hasher;
		return str_hasher(a.schema) ^ str_hasher(a.table) ^ str_hasher(a.column);
	}
};

struct QualifiedColumnEquality {
	bool operator()(const QualifiedColumnName &a, const QualifiedColumnName &b) const {
		return a.schema == b.schema && a.table == b.table && a.column == b.column;
	}
};

using qualified_column_set_t = unordered_set<QualifiedColumnName, QualifiedColumnHashFunction, QualifiedColumnEquality>;

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression_binder.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/expression/bound_expression.hpp
//
//
//===----------------------------------------------------------------------===//








namespace duckdb {

//! BoundExpression is an intermediate dummy class used by the binder. It is a ParsedExpression but holds an Expression.
//! It represents a successfully bound expression. It is used in the Binder to prevent re-binding of already bound parts
//! when dealing with subqueries.
class BoundExpression : public ParsedExpression {
public:
	BoundExpression(unique_ptr<Expression> expr);

	unique_ptr<Expression> expr;

public:
	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;
	hash_t Hash() const override;

	unique_ptr<ParsedExpression> Copy() const override;

	void Serialize(FieldWriter &writer) const override;
};

} // namespace duckdb






namespace duckdb {

class Binder;
class ClientContext;
class QueryNode;

class ScalarFunctionCatalogEntry;
class AggregateFunctionCatalogEntry;
class ScalarMacroCatalogEntry;
class CatalogEntry;
class SimpleFunction;

struct DummyBinding;

struct BoundColumnReferenceInfo {
	string name;
	idx_t query_location;
};

struct BindResult {
	BindResult() {
	}
	explicit BindResult(string error) : error(error) {
	}
	explicit BindResult(unique_ptr<Expression> expr) : expression(move(expr)) {
	}

	bool HasError() {
		return !error.empty();
	}

	unique_ptr<Expression> expression;
	string error;
};

class ExpressionBinder {
public:
	ExpressionBinder(Binder &binder, ClientContext &context, bool replace_binder = false);
	virtual ~ExpressionBinder();

	//! The target type that should result from the binder. If the result is not of this type, a cast to this type will
	//! be added. Defaults to INVALID.
	LogicalType target_type;

	DummyBinding *macro_binding;
	vector<DummyBinding> *lambda_bindings = nullptr;

public:
	unique_ptr<Expression> Bind(unique_ptr<ParsedExpression> &expr, LogicalType *result_type = nullptr,
	                            bool root_expression = true);

	//! Returns whether or not any columns have been bound by the expression binder
	bool HasBoundColumns() {
		return !bound_columns.empty();
	}
	const vector<BoundColumnReferenceInfo> &GetBoundColumns() {
		return bound_columns;
	}

	string Bind(unique_ptr<ParsedExpression> *expr, idx_t depth, bool root_expression = false);

	unique_ptr<ParsedExpression> CreateStructExtract(unique_ptr<ParsedExpression> base, string field_name);
	unique_ptr<ParsedExpression> CreateStructPack(ColumnRefExpression &colref);
	BindResult BindQualifiedColumnName(ColumnRefExpression &colref, const string &table_name);

	unique_ptr<ParsedExpression> QualifyColumnName(const string &column_name, string &error_message);
	unique_ptr<ParsedExpression> QualifyColumnName(ColumnRefExpression &colref, string &error_message);

	// Bind table names to ColumnRefExpressions
	void QualifyColumnNames(unique_ptr<ParsedExpression> &expr);
	static void QualifyColumnNames(Binder &binder, unique_ptr<ParsedExpression> &expr);

	static unique_ptr<Expression> PushCollation(ClientContext &context, unique_ptr<Expression> source,
	                                            const string &collation, bool equality_only = false);
	static void TestCollation(ClientContext &context, const string &collation);

	bool BindCorrelatedColumns(unique_ptr<ParsedExpression> &expr);

	void BindChild(unique_ptr<ParsedExpression> &expr, idx_t depth, string &error);
	static void ExtractCorrelatedExpressions(Binder &binder, Expression &expr);

	static bool ContainsNullType(const LogicalType &type);
	static LogicalType ExchangeNullType(const LogicalType &type);
	static bool ContainsType(const LogicalType &type, LogicalTypeId target);
	static LogicalType ExchangeType(const LogicalType &type, LogicalTypeId target, LogicalType new_type);

	//! Bind the given expresion. Unlike Bind(), this does *not* mute the given ParsedExpression.
	//! Exposed to be used from sub-binders that aren't subclasses of ExpressionBinder.
	virtual BindResult BindExpression(unique_ptr<ParsedExpression> *expr_ptr, idx_t depth,
	                                  bool root_expression = false);

	void ReplaceMacroParametersRecursive(unique_ptr<ParsedExpression> &expr);

protected:
	BindResult BindExpression(BetweenExpression &expr, idx_t depth);
	BindResult BindExpression(CaseExpression &expr, idx_t depth);
	BindResult BindExpression(CollateExpression &expr, idx_t depth);
	BindResult BindExpression(CastExpression &expr, idx_t depth);
	BindResult BindExpression(ColumnRefExpression &expr, idx_t depth);
	BindResult BindExpression(ComparisonExpression &expr, idx_t depth);
	BindResult BindExpression(ConjunctionExpression &expr, idx_t depth);
	BindResult BindExpression(ConstantExpression &expr, idx_t depth);
	BindResult BindExpression(FunctionExpression &expr, idx_t depth, unique_ptr<ParsedExpression> *expr_ptr);
	BindResult BindExpression(LambdaExpression &expr, idx_t depth, const bool is_lambda,
	                          const LogicalType &list_child_type);
	BindResult BindExpression(OperatorExpression &expr, idx_t depth);
	BindResult BindExpression(ParameterExpression &expr, idx_t depth);
	BindResult BindExpression(PositionalReferenceExpression &ref, idx_t depth);
	BindResult BindExpression(SubqueryExpression &expr, idx_t depth);

	void TransformCapturedLambdaColumn(unique_ptr<Expression> &original, unique_ptr<Expression> &replacement,
	                                   vector<unique_ptr<Expression>> &captures, LogicalType &list_child_type,
	                                   string &alias);
	void CaptureLambdaColumns(vector<unique_ptr<Expression>> &captures, LogicalType &list_child_type,
	                          unique_ptr<Expression> &expr, string &alias);

protected:
	virtual BindResult BindGroupingFunction(OperatorExpression &op, idx_t depth);
	virtual BindResult BindFunction(FunctionExpression &expr, ScalarFunctionCatalogEntry *function, idx_t depth);
	virtual BindResult BindLambdaFunction(FunctionExpression &expr, ScalarFunctionCatalogEntry *function, idx_t depth);
	virtual BindResult BindAggregate(FunctionExpression &expr, AggregateFunctionCatalogEntry *function, idx_t depth);
	virtual BindResult BindUnnest(FunctionExpression &expr, idx_t depth);
	virtual BindResult BindMacro(FunctionExpression &expr, ScalarMacroCatalogEntry *macro, idx_t depth,
	                             unique_ptr<ParsedExpression> *expr_ptr);

	virtual string UnsupportedAggregateMessage();
	virtual string UnsupportedUnnestMessage();

	Binder &binder;
	ClientContext &context;
	ExpressionBinder *stored_binder;
	vector<BoundColumnReferenceInfo> bound_columns;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/table_binding.hpp
//
//
//===----------------------------------------------------------------------===//










namespace duckdb {
class BindContext;
class BoundQueryNode;
class ColumnRefExpression;
class SubqueryRef;
class LogicalGet;
class TableCatalogEntry;
class TableFunctionCatalogEntry;
class BoundTableFunction;
class StandardEntry;

enum class BindingType { BASE, TABLE, DUMMY, CATALOG_ENTRY };

//! A Binding represents a binding to a table, table-producing function or subquery with a specified table index.
struct Binding {
	Binding(BindingType binding_type, const string &alias, vector<LogicalType> types, vector<string> names,
	        idx_t index);
	virtual ~Binding() = default;

	//! The type of Binding
	BindingType binding_type;
	//! The alias of the binding
	string alias;
	//! The table index of the binding
	idx_t index;
	vector<LogicalType> types;
	//! Column names of the subquery
	vector<string> names;
	//! Name -> index for the names
	case_insensitive_map_t<column_t> name_map;

public:
	bool TryGetBindingIndex(const string &column_name, column_t &column_index);
	column_t GetBindingIndex(const string &column_name);
	bool HasMatchingBinding(const string &column_name);
	virtual string ColumnNotFoundError(const string &column_name) const;
	virtual BindResult Bind(ColumnRefExpression &colref, idx_t depth);
	virtual StandardEntry *GetStandardEntry();
};

struct EntryBinding : public Binding {
public:
	EntryBinding(const string &alias, vector<LogicalType> types, vector<string> names, idx_t index,
	             StandardEntry &entry);
	StandardEntry &entry;

public:
	StandardEntry *GetStandardEntry() override;
};

//! TableBinding is exactly like the Binding, except it keeps track of which columns were bound in the linked LogicalGet
//! node for projection pushdown purposes.
struct TableBinding : public Binding {
	TableBinding(const string &alias, vector<LogicalType> types, vector<string> names, LogicalGet &get, idx_t index,
	             bool add_row_id = false);

	//! the underlying LogicalGet
	LogicalGet &get;

public:
	unique_ptr<ParsedExpression> ExpandGeneratedColumn(const string &column_name);
	BindResult Bind(ColumnRefExpression &colref, idx_t depth) override;
	StandardEntry *GetStandardEntry() override;
	string ColumnNotFoundError(const string &column_name) const override;
};

//! DummyBinding is like the Binding, except the alias and index are set by default. Used for binding lambdas and macro
//! parameters.
struct DummyBinding : public Binding {
	// NOTE: changing this string conflicts with the storage version
	static constexpr const char *DUMMY_NAME = "0_macro_parameters";

public:
	DummyBinding(vector<LogicalType> types_p, vector<string> names_p, string dummy_name_p);

	//! Arguments
	vector<unique_ptr<ParsedExpression>> *arguments;
	//! The name of the dummy binding
	string dummy_name;

public:
	BindResult Bind(ColumnRefExpression &colref, idx_t depth) override;

	//! Given the parameter colref, returns a copy of the argument that was supplied for this parameter
	unique_ptr<ParsedExpression> ParamToArg(ColumnRefExpression &colref);
};

} // namespace duckdb


namespace duckdb {
class Binder;
class LogicalGet;
class BoundQueryNode;

class StarExpression;

struct UsingColumnSet {
	string primary_binding;
	unordered_set<string> bindings;
};

//! The BindContext object keeps track of all the tables and columns that are
//! encountered during the binding process.
class BindContext {
public:
	//! Keep track of recursive CTE references
	case_insensitive_map_t<std::shared_ptr<idx_t>> cte_references;

public:
	//! Given a column name, find the matching table it belongs to. Throws an
	//! exception if no table has a column of the given name.
	string GetMatchingBinding(const string &column_name);
	//! Like GetMatchingBinding, but instead of throwing an error if multiple tables have the same binding it will
	//! return a list of all the matching ones
	unordered_set<string> GetMatchingBindings(const string &column_name);
	//! Like GetMatchingBindings, but returns the top 3 most similar bindings (in levenshtein distance) instead of the
	//! matching ones
	vector<string> GetSimilarBindings(const string &column_name);

	Binding *GetCTEBinding(const string &ctename);
	//! Binds a column expression to the base table. Returns the bound expression
	//! or throws an exception if the column could not be bound.
	BindResult BindColumn(ColumnRefExpression &colref, idx_t depth);
	string BindColumn(PositionalReferenceExpression &ref, string &table_name, string &column_name);
	BindResult BindColumn(PositionalReferenceExpression &ref, idx_t depth);

	unique_ptr<ParsedExpression> ExpandGeneratedColumn(const string &table_name, const string &column_name);

	unique_ptr<ParsedExpression> CreateColumnReference(const string &table_name, const string &column_name);
	unique_ptr<ParsedExpression> CreateColumnReference(const string &schema_name, const string &table_name,
	                                                   const string &column_name);

	//! Generate column expressions for all columns that are present in the
	//! referenced tables. This is used to resolve the * expression in a
	//! selection list.
	void GenerateAllColumnExpressions(StarExpression &expr, vector<unique_ptr<ParsedExpression>> &new_select_list);
	//! Check if the given (binding, column_name) is in the exclusion/replacement lists.
	//! Returns true if it is in one of these lists, and should therefore be skipped.
	bool CheckExclusionList(StarExpression &expr, Binding *binding, const string &column_name,
	                        vector<unique_ptr<ParsedExpression>> &new_select_list,
	                        case_insensitive_set_t &excluded_columns);

	const vector<std::pair<string, Binding *>> &GetBindingsList() {
		return bindings_list;
	}

	//! Adds a base table with the given alias to the BindContext.
	void AddBaseTable(idx_t index, const string &alias, const vector<string> &names, const vector<LogicalType> &types,
	                  LogicalGet &get);
	//! Adds a call to a table function with the given alias to the BindContext.
	void AddTableFunction(idx_t index, const string &alias, const vector<string> &names,
	                      const vector<LogicalType> &types, LogicalGet &get);
	//! Adds a table view with a given alias to the BindContext.
	void AddView(idx_t index, const string &alias, SubqueryRef &ref, BoundQueryNode &subquery, ViewCatalogEntry *view);
	//! Adds a subquery with a given alias to the BindContext.
	void AddSubquery(idx_t index, const string &alias, SubqueryRef &ref, BoundQueryNode &subquery);
	//! Adds a subquery with a given alias to the BindContext.
	void AddSubquery(idx_t index, const string &alias, TableFunctionRef &ref, BoundQueryNode &subquery);
	//! Adds a binding to a catalog entry with a given alias to the BindContext.
	void AddEntryBinding(idx_t index, const string &alias, const vector<string> &names,
	                     const vector<LogicalType> &types, StandardEntry *entry);
	//! Adds a base table with the given alias to the BindContext.
	void AddGenericBinding(idx_t index, const string &alias, const vector<string> &names,
	                       const vector<LogicalType> &types);

	//! Adds a base table with the given alias to the CTE BindContext.
	//! We need this to correctly bind recursive CTEs with multiple references.
	void AddCTEBinding(idx_t index, const string &alias, const vector<string> &names, const vector<LogicalType> &types);

	//! Add an implicit join condition (e.g. USING (x))
	void AddUsingBinding(const string &column_name, UsingColumnSet *set);

	void AddUsingBindingSet(unique_ptr<UsingColumnSet> set);

	//! Returns any using column set for the given column name, or nullptr if there is none. On conflict (multiple using
	//! column sets with the same name) throw an exception.
	UsingColumnSet *GetUsingBinding(const string &column_name);
	//! Returns any using column set for the given column name, or nullptr if there is none
	UsingColumnSet *GetUsingBinding(const string &column_name, const string &binding_name);
	//! Erase a using binding from the set of using bindings
	void RemoveUsingBinding(const string &column_name, UsingColumnSet *set);
	//! Finds the using bindings for a given column. Returns true if any exists, false otherwise.
	bool FindUsingBinding(const string &column_name, unordered_set<UsingColumnSet *> **using_columns);
	//! Transfer a using binding from one bind context to this bind context
	void TransferUsingBinding(BindContext &current_context, UsingColumnSet *current_set, UsingColumnSet *new_set,
	                          const string &binding, const string &using_column);

	//! Fetch the actual column name from the given binding, or throws if none exists
	//! This can be different from "column_name" because of case insensitivity
	//! (e.g. "column_name" might return "COLUMN_NAME")
	string GetActualColumnName(const string &binding, const string &column_name);

	case_insensitive_map_t<std::shared_ptr<Binding>> GetCTEBindings() {
		return cte_bindings;
	}
	void SetCTEBindings(case_insensitive_map_t<std::shared_ptr<Binding>> bindings) {
		cte_bindings = bindings;
	}

	//! Alias a set of column names for the specified table, using the original names if there are not enough aliases
	//! specified.
	static vector<string> AliasColumnNames(const string &table_name, const vector<string> &names,
	                                       const vector<string> &column_aliases);

	//! Add all the bindings from a BindContext to this BindContext. The other BindContext is destroyed in the process.
	void AddContext(BindContext other);

	//! Gets a binding of the specified name. Returns a nullptr and sets the out_error if the binding could not be
	//! found.
	Binding *GetBinding(const string &name, string &out_error);

private:
	void AddBinding(const string &alias, unique_ptr<Binding> binding);

private:
	//! The set of bindings
	case_insensitive_map_t<unique_ptr<Binding>> bindings;
	//! The list of bindings in insertion order
	vector<std::pair<string, Binding *>> bindings_list;
	//! The set of columns used in USING join conditions
	case_insensitive_map_t<unordered_set<UsingColumnSet *>> using_columns;
	//! Using column sets
	vector<unique_ptr<UsingColumnSet>> using_column_sets;

	//! The set of CTE bindings
	case_insensitive_map_t<std::shared_ptr<Binding>> cte_bindings;
};
} // namespace duckdb






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/query_node.hpp
//
//
//===----------------------------------------------------------------------===//







//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/common_table_expression_info.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/select_statement.hpp
//
//
//===----------------------------------------------------------------------===//






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/sql_statement.hpp
//
//
//===----------------------------------------------------------------------===//






//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/printer.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//! Printer is a static class that allows printing to logs or stdout/stderr
class Printer {
public:
	//! Print the object to stderr
	DUCKDB_API static void Print(const string &str);
	//! Prints Progress
	DUCKDB_API static void PrintProgress(int percentage, const char *pbstr, int pbwidth);
	//! Prints an empty line when progress bar is done
	DUCKDB_API static void FinishProgressBarPrint(const char *pbstr, int pbwidth);
	//! Whether or not we are printing to a terminal
	DUCKDB_API static bool IsTerminal();
};
} // namespace duckdb


namespace duckdb {

//! SQLStatement is the base class of any type of SQL statement.
class SQLStatement {
public:
	explicit SQLStatement(StatementType type) : type(type) {};
	virtual ~SQLStatement() {
	}

	//! The statement type
	StatementType type;
	//! The statement location within the query string
	idx_t stmt_location = 0;
	//! The statement length within the query string
	idx_t stmt_length = 0;
	//! The number of prepared statement parameters (if any)
	idx_t n_param = 0;
	//! The query text that corresponds to this SQL statement
	string query;

protected:
	SQLStatement(const SQLStatement &other) = default;

public:
	virtual string ToString() const {
		throw InternalException("ToString not supported for this type of SQLStatement: '%s'",
		                        StatementTypeToString(type));
	}
	//! Create a copy of this SelectStatement
	virtual unique_ptr<SQLStatement> Copy() const = 0;
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/tableref.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/tableref_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//===--------------------------------------------------------------------===//
// Table Reference Types
//===--------------------------------------------------------------------===//
enum class TableReferenceType : uint8_t {
	INVALID = 0,         // invalid table reference type
	BASE_TABLE = 1,      // base table reference
	SUBQUERY = 2,        // output of a subquery
	JOIN = 3,            // output of join
	CROSS_PRODUCT = 4,   // out of cartesian product
	TABLE_FUNCTION = 5,  // table producing function
	EXPRESSION_LIST = 6, // expression list
	CTE = 7,             // Recursive CTE
	EMPTY = 8            // placeholder for empty FROM
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/sample_options.hpp
//
//
//===----------------------------------------------------------------------===//








namespace duckdb {

enum class SampleMethod : uint8_t { SYSTEM_SAMPLE = 0, BERNOULLI_SAMPLE = 1, RESERVOIR_SAMPLE = 2 };

string SampleMethodToString(SampleMethod method);

struct SampleOptions {
	Value sample_size;
	bool is_percentage;
	SampleMethod method;
	int64_t seed = -1;

	unique_ptr<SampleOptions> Copy();
	void Serialize(Serializer &serializer);
	static unique_ptr<SampleOptions> Deserialize(Deserializer &source);
	static bool Equals(SampleOptions *a, SampleOptions *b);
};

} // namespace duckdb


namespace duckdb {
class Deserializer;
class Serializer;

//! Represents a generic expression that returns a table.
class TableRef {
public:
	explicit TableRef(TableReferenceType type) : type(type) {
	}
	virtual ~TableRef() {
	}

	TableReferenceType type;
	string alias;
	//! Sample options (if any)
	unique_ptr<SampleOptions> sample;
	//! The location in the query (if any)
	idx_t query_location = DConstants::INVALID_INDEX;

public:
	//! Convert the object to a string
	virtual string ToString() const = 0;
	string BaseToString(string result) const;
	string BaseToString(string result, const vector<string> &column_name_alias) const;
	void Print();

	virtual bool Equals(const TableRef *other) const;

	virtual unique_ptr<TableRef> Copy() = 0;

	//! Serializes a TableRef to a stand-alone binary blob
	DUCKDB_API void Serialize(Serializer &serializer) const;
	//! Serializes a TableRef to a stand-alone binary blob
	DUCKDB_API virtual void Serialize(FieldWriter &writer) const = 0;
	//! Deserializes a blob back into a TableRef
	DUCKDB_API static unique_ptr<TableRef> Deserialize(Deserializer &source);

	//! Copy the properties of this table ref to the target
	void CopyProperties(TableRef &target) const;
};
} // namespace duckdb


namespace duckdb {

class QueryNode;

//! SelectStatement is a typical SELECT clause
class SelectStatement : public SQLStatement {
public:
	SelectStatement() : SQLStatement(StatementType::SELECT_STATEMENT) {
	}

	//! The main query node
	unique_ptr<QueryNode> node;

protected:
	SelectStatement(const SelectStatement &other);

public:
	//! Convert the SELECT statement to a string
	string ToString() const override;
	//! Create a copy of this SelectStatement
	unique_ptr<SQLStatement> Copy() const override;
	//! Serializes a SelectStatement to a stand-alone binary blob
	void Serialize(Serializer &serializer) const;
	//! Deserializes a blob back into a SelectStatement, returns nullptr if
	//! deserialization is not possible
	static unique_ptr<SelectStatement> Deserialize(Deserializer &source);
	//! Whether or not the statements are equivalent
	bool Equals(const SQLStatement *other) const;
};
} // namespace duckdb


namespace duckdb {

class SelectStatement;

struct CommonTableExpressionInfo {
	vector<string> aliases;
	unique_ptr<SelectStatement> query;
};

} // namespace duckdb


namespace duckdb {

enum QueryNodeType : uint8_t {
	SELECT_NODE = 1,
	SET_OPERATION_NODE = 2,
	BOUND_SUBQUERY_NODE = 3,
	RECURSIVE_CTE_NODE = 4
};

struct CommonTableExpressionInfo;

class CommonTableExpressionMap {
public:
	CommonTableExpressionMap();

	unordered_map<string, unique_ptr<CommonTableExpressionInfo>> map;

public:
	string ToString() const;
	CommonTableExpressionMap Copy() const;
};

class QueryNode {
public:
	explicit QueryNode(QueryNodeType type) : type(type) {
	}
	virtual ~QueryNode() {
	}

	//! The type of the query node, either SetOperation or Select
	QueryNodeType type;
	//! The set of result modifiers associated with this query node
	vector<unique_ptr<ResultModifier>> modifiers;
	//! CTEs (used by SelectNode and SetOperationNode)
	CommonTableExpressionMap cte_map;

	virtual const vector<unique_ptr<ParsedExpression>> &GetSelectList() const = 0;

public:
	//! Convert the query node to a string
	virtual string ToString() const = 0;

	virtual bool Equals(const QueryNode *other) const;

	//! Create a copy of this QueryNode
	virtual unique_ptr<QueryNode> Copy() const = 0;
	//! Serializes a QueryNode to a stand-alone binary blob
	DUCKDB_API void Serialize(Serializer &serializer) const;
	//! Serializes a QueryNode to a stand-alone binary blob
	DUCKDB_API virtual void Serialize(FieldWriter &writer) const = 0;
	//! Deserializes a blob back into a QueryNode
	DUCKDB_API static unique_ptr<QueryNode> Deserialize(Deserializer &source);

	string ResultModifiersToString() const;

protected:
	//! Copy base QueryNode properties from another expression to this one,
	//! used in Copy method
	void CopyProperties(QueryNode &other) const;
};

} // namespace duckdb




namespace duckdb {
class BoundResultModifier;
class BoundSelectNode;
class ClientContext;
class ExpressionBinder;
class LimitModifier;
class OrderBinder;
class TableCatalogEntry;
class ViewCatalogEntry;
class TableMacroCatalogEntry;

struct CreateInfo;
struct BoundCreateTableInfo;
struct BoundCreateFunctionInfo;
struct CommonTableExpressionInfo;
struct BoundParameterMap;

enum class BindingMode : uint8_t { STANDARD_BINDING, EXTRACT_NAMES };

struct CorrelatedColumnInfo {
	ColumnBinding binding;
	LogicalType type;
	string name;
	idx_t depth;

	CorrelatedColumnInfo(ColumnBinding binding, LogicalType type_p, string name_p, idx_t depth)
	    : binding(binding), type(move(type_p)), name(move(name_p)), depth(depth) {
	}
	explicit CorrelatedColumnInfo(BoundColumnRefExpression &expr)
	    : CorrelatedColumnInfo(expr.binding, expr.return_type, expr.GetName(), expr.depth) {
	}

	bool operator==(const CorrelatedColumnInfo &rhs) const {
		return binding == rhs.binding;
	}
};

//! Bind the parsed query tree to the actual columns present in the catalog.
/*!
  The binder is responsible for binding tables and columns to actual physical
  tables and columns in the catalog. In the process, it also resolves types of
  all expressions.
*/
class Binder : public std::enable_shared_from_this<Binder> {
	friend class ExpressionBinder;
	friend class SelectBinder;
	friend class RecursiveSubqueryPlanner;

public:
	static shared_ptr<Binder> CreateBinder(ClientContext &context, Binder *parent = nullptr, bool inherit_ctes = true);

	//! The client context
	ClientContext &context;
	//! A mapping of names to common table expressions
	case_insensitive_map_t<CommonTableExpressionInfo *> CTE_bindings;
	//! The CTEs that have already been bound
	unordered_set<CommonTableExpressionInfo *> bound_ctes;
	//! The bind context
	BindContext bind_context;
	//! The set of correlated columns bound by this binder (FIXME: this should probably be an unordered_set and not a
	//! vector)
	vector<CorrelatedColumnInfo> correlated_columns;
	//! The set of parameter expressions bound by this binder
	BoundParameterMap *parameters;
	//! Statement properties
	StatementProperties properties;
	//! The alias for the currently processing subquery, if it exists
	string alias;
	//! Macro parameter bindings (if any)
	DummyBinding *macro_binding = nullptr;
	//! The intermediate lambda bindings to bind nested lambdas (if any)
	vector<DummyBinding> *lambda_bindings = nullptr;

public:
	BoundStatement Bind(SQLStatement &statement);
	BoundStatement Bind(QueryNode &node);

	unique_ptr<BoundCreateTableInfo> BindCreateTableInfo(unique_ptr<CreateInfo> info);
	void BindCreateViewInfo(CreateViewInfo &base);
	SchemaCatalogEntry *BindSchema(CreateInfo &info);
	SchemaCatalogEntry *BindCreateFunctionInfo(CreateInfo &info);

	//! Check usage, and cast named parameters to their types
	static void BindNamedParameters(named_parameter_type_map_t &types, named_parameter_map_t &values,
	                                QueryErrorContext &error_context, string &func_name);

	unique_ptr<BoundTableRef> Bind(TableRef &ref);
	unique_ptr<LogicalOperator> CreatePlan(BoundTableRef &ref);

	//! Generates an unused index for a table
	idx_t GenerateTableIndex();

	//! Add a common table expression to the binder
	void AddCTE(const string &name, CommonTableExpressionInfo *cte);
	//! Find a common table expression by name; returns nullptr if none exists
	CommonTableExpressionInfo *FindCTE(const string &name, bool skip = false);

	bool CTEIsAlreadyBound(CommonTableExpressionInfo *cte);

	//! Add the view to the set of currently bound views - used for detecting recursive view definitions
	void AddBoundView(ViewCatalogEntry *view);

	void PushExpressionBinder(ExpressionBinder *binder);
	void PopExpressionBinder();
	void SetActiveBinder(ExpressionBinder *binder);
	ExpressionBinder *GetActiveBinder();
	bool HasActiveBinder();

	vector<ExpressionBinder *> &GetActiveBinders();

	void MergeCorrelatedColumns(vector<CorrelatedColumnInfo> &other);
	//! Add a correlated column to this binder (if it does not exist)
	void AddCorrelatedColumn(const CorrelatedColumnInfo &info);

	string FormatError(ParsedExpression &expr_context, const string &message);
	string FormatError(TableRef &ref_context, const string &message);

	string FormatErrorRecursive(idx_t query_location, const string &message, vector<ExceptionFormatValue> &values);
	template <class T, typename... Args>
	string FormatErrorRecursive(idx_t query_location, const string &msg, vector<ExceptionFormatValue> &values, T param,
	                            Args... params) {
		values.push_back(ExceptionFormatValue::CreateFormatValue<T>(param));
		return FormatErrorRecursive(query_location, msg, values, params...);
	}

	template <typename... Args>
	string FormatError(idx_t query_location, const string &msg, Args... params) {
		vector<ExceptionFormatValue> values;
		return FormatErrorRecursive(query_location, msg, values, params...);
	}

	static void BindLogicalType(ClientContext &context, LogicalType &type, const string &schema = "");

	bool HasMatchingBinding(const string &table_name, const string &column_name, string &error_message);
	bool HasMatchingBinding(const string &schema_name, const string &table_name, const string &column_name,
	                        string &error_message);

	void SetBindingMode(BindingMode mode);
	BindingMode GetBindingMode();
	void AddTableName(string table_name);
	const unordered_set<string> &GetTableNames();

	void SetCanContainNulls(bool can_contain_nulls);

private:
	//! The parent binder (if any)
	shared_ptr<Binder> parent;
	//! The vector of active binders
	vector<ExpressionBinder *> active_binders;
	//! The count of bound_tables
	idx_t bound_tables;
	//! Whether or not the binder has any unplanned subqueries that still need to be planned
	bool has_unplanned_subqueries = false;
	//! Whether or not subqueries should be planned already
	bool plan_subquery = true;
	//! Whether CTEs should reference the parent binder (if it exists)
	bool inherit_ctes = true;
	//! Whether or not the binder can contain NULLs as the root of expressions
	bool can_contain_nulls = false;
	//! The root statement of the query that is currently being parsed
	SQLStatement *root_statement = nullptr;
	//! Binding mode
	BindingMode mode = BindingMode::STANDARD_BINDING;
	//! Table names extracted for BindingMode::EXTRACT_NAMES
	unordered_set<string> table_names;
	//! The set of bound views
	unordered_set<ViewCatalogEntry *> bound_views;

private:
	//! Bind the expressions of generated columns to check for errors
	void BindGeneratedColumns(BoundCreateTableInfo &info);
	//! Bind the default values of the columns of a table
	void BindDefaultValues(vector<ColumnDefinition> &columns, vector<unique_ptr<Expression>> &bound_defaults);
	//! Bind a limit value (LIMIT or OFFSET)
	unique_ptr<Expression> BindDelimiter(ClientContext &context, OrderBinder &order_binder,
	                                     unique_ptr<ParsedExpression> delimiter, const LogicalType &type,
	                                     Value &delimiter_value);

	//! Move correlated expressions from the child binder to this binder
	void MoveCorrelatedExpressions(Binder &other);

	BoundStatement Bind(SelectStatement &stmt);
	BoundStatement Bind(InsertStatement &stmt);
	BoundStatement Bind(CopyStatement &stmt);
	BoundStatement Bind(DeleteStatement &stmt);
	BoundStatement Bind(UpdateStatement &stmt);
	BoundStatement Bind(CreateStatement &stmt);
	BoundStatement Bind(DropStatement &stmt);
	BoundStatement Bind(AlterStatement &stmt);
	BoundStatement Bind(PrepareStatement &stmt);
	BoundStatement Bind(ExecuteStatement &stmt);
	BoundStatement Bind(TransactionStatement &stmt);
	BoundStatement Bind(PragmaStatement &stmt);
	BoundStatement Bind(ExplainStatement &stmt);
	BoundStatement Bind(VacuumStatement &stmt);
	BoundStatement Bind(RelationStatement &stmt);
	BoundStatement Bind(ShowStatement &stmt);
	BoundStatement Bind(CallStatement &stmt);
	BoundStatement Bind(ExportStatement &stmt);
	BoundStatement Bind(ExtensionStatement &stmt);
	BoundStatement Bind(SetStatement &stmt);
	BoundStatement Bind(LoadStatement &stmt);
	BoundStatement Bind(LogicalPlanStatement &stmt);

	BoundStatement BindReturning(vector<unique_ptr<ParsedExpression>> returning_list, TableCatalogEntry *table,
	                             idx_t update_table_index, unique_ptr<LogicalOperator> child_operator,
	                             BoundStatement result);

	unique_ptr<QueryNode> BindTableMacro(FunctionExpression &function, TableMacroCatalogEntry *macro_func, idx_t depth);

	unique_ptr<BoundQueryNode> BindNode(SelectNode &node);
	unique_ptr<BoundQueryNode> BindNode(SetOperationNode &node);
	unique_ptr<BoundQueryNode> BindNode(RecursiveCTENode &node);
	unique_ptr<BoundQueryNode> BindNode(QueryNode &node);

	unique_ptr<LogicalOperator> VisitQueryNode(BoundQueryNode &node, unique_ptr<LogicalOperator> root);
	unique_ptr<LogicalOperator> CreatePlan(BoundRecursiveCTENode &node);
	unique_ptr<LogicalOperator> CreatePlan(BoundSelectNode &statement);
	unique_ptr<LogicalOperator> CreatePlan(BoundSetOperationNode &node);
	unique_ptr<LogicalOperator> CreatePlan(BoundQueryNode &node);

	unique_ptr<BoundTableRef> Bind(BaseTableRef &ref);
	unique_ptr<BoundTableRef> Bind(CrossProductRef &ref);
	unique_ptr<BoundTableRef> Bind(JoinRef &ref);
	unique_ptr<BoundTableRef> Bind(SubqueryRef &ref, CommonTableExpressionInfo *cte = nullptr);
	unique_ptr<BoundTableRef> Bind(TableFunctionRef &ref);
	unique_ptr<BoundTableRef> Bind(EmptyTableRef &ref);
	unique_ptr<BoundTableRef> Bind(ExpressionListRef &ref);

	bool BindTableFunctionParameters(TableFunctionCatalogEntry &table_function,
	                                 vector<unique_ptr<ParsedExpression>> &expressions, vector<LogicalType> &arguments,
	                                 vector<Value> &parameters, named_parameter_map_t &named_parameters,
	                                 unique_ptr<BoundSubqueryRef> &subquery, string &error);
	bool BindTableInTableOutFunction(vector<unique_ptr<ParsedExpression>> &expressions,
	                                 unique_ptr<BoundSubqueryRef> &subquery, string &error);
	unique_ptr<LogicalOperator> BindTableFunction(TableFunction &function, vector<Value> parameters);
	unique_ptr<LogicalOperator>
	BindTableFunctionInternal(TableFunction &table_function, const string &function_name, vector<Value> parameters,
	                          named_parameter_map_t named_parameters, vector<LogicalType> input_table_types,
	                          vector<string> input_table_names, const vector<string> &column_name_alias,
	                          unique_ptr<ExternalDependency> external_dependency);

	unique_ptr<LogicalOperator> CreatePlan(BoundBaseTableRef &ref);
	unique_ptr<LogicalOperator> CreatePlan(BoundCrossProductRef &ref);
	unique_ptr<LogicalOperator> CreatePlan(BoundJoinRef &ref);
	unique_ptr<LogicalOperator> CreatePlan(BoundSubqueryRef &ref);
	unique_ptr<LogicalOperator> CreatePlan(BoundTableFunction &ref);
	unique_ptr<LogicalOperator> CreatePlan(BoundEmptyTableRef &ref);
	unique_ptr<LogicalOperator> CreatePlan(BoundExpressionListRef &ref);
	unique_ptr<LogicalOperator> CreatePlan(BoundCTERef &ref);

	BoundStatement BindCopyTo(CopyStatement &stmt);
	BoundStatement BindCopyFrom(CopyStatement &stmt);

	void BindModifiers(OrderBinder &order_binder, QueryNode &statement, BoundQueryNode &result);
	void BindModifierTypes(BoundQueryNode &result, const vector<LogicalType> &sql_types, idx_t projection_index);

	BoundStatement BindSummarize(ShowStatement &stmt);
	unique_ptr<BoundResultModifier> BindLimit(OrderBinder &order_binder, LimitModifier &limit_mod);
	unique_ptr<BoundResultModifier> BindLimitPercent(OrderBinder &order_binder, LimitPercentModifier &limit_mod);
	unique_ptr<Expression> BindOrderExpression(OrderBinder &order_binder, unique_ptr<ParsedExpression> expr);

	unique_ptr<LogicalOperator> PlanFilter(unique_ptr<Expression> condition, unique_ptr<LogicalOperator> root);

	void PlanSubqueries(unique_ptr<Expression> *expr, unique_ptr<LogicalOperator> *root);
	unique_ptr<Expression> PlanSubquery(BoundSubqueryExpression &expr, unique_ptr<LogicalOperator> &root);

	unique_ptr<LogicalOperator> CastLogicalOperatorToTypes(vector<LogicalType> &source_types,
	                                                       vector<LogicalType> &target_types,
	                                                       unique_ptr<LogicalOperator> op);

	string FindBinding(const string &using_column, const string &join_side);
	bool TryFindBinding(const string &using_column, const string &join_side, string &result);

	void AddUsingBindingSet(unique_ptr<UsingColumnSet> set);
	string RetrieveUsingBinding(Binder &current_binder, UsingColumnSet *current_set, const string &column_name,
	                            const string &join_side, UsingColumnSet *new_set);

	void AddCTEMap(CommonTableExpressionMap &cte_map);

public:
	// This should really be a private constructor, but make_shared does not allow it...
	// If you are thinking about calling this, you should probably call Binder::CreateBinder
	Binder(bool I_know_what_I_am_doing, ClientContext &context, shared_ptr<Binder> parent, bool inherit_ctes);
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/bound_query_node.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {

//! Bound equivalent of QueryNode
class BoundQueryNode {
public:
	explicit BoundQueryNode(QueryNodeType type) : type(type) {
	}
	virtual ~BoundQueryNode() {
	}

	//! The type of the query node, either SetOperation or Select
	QueryNodeType type;
	//! The result modifiers that should be applied to this query node
	vector<unique_ptr<BoundResultModifier>> modifiers;

	//! The names returned by this QueryNode.
	vector<string> names;
	//! The types returned by this QueryNode.
	vector<LogicalType> types;

public:
	virtual idx_t GetRootIndex() = 0;
};

} // namespace duckdb



namespace duckdb {

class BoundSubqueryExpression : public Expression {
public:
	explicit BoundSubqueryExpression(LogicalType return_type);

	bool IsCorrelated() {
		return binder->correlated_columns.size() > 0;
	}

	//! The binder used to bind the subquery node
	shared_ptr<Binder> binder;
	//! The bound subquery node
	unique_ptr<BoundQueryNode> subquery;
	//! The subquery type
	SubqueryType subquery_type;
	//! the child expression to compare with (in case of IN, ANY, ALL operators)
	unique_ptr<Expression> child;
	//! The comparison type of the child expression with the subquery (in case of ANY, ALL operators)
	ExpressionType comparison_type;
	//! The LogicalType of the subquery result. Only used for ANY expressions.
	LogicalType child_type;
	//! The target LogicalType of the subquery result (i.e. to which type it should be casted, if child_type <>
	//! child_target). Only used for ANY expressions.
	LogicalType child_target;

public:
	bool HasSubquery() const override {
		return true;
	}
	bool IsScalar() const override {
		return false;
	}
	bool IsFoldable() const override {
		return false;
	}

	string ToString() const override;

	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;

	bool PropagatesNullValues() const override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_unnest_expression.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

//! Represents a function call that has been bound to a base function
class BoundUnnestExpression : public Expression {
public:
	explicit BoundUnnestExpression(LogicalType return_type);

	unique_ptr<Expression> child;

public:
	bool IsFoldable() const override;
	string ToString() const override;

	hash_t Hash() const override;
	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/planner/expression/bound_window_expression.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/expression/window_expression.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

enum class WindowBoundary : uint8_t {
	INVALID = 0,
	UNBOUNDED_PRECEDING = 1,
	UNBOUNDED_FOLLOWING = 2,
	CURRENT_ROW_RANGE = 3,
	CURRENT_ROW_ROWS = 4,
	EXPR_PRECEDING_ROWS = 5,
	EXPR_FOLLOWING_ROWS = 6,
	EXPR_PRECEDING_RANGE = 7,
	EXPR_FOLLOWING_RANGE = 8
};

//! The WindowExpression represents a window function in the query. They are a special case of aggregates which is why
//! they inherit from them.
class WindowExpression : public ParsedExpression {
public:
	WindowExpression(ExpressionType type, string schema_name, const string &function_name);

	//! Schema of the aggregate function
	string schema;
	//! Name of the aggregate function
	string function_name;
	//! The child expression of the main window function
	vector<unique_ptr<ParsedExpression>> children;
	//! The set of expressions to partition by
	vector<unique_ptr<ParsedExpression>> partitions;
	//! The set of ordering clauses
	vector<OrderByNode> orders;
	//! Expression representing a filter, only used for aggregates
	unique_ptr<ParsedExpression> filter_expr;
	//! True to ignore NULL values
	bool ignore_nulls;
	//! The window boundaries
	WindowBoundary start = WindowBoundary::INVALID;
	WindowBoundary end = WindowBoundary::INVALID;

	unique_ptr<ParsedExpression> start_expr;
	unique_ptr<ParsedExpression> end_expr;
	//! Offset and default expressions for WINDOW_LEAD and WINDOW_LAG functions
	unique_ptr<ParsedExpression> offset_expr;
	unique_ptr<ParsedExpression> default_expr;

public:
	bool IsWindow() const override {
		return true;
	}

	//! Convert the Expression to a String
	string ToString() const override;

	static bool Equals(const WindowExpression *a, const WindowExpression *b);

	unique_ptr<ParsedExpression> Copy() const override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<ParsedExpression> Deserialize(ExpressionType type, FieldReader &source);

public:
	template <class T, class BASE, class ORDER_NODE>
	static string ToString(const T &entry, const string &schema, const string &function_name) {
		// Start with function call
		string result = schema.empty() ? function_name : schema + "." + function_name;
		result += "(";
		result += StringUtil::Join(entry.children, entry.children.size(), ", ",
		                           [](const unique_ptr<BASE> &child) { return child->ToString(); });
		// Lead/Lag extra arguments
		if (entry.offset_expr.get()) {
			result += ", ";
			result += entry.offset_expr->ToString();
		}
		if (entry.default_expr.get()) {
			result += ", ";
			result += entry.default_expr->ToString();
		}
		// IGNORE NULLS
		if (entry.ignore_nulls) {
			result += " IGNORE NULLS";
		}
		// FILTER
		if (entry.filter_expr) {
			result += ") FILTER (WHERE " + entry.filter_expr->ToString();
		}

		// Over clause
		result += ") OVER (";
		string sep;

		// Partitions
		if (!entry.partitions.empty()) {
			result += "PARTITION BY ";
			result += StringUtil::Join(entry.partitions, entry.partitions.size(), ", ",
			                           [](const unique_ptr<BASE> &partition) { return partition->ToString(); });
			sep = " ";
		}

		// Orders
		if (!entry.orders.empty()) {
			result += sep;
			result += "ORDER BY ";
			result += StringUtil::Join(entry.orders, entry.orders.size(), ", ",
			                           [](const ORDER_NODE &order) { return order.ToString(); });
			sep = " ";
		}

		// Rows/Range
		string units = "ROWS";
		string from;
		switch (entry.start) {
		case WindowBoundary::CURRENT_ROW_RANGE:
		case WindowBoundary::CURRENT_ROW_ROWS:
			from = "CURRENT ROW";
			units = (entry.start == WindowBoundary::CURRENT_ROW_RANGE) ? "RANGE" : "ROWS";
			break;
		case WindowBoundary::UNBOUNDED_PRECEDING:
			if (entry.end != WindowBoundary::CURRENT_ROW_RANGE) {
				from = "UNBOUNDED PRECEDING";
			}
			break;
		case WindowBoundary::EXPR_PRECEDING_ROWS:
		case WindowBoundary::EXPR_PRECEDING_RANGE:
			from = entry.start_expr->ToString() + " PRECEDING";
			units = (entry.start == WindowBoundary::EXPR_PRECEDING_RANGE) ? "RANGE" : "ROWS";
			break;
		case WindowBoundary::EXPR_FOLLOWING_ROWS:
		case WindowBoundary::EXPR_FOLLOWING_RANGE:
			from = entry.start_expr->ToString() + " FOLLOWING";
			units = (entry.start == WindowBoundary::EXPR_FOLLOWING_RANGE) ? "RANGE" : "ROWS";
			break;
		default:
			throw InternalException("Unrecognized FROM in WindowExpression");
		}

		string to;
		switch (entry.end) {
		case WindowBoundary::CURRENT_ROW_RANGE:
			if (entry.start != WindowBoundary::UNBOUNDED_PRECEDING) {
				to = "CURRENT ROW";
				units = "RANGE";
			}
			break;
		case WindowBoundary::CURRENT_ROW_ROWS:
			to = "CURRENT ROW";
			units = "ROWS";
			break;
		case WindowBoundary::UNBOUNDED_PRECEDING:
			to = "UNBOUNDED PRECEDING";
			break;
		case WindowBoundary::UNBOUNDED_FOLLOWING:
			to = "UNBOUNDED FOLLOWING";
			break;
		case WindowBoundary::EXPR_PRECEDING_ROWS:
		case WindowBoundary::EXPR_PRECEDING_RANGE:
			to = entry.end_expr->ToString() + " PRECEDING";
			units = (entry.end == WindowBoundary::EXPR_PRECEDING_RANGE) ? "RANGE" : "ROWS";
			break;
		case WindowBoundary::EXPR_FOLLOWING_ROWS:
		case WindowBoundary::EXPR_FOLLOWING_RANGE:
			to = entry.end_expr->ToString() + " FOLLOWING";
			units = (entry.end == WindowBoundary::EXPR_FOLLOWING_RANGE) ? "RANGE" : "ROWS";
			break;
		default:
			throw InternalException("Unrecognized TO in WindowExpression");
		}

		if (!from.empty() || !to.empty()) {
			result += sep + units;
		}
		if (!from.empty() && !to.empty()) {
			result += " BETWEEN ";
			result += from;
			result += " AND ";
			result += to;
		} else if (!from.empty()) {
			result += " ";
			result += from;
		} else if (!to.empty()) {
			result += " ";
			result += to;
		}

		result += ")";

		return result;
	}
};
} // namespace duckdb





namespace duckdb {
class AggregateFunction;

class BoundWindowExpression : public Expression {
public:
	BoundWindowExpression(ExpressionType type, LogicalType return_type, unique_ptr<AggregateFunction> aggregate,
	                      unique_ptr<FunctionData> bind_info);

	//! The bound aggregate function
	unique_ptr<AggregateFunction> aggregate;
	//! The bound function info
	unique_ptr<FunctionData> bind_info;
	//! The child expressions of the main window function
	vector<unique_ptr<Expression>> children;
	//! The set of expressions to partition by
	vector<unique_ptr<Expression>> partitions;
	//! Statistics belonging to the partitions expressions
	vector<unique_ptr<BaseStatistics>> partitions_stats;
	//! The set of ordering clauses
	vector<BoundOrderByNode> orders;
	//! Expression representing a filter, only used for aggregates
	unique_ptr<Expression> filter_expr;
	//! True to ignore NULL values
	bool ignore_nulls;
	//! The window boundaries
	WindowBoundary start = WindowBoundary::INVALID;
	WindowBoundary end = WindowBoundary::INVALID;

	unique_ptr<Expression> start_expr;
	unique_ptr<Expression> end_expr;
	//! Offset and default expressions for WINDOW_LEAD and WINDOW_LAG functions
	unique_ptr<Expression> offset_expr;
	unique_ptr<Expression> default_expr;

public:
	bool IsWindow() const override {
		return true;
	}
	bool IsFoldable() const override {
		return false;
	}

	string ToString() const override;

	bool KeysAreCompatible(const BoundWindowExpression *other) const;
	bool Equals(const BaseExpression *other) const override;

	unique_ptr<Expression> Copy() override;

	void Serialize(FieldWriter &writer) const override;
	static unique_ptr<Expression> Deserialize(ExpressionDeserializationState &state, FieldReader &reader);
};
} // namespace duckdb



#include <random>
namespace duckdb {

class AdaptiveFilter {
public:
	explicit AdaptiveFilter(const Expression &expr);
	explicit AdaptiveFilter(TableFilterSet *table_filters);
	void AdaptRuntimeStatistics(double duration);
	vector<idx_t> permutation;

private:
	//! used for adaptive expression reordering
	idx_t iteration_count;
	idx_t swap_idx;
	idx_t right_random_border;
	idx_t observe_interval;
	idx_t execute_interval;
	double runtime_sum;
	double prev_mean;
	bool observe;
	bool warmup;
	vector<idx_t> swap_likeliness;
	std::default_random_engine generator;
};
} // namespace duckdb


namespace duckdb {
class ColumnSegment;
class LocalTableStorage;
class Index;
class RowGroup;
class UpdateSegment;
class TableScanState;
class ColumnSegment;
class ValiditySegment;
class TableFilterSet;

struct SegmentScanState {
	virtual ~SegmentScanState() {
	}
};

struct IndexScanState {
	virtual ~IndexScanState() {
	}
};

typedef unordered_map<block_id_t, BufferHandle> buffer_handle_set_t;

struct ColumnScanState {
	//! The column segment that is currently being scanned
	ColumnSegment *current = nullptr;
	//! The current row index of the scan
	idx_t row_index = 0;
	//! The internal row index (i.e. the position of the SegmentScanState)
	idx_t internal_index = 0;
	//! Segment scan state
	unique_ptr<SegmentScanState> scan_state;
	//! Child states of the vector
	vector<ColumnScanState> child_states;
	//! Whether or not InitializeState has been called for this segment
	bool initialized = false;
	//! If this segment has already been checked for skipping purposes
	bool segment_checked = false;

public:
	//! Move the scan state forward by "count" rows (including all child states)
	void Next(idx_t count);
	//! Move ONLY this state forward by "count" rows (i.e. not the child states)
	void NextInternal(idx_t count);
	//! Move the scan state forward by STANDARD_VECTOR_SIZE rows
	void NextVector();
};

struct ColumnFetchState {
	//! The set of pinned block handles for this set of fetches
	buffer_handle_set_t handles;
	//! Any child states of the fetch
	vector<unique_ptr<ColumnFetchState>> child_states;

	BufferHandle &GetOrInsertHandle(ColumnSegment &segment);
};

struct LocalScanState {
	~LocalScanState();

	void SetStorage(shared_ptr<LocalTableStorage> storage);
	LocalTableStorage *GetStorage() {
		return storage.get();
	}

	idx_t chunk_index = 0;
	idx_t max_index = 0;
	idx_t last_chunk_count = 0;
	TableFilterSet *table_filters = nullptr;

private:
	shared_ptr<LocalTableStorage> storage;
};

class RowGroupScanState {
public:
	RowGroupScanState(TableScanState &parent_p) : parent(parent_p), row_group(nullptr), vector_index(0), max_row(0) {
	}

	//! The parent scan state
	TableScanState &parent;
	//! The current row_group we are scanning
	RowGroup *row_group = nullptr;
	//! The vector index within the row_group
	idx_t vector_index = 0;
	//! The maximum row index of this row_group scan
	idx_t max_row = 0;
	//! Child column scans
	unique_ptr<ColumnScanState[]> column_scans;
};

class TableScanState {
public:
	TableScanState() : row_group_scan_state(*this), max_row(0) {};

	//! The row_group scan state
	RowGroupScanState row_group_scan_state;
	//! The total maximum row index
	idx_t max_row = 0;
	//! The column identifiers of the scan
	vector<column_t> column_ids;
	//! The table filters (if any)
	TableFilterSet *table_filters = nullptr;
	//! Adaptive filter info (if any)
	unique_ptr<AdaptiveFilter> adaptive_filter;
	//! Transaction-local scan state
	LocalScanState local_state;
};

class CreateIndexScanState : public TableScanState {
public:
	vector<unique_ptr<StorageLockKey>> locks;
	unique_lock<mutex> append_lock;
	unique_lock<mutex> delete_lock;
};

} // namespace duckdb


namespace duckdb {
class DataTable;
class WriteAheadLog;
struct TableAppendState;

class LocalTableStorage : public std::enable_shared_from_this<LocalTableStorage> {
public:
	explicit LocalTableStorage(DataTable &table);
	~LocalTableStorage();

	DataTable &table;

	Allocator &allocator;
	//! The main chunk collection holding the data
	ChunkCollection collection;
	//! The set of unique indexes
	vector<unique_ptr<Index>> indexes;
	//! The set of deleted entries
	unordered_map<idx_t, unique_ptr<bool[]>> deleted_entries;
	//! The number of deleted rows
	idx_t deleted_rows;
	//! The number of active scans
	atomic<idx_t> active_scans;

public:
	void InitializeScan(LocalScanState &state, TableFilterSet *table_filters = nullptr);
	idx_t EstimatedSize();

	void Clear();
};

//! The LocalStorage class holds appends that have not been committed yet
class LocalStorage {
public:
	struct CommitState {
		unordered_map<DataTable *, unique_ptr<TableAppendState>> append_states;
	};

public:
	explicit LocalStorage(Transaction &transaction) : transaction(transaction) {
	}

	//! Initialize a scan of the local storage
	void InitializeScan(DataTable *table, LocalScanState &state, TableFilterSet *table_filters);
	//! Scan
	void Scan(LocalScanState &state, const vector<column_t> &column_ids, DataChunk &result);

	//! Append a chunk to the local storage
	void Append(DataTable *table, DataChunk &chunk);
	//! Delete a set of rows from the local storage
	idx_t Delete(DataTable *table, Vector &row_ids, idx_t count);
	//! Update a set of rows in the local storage
	void Update(DataTable *table, Vector &row_ids, const vector<column_t> &column_ids, DataChunk &data);

	//! Commits the local storage, writing it to the WAL and completing the commit
	void Commit(LocalStorage::CommitState &commit_state, Transaction &transaction, WriteAheadLog *log,
	            transaction_t commit_id);

	bool ChangesMade() noexcept {
		return table_storage.size() > 0;
	}
	idx_t EstimatedSize();

	bool Find(DataTable *table) {
		return table_storage.find(table) != table_storage.end();
	}

	idx_t AddedRows(DataTable *table) {
		auto entry = table_storage.find(table);
		if (entry == table_storage.end()) {
			return 0;
		}
		return entry->second->collection.Count() - entry->second->deleted_rows;
	}

	void AddColumn(DataTable *old_dt, DataTable *new_dt, ColumnDefinition &new_column, Expression *default_value);
	void ChangeType(DataTable *old_dt, DataTable *new_dt, idx_t changed_idx, const LogicalType &target_type,
	                const vector<column_t> &bound_columns, Expression &cast_expr);

	void MoveStorage(DataTable *old_dt, DataTable *new_dt);
	void FetchChunk(DataTable *table, Vector &row_ids, idx_t count, DataChunk &chunk);
	vector<unique_ptr<Index>> &GetIndexes(DataTable *table);

private:
	LocalTableStorage *GetStorage(DataTable *table);

	template <class T>
	bool ScanTableStorage(DataTable &table, LocalTableStorage &storage, T &&fun);

private:
	Transaction &transaction;
	unordered_map<DataTable *, shared_ptr<LocalTableStorage>> table_storage;

	void Flush(DataTable &table, LocalTableStorage &storage);
};

} // namespace duckdb



namespace duckdb {
class SequenceCatalogEntry;

class ColumnData;
class ClientContext;
class CatalogEntry;
class DataTable;
class DatabaseInstance;
class WriteAheadLog;

class ChunkVectorInfo;

struct DeleteInfo;
struct UpdateInfo;

//! The transaction object holds information about a currently running or past
//! transaction

class Transaction {
public:
	Transaction(weak_ptr<ClientContext> context, transaction_t start_time, transaction_t transaction_id,
	            timestamp_t start_timestamp, idx_t catalog_version);

	weak_ptr<ClientContext> context;
	//! The start timestamp of this transaction
	transaction_t start_time;
	//! The transaction id of this transaction
	transaction_t transaction_id;
	//! The commit id of this transaction, if it has successfully been committed
	transaction_t commit_id;
	//! Highest active query when the transaction finished, used for cleaning up
	transaction_t highest_active_query;
	//! The current active query for the transaction. Set to MAXIMUM_QUERY_ID if
	//! no query is active.
	atomic<transaction_t> active_query;
	//! The timestamp when the transaction started
	timestamp_t start_timestamp;
	//! The catalog version when the transaction was started
	idx_t catalog_version;
	//! The set of uncommitted appends for the transaction
	LocalStorage storage;
	//! Map of all sequences that were used during the transaction and the value they had in this transaction
	unordered_map<SequenceCatalogEntry *, SequenceValue> sequence_usage;
	//! Whether or not the transaction has been invalidated
	bool is_invalidated;

public:
	static Transaction &GetTransaction(ClientContext &context);

	void PushCatalogEntry(CatalogEntry *entry, data_ptr_t extra_data = nullptr, idx_t extra_data_size = 0);

	//! Commit the current transaction with the given commit identifier. Returns an error message if the transaction
	//! commit failed, or an empty string if the commit was sucessful
	string Commit(DatabaseInstance &db, transaction_t commit_id, bool checkpoint) noexcept;
	//! Returns whether or not a commit of this transaction should trigger an automatic checkpoint
	bool AutomaticCheckpoint(DatabaseInstance &db);

	//! Rollback
	void Rollback() noexcept {
		undo_buffer.Rollback();
	}
	//! Cleanup the undo buffer
	void Cleanup() {
		undo_buffer.Cleanup();
	}

	void Invalidate() {
		is_invalidated = true;
	}
	bool IsInvalidated() {
		return is_invalidated;
	}
	bool ChangesMade();

	timestamp_t GetCurrentTransactionStartTimestamp() {
		return start_timestamp;
	}

	void PushDelete(DataTable *table, ChunkVectorInfo *vinfo, row_t rows[], idx_t count, idx_t base_row);
	void PushAppend(DataTable *table, idx_t row_start, idx_t row_count);
	UpdateInfo *CreateUpdateInfo(idx_t type_size, idx_t entries);

private:
	//! The undo buffer is used to store old versions of rows that are updated
	//! or deleted
	UndoBuffer undo_buffer;

	Transaction(const Transaction &) = delete;
};

} // namespace duckdb

#include <functional>
#include <memory>

namespace duckdb {
struct AlterInfo;

class ClientContext;

typedef unordered_map<CatalogSet *, unique_lock<mutex>> set_lock_map_t;

struct MappingValue {
	explicit MappingValue(idx_t index_) : index(index_), timestamp(0), deleted(false), parent(nullptr) {
	}

	idx_t index;
	transaction_t timestamp;
	bool deleted;
	unique_ptr<MappingValue> child;
	MappingValue *parent;
};

//! The Catalog Set stores (key, value) map of a set of CatalogEntries
class CatalogSet {
	friend class DependencyManager;
	friend class EntryDropper;

public:
	DUCKDB_API explicit CatalogSet(Catalog &catalog, unique_ptr<DefaultGenerator> defaults = nullptr);

	//! Create an entry in the catalog set. Returns whether or not it was
	//! successful.
	DUCKDB_API bool CreateEntry(ClientContext &context, const string &name, unique_ptr<CatalogEntry> value,
	                            unordered_set<CatalogEntry *> &dependencies);

	DUCKDB_API bool AlterEntry(ClientContext &context, const string &name, AlterInfo *alter_info);

	DUCKDB_API bool DropEntry(ClientContext &context, const string &name, bool cascade);

	bool AlterOwnership(ClientContext &context, ChangeOwnershipInfo *info);

	void CleanupEntry(CatalogEntry *catalog_entry);

	//! Returns the entry with the specified name
	DUCKDB_API CatalogEntry *GetEntry(ClientContext &context, const string &name);

	//! Gets the entry that is most similar to the given name (i.e. smallest levenshtein distance), or empty string if
	//! none is found. The returned pair consists of the entry name and the distance (smaller means closer).
	pair<string, idx_t> SimilarEntry(ClientContext &context, const string &name);

	//! Rollback <entry> to be the currently valid entry for a certain catalog
	//! entry
	void Undo(CatalogEntry *entry);

	//! Scan the catalog set, invoking the callback method for every committed entry
	DUCKDB_API void Scan(const std::function<void(CatalogEntry *)> &callback);
	//! Scan the catalog set, invoking the callback method for every entry
	DUCKDB_API void Scan(ClientContext &context, const std::function<void(CatalogEntry *)> &callback);

	template <class T>
	vector<T *> GetEntries(ClientContext &context) {
		vector<T *> result;
		Scan(context, [&](CatalogEntry *entry) { result.push_back((T *)entry); });
		return result;
	}

	DUCKDB_API static bool HasConflict(ClientContext &context, transaction_t timestamp);
	DUCKDB_API static bool UseTimestamp(ClientContext &context, transaction_t timestamp);

	CatalogEntry *GetEntryFromIndex(idx_t index);
	void UpdateTimestamp(CatalogEntry *entry, transaction_t timestamp);

private:
	//! Adjusts table dependencies on the event of an UNDO
	void AdjustTableDependencies(CatalogEntry *entry);
	//! Adjust one dependency
	void AdjustDependency(CatalogEntry *entry, TableCatalogEntry *table, ColumnDefinition &column, bool remove);
	//! Adjust User dependency
	void AdjustUserDependency(CatalogEntry *entry, ColumnDefinition &column, bool remove);
	//! Given a root entry, gets the entry valid for this transaction
	CatalogEntry *GetEntryForTransaction(ClientContext &context, CatalogEntry *current);
	CatalogEntry *GetCommittedEntry(CatalogEntry *current);
	bool GetEntryInternal(ClientContext &context, const string &name, idx_t &entry_index, CatalogEntry *&entry);
	bool GetEntryInternal(ClientContext &context, idx_t entry_index, CatalogEntry *&entry);
	//! Drops an entry from the catalog set; must hold the catalog_lock to safely call this
	void DropEntryInternal(ClientContext &context, idx_t entry_index, CatalogEntry &entry, bool cascade);
	CatalogEntry *CreateEntryInternal(ClientContext &context, unique_ptr<CatalogEntry> entry);
	MappingValue *GetMapping(ClientContext &context, const string &name, bool get_latest = false);
	void PutMapping(ClientContext &context, const string &name, idx_t entry_index);
	void DeleteMapping(ClientContext &context, const string &name);
	void DropEntryDependencies(ClientContext &context, idx_t entry_index, CatalogEntry &entry, bool cascade);

	//! Create all default entries
	void CreateDefaultEntries(ClientContext &context, unique_lock<mutex> &lock);
	//! Attempt to create a default entry with the specified name. Returns the entry if successful, nullptr otherwise.
	CatalogEntry *CreateDefaultEntry(ClientContext &context, const string &name, unique_lock<mutex> &lock);

private:
	Catalog &catalog;
	//! The catalog lock is used to make changes to the data
	mutex catalog_lock;
	//! Mapping of string to catalog entry
	case_insensitive_map_t<unique_ptr<MappingValue>> mapping;
	//! The set of catalog entries
	unordered_map<idx_t, unique_ptr<CatalogEntry>> entries;
	//! The current catalog entry index
	idx_t current_entry = 0;
	//! The generator used to generate default internal entries
	unique_ptr<DefaultGenerator> defaults;
};
} // namespace duckdb



namespace duckdb {
class ClientContext;

class StandardEntry;
class TableCatalogEntry;
class TableFunctionCatalogEntry;
class SequenceCatalogEntry;
class Serializer;
class Deserializer;

enum class OnCreateConflict : uint8_t;

struct AlterTableInfo;
struct CreateIndexInfo;
struct CreateFunctionInfo;
struct CreateCollationInfo;
struct CreateViewInfo;
struct BoundCreateTableInfo;
struct CreatePragmaFunctionInfo;
struct CreateSequenceInfo;
struct CreateSchemaInfo;
struct CreateTableFunctionInfo;
struct CreateCopyFunctionInfo;
struct CreateTypeInfo;

struct DropInfo;

//! A schema in the catalog
class SchemaCatalogEntry : public CatalogEntry {
	friend class Catalog;

public:
	SchemaCatalogEntry(Catalog *catalog, string name, bool is_internal);

private:
	//! The catalog set holding the tables
	CatalogSet tables;
	//! The catalog set holding the indexes
	CatalogSet indexes;
	//! The catalog set holding the table functions
	CatalogSet table_functions;
	//! The catalog set holding the copy functions
	CatalogSet copy_functions;
	//! The catalog set holding the pragma functions
	CatalogSet pragma_functions;
	//! The catalog set holding the scalar and aggregate functions
	CatalogSet functions;
	//! The catalog set holding the sequences
	CatalogSet sequences;
	//! The catalog set holding the collations
	CatalogSet collations;
	//! The catalog set holding the types
	CatalogSet types;

public:
	//! Scan the specified catalog set, invoking the callback method for every entry
	void Scan(ClientContext &context, CatalogType type, const std::function<void(CatalogEntry *)> &callback);
	//! Scan the specified catalog set, invoking the callback method for every committed entry
	void Scan(CatalogType type, const std::function<void(CatalogEntry *)> &callback);

	//! Serialize the meta information of the SchemaCatalogEntry a serializer
	virtual void Serialize(Serializer &serializer);
	//! Deserializes to a CreateSchemaInfo
	static unique_ptr<CreateSchemaInfo> Deserialize(Deserializer &source);

	string ToSQL() override;

	//! Creates an index with the given name in the schema
	CatalogEntry *CreateIndex(ClientContext &context, CreateIndexInfo *info, TableCatalogEntry *table);

private:
	//! Create a scalar or aggregate function within the given schema
	CatalogEntry *CreateFunction(ClientContext &context, CreateFunctionInfo *info);
	//! Creates a table with the given name in the schema
	CatalogEntry *CreateTable(ClientContext &context, BoundCreateTableInfo *info);
	//! Creates a view with the given name in the schema
	CatalogEntry *CreateView(ClientContext &context, CreateViewInfo *info);
	//! Creates a sequence with the given name in the schema
	CatalogEntry *CreateSequence(ClientContext &context, CreateSequenceInfo *info);
	//! Create a table function within the given schema
	CatalogEntry *CreateTableFunction(ClientContext &context, CreateTableFunctionInfo *info);
	//! Create a copy function within the given schema
	CatalogEntry *CreateCopyFunction(ClientContext &context, CreateCopyFunctionInfo *info);
	//! Create a pragma function within the given schema
	CatalogEntry *CreatePragmaFunction(ClientContext &context, CreatePragmaFunctionInfo *info);
	//! Create a collation within the given schema
	CatalogEntry *CreateCollation(ClientContext &context, CreateCollationInfo *info);
	//! Create a enum within the given schema
	CatalogEntry *CreateType(ClientContext &context, CreateTypeInfo *info);

	//! Drops an entry from the schema
	void DropEntry(ClientContext &context, DropInfo *info);

	//! Append a scalar or aggregate function within the given schema
	CatalogEntry *AddFunction(ClientContext &context, CreateFunctionInfo *info);

	//! Alters a catalog entry
	void Alter(ClientContext &context, AlterInfo *info);

	//! Add a catalog entry to this schema
	CatalogEntry *AddEntry(ClientContext &context, unique_ptr<StandardEntry> entry, OnCreateConflict on_conflict);
	//! Add a catalog entry to this schema
	CatalogEntry *AddEntry(ClientContext &context, unique_ptr<StandardEntry> entry, OnCreateConflict on_conflict,
	                       unordered_set<CatalogEntry *> dependencies);

	//! Get the catalog set for the specified type
	CatalogSet &GetCatalogSet(CatalogType type);
};
} // namespace duckdb



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/deque.hpp
//
//
//===----------------------------------------------------------------------===//



#include <deque>

namespace duckdb {
using std::deque;
}


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/progress_bar.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//
//                         DuckDB
//
// duckdb.h
//
//
//===----------------------------------------------------------------------===//



// duplicate of duckdb/main/winapi.hpp
#ifndef DUCKDB_API
#ifdef _WIN32
#if defined(DUCKDB_BUILD_LIBRARY) && !defined(DUCKDB_BUILD_LOADABLE_EXTENSION)
#define DUCKDB_API __declspec(dllexport)
#else
#define DUCKDB_API __declspec(dllimport)
#endif
#else
#define DUCKDB_API
#endif
#endif

// duplicate of duckdb/main/winapi.hpp
#ifndef DUCKDB_EXTENSION_API
#ifdef _WIN32
#ifdef DUCKDB_BUILD_LOADABLE_EXTENSION
#define DUCKDB_EXTENSION_API __declspec(dllexport)
#else
#define DUCKDB_EXTENSION_API
#endif
#else
#define DUCKDB_EXTENSION_API __attribute__((visibility("default")))
#endif
#endif

// duplicate of duckdb/common/constants.hpp
#ifndef DUCKDB_API_0_3_1
#define DUCKDB_API_0_3_1 1
#endif
#ifndef DUCKDB_API_0_3_2
#define DUCKDB_API_0_3_2 2
#endif
#ifndef DUCKDB_API_LATEST
#define DUCKDB_API_LATEST DUCKDB_API_0_3_2
#endif

#ifndef DUCKDB_API_VERSION
#define DUCKDB_API_VERSION DUCKDB_API_LATEST
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

//===--------------------------------------------------------------------===//
// Type Information
//===--------------------------------------------------------------------===//
typedef uint64_t idx_t;

typedef enum DUCKDB_TYPE {
	DUCKDB_TYPE_INVALID = 0,
	// bool
	DUCKDB_TYPE_BOOLEAN,
	// int8_t
	DUCKDB_TYPE_TINYINT,
	// int16_t
	DUCKDB_TYPE_SMALLINT,
	// int32_t
	DUCKDB_TYPE_INTEGER,
	// int64_t
	DUCKDB_TYPE_BIGINT,
	// uint8_t
	DUCKDB_TYPE_UTINYINT,
	// uint16_t
	DUCKDB_TYPE_USMALLINT,
	// uint32_t
	DUCKDB_TYPE_UINTEGER,
	// uint64_t
	DUCKDB_TYPE_UBIGINT,
	// float
	DUCKDB_TYPE_FLOAT,
	// double
	DUCKDB_TYPE_DOUBLE,
	// duckdb_timestamp, in microseconds
	DUCKDB_TYPE_TIMESTAMP,
	// duckdb_date
	DUCKDB_TYPE_DATE,
	// duckdb_time
	DUCKDB_TYPE_TIME,
	// duckdb_interval
	DUCKDB_TYPE_INTERVAL,
	// duckdb_hugeint
	DUCKDB_TYPE_HUGEINT,
	// const char*
	DUCKDB_TYPE_VARCHAR,
	// duckdb_blob
	DUCKDB_TYPE_BLOB,
	// decimal
	DUCKDB_TYPE_DECIMAL,
	// duckdb_timestamp, in seconds
	DUCKDB_TYPE_TIMESTAMP_S,
	// duckdb_timestamp, in milliseconds
	DUCKDB_TYPE_TIMESTAMP_MS,
	// duckdb_timestamp, in nanoseconds
	DUCKDB_TYPE_TIMESTAMP_NS,
	// enum type, only useful as logical type
	DUCKDB_TYPE_ENUM,
	// list type, only useful as logical type
	DUCKDB_TYPE_LIST,
	// struct type, only useful as logical type
	DUCKDB_TYPE_STRUCT,
	// map type, only useful as logical type
	DUCKDB_TYPE_MAP,
	// duckdb_hugeint
	DUCKDB_TYPE_UUID,
	// const char*
	DUCKDB_TYPE_JSON,
} duckdb_type;

//! Days are stored as days since 1970-01-01
//! Use the duckdb_from_date/duckdb_to_date function to extract individual information
typedef struct {
	int32_t days;
} duckdb_date;

typedef struct {
	int32_t year;
	int8_t month;
	int8_t day;
} duckdb_date_struct;

//! Time is stored as microseconds since 00:00:00
//! Use the duckdb_from_time/duckdb_to_time function to extract individual information
typedef struct {
	int64_t micros;
} duckdb_time;

typedef struct {
	int8_t hour;
	int8_t min;
	int8_t sec;
	int32_t micros;
} duckdb_time_struct;

//! Timestamps are stored as microseconds since 1970-01-01
//! Use the duckdb_from_timestamp/duckdb_to_timestamp function to extract individual information
typedef struct {
	int64_t micros;
} duckdb_timestamp;

typedef struct {
	duckdb_date_struct date;
	duckdb_time_struct time;
} duckdb_timestamp_struct;

typedef struct {
	int32_t months;
	int32_t days;
	int64_t micros;
} duckdb_interval;

//! Hugeints are composed in a (lower, upper) component
//! The value of the hugeint is upper * 2^64 + lower
//! For easy usage, the functions duckdb_hugeint_to_double/duckdb_double_to_hugeint are recommended
typedef struct {
	uint64_t lower;
	int64_t upper;
} duckdb_hugeint;

typedef struct {
	uint8_t width;
	uint8_t scale;

	duckdb_hugeint value;
} duckdb_decimal;

typedef struct {
	void *data;
	idx_t size;
} duckdb_blob;

typedef struct {
#if DUCKDB_API_VERSION < DUCKDB_API_0_3_2
	void *data;
	bool *nullmask;
	duckdb_type type;
	char *name;
#else
	// deprecated, use duckdb_column_data
	void *__deprecated_data;
	// deprecated, use duckdb_nullmask_data
	bool *__deprecated_nullmask;
	// deprecated, use duckdb_column_type
	duckdb_type __deprecated_type;
	// deprecated, use duckdb_column_name
	char *__deprecated_name;
#endif
	void *internal_data;
} duckdb_column;

typedef struct {
#if DUCKDB_API_VERSION < DUCKDB_API_0_3_2
	idx_t column_count;
	idx_t row_count;
	idx_t rows_changed;
	duckdb_column *columns;
	char *error_message;
#else
	// deprecated, use duckdb_column_count
	idx_t __deprecated_column_count;
	// deprecated, use duckdb_row_count
	idx_t __deprecated_row_count;
	// deprecated, use duckdb_rows_changed
	idx_t __deprecated_rows_changed;
	// deprecated, use duckdb_column_ family of functions
	duckdb_column *__deprecated_columns;
	// deprecated, use duckdb_result_error
	char *__deprecated_error_message;
#endif
	void *internal_data;
} duckdb_result;

typedef void *duckdb_database;
typedef void *duckdb_connection;
typedef void *duckdb_prepared_statement;
typedef void *duckdb_pending_result;
typedef void *duckdb_appender;
typedef void *duckdb_arrow;
typedef void *duckdb_config;
typedef void *duckdb_arrow_schema;
typedef void *duckdb_arrow_array;
typedef void *duckdb_logical_type;
typedef void *duckdb_data_chunk;
typedef void *duckdb_vector;
typedef void *duckdb_value;

typedef enum { DuckDBSuccess = 0, DuckDBError = 1 } duckdb_state;
typedef enum {
	DUCKDB_PENDING_RESULT_READY = 0,
	DUCKDB_PENDING_RESULT_NOT_READY = 1,
	DUCKDB_PENDING_ERROR = 2
} duckdb_pending_state;

//===--------------------------------------------------------------------===//
// Open/Connect
//===--------------------------------------------------------------------===//

/*!
Creates a new database or opens an existing database file stored at the the given path.
If no path is given a new in-memory database is created instead.

* path: Path to the database file on disk, or `nullptr` or `:memory:` to open an in-memory database.
* out_database: The result database object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_open(const char *path, duckdb_database *out_database);

/*!
Extended version of duckdb_open. Creates a new database or opens an existing database file stored at the the given path.

* path: Path to the database file on disk, or `nullptr` or `:memory:` to open an in-memory database.
* out_database: The result database object.
* config: (Optional) configuration used to start up the database system.
* out_error: If set and the function returns DuckDBError, this will contain the reason why the start-up failed.
Note that the error must be freed using `duckdb_free`.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_open_ext(const char *path, duckdb_database *out_database, duckdb_config config,
                                        char **out_error);

/*!
Closes the specified database and de-allocates all memory allocated for that database.
This should be called after you are done with any database allocated through `duckdb_open`.
Note that failing to call `duckdb_close` (in case of e.g. a program crash) will not cause data corruption.
Still it is recommended to always correctly close a database object after you are done with it.

* database: The database object to shut down.
*/
DUCKDB_API void duckdb_close(duckdb_database *database);

/*!
Opens a connection to a database. Connections are required to query the database, and store transactional state
associated with the connection.

* database: The database file to connect to.
* out_connection: The result connection object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_connect(duckdb_database database, duckdb_connection *out_connection);

/*!
Closes the specified connection and de-allocates all memory allocated for that connection.

* connection: The connection to close.
*/
DUCKDB_API void duckdb_disconnect(duckdb_connection *connection);

//===--------------------------------------------------------------------===//
// Configuration
//===--------------------------------------------------------------------===//
/*!
Initializes an empty configuration object that can be used to provide start-up options for the DuckDB instance
through `duckdb_open_ext`.

This will always succeed unless there is a malloc failure.

* out_config: The result configuration object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_create_config(duckdb_config *out_config);

/*!
This returns the total amount of configuration options available for usage with `duckdb_get_config_flag`.

This should not be called in a loop as it internally loops over all the options.

* returns: The amount of config options available.
*/
DUCKDB_API size_t duckdb_config_count();

/*!
Obtains a human-readable name and description of a specific configuration option. This can be used to e.g.
display configuration options. This will succeed unless `index` is out of range (i.e. `>= duckdb_config_count`).

The result name or description MUST NOT be freed.

* index: The index of the configuration option (between 0 and `duckdb_config_count`)
* out_name: A name of the configuration flag.
* out_description: A description of the configuration flag.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_get_config_flag(size_t index, const char **out_name, const char **out_description);

/*!
Sets the specified option for the specified configuration. The configuration option is indicated by name.
To obtain a list of config options, see `duckdb_get_config_flag`.

In the source code, configuration options are defined in `config.cpp`.

This can fail if either the name is invalid, or if the value provided for the option is invalid.

* duckdb_config: The configuration object to set the option on.
* name: The name of the configuration flag to set.
* option: The value to set the configuration flag to.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_set_config(duckdb_config config, const char *name, const char *option);

/*!
Destroys the specified configuration option and de-allocates all memory allocated for the object.

* config: The configuration object to destroy.
*/
DUCKDB_API void duckdb_destroy_config(duckdb_config *config);

//===--------------------------------------------------------------------===//
// Query Execution
//===--------------------------------------------------------------------===//
/*!
Executes a SQL query within a connection and stores the full (materialized) result in the out_result pointer.
If the query fails to execute, DuckDBError is returned and the error message can be retrieved by calling
`duckdb_result_error`.

Note that after running `duckdb_query`, `duckdb_destroy_result` must be called on the result object even if the
query fails, otherwise the error stored within the result will not be freed correctly.

* connection: The connection to perform the query in.
* query: The SQL query to run.
* out_result: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_query(duckdb_connection connection, const char *query, duckdb_result *out_result);

/*!
Closes the result and de-allocates all memory allocated for that connection.

* result: The result to destroy.
*/
DUCKDB_API void duckdb_destroy_result(duckdb_result *result);

/*!
Returns the column name of the specified column. The result should not need be freed; the column names will
automatically be destroyed when the result is destroyed.

Returns `NULL` if the column is out of range.

* result: The result object to fetch the column name from.
* col: The column index.
* returns: The column name of the specified column.
*/
DUCKDB_API const char *duckdb_column_name(duckdb_result *result, idx_t col);

/*!
Returns the column type of the specified column.

Returns `DUCKDB_TYPE_INVALID` if the column is out of range.

* result: The result object to fetch the column type from.
* col: The column index.
* returns: The column type of the specified column.
*/
DUCKDB_API duckdb_type duckdb_column_type(duckdb_result *result, idx_t col);

/*!
Returns the logical column type of the specified column.

The return type of this call should be destroyed with `duckdb_destroy_logical_type`.

Returns `NULL` if the column is out of range.

* result: The result object to fetch the column type from.
* col: The column index.
* returns: The logical column type of the specified column.
*/
DUCKDB_API duckdb_logical_type duckdb_column_logical_type(duckdb_result *result, idx_t col);

/*!
Returns the number of columns present in a the result object.

* result: The result object.
* returns: The number of columns present in the result object.
*/
DUCKDB_API idx_t duckdb_column_count(duckdb_result *result);

/*!
Returns the number of rows present in a the result object.

* result: The result object.
* returns: The number of rows present in the result object.
*/
DUCKDB_API idx_t duckdb_row_count(duckdb_result *result);

/*!
Returns the number of rows changed by the query stored in the result. This is relevant only for INSERT/UPDATE/DELETE
queries. For other queries the rows_changed will be 0.

* result: The result object.
* returns: The number of rows changed.
*/
DUCKDB_API idx_t duckdb_rows_changed(duckdb_result *result);

/*!
**DEPRECATED**: Prefer using `duckdb_result_get_chunk` instead.

Returns the data of a specific column of a result in columnar format.

The function returns a dense array which contains the result data. The exact type stored in the array depends on the
corresponding duckdb_type (as provided by `duckdb_column_type`). For the exact type by which the data should be
accessed, see the comments in [the types section](types) or the `DUCKDB_TYPE` enum.

For example, for a column of type `DUCKDB_TYPE_INTEGER`, rows can be accessed in the following manner:
```c
int32_t *data = (int32_t *) duckdb_column_data(&result, 0);
printf("Data for row %d: %d\n", row, data[row]);
```

* result: The result object to fetch the column data from.
* col: The column index.
* returns: The column data of the specified column.
*/
DUCKDB_API void *duckdb_column_data(duckdb_result *result, idx_t col);

/*!
**DEPRECATED**: Prefer using `duckdb_result_get_chunk` instead.

Returns the nullmask of a specific column of a result in columnar format. The nullmask indicates for every row
whether or not the corresponding row is `NULL`. If a row is `NULL`, the values present in the array provided
by `duckdb_column_data` are undefined.

```c
int32_t *data = (int32_t *) duckdb_column_data(&result, 0);
bool *nullmask = duckdb_nullmask_data(&result, 0);
if (nullmask[row]) {
    printf("Data for row %d: NULL\n", row);
} else {
    printf("Data for row %d: %d\n", row, data[row]);
}
```

* result: The result object to fetch the nullmask from.
* col: The column index.
* returns: The nullmask of the specified column.
*/
DUCKDB_API bool *duckdb_nullmask_data(duckdb_result *result, idx_t col);

/*!
Returns the error message contained within the result. The error is only set if `duckdb_query` returns `DuckDBError`.

The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_result` is called.

* result: The result object to fetch the error from.
* returns: The error of the result.
*/
DUCKDB_API const char *duckdb_result_error(duckdb_result *result);

//===--------------------------------------------------------------------===//
// Result Functions
//===--------------------------------------------------------------------===//

/*!
Fetches a data chunk from the duckdb_result. This function should be called repeatedly until the result is exhausted.

This function supersedes all `duckdb_value` functions, as well as the `duckdb_column_data` and `duckdb_nullmask_data`
functions. It results in significantly better performance, and should be preferred in newer code-bases.

If this function is used, none of the other result functions can be used and vice versa (i.e. this function cannot be
mixed with the legacy result functions).

Use `duckdb_result_chunk_count` to figure out how many chunks there are in the result.

* result: The result object to fetch the data chunk from.
* chunk_index: The chunk index to fetch from.
* returns: The resulting data chunk. Returns `NULL` if the chunk index is out of bounds.
*/
DUCKDB_API duckdb_data_chunk duckdb_result_get_chunk(duckdb_result result, idx_t chunk_index);

/*!
Returns the number of data chunks present in the result.

* result: The result object
* returns: The resulting data chunk. Returns `NULL` if the chunk index is out of bounds.
*/
DUCKDB_API idx_t duckdb_result_chunk_count(duckdb_result result);

// Safe fetch functions
// These functions will perform conversions if necessary.
// On failure (e.g. if conversion cannot be performed or if the value is NULL) a default value is returned.
// Note that these functions are slow since they perform bounds checking and conversion
// For fast access of values prefer using `duckdb_result_get_chunk`

/*!
 * returns: The boolean value at the specified location, or false if the value cannot be converted.
 */
DUCKDB_API bool duckdb_value_boolean(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The int8_t value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API int8_t duckdb_value_int8(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The int16_t value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API int16_t duckdb_value_int16(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The int32_t value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API int32_t duckdb_value_int32(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The int64_t value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API int64_t duckdb_value_int64(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The duckdb_hugeint value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API duckdb_hugeint duckdb_value_hugeint(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The duckdb_decimal value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API duckdb_decimal duckdb_value_decimal(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The uint8_t value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API uint8_t duckdb_value_uint8(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The uint16_t value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API uint16_t duckdb_value_uint16(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The uint32_t value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API uint32_t duckdb_value_uint32(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The uint64_t value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API uint64_t duckdb_value_uint64(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The float value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API float duckdb_value_float(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The double value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API double duckdb_value_double(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The duckdb_date value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API duckdb_date duckdb_value_date(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The duckdb_time value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API duckdb_time duckdb_value_time(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The duckdb_timestamp value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API duckdb_timestamp duckdb_value_timestamp(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: The duckdb_interval value at the specified location, or 0 if the value cannot be converted.
 */
DUCKDB_API duckdb_interval duckdb_value_interval(duckdb_result *result, idx_t col, idx_t row);

/*!
* returns: The char* value at the specified location, or nullptr if the value cannot be converted.
The result must be freed with `duckdb_free`.
*/
DUCKDB_API char *duckdb_value_varchar(duckdb_result *result, idx_t col, idx_t row);

/*!
* returns: The char* value at the specified location. ONLY works on VARCHAR columns and does not auto-cast.
If the column is NOT a VARCHAR column this function will return NULL.

The result must NOT be freed.
*/
DUCKDB_API char *duckdb_value_varchar_internal(duckdb_result *result, idx_t col, idx_t row);

/*!
* returns: The duckdb_blob value at the specified location. Returns a blob with blob.data set to nullptr if the
value cannot be converted. The resulting "blob.data" must be freed with `duckdb_free.`
*/
DUCKDB_API duckdb_blob duckdb_value_blob(duckdb_result *result, idx_t col, idx_t row);

/*!
 * returns: Returns true if the value at the specified index is NULL, and false otherwise.
 */
DUCKDB_API bool duckdb_value_is_null(duckdb_result *result, idx_t col, idx_t row);

//===--------------------------------------------------------------------===//
// Helpers
//===--------------------------------------------------------------------===//
/*!
Allocate `size` bytes of memory using the duckdb internal malloc function. Any memory allocated in this manner
should be freed using `duckdb_free`.

* size: The number of bytes to allocate.
* returns: A pointer to the allocated memory region.
*/
DUCKDB_API void *duckdb_malloc(size_t size);

/*!
Free a value returned from `duckdb_malloc`, `duckdb_value_varchar` or `duckdb_value_blob`.

* ptr: The memory region to de-allocate.
*/
DUCKDB_API void duckdb_free(void *ptr);

/*!
The internal vector size used by DuckDB.
This is the amount of tuples that will fit into a data chunk created by `duckdb_create_data_chunk`.

* returns: The vector size.
*/
DUCKDB_API idx_t duckdb_vector_size();

//===--------------------------------------------------------------------===//
// Date/Time/Timestamp Helpers
//===--------------------------------------------------------------------===//
/*!
Decompose a `duckdb_date` object into year, month and date (stored as `duckdb_date_struct`).

* date: The date object, as obtained from a `DUCKDB_TYPE_DATE` column.
* returns: The `duckdb_date_struct` with the decomposed elements.
*/
DUCKDB_API duckdb_date_struct duckdb_from_date(duckdb_date date);

/*!
Re-compose a `duckdb_date` from year, month and date (`duckdb_date_struct`).

* date: The year, month and date stored in a `duckdb_date_struct`.
* returns: The `duckdb_date` element.
*/
DUCKDB_API duckdb_date duckdb_to_date(duckdb_date_struct date);

/*!
Decompose a `duckdb_time` object into hour, minute, second and microsecond (stored as `duckdb_time_struct`).

* time: The time object, as obtained from a `DUCKDB_TYPE_TIME` column.
* returns: The `duckdb_time_struct` with the decomposed elements.
*/
DUCKDB_API duckdb_time_struct duckdb_from_time(duckdb_time time);

/*!
Re-compose a `duckdb_time` from hour, minute, second and microsecond (`duckdb_time_struct`).

* time: The hour, minute, second and microsecond in a `duckdb_time_struct`.
* returns: The `duckdb_time` element.
*/
DUCKDB_API duckdb_time duckdb_to_time(duckdb_time_struct time);

/*!
Decompose a `duckdb_timestamp` object into a `duckdb_timestamp_struct`.

* ts: The ts object, as obtained from a `DUCKDB_TYPE_TIMESTAMP` column.
* returns: The `duckdb_timestamp_struct` with the decomposed elements.
*/
DUCKDB_API duckdb_timestamp_struct duckdb_from_timestamp(duckdb_timestamp ts);

/*!
Re-compose a `duckdb_timestamp` from a duckdb_timestamp_struct.

* ts: The de-composed elements in a `duckdb_timestamp_struct`.
* returns: The `duckdb_timestamp` element.
*/
DUCKDB_API duckdb_timestamp duckdb_to_timestamp(duckdb_timestamp_struct ts);

//===--------------------------------------------------------------------===//
// Hugeint Helpers
//===--------------------------------------------------------------------===//
/*!
Converts a duckdb_hugeint object (as obtained from a `DUCKDB_TYPE_HUGEINT` column) into a double.

* val: The hugeint value.
* returns: The converted `double` element.
*/
DUCKDB_API double duckdb_hugeint_to_double(duckdb_hugeint val);

/*!
Converts a double value to a duckdb_hugeint object.

If the conversion fails because the double value is too big the result will be 0.

* val: The double value.
* returns: The converted `duckdb_hugeint` element.
*/
DUCKDB_API duckdb_hugeint duckdb_double_to_hugeint(double val);

//===--------------------------------------------------------------------===//
// Decimal Helpers
//===--------------------------------------------------------------------===//
/*!
Converts a duckdb_decimal object (as obtained from a `DUCKDB_TYPE_DECIMAL` column) into a double.

* val: The decimal value.
* returns: The converted `double` element.
*/
DUCKDB_API double duckdb_decimal_to_double(duckdb_decimal val);

//===--------------------------------------------------------------------===//
// Prepared Statements
//===--------------------------------------------------------------------===//
// A prepared statement is a parameterized query that allows you to bind parameters to it.
// * This is useful to easily supply parameters to functions and avoid SQL injection attacks.
// * This is useful to speed up queries that you will execute several times with different parameters.
// Because the query will only be parsed, bound, optimized and planned once during the prepare stage,
// rather than once per execution.
// For example:
//   SELECT * FROM tbl WHERE id=?
// Or a query with multiple parameters:
//   SELECT * FROM tbl WHERE id=$1 OR name=$2

/*!
Create a prepared statement object from a query.

Note that after calling `duckdb_prepare`, the prepared statement should always be destroyed using
`duckdb_destroy_prepare`, even if the prepare fails.

If the prepare fails, `duckdb_prepare_error` can be called to obtain the reason why the prepare failed.

* connection: The connection object
* query: The SQL query to prepare
* out_prepared_statement: The resulting prepared statement object
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_prepare(duckdb_connection connection, const char *query,
                                       duckdb_prepared_statement *out_prepared_statement);

/*!
Closes the prepared statement and de-allocates all memory allocated for the statement.

* prepared_statement: The prepared statement to destroy.
*/
DUCKDB_API void duckdb_destroy_prepare(duckdb_prepared_statement *prepared_statement);

/*!
Returns the error message associated with the given prepared statement.
If the prepared statement has no error message, this returns `nullptr` instead.

The error message should not be freed. It will be de-allocated when `duckdb_destroy_prepare` is called.

* prepared_statement: The prepared statement to obtain the error from.
* returns: The error message, or `nullptr` if there is none.
*/
DUCKDB_API const char *duckdb_prepare_error(duckdb_prepared_statement prepared_statement);

/*!
Returns the number of parameters that can be provided to the given prepared statement.

Returns 0 if the query was not successfully prepared.

* prepared_statement: The prepared statement to obtain the number of parameters for.
*/
DUCKDB_API idx_t duckdb_nparams(duckdb_prepared_statement prepared_statement);

/*!
Returns the parameter type for the parameter at the given index.

Returns `DUCKDB_TYPE_INVALID` if the parameter index is out of range or the statement was not successfully prepared.

* prepared_statement: The prepared statement.
* param_idx: The parameter index.
* returns: The parameter type
*/
DUCKDB_API duckdb_type duckdb_param_type(duckdb_prepared_statement prepared_statement, idx_t param_idx);

/*!
Clear the params bind to the prepared statement.
*/
DUCKDB_API duckdb_state duckdb_clear_bindings(duckdb_prepared_statement prepared_statement);

/*!
Binds a bool value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_boolean(duckdb_prepared_statement prepared_statement, idx_t param_idx, bool val);

/*!
Binds an int8_t value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_int8(duckdb_prepared_statement prepared_statement, idx_t param_idx, int8_t val);

/*!
Binds an int16_t value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_int16(duckdb_prepared_statement prepared_statement, idx_t param_idx, int16_t val);

/*!
Binds an int32_t value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_int32(duckdb_prepared_statement prepared_statement, idx_t param_idx, int32_t val);

/*!
Binds an int64_t value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_int64(duckdb_prepared_statement prepared_statement, idx_t param_idx, int64_t val);

/*!
Binds an duckdb_hugeint value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_hugeint(duckdb_prepared_statement prepared_statement, idx_t param_idx,
                                            duckdb_hugeint val);

/*!
Binds an uint8_t value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_uint8(duckdb_prepared_statement prepared_statement, idx_t param_idx, uint8_t val);

/*!
Binds an uint16_t value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_uint16(duckdb_prepared_statement prepared_statement, idx_t param_idx, uint16_t val);

/*!
Binds an uint32_t value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_uint32(duckdb_prepared_statement prepared_statement, idx_t param_idx, uint32_t val);

/*!
Binds an uint64_t value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_uint64(duckdb_prepared_statement prepared_statement, idx_t param_idx, uint64_t val);

/*!
Binds an float value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_float(duckdb_prepared_statement prepared_statement, idx_t param_idx, float val);

/*!
Binds an double value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_double(duckdb_prepared_statement prepared_statement, idx_t param_idx, double val);

/*!
Binds a duckdb_date value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_date(duckdb_prepared_statement prepared_statement, idx_t param_idx,
                                         duckdb_date val);

/*!
Binds a duckdb_time value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_time(duckdb_prepared_statement prepared_statement, idx_t param_idx,
                                         duckdb_time val);

/*!
Binds a duckdb_timestamp value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_timestamp(duckdb_prepared_statement prepared_statement, idx_t param_idx,
                                              duckdb_timestamp val);

/*!
Binds a duckdb_interval value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_interval(duckdb_prepared_statement prepared_statement, idx_t param_idx,
                                             duckdb_interval val);

/*!
Binds a null-terminated varchar value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_varchar(duckdb_prepared_statement prepared_statement, idx_t param_idx,
                                            const char *val);

/*!
Binds a varchar value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_varchar_length(duckdb_prepared_statement prepared_statement, idx_t param_idx,
                                                   const char *val, idx_t length);

/*!
Binds a blob value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_blob(duckdb_prepared_statement prepared_statement, idx_t param_idx,
                                         const void *data, idx_t length);

/*!
Binds a NULL value to the prepared statement at the specified index.
*/
DUCKDB_API duckdb_state duckdb_bind_null(duckdb_prepared_statement prepared_statement, idx_t param_idx);

/*!
Executes the prepared statement with the given bound parameters, and returns a materialized query result.

This method can be called multiple times for each prepared statement, and the parameters can be modified
between calls to this function.

* prepared_statement: The prepared statement to execute.
* out_result: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_execute_prepared(duckdb_prepared_statement prepared_statement,
                                                duckdb_result *out_result);

/*!
Executes the prepared statement with the given bound parameters, and returns an arrow query result.

* prepared_statement: The prepared statement to execute.
* out_result: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_execute_prepared_arrow(duckdb_prepared_statement prepared_statement,
                                                      duckdb_arrow *out_result);

//===--------------------------------------------------------------------===//
// Pending Result Interface
//===--------------------------------------------------------------------===//
/*!
Executes the prepared statement with the given bound parameters, and returns a pending result.
The pending result represents an intermediate structure for a query that is not yet fully executed.
The pending result can be used to incrementally execute a query, returning control to the client between tasks.

Note that after calling `duckdb_pending_prepared`, the pending result should always be destroyed using
`duckdb_destroy_pending`, even if this function returns DuckDBError.

* prepared_statement: The prepared statement to execute.
* out_result: The pending query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_pending_prepared(duckdb_prepared_statement prepared_statement,
                                                duckdb_pending_result *out_result);

/*!
Closes the pending result and de-allocates all memory allocated for the result.

* pending_result: The pending result to destroy.
*/
DUCKDB_API void duckdb_destroy_pending(duckdb_pending_result *pending_result);

/*!
Returns the error message contained within the pending result.

The result of this function must not be freed. It will be cleaned up when `duckdb_destroy_pending` is called.

* result: The pending result to fetch the error from.
* returns: The error of the pending result.
*/
DUCKDB_API const char *duckdb_pending_error(duckdb_pending_result pending_result);

/*!
Executes a single task within the query, returning whether or not the query is ready.

If this returns DUCKDB_PENDING_RESULT_READY, the duckdb_execute_pending function can be called to obtain the result.
If this returns DUCKDB_PENDING_RESULT_NOT_READY, the duckdb_pending_execute_task function should be called again.
If this returns DUCKDB_PENDING_ERROR, an error occurred during execution.

The error message can be obtained by calling duckdb_pending_error on the pending_result.

* pending_result: The pending result to execute a task within..
* returns: The state of the pending result after the execution.
*/
DUCKDB_API duckdb_pending_state duckdb_pending_execute_task(duckdb_pending_result pending_result);

/*!
Fully execute a pending query result, returning the final query result.

If duckdb_pending_execute_task has been called until DUCKDB_PENDING_RESULT_READY was returned, this will return fast.
Otherwise, all remaining tasks must be executed first.

* pending_result: The pending result to execute.
* out_result: The result object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_execute_pending(duckdb_pending_result pending_result, duckdb_result *out_result);

//===--------------------------------------------------------------------===//
// Value Interface
//===--------------------------------------------------------------------===//
/*!
Destroys the value and de-allocates all memory allocated for that type.

* value: The value to destroy.
*/
DUCKDB_API void duckdb_destroy_value(duckdb_value *value);

/*!
Creates a value from a null-terminated string

* value: The null-terminated string
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
*/
DUCKDB_API duckdb_value duckdb_create_varchar(const char *text);

/*!
Creates a value from a string

* value: The text
* length: The length of the text
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
*/
DUCKDB_API duckdb_value duckdb_create_varchar_length(const char *text, idx_t length);

/*!
Creates a value from an int64

* value: The bigint value
* returns: The value. This must be destroyed with `duckdb_destroy_value`.
*/
DUCKDB_API duckdb_value duckdb_create_int64(int64_t val);

/*!
Obtains a string representation of the given value.
The result must be destroyed with `duckdb_free`.

* value: The value
* returns: The string value. This must be destroyed with `duckdb_free`.
*/
DUCKDB_API char *duckdb_get_varchar(duckdb_value value);

/*!
Obtains an int64 of the given value.

* value: The value
* returns: The int64 value, or 0 if no conversion is possible
*/
DUCKDB_API int64_t duckdb_get_int64(duckdb_value value);

//===--------------------------------------------------------------------===//
// Logical Type Interface
//===--------------------------------------------------------------------===//

/*!
Creates a `duckdb_logical_type` from a standard primitive type.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

This should not be used with `DUCKDB_TYPE_DECIMAL`.

* type: The primitive type to create.
* returns: The logical type.
*/
DUCKDB_API duckdb_logical_type duckdb_create_logical_type(duckdb_type type);

/*!
Creates a list type from its child type.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* type: The child type of list type to create.
* returns: The logical type.
*/
DUCKDB_API duckdb_logical_type duckdb_create_list_type(duckdb_logical_type type);

/*!
Creates a map type from its key type and value type.
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* type: The key type and value type of map type to create.
* returns: The logical type.
*/
DUCKDB_API duckdb_logical_type duckdb_create_map_type(duckdb_logical_type key_type, duckdb_logical_type value_type);

/*!
Creates a `duckdb_logical_type` of type decimal with the specified width and scale
The resulting type should be destroyed with `duckdb_destroy_logical_type`.

* width: The width of the decimal type
* scale: The scale of the decimal type
* returns: The logical type.
*/
DUCKDB_API duckdb_logical_type duckdb_create_decimal_type(uint8_t width, uint8_t scale);

/*!
Retrieves the type class of a `duckdb_logical_type`.

* type: The logical type object
* returns: The type id
*/
DUCKDB_API duckdb_type duckdb_get_type_id(duckdb_logical_type type);

/*!
Retrieves the width of a decimal type.

* type: The logical type object
* returns: The width of the decimal type
*/
DUCKDB_API uint8_t duckdb_decimal_width(duckdb_logical_type type);

/*!
Retrieves the scale of a decimal type.

* type: The logical type object
* returns: The scale of the decimal type
*/
DUCKDB_API uint8_t duckdb_decimal_scale(duckdb_logical_type type);

/*!
Retrieves the internal storage type of a decimal type.

* type: The logical type object
* returns: The internal type of the decimal type
*/
DUCKDB_API duckdb_type duckdb_decimal_internal_type(duckdb_logical_type type);

/*!
Retrieves the internal storage type of an enum type.

* type: The logical type object
* returns: The internal type of the enum type
*/
DUCKDB_API duckdb_type duckdb_enum_internal_type(duckdb_logical_type type);

/*!
Retrieves the dictionary size of the enum type

* type: The logical type object
* returns: The dictionary size of the enum type
*/
DUCKDB_API uint32_t duckdb_enum_dictionary_size(duckdb_logical_type type);

/*!
Retrieves the dictionary value at the specified position from the enum.

The result must be freed with `duckdb_free`

* type: The logical type object
* index: The index in the dictionary
* returns: The string value of the enum type. Must be freed with `duckdb_free`.
*/
DUCKDB_API char *duckdb_enum_dictionary_value(duckdb_logical_type type, idx_t index);

/*!
Retrieves the child type of the given list type.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* returns: The child type of the list type. Must be destroyed with `duckdb_destroy_logical_type`.
*/
DUCKDB_API duckdb_logical_type duckdb_list_type_child_type(duckdb_logical_type type);

/*!
Retrieves the key type of the given map type.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* returns: The key type of the map type. Must be destroyed with `duckdb_destroy_logical_type`.
*/
DUCKDB_API duckdb_logical_type duckdb_map_type_key_type(duckdb_logical_type type);

/*!
Retrieves the value type of the given map type.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* returns: The value type of the map type. Must be destroyed with `duckdb_destroy_logical_type`.
*/
DUCKDB_API duckdb_logical_type duckdb_map_type_value_type(duckdb_logical_type type);

/*!
Returns the number of children of a struct type.

* type: The logical type object
* returns: The number of children of a struct type.
*/
DUCKDB_API idx_t duckdb_struct_type_child_count(duckdb_logical_type type);

/*!
Retrieves the name of the struct child.

The result must be freed with `duckdb_free`

* type: The logical type object
* index: The child index
* returns: The name of the struct type. Must be freed with `duckdb_free`.
*/
DUCKDB_API char *duckdb_struct_type_child_name(duckdb_logical_type type, idx_t index);

/*!
Retrieves the child type of the given struct type at the specified index.

The result must be freed with `duckdb_destroy_logical_type`

* type: The logical type object
* index: The child index
* returns: The child type of the struct type. Must be destroyed with `duckdb_destroy_logical_type`.
*/
DUCKDB_API duckdb_logical_type duckdb_struct_type_child_type(duckdb_logical_type type, idx_t index);

/*!
Destroys the logical type and de-allocates all memory allocated for that type.

* type: The logical type to destroy.
*/
DUCKDB_API void duckdb_destroy_logical_type(duckdb_logical_type *type);

//===--------------------------------------------------------------------===//
// Data Chunk Interface
//===--------------------------------------------------------------------===//
/*!
Creates an empty DataChunk with the specified set of types.

* types: An array of types of the data chunk.
* column_count: The number of columns.
* returns: The data chunk.
*/
DUCKDB_API duckdb_data_chunk duckdb_create_data_chunk(duckdb_logical_type *types, idx_t column_count);

/*!
Destroys the data chunk and de-allocates all memory allocated for that chunk.

* chunk: The data chunk to destroy.
*/
DUCKDB_API void duckdb_destroy_data_chunk(duckdb_data_chunk *chunk);

/*!
Resets a data chunk, clearing the validity masks and setting the cardinality of the data chunk to 0.

* chunk: The data chunk to reset.
*/
DUCKDB_API void duckdb_data_chunk_reset(duckdb_data_chunk chunk);

/*!
Retrieves the number of columns in a data chunk.

* chunk: The data chunk to get the data from
* returns: The number of columns in the data chunk
*/
DUCKDB_API idx_t duckdb_data_chunk_get_column_count(duckdb_data_chunk chunk);

/*!
Retrieves the vector at the specified column index in the data chunk.

The pointer to the vector is valid for as long as the chunk is alive.
It does NOT need to be destroyed.

* chunk: The data chunk to get the data from
* returns: The vector
*/
DUCKDB_API duckdb_vector duckdb_data_chunk_get_vector(duckdb_data_chunk chunk, idx_t col_idx);

/*!
Retrieves the current number of tuples in a data chunk.

* chunk: The data chunk to get the data from
* returns: The number of tuples in the data chunk
*/
DUCKDB_API idx_t duckdb_data_chunk_get_size(duckdb_data_chunk chunk);

/*!
Sets the current number of tuples in a data chunk.

* chunk: The data chunk to set the size in
* size: The number of tuples in the data chunk
*/
DUCKDB_API void duckdb_data_chunk_set_size(duckdb_data_chunk chunk, idx_t size);

//===--------------------------------------------------------------------===//
// Vector Interface
//===--------------------------------------------------------------------===//
/*!
Retrieves the column type of the specified vector.

The result must be destroyed with `duckdb_destroy_logical_type`.

* vector: The vector get the data from
* returns: The type of the vector
*/
DUCKDB_API duckdb_logical_type duckdb_vector_get_column_type(duckdb_vector vector);

/*!
Retrieves the data pointer of the vector.

The data pointer can be used to read or write values from the vector.
How to read or write values depends on the type of the vector.

* vector: The vector to get the data from
* returns: The data pointer
*/
DUCKDB_API void *duckdb_vector_get_data(duckdb_vector vector);

/*!
Retrieves the validity mask pointer of the specified vector.

If all values are valid, this function MIGHT return NULL!

The validity mask is a bitset that signifies null-ness within the data chunk.
It is a series of uint64_t values, where each uint64_t value contains validity for 64 tuples.
The bit is set to 1 if the value is valid (i.e. not NULL) or 0 if the value is invalid (i.e. NULL).

Validity of a specific value can be obtained like this:

idx_t entry_idx = row_idx / 64;
idx_t idx_in_entry = row_idx % 64;
bool is_valid = validity_mask[entry_idx] & (1 << idx_in_entry);

Alternatively, the (slower) duckdb_validity_row_is_valid function can be used.

* vector: The vector to get the data from
* returns: The pointer to the validity mask, or NULL if no validity mask is present
*/
DUCKDB_API uint64_t *duckdb_vector_get_validity(duckdb_vector vector);

/*!
Ensures the validity mask is writable by allocating it.

After this function is called, `duckdb_vector_get_validity` will ALWAYS return non-NULL.
This allows null values to be written to the vector, regardless of whether a validity mask was present before.

* vector: The vector to alter
*/
DUCKDB_API void duckdb_vector_ensure_validity_writable(duckdb_vector vector);

/*!
Assigns a string element in the vector at the specified location.

* vector: The vector to alter
* index: The row position in the vector to assign the string to
* str: The null-terminated string
*/
DUCKDB_API void duckdb_vector_assign_string_element(duckdb_vector vector, idx_t index, const char *str);

/*!
Assigns a string element in the vector at the specified location.

* vector: The vector to alter
* index: The row position in the vector to assign the string to
* str: The string
* str_len: The length of the string (in bytes)
*/
DUCKDB_API void duckdb_vector_assign_string_element_len(duckdb_vector vector, idx_t index, const char *str,
                                                        idx_t str_len);

/*!
Retrieves the child vector of a list vector.

The resulting vector is valid as long as the parent vector is valid.

* vector: The vector
* returns: The child vector
*/
DUCKDB_API duckdb_vector duckdb_list_vector_get_child(duckdb_vector vector);

/*!
Returns the size of the child vector of the list

* vector: The vector
* returns: The size of the child list
*/
DUCKDB_API idx_t duckdb_list_vector_get_size(duckdb_vector vector);

/*!
Retrieves the child vector of a struct vector.

The resulting vector is valid as long as the parent vector is valid.

* vector: The vector
* index: The child index
* returns: The child vector
*/
DUCKDB_API duckdb_vector duckdb_struct_vector_get_child(duckdb_vector vector, idx_t index);

//===--------------------------------------------------------------------===//
// Validity Mask Functions
//===--------------------------------------------------------------------===//
/*!
Returns whether or not a row is valid (i.e. not NULL) in the given validity mask.

* validity: The validity mask, as obtained through `duckdb_data_chunk_get_validity`
* row: The row index
* returns: true if the row is valid, false otherwise
*/
DUCKDB_API bool duckdb_validity_row_is_valid(uint64_t *validity, idx_t row);

/*!
In a validity mask, sets a specific row to either valid or invalid.

Note that `duckdb_data_chunk_ensure_validity_writable` should be called before calling `duckdb_data_chunk_get_validity`,
to ensure that there is a validity mask to write to.

* validity: The validity mask, as obtained through `duckdb_data_chunk_get_validity`.
* row: The row index
* valid: Whether or not to set the row to valid, or invalid
*/
DUCKDB_API void duckdb_validity_set_row_validity(uint64_t *validity, idx_t row, bool valid);

/*!
In a validity mask, sets a specific row to invalid.

Equivalent to `duckdb_validity_set_row_validity` with valid set to false.

* validity: The validity mask
* row: The row index
*/
DUCKDB_API void duckdb_validity_set_row_invalid(uint64_t *validity, idx_t row);

/*!
In a validity mask, sets a specific row to valid.

Equivalent to `duckdb_validity_set_row_validity` with valid set to true.

* validity: The validity mask
* row: The row index
*/
DUCKDB_API void duckdb_validity_set_row_valid(uint64_t *validity, idx_t row);

//===--------------------------------------------------------------------===//
// Table Functions
//===--------------------------------------------------------------------===//
typedef void *duckdb_table_function;
typedef void *duckdb_bind_info;
typedef void *duckdb_init_info;
typedef void *duckdb_function_info;

typedef void (*duckdb_table_function_bind_t)(duckdb_bind_info info);
typedef void (*duckdb_table_function_init_t)(duckdb_init_info info);
typedef void (*duckdb_table_function_t)(duckdb_function_info info, duckdb_data_chunk output);
typedef void (*duckdb_delete_callback_t)(void *data);

/*!
Creates a new empty table function.

The return value should be destroyed with `duckdb_destroy_table_function`.

* returns: The table function object.
*/
DUCKDB_API duckdb_table_function duckdb_create_table_function();

/*!
Destroys the given table function object.

* table_function: The table function to destroy
*/
DUCKDB_API void duckdb_destroy_table_function(duckdb_table_function *table_function);

/*!
Sets the name of the given table function.

* table_function: The table function
* name: The name of the table function
*/
DUCKDB_API void duckdb_table_function_set_name(duckdb_table_function table_function, const char *name);

/*!
Adds a parameter to the table function.

* table_function: The table function
* type: The type of the parameter to add.
*/
DUCKDB_API void duckdb_table_function_add_parameter(duckdb_table_function table_function, duckdb_logical_type type);

/*!
Assigns extra information to the table function that can be fetched during binding, etc.

* table_function: The table function
* extra_info: The extra information
* destroy: The callback that will be called to destroy the bind data (if any)
*/
DUCKDB_API void duckdb_table_function_set_extra_info(duckdb_table_function table_function, void *extra_info,
                                                     duckdb_delete_callback_t destroy);

/*!
Sets the bind function of the table function

* table_function: The table function
* bind: The bind function
*/
DUCKDB_API void duckdb_table_function_set_bind(duckdb_table_function table_function, duckdb_table_function_bind_t bind);

/*!
Sets the init function of the table function

* table_function: The table function
* init: The init function
*/
DUCKDB_API void duckdb_table_function_set_init(duckdb_table_function table_function, duckdb_table_function_init_t init);

/*!
Sets the thread-local init function of the table function

* table_function: The table function
* init: The init function
*/
DUCKDB_API void duckdb_table_function_set_local_init(duckdb_table_function table_function,
                                                     duckdb_table_function_init_t init);

/*!
Sets the main function of the table function

* table_function: The table function
* function: The function
*/
DUCKDB_API void duckdb_table_function_set_function(duckdb_table_function table_function,
                                                   duckdb_table_function_t function);

/*!
Sets whether or not the given table function supports projection pushdown.

If this is set to true, the system will provide a list of all required columns in the `init` stage through
the `duckdb_init_get_column_count` and `duckdb_init_get_column_index` functions.
If this is set to false (the default), the system will expect all columns to be projected.

* table_function: The table function
* pushdown: True if the table function supports projection pushdown, false otherwise.
*/
DUCKDB_API void duckdb_table_function_supports_projection_pushdown(duckdb_table_function table_function, bool pushdown);

/*!
Register the table function object within the given connection.

The function requires at least a name, a bind function, an init function and a main function.

If the function is incomplete or a function with this name already exists DuckDBError is returned.

* con: The connection to register it in.
* function: The function pointer
* returns: Whether or not the registration was successful.
*/
DUCKDB_API duckdb_state duckdb_register_table_function(duckdb_connection con, duckdb_table_function function);

//===--------------------------------------------------------------------===//
// Table Function Bind
//===--------------------------------------------------------------------===//
/*!
Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`

* info: The info object
* returns: The extra info
*/
DUCKDB_API void *duckdb_bind_get_extra_info(duckdb_bind_info info);

/*!
Adds a result column to the output of the table function.

* info: The info object
* name: The name of the column
* type: The logical type of the column
*/
DUCKDB_API void duckdb_bind_add_result_column(duckdb_bind_info info, const char *name, duckdb_logical_type type);

/*!
Retrieves the number of regular (non-named) parameters to the function.

* info: The info object
* returns: The number of parameters
*/
DUCKDB_API idx_t duckdb_bind_get_parameter_count(duckdb_bind_info info);

/*!
Retrieves the parameter at the given index.

The result must be destroyed with `duckdb_destroy_value`.

* info: The info object
* index: The index of the parameter to get
* returns: The value of the parameter. Must be destroyed with `duckdb_destroy_value`.
*/
DUCKDB_API duckdb_value duckdb_bind_get_parameter(duckdb_bind_info info, idx_t index);

/*!
Sets the user-provided bind data in the bind object. This object can be retrieved again during execution.

* info: The info object
* extra_data: The bind data object.
* destroy: The callback that will be called to destroy the bind data (if any)
*/
DUCKDB_API void duckdb_bind_set_bind_data(duckdb_bind_info info, void *bind_data, duckdb_delete_callback_t destroy);

/*!
Sets the cardinality estimate for the table function, used for optimization.

* info: The bind data object.
* is_exact: Whether or not the cardinality estimate is exact, or an approximation
*/
DUCKDB_API void duckdb_bind_set_cardinality(duckdb_bind_info info, idx_t cardinality, bool is_exact);

/*!
Report that an error has occurred while calling bind.

* info: The info object
* error: The error message
*/
DUCKDB_API void duckdb_bind_set_error(duckdb_bind_info info, const char *error);

//===--------------------------------------------------------------------===//
// Table Function Init
//===--------------------------------------------------------------------===//

/*!
Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`

* info: The info object
* returns: The extra info
*/
DUCKDB_API void *duckdb_init_get_extra_info(duckdb_init_info info);

/*!
Gets the bind data set by `duckdb_bind_set_bind_data` during the bind.

Note that the bind data should be considered as read-only.
For tracking state, use the init data instead.

* info: The info object
* returns: The bind data object
*/
DUCKDB_API void *duckdb_init_get_bind_data(duckdb_init_info info);

/*!
Sets the user-provided init data in the init object. This object can be retrieved again during execution.

* info: The info object
* extra_data: The init data object.
* destroy: The callback that will be called to destroy the init data (if any)
*/
DUCKDB_API void duckdb_init_set_init_data(duckdb_init_info info, void *init_data, duckdb_delete_callback_t destroy);

/*!
Returns the number of projected columns.

This function must be used if projection pushdown is enabled to figure out which columns to emit.

* info: The info object
* returns: The number of projected columns.
*/
DUCKDB_API idx_t duckdb_init_get_column_count(duckdb_init_info info);

/*!
Returns the column index of the projected column at the specified position.

This function must be used if projection pushdown is enabled to figure out which columns to emit.

* info: The info object
* column_index: The index at which to get the projected column index, from 0..duckdb_init_get_column_count(info)
* returns: The column index of the projected column.
*/
DUCKDB_API idx_t duckdb_init_get_column_index(duckdb_init_info info, idx_t column_index);

/*!
Sets how many threads can process this table function in parallel (default: 1)

* info: The info object
* max_threads: The maximum amount of threads that can process this table function
*/
DUCKDB_API void duckdb_init_set_max_threads(duckdb_init_info info, idx_t max_threads);

/*!
Report that an error has occurred while calling init.

* info: The info object
* error: The error message
*/
DUCKDB_API void duckdb_init_set_error(duckdb_init_info info, const char *error);

//===--------------------------------------------------------------------===//
// Table Function
//===--------------------------------------------------------------------===//

/*!
Retrieves the extra info of the function as set in `duckdb_table_function_set_extra_info`

* info: The info object
* returns: The extra info
*/
DUCKDB_API void *duckdb_function_get_extra_info(duckdb_function_info info);
/*!
Gets the bind data set by `duckdb_bind_set_bind_data` during the bind.

Note that the bind data should be considered as read-only.
For tracking state, use the init data instead.

* info: The info object
* returns: The bind data object
*/
DUCKDB_API void *duckdb_function_get_bind_data(duckdb_function_info info);

/*!
Gets the init data set by `duckdb_init_set_init_data` during the init.

* info: The info object
* returns: The init data object
*/
DUCKDB_API void *duckdb_function_get_init_data(duckdb_function_info info);

/*!
Gets the thread-local init data set by `duckdb_init_set_init_data` during the local_init.

* info: The info object
* returns: The init data object
*/
DUCKDB_API void *duckdb_function_get_local_init_data(duckdb_function_info info);

/*!
Report that an error has occurred while executing the function.

* info: The info object
* error: The error message
*/
DUCKDB_API void duckdb_function_set_error(duckdb_function_info info, const char *error);

//===--------------------------------------------------------------------===//
// Replacement Scans
//===--------------------------------------------------------------------===//
typedef void *duckdb_replacement_scan_info;

typedef void (*duckdb_replacement_callback_t)(duckdb_replacement_scan_info info, const char *table_name, void *data);

/*!
Add a replacement scan definition to the specified database

* db: The database object to add the replacement scan to
* replacement: The replacement scan callback
* extra_data: Extra data that is passed back into the specified callback
* delete_callback: The delete callback to call on the extra data, if any
*/
DUCKDB_API void duckdb_add_replacement_scan(duckdb_database db, duckdb_replacement_callback_t replacement,
                                            void *extra_data, duckdb_delete_callback_t delete_callback);

/*!
Sets the replacement function name to use. If this function is called in the replacement callback,
 the replacement scan is performed. If it is not called, the replacement callback is not performed.

* info: The info object
* function_name: The function name to substitute.
*/
DUCKDB_API void duckdb_replacement_scan_set_function_name(duckdb_replacement_scan_info info, const char *function_name);

/*!
Adds a parameter to the replacement scan function.

* info: The info object
* parameter: The parameter to add.
*/
DUCKDB_API void duckdb_replacement_scan_add_parameter(duckdb_replacement_scan_info info, duckdb_value parameter);

//===--------------------------------------------------------------------===//
// Appender
//===--------------------------------------------------------------------===//

// Appenders are the most efficient way of loading data into DuckDB from within the C interface, and are recommended for
// fast data loading. The appender is much faster than using prepared statements or individual `INSERT INTO` statements.

// Appends are made in row-wise format. For every column, a `duckdb_append_[type]` call should be made, after which
// the row should be finished by calling `duckdb_appender_end_row`. After all rows have been appended,
// `duckdb_appender_destroy` should be used to finalize the appender and clean up the resulting memory.

// Note that `duckdb_appender_destroy` should always be called on the resulting appender, even if the function returns
// `DuckDBError`.

/*!
Creates an appender object.

* connection: The connection context to create the appender in.
* schema: The schema of the table to append to, or `nullptr` for the default schema.
* table: The table name to append to.
* out_appender: The resulting appender object.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_appender_create(duckdb_connection connection, const char *schema, const char *table,
                                               duckdb_appender *out_appender);

/*!
Returns the error message associated with the given appender.
If the appender has no error message, this returns `nullptr` instead.

The error message should not be freed. It will be de-allocated when `duckdb_appender_destroy` is called.

* appender: The appender to get the error from.
* returns: The error message, or `nullptr` if there is none.
*/
DUCKDB_API const char *duckdb_appender_error(duckdb_appender appender);

/*!
Flush the appender to the table, forcing the cache of the appender to be cleared and the data to be appended to the
base table.

This should generally not be used unless you know what you are doing. Instead, call `duckdb_appender_destroy` when you
are done with the appender.

* appender: The appender to flush.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_appender_flush(duckdb_appender appender);

/*!
Close the appender, flushing all intermediate state in the appender to the table and closing it for further appends.

This is generally not necessary. Call `duckdb_appender_destroy` instead.

* appender: The appender to flush and close.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_appender_close(duckdb_appender appender);

/*!
Close the appender and destroy it. Flushing all intermediate state in the appender to the table, and de-allocating
all memory associated with the appender.

* appender: The appender to flush, close and destroy.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_appender_destroy(duckdb_appender *appender);

/*!
A nop function, provided for backwards compatibility reasons. Does nothing. Only `duckdb_appender_end_row` is required.
*/
DUCKDB_API duckdb_state duckdb_appender_begin_row(duckdb_appender appender);

/*!
Finish the current row of appends. After end_row is called, the next row can be appended.

* appender: The appender.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_appender_end_row(duckdb_appender appender);

/*!
Append a bool value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_bool(duckdb_appender appender, bool value);

/*!
Append an int8_t value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_int8(duckdb_appender appender, int8_t value);
/*!
Append an int16_t value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_int16(duckdb_appender appender, int16_t value);
/*!
Append an int32_t value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_int32(duckdb_appender appender, int32_t value);
/*!
Append an int64_t value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_int64(duckdb_appender appender, int64_t value);
/*!
Append a duckdb_hugeint value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_hugeint(duckdb_appender appender, duckdb_hugeint value);

/*!
Append a uint8_t value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_uint8(duckdb_appender appender, uint8_t value);
/*!
Append a uint16_t value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_uint16(duckdb_appender appender, uint16_t value);
/*!
Append a uint32_t value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_uint32(duckdb_appender appender, uint32_t value);
/*!
Append a uint64_t value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_uint64(duckdb_appender appender, uint64_t value);

/*!
Append a float value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_float(duckdb_appender appender, float value);
/*!
Append a double value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_double(duckdb_appender appender, double value);

/*!
Append a duckdb_date value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_date(duckdb_appender appender, duckdb_date value);
/*!
Append a duckdb_time value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_time(duckdb_appender appender, duckdb_time value);
/*!
Append a duckdb_timestamp value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_timestamp(duckdb_appender appender, duckdb_timestamp value);
/*!
Append a duckdb_interval value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_interval(duckdb_appender appender, duckdb_interval value);

/*!
Append a varchar value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_varchar(duckdb_appender appender, const char *val);
/*!
Append a varchar value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_varchar_length(duckdb_appender appender, const char *val, idx_t length);
/*!
Append a blob value to the appender.
*/
DUCKDB_API duckdb_state duckdb_append_blob(duckdb_appender appender, const void *data, idx_t length);
/*!
Append a NULL value to the appender (of any type).
*/
DUCKDB_API duckdb_state duckdb_append_null(duckdb_appender appender);

/*!
Appends a pre-filled data chunk to the specified appender.

The types of the data chunk must exactly match the types of the table, no casting is performed.
If the types do not match or the appender is in an invalid state, DuckDBError is returned.
If the append is successful, DuckDBSuccess is returned.

* appender: The appender to append to.
* chunk: The data chunk to append.
* returns: The return state.
*/
DUCKDB_API duckdb_state duckdb_append_data_chunk(duckdb_appender appender, duckdb_data_chunk chunk);

//===--------------------------------------------------------------------===//
// Arrow Interface
//===--------------------------------------------------------------------===//
/*!
Executes a SQL query within a connection and stores the full (materialized) result in an arrow structure.
If the query fails to execute, DuckDBError is returned and the error message can be retrieved by calling
`duckdb_query_arrow_error`.

Note that after running `duckdb_query_arrow`, `duckdb_destroy_arrow` must be called on the result object even if the
query fails, otherwise the error stored within the result will not be freed correctly.

* connection: The connection to perform the query in.
* query: The SQL query to run.
* out_result: The query result.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_query_arrow(duckdb_connection connection, const char *query, duckdb_arrow *out_result);

/*!
Fetch the internal arrow schema from the arrow result.

* result: The result to fetch the schema from.
* out_schema: The output schema.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_query_arrow_schema(duckdb_arrow result, duckdb_arrow_schema *out_schema);

/*!
Fetch an internal arrow array from the arrow result.

This function can be called multiple time to get next chunks, which will free the previous out_array.
So consume the out_array before calling this function again.

* result: The result to fetch the array from.
* out_array: The output array.
* returns: `DuckDBSuccess` on success or `DuckDBError` on failure.
*/
DUCKDB_API duckdb_state duckdb_query_arrow_array(duckdb_arrow result, duckdb_arrow_array *out_array);

/*!
Returns the number of columns present in a the arrow result object.

* result: The result object.
* returns: The number of columns present in the result object.
*/
DUCKDB_API idx_t duckdb_arrow_column_count(duckdb_arrow result);

/*!
Returns the number of rows present in a the arrow result object.

* result: The result object.
* returns: The number of rows present in the result object.
*/
DUCKDB_API idx_t duckdb_arrow_row_count(duckdb_arrow result);

/*!
Returns the number of rows changed by the query stored in the arrow result. This is relevant only for
INSERT/UPDATE/DELETE queries. For other queries the rows_changed will be 0.

* result: The result object.
* returns: The number of rows changed.
*/
DUCKDB_API idx_t duckdb_arrow_rows_changed(duckdb_arrow result);

/*!
Returns the error message contained within the result. The error is only set if `duckdb_query_arrow` returns
`DuckDBError`.

The error message should not be freed. It will be de-allocated when `duckdb_destroy_arrow` is called.

* result: The result object to fetch the nullmask from.
* returns: The error of the result.
*/
DUCKDB_API const char *duckdb_query_arrow_error(duckdb_arrow result);

/*!
Closes the result and de-allocates all memory allocated for the arrow result.

* result: The result to destroy.
*/
DUCKDB_API void duckdb_destroy_arrow(duckdb_arrow *result);

//===--------------------------------------------------------------------===//
// Threading Information
//===--------------------------------------------------------------------===//
typedef void *duckdb_task_state;

/*!
Execute DuckDB tasks on this thread.

Will return after `max_tasks` have been executed, or if there are no more tasks present.

* database: The database object to execute tasks for
* max_tasks: The maximum amount of tasks to execute
*/
DUCKDB_API void duckdb_execute_tasks(duckdb_database database, idx_t max_tasks);

/*!
Creates a task state that can be used with duckdb_execute_tasks_state to execute tasks until
 duckdb_finish_execution is called on the state.

duckdb_destroy_state should be called on the result in order to free memory.

* database: The database object to create the task state for
* returns: The task state that can be used with duckdb_execute_tasks_state.
*/
DUCKDB_API duckdb_task_state duckdb_create_task_state(duckdb_database database);

/*!
Execute DuckDB tasks on this thread.

The thread will keep on executing tasks forever, until duckdb_finish_execution is called on the state.
Multiple threads can share the same duckdb_task_state.

* state: The task state of the executor
*/
DUCKDB_API void duckdb_execute_tasks_state(duckdb_task_state state);

/*!
Execute DuckDB tasks on this thread.

The thread will keep on executing tasks until either duckdb_finish_execution is called on the state,
max_tasks tasks have been executed or there are no more tasks to be executed.

Multiple threads can share the same duckdb_task_state.

* state: The task state of the executor
* max_tasks: The maximum amount of tasks to execute
* returns: The amount of tasks that have actually been executed
*/
DUCKDB_API idx_t duckdb_execute_n_tasks_state(duckdb_task_state state, idx_t max_tasks);

/*!
Finish execution on a specific task.

* state: The task state to finish execution
*/
DUCKDB_API void duckdb_finish_execution(duckdb_task_state state);

/*!
Check if the provided duckdb_task_state has finished execution

* state: The task state to inspect
* returns: Whether or not duckdb_finish_execution has been called on the task state
*/
DUCKDB_API bool duckdb_task_state_is_finished(duckdb_task_state state);

/*!
Destroys the task state returned from duckdb_create_task_state.

Note that this should not be called while there is an active duckdb_execute_tasks_state running
on the task state.

* state: The task state to clean up
*/
DUCKDB_API void duckdb_destroy_task_state(duckdb_task_state state);

#ifdef __cplusplus
}
#endif



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/profiler.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

//! The profiler can be used to measure elapsed time
template <typename T>
class BaseProfiler {
public:
	//! Starts the timer
	void Start() {
		finished = false;
		start = Tick();
	}
	//! Finishes timing
	void End() {
		end = Tick();
		finished = true;
	}

	//! Returns the elapsed time in seconds. If End() has been called, returns
	//! the total elapsed time. Otherwise returns how far along the timer is
	//! right now.
	double Elapsed() const {
		auto _end = finished ? end : Tick();
		return std::chrono::duration_cast<std::chrono::duration<double>>(_end - start).count();
	}

private:
	time_point<T> Tick() const {
		return T::now();
	}
	time_point<T> start;
	time_point<T> end;
	bool finished = false;
};

using Profiler = BaseProfiler<system_clock>;

} // namespace duckdb


namespace duckdb {

class ProgressBar {
public:
	explicit ProgressBar(Executor &executor, idx_t show_progress_after, bool print_progress);

	//! Starts the thread
	void Start();
	//! Updates the progress bar and prints it to the screen
	void Update(bool final);
	//! Gets current percentage
	double GetCurrentPercentage();

private:
	const string PROGRESS_BAR_STRING = "============================================================";
	static constexpr const idx_t PROGRESS_BAR_WIDTH = 60;

private:
	//! The executor
	Executor &executor;
	//! The profiler used to measure the time since the progress bar was started
	Profiler profiler;
	//! The time in ms after which to start displaying the progress bar
	idx_t show_progress_after;
	//! The current progress percentage
	double current_percentage;
	//! Whether or not we print the progress bar
	bool print_progress;
	//! Whether or not profiling is supported for the current query
	bool supported = true;
};
} // namespace duckdb




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/stream_query_result.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

class ClientContext;
class ClientContextLock;
class Executor;
class MaterializedQueryResult;
class PreparedStatementData;

class StreamQueryResult : public QueryResult {
	friend class ClientContext;

public:
	//! Create a successful StreamQueryResult. StreamQueryResults should always be successful initially (it makes no
	//! sense to stream an error).
	DUCKDB_API StreamQueryResult(StatementType statement_type, StatementProperties properties,
	                             shared_ptr<ClientContext> context, vector<LogicalType> types, vector<string> names);
	DUCKDB_API ~StreamQueryResult() override;

public:
	//! Fetches a DataChunk from the query result.
	DUCKDB_API unique_ptr<DataChunk> FetchRaw() override;
	//! Converts the QueryResult to a string
	DUCKDB_API string ToString() override;
	//! Materializes the query result and turns it into a materialized query result
	DUCKDB_API unique_ptr<MaterializedQueryResult> Materialize();

	DUCKDB_API bool IsOpen();

	//! Closes the StreamQueryResult
	DUCKDB_API void Close();

	//! The client context this StreamQueryResult belongs to
	shared_ptr<ClientContext> context;

private:
	unique_ptr<ClientContextLock> LockContext();
	void CheckExecutableInternal(ClientContextLock &lock);
	bool IsOpenInternal(ClientContextLock &lock);
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/table_description.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

struct TableDescription {
	//! The schema of the table
	string schema;
	//! The table name of the table
	string table;
	//! The columns of the table
	vector<ColumnDefinition> columns;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/transaction/transaction_context.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

class ClientContext;
class Transaction;
class TransactionManager;

//! The transaction context keeps track of all the information relating to the
//! current transaction
class TransactionContext {
public:
	TransactionContext(TransactionManager &transaction_manager, ClientContext &context)
	    : transaction_manager(transaction_manager), context(context), auto_commit(true), current_transaction(nullptr) {
	}
	~TransactionContext();

	Transaction &ActiveTransaction() {
		D_ASSERT(current_transaction);
		return *current_transaction;
	}

	bool HasActiveTransaction() {
		return !!current_transaction;
	}

	void RecordQuery(string query);
	void BeginTransaction();
	void Commit();
	void Rollback();
	void ClearTransaction();

	void SetAutoCommit(bool value);
	bool IsAutoCommit() {
		return auto_commit;
	}

private:
	TransactionManager &transaction_manager;
	ClientContext &context;
	bool auto_commit;

	Transaction *current_transaction;

	TransactionContext(const TransactionContext &) = delete;
};

} // namespace duckdb



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/client_config.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/output_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class ExplainOutputType : uint8_t { ALL = 0, OPTIMIZED_ONLY = 1, PHYSICAL_ONLY = 2 };

} // namespace duckdb




namespace duckdb {
class ClientContext;
class PhysicalResultCollector;
class PreparedStatementData;

typedef std::function<unique_ptr<PhysicalResultCollector>(ClientContext &context, PreparedStatementData &data)>
    get_result_collector_t;

struct ClientConfig {
	//! The home directory used by the system (if any)
	string home_directory;
	//! If the query profiler is enabled or not.
	bool enable_profiler = false;
	//! If detailed query profiling is enabled
	bool enable_detailed_profiling = false;
	//! The format to print query profiling information in (default: query_tree), if enabled.
	ProfilerPrintFormat profiler_print_format = ProfilerPrintFormat::QUERY_TREE;
	//! The file to save query profiling information to, instead of printing it to the console
	//! (empty = print to console)
	string profiler_save_location;

	//! Allows suppressing profiler output, even if enabled. We turn on the profiler on all test runs but don't want
	//! to output anything
	bool emit_profiler_output = true;

	//! If the progress bar is enabled or not.
	bool enable_progress_bar = false;
	//! If the print of the progress bar is enabled
	bool print_progress_bar = true;
	//! The wait time before showing the progress bar
	int wait_time = 2000;

	//! Preserve identifier case while parsing.
	//! If false, all unquoted identifiers are lower-cased (e.g. "MyTable" -> "mytable").
	bool preserve_identifier_case = true;
	//! The maximum expression depth limit in the parser
	idx_t max_expression_depth = 1000;

	//! Whether or not aggressive query verification is enabled
	bool query_verification_enabled = false;
	//! Whether or not verification of external operators is enabled, used for testing
	bool verify_external = false;
	//! Whether or not we should verify the serializer
	bool verify_serializer = false;
	//! Enable the running of optimizers
	bool enable_optimizer = true;
	//! Force parallelism of small tables, used for testing
	bool verify_parallelism = false;
	//! Force index join independent of table cardinality, used for testing
	bool force_index_join = false;
	//! Force out-of-core computation for operators that support it, used for testing
	bool force_external = false;
	//! Force disable cross product generation when hyper graph isn't connected, used for testing
	bool force_no_cross_product = false;
	//! Maximum bits allowed for using a perfect hash table (i.e. the perfect HT can hold up to 2^perfect_ht_threshold
	//! elements)
	idx_t perfect_ht_threshold = 12;

	//! The explain output type used when none is specified (default: PHYSICAL_ONLY)
	ExplainOutputType explain_output_type = ExplainOutputType::PHYSICAL_ONLY;

	//! Generic options
	case_insensitive_map_t<Value> set_variables;

	//! Function that is used to create the result collector for a materialized result
	//! Defaults to PhysicalMaterializedCollector
	get_result_collector_t result_collector = nullptr;

public:
	static ClientConfig &GetConfig(ClientContext &context);
	static const ClientConfig &GetConfig(const ClientContext &context);

	static string ExtractTimezoneFromConfig(ClientConfig &config);

	string ExtractTimezone() const;

	bool AnyVerification() {
		return query_verification_enabled || verify_external || verify_serializer;
	}
};

} // namespace duckdb




namespace duckdb {
class Appender;
class Catalog;
class CatalogSearchPath;
class ColumnDataCollection;
class DatabaseInstance;
class FileOpener;
class LogicalOperator;
class PreparedStatementData;
class Relation;
class BufferedFileWriter;
class QueryProfiler;
class ClientContextLock;
struct CreateScalarFunctionInfo;
class ScalarFunctionCatalogEntry;
struct ActiveQueryContext;
struct ParserOptions;
struct ClientData;

struct PendingQueryParameters {
	//! Prepared statement parameters (if any)
	vector<Value> *parameters = nullptr;
	//! Whether or not a stream result should be allowed
	bool allow_stream_result = false;
};

//! The ClientContext holds information relevant to the current client session
//! during execution
class ClientContext : public std::enable_shared_from_this<ClientContext> {
	friend class PendingQueryResult;
	friend class StreamQueryResult;
	friend class TransactionManager;

public:
	DUCKDB_API explicit ClientContext(shared_ptr<DatabaseInstance> db);
	DUCKDB_API ~ClientContext();

	//! The database that this client is connected to
	shared_ptr<DatabaseInstance> db;
	//! Data for the currently running transaction
	TransactionContext transaction;
	//! Whether or not the query is interrupted
	atomic<bool> interrupted;
	//! External Objects (e.g., Python objects) that views depend of
	unordered_map<string, vector<shared_ptr<ExternalDependency>>> external_dependencies;

	//! The client configuration
	ClientConfig config;
	//! The set of client-specific data
	unique_ptr<ClientData> client_data;

public:
	DUCKDB_API Transaction &ActiveTransaction() {
		return transaction.ActiveTransaction();
	}

	//! Interrupt execution of a query
	DUCKDB_API void Interrupt();
	//! Enable query profiling
	DUCKDB_API void EnableProfiling();
	//! Disable query profiling
	DUCKDB_API void DisableProfiling();

	//! Issue a query, returning a QueryResult. The QueryResult can be either a StreamQueryResult or a
	//! MaterializedQueryResult. The StreamQueryResult will only be returned in the case of a successful SELECT
	//! statement.
	DUCKDB_API unique_ptr<QueryResult> Query(const string &query, bool allow_stream_result);
	DUCKDB_API unique_ptr<QueryResult> Query(unique_ptr<SQLStatement> statement, bool allow_stream_result);

	//! Issues a query to the database and returns a Pending Query Result. Note that "query" may only contain
	//! a single statement.
	DUCKDB_API unique_ptr<PendingQueryResult> PendingQuery(const string &query, bool allow_stream_result);
	//! Issues a query to the database and returns a Pending Query Result
	DUCKDB_API unique_ptr<PendingQueryResult> PendingQuery(unique_ptr<SQLStatement> statement,
	                                                       bool allow_stream_result);

	//! Destroy the client context
	DUCKDB_API void Destroy();

	//! Get the table info of a specific table, or nullptr if it cannot be found
	DUCKDB_API unique_ptr<TableDescription> TableInfo(const string &schema_name, const string &table_name);
	//! Appends a DataChunk to the specified table. Returns whether or not the append was successful.
	DUCKDB_API void Append(TableDescription &description, ColumnDataCollection &collection);
	//! Try to bind a relation in the current client context; either throws an exception or fills the result_columns
	//! list with the set of returned columns
	DUCKDB_API void TryBindRelation(Relation &relation, vector<ColumnDefinition> &result_columns);

	//! Execute a relation
	DUCKDB_API unique_ptr<QueryResult> Execute(const shared_ptr<Relation> &relation);

	//! Prepare a query
	DUCKDB_API unique_ptr<PreparedStatement> Prepare(const string &query);
	//! Directly prepare a SQL statement
	DUCKDB_API unique_ptr<PreparedStatement> Prepare(unique_ptr<SQLStatement> statement);

	//! Create a pending query result from a prepared statement with the given name and set of parameters
	//! It is possible that the prepared statement will be re-bound. This will generally happen if the catalog is
	//! modified in between the prepared statement being bound and the prepared statement being run.
	DUCKDB_API unique_ptr<PendingQueryResult>
	PendingQuery(const string &query, shared_ptr<PreparedStatementData> &prepared, PendingQueryParameters parameters);

	//! Execute a prepared statement with the given name and set of parameters
	//! It is possible that the prepared statement will be re-bound. This will generally happen if the catalog is
	//! modified in between the prepared statement being bound and the prepared statement being run.
	DUCKDB_API unique_ptr<QueryResult> Execute(const string &query, shared_ptr<PreparedStatementData> &prepared,
	                                           vector<Value> &values, bool allow_stream_result = true);
	DUCKDB_API unique_ptr<QueryResult> Execute(const string &query, shared_ptr<PreparedStatementData> &prepared,
	                                           PendingQueryParameters parameters);

	//! Gets current percentage of the query's progress, returns 0 in case the progress bar is disabled.
	DUCKDB_API double GetProgress();

	//! Register function in the temporary schema
	DUCKDB_API void RegisterFunction(CreateFunctionInfo *info);

	//! Parse statements from a query
	DUCKDB_API vector<unique_ptr<SQLStatement>> ParseStatements(const string &query);

	//! Extract the logical plan of a query
	DUCKDB_API unique_ptr<LogicalOperator> ExtractPlan(const string &query);
	DUCKDB_API void HandlePragmaStatements(vector<unique_ptr<SQLStatement>> &statements);

	//! Runs a function with a valid transaction context, potentially starting a transaction if the context is in auto
	//! commit mode.
	DUCKDB_API void RunFunctionInTransaction(const std::function<void(void)> &fun,
	                                         bool requires_valid_transaction = true);
	//! Same as RunFunctionInTransaction, but does not obtain a lock on the client context or check for validation
	DUCKDB_API void RunFunctionInTransactionInternal(ClientContextLock &lock, const std::function<void(void)> &fun,
	                                                 bool requires_valid_transaction = true);

	//! Equivalent to CURRENT_SETTING(key) SQL function.
	DUCKDB_API bool TryGetCurrentSetting(const std::string &key, Value &result);

	//! Returns the parser options for this client context
	DUCKDB_API ParserOptions GetParserOptions() const;

	DUCKDB_API unique_ptr<DataChunk> Fetch(ClientContextLock &lock, StreamQueryResult &result);

	//! Whether or not the given result object (streaming query result or pending query result) is active
	DUCKDB_API bool IsActiveResult(ClientContextLock &lock, BaseQueryResult *result);

	//! Returns the current executor
	Executor &GetExecutor();

	//! Returns the current query string (if any)
	const string &GetCurrentQuery();

	//! Fetch a list of table names that are required for a given query
	DUCKDB_API unordered_set<string> GetTableNames(const string &query);

	DUCKDB_API ClientProperties GetClientProperties() const;

private:
	//! Parse statements and resolve pragmas from a query
	bool ParseStatements(ClientContextLock &lock, const string &query, vector<unique_ptr<SQLStatement>> &result,
	                     PreservedError &error);
	//! Issues a query to the database and returns a Pending Query Result
	unique_ptr<PendingQueryResult> PendingQueryInternal(ClientContextLock &lock, unique_ptr<SQLStatement> statement,
	                                                    PendingQueryParameters parameters, bool verify = true);
	unique_ptr<QueryResult> ExecutePendingQueryInternal(ClientContextLock &lock, PendingQueryResult &query);

	//! Parse statements from a query
	vector<unique_ptr<SQLStatement>> ParseStatementsInternal(ClientContextLock &lock, const string &query);
	//! Perform aggressive query verification of a SELECT statement. Only called when query_verification_enabled is
	//! true.
	PreservedError VerifyQuery(ClientContextLock &lock, const string &query, unique_ptr<SQLStatement> statement);

	void InitialCleanup(ClientContextLock &lock);
	//! Internal clean up, does not lock. Caller must hold the context_lock.
	void CleanupInternal(ClientContextLock &lock, BaseQueryResult *result = nullptr,
	                     bool invalidate_transaction = false);
	unique_ptr<PendingQueryResult> PendingStatementOrPreparedStatement(ClientContextLock &lock, const string &query,
	                                                                   unique_ptr<SQLStatement> statement,
	                                                                   shared_ptr<PreparedStatementData> &prepared,
	                                                                   PendingQueryParameters parameters);
	unique_ptr<PendingQueryResult> PendingPreparedStatement(ClientContextLock &lock,
	                                                        shared_ptr<PreparedStatementData> statement_p,
	                                                        PendingQueryParameters parameters);

	//! Internally prepare a SQL statement. Caller must hold the context_lock.
	shared_ptr<PreparedStatementData> CreatePreparedStatement(ClientContextLock &lock, const string &query,
	                                                          unique_ptr<SQLStatement> statement,
	                                                          vector<Value> *values = nullptr);
	unique_ptr<PendingQueryResult> PendingStatementInternal(ClientContextLock &lock, const string &query,
	                                                        unique_ptr<SQLStatement> statement,
	                                                        PendingQueryParameters parameters);
	unique_ptr<QueryResult> RunStatementInternal(ClientContextLock &lock, const string &query,
	                                             unique_ptr<SQLStatement> statement, bool allow_stream_result,
	                                             bool verify = true);
	unique_ptr<PreparedStatement> PrepareInternal(ClientContextLock &lock, unique_ptr<SQLStatement> statement);
	void LogQueryInternal(ClientContextLock &lock, const string &query);

	unique_ptr<QueryResult> FetchResultInternal(ClientContextLock &lock, PendingQueryResult &pending);
	unique_ptr<DataChunk> FetchInternal(ClientContextLock &lock, Executor &executor, BaseQueryResult &result);

	unique_ptr<ClientContextLock> LockContext();

	void BeginTransactionInternal(ClientContextLock &lock, bool requires_valid_transaction);
	void BeginQueryInternal(ClientContextLock &lock, const string &query);
	PreservedError EndQueryInternal(ClientContextLock &lock, bool success, bool invalidate_transaction);

	PendingExecutionResult ExecuteTaskInternal(ClientContextLock &lock, PendingQueryResult &result);

	unique_ptr<PendingQueryResult> PendingStatementOrPreparedStatementInternal(
	    ClientContextLock &lock, const string &query, unique_ptr<SQLStatement> statement,
	    shared_ptr<PreparedStatementData> &prepared, PendingQueryParameters parameters);

	unique_ptr<PendingQueryResult> PendingQueryPreparedInternal(ClientContextLock &lock, const string &query,
	                                                            shared_ptr<PreparedStatementData> &prepared,
	                                                            PendingQueryParameters parameters);

private:
	//! Lock on using the ClientContext in parallel
	mutex context_lock;
	//! The currently active query context
	unique_ptr<ActiveQueryContext> active_query;
	//! The current query progress
	atomic<double> query_progress;
};

class ClientContextLock {
public:
	explicit ClientContextLock(mutex &context_lock) : client_guard(context_lock) {
	}

	~ClientContextLock() {
	}

private:
	lock_guard<mutex> client_guard;
};

class ClientContextWrapper {
public:
	DUCKDB_API explicit ClientContextWrapper(const shared_ptr<ClientContext> &context)
	    : client_context(context) {

	      };
	shared_ptr<ClientContext> GetContext() {
		auto actual_context = client_context.lock();
		if (!actual_context) {
			throw ConnectionException("Connection has already been closed");
		}
		return actual_context;
	}

private:
	std::weak_ptr<ClientContext> client_context;
};

} // namespace duckdb



#include <memory>

namespace duckdb {
struct BoundStatement;

class ClientContextWrapper;
class Binder;
class LogicalOperator;
class QueryNode;
class TableRef;

class Relation : public std::enable_shared_from_this<Relation> {
public:
	DUCKDB_API Relation(const std::shared_ptr<ClientContext> &context, RelationType type)
	    : context(context), type(type) {
	}
	DUCKDB_API Relation(ClientContextWrapper &context, RelationType type) : context(context.GetContext()), type(type) {
	}
	DUCKDB_API virtual ~Relation() {
	}

	ClientContextWrapper context;

	RelationType type;

	shared_ptr<ExternalDependency> extra_dependencies;

public:
	DUCKDB_API virtual const vector<ColumnDefinition> &Columns() = 0;
	DUCKDB_API virtual unique_ptr<QueryNode> GetQueryNode();
	DUCKDB_API virtual BoundStatement Bind(Binder &binder);
	DUCKDB_API virtual string GetAlias();

	DUCKDB_API unique_ptr<QueryResult> Execute();
	DUCKDB_API string ToString();
	DUCKDB_API virtual string ToString(idx_t depth) = 0;

	DUCKDB_API void Print();
	DUCKDB_API void Head(idx_t limit = 10);

	DUCKDB_API shared_ptr<Relation> CreateView(const string &name, bool replace = true, bool temporary = false);
	DUCKDB_API unique_ptr<QueryResult> Query(const string &sql);
	DUCKDB_API unique_ptr<QueryResult> Query(const string &name, const string &sql);

	//! Explain the query plan of this relation
	DUCKDB_API unique_ptr<QueryResult> Explain();

	DUCKDB_API virtual unique_ptr<TableRef> GetTableRef();
	DUCKDB_API virtual bool IsReadOnly() {
		return true;
	}

public:
	// PROJECT
	DUCKDB_API shared_ptr<Relation> Project(const string &select_list);
	DUCKDB_API shared_ptr<Relation> Project(const string &expression, const string &alias);
	DUCKDB_API shared_ptr<Relation> Project(const string &select_list, const vector<string> &aliases);
	DUCKDB_API shared_ptr<Relation> Project(const vector<string> &expressions);
	DUCKDB_API shared_ptr<Relation> Project(const vector<string> &expressions, const vector<string> &aliases);

	// FILTER
	DUCKDB_API shared_ptr<Relation> Filter(const string &expression);
	DUCKDB_API shared_ptr<Relation> Filter(const vector<string> &expressions);

	// LIMIT
	DUCKDB_API shared_ptr<Relation> Limit(int64_t n, int64_t offset = 0);

	// ORDER
	DUCKDB_API shared_ptr<Relation> Order(const string &expression);
	DUCKDB_API shared_ptr<Relation> Order(const vector<string> &expressions);

	// JOIN operation
	DUCKDB_API shared_ptr<Relation> Join(const shared_ptr<Relation> &other, const string &condition,
	                                     JoinType type = JoinType::INNER);

	// CROSS PRODUCT operation
	DUCKDB_API shared_ptr<Relation> CrossProduct(const shared_ptr<Relation> &other);

	// SET operations
	DUCKDB_API shared_ptr<Relation> Union(const shared_ptr<Relation> &other);
	DUCKDB_API shared_ptr<Relation> Except(const shared_ptr<Relation> &other);
	DUCKDB_API shared_ptr<Relation> Intersect(const shared_ptr<Relation> &other);

	// DISTINCT operation
	DUCKDB_API shared_ptr<Relation> Distinct();

	// AGGREGATES
	DUCKDB_API shared_ptr<Relation> Aggregate(const string &aggregate_list);
	DUCKDB_API shared_ptr<Relation> Aggregate(const vector<string> &aggregates);
	DUCKDB_API shared_ptr<Relation> Aggregate(const string &aggregate_list, const string &group_list);
	DUCKDB_API shared_ptr<Relation> Aggregate(const vector<string> &aggregates, const vector<string> &groups);

	// ALIAS
	DUCKDB_API shared_ptr<Relation> Alias(const string &alias);

	//! Insert the data from this relation into a table
	DUCKDB_API void Insert(const string &table_name);
	DUCKDB_API void Insert(const string &schema_name, const string &table_name);
	//! Insert a row (i.e.,list of values) into a table
	DUCKDB_API void Insert(const vector<vector<Value>> &values);
	//! Create a table and insert the data from this relation into that table
	DUCKDB_API void Create(const string &table_name);
	DUCKDB_API void Create(const string &schema_name, const string &table_name);

	//! Write a relation to a CSV file
	DUCKDB_API void WriteCSV(const string &csv_file);

	//! Update a table, can only be used on a TableRelation
	DUCKDB_API virtual void Update(const string &update, const string &condition = string());
	//! Delete from a table, can only be used on a TableRelation
	DUCKDB_API virtual void Delete(const string &condition = string());
	//! Create a relation from calling a table in/out function on the input relation
	//! Create a relation from calling a table in/out function on the input relation
	DUCKDB_API shared_ptr<Relation> TableFunction(const std::string &fname, const vector<Value> &values);
	DUCKDB_API shared_ptr<Relation> TableFunction(const std::string &fname, const vector<Value> &values,
	                                              const named_parameter_map_t &named_parameters);

public:
	//! Whether or not the relation inherits column bindings from its child or not, only relevant for binding
	DUCKDB_API virtual bool InheritsColumnBindings() {
		return false;
	}
	DUCKDB_API virtual Relation *ChildRelation() {
		return nullptr;
	}
	DUCKDB_API vector<shared_ptr<ExternalDependency>> GetAllDependencies();

protected:
	DUCKDB_API string RenderWhitespace(idx_t depth);
};

} // namespace duckdb





namespace duckdb {

class ColumnDataCollection;
class ClientContext;

class DatabaseInstance;
class DuckDB;
class LogicalOperator;
class SelectStatement;

typedef void (*warning_callback)(std::string);

//! A connection to a database. This represents a (client) connection that can
//! be used to query the database.
class Connection {
public:
	DUCKDB_API explicit Connection(DuckDB &database);
	DUCKDB_API explicit Connection(DatabaseInstance &database);
	DUCKDB_API ~Connection();

	shared_ptr<ClientContext> context;
	warning_callback warning_cb;

public:
	//! Returns query profiling information for the current query
	DUCKDB_API string GetProfilingInformation(ProfilerPrintFormat format = ProfilerPrintFormat::QUERY_TREE);

	//! Interrupt execution of the current query
	DUCKDB_API void Interrupt();

	//! Enable query profiling
	DUCKDB_API void EnableProfiling();
	//! Disable query profiling
	DUCKDB_API void DisableProfiling();

	DUCKDB_API void SetWarningCallback(warning_callback);

	//! Enable aggressive verification/testing of queries, should only be used in testing
	DUCKDB_API void EnableQueryVerification();
	DUCKDB_API void DisableQueryVerification();
	//! Force parallel execution, even for smaller tables. Should only be used in testing.
	DUCKDB_API void ForceParallelism();

	//! Issues a query to the database and returns a QueryResult. This result can be either a StreamQueryResult or a
	//! MaterializedQueryResult. The result can be stepped through with calls to Fetch(). Note that there can only be
	//! one active StreamQueryResult per Connection object. Calling SendQuery() will invalidate any previously existing
	//! StreamQueryResult.
	DUCKDB_API unique_ptr<QueryResult> SendQuery(const string &query);
	//! Issues a query to the database and materializes the result (if necessary). Always returns a
	//! MaterializedQueryResult.
	DUCKDB_API unique_ptr<MaterializedQueryResult> Query(const string &query);
	//! Issues a query to the database and materializes the result (if necessary). Always returns a
	//! MaterializedQueryResult.
	DUCKDB_API unique_ptr<MaterializedQueryResult> Query(unique_ptr<SQLStatement> statement);
	// prepared statements
	template <typename... Args>
	unique_ptr<QueryResult> Query(const string &query, Args... args) {
		vector<Value> values;
		return QueryParamsRecursive(query, values, args...);
	}

	//! Issues a query to the database and returns a Pending Query Result. Note that "query" may only contain
	//! a single statement.
	DUCKDB_API unique_ptr<PendingQueryResult> PendingQuery(const string &query, bool allow_stream_result = false);
	//! Issues a query to the database and returns a Pending Query Result
	DUCKDB_API unique_ptr<PendingQueryResult> PendingQuery(unique_ptr<SQLStatement> statement,
	                                                       bool allow_stream_result = false);

	//! Prepare the specified query, returning a prepared statement object
	DUCKDB_API unique_ptr<PreparedStatement> Prepare(const string &query);
	//! Prepare the specified statement, returning a prepared statement object
	DUCKDB_API unique_ptr<PreparedStatement> Prepare(unique_ptr<SQLStatement> statement);

	//! Get the table info of a specific table (in the default schema), or nullptr if it cannot be found
	DUCKDB_API unique_ptr<TableDescription> TableInfo(const string &table_name);
	//! Get the table info of a specific table, or nullptr if it cannot be found
	DUCKDB_API unique_ptr<TableDescription> TableInfo(const string &schema_name, const string &table_name);

	//! Extract a set of SQL statements from a specific query
	DUCKDB_API vector<unique_ptr<SQLStatement>> ExtractStatements(const string &query);
	//! Extract the logical plan that corresponds to a query
	DUCKDB_API unique_ptr<LogicalOperator> ExtractPlan(const string &query);

	//! Appends a DataChunk to the specified table
	DUCKDB_API void Append(TableDescription &description, DataChunk &chunk);
	//! Appends a ColumnDataCollection to the specified table
	DUCKDB_API void Append(TableDescription &description, ColumnDataCollection &collection);

	//! Returns a relation that produces a table from this connection
	DUCKDB_API shared_ptr<Relation> Table(const string &tname);
	DUCKDB_API shared_ptr<Relation> Table(const string &schema_name, const string &table_name);
	//! Returns a relation that produces a view from this connection
	DUCKDB_API shared_ptr<Relation> View(const string &tname);
	DUCKDB_API shared_ptr<Relation> View(const string &schema_name, const string &table_name);
	//! Returns a relation that calls a specified table function
	DUCKDB_API shared_ptr<Relation> TableFunction(const string &tname);
	DUCKDB_API shared_ptr<Relation> TableFunction(const string &tname, const vector<Value> &values,
	                                              const named_parameter_map_t &named_parameters);
	DUCKDB_API shared_ptr<Relation> TableFunction(const string &tname, const vector<Value> &values);
	//! Returns a relation that produces values
	DUCKDB_API shared_ptr<Relation> Values(const vector<vector<Value>> &values);
	DUCKDB_API shared_ptr<Relation> Values(const vector<vector<Value>> &values, const vector<string> &column_names,
	                                       const string &alias = "values");
	DUCKDB_API shared_ptr<Relation> Values(const string &values);
	DUCKDB_API shared_ptr<Relation> Values(const string &values, const vector<string> &column_names,
	                                       const string &alias = "values");
	//! Reads CSV file
	DUCKDB_API shared_ptr<Relation> ReadCSV(const string &csv_file);
	DUCKDB_API shared_ptr<Relation> ReadCSV(const string &csv_file, const vector<string> &columns);
	//! Returns a relation from a query
	DUCKDB_API shared_ptr<Relation> RelationFromQuery(const string &query, const string &alias = "queryrelation",
	                                                  const string &error = "Expected a single SELECT statement");
	DUCKDB_API shared_ptr<Relation> RelationFromQuery(unique_ptr<SelectStatement> select_stmt,
	                                                  const string &alias = "queryrelation");

	DUCKDB_API void BeginTransaction();
	DUCKDB_API void Commit();
	DUCKDB_API void Rollback();
	DUCKDB_API void SetAutoCommit(bool auto_commit);
	DUCKDB_API bool IsAutoCommit();
	DUCKDB_API bool HasActiveTransaction();

	//! Fetch a list of table names that are required for a given query
	DUCKDB_API unordered_set<string> GetTableNames(const string &query);

	template <typename TR, typename... Args>
	void CreateScalarFunction(const string &name, TR (*udf_func)(Args...)) {
		scalar_function_t function = UDFWrapper::CreateScalarFunction<TR, Args...>(name, udf_func);
		UDFWrapper::RegisterFunction<TR, Args...>(name, function, *context);
	}

	template <typename TR, typename... Args>
	void CreateScalarFunction(const string &name, vector<LogicalType> args, LogicalType ret_type,
	                          TR (*udf_func)(Args...)) {
		scalar_function_t function =
		    UDFWrapper::CreateScalarFunction<TR, Args...>(name, args, move(ret_type), udf_func);
		UDFWrapper::RegisterFunction(name, args, ret_type, function, *context);
	}

	template <typename TR, typename... Args>
	void CreateVectorizedFunction(const string &name, scalar_function_t udf_func,
	                              LogicalType varargs = LogicalType::INVALID) {
		UDFWrapper::RegisterFunction<TR, Args...>(name, udf_func, *context, move(varargs));
	}

	DUCKDB_API void CreateVectorizedFunction(const string &name, vector<LogicalType> args, LogicalType ret_type,
	                                         scalar_function_t udf_func, LogicalType varargs = LogicalType::INVALID) {
		UDFWrapper::RegisterFunction(name, move(args), move(ret_type), udf_func, *context, move(varargs));
	}

	//------------------------------------- Aggreate Functions ----------------------------------------//
	template <typename UDF_OP, typename STATE, typename TR, typename TA>
	void CreateAggregateFunction(const string &name) {
		AggregateFunction function = UDFWrapper::CreateAggregateFunction<UDF_OP, STATE, TR, TA>(name);
		UDFWrapper::RegisterAggrFunction(function, *context);
	}

	template <typename UDF_OP, typename STATE, typename TR, typename TA, typename TB>
	void CreateAggregateFunction(const string &name) {
		AggregateFunction function = UDFWrapper::CreateAggregateFunction<UDF_OP, STATE, TR, TA, TB>(name);
		UDFWrapper::RegisterAggrFunction(function, *context);
	}

	template <typename UDF_OP, typename STATE, typename TR, typename TA>
	void CreateAggregateFunction(const string &name, LogicalType ret_type, LogicalType input_typeA) {
		AggregateFunction function =
		    UDFWrapper::CreateAggregateFunction<UDF_OP, STATE, TR, TA>(name, ret_type, input_typeA);
		UDFWrapper::RegisterAggrFunction(function, *context);
	}

	template <typename UDF_OP, typename STATE, typename TR, typename TA, typename TB>
	void CreateAggregateFunction(const string &name, LogicalType ret_type, LogicalType input_typeA,
	                             LogicalType input_typeB) {
		AggregateFunction function =
		    UDFWrapper::CreateAggregateFunction<UDF_OP, STATE, TR, TA, TB>(name, ret_type, input_typeA, input_typeB);
		UDFWrapper::RegisterAggrFunction(function, *context);
	}

	DUCKDB_API void CreateAggregateFunction(const string &name, vector<LogicalType> arguments, LogicalType return_type,
	                                        aggregate_size_t state_size, aggregate_initialize_t initialize,
	                                        aggregate_update_t update, aggregate_combine_t combine,
	                                        aggregate_finalize_t finalize,
	                                        aggregate_simple_update_t simple_update = nullptr,
	                                        bind_aggregate_function_t bind = nullptr,
	                                        aggregate_destructor_t destructor = nullptr) {
		AggregateFunction function =
		    UDFWrapper::CreateAggregateFunction(name, arguments, return_type, state_size, initialize, update, combine,
		                                        finalize, simple_update, bind, destructor);
		UDFWrapper::RegisterAggrFunction(function, *context);
	}

private:
	unique_ptr<QueryResult> QueryParamsRecursive(const string &query, vector<Value> &values);

	template <typename T, typename... Args>
	unique_ptr<QueryResult> QueryParamsRecursive(const string &query, vector<Value> &values, T value, Args... args) {
		values.push_back(Value::CreateValue<T>(value));
		return QueryParamsRecursive(query, values, args...);
	}
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/database.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/config.hpp
//
//
//===----------------------------------------------------------------------===//











//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/replacement_scan.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

class ClientContext;
class TableFunctionRef;

struct ReplacementScanData {
	virtual ~ReplacementScanData() {
	}
};

typedef unique_ptr<TableFunctionRef> (*replacement_scan_t)(ClientContext &context, const string &table_name,
                                                           ReplacementScanData *data);

//! Replacement table scans are automatically attempted when a table name cannot be found in the schema
//! This allows you to do e.g. SELECT * FROM 'filename.csv', and automatically convert this into a CSV scan
struct ReplacementScan {
	explicit ReplacementScan(replacement_scan_t function, unique_ptr<ReplacementScanData> data_p = nullptr)
	    : function(function), data(move(data_p)) {
	}

	replacement_scan_t function;
	unique_ptr<ReplacementScanData> data;
};

} // namespace duckdb



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/optimizer_type.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class OptimizerType : uint32_t {
	INVALID = 0,
	EXPRESSION_REWRITER,
	FILTER_PULLUP,
	FILTER_PUSHDOWN,
	REGEX_RANGE,
	IN_CLAUSE,
	JOIN_ORDER,
	DELIMINATOR,
	UNUSED_COLUMNS,
	STATISTICS_PROPAGATION,
	COMMON_SUBEXPRESSIONS,
	COMMON_AGGREGATE,
	COLUMN_LIFETIME,
	TOP_N,
	REORDER_FILTER,
	EXTENSION
};

string OptimizerTypeToString(OptimizerType type);
OptimizerType OptimizerTypeFromString(const string &str);

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/window_aggregation_mode.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class WindowAggregationMode : uint32_t {
	//! Use the window aggregate API if available
	WINDOW = 0,
	//! Don't use window, but use combine if available
	COMBINE,
	//! Don't use combine or window (compute each frame separately)
	SEPARATE
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/enums/set_scope.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

enum class SetScope : uint8_t {
	AUTOMATIC = 0,
	LOCAL = 1, /* unused */
	SESSION = 2,
	GLOBAL = 3
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parser_extension.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {

//! The ParserExtensionInfo holds static information relevant to the parser extension
//! It is made available in the parse_function, and will be kept alive as long as the database system is kept alive
struct ParserExtensionInfo {
	DUCKDB_API virtual ~ParserExtensionInfo() {
	}
};

//===--------------------------------------------------------------------===//
// Parse
//===--------------------------------------------------------------------===//
enum class ParserExtensionResultType : uint8_t { PARSE_SUCCESSFUL, DISPLAY_ORIGINAL_ERROR, DISPLAY_EXTENSION_ERROR };

//! The ParserExtensionParseData holds the result of a successful parse step
//! It will be passed along to the subsequent plan function
struct ParserExtensionParseData {
	DUCKDB_API virtual ~ParserExtensionParseData() {
	}

	virtual unique_ptr<ParserExtensionParseData> Copy() const = 0;
};

struct ParserExtensionParseResult {
	ParserExtensionParseResult() : type(ParserExtensionResultType::DISPLAY_ORIGINAL_ERROR) {
	}
	ParserExtensionParseResult(string error_p)
	    : type(ParserExtensionResultType::DISPLAY_EXTENSION_ERROR), error(move(error_p)) {
	}
	ParserExtensionParseResult(unique_ptr<ParserExtensionParseData> parse_data_p)
	    : type(ParserExtensionResultType::PARSE_SUCCESSFUL), parse_data(move(parse_data_p)) {
	}

	//! Whether or not parsing was successful
	ParserExtensionResultType type;
	//! The parse data (if successful)
	unique_ptr<ParserExtensionParseData> parse_data;
	//! The error message (if unsuccessful)
	string error;
};

typedef ParserExtensionParseResult (*parse_function_t)(ParserExtensionInfo *info, const string &query);
//===--------------------------------------------------------------------===//
// Plan
//===--------------------------------------------------------------------===//
struct ParserExtensionPlanResult {
	//! The table function to execute
	TableFunction function;
	//! Parameters to the function
	vector<Value> parameters;
	//! Whether or not the statement is read_only (i.e. can be executed in a read_only database)
	bool read_only = false;
	//! Whether or not the statement requires a valid transaction to be executed
	bool requires_valid_transaction = true;
	//! What type of result set the statement returns
	StatementReturnType return_type = StatementReturnType::NOTHING;
};

typedef ParserExtensionPlanResult (*plan_function_t)(ParserExtensionInfo *info, ClientContext &context,
                                                     unique_ptr<ParserExtensionParseData> parse_data);

//===--------------------------------------------------------------------===//
// ParserExtension
//===--------------------------------------------------------------------===//
class ParserExtension {
public:
	//! The parse function of the parser extension.
	//! Takes a query string as input and returns ParserExtensionParseData (on success) or an error
	parse_function_t parse_function;

	//! The plan function of the parser extension
	//! Takes as input the result of the parse_function, and outputs various properties of the resulting plan
	plan_function_t plan_function;

	//! Additional parser info passed to the parse function
	shared_ptr<ParserExtensionInfo> parser_info;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parser_extension.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

//! The OptimizerExtensionInfo holds static information relevant to the optimizer extension
struct OptimizerExtensionInfo {
	DUCKDB_API virtual ~OptimizerExtensionInfo() {
	}
};

typedef void (*optimize_function_t)(ClientContext &context, OptimizerExtensionInfo *info,
                                    unique_ptr<LogicalOperator> &plan);

class OptimizerExtension {
public:
	//! The parse function of the parser extension.
	//! Takes a query string as input and returns ParserExtensionParseData (on success) or an error
	optimize_function_t optimize_function;

	//! Additional parser info passed to the parse function
	shared_ptr<OptimizerExtensionInfo> optimizer_info;
};

} // namespace duckdb


namespace duckdb {
class ClientContext;
class TableFunctionRef;
class CompressionFunction;

struct CompressionFunctionSet;
struct DBConfig;

enum class AccessMode : uint8_t { UNDEFINED = 0, AUTOMATIC = 1, READ_ONLY = 2, READ_WRITE = 3 };

enum class CheckpointAbort : uint8_t {
	NO_ABORT = 0,
	DEBUG_ABORT_BEFORE_TRUNCATE = 1,
	DEBUG_ABORT_BEFORE_HEADER = 2,
	DEBUG_ABORT_AFTER_FREE_LIST_WRITE = 3
};

typedef void (*set_global_function_t)(DatabaseInstance *db, DBConfig &config, const Value &parameter);
typedef void (*set_local_function_t)(ClientContext &context, const Value &parameter);
typedef Value (*get_setting_function_t)(ClientContext &context);

struct ConfigurationOption {
	const char *name;
	const char *description;
	LogicalTypeId parameter_type;
	set_global_function_t set_global;
	set_local_function_t set_local;
	get_setting_function_t get_setting;
};

typedef void (*set_option_callback_t)(ClientContext &context, SetScope scope, Value &parameter);

struct ExtensionOption {
	ExtensionOption(string description_p, LogicalType type_p, set_option_callback_t set_function_p)
	    : description(move(description_p)), type(move(type_p)), set_function(set_function_p) {
	}

	string description;
	LogicalType type;
	set_option_callback_t set_function;
};

struct DBConfigOptions {
	//! Access mode of the database (AUTOMATIC, READ_ONLY or READ_WRITE)
	AccessMode access_mode = AccessMode::AUTOMATIC;
	//! Checkpoint when WAL reaches this size (default: 16MB)
	idx_t checkpoint_wal_size = 1 << 24;
	//! Whether or not to use Direct IO, bypassing operating system buffers
	bool use_direct_io = false;
	//! Whether extensions should be loaded on start-up
	bool load_extensions = true;
	//! The maximum memory used by the database system (in bytes). Default: 80% of System available memory
	idx_t maximum_memory = (idx_t)-1;
	//! The maximum amount of CPU threads used by the database system. Default: all available.
	idx_t maximum_threads = (idx_t)-1;
	//! The number of external threads that work on DuckDB tasks. Default: none.
	idx_t external_threads = 0;
	//! Whether or not to create and use a temporary directory to store intermediates that do not fit in memory
	bool use_temporary_directory = true;
	//! Directory to store temporary structures that do not fit in memory
	string temporary_directory;
	//! The collation type of the database
	string collation = string();
	//! The order type used when none is specified (default: ASC)
	OrderType default_order_type = OrderType::ASCENDING;
	//! Null ordering used when none is specified (default: NULLS FIRST)
	OrderByNullType default_null_order = OrderByNullType::NULLS_FIRST;
	//! enable COPY and related commands
	bool enable_external_access = true;
	//! Whether or not object cache is used
	bool object_cache_enable = false;
	//! Force checkpoint when CHECKPOINT is called or on shutdown, even if no changes have been made
	bool force_checkpoint = false;
	//! Run a checkpoint on successful shutdown and delete the WAL, to leave only a single database file behind
	bool checkpoint_on_shutdown = true;
	//! Debug flag that decides when a checkpoing should be aborted. Only used for testing purposes.
	CheckpointAbort checkpoint_abort = CheckpointAbort::NO_ABORT;
	//! Initialize the database with the standard set of DuckDB functions
	//! You should probably not touch this unless you know what you are doing
	bool initialize_default_database = true;
	//! The set of disabled optimizers (default empty)
	set<OptimizerType> disabled_optimizers;
	//! Force a specific compression method to be used when checkpointing (if available)
	CompressionType force_compression = CompressionType::COMPRESSION_AUTO;
	//! Debug flag that adds additional (unnecessary) free_list blocks to the storage
	bool debug_many_free_list_blocks = false;
	//! Debug setting for window aggregation mode: (window, combine, separate)
	WindowAggregationMode window_mode = WindowAggregationMode::WINDOW;
	//! Whether or not preserving insertion order should be preserved
	bool preserve_insertion_order = true;
	//! Database configuration variables as controlled by SET
	case_insensitive_map_t<Value> set_variables;
	//! Whether unsigned extensions should be loaded
	bool allow_unsigned_extensions = false;
};
struct DBConfig {
	friend class DatabaseInstance;
	friend class StorageManager;

public:
	DUCKDB_API DBConfig();
	DUCKDB_API ~DBConfig();

	//! Replacement table scans are automatically attempted when a table name cannot be found in the schema
	vector<ReplacementScan> replacement_scans;
	//! Extra parameters that can be SET for loaded extensions
	case_insensitive_map_t<ExtensionOption> extension_parameters;
	//! The FileSystem to use, can be overwritten to allow for injecting custom file systems for testing purposes (e.g.
	//! RamFS or something similar)
	unique_ptr<FileSystem> file_system;
	//! The allocator used by the system
	unique_ptr<Allocator> allocator;
	//! Database configuration options
	DBConfigOptions options;

	//! Extensions made to the parser
	vector<ParserExtension> parser_extensions;
	vector<OptimizerExtension> optimizer_extensions;

	DUCKDB_API void AddExtensionOption(string name, string description, LogicalType parameter,
	                                   set_option_callback_t function = nullptr);

public:
	DUCKDB_API static DBConfig &GetConfig(ClientContext &context);
	DUCKDB_API static DBConfig &GetConfig(DatabaseInstance &db);
	DUCKDB_API static const DBConfig &GetConfig(const ClientContext &context);
	DUCKDB_API static const DBConfig &GetConfig(const DatabaseInstance &db);
	DUCKDB_API static vector<ConfigurationOption> GetOptions();
	DUCKDB_API static idx_t GetOptionCount();

	//! Fetch an option by index. Returns a pointer to the option, or nullptr if out of range
	DUCKDB_API static ConfigurationOption *GetOptionByIndex(idx_t index);
	//! Fetch an option by name. Returns a pointer to the option, or nullptr if none exists.
	DUCKDB_API static ConfigurationOption *GetOptionByName(const string &name);

	DUCKDB_API void SetOption(const ConfigurationOption &option, const Value &value);

	DUCKDB_API static idx_t ParseMemoryLimit(const string &arg);

	//! Return the list of possible compression functions for the specific physical type
	DUCKDB_API vector<CompressionFunction *> GetCompressionFunctions(PhysicalType data_type);
	//! Return the compression function for the specified compression type/physical type combo
	DUCKDB_API CompressionFunction *GetCompressionFunction(CompressionType type, PhysicalType data_type);

private:
	unique_ptr<CompressionFunctionSet> compression_functions;
};

} // namespace duckdb

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/extension.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {
class DuckDB;

//! The Extension class is the base class used to define extensions
class Extension {
public:
	DUCKDB_API virtual ~Extension();

	DUCKDB_API virtual void Load(DuckDB &db) = 0;
	DUCKDB_API virtual std::string Name() = 0;
};

} // namespace duckdb


namespace duckdb {
class StorageManager;
class Catalog;
class TransactionManager;
class ConnectionManager;
class FileSystem;
class TaskScheduler;
class ObjectCache;

class DatabaseInstance : public std::enable_shared_from_this<DatabaseInstance> {
	friend class DuckDB;

public:
	DUCKDB_API DatabaseInstance();
	DUCKDB_API ~DatabaseInstance();

	DBConfig config;

public:
	DUCKDB_API StorageManager &GetStorageManager();
	DUCKDB_API Catalog &GetCatalog();
	DUCKDB_API FileSystem &GetFileSystem();
	DUCKDB_API TransactionManager &GetTransactionManager();
	DUCKDB_API TaskScheduler &GetScheduler();
	DUCKDB_API ObjectCache &GetObjectCache();
	DUCKDB_API ConnectionManager &GetConnectionManager();
	DUCKDB_API void Invalidate();
	DUCKDB_API bool IsInvalidated();

	idx_t NumberOfThreads();

	DUCKDB_API static DatabaseInstance &GetDatabase(ClientContext &context);

	DUCKDB_API const unordered_set<std::string> &LoadedExtensions();

	DUCKDB_API bool TryGetCurrentSetting(const std::string &key, Value &result);

private:
	void Initialize(const char *path, DBConfig *config);

	void Configure(DBConfig &config);

private:
	unique_ptr<StorageManager> storage;
	unique_ptr<Catalog> catalog;
	unique_ptr<TransactionManager> transaction_manager;
	unique_ptr<TaskScheduler> scheduler;
	unique_ptr<ObjectCache> object_cache;
	unique_ptr<ConnectionManager> connection_manager;
	unordered_set<std::string> loaded_extensions;
	//! Set to true if a fatal exception has occurred
	bool is_invalidated = false;
};

//! The database object. This object holds the catalog and all the
//! database-specific meta information.
class DuckDB {
public:
	DUCKDB_API explicit DuckDB(const char *path = nullptr, DBConfig *config = nullptr);
	DUCKDB_API explicit DuckDB(const string &path, DBConfig *config = nullptr);
	DUCKDB_API explicit DuckDB(DatabaseInstance &instance);

	DUCKDB_API ~DuckDB();

	//! Reference to the actual database instance
	shared_ptr<DatabaseInstance> instance;

public:
	template <class T>
	void LoadExtension() {
		T extension;
		if (ExtensionIsLoaded(extension.Name())) {
			return;
		}
		extension.Load(*this);
		SetExtensionLoaded(extension.Name());
	}

	DUCKDB_API FileSystem &GetFileSystem();

	DUCKDB_API idx_t NumberOfThreads();
	DUCKDB_API static const char *SourceID();
	DUCKDB_API static const char *LibraryVersion();
	DUCKDB_API static string Platform();
	DUCKDB_API bool ExtensionIsLoaded(const std::string &name);
	DUCKDB_API void SetExtensionLoaded(const std::string &name);
};

} // namespace duckdb


//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/loadable_extension.hpp
//
//
//===----------------------------------------------------------------------===//



#if defined(DUCKDB_BUILD_LOADABLE_EXTENSION) && defined(DUCKDB_EXTENSION_MAIN)
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif
#include <windows.h>

#undef CreateDirectory
#undef MoveFile
#undef RemoveDirectory

#include <delayimp.h>

extern "C" {
/*
This is interesting: Windows would normally require a duckdb.dll being on the DLL search path when we load an extension
using LoadLibrary(). However, there is likely no such dll, because DuckDB was statically linked, or is running as part
of an R or Python module with a completely different name (that we don't know) or something of the sorts. Amazingly,
Windows supports lazy-loading DLLs by linking them with /DELAYLOAD. Then a callback will be triggered whenever we access
symbols in the extension. Since DuckDB is already running in the host process (hopefully), we can use
GetModuleHandle(NULL) to return the current process so the symbols are looked for there. See here for another
explanation of this crazy process:

* https://docs.microsoft.com/en-us/cpp/build/reference/linker-support-for-delay-loaded-dlls?view=msvc-160
* https://docs.microsoft.com/en-us/cpp/build/reference/understanding-the-helper-function?view=msvc-160
*/
FARPROC WINAPI duckdb_dllimport_delay_hook(unsigned dliNotify, PDelayLoadInfo pdli) {
	switch (dliNotify) {
	case dliNotePreLoadLibrary:
		if (strcmp(pdli->szDll, "duckdb.dll") != 0) {
			return NULL;
		}
		return (FARPROC)GetModuleHandle(NULL);
	default:
		return NULL;
	}

	return NULL;
}

ExternC const PfnDliHook __pfnDliNotifyHook2 = duckdb_dllimport_delay_hook;
ExternC const PfnDliHook __pfnDliFailureHook2 = duckdb_dllimport_delay_hook;
}
#endif
#endif

//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/date.hpp
//
//
//===----------------------------------------------------------------------===//








namespace duckdb {

//! The Date class is a static class that holds helper functions for the Date type.
class Date {
public:
	static const char *PINF;  // NOLINT
	static const char *NINF;  // NOLINT
	static const char *EPOCH; // NOLINT

	static const string_t MONTH_NAMES[12];
	static const string_t MONTH_NAMES_ABBREVIATED[12];
	static const string_t DAY_NAMES[7];
	static const string_t DAY_NAMES_ABBREVIATED[7];
	static const int32_t NORMAL_DAYS[13];
	static const int32_t CUMULATIVE_DAYS[13];
	static const int32_t LEAP_DAYS[13];
	static const int32_t CUMULATIVE_LEAP_DAYS[13];
	static const int32_t CUMULATIVE_YEAR_DAYS[401];
	static const int8_t MONTH_PER_DAY_OF_YEAR[365];
	static const int8_t LEAP_MONTH_PER_DAY_OF_YEAR[366];

	// min date is 5877642-06-25 (BC) (-2^31+2)
	constexpr static const int32_t DATE_MIN_YEAR = -5877641;
	constexpr static const int32_t DATE_MIN_MONTH = 6;
	constexpr static const int32_t DATE_MIN_DAY = 25;
	// max date is 5881580-07-10 (2^31-2)
	constexpr static const int32_t DATE_MAX_YEAR = 5881580;
	constexpr static const int32_t DATE_MAX_MONTH = 7;
	constexpr static const int32_t DATE_MAX_DAY = 10;
	constexpr static const int32_t EPOCH_YEAR = 1970;

	constexpr static const int32_t YEAR_INTERVAL = 400;
	constexpr static const int32_t DAYS_PER_YEAR_INTERVAL = 146097;

public:
	//! Convert a string in the format "YYYY-MM-DD" to a date object
	DUCKDB_API static date_t FromString(const string &str, bool strict = false);
	//! Convert a string in the format "YYYY-MM-DD" to a date object
	DUCKDB_API static date_t FromCString(const char *str, idx_t len, bool strict = false);
	//! Convert a date object to a string in the format "YYYY-MM-DD"
	DUCKDB_API static string ToString(date_t date);
	//! Try to convert text in a buffer to a date; returns true if parsing was successful
	DUCKDB_API static bool TryConvertDate(const char *buf, idx_t len, idx_t &pos, date_t &result, bool strict = false);

	//! Create a string "YYYY-MM-DD" from a specified (year, month, day)
	//! combination
	DUCKDB_API static string Format(int32_t year, int32_t month, int32_t day);

	//! Extract the year, month and day from a given date object
	DUCKDB_API static void Convert(date_t date, int32_t &out_year, int32_t &out_month, int32_t &out_day);
	//! Create a Date object from a specified (year, month, day) combination
	DUCKDB_API static date_t FromDate(int32_t year, int32_t month, int32_t day);
	DUCKDB_API static bool TryFromDate(int32_t year, int32_t month, int32_t day, date_t &result);

	//! Returns true if (year) is a leap year, and false otherwise
	DUCKDB_API static bool IsLeapYear(int32_t year);

	//! Returns true if the specified (year, month, day) combination is a valid
	//! date
	DUCKDB_API static bool IsValid(int32_t year, int32_t month, int32_t day);

	//! Returns true if the specified date is finite
	static inline bool IsFinite(date_t date) {
		return date != date_t::infinity() && date != date_t::ninfinity();
	}

	//! The max number of days in a month of a given year
	DUCKDB_API static int32_t MonthDays(int32_t year, int32_t month);

	//! Extract the epoch from the date (seconds since 1970-01-01)
	DUCKDB_API static int64_t Epoch(date_t date);
	//! Extract the epoch from the date (nanoseconds since 1970-01-01)
	DUCKDB_API static int64_t EpochNanoseconds(date_t date);
	//! Convert the epoch (seconds since 1970-01-01) to a date_t
	DUCKDB_API static date_t EpochToDate(int64_t epoch);

	//! Extract the number of days since epoch (days since 1970-01-01)
	DUCKDB_API static int32_t EpochDays(date_t date);
	//! Convert the epoch number of days to a date_t
	DUCKDB_API static date_t EpochDaysToDate(int32_t epoch);

	//! Extract year of a date entry
	DUCKDB_API static int32_t ExtractYear(date_t date);
	//! Extract year of a date entry, but optimized to first try the last year found
	DUCKDB_API static int32_t ExtractYear(date_t date, int32_t *last_year);
	DUCKDB_API static int32_t ExtractYear(timestamp_t ts, int32_t *last_year);
	//! Extract month of a date entry
	DUCKDB_API static int32_t ExtractMonth(date_t date);
	//! Extract day of a date entry
	DUCKDB_API static int32_t ExtractDay(date_t date);
	//! Extract the day of the week (1-7)
	DUCKDB_API static int32_t ExtractISODayOfTheWeek(date_t date);
	//! Extract the day of the year
	DUCKDB_API static int32_t ExtractDayOfTheYear(date_t date);
	//! Extract the ISO week number
	//! ISO weeks start on Monday and the first week of a year
	//! contains January 4 of that year.
	//! In the ISO week-numbering system, it is possible for early-January dates
	//! to be part of the 52nd or 53rd week of the previous year.
	DUCKDB_API static void ExtractISOYearWeek(date_t date, int32_t &year, int32_t &week);
	DUCKDB_API static int32_t ExtractISOWeekNumber(date_t date);
	DUCKDB_API static int32_t ExtractISOYearNumber(date_t date);
	//! Extract the week number as Python handles it.
	//! Either Monday or Sunday is the first day of the week,
	//! and any date before the first Monday/Sunday returns week 0
	//! This is a bit more consistent because week numbers in a year are always incrementing
	DUCKDB_API static int32_t ExtractWeekNumberRegular(date_t date, bool monday_first = true);
	//! Returns the date of the monday of the current week.
	DUCKDB_API static date_t GetMondayOfCurrentWeek(date_t date);

	//! Helper function to parse two digits from a string (e.g. "30" -> 30, "03" -> 3, "3" -> 3)
	DUCKDB_API static bool ParseDoubleDigit(const char *buf, idx_t len, idx_t &pos, int32_t &result);

	DUCKDB_API static string ConversionError(const string &str);
	DUCKDB_API static string ConversionError(string_t str);

private:
	static void ExtractYearOffset(int32_t &n, int32_t &year, int32_t &year_offset);
};
} // namespace duckdb
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/blob.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

//! The Blob class is a static class that holds helper functions for the Blob type.
class Blob {
public:
	// map of integer -> hex value
	static constexpr const char *HEX_TABLE = "0123456789ABCDEF";
	// reverse map of byte -> integer value, or -1 for invalid hex values
	static const int HEX_MAP[256];
	//! map of index -> base64 character
	static constexpr const char *BASE64_MAP = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//! padding character used in base64 encoding
	static constexpr const char BASE64_PADDING = '=';

public:
	//! Returns the string size of a blob -> string conversion
	DUCKDB_API static idx_t GetStringSize(string_t blob);
	//! Converts a blob to a string, writing the output to the designated output string.
	//! The string needs to have space for at least GetStringSize(blob) bytes.
	DUCKDB_API static void ToString(string_t blob, char *output);
	//! Convert a blob object to a string
	DUCKDB_API static string ToString(string_t blob);

	//! Returns the blob size of a string -> blob conversion
	DUCKDB_API static bool TryGetBlobSize(string_t str, idx_t &result_size, string *error_message);
	DUCKDB_API static idx_t GetBlobSize(string_t str);
	//! Convert a string to a blob. This function should ONLY be called after calling GetBlobSize, since it does NOT
	//! perform data validation.
	DUCKDB_API static void ToBlob(string_t str, data_ptr_t output);
	//! Convert a string object to a blob
	DUCKDB_API static string ToBlob(string_t str);

	// base 64 conversion functions
	//! Returns the string size of a blob -> base64 conversion
	DUCKDB_API static idx_t ToBase64Size(string_t blob);
	//! Converts a blob to a base64 string, output should have space for at least ToBase64Size(blob) bytes
	DUCKDB_API static void ToBase64(string_t blob, char *output);

	//! Returns the string size of a base64 string -> blob conversion
	DUCKDB_API static idx_t FromBase64Size(string_t str);
	//! Converts a base64 string to a blob, output should have space for at least FromBase64Size(blob) bytes
	DUCKDB_API static void FromBase64(string_t str, data_ptr_t output, idx_t output_size);
};
} // namespace duckdb
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/decimal.hpp
//
//
//===----------------------------------------------------------------------===//





namespace duckdb {

template <class PHYSICAL_TYPE>
struct DecimalWidth {};

template <>
struct DecimalWidth<int16_t> {
	static constexpr uint8_t max = 4;
};

template <>
struct DecimalWidth<int32_t> {
	static constexpr uint8_t max = 9;
};

template <>
struct DecimalWidth<int64_t> {
	static constexpr uint8_t max = 18;
};

template <>
struct DecimalWidth<hugeint_t> {
	static constexpr uint8_t max = 38;
};

//! The Decimal class is a static class that holds helper functions for the Decimal type
class Decimal {
public:
	static constexpr uint8_t MAX_WIDTH_INT16 = DecimalWidth<int16_t>::max;
	static constexpr uint8_t MAX_WIDTH_INT32 = DecimalWidth<int32_t>::max;
	static constexpr uint8_t MAX_WIDTH_INT64 = DecimalWidth<int64_t>::max;
	static constexpr uint8_t MAX_WIDTH_INT128 = DecimalWidth<hugeint_t>::max;
	static constexpr uint8_t MAX_WIDTH_DECIMAL = MAX_WIDTH_INT128;

public:
	static string ToString(int16_t value, uint8_t width, uint8_t scale);
	static string ToString(int32_t value, uint8_t width, uint8_t scale);
	static string ToString(int64_t value, uint8_t width, uint8_t scale);
	static string ToString(hugeint_t value, uint8_t width, uint8_t scale);
};
} // namespace duckdb
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/uuid.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {
class ClientContext;
struct RandomEngine;

//! The UUID class contains static operations for the UUID type
class UUID {
public:
	constexpr static const uint8_t STRING_SIZE = 36;
	//! Convert a uuid string to a hugeint object
	static bool FromString(string str, hugeint_t &result);
	//! Convert a uuid string to a hugeint object
	static bool FromCString(const char *str, idx_t len, hugeint_t &result) {
		return FromString(string(str, 0, len), result);
	}
	//! Convert a hugeint object to a uuid style string
	static void ToString(hugeint_t input, char *buf);

	//! Convert a hugeint object to a uuid style string
	static hugeint_t GenerateRandomUUID(RandomEngine &engine);
	static hugeint_t GenerateRandomUUID();

	//! Convert a hugeint object to a uuid style string
	static string ToString(hugeint_t input) {
		char buff[STRING_SIZE];
		ToString(input, buff);
		return string(buff, STRING_SIZE);
	}

	static hugeint_t FromString(string str) {
		hugeint_t result;
		FromString(str, result);
		return result;
	}
};

} // namespace duckdb
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/timestamp.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {

//! The Timestamp class is a static class that holds helper functions for the Timestamp
//! type.
class Timestamp {
public:
	// min timestamp is 290308-12-22 (BC)
	constexpr static const int32_t MIN_YEAR = -290308;
	constexpr static const int32_t MIN_MONTH = 12;
	constexpr static const int32_t MIN_DAY = 22;

public:
	//! Convert a string in the format "YYYY-MM-DD hh:mm:ss" to a timestamp object
	DUCKDB_API static timestamp_t FromString(const string &str);
	DUCKDB_API static bool TryConvertTimestamp(const char *str, idx_t len, timestamp_t &result);
	DUCKDB_API static timestamp_t FromCString(const char *str, idx_t len);
	//! Convert a date object to a string in the format "YYYY-MM-DD hh:mm:ss"
	DUCKDB_API static string ToString(timestamp_t timestamp);

	DUCKDB_API static date_t GetDate(timestamp_t timestamp);

	DUCKDB_API static dtime_t GetTime(timestamp_t timestamp);
	//! Create a Timestamp object from a specified (date, time) combination
	DUCKDB_API static timestamp_t FromDatetime(date_t date, dtime_t time);
	DUCKDB_API static bool TryFromDatetime(date_t date, dtime_t time, timestamp_t &result);

	//! Is the timestamp finite or infinite?
	static inline bool IsFinite(timestamp_t timestamp) {
		return timestamp != timestamp_t::infinity() && timestamp != timestamp_t::ninfinity();
	}

	//! Extract the date and time from a given timestamp object
	DUCKDB_API static void Convert(timestamp_t date, date_t &out_date, dtime_t &out_time);
	//! Returns current timestamp
	DUCKDB_API static timestamp_t GetCurrentTimestamp();

	//! Convert the epoch (in sec) to a timestamp
	DUCKDB_API static timestamp_t FromEpochSeconds(int64_t ms);
	//! Convert the epoch (in ms) to a timestamp
	DUCKDB_API static timestamp_t FromEpochMs(int64_t ms);
	//! Convert the epoch (in microseconds) to a timestamp
	DUCKDB_API static timestamp_t FromEpochMicroSeconds(int64_t micros);
	//! Convert the epoch (in nanoseconds) to a timestamp
	DUCKDB_API static timestamp_t FromEpochNanoSeconds(int64_t micros);

	//! Convert the epoch (in seconds) to a timestamp
	DUCKDB_API static int64_t GetEpochSeconds(timestamp_t timestamp);
	//! Convert the epoch (in ms) to a timestamp
	DUCKDB_API static int64_t GetEpochMs(timestamp_t timestamp);
	//! Convert a timestamp to epoch (in microseconds)
	DUCKDB_API static int64_t GetEpochMicroSeconds(timestamp_t timestamp);
	//! Convert a timestamp to epoch (in nanoseconds)
	DUCKDB_API static int64_t GetEpochNanoSeconds(timestamp_t timestamp);

	DUCKDB_API static bool TryParseUTCOffset(const char *str, idx_t &pos, idx_t len, int &hour_offset,
	                                         int &minute_offset);

	DUCKDB_API static string ConversionError(const string &str);
	DUCKDB_API static string ConversionError(string_t str);
};
} // namespace duckdb
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/types/time.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {

//! The Time class is a static class that holds helper functions for the Time
//! type.
class Time {
public:
	//! Convert a string in the format "hh:mm:ss" to a time object
	DUCKDB_API static dtime_t FromString(const string &str, bool strict = false);
	DUCKDB_API static dtime_t FromCString(const char *buf, idx_t len, bool strict = false);
	DUCKDB_API static bool TryConvertTime(const char *buf, idx_t len, idx_t &pos, dtime_t &result, bool strict = false);

	//! Convert a time object to a string in the format "hh:mm:ss"
	DUCKDB_API static string ToString(dtime_t time);
	//! Convert a UTC offset to ±HH[:MM]
	DUCKDB_API static string ToUTCOffset(int hour_offset, int minute_offset);

	DUCKDB_API static dtime_t FromTime(int32_t hour, int32_t minute, int32_t second, int32_t microseconds = 0);

	//! Extract the time from a given timestamp object
	DUCKDB_API static void Convert(dtime_t time, int32_t &out_hour, int32_t &out_min, int32_t &out_sec,
	                               int32_t &out_micros);

	DUCKDB_API static string ConversionError(const string &str);
	DUCKDB_API static string ConversionError(string_t str);

private:
	static bool TryConvertInternal(const char *buf, idx_t len, idx_t &pos, dtime_t &result, bool strict);
};

} // namespace duckdb
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/main/appender.hpp
//
//
//===----------------------------------------------------------------------===//







namespace duckdb {

class ColumnDataCollection;
class ClientContext;
class DuckDB;
class TableCatalogEntry;
class Connection;

//! The Appender class can be used to append elements to a table.
class BaseAppender {
protected:
	//! The amount of tuples that will be gathered in the column data collection before flushing
	static constexpr const idx_t FLUSH_COUNT = STANDARD_VECTOR_SIZE * 100;

	Allocator &allocator;
	//! The append types
	vector<LogicalType> types;
	//! The buffered data for the append
	unique_ptr<ColumnDataCollection> collection;
	//! Internal chunk used for appends
	DataChunk chunk;
	//! The current column to append to
	idx_t column = 0;

public:
	DUCKDB_API BaseAppender(Allocator &allocator);
	DUCKDB_API BaseAppender(Allocator &allocator, vector<LogicalType> types);
	DUCKDB_API virtual ~BaseAppender();

	//! Begins a new row append, after calling this the other AppendX() functions
	//! should be called the correct amount of times. After that,
	//! EndRow() should be called.
	DUCKDB_API void BeginRow();
	//! Finishes appending the current row.
	DUCKDB_API void EndRow();

	// Append functions
	template <class T>
	void Append(T value) {
		throw Exception("Undefined type for Appender::Append!");
	}

	DUCKDB_API void Append(const char *value, uint32_t length);

	// prepared statements
	template <typename... Args>
	void AppendRow(Args... args) {
		BeginRow();
		AppendRowRecursive(args...);
	}

	//! Commit the changes made by the appender.
	DUCKDB_API void Flush();
	//! Flush the changes made by the appender and close it. The appender cannot be used after this point
	DUCKDB_API void Close();

	DUCKDB_API vector<LogicalType> &GetTypes() {
		return types;
	}
	DUCKDB_API idx_t CurrentColumn() {
		return column;
	}
	DUCKDB_API void AppendDataChunk(DataChunk &value);

protected:
	void Destructor();
	virtual void FlushInternal(ColumnDataCollection &collection) = 0;
	void InitializeChunk();
	void FlushChunk();

	template <class T>
	void AppendValueInternal(T value);
	template <class SRC, class DST>
	void AppendValueInternal(Vector &vector, SRC input);

	void AppendRowRecursive() {
		EndRow();
	}

	template <typename T, typename... Args>
	void AppendRowRecursive(T value, Args... args) {
		Append<T>(value);
		AppendRowRecursive(args...);
	}

	void AppendValue(const Value &value);
};

class Appender : public BaseAppender {
	//! A reference to a database connection that created this appender
	shared_ptr<ClientContext> context;
	//! The table description (including column names)
	unique_ptr<TableDescription> description;

public:
	DUCKDB_API Appender(Connection &con, const string &schema_name, const string &table_name);
	DUCKDB_API Appender(Connection &con, const string &table_name);
	DUCKDB_API ~Appender() override;

protected:
	void FlushInternal(ColumnDataCollection &collection) override;
};

class InternalAppender : public BaseAppender {
	//! The client context
	ClientContext &context;
	//! The internal table entry to append to
	TableCatalogEntry &table;

public:
	DUCKDB_API InternalAppender(ClientContext &context, TableCatalogEntry &table);
	DUCKDB_API ~InternalAppender() override;

protected:
	void FlushInternal(ColumnDataCollection &collection) override;
};

template <>
DUCKDB_API void BaseAppender::Append(bool value);
template <>
DUCKDB_API void BaseAppender::Append(int8_t value);
template <>
DUCKDB_API void BaseAppender::Append(int16_t value);
template <>
DUCKDB_API void BaseAppender::Append(int32_t value);
template <>
DUCKDB_API void BaseAppender::Append(int64_t value);
template <>
DUCKDB_API void BaseAppender::Append(hugeint_t value);
template <>
DUCKDB_API void BaseAppender::Append(uint8_t value);
template <>
DUCKDB_API void BaseAppender::Append(uint16_t value);
template <>
DUCKDB_API void BaseAppender::Append(uint32_t value);
template <>
DUCKDB_API void BaseAppender::Append(uint64_t value);
template <>
DUCKDB_API void BaseAppender::Append(float value);
template <>
DUCKDB_API void BaseAppender::Append(double value);
template <>
DUCKDB_API void BaseAppender::Append(date_t value);
template <>
DUCKDB_API void BaseAppender::Append(dtime_t value);
template <>
DUCKDB_API void BaseAppender::Append(timestamp_t value);
template <>
DUCKDB_API void BaseAppender::Append(interval_t value);
template <>
DUCKDB_API void BaseAppender::Append(const char *value);
template <>
DUCKDB_API void BaseAppender::Append(string_t value);
template <>
DUCKDB_API void BaseAppender::Append(Value value);
template <>
DUCKDB_API void BaseAppender::Append(std::nullptr_t value);

} // namespace duckdb
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/create_table_function_info.hpp
//
//
//===----------------------------------------------------------------------===//



//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/create_function_info.hpp
//
//
//===----------------------------------------------------------------------===//






namespace duckdb {

struct CreateFunctionInfo : public CreateInfo {
	explicit CreateFunctionInfo(CatalogType type, string schema = DEFAULT_SCHEMA) : CreateInfo(type, schema) {
		D_ASSERT(type == CatalogType::SCALAR_FUNCTION_ENTRY || type == CatalogType::AGGREGATE_FUNCTION_ENTRY ||
		         type == CatalogType::TABLE_FUNCTION_ENTRY || type == CatalogType::PRAGMA_FUNCTION_ENTRY ||
		         type == CatalogType::MACRO_ENTRY || type == CatalogType::TABLE_MACRO_ENTRY);
	}

	//! Function name
	string name;

protected:
	void SerializeInternal(Serializer &serializer) const override {
		serializer.WriteString(name);
	}
};

} // namespace duckdb



namespace duckdb {

struct CreateTableFunctionInfo : public CreateFunctionInfo {
	explicit CreateTableFunctionInfo(TableFunction function)
	    : CreateFunctionInfo(CatalogType::TABLE_FUNCTION_ENTRY), functions(function.name) {
		name = function.name;
		functions.AddFunction(move(function));
	}
	explicit CreateTableFunctionInfo(TableFunctionSet set)
	    : CreateFunctionInfo(CatalogType::TABLE_FUNCTION_ENTRY), functions(move(set)) {
		name = functions.name;
		for (auto &func : functions.functions) {
			func.name = functions.name;
		}
	}

	//! The table functions
	TableFunctionSet functions;

public:
	unique_ptr<CreateInfo> Copy() const override {
		TableFunctionSet set(name);
		set.functions = functions.functions;
		auto result = make_unique<CreateTableFunctionInfo>(move(set));
		CopyProperties(*result);
		return move(result);
	}
};

} // namespace duckdb
//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/create_copy_function_info.hpp
//
//
//===----------------------------------------------------------------------===//




//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/copy_function.hpp
//
//
//===----------------------------------------------------------------------===//





//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/parsed_data/copy_info.hpp
//
//
//===----------------------------------------------------------------------===//








namespace duckdb {

struct CopyInfo : public ParseInfo {
	CopyInfo() : schema(DEFAULT_SCHEMA) {
	}

	//! The schema name to copy to/from
	string schema;
	//! The table name to copy to/from
	string table;
	//! List of columns to copy to/from
	vector<string> select_list;
	//! The file path to copy to/from
	string file_path;
	//! Whether or not this is a copy to file (false) or copy from a file (true)
	bool is_from;
	//! The file format of the external file
	string format;
	//! Set of (key, value) options
	unordered_map<string, vector<Value>> options;

public:
	unique_ptr<CopyInfo> Copy() const {
		auto result = make_unique<CopyInfo>();
		result->schema = schema;
		result->table = table;
		result->select_list = select_list;
		result->file_path = file_path;
		result->is_from = is_from;
		result->format = format;
		result->options = options;
		return result;
	}
};

} // namespace duckdb


namespace duckdb {
class ExecutionContext;

struct LocalFunctionData {
	virtual ~LocalFunctionData() {
	}
};

struct GlobalFunctionData {
	virtual ~GlobalFunctionData() {
	}
};

typedef unique_ptr<FunctionData> (*copy_to_bind_t)(ClientContext &context, CopyInfo &info, vector<string> &names,
                                                   vector<LogicalType> &sql_types);
typedef unique_ptr<LocalFunctionData> (*copy_to_initialize_local_t)(ExecutionContext &context, FunctionData &bind_data);
typedef unique_ptr<GlobalFunctionData> (*copy_to_initialize_global_t)(ClientContext &context, FunctionData &bind_data,
                                                                      const string &file_path);
typedef void (*copy_to_sink_t)(ExecutionContext &context, FunctionData &bind_data, GlobalFunctionData &gstate,
                               LocalFunctionData &lstate, DataChunk &input);
typedef void (*copy_to_combine_t)(ExecutionContext &context, FunctionData &bind_data, GlobalFunctionData &gstate,
                                  LocalFunctionData &lstate);
typedef void (*copy_to_finalize_t)(ClientContext &context, FunctionData &bind_data, GlobalFunctionData &gstate);

typedef void (*copy_to_serialize_t)(FieldWriter &writer, const FunctionData &bind_data, const CopyFunction &function);

typedef unique_ptr<FunctionData> (*copy_to_deserialize_t)(ClientContext &context, FieldReader &reader,
                                                          CopyFunction &function);

typedef unique_ptr<FunctionData> (*copy_from_bind_t)(ClientContext &context, CopyInfo &info,
                                                     vector<string> &expected_names,
                                                     vector<LogicalType> &expected_types);

class CopyFunction : public Function {
public:
	explicit CopyFunction(string name)
	    : Function(name), copy_to_bind(nullptr), copy_to_initialize_local(nullptr), copy_to_initialize_global(nullptr),
	      copy_to_sink(nullptr), copy_to_combine(nullptr), copy_to_finalize(nullptr), serialize(nullptr),
	      deserialize(nullptr), copy_from_bind(nullptr) {
	}

	copy_to_bind_t copy_to_bind;
	copy_to_initialize_local_t copy_to_initialize_local;
	copy_to_initialize_global_t copy_to_initialize_global;
	copy_to_sink_t copy_to_sink;
	copy_to_combine_t copy_to_combine;
	copy_to_finalize_t copy_to_finalize;

	copy_to_serialize_t serialize;
	copy_to_deserialize_t deserialize;

	copy_from_bind_t copy_from_bind;
	TableFunction copy_from_function;

	string extension;
};

} // namespace duckdb


namespace duckdb {

struct CreateCopyFunctionInfo : public CreateInfo {
	explicit CreateCopyFunctionInfo(CopyFunction function)
	    : CreateInfo(CatalogType::COPY_FUNCTION_ENTRY), function(function) {
		this->name = function.name;
	}

	//! Function name
	string name;
	//! The table function
	CopyFunction function;

protected:
	void SerializeInternal(Serializer &) const override {
		throw NotImplementedException("Cannot serialize '%s'", CatalogTypeToString(type));
	}

public:
	unique_ptr<CreateInfo> Copy() const override {
		auto result = make_unique<CreateCopyFunctionInfo>(function);
		CopyProperties(*result);
		return move(result);
	}
};

} // namespace duckdb
