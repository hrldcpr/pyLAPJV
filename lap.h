/************************************************************************
*
*  lap.h
   version 1.0 - 21 june 1996
   author  Roy Jonker, MagicLogic Optimization Inc.
   
   header file for LAP
   
*
      pyLAPJV by Harold Cooper (hbc@mit.edu)
      2004-08-24: changed cost type from double to float, because the
          following matrix (in addition to others) wasn't working:
          http://mit.edu/harold/Public/pyLAPJV-double-fail.txt
      2004-08-13:
          -- fixed Jonker's function declarations to actually use row, col,
             and cost types
	  -- row, col, and cost now based on numarray types
*
**************************************************************************/

#include "Python.h"
#include "numpy/arrayobject.h"

/*************** CONSTANTS  *******************/

  #define BIG 100000

/*************** TYPES      *******************/

  typedef npy_int row;
  #define ROW_TYPE NPY_INT
  typedef npy_int col;
  #define COL_TYPE NPY_INT
  typedef npy_double cost;
  #define COST_TYPE NPY_DOUBLE

/*************** FUNCTIONS  *******************/

extern cost lap(int dim, cost **assigncost,
                col *rowsol, row *colsol, cost *u, cost *v);

//extern void checklap(int dim, cost **assigncost,
//                     col *rowsol, row *colsol, cost *u, cost *v);

