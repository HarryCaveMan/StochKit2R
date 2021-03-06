% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/createOutputDirs.R
\name{createOutputDirs}
\alias{createOutputDirs}
\title{Create Output Directories for ssa and tauLeaping}
\usage{
createOutputDirs(outputDir, noStats, keepTrajectories, keepHistograms, force)
}
\arguments{
\item{outputDir}{Character string with path to output directory.}

\item{noStats}{true if not keeping statistics data}

\item{keepTrajectories}{true if keeping trajectory data}

\item{keepHistograms}{true if keeping histogram data}

\item{overwrite}{and delete existing output directories, if they exists}
}
\description{
\code{createOutputDirs} Called to ssa and tauLeaping to create output directory
}
