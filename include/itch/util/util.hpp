#ifndef TV_ITCH50_CPP_UTIL_HPP
#define TV_ITCH50_CPP_UTIL_HPP

#include <bit>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

namespace itch::util {

[[nodiscard]] inline std::uint16_t byte_swap_u16(const std::uint16_t value) noexcept {
#ifdef _MSC_VER
	return _byteswap_ushort(value);
#else
	return __builtin_bswap16(value);
#endif
}


[[nodiscard]] inline std::uint32_t byte_swap_u32(const std::uint32_t value) noexcept {
#ifdef _MSC_VER
	return _byteswap_ulong(value);
#else
	return __builtin_bswap32(value);
#endif
}


[[nodiscard]] inline std::uint64_t byte_swap_u64(const std::uint64_t value) noexcept {
#ifdef _MSC_VER
	return _byteswap_uint64(value);
#else
	return __builtin_bswap64(value);
#endif
}

template <typename T>
[[nodiscard]] inline T read_be(const std::uint8_t* ptr) noexcept {
	static_assert(std::is_same_v<T, std::uint8_t > ||
				  std::is_same_v<T, std::uint16_t> ||
				  std::is_same_v<T, std::uint32_t> ||
				  std::is_same_v<T, std::uint64_t>);

	T val;
	std::memcpy(&val, ptr, sizeof(T));

	if constexpr (std::endian::native == std::endian::little) {
		if constexpr (sizeof(T) == 1) {
			return val;
		} else if constexpr (sizeof(T) == 2) {
			return util::byte_swap_u16(val);
		} else if constexpr (sizeof(T) == 4) {
			return util::byte_swap_u32(val);
		} else if constexpr (sizeof(T) == 8) {
			return util::byte_swap_u64(val);
		}
	}

	return val;
}

template <typename T>
[[nodiscard]] inline T read_be_adv(const std::uint8_t*& ptr) noexcept {
	T val = read_be<T>(ptr);
	ptr += sizeof(T);
	return val;
}

[[nodiscard]] inline std::uint64_t read_be_48b(const std::uint8_t* ptr) noexcept {
	std::uint64_t val = 0;
	std::memcpy(&val, ptr, 6);

	if constexpr (std::endian::native == std::endian::little) {
		return util::byte_swap_u64(val) >> 16;
	}

	return val >> 16;
}

[[nodiscard]] inline std::uint64_t read_be_48b_adv(const std::uint8_t*& ptr) noexcept {
	std::uint64_t val = read_be_48b(ptr);
	ptr += 6;
	return val;
}

template <typename T>
[[nodiscard]] inline T read_be_enum(const std::uint8_t* ptr) noexcept {
	static_assert(std::is_enum_v<T>);
	using ut = std::underlying_type_t<T>;
	ut val = read_be<ut>(ptr);
	return static_cast<T>(val);
}

template <typename T>
[[nodiscard]] inline T read_be_enum_adv(const std::uint8_t*& ptr) noexcept {
	T val = read_be_enum<T>(ptr);
	ptr += sizeof(T);
	return val;
}

} // namespace itch::util

#endif // TV_ITCH50_CPP_UTIL_HPP
