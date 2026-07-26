#ifndef TV_ITCH50_CPP_IOS_HPP
#define TV_ITCH50_CPP_IOS_HPP

#include "itch/spec/messages.hpp"

#include <cstdint>
#include <string>
#include <type_traits>

namespace itch::ios {

// Treats input as nanoseconds. Format: HH:MM:SS.NNNNNNNNN
std::string format_timestamp_ns(std::uint64_t ts);

// Treats input as seconds. Format: HH:MM:SS
std::string format_timestamp_sec(std::uint64_t ts);

// 4-byte prices have 4 decimal points, 8-byte prices have 8
template <typename T>
std::string format_price(const T value) {
	constexpr std::size_t decimals =
		std::is_same_v<T, std::uint32_t> ? 4 :
		std::is_same_v<T, std::uint64_t> ? 8 : 0;
	static_assert(decimals != 0, "format_price type must be uint32 or uint64");

	std::string s = std::to_string(value);
	if (s.size() <= decimals)
		s.insert(0, decimals - s.size() + 1, '0');
	s.insert(s.size() - decimals, ".");
	return s;
}

// Turns uint to left-justified string of chars, padded to the right with spaces.
template <typename T>
std::string to_str_padded(const T value) {

	static_assert(std::is_same_v<T, std::uint16_t> ||
	              std::is_same_v<T, std::uint32_t> ||
	              std::is_same_v<T, std::uint64_t>,
				  "to_str_padded type must be uint16, uint32 or uint64"
	);

	std::string s(sizeof(T), ' ');
	for (std::size_t i = 0; i < sizeof(T); ++i) {
		s[i] = static_cast<char>((value >> (8 * (sizeof(T) - i - 1))) & 0xFF);
	}
	return s;
}

std::string to_string(const spec::SystemEvent& m, const char sep = ',');

std::string to_string(const spec::StockDirectory& m, const char sep = ',');

std::string to_string(const spec::StockTradingAction& m, const char sep = ',');

std::string to_string(const spec::RegSHORestriction& m, const char sep = ',');

std::string to_string(const spec::MarketParticipantPosition& m, const char sep = ',');

std::string to_string(const spec::MWCBDeclineLevel& m, const char sep = ',');

std::string to_string(const spec::MWCBStatus& m, const char sep = ',');

std::string to_string(const spec::IPOQuotingPeriodUpdate& m, const char sep = ',');

std::string to_string(const spec::LULDAuctionCollar& m, const char sep = ',');

std::string to_string(const spec::OperationalHalt& m, const char sep = ',');

std::string to_string(const spec::AddOrder& m, const char sep = ',');

std::string to_string(const spec::AddOrderWithMPID& m, const char sep = ',');

std::string to_string(const spec::ExecuteOrder& m, const char sep = ',');

std::string to_string(const spec::ExecuteOrderWithPrice& m, const char sep = ',');

std::string to_string(const spec::CancelOrder& m, const char sep = ',');

std::string to_string(const spec::DeleteOrder& m, const char sep = ',');

std::string to_string(const spec::ReplaceOrder& m, const char sep = ',');

std::string to_string(const spec::NonCrossTrade& m, const char sep = ',');

std::string to_string(const spec::CrossTrade& m, const char sep = ',');

std::string to_string(const spec::BrokenTrade& m, const char sep = ',');

std::string to_string(const spec::NetOrderImbalance& m, const char sep = ',');

std::string to_string(const spec::RetailPriceImprovement& m, const char sep = ',');

std::string to_string(const spec::DLCRPriceDiscovery& m, const char sep = ',');

inline std::ostream& operator<<(std::ostream& out, const spec::SystemEvent& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::StockDirectory& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::StockTradingAction& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::RegSHORestriction& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::MarketParticipantPosition& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::MWCBDeclineLevel& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::MWCBStatus& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::IPOQuotingPeriodUpdate& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::LULDAuctionCollar& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::OperationalHalt& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::AddOrder& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::AddOrderWithMPID& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::ExecuteOrder& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::ExecuteOrderWithPrice& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::CancelOrder& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::DeleteOrder& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::ReplaceOrder& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::NonCrossTrade& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::CrossTrade& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::BrokenTrade& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::NetOrderImbalance& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::RetailPriceImprovement& m) {
	out << to_string(m);
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const spec::DLCRPriceDiscovery& m) {
	out << to_string(m);
	return out;
}

} // namespace itch::spec

#endif // TV_ITCH50_CPP_IOS_HPP
