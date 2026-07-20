#ifndef TV_ITCH50_CPP_ALPHA_FIELDS_HPP
#define TV_ITCH50_CPP_ALPHA_FIELDS_HPP

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <type_traits>

namespace itch::spec {

template <typename T>
constexpr T char_to_uint(std::initializer_list<char> chars) noexcept {
	static_assert(std::is_same_v<T , std::uint8_t > ||
	              std::is_same_v<T , std::uint16_t> ||
	              std::is_same_v<T , std::uint32_t> ||
	              std::is_same_v<T , std::uint64_t>);

	if (chars.size() != sizeof(T)) {
		std::cerr << "error: invalid initializer_list size";
		std::cerr.flush();
		std::abort();
	}

	T x = 0;
	int i = static_cast<int>((sizeof(T) - 1) * 8);

	for (const char c : chars) {
		x |= static_cast<T>(static_cast<unsigned char>(c)) << i;
		i -= 8;
	}

	return x;
}

enum class MessageType : std::uint8_t {
	SystemEvent               = char_to_uint<std::uint8_t>({ 'S' }),
	StockDirectory            = char_to_uint<std::uint8_t>({ 'R' }),
	StockTradingAction        = char_to_uint<std::uint8_t>({ 'H' }),
	RegSHORestriction         = char_to_uint<std::uint8_t>({ 'Y' }),
	MarketParticipantPosition = char_to_uint<std::uint8_t>({ 'L' }),
	MWCBDeclineLevel          = char_to_uint<std::uint8_t>({ 'V' }),
	MWCBStatus                = char_to_uint<std::uint8_t>({ 'W' }),
	IPOQuotingPeriodUpdate    = char_to_uint<std::uint8_t>({ 'K' }),
	LULDAuctionCollar         = char_to_uint<std::uint8_t>({ 'J' }),
	OperationalHalt           = char_to_uint<std::uint8_t>({ 'h' }),
	AddOrderWithoutMPID       = char_to_uint<std::uint8_t>({ 'A' }),
	AddOrderWithMPID          = char_to_uint<std::uint8_t>({ 'F' }),
	ExecuteOrder              = char_to_uint<std::uint8_t>({ 'E' }),
	ExecuteOrderWithPrice     = char_to_uint<std::uint8_t>({ 'C' }),
	CancelOrder               = char_to_uint<std::uint8_t>({ 'X' }),
	DeleteOrder               = char_to_uint<std::uint8_t>({ 'D' }),
	ReplaceOrder              = char_to_uint<std::uint8_t>({ 'U' }),
	NonCrossTrade             = char_to_uint<std::uint8_t>({ 'P' }),
	CrossTrade                = char_to_uint<std::uint8_t>({ 'Q' }),
	BrokenTrade               = char_to_uint<std::uint8_t>({ 'B' }),
	NOII                      = char_to_uint<std::uint8_t>({ 'I' }),
	RPII                      = char_to_uint<std::uint8_t>({ 'N' }),
	DLCRPriceDiscovery        = char_to_uint<std::uint8_t>({ 'O' }),
};

enum class Side : std::uint8_t {
	Buy  = char_to_uint<std::uint8_t>({ 'B' }),
	Sell = char_to_uint<std::uint8_t>({ 'S' }),
};

enum class SystemEventCode : std::uint8_t {
	StartOfMessages    = char_to_uint<std::uint8_t>({ 'O' }),
	StartOfSystemHours = char_to_uint<std::uint8_t>({ 'S' }),
	StartOfMarketHours = char_to_uint<std::uint8_t>({ 'Q' }),
	EndOfMarketHours   = char_to_uint<std::uint8_t>({ 'M' }),
	EndOfSystemHours   = char_to_uint<std::uint8_t>({ 'E' }),
	EndOfMessages      = char_to_uint<std::uint8_t>({ 'C' }),
};

enum class MarketCategory : std::uint8_t {
	NasdaqGlobalSelectMarket = char_to_uint<std::uint8_t>({ 'Q' }),
	NasdaqGlobalMarket       = char_to_uint<std::uint8_t>({ 'G' }),
	NasdaqCapitalMarket      = char_to_uint<std::uint8_t>({ 'S' }),
	NYSE                     = char_to_uint<std::uint8_t>({ 'N' }),
	NYSEAmerican             = char_to_uint<std::uint8_t>({ 'A' }),
	NYSEArca                 = char_to_uint<std::uint8_t>({ 'P' }),
	BATSZExchange            = char_to_uint<std::uint8_t>({ 'Z' }),
	InvestorsExchangeLLC     = char_to_uint<std::uint8_t>({ 'V' }),
	NotAvailable             = char_to_uint<std::uint8_t>({ ' ' }),
};

enum class FinancialStatus : std::uint8_t {
	Deficient                             = char_to_uint<std::uint8_t>({ 'D' }),
	Delinquent                            = char_to_uint<std::uint8_t>({ 'E' }),
	Bankrupt                              = char_to_uint<std::uint8_t>({ 'Q' }),
	Suspended                             = char_to_uint<std::uint8_t>({ 'S' }),
	DeficientAndBankrupt                  = char_to_uint<std::uint8_t>({ 'G' }),
	DeficientAndDelinquent                = char_to_uint<std::uint8_t>({ 'H' }),
	DelinquentAndBankrupt                 = char_to_uint<std::uint8_t>({ 'J' }),
	DeficientDelinquentAndBankrupt        = char_to_uint<std::uint8_t>({ 'K' }),
	CreationsOrRedemptionsSuspendedForETP = char_to_uint<std::uint8_t>({ 'C' }),
	Normal                                = char_to_uint<std::uint8_t>({ 'N' }),
	NotAvailable                          = char_to_uint<std::uint8_t>({ ' ' }),
};

enum class RoundLotsOnlyFlag: std::uint8_t {
	Yes = char_to_uint<std::uint8_t>({ 'Y' }),
	No  = char_to_uint<std::uint8_t>({ 'N' }),
};

enum class IssueClassification : std::uint8_t {
	AmericanDepositaryShare    = char_to_uint<std::uint8_t>({ 'A' }),
	Bond                       = char_to_uint<std::uint8_t>({ 'B' }),
	CommonStock                = char_to_uint<std::uint8_t>({ 'C' }),
	DepositoryReceipt          = char_to_uint<std::uint8_t>({ 'F' }),
	Rule144A                   = char_to_uint<std::uint8_t>({ 'I' }),
	LimitedPartnership         = char_to_uint<std::uint8_t>({ 'L' }),
	Notes                      = char_to_uint<std::uint8_t>({ 'N' }),
	OrdinaryShare              = char_to_uint<std::uint8_t>({ 'O' }),
	PreferredStock             = char_to_uint<std::uint8_t>({ 'P' }),
	OtherSecurities            = char_to_uint<std::uint8_t>({ 'Q' }),
	Right                      = char_to_uint<std::uint8_t>({ 'R' }),
	SharesOfBeneficialInterest = char_to_uint<std::uint8_t>({ 'S' }),
	ConvertibleDebenture       = char_to_uint<std::uint8_t>({ 'T' }),
	Unit                       = char_to_uint<std::uint8_t>({ 'U' }),
	UnitsOrBenifInt            = char_to_uint<std::uint8_t>({ 'V' }),
	Warrant                    = char_to_uint<std::uint8_t>({ 'W' }),
};

enum class IssueSubType : std::uint16_t {
	PreferredTrustSecurities                     = char_to_uint<std::uint16_t>({ 'A' , ' ' }),
	AlphaIndexETNs                               = char_to_uint<std::uint16_t>({ 'A' , 'I' }),
	IndexBasedDerivative                         = char_to_uint<std::uint16_t>({ 'B' , ' ' }),
	CommonShares                                 = char_to_uint<std::uint16_t>({ 'C' , ' ' }),
	CommodityBasedTrustShares                    = char_to_uint<std::uint16_t>({ 'C' , 'B' }),
	CommodityFuturesTrustShares                  = char_to_uint<std::uint16_t>({ 'C' , 'F' }),
	CommodityLinkedSecurities                    = char_to_uint<std::uint16_t>({ 'C' , 'L' }),
	CommodityIndexTrustShares                    = char_to_uint<std::uint16_t>({ 'C' , 'M' }),
	CollateralizedMortgageObligation             = char_to_uint<std::uint16_t>({ 'C' , 'O' }),
	CurrencyTrustShares                          = char_to_uint<std::uint16_t>({ 'C' , 'T' }),
	CommodityCurrencyLinkedSecurities            = char_to_uint<std::uint16_t>({ 'C' , 'U' }),
	CurrencyWarrants                             = char_to_uint<std::uint16_t>({ 'C' , 'W' }),
	GlobalDepositaryShares                       = char_to_uint<std::uint16_t>({ 'D' , ' ' }),
	ETFPortfolioDepositaryReceipt                = char_to_uint<std::uint16_t>({ 'E' , ' ' }),
	EquityGoldShares                             = char_to_uint<std::uint16_t>({ 'E' , 'G' }),
	ETNEquityIndexLinkedSecurities               = char_to_uint<std::uint16_t>({ 'E' , 'I' }),
	NextSharesExchangeTradedManagedFund          = char_to_uint<std::uint16_t>({ 'E' , 'M' }),
	ExchangeTradedNotes                          = char_to_uint<std::uint16_t>({ 'E' , 'N' }),
	EquityUnits                                  = char_to_uint<std::uint16_t>({ 'E' , 'U' }),
	HOLDRS                                       = char_to_uint<std::uint16_t>({ 'F' , ' ' }),
	ETNFixedIncomeLinkedSecurities               = char_to_uint<std::uint16_t>({ 'F' , 'I' }),
	ETNFuturesLinkedSecurities                   = char_to_uint<std::uint16_t>({ 'F' , 'L' }),
	GlobalShares                                 = char_to_uint<std::uint16_t>({ 'G' , ' ' }),
	ETFIndexFundShares                           = char_to_uint<std::uint16_t>({ 'I' , ' ' }),
	InterestRate                                 = char_to_uint<std::uint16_t>({ 'I' , 'R' }),
	IndexWarrant                                 = char_to_uint<std::uint16_t>({ 'I' , 'W' }),
	IndexLinkedExchangeableNotes                 = char_to_uint<std::uint16_t>({ 'I' , 'X' }),
	CorporateBackedTrustSecurity                 = char_to_uint<std::uint16_t>({ 'J' , ' ' }),
	ContingentLitigationRight                    = char_to_uint<std::uint16_t>({ 'L' , ' ' }),
	LLCSecurity                                  = char_to_uint<std::uint16_t>({ 'L' , 'L' }),
	EquityBasedDerivative                        = char_to_uint<std::uint16_t>({ 'M' , ' ' }),
	ManagedFundShares                            = char_to_uint<std::uint16_t>({ 'M' , 'F' }),
	ETNMultiFactorIndexLinkedSecurities          = char_to_uint<std::uint16_t>({ 'M' , 'L' }),
	ManagedTrustSecurities                       = char_to_uint<std::uint16_t>({ 'M' , 'T' }),
	NYRegistryShares                             = char_to_uint<std::uint16_t>({ 'N' , ' ' }),
	OpenEndedMutualFund                          = char_to_uint<std::uint16_t>({ 'O' , ' ' }),
	PrivatelyHeldSecurity                        = char_to_uint<std::uint16_t>({ 'P' , ' ' }),
	PoisonPill                                   = char_to_uint<std::uint16_t>({ 'P' , 'P' }),
	PartnershipUnits                             = char_to_uint<std::uint16_t>({ 'P' , 'U' }),
	ClosedEndFunds                               = char_to_uint<std::uint16_t>({ 'Q' , ' ' }),
	RegS                                         = char_to_uint<std::uint16_t>({ 'R' , ' ' }),
	CommodityRedeemableCommodityLinkedSecurities = char_to_uint<std::uint16_t>({ 'R' , 'C' }),
	ETNRedeemableFuturesLinkedSecurities         = char_to_uint<std::uint16_t>({ 'R' , 'F' }),
	REIT                                         = char_to_uint<std::uint16_t>({ 'R' , 'T' }),
	CommodityRedeemableCurrencyLinkedSecurities  = char_to_uint<std::uint16_t>({ 'R' , 'U' }),
	SEED                                         = char_to_uint<std::uint16_t>({ 'S' , ' ' }),
	SpotRateClosing                              = char_to_uint<std::uint16_t>({ 'S' , 'C' }),
	SpotRateIntraday                             = char_to_uint<std::uint16_t>({ 'S' , 'I' }),
	TrackingStock                                = char_to_uint<std::uint16_t>({ 'T' , ' ' }),
	TrustCertificates                            = char_to_uint<std::uint16_t>({ 'T' , 'C' }),
	TrustUnits                                   = char_to_uint<std::uint16_t>({ 'T' , 'U' }),
	Portal                                       = char_to_uint<std::uint16_t>({ 'U' , ' ' }),
	ContingentValueRight                         = char_to_uint<std::uint16_t>({ 'V' , ' ' }),
	TrustIssuedReceipts                          = char_to_uint<std::uint16_t>({ 'W' , ' ' }),
	WorldCurrencyOption                          = char_to_uint<std::uint16_t>({ 'W' , 'C' }),
	Trust                                        = char_to_uint<std::uint16_t>({ 'X' , ' ' }),
	Other                                        = char_to_uint<std::uint16_t>({ 'Y' , ' ' }),
	NotApplicable                                = char_to_uint<std::uint16_t>({ 'Z' , ' ' }),
};

enum class Authenticity : std::uint8_t {
	LiveOrProduction = char_to_uint<std::uint8_t>({ 'P' }),
	Test             = char_to_uint<std::uint8_t>({ 'T' }),
};

enum class ShortSaleThreshold : std::uint8_t {
	RestrictedUnderSECRule203b3 = char_to_uint<std::uint8_t>({ 'Y' }),
	NotRestricted               = char_to_uint<std::uint8_t>({ 'N' }),
	NotAvailable                = char_to_uint<std::uint8_t>({ ' ' }),
};

enum class IPOFlag : std::uint8_t {
	Yes          = char_to_uint<std::uint8_t>({ 'Y' }),
	No           = char_to_uint<std::uint8_t>({ 'N' }),
	NotAvailable = char_to_uint<std::uint8_t>({ ' ' }),
};

enum class LULDRefPriceTier : std::uint8_t {
	Tier1NMSStocksAndSelectETPs = char_to_uint<std::uint8_t>({ '1' }),
	Tier2NMSStocks              = char_to_uint<std::uint8_t>({ '2' }),
	NotAvailable                = char_to_uint<std::uint8_t>({ ' ' }),
};

enum class ETPFlag : std::uint8_t {
	Yes          = char_to_uint<std::uint8_t>({ 'Y' }),
	No           = char_to_uint<std::uint8_t>({ 'N' }),
	NotAvailable = char_to_uint<std::uint8_t>({ ' ' }),
};

enum class InverseETPFlag : std::uint8_t {
	Yes = char_to_uint<std::uint8_t>({ 'Y' }),
	No  = char_to_uint<std::uint8_t>({ 'N' }),
};

enum class StockTradingState : std::uint8_t {
	HaltedAcrossAllUSEquitiesOrSROs = char_to_uint<std::uint8_t>({ 'H' }),
	PausedAcrossAllUSEquitiesOrSROs = char_to_uint<std::uint8_t>({ 'P' }),
	QuotationOnlyPeriod             = char_to_uint<std::uint8_t>({ 'Q' }),
	TradingOnNasdaq                 = char_to_uint<std::uint8_t>({ 'T' }),
};

enum class TradingActionReason : std::uint32_t {
	HaltNewsPending                           = char_to_uint<std::uint32_t>({ 'T' , '1' , ' ' , ' ' }),
	HaltNewsDisseminated                      = char_to_uint<std::uint32_t>({ 'T' , '2' , ' ' , ' ' }),
	SingleSecurityTradingPauseInEffect        = char_to_uint<std::uint32_t>({ 'T' , '5' , ' ' , ' ' }),
	RegulatoryHaltExtraordinaryMarketActivity = char_to_uint<std::uint32_t>({ 'T' , '6' , ' ' , ' ' }),
	HaltETF                                   = char_to_uint<std::uint32_t>({ 'T' , '8' , ' ' , ' ' }),
	TradingHaltedForInfoToListingMarket       = char_to_uint<std::uint32_t>({ 'T' , '1' , '2' , ' ' }),
	HaltNonCompliance                         = char_to_uint<std::uint32_t>({ 'H' , '4' , ' ' , ' ' }),
	HaltFilingsNotCurrent                     = char_to_uint<std::uint32_t>({ 'H' , '9' , ' ' , ' ' }),
	HaltSECTradingSuspension                  = char_to_uint<std::uint32_t>({ 'H' , '1' , '0' , ' ' }),
	HaltRegulatoryConcern                     = char_to_uint<std::uint32_t>({ 'H' , '1' , '1' , ' ' }),
	OperationsHalt                            = char_to_uint<std::uint32_t>({ 'O' , '1' , ' ' , ' ' }),
	VolatilityTradingPause                    = char_to_uint<std::uint32_t>({ 'L' , 'U' , 'D' , 'P' }),
	VolatilityTradingPauseStraddleCondition   = char_to_uint<std::uint32_t>({ 'L' , 'U' , 'D' , 'S' }),
	MarketWideCircuitBreakerHaltLevel1        = char_to_uint<std::uint32_t>({ 'M' , 'W' , 'C' , '1' }),
	MarketWideCircuitBreakerHaltLevel2        = char_to_uint<std::uint32_t>({ 'M' , 'W' , 'C' , '2' }),
	MarketWideCircuitBreakerHaltLevel3        = char_to_uint<std::uint32_t>({ 'M' , 'W' , 'C' , '3' }),
	MarketWideCircuitBreakerHaltCarryOver     = char_to_uint<std::uint32_t>({ 'M' , 'W' , 'C' , '0' }),
	IPOIssueNotYetTrading                     = char_to_uint<std::uint32_t>({ 'I' , 'P' , 'O' , '1' }),
	CorporateAction                           = char_to_uint<std::uint32_t>({ 'M' , '1' , ' ' , ' ' }),
	QuotationNotAvailable                     = char_to_uint<std::uint32_t>({ 'M' , '2' , ' ' , ' ' }),
	NewsAndResumptionTimes                    = char_to_uint<std::uint32_t>({ 'T' , '3' , ' ' , ' ' }),
	SingleSecurityTradingPauseOrQuotationOnly = char_to_uint<std::uint32_t>({ 'T' , '7' , ' ' , ' ' }),
	QualificationsIssuesReviewedOrResolved    = char_to_uint<std::uint32_t>({ 'R' , '4' , ' ' , ' ' }),
	FilingRequirementsSatisfiedOrResolved     = char_to_uint<std::uint32_t>({ 'R' , '9' , ' ' , ' ' }),
	IssuerNewsNotForthcoming                  = char_to_uint<std::uint32_t>({ 'C' , '3' , ' ' , ' ' }),
	QualificationsHaltEndedAndMaintenanceDone = char_to_uint<std::uint32_t>({ 'C' , '4' , ' ' , ' ' }),
	QualificationsHaltConcludedAndFilingsMet  = char_to_uint<std::uint32_t>({ 'C' , '9' , ' ' , ' ' }),
	TradeHaltConcludedByOtherRegulatoryAuth   = char_to_uint<std::uint32_t>({ 'C' , '1' , '1' , ' ' }),
	MarketWideCircuitBreakerResumption        = char_to_uint<std::uint32_t>({ 'M' , 'W' , 'C' , 'Q' }),
	NewIssueAvailable                         = char_to_uint<std::uint32_t>({ 'R' , '1' , ' ' , ' ' }),
	IssueAvailable                            = char_to_uint<std::uint32_t>({ 'R' , '2' , ' ' , ' ' }),
	IPOSecurityReleasedForQuotation           = char_to_uint<std::uint32_t>({ 'I' , 'P' , 'O' , 'Q' }),
	IPOSecurityPositioningWindowExtension     = char_to_uint<std::uint32_t>({ 'I' , 'P' , 'O' , 'E' }),
	ReasonNotAvailable                        = char_to_uint<std::uint32_t>({ ' ' , ' ' , ' ' , ' ' }),
};

enum class RegSHOAction : std::uint8_t {
	NoPriceTest                                  = char_to_uint<std::uint8_t>({ '0' }),
	ShortSalePriceTestRestriction                = char_to_uint<std::uint8_t>({ '1' }),
	ShortSalePriceTestRestrictionRemainsInEffect = char_to_uint<std::uint8_t>({ '2' }),
};

enum class PrimaryMarketMakerFlag : std::uint8_t {
	Yes = char_to_uint<std::uint8_t>({ 'Y' }),
	No  = char_to_uint<std::uint8_t>({ 'N' }),
};

enum class MarketMakerMode : std::uint8_t {
	Normal       = char_to_uint<std::uint8_t>({ 'N' }),
	Passive      = char_to_uint<std::uint8_t>({ 'P' }),
	Syndicate    = char_to_uint<std::uint8_t>({ 'S' }),
	PreSyndicate = char_to_uint<std::uint8_t>({ 'R' }),
	Penalty      = char_to_uint<std::uint8_t>({ 'L' }),
};

enum class MarketParticipantState : std::uint8_t {
	Active             = char_to_uint<std::uint8_t>({ 'A' }),
	ExcusedOrWithdrawn = char_to_uint<std::uint8_t>({ 'E' }),
	Withdrawn          = char_to_uint<std::uint8_t>({ 'W' }),
	Suspended          = char_to_uint<std::uint8_t>({ 'S' }),
	Deleted            = char_to_uint<std::uint8_t>({ 'D' }),
};

enum class MWCBBreachLevel : std::uint8_t {
	Level1 = char_to_uint<std::uint8_t>({ '1' }),
	Level2 = char_to_uint<std::uint8_t>({ '2' }),
	Level3 = char_to_uint<std::uint8_t>({ '3' }),
};

enum class IPOQuotationReleaseQualifier : std::uint8_t {
	AnticipatedReleaseTime = char_to_uint<std::uint8_t>({ 'A' }),
	CanceledOrPostponed    = char_to_uint<std::uint8_t>({ 'C' }),
};

enum class MarketCode : std::uint8_t {
	Nasdaq = char_to_uint<std::uint8_t>({ 'Q' }),
	BX     = char_to_uint<std::uint8_t>({ 'B' }),
	PSX    = char_to_uint<std::uint8_t>({ 'X' }),
};

enum class OperationalHaltAction : std::uint8_t {
	Halted     = char_to_uint<std::uint8_t>({ 'H' }),
	HaltLifted = char_to_uint<std::uint8_t>({ 'T' }),
};

enum class PrintableFlag : std::uint8_t {
	NonPrintable = char_to_uint<std::uint8_t>({ 'N' }),
	Printable    = char_to_uint<std::uint8_t>({ 'Y' }),
};

enum class CrossType : std::uint8_t {
	NasdaqOpeningCross                     = char_to_uint<std::uint8_t>({ 'O' }),
	NasdaqClosingCross                     = char_to_uint<std::uint8_t>({ 'C' }),
	CrossForIPOAndHaltedOrPausedSecurities = char_to_uint<std::uint8_t>({ 'H' }),
	ExtendedTradingClose                   = char_to_uint<std::uint8_t>({ 'A' }),
};

enum class ImbalanceDirection : std::uint8_t {
	Buy          = char_to_uint<std::uint8_t>({ 'B' }),
	Sell         = char_to_uint<std::uint8_t>({ 'S' }),
	None         = char_to_uint<std::uint8_t>({ 'N' }),
	NotAvailable = char_to_uint<std::uint8_t>({ 'O' }),
	Paused       = char_to_uint<std::uint8_t>({ 'P' }),
};

enum class PriceVariationPercentage : std::uint8_t {
	LessThanOnePercent       = char_to_uint<std::uint8_t>({ 'L' }),
	OneToSubTwoPercent       = char_to_uint<std::uint8_t>({ '1' }),
	TwoToSubThreePercent     = char_to_uint<std::uint8_t>({ '2' }),
	ThreeToSubFourPercent    = char_to_uint<std::uint8_t>({ '3' }),
	FourToSubFivePercent     = char_to_uint<std::uint8_t>({ '4' }),
	FiveToSubSixPercent      = char_to_uint<std::uint8_t>({ '5' }),
	SixToSubSevenPercent     = char_to_uint<std::uint8_t>({ '6' }),
	SevenToSubEightPercent   = char_to_uint<std::uint8_t>({ '7' }),
	EightToSubNinePercent    = char_to_uint<std::uint8_t>({ '8' }),
	NineToSubTenPercent      = char_to_uint<std::uint8_t>({ '9' }),
	TenToSubTwentyPercent    = char_to_uint<std::uint8_t>({ 'A' }),
	TwentyToSubThirtyPercent = char_to_uint<std::uint8_t>({ 'B' }),
	ThirtyPercentOrGreater   = char_to_uint<std::uint8_t>({ 'C' }),
	NotAvailable             = char_to_uint<std::uint8_t>({ ' ' }),
};

enum class InterestFlagRPII : std::uint8_t {
	RPIOrdersAvailableOnBuySide   = char_to_uint<std::uint8_t>({ 'B' }),
	RPIOrdersAvailableOnSellSide  = char_to_uint<std::uint8_t>({ 'S' }),
	RPIOrdersAvailableOnBothSides = char_to_uint<std::uint8_t>({ 'A' }),
	NoRPIOrdersAvailable          = char_to_uint<std::uint8_t>({ 'N' }),
};

enum class EligibleForTradingReleaseFlag : std::uint8_t {
	NotEligible = char_to_uint<std::uint8_t>({ 'N' }),
	Eligible    = char_to_uint<std::uint8_t>({ 'Y' }),
};

} // namespace itch::spec

#endif // TV_ITCH50_CPP_ALPHA_FIELDS_HPP
