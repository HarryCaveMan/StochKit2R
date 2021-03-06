// -*- C++ -*-

/*! 
  \file src/HistogramOutputPacked.h
  \contains a vector of histogram output objects
*/

#ifndef _HISTOGRAM_OUTPUT_PACKED_H_
#define _HISTOGRAM_OUTPUT_PACKED_H_

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdio.h>
#include "../DenseVectorSubset.h"
#include "HistogramOutput.h"
#include "IntervalOutput.h"

namespace STOCHKIT
{
 template<typename _populationVectorType>
 class HistogramOutputPacked
 {	
  
 protected:

  //! The number of frames.
  std::size_t _numberOfIntervals;
  //! number of bins
  std:: size_t _numberOfBins;
  //! total number of realizations
  std::size_t _numberOfRealizations;  
  //! The vector of indices to record in histogram
  DenseVectorSubset<_populationVectorType> _speciesSubset;
  //! The number of species.
  std::size_t _numberOfSpecies;
  //! vector of output times
  std::vector<double> _outputTimes;
 
  //! The histograms.
  std::vector<HistogramOutput<typename _populationVectorType::value_type> > _histograms;


 public:

  //! Construct from the number of intervals, the number of species, the number of bins, and the total number of realizations.
  HistogramOutputPacked(const std::size_t numberOfIntervals,
			const std::size_t numberOfBins,
			const std::size_t numberOfRealizations,
			std::vector<std::size_t> speciesIndices) :
    _numberOfIntervals(numberOfIntervals+1),
    _numberOfBins(numberOfBins),
    _numberOfRealizations(numberOfRealizations)
  {
    _speciesSubset.setSubsetIndices(speciesIndices);
    _numberOfSpecies = speciesIndices.size();

    for(std::size_t i=0; i<_numberOfIntervals; i++){
      for(std::size_t j=0; j<_numberOfSpecies;j++){
	HistogramOutput<typename _populationVectorType::value_type> tempHist(_numberOfBins,i,j);
	_histograms.push_back(tempHist);
      }
    }
  }


  //! Construct from the number of intervals, the number of species, and the total number of realizations.
  HistogramOutputPacked(const std::size_t numberOfIntervals,
			const std::size_t numberOfRealizations,
			std::vector<std::size_t> speciesIndices) :
    _numberOfIntervals(numberOfIntervals+1),
    _numberOfRealizations(numberOfRealizations)
  {
    _speciesSubset.setSubsetIndices(speciesIndices);
    _numberOfSpecies = speciesIndices.size();
    _numberOfBins = 32;

    for(std::size_t i=0; i<_numberOfIntervals; i++){
      for(std::size_t j=0; j<_numberOfSpecies;j++){
	HistogramOutput<typename _populationVectorType::value_type> tempHist(_numberOfBins,i,j);
	_histograms.push_back(tempHist);
      }
    }
  }



  //! Default constructor. Invalid Histogram Packed
 HistogramOutputPacked() :
   _numberOfIntervals(0),
   _numberOfBins(0),
   _numberOfRealizations(0),
   _numberOfSpecies(0)
  { 
  }
    
  //! Destructor.
  virtual ~HistogramOutputPacked()
  {}

  //@}
  //--------------------------------------------------------------------------
  //! \name Accessors.
  //@{
 public:

  //! Return the number of intervals.
  std::size_t numberOfIntervals() const {
    return _numberOfIntervals;
  }

  //! Return the number of species.
  std::size_t numberOfSpecies() const {
    return _numberOfSpecies;
  }

  //! Return the number of realizations.
  std::size_t numberOfRealizations() const {
    return _numberOfRealizations;
  }

  //! Return the number of histograms
  std::size_t numberOfHistograms() const {
    return _histograms.size();
  }

  //! Set the number of realizations
  void setNumberOfRealizations(std::size_t nRealizations){
    _numberOfRealizations = nRealizations;
  }

  //! Set the number of species
  void setNumberOfSpecies(std::size_t nSpecies){
    _numberOfSpecies = nSpecies;
  }

  //! Set the number of bins for each histogram
  void setNumberOfBins(std::size_t nBins){
    _numberOfBins = nBins;
  }

  //! Set the indices of species to record
  void setSpeciesSubset(std::vector<std::size_t> speciesIndices){
    _speciesSubset.setSubsetIndices(speciesIndices);
  }

  //! initialize: make sure everything is set up correctly
  virtual bool initialize(std::size_t realizations, double startTime, double endTime, _populationVectorType& samplePopulationVector) {
    if(_numberOfRealizations != realizations){
      if (_numberOfRealizations>0) {// previously set
	Rcpp::Rcout<<"StochKit MESSAGE (HistogramOutputPacked::initialize): the number of realizations differ from the previously declared value\n";
      }
    }
    if(_numberOfRealizations==0) // has not been set yet
      _numberOfRealizations = realizations;
    if(_numberOfSpecies ==0) // has not been initialized -> keep all true
      _numberOfSpecies = _speciesSubset.getSubset(samplePopulationVector).size();
    if(_numberOfBins <1){
      Rcpp::Rcout<<"StochKit ERROR (HistogramOutputPacked::initialize): number of bins must be greater than 0\n";
      Rcpp::stop("Fatal error encountered, terminating StochKit2R");
    }
    if(_outputTimes.size()==0){
      std::vector<double> defaultOutputTimes;
      defaultOutputTimes.push_back(endTime);
      setOutputTimes(defaultOutputTimes);
    }

    for(std::size_t i=0; i<_outputTimes.size(); i++){
      for(std::size_t j=0; j<_numberOfSpecies;j++){
	HistogramOutput<typename _populationVectorType::value_type> tempHist(_numberOfBins,i,j);
	_histograms.push_back(tempHist);
      }
    }
    if(_histograms.size()<1){
      Rcpp::Rcout<<"StochKit ERROR (HistogramOutputPacked::initialize): histograms have not been initialized\n";
      Rcpp::stop("Fatal error encountered, terminating StochKit2R");
    }
    return true;
  }

  //! One of interval and species should start at 1 to avoid having multiple 0s
  // assume interval starts at 0 -> avoid having multiple 0 indices
  void record(std::size_t realization, std::size_t interval,_populationVectorType population) {
#ifndef DEBUG_StochKit  
    if (interval>=_numberOfIntervals || interval<0){
      Rcpp::Rcout<<"StochKit ERROR (HistogramOutputPacked::record): interval index out of bound\n";
      Rcpp::stop("Fatal error encountered, terminating StochKit2R");
    }
#endif	 
    for(std::size_t i=0; i<_numberOfSpecies;i++){
      typename _populationVectorType::value_type tempX = _speciesSubset.getSubset(population)[i]; 
      _histograms.at(interval*_numberOfSpecies+i).accumulate(tempX);
    }
  }
  //! Return the specified histogram.
 
  const HistogramOutput<typename _populationVectorType::value_type>&  operator()(const std::size_t interval, const std::size_t speciesIndex) const {
#ifndef DEBUG_StochKit  
    if (interval>_numberOfIntervals || interval<0){
      Rcpp::Rcout<<"StochKit ERROR (HistogramOutputPacked::operator()): interval index out of bound\n";
      Rcpp::stop("Fatal error encountered, terminating StochKit2R");
    }
    if (speciesIndex>=_numberOfSpecies || speciesIndex<0){
      Rcpp::Rcout<<"StochKit ERROR (HistogramOutputPacked::operator()): speciesIndex out of bound\n";
      Rcpp::stop("Fatal error encountered, terminating StochKit2R");
    }
#endif
    return _histograms.at(interval * _numberOfSpecies + speciesIndex);
  }


  void setOutputTimes(std::vector<double> outputTimes){
#ifndef DEBUG_StochKit  
    //check to ensure no duplicates and increasing order
    if (outputTimes[0]<0){
      Rcpp::Rcout<<"StochKit ERROR (HistogramOutputPacked::setOutputTimes): negative initial time\n";
      Rcpp::stop("Fatal error encountered, terminating StochKit2R");
    }
    for(std::size_t i=1; i<outputTimes.size();i++){
      if (outputTimes[i]<=outputTimes[i-1]){
	Rcpp::Rcout<<"StochKit ERROR (HistogramOutputPacked::setOutputTimes): outputTimes not monotonically increasing\n";
	Rcpp::stop("Fatal error encountered, terminating StochKit2R");
      }
    }
#endif
    this->_outputTimes=outputTimes;
    _numberOfIntervals=outputTimes.size();
  }

  std::vector<double> getOutputTimes() {
    return _outputTimes;
  }
  
  void merge(HistogramOutputPacked x){

    for (std::size_t i = 0; i <_numberOfIntervals; i++){
      for (std::size_t j=0; j<_numberOfSpecies;j++) {
	_histograms.at(i*_numberOfSpecies+j).mergeHistogram(x(i,j));
      }
    }

  }
    
  void writeHistogramsToFile(std::string filenamePrefix, std::string filenameSuffix){
    for(std::size_t i=0; i<_numberOfIntervals;i++){
      for(std::size_t j=0; j<_numberOfSpecies;j++){
	std::ostringstream species_oss;
	std::ostringstream interval_oss;
	species_oss << j;
	interval_oss << i;
	std::string fname = filenamePrefix+"_"+species_oss.str()+"_"+interval_oss.str()+filenameSuffix;
	    _histograms.at(i*_numberOfSpecies+j).writeToFile(fname, _outputTimes);
      }
    }
  }

  //include a species label in the histogram file
  void writeHistogramsToFile(std::string filenamePrefix, std::string filenameSuffix, std::vector<std::string> labels){
    for(std::size_t i=0; i<_numberOfIntervals;i++){
      for(std::size_t j=0; j<_numberOfSpecies;j++){
	std::ostringstream species_oss;
	std::ostringstream interval_oss;
	species_oss << j;
	interval_oss << i;
	std::string fname = filenamePrefix+"_"+species_oss.str()+"_"+interval_oss.str()+filenameSuffix;
	    _histograms.at(i*_numberOfSpecies+j).writeToFile(fname, _outputTimes, labels[j]);
      }
    }
  }
 };
}

#endif
