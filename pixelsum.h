class PixelSum{
  private:
    int* globalMat;
    int* sum;
    void normaliseParameters(int &x0, int &y0, int &x1, int &y1) const;
  public:
    int ROWS;
    int COLUMNS;

    PixelSum(const unsigned char* buffer, int xWidth, int yHeight);
    ~PixelSum (void);
    PixelSum (const PixelSum&);
    PixelSum& operator=(const PixelSum&);
    unsigned int getPixelSum (int x0, int y0, int x1, int y1) const;
    double getPixelAverage (int x0, int y0, int x1, int y1) const;
    int  getNonZeroCount (int x0, int y0, int x1, int y1) const;
    double getNonZeroAverage (int x0, int y0, int x1, int y1) const;
};
