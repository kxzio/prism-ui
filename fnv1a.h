#pragma once
#include <array>

template<typename T, T value>
struct constant_holder_t {
	enum class value_holder : T {
		m_value = value
	};
};

#define constant(value) ((decltype(value))constant_holder_t<decltype(value), value>::value_holder::m_value)

constexpr uint32_t seed = 0x45C3370D;
constexpr uint32_t prime = 0x1000193;

__forceinline uint32_t fnv1a_rt(const char* key) {
	auto hash = seed;

#ifdef RELEASE
	hash ^= __readfsdword(0x20);
#endif

	const char* data = const_cast<char*>(key);

	for (int i = 0; i < strlen(key); i++) {
		hash = hash ^ static_cast<uint8_t>(data[i]);
		hash *= prime;
	}

	return hash;
}

__forceinline uint32_t fnv1a_fl_rt(const char* key, uint32_t length) {
	auto hash = seed;

#ifdef RELEASE
	hash ^= __readfsdword(0x20);
#endif

	const char* data = const_cast<char*>(key);

	for (int i = 0; i < length; i++) {
		hash = hash ^ static_cast<uint8_t>(data[i]);
		hash *= prime;
	}

	return hash;
}

constexpr uint32_t fnv1a_ct(const char* str, uint32_t value = seed) noexcept { return !*str ? value : fnv1a_ct(str + 1, static_cast<unsigned>(1ull * (value ^ static_cast<uint8_t>(*str)) * prime)); }

#define modulate_en(s) (fnv1a_ct(s))