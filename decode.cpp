#include "encode.h"
#include "decode.h"

Decoder::Decoder(Mat *img) {
    this->img = *img;
    Mat stripped = (this->img)(Rect(15, 15, this->img.rows - 30, this->img.cols - 30));
    this->img = stripped;
}

char* Decoder::decodeCorner(int row, int col) {
    int i = row+2, j = col+2;
    while (i < row+16 && j < col+16) {
        int n = i, m = j;

        int vals[4] = {};
        int counts[4] = {};

        int counter = 0;
        while (n < i+4 && m < j+4) {
            Vec3b pixel = this->img.at<Vec3b>(n, m);

            vals[counter] = (pixel.val[0] + pixel.val[1] + pixel.val[2])/3;
            counts[counter] = counts[counter] + 1;

            m++;
            if (m == j+4) {
                n++;
            }

            counter++;
        }

        int maxCount = 0, maxCountIndex = 0;
        for (int k = 0; k < 4; k++) {
            if (counts[k] > maxCount) {
                maxCount = counts[k];
                maxCountIndex = k;
            }
        }

        char c = (char) vals[maxCountIndex];
        //cout << c << endl;;

        j += 6;
        if (j >= col+16) {
            j = col+2;
            i += 6;
        }
    }

    char str[] = " ";
    return str;
}

void Decoder::decode() {
    decodeCorner(0, 0);
    decodeCorner(0, this->img.cols-20);
    decodeCorner(this->img.rows-20, 0);
    decodeCorner(this->img.rows-20, this->img.cols-20);
}