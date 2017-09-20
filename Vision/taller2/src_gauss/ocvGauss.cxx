#include <iostream>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

using namespace cv;

Mat customResize( Mat src, bool isDownSample )
{
  Mat result = isDownSample ? Mat::zeros( Size( src.cols/2, src.rows/2 ), CV_8UC3 ) : Mat::zeros( Size( src.cols*2, src.rows*2 ) * 2, CV_8UC3 );

  if( isDownSample )
  {
    for( int i = 0; i < result.rows; i++ )
    {
      for( int j = 0; j < result.cols; j++ )
      {
        result.at<double>( i, j ) = src.at<double>( (i*2)+1, (j*2)+1 );
      }
    }
  }
  else
  {
    for( int i = 0; i < src.rows; i++ )
    {
      for( int j = 0; j < src.cols; j++ )
      {
        result.at<double>( i*2, j*2 ) = src.at<double>( i, j );
      }
    }
  }

  return result;
}

Mat getKernel( bool isDownSample )
{
  float x = isDownSample ? 1 : 4;

  Mat kernel = ( Mat_<float>(7, 7) << 0.00000067*x,	0.00002292*x,	0.00019117*x,	0.00038771*x,	0.00019117*x,	0.00002292*x,	0.00000067*x,
                                     0.00002292*x,	0.00078634*x,	0.00655965*x,	0.01330373*x,	0.00655965*x, 0.00078633*x,	0.00002292*x,
                                     0.00019117*x,	0.00655965*x,	0.05472157*x,	0.11098164*x,	0.05472157*x,	0.00655965*x,	0.00019117*x,
                                     0.00038771*x,	0.01330373*x,	0.11098164*x,	0.22508352*x,	0.11098164,	0.01330373*x,	0.00038771*x,
                                     0.00019117*x,	0.00655965*x,	0.05472157*x,	0.11098164*x,	0.05472157*x,	0.00655965*x,	0.00019117*x,
                                     0.00002292*x,	0.00078633*x,	0.00655965*x,	0.01330373*x,	0.00655965*x,	0.00078633*x,	0.00002292*x,
                                     0.00000067*x,	0.00002292*x,	0.00019117*x,	0.00038771*x,	0.00019117,	0.00002292*x,	0.00000067*x );

  return kernel;
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

  Mat dst, tmp = src;
  Point anchor = Point( -1, -1 );
  double delta = 0;
  int ddepth = -1;

  for( int i = 0; i < 3; i++ )
  {
    Mat filter;
    filter2D( tmp, filter, ddepth, getKernel( true ), anchor, delta, BORDER_DEFAULT );

    // Por alguna razon esta generando un Segmentation Fault. Solucion Temporal: Usar resize
    //dst = customResize( filter, true ).clone( );
    resize( filter, dst, tmp.size()/2 );

    std::stringstream ss;
    ss << "output_" << 3-i << ".png";

    imwrite( ss.str( ), dst );

    tmp = dst.clone( );

    std::cout << "Finaliza " << 3-i << std::endl;
  }

  tmp = src;
  Mat tmpS = tmp;

  imwrite( "output_4.png", src );

  std::cout << "Finaliza " << 4 << std::endl;

  for( int i = 0; i < 3; i++ )
  {
    // Por alguna razon esta generando un Segmentation Fault. Solucion Temporal: Usar resize
    // dst = customResize( tmpS, false ).clone( );
    resize( tmp, tmpS, tmp.size()*2 );

    // La variable booleana downSample sigue en true porque al usar la funcion resize, esta rellena los espacios automaticamente y si se usa el filtro * 4 causa que las imagenes se vuelvan blancas
    filter2D( tmpS, dst, ddepth, getKernel( true ), anchor, delta, BORDER_DEFAULT );

    std::stringstream ss;
    ss << "output_" << 5+i << ".png";

    imwrite( ss.str( ), dst );

    tmp = dst.clone( );

    std::cout << "Finaliza " << 5+i << std::endl;
  }

  return 0;
}
