#include "tv_itch/spec/message_lengths.hpp"
#include "tv_itch/spec/alpha_fields.hpp"


#include <cstdlib>
#include <iostream>


namespace tv_itch::spec {
[[nodiscard]] inline constexpr std::uint16_t getMessageLength(const MessageType t) noexcept {
	using mt = MessageType;

	switch (t) {
	case mt::SystemEvent:               return 12;
	case mt::StockDirectory:            return 39;
	case mt::StockTradingAction:        return 25;
	case mt::RegSHORestriction:         return 20;
	case mt::MarketParticipantPosition: return 26;
	case mt::MWCBDeclineLevel:          return 35;
	case mt::MWCBStatus:                return 12;
	case mt::IPOQuotingPeriodUpdate:    return 28;
	case mt::LULDAuctionCollar:         return 35;
	case mt::OperationalHalt:           return 21;
	case mt::AddOrderWithoutMPID:       return 36;
	case mt::AddOrderWithMPID:          return 40;
	case mt::ExecuteOrder:              return 31;
	case mt::ExecuteOrderWithPrice:     return 36;
	case mt::CancelOrder:               return 23;
	case mt::DeleteOrder:               return 19;
	case mt::ReplaceOrder:              return 35;
	case mt::NonCrossTrade:             return 44;
	case mt::CrossTrade:                return 40;
	case mt::BrokenTrade:               return 19;
	case mt::NOII:                      return 50;
	case mt::RPII:                      return 20;
	case mt::DLCRPriceDiscovery:        return 48;
	default:
		std::cerr << "error: getMessageLength called with invalid MessageType of value "
				  << "'" << static_cast<char>(t) << "'"
				  << ". Aborting\n";
		std::abort();
	}
}
}