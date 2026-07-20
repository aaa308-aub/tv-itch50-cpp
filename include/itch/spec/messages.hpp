#ifndef TV_ITCH50_CPP_MESSAGES_HPP
#define TV_ITCH50_CPP_MESSAGES_HPP

#include "alpha_fields.hpp"
#include "itch/util/util.hpp"

#include <cstdint>
#include <type_traits>
#include <variant>

namespace itch::spec {

inline constexpr std::uint32_t DEFAULT_NON_ATTRIBUTED_MPID = 0x4E534451; // "NSDQ"

struct SystemEvent {
	std::uint64_t timestamp;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	SystemEventCode event_code;
};

struct StockDirectory {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint32_t round_lot_size;
	std::uint32_t etp_leverage_factor;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	IssueSubType issue_subtype;
	MarketCategory market_category;
	FinancialStatus financial_status;
	RoundLotsOnlyFlag is_round_lots_only;
	IssueClassification issue_classification;
	Authenticity authenticity;
	ShortSaleThreshold short_sale_threshold;
	IPOFlag is_ipo;
	LULDRefPriceTier luld_ref_price_tier;
	ETPFlag is_etp;
	InverseETPFlag is_inverse_etp;
};

struct StockTradingAction {
	std::uint64_t timestamp;
	std::uint64_t stock;
	TradingActionReason trading_action_reason;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	StockTradingState trading_state;
	// The spec doesn't say what reserved means. Just describes it as "Reserved." Could be a padding thing.
	std::uint8_t reserved;
};

struct RegSHORestriction {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint16_t stock_locate;   // Spec named it "locate code" for this message. Decided to change back.
	std::uint16_t tracking_number;
	RegSHOAction reg_sho_action;
};

struct MarketParticipantPosition {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint32_t mp_id;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	PrimaryMarketMakerFlag is_primary_market_maker;
	MarketMakerMode market_maker_mode;
	MarketParticipantState market_participant_state;
};

struct MWCBDeclineLevel {
	std::uint64_t timestamp;
	// For the prices below, actual price = price / 10^8
	std::uint64_t price_level1;
	std::uint64_t price_level2;
	std::uint64_t price_level3;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct MWCBStatus {
	std::uint64_t timestamp;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	MWCBBreachLevel breached_level;
};

struct IPOQuotingPeriodUpdate {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint32_t ipo_quotation_time;
	std::uint32_t ipo_price;   // Actual Price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	// If qualifier below is set to CanceledOrPostponed ('C'), ipo_quotation_time and ipo_price = 0
	IPOQuotationReleaseQualifier ipo_quotation_release_qualifier;
};

struct LULDAuctionCollar {
	std::uint64_t timestamp;
	std::uint64_t stock;
	// For the prices below, actual price = price / 10^4
	std::uint32_t reference_price;
	std::uint32_t upper_price;
	std::uint32_t lower_price;
	std::uint32_t number_of_extensions;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct OperationalHalt {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	MarketCode market_code;
	OperationalHaltAction operational_halt_action;
};

// AddOrder struct is for both with or without MPID attribution.
struct AddOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint64_t stock;
	std::uint32_t shares;
	std::uint32_t price;   // Actual Price = price / 10^4
	std::uint32_t mp_id;   // Default = "NSDQ" for Add Order messages without MPID attribution.
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	Side side;
};

// ExecuteOrder struct is for both with or without different execution price.
struct ExecuteOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint64_t match_number;
	std::uint32_t executed_shares;
	std::uint32_t executed_price;   // If 0, implies a normal Execute Order message.
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	PrintableFlag is_printable;   // Always Printable/'Y' for normal Execute Order messages.
};

// CancelOrder struct is for both cancel order messages and delete order messages.
struct CancelOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint32_t cancelled_shares;   // If cancelled_shares = 0, delete the order.
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct ReplaceOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id_old;   // The order_id of the old order to be removed from the order book.
	std::uint64_t order_id_new;   // The order_id of the new order to be added to the order book.
	std::uint32_t shares;
	std::uint32_t price;   // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct NonCrossTrade {
	std::uint64_t timestamp;
	std::uint64_t order_id;   // Effective 06.12.2010, this field should always be 0.
	std::uint64_t stock;
	std::uint64_t match_number;
	std::uint32_t shares;
	std::uint32_t price;   // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	Side side;   // Effective 14.07.2014, this field should always be Buy / 'B'.
};

struct CrossTrade {
	std::uint64_t timestamp;
	std::uint64_t shares;
	std::uint64_t stock;
	std::uint64_t match_number;
	std::uint32_t price;   // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	CrossType cross_type;
};

struct BrokenTrade {
	std::uint64_t timestamp;
	std::uint64_t match_number;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};

struct NOII {
	std::uint64_t timestamp;
	std::uint64_t paired_shares;
	std::uint64_t imbalance_shares;
	std::uint64_t stock;
	// For the prices below, actual price = price / 10^4
	std::uint32_t far_price;
	std::uint32_t near_price;
	std::uint32_t reference_price;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	ImbalanceDirection imbalance_direction;
	CrossType cross_type;
	PriceVariationPercentage price_variation_indicator;
};

struct RPII {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	InterestFlagRPII interest_flag;
};

struct DLCRPriceDiscovery {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint64_t near_execution_time;
	// For the prices below, actual price = price / 10^4
	std::uint32_t min_allowed_price;
	std::uint32_t max_allowed_price;
	std::uint32_t near_execution_price;
	std::uint32_t lower_price_range_collar;
	std::uint32_t upper_price_range_collar;
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	EligibleForTradingReleaseFlag is_eligible_for_trading_release;
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
static_assert(std::is_aggregate_v<NOII>);
static_assert(std::is_aggregate_v<RPII>);
static_assert(std::is_aggregate_v<DLCRPriceDiscovery>);

using MessageVariant = std::variant<
	SystemEvent,
	StockDirectory,
	StockTradingAction,
	RegSHORestriction,
	MarketParticipantPosition,
	MWCBDeclineLevel,
	MWCBStatus,
	IPOQuotingPeriodUpdate,
	LULDAuctionCollar,
	OperationalHalt,
	AddOrder,
	ExecuteOrder,
	CancelOrder,
	ReplaceOrder,
	NonCrossTrade,
	CrossTrade,
	BrokenTrade,
	NOII,
	RPII,
	DLCRPriceDiscovery
>;

} // namespace itch::spec

// Note: internal pointers always point to the zero'th byte (the message type) even
// though the type is never parsed by these viewers. Just for convention, and to match
// the offsets already given by the spec.
namespace itch::spec::view {

	struct SystemEventView {

		const std::uint8_t* const base;

		auto stock_locate() const noexcept {
			return util::read_be<std::uint16_t>(base + 1);
		}

		auto tracking_number() const noexcept {
			return util::read_be<std::uint16_t>(base + 3);
		}

		auto timestamp() const noexcept {
			return util::read_be_48b(base + 5);
		}

		auto event_code() const noexcept {
			return util::read_be_enum<SystemEventCode>(base + 11);
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
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t stock() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    MarketCategory market_category() const noexcept {
	        return util::read_be_enum<MarketCategory>(base + 19);
	    }

	    FinancialStatus financial_status() const noexcept {
	        return util::read_be_enum<FinancialStatus>(base + 20);
	    }

	    std::uint32_t round_lot_size() const noexcept {
	        return util::read_be<std::uint32_t>(base + 21);
	    }

	    RoundLotsOnlyFlag is_round_lots_only() const noexcept {
	        return util::read_be_enum<RoundLotsOnlyFlag>(base + 25);
	    }

	    IssueClassification issue_classification() const noexcept {
	        return util::read_be_enum<IssueClassification>(base + 26);
	    }

	    IssueSubType issue_subtype() const noexcept {
	        return util::read_be_enum<IssueSubType>(base + 27);
	    }

	    Authenticity authenticity() const noexcept {
	        return util::read_be_enum<Authenticity>(base + 29);
	    }

	    ShortSaleThreshold short_sale_threshold() const noexcept {
	        return util::read_be_enum<ShortSaleThreshold>(base + 30);
	    }

	    IPOFlag is_ipo() const noexcept {
	        return util::read_be_enum<IPOFlag>(base + 31);
	    }

	    LULDRefPriceTier luld_ref_price_tier() const noexcept {
	        return util::read_be_enum<LULDRefPriceTier>(base + 32);
	    }

	    ETPFlag is_etp() const noexcept {
	        return util::read_be_enum<ETPFlag>(base + 33);
	    }

	    std::uint32_t etp_leverage_factor() const noexcept {
	        return util::read_be<std::uint32_t>(base + 34);
	    }

	    InverseETPFlag is_inverse_etp() const noexcept {
	        return util::read_be_enum<InverseETPFlag>(base + 38);
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
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t stock() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    StockTradingState trading_state() const noexcept {
	        return util::read_be_enum<StockTradingState>(base + 19);
	    }

	    std::uint8_t reserved() const noexcept {
	        return util::read_be<std::uint8_t>(base + 20);
	    }

	    TradingActionReason trading_action_reason() const noexcept {
	        return util::read_be_enum<TradingActionReason>(base + 21);
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
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t stock() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    RegSHOAction reg_sho_action() const noexcept {
	        return util::read_be_enum<RegSHOAction>(base + 15);
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
	        return util::read_be_48b(base + 5);
	    }

	    std::uint32_t mp_id() const noexcept {
	        return util::read_be<std::uint32_t>(base + 11);
	    }

	    std::uint64_t stock() const noexcept {
	        return util::read_be<std::uint64_t>(base + 15);
	    }

	    PrimaryMarketMakerFlag is_primary_market_maker() const noexcept {
	        return util::read_be_enum<PrimaryMarketMakerFlag>(base + 23);
	    }

	    MarketMakerMode market_maker_mode() const noexcept {
	        return util::read_be_enum<MarketMakerMode>(base + 24);
	    }

	    MarketParticipantState market_participant_state() const noexcept {
	        return util::read_be_enum<MarketParticipantState>(base + 25);
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
	        return util::read_be_48b(base + 5);
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
	        return util::read_be_48b(base + 5);
	    }

	    MWCBBreachLevel breached_level() const noexcept {
	        return util::read_be_enum<MWCBBreachLevel>(base + 11);
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
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t stock() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    std::uint32_t ipo_quotation_time() const noexcept {
	        return util::read_be<std::uint32_t>(base + 19);
	    }

	    IPOQuotationReleaseQualifier ipo_quotation_release_qualifier() const noexcept {
	        return util::read_be_enum<IPOQuotationReleaseQualifier>(base + 23);
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
	        return util::read_be_48b(base + 5);
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
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t stock() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    MarketCode market_code() const noexcept {
	        return util::read_be_enum<MarketCode>(base + 19);
	    }

	    OperationalHaltAction operational_halt_action() const noexcept {
	        return util::read_be_enum<OperationalHaltAction>(base + 20);
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
	    const bool with_mp_id;

	    std::uint16_t stock_locate() const noexcept {
	        return util::read_be<std::uint16_t>(base + 1);
	    }

	    std::uint16_t tracking_number() const noexcept {
	        return util::read_be<std::uint16_t>(base + 3);
	    }

	    std::uint64_t timestamp() const noexcept {
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t order_id() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    Side side() const noexcept {
	        return util::read_be_enum<Side>(base + 19);
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
	        return with_mp_id ?
				util::read_be<std::uint32_t>(base + 36) :
				spec::DEFAULT_NON_ATTRIBUTED_MPID;
	    }

	    AddOrder unbox() const noexcept {
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

	}; // AddOrderView

	struct ExecuteOrderView {

	    const std::uint8_t* const base;
	    const bool with_price;

	    std::uint16_t stock_locate() const noexcept {
	        return util::read_be<std::uint16_t>(base + 1);
	    }

	    std::uint16_t tracking_number() const noexcept {
	        return util::read_be<std::uint16_t>(base + 3);
	    }

	    std::uint64_t timestamp() const noexcept {
	        return util::read_be_48b(base + 5);
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

	    PrintableFlag is_printable() const noexcept {
	        return with_price ? util::read_be_enum<PrintableFlag>(base + 31) : PrintableFlag::Printable;
	    }

	    std::uint32_t executed_price() const noexcept {
	        return with_price ? util::read_be<std::uint32_t>(base + 32) : 0;
	    }

	    ExecuteOrder unbox() const noexcept {
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

	}; // ExecuteOrderView

	struct CancelOrderView {

	    const std::uint8_t* const base;
	    const bool is_delete_order;

	    std::uint16_t stock_locate() const noexcept {
	        return util::read_be<std::uint16_t>(base + 1);
	    }

	    std::uint16_t tracking_number() const noexcept {
	        return util::read_be<std::uint16_t>(base + 3);
	    }

	    std::uint64_t timestamp() const noexcept {
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t order_id() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    std::uint32_t cancelled_shares() const noexcept {
	        return is_delete_order ? 0 : util::read_be<std::uint32_t>(base + 19);
	    }

	    CancelOrder unbox() const noexcept {
	        return {
	            timestamp(),
	            order_id(),
	            cancelled_shares(),
	            stock_locate(),
	            tracking_number()
	        };
	    }

	}; // CancelOrderView

	struct ReplaceOrderView {

	    const std::uint8_t* const base;

	    std::uint16_t stock_locate() const noexcept {
	        return util::read_be<std::uint16_t>(base + 1);
	    }

	    std::uint16_t tracking_number() const noexcept {
	        return util::read_be<std::uint16_t>(base + 3);
	    }

	    std::uint64_t timestamp() const noexcept {
	        return util::read_be_48b(base + 5);
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
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t order_id() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    Side side() const noexcept {
	        return util::read_be_enum<Side>(base + 19);
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
	        return util::read_be_48b(base + 5);
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

	    CrossType cross_type() const noexcept {
	        return util::read_be_enum<CrossType>(base + 39);
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
	        return util::read_be_48b(base + 5);
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

	struct NOIIView {

	    const std::uint8_t* const base;

	    std::uint16_t stock_locate() const noexcept {
	        return util::read_be<std::uint16_t>(base + 1);
	    }

	    std::uint16_t tracking_number() const noexcept {
	        return util::read_be<std::uint16_t>(base + 3);
	    }

	    std::uint64_t timestamp() const noexcept {
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t paired_shares() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    std::uint64_t imbalance_shares() const noexcept {
	        return util::read_be<std::uint64_t>(base + 19);
	    }

	    ImbalanceDirection imbalance_direction() const noexcept {
	        return util::read_be_enum<ImbalanceDirection>(base + 27);
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

	    CrossType cross_type() const noexcept {
	        return util::read_be_enum<CrossType>(base + 48);
	    }

	    PriceVariationPercentage price_variation_indicator() const noexcept {
	        return util::read_be_enum<PriceVariationPercentage>(base + 49);
	    }

	    NOII unbox() const noexcept {
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

	}; // NOIIView

	struct RPIIView {

	    const std::uint8_t* const base;

	    std::uint16_t stock_locate() const noexcept {
	        return util::read_be<std::uint16_t>(base + 1);
	    }

	    std::uint16_t tracking_number() const noexcept {
	        return util::read_be<std::uint16_t>(base + 3);
	    }

	    std::uint64_t timestamp() const noexcept {
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t stock() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    InterestFlagRPII interest_flag() const noexcept {
	        return util::read_be_enum<InterestFlagRPII>(base + 19);
	    }

	    RPII unbox() const noexcept {
	        return {
	            timestamp(),
	            stock(),
	            stock_locate(),
	            tracking_number(),
	            interest_flag()
	        };
	    }

	}; // RPIIView

	struct DLCRPriceDiscoveryView {

	    const std::uint8_t* const base;

	    std::uint16_t stock_locate() const noexcept {
	        return util::read_be<std::uint16_t>(base + 1);
	    }

	    std::uint16_t tracking_number() const noexcept {
	        return util::read_be<std::uint16_t>(base + 3);
	    }

	    std::uint64_t timestamp() const noexcept {
	        return util::read_be_48b(base + 5);
	    }

	    std::uint64_t stock() const noexcept {
	        return util::read_be<std::uint64_t>(base + 11);
	    }

	    EligibleForTradingReleaseFlag is_eligible_for_trading_release() const noexcept {
	        return util::read_be_enum<EligibleForTradingReleaseFlag>(base + 19);
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

	static_assert(std::is_aggregate_v<SystemEventView>);
	static_assert(std::is_aggregate_v<StockDirectoryView>);
	static_assert(std::is_aggregate_v<StockTradingActionView>);
	static_assert(std::is_aggregate_v<RegSHORestrictionView>);
	static_assert(std::is_aggregate_v<MarketParticipantPositionView>);
	static_assert(std::is_aggregate_v<MWCBDeclineLevelView>);
	static_assert(std::is_aggregate_v<MWCBStatusView>);
	static_assert(std::is_aggregate_v<IPOQuotingPeriodUpdateView>);
	static_assert(std::is_aggregate_v<LULDAuctionCollarView>);
	static_assert(std::is_aggregate_v<OperationalHaltView>);
	static_assert(std::is_aggregate_v<AddOrderView>);
	static_assert(std::is_aggregate_v<ExecuteOrderView>);
	static_assert(std::is_aggregate_v<CancelOrderView>);
	static_assert(std::is_aggregate_v<ReplaceOrderView>);
	static_assert(std::is_aggregate_v<NonCrossTradeView>);
	static_assert(std::is_aggregate_v<CrossTradeView>);
	static_assert(std::is_aggregate_v<BrokenTradeView>);
	static_assert(std::is_aggregate_v<NOIIView>);
	static_assert(std::is_aggregate_v<RPIIView>);
	static_assert(std::is_aggregate_v<DLCRPriceDiscoveryView>);

	using MessageViewVariant = std::variant<
		SystemEvent,
		StockDirectory,
		StockTradingAction,
		RegSHORestriction,
		MarketParticipantPosition,
		MWCBDeclineLevel,
		MWCBStatus,
		IPOQuotingPeriodUpdate,
		LULDAuctionCollar,
		OperationalHalt,
		AddOrder,
		ExecuteOrder,
		CancelOrder,
		ReplaceOrder,
		NonCrossTrade,
		CrossTrade,
		BrokenTrade,
		NOII,
		RPII,
		DLCRPriceDiscovery
	>;

} // namespace itch::spec::view

#endif // TV_ITCH50_CPP_MESSAGES_HPP
