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

    quad1.copyTo(imagemdf(Rect(alturaq,larguraq,alturaq,larguraq)));
    quad2.copyTo(imagemdf(Rect(0,larguraq,alturaq,larguraq)));
    quad3.copyTo(imagemdf(Rect(alturaq,0,alturaq,larguraq)));
    quad4.copyTo(imagemdf(Rect(0,0,alturaq,larguraq)));

    imshow("janela", image);
    imshow("janela_troca",imagemdf);
    waitKey();

    return 0;
}