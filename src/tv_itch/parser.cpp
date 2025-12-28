#include "tv_itch/parser.hpp"
#include "tv_itch/mmap/mmap.hpp"
#include "tv_itch/spec/alpha_fields.hpp"
#include "tv_itch/spec/messages.hpp"
#include "tv_itch/util/util.hpp"


#if defined(DEBUG) || defined(_DEBUG) || !defined(NDEBUG)
#define TV_ITCH50_CPP_DEBUG
#endif


#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>


namespace tv_itch {
Parser::Parser(const std::string& filename) noexcept
	: mmap(filename)
	, mmap_ptr(mmap.data())
	, mmap_end(mmap.data() + mmap.size()) {
	if (mmap.size() == 0) {
		// MemoryMap always checks if file is empty, so this would be unexpected.
		std::cerr << "fatal error: Parser found file to be empty despite previous assertions";
		std::abort();
	}
}

bool Parser::nextRecord() noexcept {
	if (is_eof) {
		return false;
	}

	current_record = parseNextMessage();
	if (mmap_ptr == mmap_end)
		is_eof = true;

	return true;
}

spec::MessageVariant Parser::parseNextMessage() noexcept {
	using mt = MessageType;

	const mt message_type = getMessageType();
	switch (message_type) {
	case mt::SystemEvent:               return parseSystemEvent();
	case mt::StockDirectory:            return parseStockDirectory();
	case mt::StockTradingAction:        return parseStockTradingAction();
	case mt::RegSHORestriction:         return parseRegSHORestriction();
	case mt::MarketParticipantPosition: return parseMarketParticipantPosition();
	case mt::MWCBDeclineLevel:          return parseMWCBDeclineLevel();
	case mt::MWCBStatus:                return parseMWCBStatus();
	case mt::IPOQuotingPeriodUpdate:    return parseIPOQuotingPeriodUpdate();
	case mt::LULDAuctionCollar:         return parseLULDAuctionCollar();
	case mt::OperationalHalt:           return parseOperationHalt();
	case mt::AddOrderWithoutMPID:       return parseAddOrder(false);
	case mt::AddOrderWithMPID:          return parseAddOrder(true);
	case mt::ExecuteOrder:              return parseExecuteOrder(false);
	case mt::ExecuteOrderWithPrice:     return parseExecuteOrder(true);
	case mt::CancelOrder:               return parseCancelOrder(false);
	case mt::DeleteOrder:               return parseCancelOrder(true);
	case mt::ReplaceOrder:              return parseReplaceOrder();
	case mt::NonCrossTrade:             return parseNonCrossTrade();
	case mt::CrossTrade:                return parseCrossTrade();
	case mt::BrokenTrade:               return parseBrokenTrade();
	case mt::NOII:                      return parseNOII();
	case mt::RPII:                      return parseRPII();
	case mt::DLCRPriceDiscovery:        return parseDLCRPriceDiscovery();
	default:
		std::cerr << "error: invalid message type found, of character "
		<< "'" << static_cast<char>(message_type) << "'"
		<< ". Aborting\n";
		std::abort();
	}
}

// In debug mode, finds message length and type by the first 3 bytes of the message and asserts that
// the length is correct. Outside debug mode, skips first 2 bytes and gets message type directly.
[[nodiscard]] spec::MessageType Parser::getMessageType() noexcept {
#ifdef TV_ITCH50_CPP_DEBUG
	const auto message_length = read_and_advance_u16();
	const auto message_type = readEnumAndAdvance<MessageType>();
	const auto canonical_length = spec::getMessageLength(message_type);

	if (message_length != canonical_length) {
		std::cerr << "error: message length of type "
				  << static_cast<char>(message_type)
				  << " is " << message_length
				  << ". Expected " << canonical_length
				  << ". Aborting\n";
		std::abort();
	}
	return message_type;

#else
	mmap_ptr += 2;
	return readEnumAndAdvance<spec::MessageType>();

#endif
}

[[nodiscard]] std::uint16_t Parser::read_and_advance_u16() noexcept {
	std::uint16_t value;
	std::memcpy(&value, mmap_ptr, 2);
	mmap_ptr += 2;

#ifdef TV_ITCH50_CPP_LITTLE_ENDIAN
	return util::byte_swap_u16(value);
#else
	return value;
#endif
}

[[nodiscard]] std::uint32_t Parser::read_and_advance_u32() noexcept {
	std::uint32_t value;
	std::memcpy(&value, mmap_ptr, 4);
	mmap_ptr += 4;

#ifdef TV_ITCH50_CPP_LITTLE_ENDIAN
	return util::byte_swap_u32(value);
#else
	return value;
#endif
}

[[nodiscard]] std::uint64_t Parser::read_and_advance_u64() noexcept {
	std::uint64_t value;
	std::memcpy(&value, mmap_ptr, 8);
	mmap_ptr += 8;

#ifdef TV_ITCH50_CPP_LITTLE_ENDIAN
	return util::byte_swap_u64(value);
#else
	return value;
#endif
}

[[nodiscard]] std::uint64_t Parser::read_and_advance_ts() noexcept {
	std::uint64_t value = 0;
	std::memcpy(&value, mmap_ptr, 6);
	mmap_ptr += 6;

#ifdef TV_ITCH50_CPP_LITTLE_ENDIAN
	value <<= 16;
	return util::byte_swap_u64(value);
#else
	return value;
#endif
}

spec::MessageVariant Parser::parseSystemEvent() noexcept {
	spec::SystemEvent message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.event_code = readEnumAndAdvance<spec::SystemEventCode>();

	return message;
}

spec::MessageVariant Parser::parseStockDirectory() noexcept {
	spec::StockDirectory message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.stock = read_and_advance_u64();
	message.market_category = readEnumAndAdvance<spec::MarketCategory>();
	message.financial_status = readEnumAndAdvance<spec::FinancialStatus>();
	message.round_lot_size = read_and_advance_u32();
	message.is_round_lots_only = readEnumAndAdvance<spec::RoundLotsOnlyFlag>();
	message.issue_classification = readEnumAndAdvance<spec::IssueClassification>();
	message.issue_subtype = static_cast<spec::IssueSubType>(
		read_and_advance_u16());   // This enum is of underlying type uint16_t , not char
	message.authenticity = readEnumAndAdvance<spec::Authenticity>();
	message.short_sale_threshold = readEnumAndAdvance<spec::ShortSaleThreshold>();
	message.is_ipo = readEnumAndAdvance<spec::IPOFlag>();
	message.luld_ref_price_tier = readEnumAndAdvance<spec::LULDRefPriceTier>();
	message.is_etp = readEnumAndAdvance<spec::ETPFlag>();
	message.etp_leverage_factor = read_and_advance_u32();
	message.is_inverse_etp = readEnumAndAdvance<spec::InverseETPFlag>();

	return message;
}

spec::MessageVariant Parser::parseStockTradingAction() noexcept {
	spec::StockTradingAction message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.stock = read_and_advance_u64();
	message.trading_state = readEnumAndAdvance<spec::StockTradingState>();
	// The infamous "reserved" field. Noone knows why it's there. I still choose to save it
	message.reserved = *(mmap_ptr++);
	message.trading_action_reason = static_cast<spec::TradingActionReason>(
		read_and_advance_u32());   // This enum is of underlying type uint32_t , not char

	return message;
}

spec::MessageVariant Parser::parseRegSHORestriction() noexcept {
	spec::RegSHORestriction message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.stock = read_and_advance_u64();
	message.reg_sho_action = readEnumAndAdvance<spec::RegSHOAction>();

	return message;
}

spec::MessageVariant Parser::parseMarketParticipantPosition() noexcept {
	spec::MarketParticipantPosition message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.mp_id = read_and_advance_u32();
	message.stock = read_and_advance_u64();
	message.is_primary_market_maker = readEnumAndAdvance<spec::PrimaryMarketMakerFlag>();
	message.market_maker_mode = readEnumAndAdvance<spec::MarketMakerMode>();
	message.market_participant_state = readEnumAndAdvance<spec::MarketParticipantState>();

	return message;
}

spec::MessageVariant Parser::parseMWCBDeclineLevel() noexcept {
	spec::MWCBDeclineLevel message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.price_level1 = read_and_advance_u64();
	message.price_level2 = read_and_advance_u64();
	message.price_level3 = read_and_advance_u64();

	return message;
}

spec::MessageVariant Parser::parseMWCBStatus() noexcept {
	spec::MWCBStatus message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.breached_level = readEnumAndAdvance<spec::MWCBBreachLevel>();

	return message;
}

spec::MessageVariant Parser::parseIPOQuotingPeriodUpdate() noexcept {
	spec::IPOQuotingPeriodUpdate message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.stock = read_and_advance_u64();
	message.ipo_quotation_time = read_and_advance_u32();
	message.ipo_quotation_release_qualifier =
		readEnumAndAdvance<spec::IPOQuotationReleaseQualifier>();
	message.ipo_price = read_and_advance_u32();

	return message;
}

spec::MessageVariant Parser::parseLULDAuctionCollar() noexcept {
	spec::LULDAuctionCollar message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.stock = read_and_advance_u64();
	message.reference_price = read_and_advance_u32();
	message.lower_price = read_and_advance_u32();
	message.upper_price = read_and_advance_u32();
	message.number_of_extensions = read_and_advance_u32();

	return message;
}

spec::MessageVariant Parser::parseOperationHalt() noexcept {
	spec::OperationalHalt message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.stock = read_and_advance_u64();
	message.market_code = readEnumAndAdvance<spec::MarketCode>();
	message.operational_halt_action = readEnumAndAdvance<spec::OperationalHaltAction>();

	return message;
}

spec::MessageVariant Parser::parseAddOrder(const bool with_mp_id) noexcept {
	spec::AddOrder message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.order_id = read_and_advance_u64();
	message.side = readEnumAndAdvance<spec::Side>();
	message.shares = read_and_advance_u32();
	message.stock = read_and_advance_u64();
	message.price = read_and_advance_u32();
	message.mp_id = (with_mp_id) ? read_and_advance_u32()
								 : spec::DEFAULT_NON_ATTRIBUTED_MPID;

	return message;
}

spec::MessageVariant Parser::parseExecuteOrder(const bool with_price) noexcept {
	spec::ExecuteOrder message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.order_id = read_and_advance_u64();
	message.executed_shares = read_and_advance_u32();
	message.match_number = read_and_advance_u64();
	if (with_price) {
		message.is_printable = readEnumAndAdvance<spec::PrintableFlag>();
		message.executed_price = read_and_advance_u32();
	} else {
		message.is_printable = spec::PrintableFlag::Printable;
		message.executed_price = 0;
	}

	return message;
}

spec::MessageVariant Parser::parseCancelOrder(const bool is_delete_order) noexcept {
	spec::CancelOrder message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.order_id = read_and_advance_u64();
	message.cancelled_shares = (is_delete_order) ? 0 : read_and_advance_u32();

	return message;
}

spec::MessageVariant Parser::parseReplaceOrder() noexcept {
	spec::ReplaceOrder message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.order_id_old = read_and_advance_u64();
	message.order_id_new = read_and_advance_u64();
	message.shares = read_and_advance_u32();
	message.price = read_and_advance_u32();

	return message;
}

spec::MessageVariant Parser::parseNonCrossTrade() noexcept {
	spec::NonCrossTrade message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.order_id = read_and_advance_u64();
	message.side = readEnumAndAdvance<spec::Side>();
	message.shares = read_and_advance_u32();
	message.stock = read_and_advance_u64();
	message.price = read_and_advance_u32();
	message.match_number = read_and_advance_u64();

	return message;
}

spec::MessageVariant Parser::parseCrossTrade() noexcept {
	spec::CrossTrade message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.shares = read_and_advance_u64();
	message.stock = read_and_advance_u64();
	message.price = read_and_advance_u32();
	message.match_number = read_and_advance_u64();
	message.cross_type = readEnumAndAdvance<spec::CrossType>();

	return message;
}

spec::MessageVariant Parser::parseBrokenTrade() noexcept {
	spec::BrokenTrade message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.match_number = read_and_advance_u64();

	return message;
}

spec::MessageVariant Parser::parseNOII() noexcept {
	spec::NOII message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.paired_shares = read_and_advance_u64();
	message.imbalance_shares = read_and_advance_u64();
	message.imbalance_direction = readEnumAndAdvance<spec::ImbalanceDirection>();
	message.stock = read_and_advance_u64();
	message.far_price = read_and_advance_u32();
	message.near_price = read_and_advance_u32();
	message.reference_price = read_and_advance_u32();
	message.cross_type = readEnumAndAdvance<spec::CrossTypeNOII>();
	message.price_variation_indicator = readEnumAndAdvance<spec::PriceVariationPercentage>();

	return message;
}

spec::MessageVariant Parser::parseRPII() noexcept {
	spec::RPII message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.stock = read_and_advance_u64();
	message.interest_flag = readEnumAndAdvance<spec::InterestFlagRPII>();

	return message;
}

spec::MessageVariant Parser::parseDLCRPriceDiscovery() noexcept {
	spec::DLCRPriceDiscovery message;

	message.stock_locate = read_and_advance_u16();
	message.tracking_number = read_and_advance_u16();
	message.timestamp = read_and_advance_ts();
	message.stock = read_and_advance_u64();
	message.is_eligible_for_trading_release =
		readEnumAndAdvance<spec::EligibleForTradingReleaseFlag>();
	message.min_allowed_price = read_and_advance_u32();
	message.max_allowed_price = read_and_advance_u32();
	message.near_execution_price = read_and_advance_u32();
	message.near_execution_time = read_and_advance_u64();
	message.lower_price_range_collar = read_and_advance_u32();
	message.upper_price_range_collar = read_and_advance_u32();

	return message;
}
}