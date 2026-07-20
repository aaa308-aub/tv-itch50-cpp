#include "itch/ios/ios.hpp"
#include "itch/spec/alpha_fields.hpp"
#include "itch/spec/messages.hpp"

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>

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

std::string to_string(const spec::MessageType e) {
	using t = spec::MessageType;
	switch (e) {
	case t::SystemEvent:               return "System Event";
	case t::StockDirectory:            return "Stock Directory";
	case t::StockTradingAction:        return "Stock Trading Action";
	case t::RegSHORestriction:         return "Reg SHO Restriction";
	case t::MarketParticipantPosition: return "Market Participant Position";
	case t::MWCBDeclineLevel:          return "MWCB Decline Level";
	case t::MWCBStatus:                return "MWCB Status";
	case t::IPOQuotingPeriodUpdate:    return "IPO Quoting Period Update";
	case t::LULDAuctionCollar:         return "LULD Auction Collar";
	case t::OperationalHalt:           return "Operational Halt";
	case t::AddOrderWithoutMPID:       return "Add Order Without MPID Attribution";
	case t::AddOrderWithMPID:          return "Add Order With MPID Attribution";
	case t::ExecuteOrder:              return "Execute Order";
	case t::ExecuteOrderWithPrice:     return "Execute Order With Price";
	case t::CancelOrder:               return "Cancel Order";
	case t::DeleteOrder:               return "Delete Order";
	case t::ReplaceOrder:              return "Replace Order";
	case t::NonCrossTrade:             return "Non-Cross Trade";
	case t::CrossTrade:                return "Cross Trade";
	case t::BrokenTrade:               return "Broken Trade";
	case t::NOII:                      return "Net Order Imbalance Indicator (NOII)";
	case t::RPII:                      return "Retail Price Improvement Indicator (RPII)";
	case t::DLCRPriceDiscovery:        return "DLCR Price Discovery";
	default:
		throw std::runtime_error(
			std::string("Invalid MessageType: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
		);
	}
}

std::string to_string(const spec::Side e) {
	using t = spec::Side;
	switch (e) {
	case t::Buy:  return "Buy";
	case t::Sell: return "Sell";
	default:
		throw std::runtime_error(
			std::string("Invalid Side: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::SystemEventCode e) {
	using t = spec::SystemEventCode;
	switch (e) {
	case t::StartOfMessages:    return "Start Of Messages";
	case t::StartOfSystemHours: return "Start Of System Hours";
	case t::StartOfMarketHours: return "Start Of Market Hours";
	case t::EndOfMarketHours:   return "End Of Market Hours";
	case t::EndOfSystemHours:   return "End Of System Hours";
	case t::EndOfMessages:      return "End Of Messages";
	default:
		throw std::runtime_error(
			std::string("Invalid SystemEventCode: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::MarketCategory e) {
	using t = spec::MarketCategory;
	switch (e) {
	case t::NasdaqGlobalSelectMarket: return "Nasdaq Global Select Market";
	case t::NasdaqGlobalMarket:       return "Nasdaq Global Market";
	case t::NasdaqCapitalMarket:      return "Nasdaq Capital Market";
	case t::NYSE:                     return "NYSE";
	case t::NYSEAmerican:             return "NYSE American";
	case t::NYSEArca:                 return "NYSE Arca";
	case t::BATSZExchange:            return "BATS Z Exchange";
	case t::InvestorsExchangeLLC:     return "Investors' Exchange, LLC";
	case t::NotAvailable:             return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid MarketCategory: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::FinancialStatus e) {
	using t = spec::FinancialStatus;
	switch (e) {
	case t::Deficient:                             return "Deficient";
	case t::Delinquent:                            return "Delinquent";
	case t::Bankrupt:                              return "Bankrupt";
	case t::Suspended:                             return "Suspended";
	case t::DeficientAndBankrupt:                  return "Deficient And Bankrupt";
	case t::DeficientAndDelinquent:                return "Deficient And Delinquent";
	case t::DelinquentAndBankrupt:                 return "Delinquent And Bankrupt";
	case t::DeficientDelinquentAndBankrupt:        return "Deficient Delinquent And Bankrupt";
	case t::CreationsOrRedemptionsSuspendedForETP: return "Creations And/Or Redemptions Suspended For ETP";
	case t::Normal:                                return "Normal";
	case t::NotAvailable:                          return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid FinancialStatus: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::RoundLotsOnlyFlag e) {
	using t = spec::RoundLotsOnlyFlag;
	switch (e) {
	case t::Yes: return "Yes";
	case t::No:  return "No";
	default:
		throw std::runtime_error(
			std::string("Invalid RoundLotsOnlyFlag: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::IssueClassification e) {
	using t = spec::IssueClassification;
	switch (e) {
	case t::AmericanDepositaryShare:    return "American Depositary Share";
	case t::Bond:                       return "Bond";
	case t::CommonStock:                return "Common Stock";
	case t::DepositoryReceipt:          return "Depository Receipt";
	case t::Rule144A:                   return "144A";
	case t::LimitedPartnership:         return "Limited Partnership";
	case t::Notes:                      return "Notes";
	case t::OrdinaryShare:              return "Ordinary Share";
	case t::PreferredStock:             return "Preferred Stock";
	case t::OtherSecurities:            return "Other Securities";
	case t::Right:                      return "Right";
	case t::SharesOfBeneficialInterest: return "Shares Of Beneficial Interest";
	case t::ConvertibleDebenture:       return "Convertible Debenture";
	case t::Unit:                       return "Unit";
	case t::UnitsOrBenifInt:            return "Units/Benif Int";
	case t::Warrant:                    return "Warrant";
	default:
		throw std::runtime_error(
			std::string("Invalid IssueClassification: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::IssueSubType e) {
	using t = spec::IssueSubType;
	switch (e) {
	case t::PreferredTrustSecurities:                     return "Preferred Trust Securities";
	case t::AlphaIndexETNs:                               return "Alpha Index ETNs";
	case t::IndexBasedDerivative:                         return "Index Based Derivative";
	case t::CommonShares:                                 return "Common Shares";
	case t::CommodityBasedTrustShares:                    return "Commodity Based Trust Shares";
	case t::CommodityFuturesTrustShares:                  return "Commodity Futures Trust Shares";
	case t::CommodityLinkedSecurities:                    return "Commodity-Linked Securities";
	case t::CommodityIndexTrustShares:                    return "Commodity Index Trust Shares";
	case t::CollateralizedMortgageObligation:             return "Collateralized Mortgage Obligation";
	case t::CurrencyTrustShares:                          return "Currency Trust Shares";
	case t::CommodityCurrencyLinkedSecurities:            return "Commodity-Currency-Linked Securities";
	case t::CurrencyWarrants:                             return "Currency Warrants";
	case t::GlobalDepositaryShares:                       return "Global Depositary Shares";
	case t::ETFPortfolioDepositaryReceipt:                return "ETF-Portfolio Depositary Receipt";
	case t::EquityGoldShares:                             return "Equity Gold Shares";
	case t::ETNEquityIndexLinkedSecurities:               return "ETN-Equity Index-Linked Securities";
	case t::NextSharesExchangeTradedManagedFund:          return "NextShares Exchange Traded Managed Fund";
	case t::ExchangeTradedNotes:                          return "Exchange Traded Notes";
	case t::EquityUnits:                                  return "Equity Units";
	case t::HOLDRS:                                       return "HOLDRS";
	case t::ETNFixedIncomeLinkedSecurities:               return "ETN-Fixed Income-Linked Securities";
	case t::ETNFuturesLinkedSecurities:                   return "ETN-Futures-Linked Securities";
	case t::GlobalShares:                                 return "Global Shares";
	case t::ETFIndexFundShares:                           return "ETF-Index Fund Shares";
	case t::InterestRate:                                 return "Interest Rate";
	case t::IndexWarrant:                                 return "Index Warrant";
	case t::IndexLinkedExchangeableNotes:                 return "Index-Linked Exchangeable Notes";
	case t::CorporateBackedTrustSecurity:                 return "Corporate Backed Trust Security";
	case t::ContingentLitigationRight:                    return "Contingent Litigation Right";
	case t::LLCSecurity:                                  return "Limited Liability Company";
	case t::EquityBasedDerivative:                        return "Equity-Based Derivative";
	case t::ManagedFundShares:                            return "Managed Fund Shares";
	case t::ETNMultiFactorIndexLinkedSecurities:          return "ETN-Multi-Factor Index-Linked Securities";
	case t::ManagedTrustSecurities:                       return "Managed Trust Securities";
	case t::NYRegistryShares:                             return "NY Registry Shares";
	case t::OpenEndedMutualFund:                          return "Open Ended Mutual Fund";
	case t::PrivatelyHeldSecurity:                        return "Privately Held Security";
	case t::PoisonPill:                                   return "Poison Pill";
	case t::PartnershipUnits:                             return "Partnership Units";
	case t::ClosedEndFunds:                               return "Closed-End Funds";
	case t::RegS:                                         return "Reg-S";
	case t::CommodityRedeemableCommodityLinkedSecurities:
		return "Commodity-Redeemable Commodity-Linked Securities";
	case t::ETNRedeemableFuturesLinkedSecurities:         return "ETN-Redeemable Futures-Linked Securities";
	case t::REIT:                                         return "REIT";
	case t::CommodityRedeemableCurrencyLinkedSecurities:
		return "Commodity-Redeemable Currency-Linked Securities";
	case t::SEED:                                         return "SEED";
	case t::SpotRateClosing:                              return "Spot Rate Closing";
	case t::SpotRateIntraday:                             return "Spot Rate Intraday";
	case t::TrackingStock:                                return "Tracking Stock";
	case t::TrustCertificates:                            return "Trust Certificates";
	case t::TrustUnits:                                   return "Trust Units";
	case t::Portal:                                       return "Portal";
	case t::ContingentValueRight:                         return "Contingent Value Right";
	case t::TrustIssuedReceipts:                          return "Trust Issued Receipts";
	case t::WorldCurrencyOption:                          return "World Currency Option";
	case t::Trust:                                        return "Trust";
	case t::Other:                                        return "Other";
	case t::NotApplicable:                                return "Not Applicable";
	default:
		throw std::runtime_error(
			std::string("Invalid IssueSubType of underlying value ")
			+ std::to_string(static_cast<std::uint16_t>(e))
			);
	}
}

std::string to_string(const spec::Authenticity e) {
	using t = spec::Authenticity;
	switch (e) {
	case t::LiveOrProduction: return "Live/Production";
	case t::Test:             return "Test";
	default:
		throw std::runtime_error(
			std::string("Invalid Authenticity: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::ShortSaleThreshold e) {
	using t = spec::ShortSaleThreshold;
	switch (e) {
	case t::RestrictedUnderSECRule203b3: return "Restricted Under SEC Rule 203(b)(3)";
	case t::NotRestricted:               return "Not Restricted";
	case t::NotAvailable:                return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid ShortSaleThreshold: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::IPOFlag e) {
	using t = spec::IPOFlag;
	switch (e) {
	case t::Yes:          return "Yes";
	case t::No:           return "No";
	case t::NotAvailable: return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid IPOFlag: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::LULDRefPriceTier e) {
	using t = spec::LULDRefPriceTier;
	switch (e) {
	case t::Tier1NMSStocksAndSelectETPs: return "Tier 1 NMS Stocks And Select ETPs";
	case t::Tier2NMSStocks:              return "Tier 2 NMS Stocks";
	case t::NotAvailable:                return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid LULDRefPriceTier: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::ETPFlag e) {
	using t = spec::ETPFlag;
	switch (e) {
	case t::Yes:          return "Yes";
	case t::No:           return "No";
	case t::NotAvailable: return "Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid ETPFlag: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::InverseETPFlag e) {
	using t = spec::InverseETPFlag;
	switch (e) {
	case t::Yes: return "Yes";
	case t::No:  return "No";
	default:
		throw std::runtime_error(
			std::string("Invalid InverseETPFlag: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::StockTradingState e) {
	using t = spec::StockTradingState;
	switch (e) {
	case t::HaltedAcrossAllUSEquitiesOrSROs: return "Halted Across All US Equity Markets/SROs";
	case t::PausedAcrossAllUSEquitiesOrSROs: return "Paused Across All US Equity Markets/SROs";
	case t::QuotationOnlyPeriod:             return "Quotation Only Period For Cross-SRO Halt/Pause";
	case t::TradingOnNasdaq:                 return "Trading On Nasdaq";
	default:
		throw std::runtime_error(
			std::string("Invalid StockTradingState: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::TradingActionReason e) {
	using t = spec::TradingActionReason;
	switch (e) {
	case t::HaltNewsPending:                           return "Halt News Pending";
	case t::HaltNewsDisseminated:                      return "Halt News Disseminated";
	case t::SingleSecurityTradingPauseInEffect:        return "Single Security Trading Pause In Effect";
	case t::RegulatoryHaltExtraordinaryMarketActivity:
		return "Regulatory Halt -- Extraordinary Market Activity";
	case t::HaltETF:                                   return "Halt ETF";
	case t::TradingHaltedForInfoToListingMarket:
		return "Trading Halted For Info Requested By Listing Market";
	case t::HaltNonCompliance:                         return "Halt Non-Compliance";
	case t::HaltFilingsNotCurrent:                     return "Halt Filings Not Current";
	case t::HaltSECTradingSuspension:                  return "Halt SEC Trading Suspension";
	case t::HaltRegulatoryConcern:                     return "Halt Regulatory Concern";
	case t::OperationsHalt:                            return "Operations Halt -- Contact Market Operations";
	case t::VolatilityTradingPause:                    return "Volatility Trading Pause";
	case t::VolatilityTradingPauseStraddleCondition:
		return "Volatility Trading Pause -- Straddle Condition";
	case t::MarketWideCircuitBreakerHaltLevel1:        return "Market Wide Circuit Breaker Halt -- Level 1";
	case t::MarketWideCircuitBreakerHaltLevel2:        return "Market Wide Circuit Breaker Halt -- Level 2";
	case t::MarketWideCircuitBreakerHaltLevel3:        return "Market Wide Circuit Breaker Halt -- Level 3";
	case t::MarketWideCircuitBreakerHaltCarryOver:
		return "Market Wide Circuit Breaker Halt -- Carry Over From Previous Day";
	case t::IPOIssueNotYetTrading:                     return "IPO Issue Not Yet Trading";
	case t::CorporateAction:                           return "Corporate Action";
	case t::QuotationNotAvailable:                     return "Quotation Not Available";
	case t::NewsAndResumptionTimes:                    return "News And Resumption Times";
	case t::SingleSecurityTradingPauseOrQuotationOnly:
		return "Single Security Trading Pause/Quotation Only Period";
	case t::QualificationsIssuesReviewedOrResolved:
		return "Qualifications Issues Reviewed/Resolved -- Trading Resumed";
	case t::FilingRequirementsSatisfiedOrResolved:
		return "Filing Requirements Satisfied/Resolved -- Trading Resumed";
	case t::IssuerNewsNotForthcoming:
		return "Issuer News Not Forthcoming -- Trading Resumed";
	case t::QualificationsHaltEndedAndMaintenanceDone:
		return "Qualifications Halt Ended And Maintenance Requirements Met -- Trading Resumed";
	case t::QualificationsHaltConcludedAndFilingsMet:
		return "Qualifications Halt Concluded And Filings Met -- Trading Resumed";
	case t::TradeHaltConcludedByOtherRegulatoryAuth:
		return "Trade Halt Concluded By Other Regulatory Authority -- Trading Resumed";
	case t::MarketWideCircuitBreakerResumption:        return "Market Wide Circuit Breaker Resumption";
	case t::NewIssueAvailable:                         return "New Issue Available";
	case t::IssueAvailable:                            return "Issue Available";
	case t::IPOSecurityReleasedForQuotation:           return "IPO Security Released For Quotation";
	case t::IPOSecurityPositioningWindowExtension:
		return "IPO Security -- Positioning Window Extension";
	case t::ReasonNotAvailable:                        return "Reason Not Available";
	default:
		throw std::runtime_error(
			std::string("Invalid TradingActionReason of underlying value ")
			+ std::to_string(static_cast<std::uint32_t>(e))
			);
	}
}

std::string to_string(const spec::RegSHOAction e) {
	using t = spec::RegSHOAction;
	switch (e) {
	case t::NoPriceTest:
		return "No Price Test In Place";
	case t::ShortSalePriceTestRestriction:
		return "Short Sale Price Test Restriction Due to Intraday Price Drop";
	case t::ShortSalePriceTestRestrictionRemainsInEffect:
		return "Short Sale Price Test Restriction Remains In Effect";
	default:
		throw std::runtime_error(
			std::string("Invalid Reg SHO Action: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::PrimaryMarketMakerFlag e) {
	using t = spec::PrimaryMarketMakerFlag;
	switch (e) {
	case t::Yes: return "Yes";
	case t::No:  return "No";
	default:
		throw std::runtime_error(
			std::string("Invalid PrimaryMarketMakerFlag: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::MarketMakerMode e) {
	using t = spec::MarketMakerMode;
	switch (e) {
	case t::Normal:       return "Normal";
	case t::Passive:      return "Passive";
	case t::Syndicate:    return "Syndicate";
	case t::PreSyndicate: return "Pre-Syndicate";
	case t::Penalty:      return "Penalty";
	default:
		throw std::runtime_error(
			std::string("Invalid MarketMakerMode: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::MarketParticipantState e) {
	using t = spec::MarketParticipantState;
	switch (e) {
	case t::Active:             return "Active";
	case t::ExcusedOrWithdrawn: return "Excused/Withdrawn";
	case t::Withdrawn:          return "Withdrawn";
	case t::Suspended:          return "Suspended";
	case t::Deleted:            return "Deleted";
	default:
		throw std::runtime_error(
			std::string("Invalid MarketParticipantState: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::MWCBBreachLevel e) {
	using t = spec::MWCBBreachLevel;
	switch (e) {
	case t::Level1: return "Level 1";
	case t::Level2: return "Level 2";
	case t::Level3: return "Level 3";
	default:
		throw std::runtime_error(
			std::string("Invalid MWCBBreachLevel: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::IPOQuotationReleaseQualifier e) {
	using t = spec::IPOQuotationReleaseQualifier;
	switch (e) {
	case t::AnticipatedReleaseTime: return "Anticipated Quotation Release Time";
	case t::CanceledOrPostponed:    return "IPO Release Canceled/Postponed";
	default:
		throw std::runtime_error(
			std::string("Invalid IPOQuotationReleaseQualifier: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::MarketCode e) {
	using t = spec::MarketCode;
	switch (e) {
	case t::Nasdaq: return "Nasdaq";
	case t::BX:     return "BX";
	case t::PSX:    return "PSX";
	default:
		throw std::runtime_error(
			std::string("Invalid MarketCode: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::OperationalHaltAction e) {
	using t = spec::OperationalHaltAction;
	switch (e) {
	case t::Halted:     return "Halted";
	case t::HaltLifted: return "Halt Lifted -- Trading Resumed";
	default:
		throw std::runtime_error(
			std::string("Invalid OperationalHaltAction: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::PrintableFlag e) {
	using t = spec::PrintableFlag;
	switch (e) {
	case t::NonPrintable: return "Non-Printable";
	case t::Printable:    return "Printable";
	default:
		throw std::runtime_error(
			std::string("Invalid PrintableFlag: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::CrossType e) {
	using t = spec::CrossType;
	switch (e) {
	case t::NasdaqOpeningCross:                     return "Nasdaq Opening Cross";
	case t::NasdaqClosingCross:                     return "Nasdaq Closing Cross";
	case t::CrossForIPOAndHaltedOrPausedSecurities: return "Cross For IPO And Halted/Paused Securities";
	case t::ExtendedTradingClose:                   return "Extended Trading Close";
	default:
		throw std::runtime_error(
			std::string("Invalid CrossType: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::ImbalanceDirection e) {
	using t = spec::ImbalanceDirection;
	switch (e) {
	case t::Buy:          return "Buy Imbalance";
	case t::Sell:         return "Sell Imbalance";
	case t::None:         return "No Imbalance";
	case t::NotAvailable: return "Insufficient Orders To Calculate";
	case t::Paused:       return "Paused";
	default:
		throw std::runtime_error(
			std::string("Invalid ImbalanceDirection: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::PriceVariationPercentage e) {
	using t = spec::PriceVariationPercentage;
	switch (e) {
	case t::LessThanOnePercent:       return "Less Than 1%";
	case t::OneToSubTwoPercent:       return "1 To 1.99%";
	case t::TwoToSubThreePercent:     return "2 To 2.99%";
	case t::ThreeToSubFourPercent:    return "3 To 3.99%";
	case t::FourToSubFivePercent:     return "4 To 4.99%";
	case t::FiveToSubSixPercent:      return "5 To 5.99%";
	case t::SixToSubSevenPercent:     return "6 To 6.99%";
	case t::SevenToSubEightPercent:   return "7 To 7.99%";
	case t::EightToSubNinePercent:    return "8 To 8.99%";
	case t::NineToSubTenPercent:      return "9 To 9.99%";
	case t::TenToSubTwentyPercent:    return "10 To 19.99%";
	case t::TwentyToSubThirtyPercent: return "20 To 29.99%";
	case t::ThirtyPercentOrGreater:   return "30% Or Greater";
	case t::NotAvailable:             return "Cannot Be Calculated";
	default:
		throw std::runtime_error(
			std::string("Invalid PriceVariationPercentage: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::InterestFlagRPII e) {
	using t = spec::InterestFlagRPII;
	switch (e) {
	case t::RPIOrdersAvailableOnBuySide:   return "RPI Orders Available On Buy Side";
	case t::RPIOrdersAvailableOnSellSide:  return "RPI Orders Available On Sell Side";
	case t::RPIOrdersAvailableOnBothSides: return "RPI Orders Available On Both Sides";
	case t::NoRPIOrdersAvailable:          return "No RPI Orders Available";
	default:
		throw std::runtime_error(
			std::string("Invalid InterestFlagRPII: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::EligibleForTradingReleaseFlag e) {
	using t = spec::EligibleForTradingReleaseFlag;
	switch (e) {
	case t::NotEligible: return "Not Eligible";
	case t::Eligible:    return "Eligible";
	default:
		throw std::runtime_error(
			std::string("Invalid EligibleForTradingReleaseFlag: ")
			+ "'" + std::string(1, static_cast<char>(e)) + "'"
			);
	}
}

std::string to_string(const spec::SystemEvent& m) {
	return std::string("S,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ enum_8b_to_str(m.event_code);
}

std::string to_string(const spec::StockDirectory& m) {
	return std::string("R,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_str_padded(m.stock) + ","
		+ enum_8b_to_str(m.market_category) + ","
		+ enum_8b_to_str(m.financial_status) + ","
		+ std::to_string(m.round_lot_size) + ","
		+ enum_8b_to_str(m.is_round_lots_only) + ","
		+ enum_8b_to_str(m.issue_classification) + ","
		+ to_str_padded(static_cast<std::uint16_t>(m.issue_subtype)) + ","
		+ enum_8b_to_str(m.authenticity) + ","
		+ enum_8b_to_str(m.short_sale_threshold) + ","
		+ enum_8b_to_str(m.is_ipo) + ","
		+ enum_8b_to_str(m.luld_ref_price_tier) + ","
		+ enum_8b_to_str(m.is_etp) + ","
		+ std::to_string(m.etp_leverage_factor) + ","
		+ enum_8b_to_str(m.is_inverse_etp);
}

std::string to_string(const spec::StockTradingAction& m) {
	return std::string("H,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_str_padded(m.stock) + ","
		+ enum_8b_to_str(m.trading_state) + ","
		// reserved field skipped.
		+ to_str_padded(static_cast<std::uint32_t>(m.trading_action_reason));
}

std::string to_string(const spec::RegSHORestriction& m) {
	return std::string("Y,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_str_padded(m.stock) + ","
		+ static_cast<char>(m.reg_sho_action);
}

std::string to_string(const spec::MarketParticipantPosition& m) {
	return std::string("L,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_str_padded(m.mp_id) + ","
		+ to_str_padded(m.stock) + ","
		+ enum_8b_to_str(m.is_primary_market_maker) + ","
		+ enum_8b_to_str(m.market_maker_mode) + ","
		+ enum_8b_to_str(m.market_participant_state);
}

std::string to_string(const spec::MWCBDeclineLevel& m) {
	return std::string("V,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ format_price(m.price_level1) + ","
		+ format_price(m.price_level2) + ","
		+ format_price(m.price_level3);
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
		+ to_str_padded(m.stock) + ","
		+ format_timestamp_sec(m.ipo_quotation_time) + ","
		+ static_cast<char>(m.ipo_quotation_release_qualifier) + ","
		+ format_price<std::uint32_t>(m.ipo_price);
}

std::string to_string(const spec::LULDAuctionCollar& m) {
	return std::string("J,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_str_padded(m.stock) + ","
		+ format_price(m.reference_price) + ","
		+ format_price(m.upper_price) + ","
		+ format_price(m.lower_price) + ","
		+ std::to_string(m.number_of_extensions);
}

std::string to_string(const spec::OperationalHalt& m) {
	return std::string("h,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_str_padded(m.stock) + ","
		+ enum_8b_to_str(m.market_code) + ","
		+ enum_8b_to_str(m.operational_halt_action);
}

std::string to_string(const spec::AddOrder& m) {
	const bool with_mp_id = (m.mp_id != spec::DEFAULT_NON_ATTRIBUTED_MPID);

	return std::string((with_mp_id) ? "F" : "A") + ","
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.order_id) + ","
		+ enum_8b_to_str(m.side) + ","
		+ std::to_string(m.shares) + ","
		+ to_str_padded(m.stock) + ","
		+ format_price(m.price)
		+ ((with_mp_id) ? "," + to_str_padded(m.mp_id) : "");
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
		+ ((with_price) ? "," + format_price(m.executed_price) : "");
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
		+ format_price(m.price);
}

std::string to_string(const spec::NonCrossTrade& m) {
	return std::string("P,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.order_id) + ","
		+ enum_8b_to_str(m.side) + ","
		+ std::to_string(m.shares) + ","
		+ to_str_padded(m.stock) + ","
		+ format_price(m.price) + ","
		+ std::to_string(m.match_number);
}

std::string to_string(const spec::CrossTrade& m) {
	return std::string("Q,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ std::to_string(m.shares) + ","
		+ to_str_padded(m.stock) + ","
		+ format_price(m.price) + ","
		+ std::to_string(m.match_number) + ","
		+ enum_8b_to_str(m.cross_type);
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
		+ enum_8b_to_str(m.imbalance_direction) + ","
		+ to_str_padded(m.stock) + ","
		+ format_price(m.far_price) + ","
		+ format_price(m.near_price) + ","
		+ format_price(m.reference_price) + ","
		+ enum_8b_to_str(m.cross_type) + ","
		+ enum_8b_to_str(m.price_variation_indicator);
}

std::string to_string(const spec::RPII& m) {
	return std::string("N,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_str_padded(m.stock) + ","
		+ enum_8b_to_str(m.interest_flag);
}

std::string to_string(const spec::DLCRPriceDiscovery& m) {
	return std::string("O,")
		+ std::to_string(m.stock_locate) + ","
		+ std::to_string(m.tracking_number) + ","
		+ format_timestamp_ns(m.timestamp) + ","
		+ to_str_padded(m.stock) + ","
		+ enum_8b_to_str(m.is_eligible_for_trading_release) + ","
		+ format_price(m.min_allowed_price) + ","
		+ format_price(m.max_allowed_price) + ","
		+ format_price(m.near_execution_price) + ","
		+ format_timestamp_ns(m.near_execution_time) + ","
		+ format_price(m.lower_price_range_collar) + ","
		+ format_price(m.upper_price_range_collar);
}

std::string to_string(const spec::MessageVariant& mv) {
	std::string s;
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

} // namespace itch::ios
