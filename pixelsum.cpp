#include <iostream>
#include <cmath>
#include <cstdlib>
#include "pixelsum.h"
using namespace std;

PixelSum::PixelSum(const unsigned char* buffer, int xWidth, int yHeight){
    ROWS = yHeight;
    COLUMNS = xWidth;

    //allocate memory
    globalMat = new int[ROWS*COLUMNS];
    sum = new int[ROWS*COLUMNS];

    //make a copy of the buffer
    for (int i=0; i<ROWS * COLUMNS; i++){
      globalMat[i] = buffer[i];
    }

    //initialise the sum array to 0s
    for (int i=0; i < ROWS * COLUMNS; i++)
        sum[i] = 0;

    //pre-process input buffer. sum array stores sums of elements
    sum[0] = globalMat[0];

    //pre-process row
    for (int j=1; j < ROWS; j++){
        sum[0 + j * COLUMNS] = globalMat[0 + j * COLUMNS] + sum[0 + (j-1) * COLUMNS];
    }

    //pre-process column
    for (int i=1; i < COLUMNS; i++){
        sum[i + 0 * COLUMNS] = globalMat[i + 0 * COLUMNS] + sum[(i-1) + 0 * COLUMNS];
    }

    //pre-process input buffer
    for (int j=1; j < ROWS; j++){
        for (int i=1; i < COLUMNS; i++){
            sum[i + j * COLUMNS] = globalMat[i + j * COLUMNS] + \
                sum[(i-1) + j * COLUMNS] + \
                sum[i + (j-1) * COLUMNS] - \
                sum[(i-1) + (j-1) * COLUMNS];
        }
    }
}


PixelSum::PixelSum(const PixelSum &oldPixelSum){
    //copy constructor
    
    ROWS = oldPixelSum.ROWS;
    COLUMNS = oldPixelSum.COLUMNS;

    globalMat = new int[ROWS*COLUMNS];
    sum = new int[ROWS*COLUMNS];
    for (int i =0; i<ROWS*COLUMNS; i++){
        globalMat[i] = oldPixelSum.globalMat[i];
        sum[i] = oldPixelSum.sum[i];
    }
}

PixelSum& PixelSum::operator=(const PixelSum &oldPixelSum){
    //copy data

    ROWS = oldPixelSum.ROWS;
    COLUMNS = oldPixelSum.COLUMNS;

    globalMat = new int[ROWS*COLUMNS];
    sum = new int[ROWS*COLUMNS];
    for (int i =0; i<ROWS*COLUMNS; i++){
        globalMat[i] = oldPixelSum.globalMat[i];
        sum[i] = oldPixelSum.sum[i];
    }

    return *this;
}

void PixelSum::normaliseParameters(int &x0, int &y0, int &x1, int &y1) const{
    //normalise the x0, y0, x1, y1 parameters

    if (x0 < 0) x0 = 0;
    if (x0 > COLUMNS-1) x0 = COLUMNS-1;
    if (y0 < 0) y0 = 0;
    if (y0 > ROWS-1) y0 = ROWS-1;

    if (x1 < 0) x1 = 0;
    if (x1 > COLUMNS-1) x1 = COLUMNS-1;
    if (y1 < 0) y1 = 0;
    if (y1 > ROWS-1) y1 = ROWS-1;

    if (x0 > x1){int temp=x0; x0=x1; x1=temp;}
    if (y0 > y1){int temp=y0; y0=y1; y1=temp;}
}


int PixelSum::getNonZeroCount(int x0, int y0, int x1, int y1) const{
    normaliseParameters(x0, y0, x1, y1);

    int counter = 0;

    //no faster than O(n^2) way to count the non-zero element
    for (int row = y0; row <= y1; row++)
        for (int column=x0; column <= x1; column++)
            if (globalMat[column + row * COLUMNS] != 0)
                counter++;

    return counter;
}

double PixelSum::getNonZeroAverage(int x0, int y0, int x1, int y1) const{
    //return 0 instead of -nan
    
    int nonZeros = getNonZeroCount(x0, y0, x1, y1);
    if (nonZeros != 0)
        return getPixelSum(x0, y0, x1, y1) / (float)getNonZeroCount(x0, y0, x1, y1);
    else
        return 0;
}

unsigned int PixelSum::getPixelSum(int x0, int y0, int x1, int y1) const{
    normaliseParameters(x0, y0, x1, y1);

    //total = sum[r][s] - sum[r][q-1] - sum[p-1][s] + sum[p-1][q-1]

    int total = sum[x1 + y1 * COLUMNS];

    if (y0 - 1 >= 0)
        total -= sum[x1 + (y0 - 1) * COLUMNS];

    if (x0 - 1 >= 0)
        total -= sum[(x0 - 1) + y1 * COLUMNS];

    if (x0 - 1 >= 0 && y0 - 1 >= 0)
        total += sum[(x0 - 1) + (y0 - 1) * COLUMNS];

    return total;
}

double PixelSum::getPixelAverage(int x0, int y0, int x1, int y1) const{
    //number of pixels is a distance between the two points

    int numberOfPixels = (std::abs(x0-x1)+1) * (std::abs(y0-y1)+1);
    return getPixelSum(x0, y0, x1, y1) / (float)numberOfPixels;
}

PixelSum::~PixelSum(){
    delete globalMat;
    delete sum;
}

