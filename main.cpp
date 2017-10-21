#include "encode.h"

int main(int argc, char **argv) {
    Mat img = imread("mcdonalds.jpg");
    Encoder encoder(&img);
    encoder.encode();

    namedWindow("Test");
    encoder.show("Test");
    waitKey(0);
    destroyAllWindows();
}