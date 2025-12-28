#ifndef TV_ITCH50_CPP_UTIL_HPP
#define TV_ITCH50_CPP_UTIL_HPP


#include <cstdint>
#include <cstdlib>


namespace tv_itch::util {
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
}


#endif