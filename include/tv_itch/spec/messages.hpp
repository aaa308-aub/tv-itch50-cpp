#ifndef TV_ITCH50_CPP_MESSAGES_HPP
#define TV_ITCH50_CPP_MESSAGES_HPP


#include "alpha_fields.hpp"


#include <cstdint>
#include <type_traits>
#include <variant>


namespace tv_itch::spec {
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
	// The spec doesn't say what reserved means. Just describes it as "Reserved." Could be a padding thing
	std::uint8_t reserved;
};


struct RegSHORestriction {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint16_t stock_locate;   // Spec named it "locate code" for this message. Decided to change back
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


// AddOrder struct is for both with or without MPID attribution
struct AddOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint64_t stock;
	std::uint32_t shares;
	std::uint32_t price;   // Actual Price = price / 10^4
	std::uint32_t mp_id;   // Default = "NSDQ" for Add Order messages without MPID attribution
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	Side side;
};


// ExecuteOrder struct is for both with or without different execution price
struct ExecuteOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint64_t match_number;
	std::uint32_t executed_shares;
	std::uint32_t executed_price;   // If 0, implies a normal Execute Order message
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	PrintableFlag is_printable;   // Always Printable/'Y' for normal Execute Order messages
};


// CancelOrder struct is for both cancel order messages and delete order messages.
struct CancelOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id;
	std::uint32_t cancelled_shares;   // If cancelled_shares = 0, delete the order
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};


struct ReplaceOrder {
	std::uint64_t timestamp;
	std::uint64_t order_id_old;   // The order_id of the old order to be removed from the order book
	std::uint64_t order_id_new;   // The order_id of the new order to be added into the order book
	std::uint32_t shares;
	std::uint32_t price;   // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
};


struct NonCrossTrade {
	// Dates mentioned below are in DD.MM.YYYY format
	std::uint64_t timestamp;
	std::uint64_t order_id;   // Effective 06.12.2010, this field should always be 0
	std::uint64_t stock;
	std::uint64_t match_number;
	std::uint32_t shares;
	std::uint32_t price;   // Actual price = price / 10^4
	std::uint16_t stock_locate;
	std::uint16_t tracking_number;
	Side side;   // Effective 14.07.2014, this field should always be Buy / 'B'
};


struct CrossTrade {
	std::uint64_t timestamp;
	std::uint64_t stock;
	std::uint64_t match_number;
	std::uint32_t shares;
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
	CrossTypeNOII cross_type;
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
}


#endif