#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define STEP 5
#define JITTER 3
#define RAIO 3

int main(int argc, char** argv){
    vector<int> yrange;
    vector<int> xrange;

    Mat image, frame, points;

    int width, height, gray;
    int x, y;
    
    image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

    srand(time(0));
    
    if(!image.data){
        cout << "nao abriu" << argv[1] << endl;
        cout << argv[0] << " imagem.jpg";
        exit(0);
    }

    width=image.size().width;
    height=image.size().height;

    xrange.resize(height/STEP);
    yrange.resize(width/STEP);
    
    iota(xrange.begin(), xrange.end(), 0); 
    iota(yrange.begin(), yrange.end(), 0);

    for(uint i=0; i<xrange.size(); i++){
        xrange[i]= xrange[i]*STEP+STEP/2;
    }

    for(uint i=0; i<yrange.size(); i++){
        yrange[i]= yrange[i]*STEP+STEP/2;
    }

    points = Mat(height, width, CV_8U, Scalar(255));

    random_shuffle(xrange.begin(), xrange.end());
    
    for(auto i : xrange){
        random_shuffle(yrange.begin(), yrange.end());
        for(auto j : yrange){
        x = i+rand()%(2*JITTER)-JITTER+1;
        y = j+rand()%(2*JITTER)-JITTER+1;
        gray = image.at<uchar>(x,y);
        circle(points,
                cv::Point(y,x),
                RAIO,
                CV_RGB(gray,gray,gray),
                -1,
                CV_AA);
        }
    }
    imwrite("pontos.jpg", points);
        
    //Agora criamos a imagem do pontilhismo utilizando Canny

    //primeiro define-se a quantidade de vezes que o algoritmo
    //será executado
    //Vale salientar que cada vez que o passo aumenta, o raio
    //dos circulos será menor, criando assim uma imagem com
    //melhor qualidade
    int qnt_exec = 5;

    for(int l = 0; l < qnt_exec; l++){
        int raio = 5 - l;
        int limiar_t2 = 15*l;
        int limiar_t1 = limiar_t2 * 3;

        Canny(image, image_canny, limiar_t2, limiar_t1);

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                gray = image.at<uchar>(i,j);
                circle(points,
                cv::Point(j,i),
                raio,
                CV_RGB(gray,gray,gray),
                -1,
                CV_AA);
            }
        }
    }
    

  return 0;
}