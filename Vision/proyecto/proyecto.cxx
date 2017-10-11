#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;

#define PI 3.14159265

void applyPasaBajos( Mat src )
{
  Point anchor;
  double delta;
  int ddepth, kernel_size;

  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;
  kernel_size = 3;
  Mat kernel = Mat::ones( kernel_size, kernel_size, CV_64F );

  for( int i = 0; i < kernel_size; i++ )
  {
    for( int j = 0; j < kernel_size; j++ )
    {
      kernel.at< double >( i, j ) = 0.11111;
    }
  }

  Mat dst;
  filter2D( src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT );
  imwrite( "outputPasaBajos.png", dst );
}

void applyPasaAltos( Mat src )
{
  Point anchor;
  double delta;
  int ddepth, kernel_size;

  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;
  kernel_size = 3;
  Mat kernel = Mat::zeros( kernel_size, kernel_size, CV_64F );

  for( int i = 0; i < kernel_size; i++ )
  {
    for( int j = 0; j < kernel_size; j++ )
    {
      if( i == 1 && j == 1 )
      {
        kernel.at< double >( 1, 1 ) = 9;
      }
      else
      {
        kernel.at< double >( i, j ) = -1;
      }
    }
  }

  Mat dst;
  filter2D( src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT );
  imwrite( "outputPasaAltos.png", dst );
}

void applyRelieve( Mat src )
{
  Point anchor;
  double delta;
  int ddepth, kernel_size;

  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;
  kernel_size = 3;
  Mat kernel = Mat::zeros( kernel_size, kernel_size, CV_64F );

  kernel.at< double >( 0, 0 ) = -1;
  kernel.at< double >( 0, 1 ) = -1;
  kernel.at< double >( 1, 0 ) = -1;
  kernel.at< double >( 2, 1 ) = 1;
  kernel.at< double >( 1, 2 ) = 1;
  kernel.at< double >( 2, 2 ) = 1;

  Mat dst;
  filter2D( src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT );
  imwrite( "outputRelieve.png", dst );
}

void applyIdentity( Mat src )
{
  Point anchor;
  double delta;
  int ddepth, kernel_size;

  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;
  kernel_size = 3;
  Mat kernel = Mat::zeros( kernel_size, kernel_size, CV_64F );

  kernel.at< double >( 1, 1 ) = 1;

  Mat dst;
  filter2D( src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT );
  imwrite( "outputIdentity.png", dst );
}

void applyThreshold( Mat src, int thresholdValue )
{
  Mat src_grey, dst;
  cvtColor( src, src_grey, COLOR_RGB2GRAY );

  for( int i = 0; i < 5; i++ )
  {
    threshold( src_grey, dst, thresholdValue, 255, i );
    std::stringstream ss;
    ss << "outputThreshold_" << i+1 << ".png";
    imwrite( ss.str( ), dst );
  }
}

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

  applyPasaBajos( src );
  applyPasaAltos( src );
  applyRelieve( src );
  applyIdentity( src );
  applyThreshold( src, 128 );

  return 0;
}
