#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main( int argc, char** argv )
{
  if( argc < 2 )
  {
    std::cerr << "Ayuda: " << std::endl << argv[ 0 ] << " archivo_imagen" << std::endl;
    return( -1 );
  }

  Mat image;
  image = imread( argv[ 1 ], 1 );

  if( !image.data )
  {
    std::cerr << "Error: La image no existe." << std::endl;
    return( -1 );
  }

  Mat rImg = Mat::zeros( image.size( ), CV_8UC3 );
  Mat gImg = Mat::zeros( image.size( ), CV_8UC3 );
  Mat bImg = Mat::zeros( image.size( ), CV_8UC3 );

  MatIterator_< Vec3b > it, crIt, cgIt, cbIt, end, endr, endg, endb;

  it = image.begin< Vec3b >( );
  crIt = rImg.begin< Vec3b >( );
  cgIt = gImg.begin< Vec3b >( );
  cbIt = bImg.begin< Vec3b >( );
  end = image.end< Vec3b >( );
  endr = rImg.end< Vec3b >( );
  endg = gImg.end< Vec3b >( );
  endb = bImg.end< Vec3b >( );

  for( ; it != end, crIt != endr, cgIt != endg, cbIt != endb; ++it, ++crIt, ++cgIt, ++cbIt)
  {
    (*crIt)[0] = 0;
    (*crIt)[1] = 0;
    (*crIt)[2] = (*it)[2];

    (*cgIt)[0] = 0;
    (*cgIt)[1] = (*it)[1];
    (*cgIt)[2] = 0;

    (*cbIt)[0] = (*it)[0];
    (*cbIt)[1] = 0;
    (*cbIt)[2] = 0;
  }

  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );

  imwrite( basename + "_R.png", rImg );
  imwrite( basename + "_G.png", gImg );
  imwrite( basename + "_B.png", bImg );

  std::cout << "Termina separacion de canales." << std::endl;

  Mat res_img_r, res_img_g, res_img_b;
  resize( rImg, res_img_r, Size( ), 0.75f, 0.75f );
  resize( gImg, res_img_g, Size( ), 0.5f, 0.5f );
  resize( bImg, res_img_b, Size( ), 0.25f, 0.25f );

  imwrite( basename + "_sR.png", res_img_r );
  imwrite( basename + "_sG.png", res_img_g );
  imwrite( basename + "_sB.png", res_img_b );

  Mat ress_img_r, ress_img_g, ress_img_b;
  resize( res_img_r, ress_img_r, Size( ), 1.3334f, 1.3334f );
  resize( res_img_g, ress_img_g, Size( ), 2, 2 );
  resize( res_img_b, ress_img_b, Size( ), 4, 4 );

  imwrite( basename + "_ssR.png", ress_img_r );
  imwrite( basename + "_ssG.png", ress_img_g );
  imwrite( basename + "_ssB.png", ress_img_b );

  std::cout << "Termina Escalamiento y ReEscalamiento." << std::endl;

  Mat rgbImg = Mat::zeros( image.size( ), CV_8UC3 );

  MatIterator_< Vec3b > rgbIt, endRgb;
  rgbIt = rgbImg.begin< Vec3b >( );
  endRgb = rgbImg.end< Vec3b >( );

  crIt = rImg.begin< Vec3b >( );
  cgIt = gImg.begin< Vec3b >( );
  cbIt = bImg.begin< Vec3b >( );

  for( ; crIt != endr, cgIt != endg, cbIt != endb, rgbIt != endRgb; ++crIt, ++cgIt, ++cbIt, ++rgbIt)
  {
    (*rgbIt)[ 0 ] = (*cbIt)[ 0 ];
    (*rgbIt)[ 1 ] = (*cgIt)[ 1 ];
    (*rgbIt)[ 2 ] = (*crIt)[ 2 ];
  }

  imwrite( basename + "_RGB.png", rgbImg );

  std::cout << "Termina union de canales." << std::endl;

  Mat diffImg = Mat::zeros( image.size( ), CV_8UC3 );

  MatIterator_< Vec3b > diIt, enddi;
  diIt = diffImg.begin< Vec3b >( );
  enddi = diffImg.end< Vec3b >( );

  it = image.begin< Vec3b >( );
  rgbIt = rgbImg.begin< Vec3b >( );

  for( ; it != end, rgbIt != endRgb, diIt != enddi; ++it, ++rgbIt, ++diIt )
  {
    (*diIt)[ 0 ] = (*it)[ 0 ] - (*rgbIt)[ 0 ];
    (*diIt)[ 1 ] = (*it)[ 1 ] - (*rgbIt)[ 1 ];
    (*diIt)[ 2 ] = (*it)[ 2 ] - (*rgbIt)[ 2 ];
  }

  imwrite( basename + "_diff.png", diffImg );

  std::cout << "Termina diferencia de Imagenes." << std::endl;

  return( 0 );
}
