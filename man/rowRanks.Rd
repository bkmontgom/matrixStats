% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/rowRanks.R
\name{rowRanks}
\alias{rowRanks}
\alias{colRanks}
\title{Gets the rank of the elements in each row (column) of a matrix}
\usage{
rowRanks(x, rows = NULL, cols = NULL, ties.method = c("max",
  "average", "first", "last", "random", "max", "min", "dense"),
  dim. = dim(x), ...)

colRanks(x, rows = NULL, cols = NULL, ties.method = c("max",
  "average", "first", "last", "random", "max", "min", "dense"),
  dim. = dim(x), preserveShape = FALSE, ...)
}
\arguments{
\item{x}{A \code{\link[base]{numeric}} or \code{\link[base]{integer}} NxK
\code{\link[base]{matrix}}.}

\item{rows, cols}{A \code{\link[base]{vector}} indicating subset of rows
(and/or columns) to operate over. If \code{\link[base]{NULL}}, no subsetting
is done.}

\item{ties.method}{A \code{\link[base]{character}} string specifying how
ties are treated.  For details, see below.}

\item{dim.}{An \code{\link[base]{integer}} \code{\link[base]{vector}} of
length two specifying the dimension of \code{x}, also when not a
\code{\link[base]{matrix}}.}

\item{...}{Not used.}

\item{preserveShape}{A \code{\link[base]{logical}} specifying whether the
\code{\link[base]{matrix}} returned should preserve the input shape of
\code{x}, or not.}
}
\value{
An \code{\link[base]{integer}} \code{\link[base]{matrix}} is
returned.  The \code{rowRanks()} function always returns an NxK
\code{\link[base]{matrix}}, where N (K) is the number of rows (columns)
whose ranks are calculated.

The \code{colRanks()} function returns an NxK \code{\link[base]{matrix}}, if
\code{preserveShape = TRUE}, otherwise a KxN \code{\link[base]{matrix}}.

%% The mode of the returned matrix is \code{\link[base]{integer}}, except
for %% \code{ties.method == "average"} when it is
\code{\link[base]{double}}.
}
\description{
Gets the rank of the elements in each row (column) of a matrix.
}
\details{
The row ranks of \code{x} are collected as \emph{rows} of the result matrix.

The column ranks of \code{x} are collected as \emph{rows} if
\code{preserveShape = FALSE}, otherwise as \emph{columns}.

The implementation is optimized for both speed and memory.  To avoid
coercing to \code{\link[base]{double}}s (and hence memory allocation), there
is a unique implementation for \code{\link[base]{integer}} matrices.  It is
more memory efficient to do \code{colRanks(x, preserveShape = TRUE)} than
\code{t(colRanks(x, preserveShape = FALSE))}.

Any \code{\link[base]{names}} of \code{x} are ignored and absent in the
result.
}
\section{Missing and non- values}{
 These are ranked as \code{NA}, as with
\code{na.last = "keep"} in the \code{\link[base]{rank}}() function.
}

\seealso{
\code{\link[base]{rank}}().  
\code{\link[data.table]{frank}}() for ties.method 'dense'.  
For developers, see also Section Utility functions' in 
'Writing R Extensions manual', particularly the
native functions \code{R_qsort_I()} and \code{R_qsort_int_I()}.
}
\author{
Hector Corrada Bravo and Harris Jaffee.  Peter Langfelder for adding
'ties.method' support.  Brian Montgomery for adding more 'ties.method's.
Henrik Bengtsson adapted the original native
implementation of \code{rowRanks()} from Robert Gentleman's \code{rowQ()} in
the \pkg{Biobase} package.
}
\keyword{array}
\keyword{iteration}
\keyword{robust}
\keyword{univar}
