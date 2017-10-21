#include "main.h"
#include "encode.h"
#include "decode.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Invalid number of args" << endl;
        return 1;
    }

    char *url = argv[1];

    if (strlen(url) > 36) {
        cout << "URL length greater than 36" << endl;
        return 1;
    }

    Mat img = imread("mcdonalds.jpg");
    resize(img, img, Size(400, 400), 0, 0, CV_INTER_LINEAR);

    Encoder encoder(&img, url);
    encoder.encode();

    namedWindow("Test");
    encoder.show("Test");

    Decoder decoder(encoder.getImg());
    decoder.decode();

    waitKey(0);
    destroyAllWindows();
}