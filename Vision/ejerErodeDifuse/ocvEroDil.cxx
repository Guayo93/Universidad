#include <iostream>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

using namespace cv;

Mat opening( Mat src )
{
  Mat erod;
  erode( src, erod, Mat( ), Point( -1, -1 ), 1, BORDER_CONSTANT, morphologyDefaultBorderValue( ) );
  Mat dst;
  dilate( erod, dst, Mat( ), Point( -1, -1 ), 1, BORDER_CONSTANT, morphologyDefaultBorderValue( ) );

  return dst;
}

Mat closing( Mat src )
{
  Mat dil;
  dilate( src, dil, Mat( ), Point( -1, -1 ), 1, BORDER_CONSTANT, morphologyDefaultBorderValue( ) );
  Mat dst;
  erode( dil, dst, Mat( ), Point( -1, -1 ), 1, BORDER_CONSTANT, morphologyDefaultBorderValue( ) );

  return dst;
}

Mat succesiveErode( Mat src, int its )
{
  Mat dst;
  erode( src, dst, Mat( ), Point( -1, -1 ), its, BORDER_CONSTANT, morphologyDefaultBorderValue( ) );

  return dst;
}

Mat succesiveDilate( Mat src, int its )
{
  Mat dst;
  dilate( src, dst, Mat( ), Point( -1, -1 ), its, BORDER_CONSTANT, morphologyDefaultBorderValue( ) );

  return dst;
}

Mat gradient( Mat src )
{
  Mat dil;
  dilate( src, dil, Mat( ), Point( -1, -1 ), 1, BORDER_CONSTANT, morphologyDefaultBorderValue( ) );
  Mat erod;
  erode( src, erod, Mat( ), Point( -1, -1 ), 1, BORDER_CONSTANT, morphologyDefaultBorderValue( ) );

  return dil - erod;
}

Mat topHat( Mat src )
{
  Mat open = opening( src );

  return src - open;
}

Mat bottomHat( Mat src )
{
  Mat close = closing( src );

  return close - src;
}

int main( int argc, char** argv )
{
  if( argc < 4 )
  {
    std::cerr << "Ayuda: " << std::endl << argv[ 0 ] << " archivo_imagen id_operacion (1: Apertura, 2: Cierre, 3: Dilataciones Sucesivas, 4: Erosiones Sucesivas, 5: Gradiente, 6: Top-hat, 7: Bottom-hat) iteraciones( si son necesarias)" << std::endl;
    return( -1 );
  }

  Mat src;
  src = imread( argv[ 1 ], 1 );

  if( !src.data )
  {
    std::cerr << "Error: La imagen no existe." << std::endl;
    return( -1 );
  }

  Mat dst;
  int opCode = 0, its = 0;
  std::stringstream param( argv[ 2 ] );
  param >> opCode;
  std::stringstream nIts( argv[ 3 ] );
  nIts >> its;

  switch( opCode )
  {
    case 1:
      dst = opening( src );
      imwrite( "output.png", dst );
    break;
    case 2:
      dst = closing( src );
      imwrite( "output.png", dst );
    break;
    case 3:
      dst = succesiveErode( src, its );
      imwrite( "output.png", dst );
    break;
    case 4:
      dst = succesiveDilate( src, its );
      imwrite( "output.png", dst );
    break;
    case 5:
      dst = gradient( src );
      imwrite( "output.png", dst );
    break;
    case 6:
      dst = topHat( src );
      imwrite( "output.png", dst );
    break;
    case 7:
      dst = bottomHat( src );
      imwrite( "output.png", dst );
    break;
  }

  return 0;
}
