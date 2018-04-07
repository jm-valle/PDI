#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
    Mat image;
    Vec3b val;

    image = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);
}