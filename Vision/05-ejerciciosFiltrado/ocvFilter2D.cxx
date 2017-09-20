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

  Mat dst, kernel;
  Point anchor;
  double delta;
  int ddepth, kernel_size;

  anchor = Point( -1, -1 );
  delta = 0;
  ddepth = -1;

  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );

  for( int i = 0; i < 5; i++ )
  {
    kernel_size = 3 + 2 * (i % 5);
    kernel = Mat::ones( kernel_size, kernel_size, CV_32F ) / ( float ) ( kernel_size * kernel_size );

    filter2D( src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT );
    char* surname = "_filer";
    std::stringstream ss0;
    ss0 << surname << i+1 << ".png";
    imwrite( basename + ss0.str(), dst );
  }

  kernel_size = 11;
  kernel = Mat::ones( kernel_size, kernel_size, CV_32F ) / ( float ) ( kernel_size * kernel_size );
  filter2D( src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT );

  imwrite( basename + "_filerx11.png", dst);
}
