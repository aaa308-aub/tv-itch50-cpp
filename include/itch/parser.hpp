#ifndef TV_ITCH50_CPP_PARSER_HPP
#define TV_ITCH50_CPP_PARSER_HPP

#include "itch/mmap/mmap.hpp"
#include "itch/spec/messages.hpp"
#include "itch/util/util.hpp"

#include <cstdint>
#include <cstdlib>
#include <cstring>

namespace itch {

template <class Handler>
class Parser {

private:
	Handler& handler;
	const mmap::MemoryMap mmap;
	const std::uint8_t* mmap_ptr;
	const std::uint8_t* mmap_end;
	std::uint16_t msg_len;
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
			msg_len = util::read_be<std::uint16_t>(mmap_ptr);
			mmap_ptr += 2;

			if (mmap_ptr + msg_len == mmap_end) {
				is_eof = true;
			}

			return true;
		}

		return false;
	}

	void callHandler() const noexcept {
		using namespace spec::view;

		const auto curr_msg_type = util::read_be<std::uint8_t>(mmap_ptr);
		switch (curr_msg_type) {
			case 'S': {
				using msgV = SystemEventView;
				if constexpr (requires (Handler h, msgV v)
				              {h.onSystemEvent(v);}) {
					handler.onSystemEvent( msgV{mmap_ptr} );
				}
				break;
			}
			case 'R': {
				using msgV = StockDirectoryView;
				if constexpr (requires (Handler h, msgV v)
				              {h.onStockDirectory(v);}) {
					handler.onStockDirectory( msgV{mmap_ptr} );
				}
				break;
			}
		    case 'H': {
	            using msgV = StockTradingActionView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onStockTradingAction(v);}) {
	                handler.onStockTradingAction(msgV{mmap_ptr});
	            }
	            break;
			}
			case 'Y': {
	            using msgV = RegSHORestrictionView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onRegSHORestriction(v);}) {
	                handler.onRegSHORestriction(msgV{mmap_ptr});
	            }
	            break;
	        }
			case 'L': {
	            using msgV = MarketParticipantPositionView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onMarketParticipantPosition(v);}) {
	                handler.onMarketParticipantPosition(msgV{mmap_ptr});
	            }
	            break;
	        }
   			case 'V': {
	            using msgV = MWCBDeclineLevelView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onMWCBDeclineLevel(v);}) {
	                handler.onMWCBDeclineLevel(msgV{mmap_ptr});
	            }
	            break;
	        }
      		case 'W': {
	            using msgV = MWCBStatusView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onMWCBStatus(v);}) {
	                handler.onMWCBStatus(msgV{mmap_ptr});
	            }
	            break;
	        }
        	case 'K': {
	            using msgV = IPOQuotingPeriodUpdateView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onIPOQuotingPeriodUpdate(v);}) {
	                handler.onIPOQuotingPeriodUpdate(msgV{mmap_ptr});
	            }
	            break;
	        }
         	case 'J': {
	            using msgV = LULDAuctionCollarView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onLULDAuctionCollar(v);}) {
	                handler.onLULDAuctionCollar(msgV{mmap_ptr});
	            }
	            break;
	        }
          	case 'h': {
	            using msgV = OperationalHaltView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onOperationalHalt(v);}) {
	                handler.onOperationalHalt(msgV{mmap_ptr});
	            }
	            break;
	        }

           	case 'A': {
	            using msgV = AddOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onAddOrder(v);}) {
	                handler.onAddOrder(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'F': {
	            using msgV = AddOrderWithMPIDView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onAddOrderWithMPID(v);}) {
	                handler.onAddOrderWithMPID(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'E': {
	            using msgV = ExecuteOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onExecuteOrder(v);}) {
	                handler.onExecuteOrder(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'C': {
	            using msgV = ExecuteOrderWithPriceView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onExecuteOrderWithPrice(v);}) {
	                handler.onExecuteOrderWithPrice(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'X': {
	            using msgV = CancelOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onCancelOrder(v);}) {
	                handler.onCancelOrder(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'D': {
	            using msgV = DeleteOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onDeleteOrder(v);}) {
	                handler.onDeleteOrder(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'U': {
	            using msgV = ReplaceOrderView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onReplaceOrder(v);}) {
	                handler.onReplaceOrder(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'P': {
	            using msgV = NonCrossTradeView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onNonCrossTrade(v);}) {
	                handler.onNonCrossTrade(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'Q': {
	            using msgV = CrossTradeView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onCrossTrade(v);}) {
	                handler.onCrossTrade(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'B': {
	            using msgV = BrokenTradeView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onBrokenTrade(v);}) {
	                handler.onBrokenTrade(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'I': {
	            using msgV = NetOrderImbalanceView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onNetOrderImbalance(v);}) {
	                handler.onNetOrderImbalance(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'N': {
	            using msgV = RetailPriceImprovementView;
	            if constexpr (requires (Handler h, msgV v)
							  {h.onRetailPriceImprovement(v);}) {
	                handler.onRetailPriceImprovement(msgV{mmap_ptr});
	            }
	            break;
	        }
            case 'O': {
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
