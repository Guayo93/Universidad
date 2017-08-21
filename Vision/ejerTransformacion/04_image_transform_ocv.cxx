#include <iostream>
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

  Mat image;
  image = imread( argv[ 1 ], 1 );

  if( !image.data )
  {
    std::cerr << "Error: La image no existe." << std::endl;
    return( -1 );
  }

  // Full Matrix Transformation ------------------------------------------------
  Mat transfMat( 2, 3, CV_64F, cvScalar( 0.0 ) );
  double angle = 35 * PI / 180;

  transfMat.at< double >( 0, 0 ) = 0.8 * cos( angle );
  transfMat.at< double >( 0, 1 ) = 0.8 * sin( angle );
  transfMat.at< double >( 0, 2 ) = ( -33.6 * cos( angle ) ) - ( 29.6 * sin( angle ) );
  transfMat.at< double >( 1, 0 ) = -0.8 * sin( angle );
  transfMat.at< double >( 1, 1 ) = 0.8 * cos( angle );
  transfMat.at< double >( 1, 2 ) = ( -33.6 * sin( angle ) ) + ( 29.6 * cos( angle ) );

  Mat destiny;
  Size size_mat( image.cols, image.rows );
  warpAffine( image, destiny, transfMat, size_mat, INTER_LINEAR, BORDER_CONSTANT );

  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );

  imwrite( basename + "_matrix.png", destiny );

  // Steps Transformation ------------------------------------------------------

  Mat transSca, transRot, transTra;
  Point axis = Point( 0.0 , 0.0 );

  transTra = ( Mat_<double>(2,3) << 1, 0, -42, 0, 1, 37 );
  Mat ttDestiny = Mat::zeros( image.size( ), image.type() );
  warpAffine( image , ttDestiny , transTra , image.size() );

  transRot = getRotationMatrix2D( axis, 35, 1 );
  Mat trDestiny = Mat::zeros( image.size() , image.type() );
  warpAffine( ttDestiny , trDestiny , transRot , image.size() );

  transSca = getRotationMatrix2D( axis, 0, 0.8);
  Mat tsDestiny = Mat::zeros( image.size() , image.type() );
  warpAffine( trDestiny , tsDestiny , transSca , image.size() );

  imwrite( basename + "_translate.png", ttDestiny );
  imwrite( basename + "_rotate.png", trDestiny );
  imwrite( basename + "_scale.png", tsDestiny );

  return( 0 );
}
