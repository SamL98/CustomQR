#include "/usr/local/include/opencv2/core/core.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cstring>

using namespace std;
using namespace cv;

class Encoder {
public:
    Encoder(Mat *img, char *url);
    void encode();
    void show(string window);
private:
    Mat *img;
    char *url;
    void setAllChannels(int row int col)
    void drawCorner(int row, int col);
    void encodeCorner(int row, int col, int strPos);
};