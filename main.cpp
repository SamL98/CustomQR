#include "main.h"
#include "encode.h"
#include "decode.h"
#include <typeinfo>

Point2f findCorner(Mat *img, int type) {
    int i = 0, j = 0;
    if (type == 0) {
        while (i < img->rows && j < img->cols) {
            Vec3b color = img->at<Vec3b>(i, j);
            if (color.val[0] <= 10 && color.val[1] <= 10 && color.val[2] <= 10) {
                cout << type << " " << i << " " << j << endl;
                return Point2f(i, j);
            }
            i++; j++;
        }
    } else if (type == 1) {
        j = img->cols-1;
        while (i < img->rows && j > 0) {
            Vec3b color = img->at<int>(i, j);
            cout << color.val[0] << color.val[1] << color.val[2] << endl;
            if (color.val[0] <= 10 && color.val[1] <= 10 && color.val[2] <= 10) {
                cout << type << " " << i << " " << j << endl;
                return Point2f(i, j);
            }
            i++; j--;
        }
    } else if (type == 2) {
        i = img->rows-1;
        while (i > 0 && j < img->cols) {
            Vec3b color = img->at<int>(i, j);
            if (color.val[0] <= 10 && color.val[1] <= 10 && color.val[2] <= 10) {
                cout << type << " " << i << " " << j << endl;
                return Point2f(i, j);
            }
            i--; j++;
        }
    } else {
        i = img->rows-1;
        j = img->cols-1;
        while (i > 0 && j > 0) {
            Vec3b color = img->at<int>(i, j);
            if (color.val[0] <= 10 && color.val[1] <= 10 && color.val[2] <= 10) {
                cout << type << " " << i << " " << j << endl;
                return Point2f(i, j);
            }
            i--; j--;
        }
    }

    return Point2f(0, 0);
}

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

    //namedWindow("Test");
    //encoder.show("Test");

    /*
    VideoCapture camera;
    camera.open(0);
    if (!camera.isOpened()) {
      cerr << "ERROR: Could not access the camera or video!" << endl;
      exit(1);
    }

    camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    namedWindow("Scanner");

    Mat cameraFrame;
    while (1) {
        bool bSuccess = camera.read(cameraFrame);
        if (!bSuccess) {
          std::cerr << "ERROR: Couldn't grab camera frame." << std::endl;
          exit(1);
        }

        imshow("Scanner", cameraFrame);
        
        if (waitKey(20) == 'a') break;
    }
    */

    //Decoder decoder(&cameraFrame);
    //decoder.decode();
    
    Mat test = imread("./test3.jpg");
    resize(test, test, Size(400, 400), 0, 0, CV_INTER_LINEAR);

    threshold(test, test, 50, 255, THRESH_BINARY);

    vector<Point2f> ptsSrc;
    ptsSrc.push_back(Point2f(0, 0));
    ptsSrc.push_back(Point2f(400, 0));
    ptsSrc.push_back(Point2f(0, 400));
    ptsSrc.push_back(Point2f(400, 400));

    vector<Point2f> dstSrc;
    dstSrc.push_back(findCorner(&test, 0));
    dstSrc.push_back(findCorner(&test, 1));
    dstSrc.push_back(findCorner(&test, 2));
    dstSrc.push_back(findCorner(&test, 3));

    cout << dstSrc << endl;
    
    
    Mat homo = findHomography(ptsSrc, dstSrc, 0, 3, noArray());

    //test.convertTo(test, CV_32F);
    //homo.convertTo(homo, CV_32F);
    
    Mat out;
    warpPerspective(test, out, homo, Size(400, 400));

    namedWindow("test");
    imshow("test", test);

    Decoder decoder(&test);
    decoder.decode();

    waitKey(0);
    destroyAllWindows();

    

    //Andy's Last Ditch Effort At Realigning Image
    /*
    Mat inputImg = imread("./Homography.png");
    Mat templateImg = imread("./mcdonalds.jpg");

    Mat inputGray, templateGray;

    cvtColor(inputImg, inputGray, CV_BGR2GRAY);
    cvtColor(templateImg, templateGray, CV_BGR2GRAY);

    Mat warp_matrix = Mat::eye(3, 3, CV_32F);

    // Specify the number of iterations.
    int number_of_iterations = 5000;

    // Specify the threshold of the increment
    // in the correlation coefficient between two iterations
    double termination_eps = 1e-10;

    // Define termination criteria
    TermCriteria criteria (TermCriteria::COUNT+TermCriteria::EPS, 
        number_of_iterations, termination_eps
    );

    findTransformECC(templateGray, 
        inputGray, 
        warp_matrix, 
        MOTION_HOMOGRAPHY, 
        criteria
    );

    Mat inputImgAligned;

    warpPerspective(inputImg, inputImgAligned, warp_matrix, 
        templateImg.size(),INTER_LINEAR + WARP_INVERSE_MAP
    );

    namedWindow("alignmentTest");

    imshow("alignmentTest", inputImgAligned);

    waitKey(0);
    destroyAllWindows();
    */
}