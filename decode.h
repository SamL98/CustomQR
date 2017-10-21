#include "main.h"

class Decoder {
public:
    Decoder(Mat *img);
    void decode();
private:
    Mat img;
    char* decodeCorner(int row, int col);
};