% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/plotTrajectories.R
\name{plotTrajectories}
\alias{plotTrajectories}
\title{Plot StochKit2R simulation trajectory output data}
\usage{
plotTrajectories(trajectoriesData, outputIndex, speciesIndex, file = F)
}
\arguments{
\item{trajectoriesData}{String containing file (must end in /trajectories) name or $trajs list of ssa output, depending on the value of the file parameter}

\item{outputIndex}{Integer vector containing indexes for which trials will be plotted}

\item{speciesIndex}{Integer Vector of the species indices that will be plotted. The first species is index 1}
}
\value{
The ggplot object
}
\description{
\code{plotTrajectories} Plots trajectories \code{outputIndex} of populations specified in \code{speciesIndex} in the StochKit2R trajectories in \code{trajectoriesData}
}
\examples{
\dontrun{
#example using included dimer_decay.xml file
model <- system.file("dimer_decay.xml",package="StochKit2R")
#output written to ex_out directory (created in current working directory)
out <- ssa(model,10,100,20,F,T,T,outputDir="ex_out",force=T)
#plot the data for species 1,2 and 3 for trajectories 2,3,4 and 5 from file
plotTrajectories("ex_out/trajectories",2:3,1:3,TRUE)
#same plot from output
plotTrajectories(out$trajs,2:3,1:3)
}
}
