#include "encode.h"

Encoder::Encoder(Mat *img, char *url) {
    this->img = img;
    this->url = url;
}

void Encoder::drawCorner(int row, int col) {
    for (int i = row; i < row+18; i++) {
        for (int j = col; j < row+18; j++) {
            
        }
    }
}

void Encoder::encodeCorner(int row, int col, int strPos) {
    for (int i = strPos; i < strlen(this->url) && i < strPos+9l i++) {

    }
}

void Encoder::encode() {
    for (int i = 0; i < strlen(this->url); i++) {
        for (int row = 0; row < 8; row++) {
            int start = i * 16;
            for (int col = start; col < start+8; col++) {
                char c = this->url[i];
                (*(this->img)).at<Vec3b>(row, col)[0] = (int) c;
                (*(this->img)).at<Vec3b>(row, col)[1] = (int) c;
                (*(this->img)).at<Vec3b>(row, col)[2] = (int) c;
            }
        }
    }

    Mat *dst;
    dst = this->img;
    Scalar value = Scalar(0, 0, 0);
    copyMakeBorder(*(this->img), *dst, 20, 20, 20, 20, BORDER_CONSTANT, value);
    this->img = dst;
}

void Encoder::show(string window) {
    imshow(window, *(this->img));
}