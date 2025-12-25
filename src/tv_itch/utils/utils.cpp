#include "tv_itch/utils/utils.hpp"


#include <cstdint>
#include <cstdlib>


namespace tv_itch::utils {
std::uint16_t byte_swap_u16(const std::uint16_t value) noexcept {
#ifdef _MSC_VER
	return _byteswap_ushort(value);
#else
	return __builtin_bswap16(value);
#endif
}


std::uint32_t byte_swap_u32(const std::uint32_t value) noexcept {
#ifdef _MSC_VER
	return _byteswap_ulong(value);
#else
	return __builtin_bswap32(value);
#endif
}


std::uint64_t byte_swap_u64(const std::uint64_t value) noexcept {
#ifdef _MSC_VER
	return _byteswap_uint64(value);
#else
	return __builtin_bswap64(value);
#endif
}
}