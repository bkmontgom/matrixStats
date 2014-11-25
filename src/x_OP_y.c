#include <Rdefines.h>
#include "types.h"
#include "utils.h"

#define METHOD x_OP_y

/* Addition */
#define X_TYPE 'i'
#define Y_TYPE 'i'
#define ANS_TYPE 'i'
#define OP '+'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'i'
#define Y_TYPE 'r'
#define ANS_TYPE 'r'
#define OP '+'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'r'
#define Y_TYPE 'i'
#define ANS_TYPE 'r'
#define OP '+'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'r'
#define Y_TYPE 'r'
#define ANS_TYPE 'r'
#define OP '+'
#include "x_OP_y_TYPE-template.h"


/* Subtraction */
#define X_TYPE 'i'
#define Y_TYPE 'i'
#define ANS_TYPE 'i'
#define OP '-'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'i'
#define Y_TYPE 'r'
#define ANS_TYPE 'r'
#define OP '-'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'r'
#define Y_TYPE 'i'
#define ANS_TYPE 'r'
#define OP '-'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'r'
#define Y_TYPE 'r'
#define ANS_TYPE 'r'
#define OP '-'
#include "x_OP_y_TYPE-template.h"


/* Multiplication */
#define X_TYPE 'i'
#define Y_TYPE 'i'
#define ANS_TYPE 'i'
#define OP '*'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'i'
#define Y_TYPE 'r'
#define ANS_TYPE 'r'
#define OP '*'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'r'
#define Y_TYPE 'i'
#define ANS_TYPE 'r'
#define OP '*'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'r'
#define Y_TYPE 'r'
#define ANS_TYPE 'r'
#define OP '*'
#include "x_OP_y_TYPE-template.h"


/* Division */
#define X_TYPE 'i'
#define Y_TYPE 'i'
#define ANS_TYPE 'r'
#define OP '/'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'i'
#define Y_TYPE 'r'
#define ANS_TYPE 'r'
#define OP '/'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'r'
#define Y_TYPE 'i'
#define ANS_TYPE 'r'
#define OP '/'
#include "x_OP_y_TYPE-template.h"

#define X_TYPE 'r'
#define Y_TYPE 'r'
#define ANS_TYPE 'r'
#define OP '/'
#include "x_OP_y_TYPE-template.h"


#undef METHOD


SEXP x_OP_y(SEXP x, SEXP y, SEXP dim, SEXP naRm, SEXP hasNA, SEXP operator) {
  SEXP ans;
  int narm, hasna, op;
  R_xlen_t nrow, ncol;

  /* Argument 'x' and 'dim': */
  assertArgMatrix(x, dim, (R_TYPE_INT | R_TYPE_REAL), "x");
  nrow = INTEGER(dim)[0];
  ncol = INTEGER(dim)[1];

  /* Argument 'y': */
  assertArgVector(y, (R_TYPE_INT | R_TYPE_REAL), "y");

  /* Argument 'naRm': */
  narm = asLogicalNoNA(naRm, "na.rm");

  /* Argument 'hasNA': */
  hasna = asLogicalNoNA(hasNA, "hasNA");

  /* Argument 'operator': */
  op = asInteger(operator);


  if (op == 1) {
    /* Addition */  
    if (isReal(x) || isReal(y)) {
      PROTECT(ans = allocMatrix(REALSXP, nrow, ncol));
      if (isReal(x) && isReal(y)) {
        x_OP_y_Real_Real_Add(REAL(x), xlength(x), REAL(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
      } else if (isReal(x) && isInteger(y)) {
        x_OP_y_Real_Integer_Add(REAL(x), xlength(x), INTEGER(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
      } else if (isInteger(x) && isReal(y)) {
        x_OP_y_Integer_Real_Add(INTEGER(x), xlength(x), REAL(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
      }
      UNPROTECT(1);
    } else {
      PROTECT(ans = allocMatrix(INTSXP, nrow, ncol));
      x_OP_y_Integer_Integer_Add(INTEGER(x), xlength(x), INTEGER(y), xlength(y), narm, FALSE, INTEGER(ans), xlength(ans));
      UNPROTECT(1);
    }
  } if (op == 2) {
    /* Subtraction */  
    if (isReal(x) || isReal(y)) {
      PROTECT(ans = allocMatrix(REALSXP, nrow, ncol));
      if (isReal(x) && isReal(y)) {
        x_OP_y_Real_Real_Sub(REAL(x), xlength(x), REAL(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
      } else if (isReal(x) && isInteger(y)) {
        x_OP_y_Real_Integer_Sub(REAL(x), xlength(x), INTEGER(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
      } else if (isInteger(x) && isReal(y)) {
        x_OP_y_Integer_Real_Sub(INTEGER(x), xlength(x), REAL(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
      }
      UNPROTECT(1);
    } else {
      PROTECT(ans = allocMatrix(INTSXP, nrow, ncol));
      x_OP_y_Integer_Integer_Sub(INTEGER(x), xlength(x), INTEGER(y), xlength(y), narm, FALSE, INTEGER(ans), xlength(ans));
      UNPROTECT(1);
    }
  } else if (op == 3) {
    /* Multiplication */  
    if (isReal(x) || isReal(y)) {
      PROTECT(ans = allocMatrix(REALSXP, nrow, ncol));
      if (isReal(x) && isReal(y)) {
        x_OP_y_Real_Real_Mul(REAL(x), xlength(x), REAL(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
      } else if (isReal(x) && isInteger(y)) {
        x_OP_y_Real_Integer_Mul(REAL(x), xlength(x), INTEGER(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
      } else if (isInteger(x) && isReal(y)) {
        x_OP_y_Integer_Real_Mul(INTEGER(x), xlength(x), REAL(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
      }
      UNPROTECT(1);
    } else {
      PROTECT(ans = allocMatrix(INTSXP, nrow, ncol));
      x_OP_y_Integer_Integer_Mul(INTEGER(x), xlength(x), INTEGER(y), xlength(y), narm, FALSE, INTEGER(ans), xlength(ans));
      UNPROTECT(1);
    }
  } else if (op == 4) {
    /* Division */  
    PROTECT(ans = allocMatrix(REALSXP, nrow, ncol));
    if (isReal(x) && isReal(y)) {
      x_OP_y_Real_Real_Div(REAL(x), xlength(x), REAL(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
    } else if (isReal(x) && isInteger(y)) {
      x_OP_y_Real_Integer_Div(REAL(x), xlength(x), INTEGER(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
    } else if (isInteger(x) && isReal(y)) {
      x_OP_y_Integer_Real_Div(INTEGER(x), xlength(x), REAL(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
    } else if (isInteger(x) && isInteger(y)) {
      x_OP_y_Integer_Integer_Div(INTEGER(x), xlength(x), INTEGER(y), xlength(y), narm, FALSE, REAL(ans), xlength(ans));
    }
    UNPROTECT(1);
  }

  return(ans);
} /* x_OP_y() */
