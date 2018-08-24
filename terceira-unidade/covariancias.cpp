#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int co_Occurrance(Mat image, int inicioregiao_x, int inicioregiao_y,
                int fimregiao_x, int fimregiao_y){
    
    int inicio_regiao_x = inicioregiao_x, inicio_regiao_y = inicioregiao_y;
    int fim_regiao_x = fimregiao_x, fim_regiao_y = fimregiao_y;
    
    Mat imagem;
    image.copyTo(imagem);
    
    /*Normalizacao da imagem por N = 32*/
    uchar N = 128;
    imagem /= N;
    imagem *= N;
    
    imshow("imagem quantizada", imagem);
    waitKey();
    cout << inicio_regiao_x << endl << inicio_regiao_y << endl << fim_regiao_x << endl << fim_regiao_y << endl;

    //descomentar



    /*Primeiramente calculamos a matriz de co-ocorrencia da imagem original.
    A matriz de co-ocorrencia é uma matriz quadrada de tamanho RxR, onde
    R é o numero de tons de cinza da imagem, geralmente, após uma equalização*/
    int sumValues = 0;
    int aux_vector[256] = {};
    int aux = 0;
    /* Loop para contar o valor total dos valores da imagem*/
    for(int i = inicio_regiao_x; i < fim_regiao_x; i++){
        for(int j = inicio_regiao_y; j < fim_regiao_y; j++){
            sumValues = sumValues + imagem.at<uchar>(i,j);
            aux = imagem.at<uchar>(i,j); 
            aux_vector[aux]++;
        } 
    }
    cout << sumValues << endl;
    
    int R = 0;
    for(int i = 0; i < 255; i++){
        if(aux_vector != 0){
            R++;
        }
    }
    
    Mat co_occurance(Size(256, 256), CV_64FC1);
    co_occurance = 0;
    int aux_occurance_x = 0, aux_occurance_y = 0;

    int rows = co_occurance.rows;
    int cols = co_occurance.cols;

    /*Cálculo da matriz de co-ocorrencia: 0 graus p/ direita*/
    for(int i = inicio_regiao_x; i < fim_regiao_x; i++){
        for(int j = inicio_regiao_y; j < fim_regiao_y-1; j++){
            aux_occurance_x = imagem.at<uchar>(i,j);
            aux_occurance_y = imagem.at<uchar>(i,j+1);
            //cout << aux_occurance_x << endl << aux_occurance_y << endl;
            //Size s = co_occurance.size();
            //rows = s.height;
            //cols = s.width;
            //cout << rows << endl << cols << endl;
            co_occurance.at<uchar>(aux_occurance_x,aux_occurance_y)++;
        }
    }
    int width = co_occurance.cols;
    int height = co_occurance.rows;

    /*Cálculo da matriz de co-ocorrencia para ambas as direções:
    Após calculado a matriz de co-ocorrencia para uma direção, é válido
    ressaltar que é muito simples calcular a matriz de co-ocorrencia
    para a direcao contraria sem mudar os parametros do loop,]
    basta percorrer a matriz resultante e somar os 
    valores da seguinte maneira M[x,y]+M[y,x]*/
    //Mat co_occurance_aux(Size(256, 256), CV_64FC1);
    //for(int i = 0; i < height; i++){
    //   for(int j = 0; j < width-1; j++){
    //       if(i >= j){
    //           co_occurance_aux.at<uchar>(i,j) = 
    //                   co_occurance.at<uchar>(i,j)+co_occurance.at<uchar>(j,i);
    //       }
    //   }
    //}
    //for(int i = 0; i < height; i++){
    //   for(int j = 0; j < width-1; j++){
    //       if(i < j){
    //           co_occurance_aux.at<uchar>(i,j) = co_occurance.at<uchar>(j,i);
    //       }
    //   }
    
    //}
    imshow("co-ocorrencia",co_occurance);
    waitKey();

    
    //SAÍDA
    

    //descomentar



    //descomentar
    // /*Cálculo da matriz de co-ocorrencia: +45 graus*/
    // for(int i = 1; i < height; i++){
    //     for(int j = 0; j < width-1; j++){
    //         aux_occurance_x = imagem.at<uchar>(i,j);
    //         aux_occurance_y = imagem.at<uchar>(i-1,j+1);
    //         co_occurance.at<uchar>(aux_occurance_x,aux_occurance_y)++;
    //     }
    // }

    // /*Cálculo da matriz de co-ocorrencia: +135 graus */
    // for(int i = 1; i < height; i++){
    //     for(int j = 1; j < width; j++){
    //         aux_occurance_x = imagem.at<uchar>(i,j);
    //         aux_occurance_y = imagem.at<uchar>(i-1,j-1);
    //         co_occurance.at<uchar>(aux_occurance_x,aux_occurance_y)++;
    //     }
    // }

    // /*Cálculo da matriz de co-ocorrencia: +90 graus */
    // for(int i = 1; i < height; i++){
    //     for(int j = 0; j < width; j++){
    //         aux_occurance_x = imagem.at<uchar>(i,j);
    //         aux_occurance_y = imagem.at<uchar>(i-1,j);
    //         co_occurance.at<uchar>(aux_occurance_x,aux_occurance_y)++;
    //     }
    // }
    //descomentar

    // /*Cálculo da matriz de co-ocorrencia: 0 graus p/ esquerda*/
    // for(int i = 0; i < height; i++){
    //     for(int j = 1; j < width; j++){
    //         aux_occurance_x = imagem.at<uchar>(i,j);
    //         aux_occurance_y = imagem.at<uchar>(i,j-1);
    //         co_occurance.at<uchar>(aux_occurance_x,aux_occurance_y)++;
    //     }
    // }   
    
    // /*Cálculo da matriz de co-ocorrencia: -90 graus */
    // for(int i = 0; i < height-1; i++){
    //     for(int j = 0; j < width; j++){
    //         aux_occurance_x = imagem.at<uchar>(i,j);
    //         aux_occurance_y = imagem.at<uchar>(i+1,j);
    //         co_occurance.at<uchar>(aux_occurance_x,aux_occurance_y)++;
    //     }
    // }

    // /*Cálculo da matriz de co-ocorrencia: -135 graus */
    // for(int i = 0; i < height-1; i++){
    //     for(int j = 1; j < width-1; j++){
    //         aux_occurance_x = imagem.at<uchar>(i,j);
    //         aux_occurance_y = imagem.at<uchar>(i+1,j-1);
    //         co_occurance.at<uchar>(aux_occurance_x,aux_occurance_y)++;
    //     }
    // }

    /*Utilizamos os valores dos pixels da imagem escolhida para
    criar uma tabela de probabilidade através de uma equação de normalização*/
    
    Mat probabilityTable(Size(256,256), CV_64FC1);
        for(int i = 0; i < width; i++){
             for(int j = 0; j < height; j++){
                 probabilityTable.at<uchar> (i,j) = co_occurance.at<uchar>(i,j)/sumValues;
         } 
    }

    // /* Feito isso, normalizamos a matriz de probabilidade pelo número de valores
    // diferentes na imagem original, R*/
    
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            probabilityTable.at<uchar> (i,j) = probabilityTable.at<uchar>(i,j)/R;
        } 
    }
    
    return 0;
}


int main(int argc, char** argv){
    
    Mat image;

    int inicioregiao_x = 50, fimregiao_x = 300;
    int inicioregiao_y = 50, fimregiao_y = 300;
    
    image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    imshow("imagem", image);

    if(!image.data){
        std::cout << "imagem nao carregou corretamente\n";
        return(-1);
    }

     co_Occurrance(image, inicioregiao_x, inicioregiao_y, fimregiao_x, fimregiao_y);


    return 0;
}