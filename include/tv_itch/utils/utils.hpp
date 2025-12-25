#ifndef TV_ITCH50_CPP_UTILS_HPP
#define TV_ITCH50_CPP_UTILS_HPP


#include <cstdint>


namespace tv_itch::utils {
std::uint16_t byte_swap_u16(const std::uint16_t value) noexcept;


std::uint32_t byte_swap_u32(const std::uint32_t value) noexcept;


std::uint64_t byte_swap_u64(const std::uint64_t value) noexcept;
}


#endif