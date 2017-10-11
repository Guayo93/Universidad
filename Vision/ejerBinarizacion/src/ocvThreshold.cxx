#include <iostream>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

using namespace cv;

int main( int argc, char** argv )
{
  if( argc < 4 )
  {
    std::cerr << "Ayuda: " << std::endl << argv[ 0 ] << " archivo_imagen valor_binarizacion_(0-255) valor_binarizacion_adaptable_(0-255)" << std::endl;
    return( -1 );
  }

  Mat src, src_grey;
  int thresholdValue, adaptiveThresholdValue;
  src = imread( argv[ 1 ], 1 );

  if( !src.data )
  {
    std::cerr << "Error: La imagen no existe." << std::endl;
    return( -1 );
  }

  std::stringstream ss;
  ss << argv[ 2 ];
  ss >> thresholdValue;
  ss.clear();

  if( thresholdValue < 0 || thresholdValue > 255 )
  {
    std::cerr << "Error: El valor binario ingresado no es valido." << std::endl;
    return( -1 );
  }

  ss << argv[ 3 ];
  ss >> adaptiveThresholdValue;

  if( adaptiveThresholdValue < 0 || adaptiveThresholdValue > 255 )
  {
    std::cerr << "Error: El valor adaptable ingresado no es valido." << std::endl;
    return( -1 );
  }

  cvtColor( src, src_grey, COLOR_RGB2GRAY );

  Mat dst;
  for( int i = 0; i < 5; i++ )
  {
    threshold( src_grey, dst, thresholdValue, 255, i );

    std::stringstream ss0;
    ss0 << "output_" << i+1 << "_" << thresholdValue << ".png";
    imwrite( ss0.str(), dst );
  }

  for( double i = 0; i < 2; i++ )
  {
    adaptiveThreshold( src_grey, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, i, 5, adaptiveThresholdValue);

    std::stringstream ss0;
    ss0 << "output_A_" << i+1 << "_" << adaptiveThresholdValue << ".png";
    imwrite( ss0.str(), dst );
  }
}
