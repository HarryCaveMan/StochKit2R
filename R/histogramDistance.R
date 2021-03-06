#'@title Plot two StochKit2R simulation histograms and display distance
#'
#'@description
#'\code{histogramDistance} Plots histograms of data stored in StochKit2R histogram output files \code{histogramFileName1} and \code{histogramFileName1} and calculates histogram distance. IMPORTANT: histogram file names have format hist_<species index>_<time point>.dat, where species index STARTS AT 0 (not 1!)
#'
#'@param histogramData1 character vector from output object or string with path to StochKit2 histogram output file 1. IMPORTANT: histogram file names have format hist_<species index>_<time point>.dat, where species index STARTS AT 0 (not 1!)
#'@param histogramData2 character vector from output object or string with path to StochKit2 histogram output file 1. IMPORTANT: histogram file names have format hist_<species index>_<time point>.dat, where species index STARTS AT 0 (not 1!)
#'@param file1 indicates whether \code{histogramData1} is data or file name
#'@param file2 indicates whether \code{histogramData2} is data or file name
#'@return The ggplot object
#'@examples
#'\dontrun{
#'#example using included dimer_decay.xml file
#'model <- system.file("dimer_decay.xml",package="StochKit2R")
#'#output written to ex_out directory (created in current working directory)
#'result1 = ssa(model,"ex_out",10,100,20,keepHistograms=TRUE,force=TRUE)
#'
#'#another ensemble with output written to ex_out2 directory
#'result2 = ssa(model,"ex_out2",10,100,20,keepHistograms=TRUE,force=TRUE)
#'#plot the histograms for species 2 ("S2") at time point 5 (t=2.0) for the two runs above
#'histogramDistance(result1$hist$S2[[5]],result2$hist$S2[[5]])
#'#IMPORTANT: histogram file names have format:
#'#hist_<species index>_<time point>.dat, where species index STARTS AT 0
#'histogramDistance("ex_out/histograms/hist_1_4.dat",
#'                  "ex_out2/histograms/hist_1_4.dat",TRUE,TRUE)
#'}
histogramDistance <- function(histogramData1,histogramData2,file1=FALSE,file2=FALSE) {
  
  # read in the lines for the first data 
  if (!file1) {
    # data is coming from character vector from output object, not file
    if (length(histogramData1)!=3) {
      if (length(histogramData1==1)) {
        stop('Invalid histogramData1 (did you intend to set file1=TRUE?)')
      }
      else {
        stop('Invalid histogramData1')        
      }
    }
    
    lines1 <- strsplit(histogramData1,split="\t")
  }
  else {
    #histogramData is a histogram output file name
    if (length(histogramData1)!=1) {
      stop('Invalid histogramData1 argument with file1=TRUE')
    }
    
    # read in the lines 
    lines1 <- strsplit(readLines(histogramData1),split="\t")
  }  
  sID1 <- lines1[[1]][1] # species ID
  time1 = as.numeric(lines1[[1]][2]) # time
  sInd1 = as.numeric(lines1[[1]][2]) # species index
  tInd1 = as.numeric(lines1[[1]][3]) # time index

  lb1 = as.numeric(lines1[[2]][1]) # lower bound
  ub1 = as.numeric(lines1[[2]][2]) # upper bound
  width1 = as.numeric(lines1[[2]][3]) # width
  bsize1 = as.numeric(lines1[[2]][4]) # number of bins

  # read in the third line (bin counts)
  data1 = as.numeric(lines1[[3]])
  # error checking
  if (bsize1!=length(data1)) {
    stop('retrieved size of bins are not equal to the number of bins in the data line')
  }

  dataRange1 <- seq(lb1,ub1,by=width1)
  bincenters1 <- (dataRange1[-1] + dataRange1[-length(dataRange1)])/2
  df1 <- data.frame(centers=bincenters1,counts=data1)

  #read in second file
  # read in the lines for the first data 
  if (!file2) {
    # data is coming from character vector from output object, not file
    if (length(histogramData2)!=3) {
      if (length(histogramData2==1)) {
        stop('Invalid histogramData2 (did you intend to set file2=TRUE?)')
      }
      else {
        stop('Invalid histogramData2')        
      }
    }
    
    lines2 <- strsplit(histogramData2,split="\t")
  }
  else {
    #histogramData is a histogram output file name
    if (length(histogramData2)!=1) {
      stop('Invalid histogramData2 argument with file2=TRUE')
    }
    
    # read in the lines 
    lines2 <- strsplit(readLines(histogramData2),split="\t")
  }  
  
  sID2 <- lines2[[1]][1] # species ID
  time2 = as.numeric(lines2[[1]][2]) # time
  sInd2 = as.numeric(lines2[[1]][2]) # species index
  tInd2 = as.numeric(lines2[[1]][3]) # time index
  
  lb2 = as.numeric(lines2[[2]][1]) # lower bound
  ub2 = as.numeric(lines2[[2]][2]) # upper bound
  width2 = as.numeric(lines2[[2]][3]) # width
  bsize2 = as.numeric(lines2[[2]][4]) # number of bins
  
  # read in the third line (bin counts)
  data2 = as.numeric(lines2[[3]])
  # error checking
  if (bsize2!=length(data2)) {
    stop('retrieved size of bins are not equal to the number of bins in the data line')
  }
  
  dataRange2 <- seq(lb2,ub2,by=width2)
  bincenters2 <- (dataRange2[-1] + dataRange2[-length(dataRange2)])/2
  centers=NULL#only to appease R CMD CHECK for CRAN
  counts=NULL#only to appease R CMD CHECK for CRAN
  df2 <- data.frame(centers=bincenters2,counts=data2)
 
  if (sID1!=sID2) {
    warning(paste('Species ID mismatch, ID1:',sID1,", ID2:",sID2))
  }
  if (time1!=time2) {
    warning(paste('Time point mismatch, Time1:',time1,", Time2:",time2))
  }
  if (bsize1!=bsize2) {
    stop('two histograms must have the same number of bins')
  }
  
  # Syncronize the histograms if necessary
  llb1 = lb1 + (which(data1>0)[1]-1)*width1
  llb2 = lb2 + (which(data2>0)[1]-1)*width2
  glb = min(llb1,llb2)
  lub1 = lb1 + (which(data1>0)[length(which(data1>0))])*width1
  lub2 = lb2 + (which(data2>0)[length(which(data2>0))])*width2
  gub = max(lub1,lub2)
  gwidth = max(width1,width2)

  if (glb<0 | glb>gub) {
    stop("error in bounds")
  }
  nlb = floor((glb/gwidth)*gwidth)
  nub = nlb+length(data1)*gwidth
  while (gub > nub) {
    gwidth = gwidth*2
    nlb = floor(glb / gwidth) * gwidth
    nub = nlb + length(data1) * gwidth
  }
  gIwidth = 1/gwidth
  
  his1 = rep(0,length(data1))
  his2 = rep(0,length(data2))

  #data1
  for (i in 0:(length(data1)-1)) {
    if (data1[i+1] != 0) {
      event = lb1+i*width1
      if (nlb>event || event>=nub) {
        stop('invalid new upper and/or lower bound')
      }
      his1[1+floor((event-nlb)*gIwidth)] = his1[1+floor((event-nlb)*gIwidth)]+data1[i+1];
    }
  }
  
  #data2
  for (i in 0:(length(data2)-1)) {
    if (data2[i+1] != 0) {
      event2 = lb2+i*width2
      if (nlb>event2 ||event2>=nub) {
        stop('invalid new upper and/or lower bound')
      }
      his2[1+floor((event2-nlb)*gIwidth)] = his2[1+floor((event2-nlb)*gIwidth)]+data2[i+1]
    }
  }
 
  # plot
  dataRange <- seq(nlb,nub,by=gwidth)
  bincenters <- (dataRange[-1] + dataRange[-length(dataRange)])/2
  df1 <- data.frame(centers=bincenters,counts=his1)
  
  p <- ggplot(data=df1,aes(x=centers,y=counts)) + geom_bar(stat="identity",width=gwidth,colour="red",fill="red",alpha=.65) + ylab("Bin Counts") + xlab("Bin Centers") + ggtitle(paste("Species:",sID1," Time:",time1))

  df2 <- data.frame(centers=bincenters,counts=his2)
  p2 <- p + geom_bar(data=df2,stat="identity",width=gwidth,colour="dark blue",fill="dark blue",alpha=.65)
  
  maxCount <- max(his1,his2)
  
  # compute histogram distance
  his1= his1/sum(his1);
  his2= his2/sum(his2);
  
  euclidean_distance = sqrt(sum(abs(his1-his2)^2))
  manhattan_distance = sum(abs(his1-his2))
  p3 <- p2 + annotate("text", size=4, x = (dataRange[length(dataRange)]+dataRange[1])/2, y = maxCount*1.1, label = sprintf("Euclidean d=%2.3f, Manhattan d=%2.3f",euclidean_distance,manhattan_distance))
  return(p3)
}
