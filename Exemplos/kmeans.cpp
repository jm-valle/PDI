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