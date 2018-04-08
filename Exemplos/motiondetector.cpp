#include <iostream>
#include <opencv2/opencv.hpp>
#include <unistd.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes;
  Mat histR, histG, histB;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
  double aux = 0;
  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }
  
  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgG(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgB(histh, histw, CV_8UC3, Scalar(0,0,0));

  Mat hist_antigo(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat hist_detector(histh, histw, CV_8UC3, Scalar(0,0,0));

  cap >> image;
  split (image, planes);
  calcHist(&planes[1], 1, 0, Mat(), hist_antigo, 1,
  &nbins, &histrange, uniform, acummulate);


  while(1){

    cap >> image;
    split (image, planes);
    calcHist(&planes[1], 1, 0, Mat(), hist_antigo, 1,
    &nbins, &histrange, uniform, acummulate);

    cap >> image;
    split (image, planes);
    calcHist(&planes[1], 1, 0, Mat(), hist_detector, 1,
  &nbins, &histrange, uniform, acummulate);

    aux = compareHist(hist_detector,hist_antigo, CV_COMP_CHISQR);
    if(aux > 500){
        cout << "MOVIMENTO DETECTADO" << endl;
    }
    

    merge(planes, image);


    
    
    imshow("image", image);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}