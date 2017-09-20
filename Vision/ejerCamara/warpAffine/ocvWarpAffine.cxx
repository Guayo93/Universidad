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

  Mat src;
  src = imread( argv[ 1 ], 1 );

  if( !src.data )
  {
    std::cerr << "Error: La imagen no existe." << std::endl;
    return( -1 );
  }

  Point2f srcTri[3];
  Point2f dstTri[3];

  Mat warp_mat( 2, 3, CV_32FC1 );
  Mat warp_dst;

  /// Set the dst image the same type and size as src
  warp_dst = Mat::zeros( src.rows, src.cols, src.type() );

  /// Set your 3 points to calculate the  Affine Transform
  srcTri[0] = Point2f( 0,0 );
  srcTri[1] = Point2f( src.cols - 1, 0 );
  srcTri[2] = Point2f( 0, src.rows - 1 );

  dstTri[0] = Point2f( src.cols*0.0, src.rows*0.33 );
  dstTri[1] = Point2f( src.cols*0.85, src.rows*0.25 );
  dstTri[2] = Point2f( src.cols*0.15, src.rows*0.7 );

  /// Get the Affine Transform
  warp_mat = getAffineTransform( srcTri, dstTri );

  /// Apply the Affine Transform just found to the src image
  warpAffine( src, warp_dst, warp_mat, warp_dst.size() );

  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );
  imwrite( basename + "_affine.png", warp_dst);
}
