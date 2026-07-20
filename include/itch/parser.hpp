#ifndef TV_ITCH50_CPP_PARSER_HPP
#define TV_ITCH50_CPP_PARSER_HPP

#include "itch/mmap/mmap.hpp"
#include "itch/spec/alpha_fields.hpp"
#include "itch/spec/messages.hpp"
#include "itch/util/util.hpp"

#include <cstdint>
#include <cstdlib>
#include <cstring>

namespace itch {

template <typename Handler>
class Parser {

private:
	Handler& handler;
	const mmap::MemoryMap mmap;
	const std::uint8_t* mmap_ptr;
	const std::uint8_t* mmap_end;
	std::uint8_t msg_len;
	bool is_eof;

public:
	explicit Parser(const std::string& filepath, Handler& h)
	: handler(h)
	, mmap(filepath)
	, mmap_ptr(mmap.data())
	, mmap_end(mmap.data() + mmap.size())
	, msg_len(0)
	, is_eof(mmap_ptr >= mmap_end)
	{/*no-op*/}

	Parser(const Parser&) = delete;
	Parser& operator=(const Parser&) = delete;
	Parser(const Parser&&) = delete;
	Parser& operator=(const Parser&&) = delete;

	[[nodiscard]] bool eof() const noexcept { return is_eof; }

	bool next() noexcept {
		if (!is_eof) {
			mmap_ptr += msg_len;
			msg_len = static_cast<std::uint8_t>(
				util::read_be_adv<std::uint16_t>(mmap_ptr));

			if (mmap_ptr + msg_len == mmap_end) {
				is_eof = true;
			}

			// Chose not to call handler here and instead let the user explicitly
			// do it, in case they want to do something in-between handler callbacks.

			return true;
		}

		return false;
	}

	void callHandler() noexcept {
		using namespace spec;
		using namespace spec::view;

		using msgT = MessageType;
		const msgT curr_msg_type = util::read_be_enum<msgT>(mmap_ptr);
		switch (curr_msg_type) {
			case msgT::SystemEvent: { // Enclosures required to keep re-defining type alias.
				using msgV = SystemEventView;
				if constexpr (requires (Handler h, msgV v)
				              {h.onSystemEvent(v);}) {
					handler.onSystemEvent( msgV{mmap_ptr} );
				}
				break;
			}

			case msgT::StockDirectory: {
				using msgV = StockDirectoryView;
				if constexpr (requires (Handler h, msgV v)
				              {h.onStockDirectory(v);}) {
					handler.onStockDirectory( msgV{mmap_ptr} );
				}
				break;
			}

		    case msgT::StockTradingAction: {
	            using msgV = StockTradingActionView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onStockTradingAction(v);}) {
	                handler.onStockTradingAction(msgV{mmap_ptr});
	            }
	            break;
		        }

	        case msgT::RegSHORestriction: {
	            using msgV = RegSHORestrictionView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onRegSHORestriction(v);}) {
	                handler.onRegSHORestriction(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::MarketParticipantPosition: {
	            using msgV = MarketParticipantPositionView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onMarketParticipantPosition(v);}) {
	                handler.onMarketParticipantPosition(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::MWCBDeclineLevel: {
	            using msgV = MWCBDeclineLevelView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onMWCBDeclineLevel(v);}) {
	                handler.onMWCBDeclineLevel(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::MWCBStatus: {
	            using msgV = MWCBStatusView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onMWCBStatus(v);}) {
	                handler.onMWCBStatus(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::IPOQuotingPeriodUpdate: {
	            using msgV = IPOQuotingPeriodUpdateView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onIPOQuotingPeriodUpdate(v);}) {
	                handler.onIPOQuotingPeriodUpdate(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::LULDAuctionCollar: {
	            using msgV = LULDAuctionCollarView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onLULDAuctionCollar(v);}) {
	                handler.onLULDAuctionCollar(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::OperationalHalt: {
	            using msgV = OperationalHaltView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onOperationalHalt(v);}) {
	                handler.onOperationalHalt(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::AddOrderWithoutMPID: {
	            using msgV = AddOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onAddOrder(v);}) {
	                handler.onAddOrder(msgV{mmap_ptr, false});
	            }
	            break;
	        }

	        case msgT::AddOrderWithMPID: {
	            using msgV = AddOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onAddOrder(v);}) {
	                handler.onAddOrder(msgV{mmap_ptr, true});
	            }
	            break;
	        }

	        case msgT::ExecuteOrder: {
	            using msgV = ExecuteOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onExecuteOrder(v);}) {
	                handler.onExecuteOrder(msgV{mmap_ptr, false});
	            }
	            break;
	        }

	        case msgT::ExecuteOrderWithPrice: {
	            using msgV = ExecuteOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onExecuteOrder(v);}) {
	                handler.onExecuteOrder(msgV{mmap_ptr, true});
	            }
	            break;
	        }

	        case msgT::CancelOrder: {
	            using msgV = CancelOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onCancelOrder(v);}) {
	                handler.onCancelOrder(msgV{mmap_ptr, false});
	            }
	            break;
	        }

	        case msgT::DeleteOrder: {
	            using msgV = CancelOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onCancelOrder(v);}) {
	                handler.onCancelOrder(msgV{mmap_ptr, true});
	            }
	            break;
	        }

	        case msgT::ReplaceOrder: {
	            using msgV = ReplaceOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onReplaceOrder(v);}) {
	                handler.onReplaceOrder(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::NonCrossTrade: {
	            using msgV = NonCrossTradeView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onNonCrossTrade(v);}) {
	                handler.onNonCrossTrade(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::CrossTrade: {
	            using msgV = CrossTradeView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onCrossTrade(v);}) {
	                handler.onCrossTrade(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::BrokenTrade: {
	            using msgV = BrokenTradeView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onBrokenTrade(v);}) {
	                handler.onBrokenTrade(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::NOII: {
	            using msgV = NOIIView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onNOII(v);}) {
	                handler.onNOII(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::RPII: {
	            using msgV = RPIIView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onRPII(v);}) {
	                handler.onRPII(msgV{mmap_ptr});
	            }
	            break;
	        }

	        case msgT::DLCRPriceDiscovery: {
	            using msgV = DLCRPriceDiscoveryView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onDLCRPriceDiscovery(v);}) {
	                handler.onDLCRPriceDiscovery(msgV{mmap_ptr});
	            }
	            break;
	        }
		}
	}

}; // class Parser

} // namespace itch

#endif // TV_ITCH50_CPP_PARSER_HPP
