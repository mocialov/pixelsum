* O(1) time for submatrix summation: https://www.techiedelight.com/calculate-sum-elements-sub-matrix-constant-time/

* O(n*m) to count zeros in matrix

* TESTS:
  - square matrix - one non-zero element
  - square matrix - two non-zero elements
  - square matrix - one zero element
  - square matrix - outside boundaries
  - square matrix - x0 > x1 and y0 > y1
  - square matrix - copy constructor
  - square matrix - operator=
  - non-square matrix - outside boundaries (left-top, right-top, right-bottom, left-bottom)
  - non-square matrix - submatrix outside the actual matrix

* COMPILE'n'RUN: g++ tests.cpp pixelsum.cpp -o testpixelsum && ./testpixelsum
