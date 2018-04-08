<<<<<<< HEAD
<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
(https://github.com/thlorenz/doctoc)*

  - [PROCESSAMENTO DIGITAL DE IMAGENS - UFRN](#processamento-digital-de-imagens---ufrn)
- [PROCESSAMENTO DIGITAL DE IMAGENS - UFRN](#processamento-digital-de-imagens---ufrn-1)
  - [Unidade 1](#unidade-1)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## PROCESSAMENTO DIGITAL DE IMAGENS - UFRN
=======

João Marcos Araújo do Valle



## Unidade 1
### 2. Manipulando Pixels em Uma imagem
#### 2.1. Efeito Negativo

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




