#include "/usr/local/include/opencv2/core/core.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

class Encoder {
public:
    Encoder(Mat *img);
    void encode();
    void show(string window);
private:
    Mat *img;
};