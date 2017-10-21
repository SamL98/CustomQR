#include "encode.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Invalid number of args" << endl;
        return 1;
    }

    char *url = argv[1];

    Mat img = imread("mcdonalds.jpg");
    Encoder encoder(&img, url);
    encoder.encode();

    namedWindow("Test");
    encoder.show("Test");
    waitKey(0);
    destroyAllWindows();
}