#include <iostream>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

using namespace cv;

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

  Mat dst, kernelProm, kernelHigh;
  Point anchor;
  double delta;
  int ddepth, kernel_size;

  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;
  kernel_size = 3;

  kernelProm = Mat::ones( kernel_size, kernel_size, CV_32F ) / ( float ) ( kernel_size * kernel_size );
  kernelHigh = Mat::ones( 3, 3, CV_64F );
  for(int i = 0; i < kernelHigh.rows; i++ )
  {
    for(int j = 0; j < kernelHigh.cols; j++ )
    {
      if( i == 1 && j == 1 )
      {
        kernelHigh.at<double>( i, j ) = 9;
      }
      else
      {
        kernelHigh.at<double>( i, j ) = -1;
      }
    }
  }

  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );

  filter2D( src, dst, ddepth, kernelProm, anchor, delta, BORDER_DEFAULT );
  filter2D( dst, dst, ddepth, kernelHigh, anchor, delta, BORDER_DEFAULT );

  imwrite( basename + "_NR.png", dst);
}
