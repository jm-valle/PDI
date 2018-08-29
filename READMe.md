# PROCESSAMENTO DIGITAL DE IMAGENS - UFRN
João Marcos Araújo do Valle <jmarcos.araujo96@gmail.com>
<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->


- [Unidade 1](#unidade-1)
  - [1. Manipulando Pixels em Uma imagem](#1-manipulando-pixels-em-uma-imagem)
    - [1.1. Efeito Negativo](#11-efeito-negativo)
      - [Código](#c%C3%B3digo)
      - [Resultado](#resultado)
    - [1.2. Mudança de Quadrantes](#12-mudan%C3%A7a-de-quadrantes)
      - [Código](#c%C3%B3digo-1)
      - [Resultado](#resultado-1)
  - [2.Preenchendo Regiões](#2preenchendo-regi%C3%B5es)
    - [2.1. Algoritmo Contador](#21-algoritmo-contador)
      - [Código](#c%C3%B3digo-2)
      - [Resultado](#resultado-2)
  - [3. Histogramas](#3-histogramas)
    - [3.1 Equalizador de Histogramas](#31-equalizador-de-histogramas)
      - [Código](#c%C3%B3digo-3)
      - [Resultado](#resultado-3)
    - [Detector de Movimento](#detector-de-movimento)
      - [Código](#c%C3%B3digo-4)
      - [Resultado](#resultado-4)
  - [Filtros Espaciais I](#filtros-espaciais-i)
    - [Laplaciano do Gaussiano](#laplaciano-do-gaussiano)
      - [Código](#c%C3%B3digo-5)
      - [Resultado](#resultado-5)
- [Unidade 2](#unidade-2)
  - [7. Filtragem no Domínio da Frequência](#7-filtragem-no-dom%C3%ADnio-da-frequ%C3%AAncia)
    - [Filtro Homomórfico](#filtro-homom%C3%B3rfico)
      - [Código](#c%C3%B3digo-6)
      - [Resultado](#resultado-6)
  - [8. Detecção de Bordas Com o Algoritmo de Canny](#8-detec%C3%A7%C3%A3o-de-bordas-com-o-algoritmo-de-canny)
    - [Pontilhismo utilizando o Algoritmo de Canny](#pontilhismo-utilizando-o-algoritmo-de-canny)
      - [Código](#c%C3%B3digo-7)
      - [Resultado](#resultado-7)
  - [9. Quantização vetorial com k-means](#9-quantiza%C3%A7%C3%A3o-vetorial-com-k-means)
    - [Algoritmo do k-means](#algoritmo-do-k-means)
      - [Código](#c%C3%B3digo-8)
      - [Resultado](#resultado-8)
  - [Projeto da Terceira Unidade - Matrizes de Co-ocorrência](#projeto-da-terceira-unidade---matrizes-de-co-ocorr%C3%AAncia)

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
##### Resultado

[Saída Regions.cpp](Exemplos/regions.png)


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

[Saída trocaderegioes.cpp](Exemplos/trocaderegioes.png)


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
##### Resultado

[Saída contador.cpp](Exemplos/contador.png)

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
##### Resultado

[Saída histograma.cpp](Exemplos/histograma.png)


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
##### Resultado

[Saída motiondetector.cpp](Exemplos/motiondetector.png)


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
##### Resultado

[Saída laplgauss.cpp](Exemplos/laplgauss.png)


## Unidade 2
### 7. Filtragem no Domínio da Frequência
#### Filtro Homomórfico

##### Código
```c++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define RADIUS 20

using namespace cv;
using namespace std;

// troca os quadrantes da imagem da DFT
void deslocaDFT(Mat& image ){
  Mat tmp, A, B, C, D;

  // se a imagem tiver tamanho impar, recorta a regiao para
  // evitar cópias de tamanho desigual
  image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
  int cx = image.cols/2;
  int cy = image.rows/2;

  // reorganiza os quadrantes da transformada
  // A B   ->  D C
  // C D       B A
  A = image(Rect(0, 0, cx, cy));
  B = image(Rect(cx, 0, cx, cy));
  C = image(Rect(0, cy, cx, cy));
  D = image(Rect(cx, cy, cx, cy));

  // A <-> D
  A.copyTo(tmp);  D.copyTo(A);  tmp.copyTo(D);

  // C <-> B
  C.copyTo(tmp);  B.copyTo(C);  tmp.copyTo(B);
}

int main(int , char**){
  VideoCapture cap;
  Mat imaginaryInput, complexImage, multsp;
  Mat padded, filter, mag;
  Mat image, imagegray, tmp;
  Mat_<float> realInput, zeros;
  vector<Mat> planos;



  char *jan_track = "trackbar";
  //Valores iniciais do filtro homomórfico
  float d;
  //Variáveis de iluminância e reflectância
  int yH, yH_max = 25, yL, yL_max = 25;
  //Variáveis da frequencia de corte 
  int d0 = 5, d0_max = 60;
  //Variáveis da curva do filtro
  int c, c_max = 20;
  //Janela para as trackbars
  namedWindow(jan_track, CV_WINDOW_AUTOSIZE);
  //Cria as trackbars para ajustar os valores do filtro homomórfico
  createTrackbar("Gama H", jan_track, &yH, yH_max);
  createTrackbar("Gama L", jan_track, &yL, yL_max);
  createTrackbar("D0", jan_track, &d0, d0_max);
  createTrackbar("c", jan_track, &c, c_max);



  // habilita/desabilita ruido
  int noise=0;
  // frequencia do ruido
  int freq=10;
  // ganho inicial do ruido
  float gain=1;

  // valor do ruido
  float mean;

  // guarda tecla capturada
  char key;

  // valores ideais dos tamanhos da imagem
  // para calculo da DFT
  int dft_M, dft_N;

  // abre a câmera default
  cap.open(0);
  if(!cap.isOpened())
    return -1;

  // captura uma imagem para recuperar as
  // informacoes de gravação
  cap >> image;

  // identifica os tamanhos otimos para
  // calculo do FFT
  dft_M = getOptimalDFTSize(image.rows);
  dft_N = getOptimalDFTSize(image.cols);

  // realiza o padding da imagem
  copyMakeBorder(image, padded, 0,
                 dft_M - image.rows, 0,
                 dft_N - image.cols,
                 BORDER_CONSTANT, Scalar::all(0));

  // parte imaginaria da matriz complexa (preenchida com zeros)
  zeros = Mat_<float>::zeros(padded.size());

  // prepara a matriz complexa para ser preenchida
  complexImage = Mat(padded.size(), CV_32FC2, Scalar(0));

  // a função de transferência (filtro frequencial) deve ter o
  // mesmo tamanho e tipo da matriz complexa
  filter = complexImage.clone();

  // cria uma matriz temporária para criar as componentes real
  // e imaginaria do filtro ideal
  tmp = Mat(dft_M, dft_N, CV_32F);

  // cria a matriz com as componentes do filtro e junta
  // ambas em uma matriz multicanal complexa
  Mat comps[]= {tmp, tmp};
  merge(comps, 2, filter);

  for(;;){
    cap >> image;
    cvtColor(image, imagegray, CV_BGR2GRAY);
    imshow("original", imagegray);

    //Cálculo do filtro homomórfico, 
    for(int i=0; i<dft_M; i++){
      for(int j=0; j<dft_N; j++){
        //Calcula-se o D(i,j) = [(i − M/2)² + (j − N/2)²]^0.5
        d = pow(pow(i - dft_M/2, 2) + pow(j - dft_N/2, 2), 0.5);
        //Depois calcula-se o valor de H para cada pixel
        tmp.at<float> (i,j) = (yH - yL)*(1 - exp(-1*c*(pow(d,2)/pow(d0,2)))) + yL;
      }
    }
    comps[0] = tmp;
    comps[1] = tmp;
    merge(comps,2,filter);

    // realiza o padding da imagem
    copyMakeBorder(imagegray, padded, 0,
                   dft_M - image.rows, 0,
                   dft_N - image.cols,
                   BORDER_CONSTANT, Scalar::all(0));

    // limpa o array de matrizes que vao compor a
    // imagem complexa
    planos.clear();
    // cria a compoente real
    realInput = Mat_<float>(padded);
    // insere as duas componentes no array de matrizes
    planos.push_back(realInput);
    planos.push_back(zeros);

    // combina o array de matrizes em uma unica
    // componente complexa
    merge(planos, complexImage);

    //Logaritmo necessario para realizar a transformada
    //Realiza-se a soma +1 ao logaritmo caso o valor do pixel
    //Seja 0, o que acarretaria em um erro, como 1 é o elementro
    //neutro do logaritmo, soma-se 1
    for(int i = 0; i < dft_M; i++){
      for(int j = 0; j < dft_N; j++){
        complexImage.at<char>(i,j) = log(complexImage.at<char>(i,j)+1);
      }
    }

    // calcula o dft
    dft(complexImage, complexImage);

    // realiza a troca de quadrantes
    deslocaDFT(complexImage);

    // aplica o filtro frequencial
    mulSpectrums(complexImage,filter,complexImage,0);

    // limpa o array de planos
    planos.clear();
    // separa as partes real e imaginaria para modifica-las
    split(complexImage, planos);

    // usa o valor medio do espectro para dosar o ruido
    mean = abs(planos[0].at<float> (dft_M/2,dft_N/2));

    // insere ruido coerente, se habilitado
    if(noise){
      // F(u,v) recebe ganho proporcional a F(0,0)
      planos[0].at<float>(dft_M/2 +freq, dft_N/2 +freq) +=
        gain*mean;

      planos[1].at<float>(dft_M/2 +freq, dft_N/2 +freq) +=
        gain*mean;

      // F*(-u,-v) = F(u,v)
      planos[0].at<float>(dft_M/2 -freq, dft_N/2 -freq) =
        planos[0].at<float>(dft_M/2 +freq, dft_N/2 +freq);

      planos[1].at<float>(dft_M/2 -freq, dft_N/2 -freq) =
        -planos[1].at<float>(dft_M/2 +freq, dft_N/2 +freq);

    }

    // recompoe os planos em uma unica matriz complexa
    merge(planos, complexImage);

    // troca novamente os quadrantes
    deslocaDFT(complexImage);

	  cout << complexImage.size().height << endl;
    // calcula a DFT inversa
    idft(complexImage, complexImage);

    //Para obtenção da imagem após a filtragem, é necessario aplicar
    //a exponencial a imagem filtrada
    for(int i = 0; i < dft_M; i++){
      for(int j = 0; j < dft_N; j++){
        complexImage.at<char>(i,j) = exp(complexImage.at<char>(i,j));
      }
    }

    // limpa o array de planos
    planos.clear();

    // separa as partes real e imaginaria da
    // imagem filtrada
    split(complexImage, planos);

    // normaliza a parte real para exibicao
    normalize(planos[0], planos[0], 0, 1, CV_MINMAX);
    imshow("filtrada", planos[0]);

    key = (char) waitKey(10);
    if( key == 27 ) break; // esc pressed!
    switch(key){
      // aumenta a frequencia do ruido
    case 'q':
      freq=freq+1;
      if(freq > dft_M/2-1)
        freq = dft_M/2-1;
      break;
      // diminui a frequencia do ruido
    case 'a':
      freq=freq-1;
      if(freq < 1)
        freq = 1;
      break;
      // amplifica o ruido
    case 'x':
      gain += 0.1;
      break;
      // atenua o ruido
    case 'z':
      gain -= 0.1;
      if(gain < 0)
        gain=0;
      break;
      // insere/remove ruido
    case 'e':
      noise=!noise;
      break;
    }
  }
  return 0;
}
```
##### Resultado

[Saída homomorfico.cpp](Exemplos/homomorfico.png)

### 8. Detecção de Bordas Com o Algoritmo de Canny
#### Pontilhismo utilizando o Algoritmo de Canny

##### Código
```c++
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

/*
Para este código utilizei o algoritmo pontilhismo.cpp e apenas
adicionei o algoritmo de Canny ao final do mesmo
*/

#define STEP 5
#define JITTER 3
#define RAIO 3

int main(int argc, char** argv){
    vector<int> yrange;
    vector<int> xrange;

    Mat image, frame, points, image_canny, points_canny;

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
        //Loop utilizado para desenhar a imagem pontilhista
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(image_canny.at<uchar>(i,j)>0){
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
    }
    imwrite("pontilhismo_canny.jpg",points);
    waitKey();

  return 0;
}
```

##### Resultado

[Saída cannypoints.cpp](Exemplos/cannypoints.png)

### 9. Quantização vetorial com k-means

#### Algoritmo do k-means

##### Código
```c++
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <string>


using namespace cv;
using namespace std;
/* Para este código, foi modificado apenas o numero de rodadas
e a flag do kmeans, que foi definida como KMEANS_RANDOM_CENTERS
Além disso o código foi colocado dentro de um loop, pois o 
ao executar o código fora do loop, o resultado foi sempre o mesmo
o que indica que o OpenCV provavelmente está usando a mesma
Seed para a criação da variável aleatória
*/

int main( int argc, char** argv ){
  int nClusters = 6;
  Mat rotulos;
  int nRodadas = 1;
  Mat centros;

  if(argc!=3){
	exit(0);
  }
  
  for(int i = 0; i < 10; i++){
  Mat img = imread( argv[1], CV_LOAD_IMAGE_COLOR);
  Mat samples(img.rows * img.cols, 3, CV_32F);

  for( int y = 0; y < img.rows; y++ ){
    for( int x = 0; x < img.cols; x++ ){
      for( int z = 0; z < 3; z++){
        samples.at<float>(y + x*img.rows, z) = img.at<Vec3b>(y,x)[z];
	  }
	}
  }
  
  kmeans(samples,
		 nClusters,
		 rotulos,
		 TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10, 0.0001),
		 nRodadas,
		 KMEANS_RANDOM_CENTERS,
		 centros );


  Mat rotulada( img.size(), img.type() );
  for( int y = 0; y < img.rows; y++ ){
    for( int x = 0; x < img.cols; x++ ){ 
	  int indice = rotulos.at<int>(y + x*img.rows,0);
	  rotulada.at<Vec3b>(y,x)[0] = (uchar) centros.at<float>(indice, 0);
	  rotulada.at<Vec3b>(y,x)[1] = (uchar) centros.at<float>(indice, 1);
	  rotulada.at<Vec3b>(y,x)[2] = (uchar) centros.at<float>(indice, 2);
	}
  }
  //imshow( "clustered image", rotulada );
  string auxiliar = argv[2];
  string nomeimagem = auxiliar + to_string(i) + ".jpg";
   char *nomeimagem1 = &nomeimagem[0u];
  imwrite(nomeimagem1, rotulada);
  }
  
}
```
##### Resultado

Os resultados observados diferem pela inicialização aleatória do
algoritmo k-means. Como é realizada apenas uma rodada, os clusters
não irão sempre converger para o mesmo resultado, por causa da 
inicialização aleatória


[Imagem Original](Exemplos/gorillaz.jpg)

[Imagens Após a execução do K-means](Exemplos/resultadokmeans.png)


### Projeto da Terceira Unidade - Matrizes de Co-ocorrência

#### Descrição do projeto

O projeto da terceira unidade consiste em uma aplicação JavaScript que utiliza a biblioteca OpenJS para o cálculo de alguns descritores de Haralick para matrizes de co-ocorrência.

---

Acessar página do [Projeto](TrabFinal/doc_terc_unid.md)

