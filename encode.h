#include "main.h"

class Encoder {
public:
    Encoder(Mat *img, char *url);
    void encode();
    void show(string window);
    Mat *getImg();
    void save();
private:
    Mat *img;
    char *url;
    void setAllChannels(int row, int col, int val);
    void drawCorner(int row, int col);
    void encodeCorner(int row, int col, int strPos);
};