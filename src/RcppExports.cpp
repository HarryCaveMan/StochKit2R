// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// ssaSingleStochKit2RInterface
RcppExport SEXP ssaSingleStochKit2RInterface(Rcpp::List StochKit2Rmodel, std::string outputFileNameString, double startTime, double endTime, unsigned int seed);
RcppExport SEXP StochKit2R_ssaSingleStochKit2RInterface(SEXP StochKit2RmodelSEXP, SEXP outputFileNameStringSEXP, SEXP startTimeSEXP, SEXP endTimeSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type StochKit2Rmodel(StochKit2RmodelSEXP);
    Rcpp::traits::input_parameter< std::string >::type outputFileNameString(outputFileNameStringSEXP);
    Rcpp::traits::input_parameter< double >::type startTime(startTimeSEXP);
    Rcpp::traits::input_parameter< double >::type endTime(endTimeSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(ssaSingleStochKit2RInterface(StochKit2Rmodel, outputFileNameString, startTime, endTime, seed));
    return rcpp_result_gen;
END_RCPP
}
// ssaStochKit2RInterface
RcppExport SEXP ssaStochKit2RInterface(Rcpp::List StochKit2Rmodel, std::string outputDirNameString, double time, int realizations, int intervals, bool keepStats, bool keepTrajectories, bool keepHistograms, int bins, unsigned int seed, int p);
RcppExport SEXP StochKit2R_ssaStochKit2RInterface(SEXP StochKit2RmodelSEXP, SEXP outputDirNameStringSEXP, SEXP timeSEXP, SEXP realizationsSEXP, SEXP intervalsSEXP, SEXP keepStatsSEXP, SEXP keepTrajectoriesSEXP, SEXP keepHistogramsSEXP, SEXP binsSEXP, SEXP seedSEXP, SEXP pSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type StochKit2Rmodel(StochKit2RmodelSEXP);
    Rcpp::traits::input_parameter< std::string >::type outputDirNameString(outputDirNameStringSEXP);
    Rcpp::traits::input_parameter< double >::type time(timeSEXP);
    Rcpp::traits::input_parameter< int >::type realizations(realizationsSEXP);
    Rcpp::traits::input_parameter< int >::type intervals(intervalsSEXP);
    Rcpp::traits::input_parameter< bool >::type keepStats(keepStatsSEXP);
    Rcpp::traits::input_parameter< bool >::type keepTrajectories(keepTrajectoriesSEXP);
    Rcpp::traits::input_parameter< bool >::type keepHistograms(keepHistogramsSEXP);
    Rcpp::traits::input_parameter< int >::type bins(binsSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type p(pSEXP);
    rcpp_result_gen = Rcpp::wrap(ssaStochKit2RInterface(StochKit2Rmodel, outputDirNameString, time, realizations, intervals, keepStats, keepTrajectories, keepHistograms, bins, seed, p));
    return rcpp_result_gen;
END_RCPP
}
// tauLeapingStochKit2RInterface
RcppExport SEXP tauLeapingStochKit2RInterface(Rcpp::List StochKit2Rmodel, std::string outputDirNameString, double time, int realizations, int intervals, bool keepStats, bool keepTrajectories, bool keepHistograms, int bins, unsigned int seed, int p, double epsilon, int threshold);
RcppExport SEXP StochKit2R_tauLeapingStochKit2RInterface(SEXP StochKit2RmodelSEXP, SEXP outputDirNameStringSEXP, SEXP timeSEXP, SEXP realizationsSEXP, SEXP intervalsSEXP, SEXP keepStatsSEXP, SEXP keepTrajectoriesSEXP, SEXP keepHistogramsSEXP, SEXP binsSEXP, SEXP seedSEXP, SEXP pSEXP, SEXP epsilonSEXP, SEXP thresholdSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type StochKit2Rmodel(StochKit2RmodelSEXP);
    Rcpp::traits::input_parameter< std::string >::type outputDirNameString(outputDirNameStringSEXP);
    Rcpp::traits::input_parameter< double >::type time(timeSEXP);
    Rcpp::traits::input_parameter< int >::type realizations(realizationsSEXP);
    Rcpp::traits::input_parameter< int >::type intervals(intervalsSEXP);
    Rcpp::traits::input_parameter< bool >::type keepStats(keepStatsSEXP);
    Rcpp::traits::input_parameter< bool >::type keepTrajectories(keepTrajectoriesSEXP);
    Rcpp::traits::input_parameter< bool >::type keepHistograms(keepHistogramsSEXP);
    Rcpp::traits::input_parameter< int >::type bins(binsSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    Rcpp::traits::input_parameter< int >::type p(pSEXP);
    Rcpp::traits::input_parameter< double >::type epsilon(epsilonSEXP);
    Rcpp::traits::input_parameter< int >::type threshold(thresholdSEXP);
    rcpp_result_gen = Rcpp::wrap(tauLeapingStochKit2RInterface(StochKit2Rmodel, outputDirNameString, time, realizations, intervals, keepStats, keepTrajectories, keepHistograms, bins, seed, p, epsilon, threshold));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"StochKit2R_ssaSingleStochKit2RInterface", (DL_FUNC) &StochKit2R_ssaSingleStochKit2RInterface, 5},
    {"StochKit2R_ssaStochKit2RInterface", (DL_FUNC) &StochKit2R_ssaStochKit2RInterface, 11},
    {"StochKit2R_tauLeapingStochKit2RInterface", (DL_FUNC) &StochKit2R_tauLeapingStochKit2RInterface, 13},
    {NULL, NULL, 0}
};

RcppExport void R_init_StochKit2R(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
