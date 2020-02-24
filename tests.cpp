#include "pixelsum.h"
#include <iostream>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]){
  
  int rows = 6;
  int columns = 6;

  const unsigned char buffer[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

  PixelSum pixSum(buffer, rows, columns);

  //TEST 1 - square matrix - one non-zero element; 7 @ (1,1)
  int x0 = 1;
  int y0 = 1;
  int x1 = 1;
  int y1 = 1;

  assert(pixSum.getPixelSum(x0, y0, x1, y1) == 7);
  assert(pixSum.getPixelAverage(x0, y0, x1, y1) == 7);
  assert(pixSum.getNonZeroCount(x0, y0, x1, y1) == 1);
  assert(pixSum.getNonZeroAverage(x0, y0, x1, y1) == 7);


  //TEST 2 - square matrix - two non-zero elements; 7 & 8 @ (1,1)-(1,2)
  x0 = 1;
  y0 = 1;
  x1 = 2;
  y1 = 1;

  assert(pixSum.getPixelSum(x0, y0, x1, y1) == 15);
  assert(pixSum.getPixelAverage(x0, y0, x1, y1) == 15 / float(2));
  assert(pixSum.getNonZeroCount(x0, y0, x1, y1) == 2);
  assert(pixSum.getNonZeroAverage(x0, y0, x1, y1) == 15 / float(2));


  //TEST 3 - square matrix - one zero element; 0 @ (0, 0)
  x0 = 0;
  y0 = 0;
  x1 = 0;
  y1 = 0;

  assert(pixSum.getPixelSum(x0, y0, x1, y1) == 0);
  assert(pixSum.getPixelAverage(x0, y0, x1, y1) == 0);
  assert(pixSum.getNonZeroCount(x0, y0, x1, y1) == 0);
  assert(pixSum.getNonZeroAverage(x0, y0, x1, y1) == 0);

  //TEST 4 - square matrix - outside boundaries left-top side; 0, 1, 6, 7 @ (-1,-1)-(1,1)
  x0 = -1;
  y0 = -1;
  x1 = 1;
  y1 = 1;

  assert(pixSum.getPixelSum(x0, y0, x1, y1) == 14);
  assert(pixSum.getPixelAverage(x0, y0, x1, y1) == 14/(float)9);
  assert(pixSum.getNonZeroCount(x0, y0, x1, y1) == 3);
  assert(pixSum.getNonZeroAverage(x0, y0, x1, y1) == 14/(float)3);

  //TEST 5 - square matrix - x0 > x1 & y0 > y1; 0, 1, 6, 7 @ (1,1)-(-1,-1)
  x0 = 1;
  y0 = 1;
  x1 = -1;
  y1 = -1;

  assert(pixSum.getPixelSum(x0, y0, x1, y1) == 14);
  assert(pixSum.getPixelAverage(x0, y0, x1, y1) == 14/(float)9);
  assert(pixSum.getNonZeroCount(x0, y0, x1, y1) == 3);
  assert(pixSum.getNonZeroAverage(x0, y0, x1, y1) == 14/(float)3);


  //TEST 6 - square matrix - copy constructor (same as test 5)
  PixelSum pixSum1 = pixSum;
  x0 = 1;
  y0 = 1;
  x1 = -1;
  y1 = -1;

  assert(pixSum1.getPixelSum(x0, y0, x1, y1) == 14);
  assert(pixSum1.getPixelAverage(x0, y0, x1, y1) == 14/(float)9);
  assert(pixSum1.getNonZeroCount(x0, y0, x1, y1) == 3);
  assert(pixSum1.getNonZeroAverage(x0, y0, x1, y1) == 14/(float)3);

  //TEST 7 - square matrix - assigning one object to another (same as test 5)
  const unsigned char buffer1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  PixelSum pixSum2(buffer1, rows, columns);

  x0 = 1;
  y0 = 1;
  x1 = -1;
  y1 = -1;

  assert(pixSum2.getPixelSum(x0, y0, x1, y1) == 0);
  assert(pixSum2.getPixelAverage(x0, y0, x1, y1) == 0);
  assert(pixSum2.getNonZeroCount(x0, y0, x1, y1) == 0);
  assert(pixSum2.getNonZeroAverage(x0, y0, x1, y1) == 0);

  pixSum2 = pixSum1;

  x0 = 1;
  y0 = 1;
  x1 = -1;
  y1 = -1;

  assert(pixSum2.getPixelSum(x0, y0, x1, y1) == 14);
  assert(pixSum2.getPixelAverage(x0, y0, x1, y1) == 14/(float)9);
  assert(pixSum2.getNonZeroCount(x0, y0, x1, y1) == 3);
  assert(pixSum2.getNonZeroAverage(x0, y0, x1, y1) == 14/(float)3);


  //TEST 8.1 - non-square matrix - outside boundaries left-top side; 0, 1, 9, 10 @ (-1,-1)-(1,1)


  columns = 9;
  rows = 2;

  const unsigned char buffer2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

  PixelSum pixSum3(buffer2, columns, rows);
  x0 = -1;
  y0 = -1;
  x1 = 1;
  y1 = 1;

  assert(pixSum3.getPixelSum(x0, y0, x1, y1) == 20);
  assert(pixSum3.getPixelAverage(x0, y0, x1, y1) == 20/float(9));
  assert(pixSum3.getNonZeroCount(x0, y0, x1, y1) == 3);
  assert(pixSum3.getNonZeroAverage(x0, y0, x1, y1) == 20/float(3));
  

  //TEST 8.2 - non-square matrix - outside boundaries right-top side; 7, 8, 16, 17 @ (7,0)-(9,2)
  x0 = 7;
  y0 = 0;
  x1 = 9;
  y1 = 2;

  assert(pixSum3.getPixelSum(x0, y0, x1, y1) == 48);
  assert(pixSum3.getPixelAverage(x0, y0, x1, y1) == 48/float(9));
  assert(pixSum3.getNonZeroCount(x0, y0, x1, y1) == 4);
  assert(pixSum3.getNonZeroAverage(x0, y0, x1, y1) == 48/float(4));

  //TEST 8.3 - non-square matrix - outside boundaries right-bottom side; 16,17 @ (7,1)-(9,3)
  x0 = 7;
  y0 = 1;
  x1 = 9;
  y1 = 3;

  assert(pixSum3.getPixelSum(x0, y0, x1, y1) == 33);
  assert(pixSum3.getPixelAverage(x0, y0, x1, y1) == 33/float(9));
  assert(pixSum3.getNonZeroCount(x0, y0, x1, y1) == 2);
  assert(pixSum3.getNonZeroAverage(x0, y0, x1, y1) == 33/float(2));

  
  //TEST 8.4 - non-square matrix - outside boundaries left-bottom side; 9, 10 @ (-1,3)-(1, 1)
  x0 = -1;
  y0 = 3;
  x1 = 1;
  y1 = 1;

  assert(pixSum3.getPixelSum(x0, y0, x1, y1) == 19);
  assert(pixSum3.getPixelAverage(x0, y0, x1, y1) == 19/float(9));
  assert(pixSum3.getNonZeroCount(x0, y0, x1, y1) == 2);
  assert(pixSum3.getNonZeroAverage(x0, y0, x1, y1) == 19/float(2));


  //TEST 9 - non-square matrix - submatrix outside the actual matrix; nothing @ (-100, -100)-(-1,-1)
  x0 = -100;
  y0 = -100;
  x1 = -1;
  y1 = -1;

  assert(pixSum3.getPixelSum(x0, y0, x1, y1) == 0);
  assert(pixSum3.getPixelAverage(x0, y0, x1, y1) == 0);
  assert(pixSum3.getNonZeroCount(x0, y0, x1, y1) == 0);
  assert(pixSum3.getNonZeroAverage(x0, y0, x1, y1) == 0);

  cout << "All tests passed" << endl;
  return 0;
}

