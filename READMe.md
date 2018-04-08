# PROCESSAMENTO DIGITAL DE IMAGENS - UFRN
João Marcos Araújo do Valle <jmarcos.araujo96@gmail.com>
<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->


- [Unidade 1](#unidade-1)
  - [1. Manipulando Pixels em Uma imagem](#1-manipulando-pixels-em-uma-imagem)
    - [1.1. Efeito Negativo](#11-efeito-negativo)
      - [Código](#c%C3%B3digo)
  - [2.Preenchendo Regiões](#2preenchendo-regi%C3%B5es)
    - [2.1. Algoritmo Contador](#21-algoritmo-contador)
      - [Código](#c%C3%B3digo-1)

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


