#include "encode.h"

Encoder::Encoder(Mat *img) {
    this->img = img;
}

void Encoder::encode() {
    Mat *dst;
    dst = this->img;
    Scalar value = Scalar(0, 0, 0);
    copyMakeBorder(*(this->img), *dst, 20, 20, 20, 20, BORDER_CONSTANT, value);
    this->img = dst;
}

void Encoder::show(string window) {
    imshow(window, *(this->img));
}