#ifndef TV_ITCH50_CPP_MESSAGES_HPP
#define TV_ITCH50_CPP_MESSAGES_HPP

#include "itch/util/util.hpp"

#include <cstdint>
#include <type_traits>

namespace itch::spec {

struct SystemEvent {
	std::uint64_t timestamp;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  event_code;
};

struct StockDirectory {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint32_t round_lot_size;
	std::uint32_t etp_leverage_factor;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint16_t issue_subtype;
	std::uint8_t  market_category;
	std::uint8_t  financial_status;
	std::uint8_t  is_round_lots_only;
	std::uint8_t  issue_classification;
	std::uint8_t  authenticity;
	std::uint8_t  short_sale_threshold;
	std::uint8_t  is_ipo;
	std::uint8_t  luld_ref_price_tier;
	std::uint8_t  is_etp;
	std::uint8_t  is_inverse_etp;
};

struct StockTradingAction {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint32_t trading_action_reason;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  trading_state;
	std::uint8_t  reserved; // A reserved field in the spec. Could be a padding thing.
};

struct RegSHORestriction {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint16_t stock_locate;   // Named "locate code" in spec. Decided to change back.
	std::uint16_t tracking_number;
	std::uint8_t  reg_sho_action;
};

struct MarketParticipantPosition {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint32_t mp_id;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  is_primary_market_maker;
	std::uint8_t  market_maker_mode;
	std::uint8_t  market_participant_state;
};

struct MWCBDeclineLevel {
	std::uint64_t timestamp;
	std::uint64_t price_level1; // Actual price = price / 10^8
	std::uint64_t price_level2; // Actual price = price / 10^8
	std::uint64_t price_level3; // Actual price = price / 10^8
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct MWCBStatus {
	std::uint64_t timestamp;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  breached_level;
};

struct IPOQuotingPeriodUpdate {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint32_t ipo_quotation_time; // Seconds since midnight, not nanoseconds.
	std::uint32_t ipo_price; // Actual Price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  ipo_quotation_release_flag; // If equal to 'C', quotation time and price equal zero.
};

struct LULDAuctionCollar {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint32_t reference_price; // Actual price = price / 10^4
	std::uint32_t upper_price;     // Actual price = price / 10^4
	std::uint32_t lower_price;     // Actual price = price / 10^4
	std::uint32_t number_of_extensions;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct OperationalHalt {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  market_code;
	std::uint8_t  operational_halt_action;
};

struct AddOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint64_t stock;
	std::uint32_t shares;
	std::uint32_t price; // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  side;
};

struct AddOrderWithMPID {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint64_t stock;
	std::uint32_t shares;
	std::uint32_t price; // Actual price = price / 10^4
	std::uint32_t mp_id;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  side;
};

struct ExecuteOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint64_t match_number;
	std::uint32_t executed_shares;
	std::uint32_t executed_price;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct ExecuteOrderWithPrice {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint64_t match_number;
	std::uint32_t executed_shares;
	std::uint32_t executed_price;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  is_printable;
};

struct CancelOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint32_t cancelled_shares;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct DeleteOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct ReplaceOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id_old;
	std::uint64_t order_id_new;
	std::uint32_t shares;
	std::uint32_t price; // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct NonCrossTrade {
	std::uint64_t timestamp;
	std::uint64_t order_id;   // Always zero since 06.12.2010 (DD.MM.YYYY)
	std::uint64_t stock;
	std::uint64_t match_number;
	std::uint32_t shares;
	std::uint32_t price;   // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  side; // Always 'B' since 14.07.2014 (DD.MM.YYYY)
};

struct CrossTrade {
	std::uint64_t timestamp;
	std::uint64_t shares;
	std::uint64_t stock;
	std::uint64_t match_number;
	std::uint32_t price;   // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  cross_type;
};

struct BrokenTrade {
	std::uint64_t timestamp;
	std::uint64_t match_number;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct NetOrderImbalance {
	std::uint64_t timestamp;
	std::uint64_t paired_shares;
	std::uint64_t imbalance_shares;
	std::uint64_t stock;
	std::uint32_t far_price;       // Actual price = price / 10^4
	std::uint32_t near_price;      // Actual price = price / 10^4
	std::uint32_t reference_price; // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  imbalance_direction;
	std::uint8_t  cross_type;
	std::uint8_t  price_variation_indicator;
};

struct RetailPriceImprovement {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  interest_flag;
};

struct DLCRPriceDiscovery {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint64_t near_execution_time; // Contacted NASDAQ; they said this is nanoseconds.
	std::uint32_t min_allowed_price;        // Actual price = price / 10^4
	std::uint32_t max_allowed_price;        // Actual price = price / 10^4
	std::uint32_t near_execution_price;     // Actual price = price / 10^4
	std::uint32_t lower_price_range_collar; // Actual price = price / 10^4
	std::uint32_t upper_price_range_collar; // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	std::uint8_t  is_eligible_for_trading_release;
};

static_assert(std::is_aggregate_v<SystemEvent>);
static_assert(std::is_aggregate_v<StockDirectory>);
static_assert(std::is_aggregate_v<StockTradingAction>);
static_assert(std::is_aggregate_v<RegSHORestriction>);
static_assert(std::is_aggregate_v<MarketParticipantPosition>);
static_assert(std::is_aggregate_v<MWCBDeclineLevel>);
static_assert(std::is_aggregate_v<MWCBStatus>);
static_assert(std::is_aggregate_v<IPOQuotingPeriodUpdate>);
static_assert(std::is_aggregate_v<LULDAuctionCollar>);
static_assert(std::is_aggregate_v<OperationalHalt>);
static_assert(std::is_aggregate_v<AddOrder>);
static_assert(std::is_aggregate_v<ExecuteOrder>);
static_assert(std::is_aggregate_v<CancelOrder>);
static_assert(std::is_aggregate_v<ReplaceOrder>);
static_assert(std::is_aggregate_v<NonCrossTrade>);
static_assert(std::is_aggregate_v<CrossTrade>);
static_assert(std::is_aggregate_v<BrokenTrade>);
static_assert(std::is_aggregate_v<NetOrderImbalance>);
static_assert(std::is_aggregate_v<RetailPriceImprovement>);
static_assert(std::is_aggregate_v<DLCRPriceDiscovery>);

} // namespace itch::spec

// Note: internal pointers always point to the zero'th byte (the message type) to match
// the offsets already given by the spec.
namespace itch::spec::view {

struct SystemEventView {

	const std::uint8_t* const base;

	std::uint16_t stock_locate() const noexcept {
		return util::read_be<std::uint16_t>(base + 1);
	}

	std::uint16_t tracking_number() const noexcept {
		return util::read_be<std::uint16_t>(base + 3);
	}

	std::uint64_t timestamp() const noexcept {
		return util::read_be_u48(base + 5);
	}

	std::uint8_t event_code() const noexcept {
		return util::read_be<std::uint8_t>(base + 11);
	}

	SystemEvent unbox() const noexcept {
		return {
			timestamp(),
			stock_locate(),
			tracking_number(),
			event_code()
		};
	}

}; // SystemEventView

struct StockDirectoryView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint8_t market_category() const noexcept {
        return util::read_be<std::uint8_t>(base + 19);
    }

    std::uint8_t financial_status() const noexcept {
        return util::read_be<std::uint8_t>(base + 20);
    }

    std::uint32_t round_lot_size() const noexcept {
        return util::read_be<std::uint32_t>(base + 21);
    }

    std::uint8_t is_round_lots_only() const noexcept {
        return util::read_be<std::uint8_t>(base + 25);
    }

    std::uint8_t issue_classification() const noexcept {
        return util::read_be<std::uint8_t>(base + 26);
    }

    std::uint16_t issue_subtype() const noexcept {
        return util::read_be<std::uint16_t>(base + 27);
    }

    std::uint8_t authenticity() const noexcept {
        return util::read_be<std::uint8_t>(base + 29);
    }

    std::uint8_t short_sale_threshold() const noexcept {
        return util::read_be<std::uint8_t>(base + 30);
    }

    std::uint8_t is_ipo() const noexcept {
        return util::read_be<std::uint8_t>(base + 31);
    }

    std::uint8_t luld_ref_price_tier() const noexcept {
        return util::read_be<std::uint8_t>(base + 32);
    }

    std::uint8_t is_etp() const noexcept {
        return util::read_be<std::uint8_t>(base + 33);
    }

    std::uint32_t etp_leverage_factor() const noexcept {
        return util::read_be<std::uint32_t>(base + 34);
    }

    std::uint8_t is_inverse_etp() const noexcept {
        return util::read_be<std::uint8_t>(base + 38);
    }

    StockDirectory unbox() const noexcept {
        return {
            timestamp(),
            stock(),
            round_lot_size(),
            etp_leverage_factor(),
            stock_locate(),
            tracking_number(),
            issue_subtype(),
            market_category(),
            financial_status(),
            is_round_lots_only(),
            issue_classification(),
            authenticity(),
            short_sale_threshold(),
            is_ipo(),
            luld_ref_price_tier(),
            is_etp(),
            is_inverse_etp()
        };
    }

}; // StockDirectoryView

struct StockTradingActionView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint8_t trading_state() const noexcept {
        return util::read_be<std::uint8_t>(base + 19);
    }

    std::uint8_t reserved() const noexcept {
        return util::read_be<std::uint8_t>(base + 20);
    }

    std::uint32_t trading_action_reason() const noexcept {
        return util::read_be<std::uint32_t>(base + 21);
    }

    StockTradingAction unbox() const noexcept {
        return {
            timestamp(),
            stock(),
            trading_action_reason(),
            stock_locate(),
            tracking_number(),
            trading_state(),
            reserved()
        };
    }

}; // StockTradingActionView

struct RegSHORestrictionView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint8_t reg_sho_action() const noexcept {
        return util::read_be<std::uint8_t>(base + 19);
    }

    RegSHORestriction unbox() const noexcept {
        return {
            timestamp(),
            stock(),
            stock_locate(),
            tracking_number(),
            reg_sho_action()
        };
    }

}; // RegSHORestrictionView

struct MarketParticipantPositionView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint32_t mp_id() const noexcept {
        return util::read_be<std::uint32_t>(base + 11);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 15);
    }

    std::uint8_t is_primary_market_maker() const noexcept {
        return util::read_be<std::uint8_t>(base + 23);
    }

    std::uint8_t market_maker_mode() const noexcept {
        return util::read_be<std::uint8_t>(base + 24);
    }

    std::uint8_t market_participant_state() const noexcept {
        return util::read_be<std::uint8_t>(base + 25);
    }

    MarketParticipantPosition unbox() const noexcept {
        return {
            timestamp(),
            stock(),
            mp_id(),
            stock_locate(),
            tracking_number(),
            is_primary_market_maker(),
            market_maker_mode(),
            market_participant_state()
        };
    }

}; // MarketParticipantPositionView

struct MWCBDeclineLevelView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t price_level1() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint64_t price_level2() const noexcept {
        return util::read_be<std::uint64_t>(base + 19);
    }

    std::uint64_t price_level3() const noexcept {
        return util::read_be<std::uint64_t>(base + 27);
    }

    MWCBDeclineLevel unbox() const noexcept {
        return {
            timestamp(),
            price_level1(),
            price_level2(),
            price_level3(),
            stock_locate(),
            tracking_number()
        };
    }

}; // MWCBDeclineLevelView

struct MWCBStatusView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint8_t breached_level() const noexcept {
        return util::read_be<std::uint8_t>(base + 11);
    }

    MWCBStatus unbox() const noexcept {
        return {
            timestamp(),
            stock_locate(),
            tracking_number(),
            breached_level()
        };
    }

}; // MWCBStatusView

struct IPOQuotingPeriodUpdateView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint32_t ipo_quotation_time() const noexcept {
        return util::read_be<std::uint32_t>(base + 19);
    }

    std::uint8_t ipo_quotation_release_qualifier() const noexcept {
        return util::read_be<std::uint8_t>(base + 23);
    }

    std::uint32_t ipo_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 24);
    }

    IPOQuotingPeriodUpdate unbox() const noexcept {
        return {
            timestamp(),
            stock(),
            ipo_quotation_time(),
            ipo_price(),
            stock_locate(),
            tracking_number(),
            ipo_quotation_release_qualifier()
        };
    }

}; // IPOQuotingPeriodUpdateView

struct LULDAuctionCollarView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint32_t reference_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 19);
    }

    std::uint32_t lower_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 23);
    }

    std::uint32_t upper_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 27);
    }

    std::uint32_t number_of_extensions() const noexcept {
        return util::read_be<std::uint32_t>(base + 31);
    }

    LULDAuctionCollar unbox() const noexcept {
        return {
            timestamp(),
            stock(),
            reference_price(),
            upper_price(),
            lower_price(),
            number_of_extensions(),
            stock_locate(),
            tracking_number()
        };
    }

}; // LULDAuctionCollarView

struct OperationalHaltView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint8_t market_code() const noexcept {
        return util::read_be<std::uint8_t>(base + 19);
    }

    std::uint8_t operational_halt_action() const noexcept {
        return util::read_be<std::uint8_t>(base + 20);
    }

    OperationalHalt unbox() const noexcept {
        return {
            timestamp(),
            stock(),
            stock_locate(),
            tracking_number(),
            market_code(),
            operational_halt_action()
        };
    }

}; // OperationalHaltView

struct AddOrderView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t order_id() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint8_t side() const noexcept {
        return util::read_be<std::uint8_t>(base + 19);
    }

    std::uint32_t shares() const noexcept {
        return util::read_be<std::uint32_t>(base + 20);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 24);
    }

    std::uint32_t price() const noexcept {
        return util::read_be<std::uint32_t>(base + 32);
    }

    AddOrder unbox() const noexcept {
        return {
            timestamp(),
            order_id(),
            stock(),
            shares(),
            price(),
            stock_locate(),
            tracking_number(),
            side()
        };
    }

}; // AddOrderView

struct AddOrderWithMPIDView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t order_id() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint8_t side() const noexcept {
        return util::read_be<std::uint8_t>(base + 19);
    }

    std::uint32_t shares() const noexcept {
        return util::read_be<std::uint32_t>(base + 20);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 24);
    }

    std::uint32_t price() const noexcept {
        return util::read_be<std::uint32_t>(base + 32);
    }

    std::uint32_t mp_id() const noexcept {
        return util::read_be<std::uint32_t>(base + 36);
    }

    AddOrderWithMPID unbox() const noexcept {
        return {
            timestamp(),
            order_id(),
            stock(),
            shares(),
            price(),
            mp_id(),
            stock_locate(),
            tracking_number(),
            side()
        };
    }

}; // AddOrderWithMPIDView

struct ExecuteOrderView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t order_id() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint32_t executed_shares() const noexcept {
        return util::read_be<std::uint32_t>(base + 19);
    }

    std::uint64_t match_number() const noexcept {
        return util::read_be<std::uint64_t>(base + 23);
    }

    ExecuteOrder unbox() const noexcept {
        return {
            timestamp(),
            order_id(),
            match_number(),
            executed_shares(),
            stock_locate(),
            tracking_number(),
        };
    }

}; // ExecuteOrderView

struct ExecuteOrderWithPriceView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t order_id() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint32_t executed_shares() const noexcept {
        return util::read_be<std::uint32_t>(base + 19);
    }

    std::uint64_t match_number() const noexcept {
        return util::read_be<std::uint64_t>(base + 23);
    }

    std::uint8_t is_printable() const noexcept {
        return util::read_be<std::uint8_t>(base + 31);
    }

    std::uint32_t executed_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 32);
    }

    ExecuteOrderWithPrice unbox() const noexcept {
        return {
            timestamp(),
            order_id(),
            match_number(),
            executed_shares(),
            executed_price(),
            stock_locate(),
            tracking_number(),
            is_printable()
        };
    }

}; // ExecuteOrderWithPriceView

struct CancelOrderView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t order_id() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint32_t cancelled_shares() const noexcept {
        return util::read_be<std::uint32_t>(base + 19);
    }

    CancelOrder unbox() const noexcept {
        return {
            timestamp(),
            order_id(),
            cancelled_shares(),
            stock_locate(),
            tracking_number(),
        };
    }

}; // CancelOrderView

struct DeleteOrderView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t order_id() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    DeleteOrder unbox() const noexcept {
        return {
            timestamp(),
            order_id(),
            stock_locate(),
            tracking_number()
        };
    }

}; // DeleteOrderView

struct ReplaceOrderView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t order_id_old() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint64_t order_id_new() const noexcept {
        return util::read_be<std::uint64_t>(base + 19);
    }

    std::uint32_t shares() const noexcept {
        return util::read_be<std::uint32_t>(base + 27);
    }

    std::uint32_t price() const noexcept {
        return util::read_be<std::uint32_t>(base + 31);
    }

    ReplaceOrder unbox() const noexcept {
        return {
            timestamp(),
            order_id_old(),
            order_id_new(),
            shares(),
            price(),
            stock_locate(),
            tracking_number()
        };
    }

}; // ReplaceOrderView

struct NonCrossTradeView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t order_id() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint8_t side() const noexcept {
        return util::read_be<std::uint8_t>(base + 19);
    }

    std::uint32_t shares() const noexcept {
        return util::read_be<std::uint32_t>(base + 20);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 24);
    }

    std::uint32_t price() const noexcept {
        return util::read_be<std::uint32_t>(base + 32);
    }

    std::uint64_t match_number() const noexcept {
        return util::read_be<std::uint64_t>(base + 36);
    }

    NonCrossTrade unbox() const noexcept {
        return {
            timestamp(),
            order_id(),
            stock(),
            match_number(),
            shares(),
            price(),
            stock_locate(),
            tracking_number(),
            side()
        };
    }

}; // NonCrossTradeView

struct CrossTradeView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t shares() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 19);
    }

    std::uint32_t price() const noexcept {
        return util::read_be<std::uint32_t>(base + 27);
    }

    std::uint64_t match_number() const noexcept {
        return util::read_be<std::uint64_t>(base + 31);
    }

    std::uint8_t cross_type() const noexcept {
        return util::read_be<std::uint8_t>(base + 39);
    }

    CrossTrade unbox() const noexcept {
        return {
            timestamp(),
            shares(),
            stock(),
            match_number(),
            price(),
            stock_locate(),
            tracking_number(),
            cross_type()
        };
    }

}; // CrossTradeView

struct BrokenTradeView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t match_number() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    BrokenTrade unbox() const noexcept {
        return {
            timestamp(),
            match_number(),
            stock_locate(),
            tracking_number()
        };
    }

}; // BrokenTradeView

struct NetOrderImbalanceView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t paired_shares() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint64_t imbalance_shares() const noexcept {
        return util::read_be<std::uint64_t>(base + 19);
    }

    std::uint8_t imbalance_direction() const noexcept {
        return util::read_be<std::uint8_t>(base + 27);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 28);
    }

    std::uint32_t far_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 36);
    }

    std::uint32_t near_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 40);
    }

    std::uint32_t reference_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 44);
    }

    std::uint8_t cross_type() const noexcept {
        return util::read_be<std::uint8_t>(base + 48);
    }

    std::uint8_t price_variation_indicator() const noexcept {
        return util::read_be<std::uint8_t>(base + 49);
    }

    NetOrderImbalance unbox() const noexcept {
        return {
            timestamp(),
            paired_shares(),
            imbalance_shares(),
            stock(),
            far_price(),
            near_price(),
            reference_price(),
            stock_locate(),
            tracking_number(),
            imbalance_direction(),
            cross_type(),
            price_variation_indicator()
        };
    }

}; // NetOrderImbalanceView

struct RetailPriceImprovementView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint8_t interest_flag() const noexcept {
        return util::read_be<std::uint8_t>(base + 19);
    }

    RetailPriceImprovement unbox() const noexcept {
        return {
            timestamp(),
            stock(),
            stock_locate(),
            tracking_number(),
            interest_flag()
        };
    }

}; // RetailPriceImprovementView

struct DLCRPriceDiscoveryView {

    const std::uint8_t* const base;

    std::uint16_t stock_locate() const noexcept {
        return util::read_be<std::uint16_t>(base + 1);
    }

    std::uint16_t tracking_number() const noexcept {
        return util::read_be<std::uint16_t>(base + 3);
    }

    std::uint64_t timestamp() const noexcept {
        return util::read_be_u48(base + 5);
    }

    std::uint64_t stock() const noexcept {
        return util::read_be<std::uint64_t>(base + 11);
    }

    std::uint8_t is_eligible_for_trading_release() const noexcept {
        return util::read_be<std::uint8_t>(base + 19);
    }

    std::uint32_t min_allowed_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 20);
    }

    std::uint32_t max_allowed_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 24);
    }

    std::uint32_t near_execution_price() const noexcept {
        return util::read_be<std::uint32_t>(base + 28);
    }

    std::uint64_t near_execution_time() const noexcept {
        return util::read_be<std::uint64_t>(base + 32);
    }

    std::uint32_t lower_price_range_collar() const noexcept {
        return util::read_be<std::uint32_t>(base + 40);
    }

    std::uint32_t upper_price_range_collar() const noexcept {
        return util::read_be<std::uint32_t>(base + 44);
    }

    DLCRPriceDiscovery unbox() const noexcept {
        return {
            timestamp(),
            stock(),
            near_execution_time(),
            min_allowed_price(),
            max_allowed_price(),
            near_execution_price(),
            lower_price_range_collar(),
            upper_price_range_collar(),
            stock_locate(),
            tracking_number(),
            is_eligible_for_trading_release()
        };
    }

}; // DLCRPriceDiscoveryView

} // namespace itch::spec::view

#endif // TV_ITCH50_CPP_MESSAGES_HPP
