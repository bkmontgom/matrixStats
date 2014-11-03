/***********************************************************************
 TEMPLATE:
  SEXP sumOver_<Integer|Real>(SEXP x, SEXP idxs, SEXP naRm, SEXP mode)

 GENERATES:
  SEXP sumOver_Integer(SEXP x, SEXP idxs, SEXP naRm, SEXP mode)
  SEXP sumOver_Real(SEXP x, SEXP idxs, SEXP naRm, SEXP mode)

 Arguments:
   The following macros ("arguments") should be defined for the
   template to work as intended.

  - METHOD_NAME: the name of the resulting function
  - X_TYPE: 'i' or 'r'

 Copyright: Henrik Bengtsson, 2014
 ***********************************************************************/
#include <Rdefines.h>
#include <Rmath.h>
#include <float.h>

/* Expand arguments:
    X_TYPE => (X_C_TYPE, X_IN_C, [METHOD_NAME])
 */
#include "templates-types.h"
#include <R_ext/Error.h>

#define R_INT_MAX  INT_MAX
#define R_INT_MIN -INT_MAX

SEXP METHOD_NAME(SEXP x, SEXP idxs, SEXP naRm, SEXP mode) {
  /* Arguments */
  X_C_TYPE *xp, value;
  int *idxsp;
  int narm;
  /* Value */
  SEXP ans;

  int n, nx;
  /*
  R_XLEN_T n;
  R_XLEN_T nx;
  */

  int i, idx;
  double sum = 0;

  /* Argument 'naRm': */
  if (!isLogical(naRm))
    error("Argument 'naRm' must be a single logical.");

  if (length(naRm) != 1)
    error("Argument 'naRm' must be a single logical.");

  narm = LOGICAL(naRm)[0];
  if (narm != TRUE && narm != FALSE) {
    error("Argument 'naRm' must be either TRUE or FALSE.");
  }

  /* Argument 'mode': */
  if (!isInteger(mode))
    error("Argument 'mode' must be a single integer.");

  xp = X_IN_C(x);
  nx = XLENGTH(x);

  /* Sum over all element? */
  if (isNull(idxs)) {
    for (i=0; i < nx; i++) {
      value = xp[i];
#if X_TYPE == 'i'
      if (!X_ISNAN(value)) {
        sum += (double)value;
      } else if (!narm) {
          sum = R_NaReal;
          break;
      }
#elif X_TYPE == 'r'
      if (!narm || !X_ISNAN(value)) {
        sum += (double)value;
      }
#endif
    } /* for (i ...) */
  } else {
    idxsp = INTEGER(idxs);
    n = XLENGTH(idxs);

    for (i=0; i < n; i++) {
      idx = idxsp[i];
      if (idx <= 0) {
        Rf_error("Argument \'idxs\' contains a non-positive index: %d", idx);
      } else if (idx > nx) {
        Rf_error("Argument \'idxs\' contains an index out of range [1,%d]: %d", n, idx);
      }
      value = xp[idx-1];
#if X_TYPE == 'i'
      if (!X_ISNAN(value)) {
        sum += (double)value;
      } else if (!narm) {
          sum = R_NaReal;
          break;
      }
#elif X_TYPE == 'r'
      if (!narm || !X_ISNAN(value)) {
        sum += (double)value;
      }
#endif
    } /* for (i ...) */
  }


  /* Return type? */
  switch (asInteger(mode)) {
  case 1: /* integer */
    PROTECT(ans = allocVector(INTSXP, 1));
    if (ISNAN(sum)) {
      INTEGER(ans)[0] = NA_INTEGER;
    } else if (sum > R_INT_MAX || sum < R_INT_MIN) {
      Rf_warning("Integer overflow. Use sumOver(..., mode=\"numeric\") to avoid this.");
      INTEGER(ans)[0] = NA_INTEGER;
    } else {
      INTEGER(ans)[0] = (int)sum;
    }
    UNPROTECT(1);
    break;
  case 2: /* numeric */
    PROTECT(ans = allocVector(REALSXP, 1));
    if (sum > DBL_MAX) {
      REAL(ans)[0] = R_PosInf;
    } else if (sum < -DBL_MAX) {
      REAL(ans)[0] = R_NegInf;
    } else {
      REAL(ans)[0] = sum;
    }
    UNPROTECT(1);
    break;

  default:
    /* To please the compiler; should never happen. */
    ans = NILSXP;
    break;
  }

  return(ans);
}

/* Undo template macros */
#include "templates-types_undef.h"

/***************************************************************************
 HISTORY:
 2014-11-02 [HB]
 o Created.
 **************************************************************************/