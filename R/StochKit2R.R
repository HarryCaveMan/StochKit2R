#' StochKit2R: a package for efficient discrete stochastic simulation using the Gillepie Algorithm (SSA) and tau-leaping
#'
#' The package provides an R interface to stochastic simulation functions and 
#' provides functions for generating plots of the simulation data.
#'
#' @section Simulation functions:
#' There are three simulation functions: ssa, ssaSingle and tauLeaping. 
#' ssa and tauLeaping run ensembles (many simulations) and store output at uniformly
#' spaced time intervals. By default they store means and variances, but trajectories
#' and histogram data can also be stored. ssaSingle runs a single trajectory and
#' stores a row of output for every reaction event that occurs.  Consult the individual
#' function help functions or the User Manual vignette for more information.
#'
#' @section Plotting functions:
#' There are four plotting functions: plotStats, plotTrajectories, plotHistogram, and histogramDistance 
#' For plotting stats, trajectories, and histogram data. Consult the individual function help functions
#' or the User Manual vignette for more information.
#'
#' @docType package
#' @name StochKit2R
NULL
