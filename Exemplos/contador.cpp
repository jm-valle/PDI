#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects;
  
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;

  //realizar a eliminação de objetos nas bordas

  for(int aux = 0; aux < height; aux++){
      floodFill(image, CvPoint(aux,0), 0);
      floodFill(image, CvPoint(aux,255), 0);
      floodFill(image, CvPoint(0,aux), 0);
      floodFill(image, CvPoint(255,aux), 0);
  }

  // busca objetos com buracos presentes
  nobjects=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
		// achou um objeto
		nobjects++;
		p.x=j;
		p.y=i;
		floodFill(image,p,190);
	  }
	}
  }
  //preencher o fundo da imagem com o tom de cinza 80
  floodFill(image, cvPoint(0,0), 80);

  //Contando os buracos
  int num_buracos = 0;
 
  for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
          if(image.at<uchar>(i,j) == 0){
              p.x = j;
              p.y = i;
              floodFill(image, p, 80);

              num_buracos++;

          }
      }
  }
  cout << "Numero de objetos: " << nobjects << endl;
  cout << "Numero de buracos: " << num_buracos << endl;
  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}