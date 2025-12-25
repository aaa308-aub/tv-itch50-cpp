#ifndef TV_ITCH50_CPP_PARSER_HPP
#define TV_ITCH50_CPP_PARSER_HPP


#ifndef TV_ITCH50_CPP_BIG_ENDIAN
#define TV_ITCH50_CPP_LITTLE_ENDIAN
#endif


#include "tv_itch/mmap/mmap.hpp"
#include "tv_itch/spec/alpha_fields.hpp"
#include "tv_itch/spec/messages.hpp"
#include "tv_itch/spec/message_lengths.hpp"
#include "tv_itch/utils/utils.hpp"


#include <cstdint>
#include <cstdlib>
#include <type_traits>


namespace tv_itch {
class Parser {
public:
	using MessageType = spec::MessageType;
	using MessageVariant = spec::MessageVariant;

	explicit Parser(const std::string& filename) noexcept;

	Parser(const Parser&) = delete;
	Parser& operator=(const Parser&) = delete;

	[[nodiscard]] bool eof() const noexcept { return is_eof; }

	[[nodiscard]] MessageVariant record() const noexcept { return current_record; }

	bool nextRecord() noexcept;

private:
	const mmap::MemoryMap mmap;
	const std::uint8_t* mmap_ptr;
	const std::uint8_t* mmap_end;
	bool is_eof = false;
	MessageVariant current_record;

	MessageVariant parseNextMessage() noexcept;

	// In debug mode, finds message length and type by the first 3 bytes of the message and asserts that
	// the length is correct. Outside debug mode, skips first 2 bytes and gets message type directly.
	[[nodiscard]] MessageType getMessageType() noexcept;

	[[nodiscard]] std::uint16_t read_and_advance_u16() noexcept;

	[[nodiscard]] std::uint32_t read_and_advance_u32() noexcept;

	[[nodiscard]] std::uint64_t read_and_advance_u64() noexcept;

	// Timestamps are saved in uint64_t but are actually 6 byte fields
	// Note that we're trying to avoid reinterpret_cast
	[[nodiscard]] std::uint64_t read_and_advance_ts() noexcept;

	// This is for enums (or enum classes) of underlying type char. There are currently two enum classes
	// which cannot use this method because their underlying types are uint16_t and uint32_t
	template <typename T>
	[[nodiscard]] inline T readEnumAndAdvance() noexcept {
		static_assert(std::is_enum_v<T>
					  && std::is_same_v<std::underlying_type_t<T>, char>,
					  "T must be an enum of underlying type char");

		return static_cast<T>(static_cast<char>(*(mmap_ptr++)));
	}

	MessageVariant parseSystemEvent() noexcept;

	MessageVariant parseStockDirectory() noexcept;

	MessageVariant parseStockTradingAction() noexcept;

	MessageVariant parseRegSHORestriction() noexcept;

	MessageVariant parseMarketParticipantPosition() noexcept;

	MessageVariant parseMWCBDeclineLevel() noexcept;

	MessageVariant parseMWCBStatus() noexcept;

	MessageVariant parseIPOQuotingPeriodUpdate() noexcept;

	MessageVariant parseLULDAuctionCollar() noexcept;

	MessageVariant parseOperationHalt() noexcept;

	MessageVariant parseAddOrder(const bool with_mp_id) noexcept;

	MessageVariant parseExecuteOrder(const bool with_price) noexcept;

	MessageVariant parseCancelOrder(const bool is_delete_order) noexcept;

	MessageVariant parseReplaceOrder() noexcept;

	MessageVariant parseNonCrossTrade() noexcept;

	MessageVariant parseCrossTrade() noexcept;

	MessageVariant parseBrokenTrade() noexcept;

	MessageVariant parseNOII() noexcept;

	MessageVariant parseRPII() noexcept;

	MessageVariant parseDLCRPriceDiscovery() noexcept;
};
}


#endif