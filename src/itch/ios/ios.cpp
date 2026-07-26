#include "itch/ios/ios.hpp"
#include "itch/spec/messages.hpp"

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace itch::ios {

std::string format_timestamp_ns(std::uint64_t ts) {
	using namespace std::chrono;

	const auto h = duration_cast<hours>(nanoseconds(ts));
	ts -= duration_cast<nanoseconds>(h).count();

	const auto m = duration_cast<minutes>(nanoseconds(ts));
	ts -= duration_cast<nanoseconds>(m).count();

	const auto s = duration_cast<seconds>(nanoseconds(ts));
	ts -= duration_cast<nanoseconds>(s).count();

	std::ostringstream out;
	out << std::setw(2) << std::setfill('0') << h.count() << ":"
		<< std::setw(2) << std::setfill('0') << m.count() << ":"
		<< std::setw(2) << std::setfill('0') << s.count() << "."
		<< std::setw(9) << std::setfill('0') << ts;

	return out.str();
}

std::string format_timestamp_sec(std::uint64_t ts) {
	using namespace std::chrono;

	const auto h = duration_cast<hours>(seconds(ts));
	ts -= duration_cast<seconds>(h).count();

	const auto m = duration_cast<minutes>(seconds(ts));
	ts -= duration_cast<seconds>(m).count();

	std::ostringstream out;
	out << std::setw(2) << std::setfill('0') << h.count() << ":"
		<< std::setw(2) << std::setfill('0') << m.count() << ":"
		<< std::setw(2) << std::setfill('0') << ts;

	return out.str();
}

std::string to_string(const spec::SystemEvent& m, const char sep) {
	const std::string s(1, sep);
	return std::string("S") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ static_cast<char>(m.event_code);
}

std::string to_string(const spec::StockDirectory& m, const char sep) {
	const std::string s(1, sep);
	return std::string("R") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ to_str_padded(m.stock) + s
		+ static_cast<char>(m.market_category) + s
		+ static_cast<char>(m.financial_status) + s
		+ std::to_string(m.round_lot_size) + s
		+ static_cast<char>(m.is_round_lots_only) + s
		+ static_cast<char>(m.issue_classification) + s
		+ to_str_padded(m.issue_subtype) + s
		+ static_cast<char>(m.authenticity) + s
		+ static_cast<char>(m.short_sale_threshold) + s
		+ static_cast<char>(m.is_ipo) + s
		+ static_cast<char>(m.luld_ref_price_tier) + s
		+ static_cast<char>(m.is_etp) + s
		+ std::to_string(m.etp_leverage_factor) + s
		+ static_cast<char>(m.is_inverse_etp);
}

std::string to_string(const spec::StockTradingAction& m, const char sep) {
	const std::string s(1, sep);
	return std::string("H") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ to_str_padded(m.stock) + s
		+ static_cast<char>(m.trading_state) + s
		// reserved field skipped.
		+ to_str_padded(m.trading_action_reason);
}

std::string to_string(const spec::RegSHORestriction& m, const char sep) {
	const std::string s(1, sep);
	return std::string("Y") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ to_str_padded(m.stock) + s
		+ static_cast<char>(m.reg_sho_action);
}

std::string to_string(const spec::MarketParticipantPosition& m, const char sep) {
	const std::string s(1, sep);
	return std::string("L") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ to_str_padded(m.mp_id) + s
		+ to_str_padded(m.stock) + s
		+ static_cast<char>(m.is_primary_market_maker) + s
		+ static_cast<char>(m.market_maker_mode) + s
		+ static_cast<char>(m.market_participant_state);
}

std::string to_string(const spec::MWCBDeclineLevel& m, const char sep) {
	const std::string s(1, sep);
	return std::string("V") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ format_price(m.price_level1) + s
		+ format_price(m.price_level2) + s
		+ format_price(m.price_level3);
}

std::string to_string(const spec::MWCBStatus& m, const char sep) {
	const std::string s(1, sep);
	return std::string("W") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ static_cast<char>(m.breached_level);
}

std::string to_string(const spec::IPOQuotingPeriodUpdate& m, const char sep) {
	const std::string s(1, sep);
	return std::string("K") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ to_str_padded(m.stock) + s
		+ format_timestamp_sec(m.ipo_quotation_time) + s
		+ static_cast<char>(m.ipo_quotation_release_flag) + s
		+ format_price(m.ipo_price);
}

std::string to_string(const spec::LULDAuctionCollar& m, const char sep) {
	const std::string s(1, sep);
	return std::string("J") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ to_str_padded(m.stock) + s
		+ format_price(m.reference_price) + s
		+ format_price(m.upper_price) + s
		+ format_price(m.lower_price) + s
		+ std::to_string(m.number_of_extensions);
}

std::string to_string(const spec::OperationalHalt& m, const char sep) {
	const std::string s(1, sep);
	return std::string("h") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ to_str_padded(m.stock) + s
		+ static_cast<char>(m.market_code) + s
		+ static_cast<char>(m.operational_halt_action);
}

std::string to_string(const spec::AddOrder& m, const char sep) {
	const std::string s(1, sep);
	return std::string("A") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.order_id) + s
		+ static_cast<char>(m.side) + s
		+ std::to_string(m.shares) + s
		+ to_str_padded(m.stock) + s
		+ format_price(m.price);
}

std::string to_string(const spec::AddOrderWithMPID& m, const char sep) {
	const std::string s(1, sep);
	return std::string("F") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.order_id) + s
		+ static_cast<char>(m.side) + s
		+ std::to_string(m.shares) + s
		+ to_str_padded(m.stock) + s
		+ format_price(m.price) + s
		+ to_str_padded(m.mp_id);
}

std::string to_string(const spec::ExecuteOrder& m, const char sep) {
	const std::string s(1, sep);
	return std::string("E") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.order_id) + s
		+ std::to_string(m.executed_shares) + s
		+ std::to_string(m.match_number);
}

std::string to_string(const spec::ExecuteOrderWithPrice& m, const char sep) {
	const std::string s(1, sep);
	return std::string("C") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.order_id) + s
		+ std::to_string(m.executed_shares) + s
		+ std::to_string(m.match_number) + s
		+ static_cast<char>(m.is_printable) + s
		+ format_price(m.executed_price);
}

std::string to_string(const spec::CancelOrder& m, const char sep) {
	const std::string s(1, sep);
	return std::string("X") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.order_id) + s
		+ std::to_string(m.cancelled_shares);
}

std::string to_string(const spec::DeleteOrder& m, const char sep) {
	const std::string s(1, sep);
	return std::string("D") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.order_id);
}

std::string to_string(const spec::ReplaceOrder& m, const char sep) {
	const std::string s(1, sep);
	return std::string("U") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.order_id_old) + s
		+ std::to_string(m.order_id_new) + s
		+ std::to_string(m.shares) + s
		+ format_price(m.price);
}

std::string to_string(const spec::NonCrossTrade& m, const char sep) {
	const std::string s(1, sep);
	return std::string("P") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.order_id) + s
		+ static_cast<char>(m.side) + s
		+ std::to_string(m.shares) + s
		+ to_str_padded(m.stock) + s
		+ format_price(m.price) + s
		+ std::to_string(m.match_number);
}

std::string to_string(const spec::CrossTrade& m, const char sep) {
	const std::string s(1, sep);
	return std::string("Q") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.shares) + s
		+ to_str_padded(m.stock) + s
		+ format_price(m.price) + s
		+ std::to_string(m.match_number) + s
		+ static_cast<char>(m.cross_type);
}

std::string to_string(const spec::BrokenTrade& m, const char sep) {
	const std::string s(1, sep);
	return std::string("B") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.match_number);
}

std::string to_string(const spec::NetOrderImbalance& m, const char sep) {
	const std::string s(1, sep);
	return std::string("I") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ std::to_string(m.paired_shares) + s
		+ std::to_string(m.imbalance_shares) + s
		+ static_cast<char>(m.imbalance_direction) + s
		+ to_str_padded(m.stock) + s
		+ format_price(m.far_price) + s
		+ format_price(m.near_price) + s
		+ format_price(m.reference_price) + s
		+ static_cast<char>(m.cross_type) + s
		+ static_cast<char>(m.price_variation_indicator);
}

std::string to_string(const spec::RetailPriceImprovement& m, const char sep) {
	const std::string s(1, sep);
	return std::string("N") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ to_str_padded(m.stock) + s
		+ static_cast<char>(m.interest_flag);
}

std::string to_string(const spec::DLCRPriceDiscovery& m, const char sep) {
	const std::string s(1, sep);
	return std::string("O") + s
		+ std::to_string(m.stock_locate) + s
		+ std::to_string(m.tracking_number) + s
		+ format_timestamp_ns(m.timestamp) + s
		+ to_str_padded(m.stock) + s
		+ static_cast<char>(m.is_eligible_for_trading_release) + s
		+ format_price(m.min_allowed_price) + s
		+ format_price(m.max_allowed_price) + s
		+ format_price(m.near_execution_price) + s
		+ format_timestamp_ns(m.near_execution_time) + s
		+ format_price(m.lower_price_range_collar) + s
		+ format_price(m.upper_price_range_collar);
}

} // namespace itch::ios
