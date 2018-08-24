#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

double max_Probability(Mat pij){
    double min, max;
    minMaxLoc(pij, &min, &max);
    return max;
}

float corelaction(Mat pij){
    int width = pij.cols;
    int height = pij.rows;
    
    float mr = 0.0, mc = 0.0, sigmaR = 0.0, sigmaC = 0.0;
    float sigmaR_sqrt = 0.0, sigmaC_sqrt = 0.0;
    int correlaction_value = 0;
    int aux = 0;
    //Calculo de mr
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            aux = aux + pij.at<uchar>(i,j);
        }
        mr = mr + (aux * i); 
    }

    int aux1 = 0;
    //Calculo de mc
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            aux1 = aux1 + pij.at<uchar>(i,j);
        }
        mc = mc + (aux1 * j); 
    }
    cout << "trolo" << endl << endl << mc << endl << mr;
    int aux2 = 0;
    //Calculo de sigmaR
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            aux2 = aux2 + pij.at<uchar>(i,j);
        }
        sigmaR = sigmaR + (pow((i-mr), 2) * aux2); 
    }
    sigmaR_sqrt = sqrt(sigmaR);

    float aux3 = 0;
    //Calculo de sigmaC
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            aux3 = aux3 + pij.at<uchar>(i,j);
        }
        sigmaC = sigmaC + (pow((i-mc), 2) * aux3); 
    }
    sigmaC_sqrt = sqrt(sigmaC);

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            correlaction_value = correlaction_value + (((i - mr) * (j-mc) * (pij.at<uchar>(i,j))) / (sigmaR_sqrt * sigmaC_sqrt));
        }
    }

    return correlaction_value;
}

int contrast(Mat pij){
    int width = pij.cols;
    int height = pij.rows;
    
    int contrast_value = 0;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            contrast_value = contrast_value + (((pow((i-j),2))*pij.at<uchar>(i,j)));
        } 
    }
    return contrast_value;
}

int uniformity(Mat pij){
    int width = pij.cols;
    int height = pij.rows;
    
    int uniformity_value = 0;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            uniformity_value = uniformity_value + ((pij.at<uchar>(i,j))^2);
        } 
    }
    return uniformity_value;
}

int entropy(Mat pij){
    int width = pij.cols;
    int height = pij.rows;
    
    int entropy_value = 0;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            entropy_value = entropy_value + (pij.at<uchar>(i,j)*log(pij.at<uchar>(i,j)));
        } 
    }
    return entropy_value;
}

float homogenity(Mat pij){
    int width = pij.cols;
    int height = pij.rows;
    
    float homogenity_value = 0.0;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            
            homogenity_value = homogenity_value + (pij.at<uchar>(i,j)/ (1 +  abs(i-j)));
        } 
    }
    return homogenity_value;
}

int co_Occurrance(Mat image, int inicioregiao_x, int inicioregiao_y,
                int fimregiao_x, int fimregiao_y){
    
    int inicio_regiao_x = inicioregiao_x, inicio_regiao_y = inicioregiao_y;
    int fim_regiao_x = fimregiao_x, fim_regiao_y = fimregiao_y;
    
    Mat imagem;
    image.copyTo(imagem);
    
    
    /*Normalizacao da imagem por N = 32*/
    
    uchar N = 32;
    imagem /= N;
    

    double max, min;
    minMaxLoc(imagem, &min, &max);
    cout << max << endl;
    
    imshow("imagem quantizada", imagem);
    waitKey();
    cout << inicio_regiao_x << endl << inicio_regiao_y << endl << fim_regiao_x << endl << fim_regiao_y << endl;

    /*Primeiramente calculamos a matriz de co-ocorrencia da imagem original.
    A matriz de co-ocorrencia é uma matriz quadrada de tamanho RxR, onde
    R é o numero de tons de cinza da imagem, geralmente, após uma equalização*/
    int aux_vector[N] = {};
    int aux = 0;

    //ERRO: mesmo eu normalizando por 32, aparecem muitos tons de cinza, onde só deveriam aparecer tres: branco, cinza, e preto
    /* Loops para contar o valor total dos tons de cinza da imagem*/
    for(int i = inicio_regiao_x; i < fim_regiao_x; i++){
        for(int j = inicio_regiao_y; j < fim_regiao_y; j++){
            aux = imagem.at<uchar>(i,j); 
            aux_vector[aux]++;
        } 
    }
    int r = 8;
    //for(int i = 0; i < 255; i++){
      //  if(aux_vector[i] != 0){
        //    r++;
        //}
    //}
    
    Mat co_occurance(Size(8, 8), CV_64FC1);
    co_occurance = 0;
    int aux_occurance_x = 0, aux_occurance_y = 0;

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
    int sumValues = 0;

    int aux_soma = 0;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            aux_soma = co_occurance.at<uchar>(i,j);
            sumValues = sumValues + aux_soma;
        } 
    }
    
    //imshow("co-ocorrencia",co_occurance);
    //waitKey();
    cout << "Soma dos Valores (sumValue)" << sumValues << endl;
    cout << "Nível dos tons de cinza (r)" << r << endl;
    /*Utilizamos os valores dos pixels da imagem escolhida para
    criar uma tabela de probabilidade através de uma equação de normalização*/
    
    Mat probabilityTable(Size(8,8), CV_64FC1);
    int aux_prob = 0;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            aux_prob = co_occurance.at<uchar>(i,j);
            probabilityTable.at<uchar> (i,j) = aux_prob/sumValues;
        } 
    }

    // /* Feito isso, normalizamos a matriz de probabilidade pelo número de valores
    // diferentes na imagem original, R*/
    float aux_norm = 0.0;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            aux_norm = probabilityTable.at<uchar>(i,j);
            probabilityTable.at<uchar> (i,j) = aux_norm/r;
        } 
    }
    
    double probabilidade_maxima = max_Probability(probabilityTable);
    
    //Erro: o resultado sempre está dando zero;
    float contraste = contrast(probabilityTable);

    float entropia = entropy(probabilityTable);
    float uniformidade = uniformity(probabilityTable);

    //Erro: o resultado sempre está dando zero;
    float homogeneidade = homogenity(probabilityTable);
    //Erro: o resultado sempre está dando -nan, o que nao faz sentido nenhum;
    float correlacao = corelaction(probabilityTable);
    cout << probabilidade_maxima << endl << contraste << endl << entropia << endl << uniformidade << endl << homogeneidade << endl << correlacao;
    return 0;
}


int main(int argc, char** argv){
    
    Mat image;

    int inicioregiao_x = 1, fimregiao_x = 300;
    int inicioregiao_y = 1, fimregiao_y = 300;
    
    image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    imshow("imagem", image);

    if(!image.data){
        std::cout << "imagem nao carregou corretamente\n";
        return(-1);
    }

    co_Occurrance(image, inicioregiao_x, inicioregiao_y, fimregiao_x, fimregiao_y);


    return 0;
}