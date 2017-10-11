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

  Mat dstA, dstB, kernelA, kernelB;
  Point anchor;
  double delta;
  int ddepth, kernel_size;

  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;
  kernel_size = 3;

  kernelA = Mat::ones( kernel_size, kernel_size, CV_64F );
  kernelB = Mat::zeros( kernel_size, kernel_size, CV_64F );

  kernelA.at< double >( 0, 0 ) = -(1/3);
  kernelA.at< double >( 0, 1 ) = -(1/3);
  kernelA.at< double >( 0, 2 ) = -(1/3);

  kernelA.at< double >( 2, 0 ) = -(1/3);
  kernelA.at< double >( 2, 1 ) = -(1/3);
  kernelA.at< double >( 2, 2 ) = -(1/3);

  filter2D( src, dstA, ddepth, kernelA, anchor, delta, BORDER_DEFAULT );
  imwrite( "outputKernelA.png", dstA );

  kernelB.at< double >( 0, 0 ) = -0.333;
  kernelB.at< double >( 1, 0 ) = -0.333;
  kernelB.at< double >( 2, 0 ) = -0.333;

  kernelB.at< double >( 0, 2 ) = 0.333;
  kernelB.at< double >( 1, 2 ) = 0.333;
  kernelB.at< double >( 2, 2 ) = 0.333;

  filter2D( src, dstB, ddepth, kernelB, anchor, delta, BORDER_DEFAULT );
  imwrite( "outputKernelB.png", dstB );

  return 0;
}
