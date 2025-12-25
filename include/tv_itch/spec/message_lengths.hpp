#ifndef TV_ITCH50_CPP_MESSAGE_LENGTHS_HPP
#define TV_ITCH50_CPP_MESSAGE_LENGTHS_HPP


#include "alpha_fields.hpp"


namespace tv_itch::spec {
[[nodiscard]] inline constexpr std::uint16_t getMessageLength(const MessageType t) noexcept;
}


#endif //TV_ITCH50_CPP_MESSAGE_LENGTHS_HPP