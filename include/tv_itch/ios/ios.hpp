#ifndef TV_ITCH50_CPP_IOS_HPP
#define TV_ITCH50_CPP_IOS_HPP

#include "tv_itch/spec/alpha_fields.hpp"
#include "tv_itch/spec/messages.hpp"


#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>


namespace tv_itch::ios {
std::string format_timestamp_ns(std::uint64_t ts);


std::string format_timestamp_sec(std::uint64_t ts);


template <typename T>
std::string format_price(const T value, const std::uint8_t num_decimal_points) {
	static_assert(std::is_same_v<T, std::uint32_t> || std::is_same_v<T, std::uint64_t>,
		  "compile error: format_price must be called with uint32_t or uint64_t");

	std::string s = std::to_string(value);
	if (num_decimal_points >= s.size())
		s.insert(0, num_decimal_points - s.size() + 1, '0');

	s.insert(s.size() - num_decimal_points, ".");
	return s;
}


// For MPID, stock symbols, and certain enum classes with non-char underlying type
template <typename T>
std::string int_to_ascii_str(const T value) {
	static_assert(
		std::is_integral_v<T>,
		"compile error: int_to_ascii_str called with non-integral type");

	std::string s(sizeof(T), ' ');
	for (std::size_t i = 0; i < sizeof(T); ++i) {
		s[i] = static_cast<char>(
			( value >> ( 8 * (sizeof(T) - i - 1) ) ) & 0xFF
			);
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


std::string to_string(const spec::CrossTypeNOII t);


std::string to_string(const spec::PriceVariationPercentage t);


std::string to_string(const spec::InterestFlagRPII t);


std::string to_string(const spec::EligibleForTradingReleaseFlag t);


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
}


#endif