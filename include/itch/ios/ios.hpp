#ifndef TV_ITCH50_CPP_IOS_HPP
#define TV_ITCH50_CPP_IOS_HPP

#include "itch/spec/alpha_fields.hpp"
#include "itch/spec/messages.hpp"

#include <cstdint>
#include <string>
#include <type_traits>

namespace itch::ios {

template <typename T>
std::string enum_8b_to_str(T e) {
	static_assert(std::is_enum_v<T> && sizeof(T) == 1);
	return std::string(1, static_cast<unsigned char>(e));
}

// Format: HH:MM:SS.NNNNNNNNN
std::string format_timestamp_ns(std::uint64_t ts);

// Format: HH:MM:SS
std::string format_timestamp_sec(std::uint64_t ts);

// 4-byte prices have 4 decimal points, 8-byte prices have 8.
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

// Turns uint to string of chars, padded to the right with spaces as in spec.
template <typename T>
std::string to_str_padded(const T value) {

	static_assert(std::is_same_v<T, std::uint16_t> ||
	              std::is_same_v<T, std::uint32_t> ||
	              std::is_same_v<T, std::uint64_t>);

	std::string s(sizeof(T), ' ');
	for (std::size_t i = 0; i < sizeof(T); ++i) {
		s[i] = static_cast<char>((value >> (8 * (sizeof(T) - i - 1))) & 0xFF);
	}
	return s;
}

std::string to_string(const spec::MessageType t);

std::string to_string(const spec::Side t);

std::string to_string(const spec::SystemEventCode t);

std::string to_string(const spec::MarketCategory t);

std::string to_string(const spec::FinancialStatus t);

std::string to_string(const spec::RoundLotsOnlyFlag t);

std::string to_string(const spec::IssueClassification t);

std::string to_string(const spec::IssueSubType t);

std::string to_string(const spec::Authenticity t);

std::string to_string(const spec::ShortSaleThreshold t);

std::string to_string(const spec::IPOFlag t);

std::string to_string(const spec::LULDRefPriceTier t);

std::string to_string(const spec::ETPFlag t);

std::string to_string(const spec::InverseETPFlag t);

std::string to_string(const spec::StockTradingState t);

std::string to_string(const spec::TradingActionReason t);

std::string to_string(const spec::RegSHOAction t);

std::string to_string(const spec::PrimaryMarketMakerFlag t);

std::string to_string(const spec::MarketMakerMode t);

std::string to_string(const spec::MarketParticipantState t);

std::string to_string(const spec::MWCBBreachLevel t);

std::string to_string(const spec::IPOQuotationReleaseQualifier t);

std::string to_string(const spec::MarketCode t);

std::string to_string(const spec::OperationalHaltAction t);

std::string to_string(const spec::PrintableFlag t);

std::string to_string(const spec::CrossType t);

std::string to_string(const spec::ImbalanceDirection t);

std::string to_string(const spec::PriceVariationPercentage t);

std::string to_string(const spec::InterestFlagRPII t);

std::string to_string(const spec::EligibleForTradingReleaseFlag t);

std::string to_string(const spec::SystemEvent& m);

std::string to_string(const spec::StockDirectory& m);

std::string to_string(const spec::StockTradingAction& m);

std::string to_string(const spec::RegSHORestriction& m);

std::string to_string(const spec::MarketParticipantPosition& m);

std::string to_string(const spec::MWCBDeclineLevel& m);

std::string to_string(const spec::MWCBStatus& m);

std::string to_string(const spec::IPOQuotingPeriodUpdate& m);

std::string to_string(const spec::LULDAuctionCollar& m);

std::string to_string(const spec::OperationalHalt& m);

std::string to_string(const spec::AddOrder& m);

std::string to_string(const spec::ExecuteOrder& m);

std::string to_string(const spec::CancelOrder& m);

std::string to_string(const spec::ReplaceOrder& m);

std::string to_string(const spec::NonCrossTrade& m);

std::string to_string(const spec::CrossTrade& m);

std::string to_string(const spec::BrokenTrade& m);

std::string to_string(const spec::NOII& m);

std::string to_string(const spec::RPII& m);

std::string to_string(const spec::DLCRPriceDiscovery& m);

std::string to_string(const spec::MessageVariant& mv);

std::ostream& operator<<(std::ostream& out, const spec::SystemEvent& m);

std::ostream& operator<<(std::ostream& out, const spec::StockDirectory& m);

std::ostream& operator<<(std::ostream& out, const spec::StockTradingAction& m);

std::ostream& operator<<(std::ostream& out, const spec::RegSHORestriction& m);

std::ostream& operator<<(std::ostream& out, const spec::MarketParticipantPosition& m);

std::ostream& operator<<(std::ostream& out, const spec::MWCBDeclineLevel& m);

std::ostream& operator<<(std::ostream& out, const spec::MWCBStatus& m);

std::ostream& operator<<(std::ostream& out, const spec::IPOQuotingPeriodUpdate& m);

std::ostream& operator<<(std::ostream& out, const spec::LULDAuctionCollar& m);

std::ostream& operator<<(std::ostream& out, const spec::OperationalHalt& m);

std::ostream& operator<<(std::ostream& out, const spec::AddOrder& m);

std::ostream& operator<<(std::ostream& out, const spec::ExecuteOrder& m);

std::ostream& operator<<(std::ostream& out, const spec::CancelOrder& m);

std::ostream& operator<<(std::ostream& out, const spec::ReplaceOrder& m);

std::ostream& operator<<(std::ostream& out, const spec::NonCrossTrade& m);

std::ostream& operator<<(std::ostream& out, const spec::CrossTrade& m);

std::ostream& operator<<(std::ostream& out, const spec::BrokenTrade& m);

std::ostream& operator<<(std::ostream& out, const spec::NOII& m);

std::ostream& operator<<(std::ostream& out, const spec::RPII& m);

std::ostream& operator<<(std::ostream& out, const spec::DLCRPriceDiscovery& m);

std::ostream& operator<<(std::ostream& out, const spec::MessageVariant& mv);

} // namespace itch::spec

#endif // TV_ITCH50_CPP_IOS_HPP
