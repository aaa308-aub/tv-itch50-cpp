#ifndef TV_ITCH50_CPP_ALPHA_FIELDS_HPP
#define TV_ITCH50_CPP_ALPHA_FIELDS_HPP


#include <cstdint>


namespace tv_itch::spec {
inline constexpr std::uint16_t enum_fill_u16(const char a, const char b) noexcept {
	return (static_cast<std::uint16_t>(static_cast<unsigned char>(a)) << 8) |
			static_cast<std::uint16_t>(static_cast<unsigned char>(b));
}


inline constexpr std::uint32_t enum_fill_u32(const char a, const char b, const char c, const char d) noexcept {
	return (static_cast<std::uint32_t>(static_cast<unsigned char>(a)) << 24) |
		   (static_cast<std::uint32_t>(static_cast<unsigned char>(b)) << 16) |
		   (static_cast<std::uint32_t>(static_cast<unsigned char>(c)) << 8) |
			   static_cast<std::uint32_t>(static_cast<unsigned char>(d));
}


enum class MessageType : char {
	SystemEvent               = 'S',
	StockDirectory            = 'R',
	StockTradingAction        = 'H',
	RegSHORestriction         = 'Y',
	MarketParticipantPosition = 'L',
	MWCBDeclineLevel          = 'V',
	MWCBStatus                = 'W',
	IPOQuotingPeriodUpdate    = 'K',
	LULDAuctionCollar         = 'J',
	OperationalHalt           = 'h',   // Not a typo, it is lowercase
	AddOrderWithoutMPID       = 'A',
	AddOrderWithMPID          = 'F',
	ExecuteOrder              = 'E',
	ExecuteOrderWithPrice     = 'C',
	CancelOrder               = 'X',
	DeleteOrder               = 'D',
	ReplaceOrder              = 'U',
	NonCrossTrade             = 'P',
	CrossTrade                = 'Q',
	BrokenTrade               = 'B',
	NOII                      = 'I',
	RPII                      = 'N',
	DLCRPriceDiscovery        = 'O',
};


enum class Side : char {
	Buy  = 'B',
	Sell = 'S',
};


enum class SystemEventCode : char {
	StartOfMessages    = 'O',
	StartOfSystemHours = 'S',
	StartOfMarketHours = 'Q',
	EndOfMarketHours   = 'M',
	EndOfSystemHours   = 'E',
	EndOfMessages      = 'C',
};


enum class MarketCategory : char {
	NasdaqGlobalSelectMarket = 'Q',
	NasdaqGlobalMarket       = 'G',
	NasdaqCapitalMarket      = 'S',
	NYSE                     = 'N',
	NYSEAmerican             = 'A',
	NYSEArca                 = 'P',
	BATSZExchange            = 'Z',
	InvestorsExchangeLLC     = 'V',
	NotAvailable             = ' ',
};


enum class FinancialStatus : char {
	Deficient                             = 'D',
	Delinquent                            = 'E',
	Bankrupt                              = 'Q',
	Suspended                             = 'S',
	DeficientAndBankrupt                  = 'G',
	DeficientAndDelinquent                = 'H',
	DelinquentAndBankrupt                 = 'J',
	DeficientDelinquentAndBankrupt        = 'K',
	CreationsOrRedemptionsSuspendedForETP = 'C',
	Normal                                = 'N',
	NotAvailable                          = ' ',
};


enum class RoundLotsOnlyFlag: char {
	Yes = 'Y',
	No  = 'N',
};


enum class IssueClassification : char {
	AmericanDepositaryShare    = 'A',
	Bond                       = 'B',
	CommonStock                = 'C',
	DepositoryReceipt          = 'F',
	Rule144A                   = 'I',
	LimitedPartnership         = 'L',
	Notes                      = 'N',
	OrdinaryShare              = 'O',
	PreferredStock             = 'P',
	OtherSecurities            = 'Q',
	Right                      = 'R',
	SharesOfBeneficialInterest = 'S',
	ConvertibleDebenture       = 'T',
	Unit                       = 'U',
	UnitsOrBenifInt            = 'V',
	Warrant                    = 'W',
};


enum class IssueSubType : std::uint16_t {
    PreferredTrustSecurities                     = enum_fill_u16('A', ' '),
    AlphaIndexETNs                               = enum_fill_u16('A', 'I'),
    IndexBasedDerivative                         = enum_fill_u16('B', ' '),
    CommonShares                                 = enum_fill_u16('C', ' '),
    CommodityBasedTrustShares                    = enum_fill_u16('C', 'B'),
    CommodityFuturesTrustShares                  = enum_fill_u16('C', 'F'),
    CommodityLinkedSecurities                    = enum_fill_u16('C', 'L'),
    CommodityIndexTrustShares                    = enum_fill_u16('C', 'M'),
    CollateralizedMortgageObligation             = enum_fill_u16('C', 'O'),
    CurrencyTrustShares                          = enum_fill_u16('C', 'T'),
    CommodityCurrencyLinkedSecurities            = enum_fill_u16('C', 'U'),
    CurrencyWarrants                             = enum_fill_u16('C', 'W'),
    GlobalDepositaryShares                       = enum_fill_u16('D', ' '),
    ETFPortfolioDepositaryReceipt                = enum_fill_u16('E', ' '),
    EquityGoldShares                             = enum_fill_u16('E', 'G'),
    ETNEquityIndexLinkedSecurities               = enum_fill_u16('E', 'I'),
    NextSharesExchangeTradedManagedFund          = enum_fill_u16('E', 'M'),
    ExchangeTradedNotes                          = enum_fill_u16('E', 'N'),
    EquityUnits                                  = enum_fill_u16('E', 'U'),
    HOLDRS                                       = enum_fill_u16('F', ' '),
    ETNFixedIncomeLinkedSecurities               = enum_fill_u16('F', 'I'),
    ETNFuturesLinkedSecurities                   = enum_fill_u16('F', 'L'),
    GlobalShares                                 = enum_fill_u16('G', ' '),
    ETFIndexFundShares                           = enum_fill_u16('I', ' '),
    InterestRate                                 = enum_fill_u16('I', 'R'),
    IndexWarrant                                 = enum_fill_u16('I', 'W'),
    IndexLinkedExchangeableNotes                 = enum_fill_u16('I', 'X'),
    CorporateBackedTrustSecurity                 = enum_fill_u16('J', ' '),
    ContingentLitigationRight                    = enum_fill_u16('L', ' '),
	LLCSecurity                                  = enum_fill_u16('L', 'L'),
	EquityBasedDerivative                        = enum_fill_u16('M', ' '),
	ManagedFundShares                            = enum_fill_u16('M', 'F'),
	ETNMultiFactorIndexLinkedSecurities          = enum_fill_u16('M', 'L'),
	ManagedTrustSecurities                       = enum_fill_u16('M', 'T'),
	NYRegistryShares                             = enum_fill_u16('N', ' '),
	OpenEndedMutualFund                          = enum_fill_u16('O', ' '),
	PrivatelyHeldSecurity                        = enum_fill_u16('P', ' '),
    PoisonPill                                   = enum_fill_u16('P', 'P'),
	PartnershipUnits                             = enum_fill_u16('P', 'U'),
    ClosedEndFunds                               = enum_fill_u16('Q', ' '),
	RegS                                         = enum_fill_u16('R', ' '),
	CommodityRedeemableCommodityLinkedSecurities = enum_fill_u16('R', 'C'),
	ETNRedeemableFuturesLinkedSecurities         = enum_fill_u16('R', 'F'),
    REIT                                         = enum_fill_u16('R', 'T'),
	CommodityRedeemableCurrencyLinkedSecurities  = enum_fill_u16('R', 'U'),
	SEED                                         = enum_fill_u16('S', ' '),
    SpotRateClosing                              = enum_fill_u16('S', 'C'),
    SpotRateIntraday                             = enum_fill_u16('S', 'I'),
	TrackingStock                                = enum_fill_u16('T', ' '),
	TrustCertificates                            = enum_fill_u16('T', 'C'),
	TrustUnits                                   = enum_fill_u16('T', 'U'),
	Portal                                       = enum_fill_u16('U', ' '),
	ContingentValueRight                         = enum_fill_u16('V', ' '),
	TrustIssuedReceipts                          = enum_fill_u16('W', ' '),
    WorldCurrencyOption                          = enum_fill_u16('W', 'C'),
    Trust                                        = enum_fill_u16('X', ' '),
    Other                                        = enum_fill_u16('Y', ' '),
    NotApplicable                                = enum_fill_u16('Z', ' '),
};


enum class Authenticity : char {
	LiveOrProduction = 'P',
	Test             = 'T',
};


enum class ShortSaleThreshold : char {
	RestrictedUnderSECRule203b3 = 'Y',
	NotRestricted               = 'N',
	NotAvailable                = ' ',
};


enum class IPOFlag : char {
	Yes          = 'Y',
	No           = 'N',
	NotAvailable = ' ',
};


enum class LULDRefPriceTier : char {
	Tier1NMSStocksAndSelectETPs = '1',
	Tier2NMSStocks              = '2',
	NotAvailable                = ' ',
};


enum class ETPFlag : char {
	Yes          = 'Y',
	No           = 'N',
	NotAvailable = ' ',
};


enum class InverseETPFlag : char {
	Yes = 'Y',
	No  = 'N',
};


enum class StockTradingState : char {
	HaltedAcrossAllUSEquitiesOrSROs = 'H',
	PausedAcrossAllUSEquitiesOrSROs = 'P',
	QuotationOnlyPeriod             = 'Q',
	TradingOnNasdaq                 = 'T',
};


enum class TradingActionReason : std::uint32_t {
    HaltNewsPending                           = enum_fill_u32('T', '1', ' ', ' '),
    HaltNewsDisseminated                      = enum_fill_u32('T', '2', ' ', ' '),
    SingleSecurityTradingPauseInEffect        = enum_fill_u32('T', '5', ' ', ' '),
    RegulatoryHaltExtraordinaryMarketActivity = enum_fill_u32('T', '6', ' ', ' '),
    HaltETF                                   = enum_fill_u32('T', '8', ' ', ' '),
    TradingHaltedForInfoToListingMarket       = enum_fill_u32('T', '1', '2', ' '),
    HaltNonCompliance                         = enum_fill_u32('H', '4', ' ', ' '),
    HaltFilingsNotCurrent                     = enum_fill_u32('H', '9', ' ', ' '),
    HaltSECTradingSuspension                  = enum_fill_u32('H', '1', '0', ' '),
    HaltRegulatoryConcern                     = enum_fill_u32('H', '1', '1', ' '),
    OperationsHalt                            = enum_fill_u32('O', '1', ' ', ' '),
    VolatilityTradingPause                    = enum_fill_u32('L', 'U', 'D', 'P'),
    VolatilityTradingPauseStraddleCondition   = enum_fill_u32('L', 'U', 'D', 'S'),
    MarketWideCircuitBreakerHaltLevel1        = enum_fill_u32('M', 'W', 'C', '1'),
    MarketWideCircuitBreakerHaltLevel2        = enum_fill_u32('M', 'W', 'C', '2'),
    MarketWideCircuitBreakerHaltLevel3        = enum_fill_u32('M', 'W', 'C', '3'),
    MarketWideCircuitBreakerHaltCarryOver     = enum_fill_u32('M', 'W', 'C', '0'),
    IPOIssueNotYetTrading                     = enum_fill_u32('I', 'P', 'O', '1'),
    CorporateAction                           = enum_fill_u32('M', '1', ' ', ' '),
    QuotationNotAvailable                     = enum_fill_u32('M', '2', ' ', ' '),
    NewsAndResumptionTimes                    = enum_fill_u32('T', '3', ' ', ' '),
    SingleSecurityTradingPauseOrQuotationOnly = enum_fill_u32('T', '7', ' ', ' '),
    QualificationsIssuesReviewedOrResolved    = enum_fill_u32('R', '4', ' ', ' '),
    FilingRequirementsSatisfiedOrResolved     = enum_fill_u32('R', '9', ' ', ' '),
    IssuerNewsNotForthcoming                  = enum_fill_u32('C', '3', ' ', ' '),
    QualificationsHaltEndedAndMaintenanceDone = enum_fill_u32('C', '4', ' ', ' '),
    QualificationsHaltConcludedAndFilingsMet  = enum_fill_u32('C', '9', ' ', ' '),
    TradeHaltConcludedByOtherRegulatoryAuth   = enum_fill_u32('C', '1', '1', ' '),
    MarketWideCircuitBreakerResumption        = enum_fill_u32('M', 'W', 'C', 'Q'),
    NewIssueAvailable                         = enum_fill_u32('R', '1', ' ', ' '),
    IssueAvailable                            = enum_fill_u32('R', '2', ' ', ' '),
    IPOSecurityReleasedForQuotation           = enum_fill_u32('I', 'P', 'O', 'Q'),
    IPOSecurityPositioningWindowExtension     = enum_fill_u32('I', 'P', 'O', 'E'),
    ReasonNotAvailable                        = enum_fill_u32(' ', ' ', ' ', ' '),
};


enum class RegSHOAction : char {
	NoPriceTest                                  = '0',
	ShortSalePriceTestRestriction                = '1',
	ShortSalePriceTestRestrictionRemainsInEffect = '2',
};


enum class PrimaryMarketMakerFlag : char {
	Yes = 'Y',
	No  = 'N',
};


enum class MarketMakerMode : char {
	Normal       = 'N',
	Passive      = 'P',
	Syndicate    = 'S',
	PreSyndicate = 'R',
	Penalty      = 'L',
};


enum class MarketParticipantState : char{
	Active             = 'A',
	ExcusedOrWithdrawn = 'E',
	Withdrawn          = 'W',
	Suspended          = 'S',
	Deleted            = 'D',
};


enum class MWCBBreachLevel : char {
	Level1 = '1',
	Level2 = '2',
	Level3 = '3',
};


enum class IPOQuotationReleaseQualifier : char {
	AnticipatedReleaseTime = 'A',
	CanceledOrPostponed    = 'C',
};


enum class MarketCode : char {
	Nasdaq = 'Q',
	BX =     'B',
	PSX =    'X',
};


enum class OperationalHaltAction : char {
	Halted     = 'H',
	HaltLifted = 'T',
};


enum class PrintableFlag : char {
	NonPrintable = 'N',
	Printable    = 'Y',
};


enum class CrossType : char {
	NasdaqOpeningCross                     = 'O',
	NasdaqClosingCross                     = 'C',
	CrossForIPOAndHaltedOrPausedSecurities = 'H',
};


enum class ImbalanceDirection : char {
	Buy          = 'B',
	Sell         = 'S',
	None         = 'N',
	NotAvailable = 'O',
	Paused       = 'P',
};


enum class CrossTypeNOII : char{
	NasdaqOpeningCross                     = 'O',
	NasdaqClosingCross                     = 'C',
	CrossForIPOAndHaltedOrPausedSecurities = 'H',
	ExtendedTradingClose                   = 'A',
};


enum class PriceVariationPercentage : char {
	LessThanOnePercent       = 'L',
	OneToSubTwoPercent       = '1',
	TwoToSubThreePercent     = '2',
	ThreeToSubFourPercent    = '3',
	FourToSubFivePercent     = '4',
	FiveToSubSixPercent      = '5',
	SixToSubSevenPercent     = '6',
	SevenToSubEightPercent   = '7',
	EightToSubNinePercent    = '8',
	NineToSubTenPercent      = '9',
	TenToSubTwentyPercent    = 'A',
	TwentyToSubThirtyPercent = 'B',
	ThirtyPercentOrGreater   = 'C',
	NotAvailable             = ' ',
};


enum class InterestFlagRPII : char {
	RPIOrdersAvailableOnBuySide   = 'B',
	RPIOrdersAvailableOnSellSide  = 'S',
	RPIOrdersAvailableOnBothSides = 'A',
	NoRPIOrdersAvailable          = 'N',
};


enum class EligibleForTradingReleaseFlag : char {
	NotEligible = 'N',
	Eligible    = 'Y',
};
}


#endif