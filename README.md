**This is an outdated package**

Consider using [scipy.optimize.linear_sum_assignment](https://docs.scipy.org/doc/scipy/reference/generated/scipy.optimize.linear_sum_assignment.html) instead.

*For posterity:*

This Python module is just a simple wrapper for the C++ code written by Jonker to implement the Jonker-Volgenant algorithm, LAPJV, for the linear assignment problem.

See the important notes below to properly use this algorithm. For a more tolerant, but slower, LAP algorithm see http://github.com/hrldcpr/hungarian

Note that this module depends on the numpy module. You must install numpy before you can compile this module. Numpy can be downloaded from http://numpy.scipy.org

If you have any problems with this module, you should contact me, not Dr. Jonker.


To build this module run:

    > python setup.py build

Then you can either put the file build/lib-<YOUR-PLATFORM>/LAPJV.so in the same directory as the code that will be using it, or you can install it so that all of your python programs can see it:

    > python setup.py install

For the module's documentation, type at a Python prompt:

    >>> help('LAPJV')

For a usage example, courtesy of Dr. N.D. van Foreest, see example.py


Additional Information
----------------------

LAPJV comes from the paper:

R. Jonker and A. Volgenant, "A Shortest Augmenting Path Algorithm for Dense and Sparse Linear Assignment Problems," _Computing_, vol. 38, pp. 325-340, 1987.

According to that paper, it is notably faster than the Hungarian algorithm (a.k.a. Munkres' algorithm) and several other linear assignment algorithms.

The C++ source comes from:
http://www.magiclogic.com/assignment.html

If any of those links are broken then try them in the Wayback Machine! For example the original C++ source zip can be obtained at:
https://web.archive.org/web/*/http://www.magiclogic.com/assignment/lap_cpp.zip

This wrapper for the algorithm uses single precision (i.e. 32-bit) floating point arithmetic. To change it to double precision, integer, or anything else, simply change the corresponding types in lap.h

Nota Bene
---------
The following matrices, and others, cause Jonker's code to loop forever. According to Dr. Volgenant, "The failure is a consequence of a tolerance not suited for the data ... You have to reduce the value of the tolerance such that it is smaller than the smallest difference between any pair of cost elements in the cost matrix."

There is no variable tolerance inherent to Jonker's code, so the solution is to scale all of the costs by some factor, which of course will not change the optimal assignment. For example, both of the matrices below no longer fail under single-precision if multiplied by 10. Under double-precision, however, it seems harder to fix.

Here are two offending matrices, for single and double precision:
* http://syzygy.st/Public/pyLAPJV-float-fail.txt
* http://syzygy.st/Public/pyLAPJV-double-fail.txt

Nota Melior
-----------
Tom Marthaler may have solved the preceding problem, although I've yet to try it, but it sounds good. His email says:

"If you don't care about the actual value difference between the optimal assignments, have you tried to map the values using a simple log function? Meaning, if you did a -log(x) on all of the values in the cost matrix, then the optimal assignment should be the same (I am not going to prove it though!) but the relative differences between the cost values should increase. Its what we do for our lapjv implementation, and I have yet to see the type of problems that you describe (however, our precision is only to 2-3 decimals)."

Thanks Tom!
