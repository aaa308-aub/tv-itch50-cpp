#include "tv_itch/ios/ios.hpp"
#include "tv_itch/spec/alpha_fields.hpp"
#include "tv_itch/spec/messages.hpp"


#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>


namespace tv_itch::ios {
std::string format_timestamp_ns(std::uint64_t ts) {
	using namespace std::chrono;

	const auto h = duration_cast<hours>(nanoseconds(ts));
	ts -= duration_cast<nanoseconds>(h).count();

	const auto m = duration_cast<minutes>(nanoseconds(ts));
	ts -= duration_cast<nanoseconds>(m).count();

	const auto s = duration_cast<seconds>(nanoseconds(ts));
	ts -= duration_cast<nanoseconds>(s).count();

	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << h.count() << ":"
		<< std::setw(2) << std::setfill('0') << m.count() << ":"
		<< std::setw(2) << std::setfill('0') << s.count() << "."
		<< std::setw(9) << std::setfill('0') << ts;

	return oss.str();
}


std::string format_timestamp_sec(std::uint64_t ts) {
	using namespace std::chrono;

	const auto h = duration_cast<hours>(seconds(ts));
	ts -= duration_cast<seconds>(h).count();

	const auto m = duration_cast<minutes>(seconds(ts));
	ts -= duration_cast<seconds>(m).count();

	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << h.count() << ":"
		<< std::setw(2) << std::setfill('0') << m.count() << ":"
		<< std::setw(2) << std::setfill('0') << ts;

	return oss.str();
}


// For 4-byte prices, which must have 4 decimal points
std::string format_price_u32(const std::uint32_t value) {
	std::string s = std::to_string(value);

	if (s.size() <= 4)
		s.insert(0, 4 - s.size() + 1, '0');

	s.insert(s.size() - 4, ".");
	return s;
}


// For 8-byte prices, which must have 8 decimal points
std::string format_price_u64(const std::uint64_t value) {
	std::string s = std::to_string(value);

	if (s.size() <= 8)
		s.insert(0, 8 - s.size() + 1, '0');

	s.insert(s.size() - 8, ".");
	return s;
}


std::string to_ascii_str_u16(const std::uint16_t value) {
	std::string s(2, ' ');

	for (std::size_t i = 0; i < 2; ++i) {
		s[i] = static_cast<char>(
			( value >> ( 8 * (2 - i - 1) ) ) & 0xFF
			);
	}

	return s;
}


std::string to_ascii_str_u32(const std::uint32_t value) {
	std::string s(4, ' ');

	for (std::size_t i = 0; i < 4; ++i) {
		s[i] = static_cast<char>(
			( value >> ( 8 * (4 - i - 1) ) ) & 0xFF
			);
	}

	return s;
}


std::string to_ascii_str_u64(const std::uint64_t value) {
	std::string s(8, ' ');

	for (std::size_t i = 0; i < 8; ++i) {
		s[i] = static_cast<char>(
			( value >> ( 8 * (8 - i - 1) ) ) & 0xFF
			);
	}

	return s;
}


std::string to_string(const spec::MessageType t) {
	using e = spec::MessageType;
	switch (t) {
	case e::SystemEvent:               return "System Event";
	case e::StockDirectory:            return "Stock Directory";
	case e::StockTradingAction:        return "Stock Trading Action";
	case e::RegSHORestriction:         return "Reg SHO Restriction";
	case e::MarketParticipantPosition: return "Market Participant Position";
	case e::MWCBDeclineLevel:          return "MWCB Decline Level";
	case e::MWCBStatus:                return "MWCB Status";
	case e::IPOQuotingPeriodUpdate:    return "IPO Quoting Period Update";
	case e::LULDAuctionCollar:         return "LULD Auction Collar";
	case e::OperationalHalt:           return "Operational Halt";
	case e::AddOrderWithoutMPID:       return "Add Order Without MPID Attribution";
	case e::AddOrderWithMPID:          return "Add Order With MPID Attribution";
	case e::ExecuteOrder:              return "Execute Order";
	case e::ExecuteOrderWithPrice:     return "Execute Order With Price";
	case e::CancelOrder:               return "Cancel Order";
	case e::DeleteOrder:               return "Delete Order";
	case e::ReplaceOrder:              return "Replace Order";
	case e::NonCrossTrade:             return "Non-Cross Trade";
	case e::CrossTrade:                return "Cross Trade";
	case e::BrokenTrade:               return "Broken Trade";
	case e::NOII:                      return "Net Order Imbalance Indicator (NOII)";
	case e::RPII:                      return "Retail Price Improvement Indicator (RPII)";
	case e::DLCRPriceDiscovery:        return "DLCR Price Discovery";
	default:
		throw std::runtime_error(
			std::string("Invalid MessageType: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
		);
	}
}


std::string to_string(const spec::Side t) {
	using e = spec::Side;
	switch (t) {
	case e::Buy:  return "Buy";
	case e::Sell: return "Sell";
	default:
		throw std::runtime_error(
			std::string("Invalid Side: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::SystemEventCode t) {
	using e = spec::SystemEventCode;
	switch (t) {
	case e::StartOfMessages:    return "Start Of Messages";
	case e::StartOfSystemHours: return "Start Of System Hours";
	case e::StartOfMarketHours: return "Start Of Market Hours";
	case e::EndOfMarketHours:   return "End Of Market Hours";
	case e::EndOfSystemHours:   return "End Of System Hours";
	case e::EndOfMessages:      return "End Of Messages";
	default:
		throw std::runtime_error(
			std::string("Invalid SystemEventCode: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::MarketCategory t) {
	using e = spec::MarketCategory;
	switch (t) {
	case e::NasdaqGlobalSelectMarket: return "Nasdaq Global Select Market";
	case e::NasdaqGlobalMarket:       return "Nasdaq Global Market";
	case e::NasdaqCapitalMarket:      return "Nasdaq Capital Market";
	case e::NYSE:                     return "NYSE";
	case e::NYSEAmerican:             return "NYSE American";
	case e::NYSEArca:                 return "NYSE Arca";
	case e::BATSZExchange:            return "BATS Z Exchange";
	case e::InvestorsExchangeLLC:     return "Investors' Exchange, LLC";
	case e::NotAvailable:             return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid MarketCategory: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::FinancialStatus t) {
	using e = spec::FinancialStatus;
	switch (t) {
	case e::Deficient:                             return "Deficient";
	case e::Delinquent:                            return "Delinquent";
	case e::Bankrupt:                              return "Bankrupt";
	case e::Suspended:                             return "Suspended";
	case e::DeficientAndBankrupt:                  return "Deficient And Bankrupt";
	case e::DeficientAndDelinquent:                return "Deficient And Delinquent";
	case e::DelinquentAndBankrupt:                 return "Delinquent And Bankrupt";
	case e::DeficientDelinquentAndBankrupt:        return "Deficient Delinquent And Bankrupt";
	case e::CreationsOrRedemptionsSuspendedForETP: return "Creations And/Or Redemptions Suspended For ETP";
	case e::Normal:                                return "Normal";
	case e::NotAvailable:                          return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid FinancialStatus: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::RoundLotsOnlyFlag t) {
	using e = spec::RoundLotsOnlyFlag;
	switch (t) {
	case e::Yes: return "Yes";
	case e::No:  return "No";
	default:
		throw std::runtime_error(
			std::string("Invalid RoundLotsOnlyFlag: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::IssueClassification t) {
	using e = spec::IssueClassification;
	switch (t) {
	case e::AmericanDepositaryShare:    return "American Depositary Share";
	case e::Bond:                       return "Bond";
	case e::CommonStock:                return "Common Stock";
	case e::DepositoryReceipt:          return "Depository Receipt";
	case e::Rule144A:                   return "144A";
	case e::LimitedPartnership:         return "Limited Partnership";
	case e::Notes:                      return "Notes";
	case e::OrdinaryShare:              return "Ordinary Share";
	case e::PreferredStock:             return "Preferred Stock";
	case e::OtherSecurities:            return "Other Securities";
	case e::Right:                      return "Right";
	case e::SharesOfBeneficialInterest: return "Shares Of Beneficial Interest";
	case e::ConvertibleDebenture:       return "Convertible Debenture";
	case e::Unit:                       return "Unit";
	case e::UnitsOrBenifInt:            return "Units/Benif Int";
	case e::Warrant:                    return "Warrant";
	default:
		throw std::runtime_error(
			std::string("Invalid IssueClassification: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::IssueSubType t) {
	using e = spec::IssueSubType;
	switch (t) {
	case e::PreferredTrustSecurities:                     return "Preferred Trust Securities";
	case e::AlphaIndexETNs:                               return "Alpha Index ETNs";
	case e::IndexBasedDerivative:                         return "Index Based Derivative";
	case e::CommonShares:                                 return "Common Shares";
	case e::CommodityBasedTrustShares:                    return "Commodity Based Trust Shares";
	case e::CommodityFuturesTrustShares:                  return "Commodity Futures Trust Shares";
	case e::CommodityLinkedSecurities:                    return "Commodity-Linked Securities";
	case e::CommodityIndexTrustShares:                    return "Commodity Index Trust Shares";
	case e::CollateralizedMortgageObligation:             return "Collateralized Mortgage Obligation";
	case e::CurrencyTrustShares:                          return "Currency Trust Shares";
	case e::CommodityCurrencyLinkedSecurities:            return "Commodity-Currency-Linked Securities";
	case e::CurrencyWarrants:                             return "Currency Warrants";
	case e::GlobalDepositaryShares:                       return "Global Depositary Shares";
	case e::ETFPortfolioDepositaryReceipt:                return "ETF-Portfolio Depositary Receipt";
	case e::EquityGoldShares:                             return "Equity Gold Shares";
	case e::ETNEquityIndexLinkedSecurities:               return "ETN-Equity Index-Linked Securities";
	case e::NextSharesExchangeTradedManagedFund:          return "NextShares Exchange Traded Managed Fund";
	case e::ExchangeTradedNotes:                          return "Exchange Traded Notes";
	case e::EquityUnits:                                  return "Equity Units";
	case e::HOLDRS:                                       return "HOLDRS";
	case e::ETNFixedIncomeLinkedSecurities:               return "ETN-Fixed Income-Linked Securities";
	case e::ETNFuturesLinkedSecurities:                   return "ETN-Futures-Linked Securities";
	case e::GlobalShares:                                 return "Global Shares";
	case e::ETFIndexFundShares:                           return "ETF-Index Fund Shares";
	case e::InterestRate:                                 return "Interest Rate";
	case e::IndexWarrant:                                 return "Index Warrant";
	case e::IndexLinkedExchangeableNotes:                 return "Index-Linked Exchangeable Notes";
	case e::CorporateBackedTrustSecurity:                 return "Corporate Backed Trust Security";
	case e::ContingentLitigationRight:                    return "Contingent Litigation Right";
	case e::LLCSecurity:                                  return "Limited Liability Company";
	case e::EquityBasedDerivative:                        return "Equity-Based Derivative";
	case e::ManagedFundShares:                            return "Managed Fund Shares";
	case e::ETNMultiFactorIndexLinkedSecurities:          return "ETN-Multi-Factor Index-Linked Securities";
	case e::ManagedTrustSecurities:                       return "Managed Trust Securities";
	case e::NYRegistryShares:                             return "NY Registry Shares";
	case e::OpenEndedMutualFund:                          return "Open Ended Mutual Fund";
	case e::PrivatelyHeldSecurity:                        return "Privately Held Security";
	case e::PoisonPill:                                   return "Poison Pill";
	case e::PartnershipUnits:                             return "Partnership Units";
	case e::ClosedEndFunds:                               return "Closed-End Funds";
	case e::RegS:                                         return "Reg-S";
	case e::CommodityRedeemableCommodityLinkedSecurities:
		return "Commodity-Redeemable Commodity-Linked Securities";
	case e::ETNRedeemableFuturesLinkedSecurities:         return "ETN-Redeemable Futures-Linked Securities";
	case e::REIT:                                         return "REIT";
	case e::CommodityRedeemableCurrencyLinkedSecurities:
		return "Commodity-Redeemable Currency-Linked Securities";
	case e::SEED:                                         return "SEED";
	case e::SpotRateClosing:                              return "Spot Rate Closing";
	case e::SpotRateIntraday:                             return "Spot Rate Intraday";
	case e::TrackingStock:                                return "Tracking Stock";
	case e::TrustCertificates:                            return "Trust Certificates";
	case e::TrustUnits:                                   return "Trust Units";
	case e::Portal:                                       return "Portal";
	case e::ContingentValueRight:                         return "Contingent Value Right";
	case e::TrustIssuedReceipts:                          return "Trust Issued Receipts";
	case e::WorldCurrencyOption:                          return "World Currency Option";
	case e::Trust:                                        return "Trust";
	case e::Other:                                        return "Other";
	case e::NotApplicable:                                return "Not Applicable";
	default:
		throw std::runtime_error(
			std::string("Invalid IssueSubType of underlying value ")
			+ std::to_string(static_cast<std::uint16_t>(t))
			);
	}
}


std::string to_string(const spec::Authenticity t) {
	using e = spec::Authenticity;
	switch (t) {
	case e::LiveOrProduction: return "Live/Production";
	case e::Test:             return "Test";
	default:
		throw std::runtime_error(
			std::string("Invalid Authenticity: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::ShortSaleThreshold t) {
	using e = spec::ShortSaleThreshold;
	switch (t) {
	case e::RestrictedUnderSECRule203b3: return "Restricted Under SEC Rule 203(b)(3)";
	case e::NotRestricted:               return "Not Restricted";
	case e::NotAvailable:                return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid ShortSaleThreshold: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::IPOFlag t) {
	using e = spec::IPOFlag;
	switch (t) {
	case e::Yes:          return "Yes";
	case e::No:           return "No";
	case e::NotAvailable: return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid IPOFlag: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::LULDRefPriceTier t) {
	using e = spec::LULDRefPriceTier;
	switch (t) {
	case e::Tier1NMSStocksAndSelectETPs: return "Tier 1 NMS Stocks And Select ETPs";
	case e::Tier2NMSStocks:              return "Tier 2 NMS Stocks";
	case e::NotAvailable:                return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid LULDRefPriceTier: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::ETPFlag t) {
	using e = spec::ETPFlag;
	switch (t) {
	case e::Yes:          return "Yes";
	case e::No:           return "No";
	case e::NotAvailable: return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid ETPFlag: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::InverseETPFlag t) {
	using e = spec::InverseETPFlag;
	switch (t) {
	case e::Yes: return "Yes";
	case e::No:  return "No";
	default:
		throw std::runtime_error(
			std::string("Invalid InverseETPFlag: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::StockTradingState t) {
	using e = spec::StockTradingState;
	switch (t) {
	case e::HaltedAcrossAllUSEquitiesOrSROs: return "Halted Across All US Equity Markets/SROs";
	case e::PausedAcrossAllUSEquitiesOrSROs: return "Paused Across All US Equity Markets/SROs";
	case e::QuotationOnlyPeriod:             return "Quotation Only Period For Cross-SRO Halt/Pause";
	case e::TradingOnNasdaq:                 return "Trading On Nasdaq";
	default:
		throw std::runtime_error(
			std::string("Invalid StockTradingState: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::TradingActionReason t) {
	using e = spec::TradingActionReason;
	switch (t) {
	case e::HaltNewsPending:                           return "Halt News Pending";
	case e::HaltNewsDisseminated:                      return "Halt News Disseminated";
	case e::SingleSecurityTradingPauseInEffect:        return "Single Security Trading Pause In Effect";
	case e::RegulatoryHaltExtraordinaryMarketActivity:
		return "Regulatory Halt -- Extraordinary Market Activity";
	case e::HaltETF:                                   return "Halt ETF";
	case e::TradingHaltedForInfoToListingMarket:
		return "Trading Halted For Info Requested By Listing Market";
	case e::HaltNonCompliance:                         return "Halt Non-Compliance";
	case e::HaltFilingsNotCurrent:                     return "Halt Filings Not Current";
	case e::HaltSECTradingSuspension:                  return "Halt SEC Trading Suspension";
	case e::HaltRegulatoryConcern:                     return "Halt Regulatory Concern";
	case e::OperationsHalt:                            return "Operations Halt -- Contact Market Operations";
	case e::VolatilityTradingPause:                    return "Volatility Trading Pause";
	case e::VolatilityTradingPauseStraddleCondition:
		return "Volatility Trading Pause -- Straddle Condition";
	case e::MarketWideCircuitBreakerHaltLevel1:        return "Market Wide Circuit Breaker Halt -- Level 1";
	case e::MarketWideCircuitBreakerHaltLevel2:        return "Market Wide Circuit Breaker Halt -- Level 2";
	case e::MarketWideCircuitBreakerHaltLevel3:        return "Market Wide Circuit Breaker Halt -- Level 3";
	case e::MarketWideCircuitBreakerHaltCarryOver:
		return "Market Wide Circuit Breaker Halt -- Carry Over From Previous Day";
	case e::IPOIssueNotYetTrading:                     return "IPO Issue Not Yet Trading";
	case e::CorporateAction:                           return "Corporate Action";
	case e::QuotationNotAvailable:                     return "Quotation Not Available";
	case e::NewsAndResumptionTimes:                    return "News And Resumption Times";
	case e::SingleSecurityTradingPauseOrQuotationOnly:
		return "Single Security Trading Pause/Quotation Only Period";
	case e::QualificationsIssuesReviewedOrResolved:
		return "Qualifications Issues Reviewed/Resolved -- Trading Resumed";
	case e::FilingRequirementsSatisfiedOrResolved:
		return "Filing Requirements Satisfied/Resolved -- Trading Resumed";
	case e::IssuerNewsNotForthcoming:
		return "Issuer News Not Forthcoming -- Trading Resumed";
	case e::QualificationsHaltEndedAndMaintenanceDone:
		return "Qualifications Halt Ended And Maintenance Requirements Met -- Trading Resumed";
	case e::QualificationsHaltConcludedAndFilingsMet:
		return "Qualifications Halt Concluded And Filings Met -- Trading Resumed";
	case e::TradeHaltConcludedByOtherRegulatoryAuth:
		return "Trade Halt Concluded By Other Regulatory Authority -- Trading Resumed";
	case e::MarketWideCircuitBreakerResumption:        return "Market Wide Circuit Breaker Resumption";
	case e::NewIssueAvailable:                         return "New Issue Available";
	case e::IssueAvailable:                            return "Issue Available";
	case e::IPOSecurityReleasedForQuotation:           return "IPO Security Released For Quotation";
	case e::IPOSecurityPositioningWindowExtension:
		return "IPO Security -- Positioning Window Extension";
	case e::ReasonNotAvailable:                        return "Reason Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid TradingActionReason of underlying value ")
			+ std::to_string(static_cast<std::uint32_t>(t))
			);
	}
}


std::string to_string(const spec::RegSHOAction t) {
	using e = spec::RegSHOAction;
	switch (t) {
	case e::NoPriceTest:                                  return "No Price Test In Place";
	case e::ShortSalePriceTestRestriction:
		return "Short Sale Price Test Restriction Due to Intraday Price Drop";
	case e::ShortSalePriceTestRestrictionRemainsInEffect:
		return "Short Sale Price Test Restriction Remains In Effect";
	default:
		throw std::runtime_error(
			std::string("Invalid Reg SHO Action: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::PrimaryMarketMakerFlag t) {
	using e = spec::PrimaryMarketMakerFlag;
	switch (t) {
	case e::Yes: return "Yes";
	case e::No:  return "No";
	default:
		throw std::runtime_error(
			std::string("Invalid PrimaryMarketMakerFlag: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::MarketMakerMode t) {
	using e = spec::MarketMakerMode;
	switch (t) {
	case e::Normal:       return "Normal";
	case e::Passive:      return "Passive";
	case e::Syndicate:    return "Syndicate";
	case e::PreSyndicate: return "Pre-Syndicate";
	case e::Penalty:      return "Penalty";
	default:
		throw std::runtime_error(
			std::string("Invalid MarketMakerMode: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::MarketParticipantState t) {
	using e = spec::MarketParticipantState;
	switch (t) {
	case e::Active:             return "Active";
	case e::ExcusedOrWithdrawn: return "Excused/Withdrawn";
	case e::Withdrawn:          return "Withdrawn";
	case e::Suspended:          return "Suspended";
	case e::Deleted:            return "Deleted";
	default:
		throw std::runtime_error(
			std::string("Invalid MarketParticipantState: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::MWCBBreachLevel t) {
	using e = spec::MWCBBreachLevel;
	switch (t) {
	case e::Level1: return "Level 1";
	case e::Level2: return "Level 2";
	case e::Level3: return "Level 3";
	default:
		throw std::runtime_error(
			std::string("Invalid MWCBBreachLevel: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::IPOQuotationReleaseQualifier t) {
	using e = spec::IPOQuotationReleaseQualifier;
	switch (t) {
	case e::AnticipatedReleaseTime: return "Anticipated Quotation Release Time";
	case e::CanceledOrPostponed:    return "IPO Release Canceled/Postponed";
	default:
		throw std::runtime_error(
			std::string("Invalid IPOQuotationReleaseQualifier: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::MarketCode t) {
	using e = spec::MarketCode;
	switch (t) {
	case e::Nasdaq: return "Nasdaq";
	case e::BX:     return "BX";
	case e::PSX:    return "PSX";
	default:
		throw std::runtime_error(
			std::string("Invalid MarketCode: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::OperationalHaltAction t) {
	using e = spec::OperationalHaltAction;
	switch (t) {
	case e::Halted:     return "Halted";
	case e::HaltLifted: return "Halt Lifted -- Trading Resumed";
	default:
		throw std::runtime_error(
			std::string("Invalid OperationalHaltAction: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::PrintableFlag t) {
	using e = spec::PrintableFlag;
	switch (t) {
	case e::NonPrintable: return "Non-Printable";
	case e::Printable:    return "Printable";
	default:
		throw std::runtime_error(
			std::string("Invalid PrintableFlag: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::CrossType t) {
	using e = spec::CrossType;
	switch (t) {
	case e::NasdaqOpeningCross:                     return "Nasdaq Opening Cross";
	case e::NasdaqClosingCross:                     return "Nasdaq Closing Cross";
	case e::CrossForIPOAndHaltedOrPausedSecurities: return "Cross For IPO And Halted/Paused Securities";
	default:
		throw std::runtime_error(
			std::string("Invalid CrossType: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::ImbalanceDirection t) {
	using e = spec::ImbalanceDirection;
	switch (t) {
	case e::Buy:          return "Buy Imbalance";
	case e::Sell:         return "Sell Imbalance";
	case e::None:         return "No Imbalance";
	case e::NotAvailable: return "Insufficient Orders To Calculate";
	case e::Paused:       return "Paused";
	default:
		throw std::runtime_error(
			std::string("Invalid ImbalanceDirection: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::CrossTypeNOII t) {
	using e = spec::CrossTypeNOII;
	switch (t) {
	case e::NasdaqOpeningCross:                     return "Nasdaq Opening Cross";
	case e::NasdaqClosingCross:                     return "Nasdaq Closing Cross";
	case e::CrossForIPOAndHaltedOrPausedSecurities: return "Cross For IPO And Halted/Paused Securities";
	case e::ExtendedTradingClose:                   return "Extended Trading Close";
	default:
		throw std::runtime_error(
			std::string("Invalid CrossTypeNOII: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::PriceVariationPercentage t) {
	using e = spec::PriceVariationPercentage;
	switch (t) {
	case e::LessThanOnePercent:       return "Less Than 1%";
	case e::OneToSubTwoPercent:       return "1 To 1.99%";
	case e::TwoToSubThreePercent:     return "2 To 2.99%";
	case e::ThreeToSubFourPercent:    return "3 To 3.99%";
	case e::FourToSubFivePercent:     return "4 To 4.99%";
	case e::FiveToSubSixPercent:      return "5 To 5.99%";
	case e::SixToSubSevenPercent:     return "6 To 6.99%";
	case e::SevenToSubEightPercent:   return "7 To 7.99%";
	case e::EightToSubNinePercent:    return "8 To 8.99%";
	case e::NineToSubTenPercent:      return "9 To 9.99%";
	case e::TenToSubTwentyPercent:    return "10 To 19.99%";
	case e::TwentyToSubThirtyPercent: return "20 To 29.99%";
	case e::ThirtyPercentOrGreater:   return "30% Or Greater";
	case e::NotAvailable:             return "Cannot Be Calculated";
	default:
		throw std::runtime_error(
			std::string("Invalid PriceVariationPercentage: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::InterestFlagRPII t) {
	using e = spec::InterestFlagRPII;
	switch (t) {
	case e::RPIOrdersAvailableOnBuySide:   return "RPI Orders Available On Buy Side";
	case e::RPIOrdersAvailableOnSellSide:  return "RPI Orders Available On Sell Side";
	case e::RPIOrdersAvailableOnBothSides: return "RPI Orders Available On Both Sides";
	case e::NoRPIOrdersAvailable:          return "No RPI Orders Available";
	default:
		throw std::runtime_error(
			std::string("Invalid InterestFlagRPII: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::EligibleForTradingReleaseFlag t) {
	using e = spec::EligibleForTradingReleaseFlag;
	switch (t) {
	case e::NotEligible: return "Not Eligible";
	case e::Eligible:    return "Eligible";
	default:
		throw std::runtime_error(
			std::string("Invalid EligibleForTradingReleaseFlag: ")
			+ "'" + std::string(1, static_cast<char>(t)) + "'"
			);
	}
}


std::string to_string(const spec::SystemEvent& m) {
	return std::string("S,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ static_cast<char>(m.event_code);
}


std::string to_string(const spec::StockDirectory& m) {
	return std::string("R,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ static_cast<char>(m.market_category) + ","
		+ static_cast<char>(m.financial_status) + ","
		+ std::to_string(m.round_lot_size) + ","
		+ static_cast<char>(m.is_round_lots_only) + ","
		+ static_cast<char>(m.issue_classification) + ","
		+ to_ascii_str_u16(static_cast<std::uint16_t>(m.issue_subtype)) + ","
		+ static_cast<char>(m.authenticity) + ","
		+ static_cast<char>(m.short_sale_threshold) + ","
		+ static_cast<char>(m.is_ipo) + ","
		+ static_cast<char>(m.luld_ref_price_tier) + ","
		+ static_cast<char>(m.is_etp) + ","
		+ std::to_string(m.etp_leverage_factor) + ","
		+ static_cast<char>(m.is_inverse_etp);
}


std::string to_string(const spec::StockTradingAction& m) {
	return std::string("H,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ static_cast<char>(m.trading_state) + ","
		//+ m.reserved + ","   // Should probably skip this
		+ to_ascii_str_u32(static_cast<std::uint32_t>(m.trading_action_reason));
}


std::string to_string(const spec::RegSHORestriction& m) {
	return std::string("Y,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ static_cast<char>(m.reg_sho_action);
}


std::string to_string(const spec::MarketParticipantPosition& m) {
	return std::string("L,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_ascii_str_u32(m.mp_id) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ static_cast<char>(m.is_primary_market_maker) + ","
		+ static_cast<char>(m.market_maker_mode) + ","
		+ static_cast<char>(m.market_participant_state);
}


std::string to_string(const spec::MWCBDeclineLevel& m) {
	return std::string("V,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ format_price_u32(m.price_level1) + ","
		+ format_price_u32(m.price_level2) + ","
		+ format_price_u32(m.price_level3);
}


std::string to_string(const spec::MWCBStatus& m) {
	return std::string("W,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ static_cast<char>(m.breached_level);
}


std::string to_string(const spec::IPOQuotingPeriodUpdate& m) {
	return std::string("K,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ format_timestamp_sec(m.ipo_quotation_time) + ","
		+ static_cast<char>(m.ipo_quotation_release_qualifier) + ","
		+ format_price_u32(m.ipo_price);
}


std::string to_string(const spec::LULDAuctionCollar& m) {
	return std::string("J,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ format_price_u32(m.reference_price) + ","
		+ format_price_u32(m.upper_price) + ","
		+ format_price_u32(m.lower_price) + ","
		+ std::to_string(m.number_of_extensions);
}


std::string to_string(const spec::OperationalHalt& m) {
	return std::string("h,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ static_cast<char>(m.market_code) + ","
		+ static_cast<char>(m.operational_halt_action);
}


std::string to_string(const spec::AddOrder& m) {
	const bool with_mp_id = (m.mp_id != spec::DEFAULT_NON_ATTRIBUTED_MPID);

	return std::string((with_mp_id) ? "F" : "A") + ","
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.order_id) + ","
		+ static_cast<char>(m.side) + ","
		+ std::to_string(m.shares) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ format_price_u32(m.price)
		+ ((with_mp_id) ? "," + to_ascii_str_u32(m.mp_id) : "");
}


std::string to_string(const spec::ExecuteOrder& m) {
	const bool with_price = (m.executed_price != 0);

	return std::string((with_price) ? "C" : "E") + ","
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.order_id) + ","
		+ std::to_string(m.executed_shares) + ","
		+ std::to_string(m.match_number)
		+ ((with_price) ? "," + format_price_u32(m.executed_price) : "");
}


std::string to_string(const spec::CancelOrder& m) {
	const bool is_delete_order = (m.cancelled_shares == 0);

	return std::string((is_delete_order) ? "D" : "X") + ","
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.order_id)
		+ ((!is_delete_order) ? "," + std::to_string(m.cancelled_shares) : "");
}


std::string to_string(const spec::ReplaceOrder& m) {
	return std::string("U,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.order_id_old) + ","
		+ std::to_string(m.order_id_new) + ","
		+ std::to_string(m.shares) + ","
		+ format_price_u32(m.price);
}


std::string to_string(const spec::NonCrossTrade& m) {
	return std::string("P,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.order_id) + ","
		+ static_cast<char>(m.side) + ","
		+ std::to_string(m.shares) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ format_price_u32(m.price) + ","
		+ std::to_string(m.match_number);
}


std::string to_string(const spec::CrossTrade& m) {
	return std::string("Q,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.shares) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ format_price_u32(m.price) + ","
		+ std::to_string(m.match_number) + ","
		+ static_cast<char>(m.cross_type);
}


std::string to_string(const spec::BrokenTrade& m) {
	return std::string("B,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.match_number);
}


std::string to_string(const spec::NOII& m) {
	return std::string("I,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.paired_shares) + ","
		+ std::to_string(m.imbalance_shares) + ","
		+ static_cast<char>(m.imbalance_direction) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ format_price_u32(m.far_price) + ","
		+ format_price_u32(m.near_price) + ","
		+ format_price_u32(m.reference_price) + ","
		+ static_cast<char>(m.cross_type) + ","
		+ static_cast<char>(m.price_variation_indicator);
}


std::string to_string(const spec::RPII& m) {
	return std::string("N,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ static_cast<char>(m.interest_flag);
}


std::string to_string(const spec::DLCRPriceDiscovery& m) {
	return std::string("O,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_ascii_str_u64(m.stock) + ","
		+ static_cast<char>(m.is_eligible_for_trading_release) + ","
		+ format_price_u32(m.min_allowed_price) + ","
		+ format_price_u32(m.max_allowed_price) + ","
		+ format_price_u32(m.near_execution_price) + ","
		+ format_timestamp_ns(m.near_execution_time) + ","
		+ format_price_u32(m.lower_price_range_collar) + ","
		+ format_price_u32(m.upper_price_range_collar);
}


std::string to_string(const spec::MessageVariant& mv) {
	std::string s = "message variant failure";
	std::visit([&](const auto& m) {
		s = to_string(m);
	}, mv);
	return s;
}


std::ostream& operator<<(std::ostream& out, const spec::SystemEvent& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::StockDirectory& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::StockTradingAction& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::RegSHORestriction& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::MarketParticipantPosition& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::MWCBDeclineLevel& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::MWCBStatus& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::IPOQuotingPeriodUpdate& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::LULDAuctionCollar& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::OperationalHalt& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::AddOrder& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::ExecuteOrder& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::CancelOrder& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::ReplaceOrder& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::NonCrossTrade& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::CrossTrade& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::BrokenTrade& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::NOII& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::RPII& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::DLCRPriceDiscovery& m) {
	out << to_string(m);
	return out;
}


std::ostream& operator<<(std::ostream& out, const spec::MessageVariant& mv) {
	std::visit([&](const auto& m) {
		out << m;
	}, mv);
	return out;
}
}