#include "encode.h"

Encoder::Encoder(Mat *img, char *url) {
    this->img = img;
    this->url = url;
}

void Encoder::setAllChannels(int row, int col, int val) {
    (*(this->img)).at<Vec3b>(row, col)[0] = val;
    (*(this->img)).at<Vec3b>(row, col)[1] = val;
    (*(this->img)).at<Vec3b>(row, col)[2] = val;
}

void Encoder::drawCorner(int row, int col) {
    for (int j = col; j < col+20; j++) {
        setAllChannels(row, j, 0);
        setAllChannels(row+1, j, 0);
        
        setAllChannels(row+6, j, 0);
        setAllChannels(row+7, j, 0);

        setAllChannels(row+12, j, 0);
        setAllChannels(row+13, j, 0);

        setAllChannels(row+18, j, 0);
        setAllChannels(row+19, j, 0);
    }

    for (int i = row; i < row+20; i++) {
        setAllChannels(i, col, 0);
        setAllChannels(i, col+1, 0);

        setAllChannels(i, col+6, 0);
        setAllChannels(i, col+7, 0);

        setAllChannels(i, col+12, 0);
        setAllChannels(i, col+13, 0);

        setAllChannels(i, col+18, 0);
        setAllChannels(i, col+19, 0);
    }
}

void Encoder::encodeCorner(int row, int col, int strPos) {
    int counter = 0;
    for (int pos = strPos; pos < strlen(this->url) && pos < strPos+9; pos++) {
        int gridRow = (pos-strPos)/3;
        int gridCol = counter;

        counter++;
        if (counter == 3) {
            counter = 0;
        }

        gridRow = row + gridRow*6 + 2;
        gridCol = col + gridCol*6 + 2;
        
        for (int i = gridRow; i < gridRow+4; i++) {
            for (int j = gridCol; j < gridCol+4; j++) {
                setAllChannels(i, j, (int) this->url[pos]);
            }
        }
    }
}

void Encoder::encode() {
    drawCorner(0, 0);
    drawCorner(0, this->img->cols-20);
    drawCorner(this->img->rows-20, 0);
    drawCorner(this->img->rows-20, this->img->cols-20);

    encodeCorner(0, 0, 0);
    encodeCorner(0, this->img->cols-20, 9);
    encodeCorner(this->img->rows-20, 0, 18);
    encodeCorner(this->img->rows-20, this->img->cols-20, 27);

    Mat *dst;
    dst = this->img;
    Scalar value = Scalar(0, 0, 0);
    copyMakeBorder(*(this->img), *dst, 15, 15, 15, 15, BORDER_CONSTANT, value);
    this->img = dst;
}

void Encoder::show(string window) {
    imshow(window, *(this->img));
}

Mat *Encoder::getImg() {
    return this->img;
}

void Encoder::save() {
    imwrite("./encoded.jpg", *(this->img));
}