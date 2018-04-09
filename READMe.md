# PROCESSAMENTO DIGITAL DE IMAGENS - UFRN
João Marcos Araújo do Valle <jmarcos.araujo96@gmail.com>
<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->


- [Unidade 1](#unidade-1)
  - [1. Manipulando Pixels em Uma imagem](#1-manipulando-pixels-em-uma-imagem)
    - [1.1. Efeito Negativo](#11-efeito-negativo)
      - [Código](#c%C3%B3digo)
    - [1.2. Mudança de Quadrantes](#12-mudan%C3%A7a-de-quadrantes)
      - [Código](#c%C3%B3digo-1)
      - [Resultado](#resultado)
  - [2.Preenchendo Regiões](#2preenchendo-regi%C3%B5es)
    - [2.1. Algoritmo Contador](#21-algoritmo-contador)
      - [Código](#c%C3%B3digo-2)
  - [3. Histogramas](#3-histogramas)
    - [3.1 Equalizador de Histogramas](#31-equalizador-de-histogramas)
      - [Código](#c%C3%B3digo-3)
    - [Detector de Movimento](#detector-de-movimento)
      - [Código](#c%C3%B3digo-4)
  - [Filtros Espaciais I](#filtros-espaciais-i)
    - [Laplaciano do Gaussiano](#laplaciano-do-gaussiano)
      - [Código](#c%C3%B3digo-5)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


## Unidade 1
### 1. Manipulando Pixels em Uma imagem
#### 1.1. Efeito Negativo

##### Código

```c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
    Mat image;
    Vec3b val;

    Size tamanho;

    int p1[2], p2[2]; //Ponto 1 e ponto 2, respectivamente

    int altura, largura; 

    image = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);
    if(!image.data){
        cout << "Não foi possível abrir a imagem" << endl;
        exit(1);
    }
    namedWindow("janela", WINDOW_AUTOSIZE);
    namedWindow("janela_negativo", WINDOW_AUTOSIZE);

    imshow("janela", image);
    tamanho = image.size();
    altura = tamanho.height;
    largura = tamanho.width; 
    
    //Inserção das coordenadas do primeiro ponto
    cout << "Insira as coordenadas do ponto 1 (X, Y): ";
    cin >> p1[0] >> p1[1];
    
    //Caso os valores de P1 inseridos sejam inválidos, fechamos o programa
    if(p1[0] < 0 || p1[0] > altura || p1[1] < 0 || p1[1] > largura){
        cout << "Valores de ponto incorretos, encerrando programa...";
        exit(1);

    }
    //Inserção das coordenadas do segundo ponto
    cout << "Insira as coordenadas do ponto 2 (X, Y): ";
    cin >> p2[0] >> p2[1];

    //Caso os valores inseridos sejam inválidos, fechamos o programa
    if(p2[0] < 0 || p2[0] > altura || p2[1] < 0 || p2[1] > largura){
        cout << "Valores de ponto incorretos, encerrando programa...";
        exit(1);
    }

    for(int i = p1[0]; i < p2[0]; i++){
        for(int j = p1[1]; j < p2[1]; j++){
            image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
        }
    }

    imshow("janela_negativo", image);
    waitKey();


    return 0;

}
```
#### 1.2. Mudança de Quadrantes

##### Código

```c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
    Mat image, imagemdf;
    Mat quad1, quad2, quad3, quad4;

    Size tamanho;

    int altura, largura;
    int alturaq, larguraq;

    image = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);

    if(!image.data){
        cout << "Não foi possível abrir a imagem" << endl;
        exit(1);
    }

    namedWindow("janela", WINDOW_AUTOSIZE);
    namedWindow("janela_troca", WINDOW_AUTOSIZE);

    imshow("janela", image);
    tamanho = image.size();
    altura = tamanho.height;
    largura = tamanho.width;

    image.copyTo(imagemdf);

    alturaq = altura/2;
    larguraq = largura/2;

    quad1 = image(Rect(0,0,alturaq,larguraq)); //Quadrante 1 original 
    quad2 = image(Rect(alturaq,0,alturaq,larguraq)); //Quadrante 2 original
    quad3 = image(Rect(0,larguraq,alturaq,larguraq)); //Quadrante 3 original
    quad4 = image(Rect(alturaq,larguraq,alturaq,larguraq)); //Quadrante 4 original
    
    //Aqui, copiamos os quadrantes originais para as posições desejadas
    quad1.copyTo(imagemdf(Rect(alturaq,larguraq,alturaq,larguraq)));
    quad2.copyTo(imagemdf(Rect(0,larguraq,alturaq,larguraq)));
    quad3.copyTo(imagemdf(Rect(alturaq,0,alturaq,larguraq)));
    quad4.copyTo(imagemdf(Rect(0,0,alturaq,larguraq)));

    imshow("janela", image);
    imshow("janela_troca",imagemdf);
    waitKey();

    return 0;
}
```

##### Resultado


### 2.Preenchendo Regiões 
#### 2.1. Algoritmo Contador

##### Código

```c++
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
 /*
 O Loop Funciona da seguinte maneira: depois que o fundo da imagem
 foi preenchido com tons de cinza 80 e as bolhas foram preenchidas
 com o tom de cinza 190, os conjuntos de pixels restantes que forem
 em tom de cinza 0 são os buracos, então a cada pixel com tom 0 que
 é encontrado, conta-se como um buraco, e realiza um floodFill para
 que não seja contado de novo
 */
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
```
### 3. Histogramas
#### 3.1 Equalizador de Histogramas

##### Código

```c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, image_original;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes;
  Mat histR, histG, histB;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

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

  while(1){
    cap >> image;
    split (image, planes);
    //Este merge é feito para termos uma janela com a imagem original
    merge(planes, image_original);
    //Equalização das capturas
    equalizeHist(planes[0], planes[0]);
    equalizeHist(planes[1], planes[1]);
    equalizeHist(planes[2], planes[2]);

    merge(planes, image);


    calcHist(&planes[0], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[1], 1, 0, Mat(), histG, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[2], 1, 0, Mat(), histB, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
    normalize(histG, histG, 0, histImgG.rows, NORM_MINMAX, -1, Mat());
    normalize(histB, histB, 0, histImgB.rows, NORM_MINMAX, -1, Mat());

    histImgR.setTo(Scalar(0));
    histImgG.setTo(Scalar(0));
    histImgB.setTo(Scalar(0));
    
    for(int i=0; i<nbins; i++){
      line(histImgR,
           Point(i, histh),
           Point(i, histh-cvRound(histR.at<float>(i))),
           Scalar(0, 0, 255), 1, 8, 0);
      line(histImgG,
           Point(i, histh),
           Point(i, histh-cvRound(histG.at<float>(i))),
           Scalar(0, 255, 0), 1, 8, 0);
      line(histImgB,
           Point(i, histh),
           Point(i, histh-cvRound(histB.at<float>(i))),
           Scalar(255, 0, 0), 1, 8, 0);
    }
    histImgR.copyTo(image(Rect(0, 0       ,nbins, histh)));
    histImgG.copyTo(image(Rect(0, histh   ,nbins, histh)));
    histImgB.copyTo(image(Rect(0, 2*histh ,nbins, histh)));
    imshow("image", image);
    imshow("iamgem original", image_original);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
``` 

#### Detector de Movimento

##### Código
```c++
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
```

### Filtros Espaciais I

#### Laplaciano do Gaussiano

##### Código
```c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void printmask(Mat &m){
  for(int i=0; i<m.size().height; i++){
    for(int j=0; j<m.size().width; j++){
      cout << m.at<float>(i,j) << ",";
    }
    cout << endl;
  }
}

void menu(){
  cout << "\npressione a tecla para ativar o filtro: \n"
	"a - calcular modulo\n"
    "m - media\n"
    "g - gauss\n"
    "v - vertical\n"
	"h - horizontal\n"
    "l - laplaciano\n"
    "n - laplaciano do gaussiano"
	"esc - sair\n";
}

int main(int argvc, char** argv){
  VideoCapture video;
  float media[] = {1,1,1,
				   1,1,1,
				   1,1,1};
  float gauss[] = {1,2,1,
				   2,4,2,
				   1,2,1};
  float horizontal[]={-1,0,1,
					  -2,0,2,
					  -1,0,1};
  float vertical[]={-1,-2,-1,
					0,0,0,
					1,2,1};
  float laplacian[]={0,-1,0,
					 -1,4,-1,
					 0,-1,0};
    //Máscara do laplaciano do gaussiano
  float laplgauss[]=  {0,  0,  -1,  0,  0,
                       0, -1,  -2, -1,  0,
                       -1, -2,  16, -2, -1,
                       0, -1,  -2, -1,  0,
                       0,  0,  -1,  0,  0};
                
  Mat cap, frame, frame32f, frameFiltered;
  Mat mask(3,3,CV_32F), mask1;
  Mat result, result1;
  double width, height, min, max;
  int absolut;
  char key;
  
  video.open(0); 
  if(!video.isOpened()) 
    return -1;
  width=video.get(CV_CAP_PROP_FRAME_WIDTH);
  height=video.get(CV_CAP_PROP_FRAME_HEIGHT);
  std::cout << "largura=" << width << "\n";;
  std::cout << "altura =" << height<< "\n";;

  namedWindow("filtroespacial",1);

  mask = Mat(3, 3, CV_32F, media); 
  scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
  swap(mask, mask1);
  absolut=1; // calcs abs of the image

  menu();
  for(;;){
    video >> cap; 
    cvtColor(cap, frame, CV_BGR2GRAY);
    flip(frame, frame, 1);
    imshow("original", frame);
    frame.convertTo(frame32f, CV_32F);
    filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
    if(absolut){
      frameFiltered=abs(frameFiltered);
    }
    frameFiltered.convertTo(result, CV_8U);
    imshow("filtroespacial", result);
    key = (char) waitKey(10);
    if( key == 27 ) break; // esc pressed!
    switch(key){
    case 'a':
	  menu();
      absolut=!absolut;
      break;
    case 'm':
	  menu();
      mask = Mat(3, 3, CV_32F, media);
      scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
      mask = mask1;
      printmask(mask);
      break;
    case 'g':
	  menu();
      mask = Mat(3, 3, CV_32F, gauss);
      scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
      mask = mask1;
      printmask(mask);
      break;
    case 'h':
	  menu();
      mask = Mat(3, 3, CV_32F, horizontal);
      printmask(mask);
      break;
    case 'v':
	  menu();
      mask = Mat(3, 3, CV_32F, vertical);
      printmask(mask);
      break;
    case 'l':
	  menu();
      mask = Mat(3, 3, CV_32F, laplacian);
      printmask(mask);
      break;
    //Implementação do laplaciano do gaussiano
    case 'n':
        menu();
        mask = Mat(5, 5, CV_32F, laplgauss);
        printmask(mask);
        break;
    default:
      break;
    }
  }
  return 0;
}
```