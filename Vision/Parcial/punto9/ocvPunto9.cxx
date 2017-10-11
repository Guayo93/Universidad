#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;

#define PI 3.14159265

int main( int argc, char** argv )
{
  if( argc < 2 )
  {
    std::cerr << "Ayuda: " << std::endl << argv[ 0 ] << " archivo_imagen" << std::endl;
    return( -1 );
  }

  Mat src;
  src = imread( argv[ 1 ], 1 );

  if( !src.data )
  {
    std::cerr << "Error: La imagen no existe." << std::endl;
    return( -1 );
  }

  Mat transfMat( 2, 3, CV_64F, cvScalar( 0.0 ) );
  double angle = 35 * PI / 180;

  transfMat.at< double >( 0, 0 ) = 1.25 * cos( angle );
  transfMat.at< double >( 0, 1 ) = -0.875 * sin( angle );
  transfMat.at< double >( 0, 2 ) = ( -21 * cos( angle ) ) - ( 15 * sin( angle ) );
  transfMat.at< double >( 1, 0 ) = 1.25 * sin( angle );
  transfMat.at< double >( 1, 1 ) = 0.875 * cos( angle );
  transfMat.at< double >( 1, 2 ) = ( -21 * sin( angle ) ) + ( 15* cos( angle ) );
  
  Mat dst;
  warpAffine( src, dst, transfMat, Size( src.cols, src.rows ), INTER_LINEAR, BORDER_CONSTANT );

  imwrite( "output.png", dst );

  return 0;
}
