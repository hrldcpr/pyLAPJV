/*
  pyLAPJV by Harold Cooper (hbc@mit.edu)
  pyLAPJV.cpp 2004-08-20
*/

#include "lap.h"

static PyObject *
LAPJV_lap(PyObject *self, PyObject *args)
//lap(costs)
{
  PyObject *ocosts;
  PyArrayObject *costs;
  int n;
  col *rowsol;
  row *colsol;
  cost lapcost,*buf,**ccosts,*u,*v;
  npy_intp *strides;

  if (!PyArg_ParseTuple(args, "O", &ocosts))
    return NULL;
  costs = (PyArrayObject*)PyArray_FromAny(
                                          ocosts,PyArray_DescrFromType(COST_TYPE),2,2,
                                          NPY_CONTIGUOUS|NPY_ALIGNED|NPY_FORCECAST,0
                                          );
  if (costs->nd!=2)
    {
      PyErr_SetString(PyExc_ValueError,"lap() requires a 2-D matrix");
      goto error;
    }
  n = costs->dimensions[0];
  if (costs->dimensions[1]!=n)
    {
      PyErr_SetString(PyExc_ValueError,"lap() requires a square matrix");
      goto error;
    }

  //get inputted matrix as a 1-D C array:
  //buf = (cost *)NA_OFFSETDATA(costs);
  buf = (cost*)PyArray_DATA(costs);

  //copy inputted matrix into a 2-dimensional C array:
  strides = PyArray_STRIDES(costs);
  assert(strides[1] == sizeof(cost));
  ccosts = (cost **)malloc(sizeof(cost *)*n);
  if(!ccosts)
    {
      PyErr_NoMemory();
      goto error;
    }
  for(int i=0;i<n;i++)
    ccosts[i] = buf+i*(strides[0]/sizeof(cost));

  rowsol = (col *)malloc(sizeof(col)*n);
  colsol = (row *)malloc(sizeof(row)*n);
  u = (cost *)malloc(sizeof(cost)*n);
  v = (cost *)malloc(sizeof(cost)*n);
  if(!(rowsol&&colsol&&u&&v))
    {
      PyErr_NoMemory();
      goto error;
    }

  //run LAPJV!:
  lapcost = lap(n,ccosts,rowsol,colsol,u,v);

  //NA_InputArray() incremented costs, but now we're done with it, so let it get GC'ed:
  Py_XDECREF(costs);

  return Py_BuildValue("(dOOOO)",lapcost,
                       PyArray_SimpleNewFromData(1,(npy_intp*)&n,COL_TYPE,rowsol),
                       PyArray_SimpleNewFromData(1,(npy_intp*)&n,ROW_TYPE,colsol),
                       PyArray_SimpleNewFromData(1,(npy_intp*)&n,COST_TYPE,u),
                       PyArray_SimpleNewFromData(1,(npy_intp*)&n,COST_TYPE,v)
                       );

 error:
  Py_XDECREF(costs);
  return NULL;
}

static PyMethodDef LAPJVMethods[] = {
  {"lap",  LAPJV_lap, METH_VARARGS,
   "Solves the linear assignment problem using the Jonker-Volgenant\nalgorithm.\n\nlap() takes a single argument - a square cost matrix - and returns a\n5-tuple of the form\n(min_cost,row_assigns,col_assigns,row_dual_vars,col_dual_vars).\n\nThe average user probably just wants the second or third of these\nelements, so a call like: \'assigns=lap(costs)[2]\' would be the\nmost common use."},
  {NULL, NULL, 0, NULL}        /* Sentinel (terminates structure) */
};

PyMODINIT_FUNC
initLAPJV(void)
{
  (void) Py_InitModule("LAPJV", LAPJVMethods);
  import_array();
}

int
main(int argc, char *argv[])
{
  /* Pass argv[0] to the Python interpreter */
  Py_SetProgramName(argv[0]);

  /* Initialize the Python interpreter.  Required. */
  Py_Initialize();

  /* Add a static module */
  initLAPJV();

  return 0;
}
