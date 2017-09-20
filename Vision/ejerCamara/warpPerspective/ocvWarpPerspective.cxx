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

  // Input Quadilateral or Image plane coordinates
  Point2f inputQuad[4];
  // Output Quadilateral or World plane coordinates
  Point2f outputQuad[4];

  // Lambda Matrix
  Mat lambda( 2, 4, CV_32FC1 );
  //Input and Output Image;
  Mat output;
  // Set the lambda matrix the same type and size as input
  lambda = Mat::zeros( src.rows, src.cols, src.type() );

  // The 4 points that select quadilateral on the input , from top-left in clockwise order
  // These four pts are the sides of the rect box used as input
  inputQuad[0] = Point2f( -30,-60 );
  inputQuad[1] = Point2f( src.cols+50,-50);
  inputQuad[2] = Point2f( src.cols+100,src.rows+50);
  inputQuad[3] = Point2f( -50,src.rows+50  );
  // The 4 points where the mapping is to be done , from top-left in clockwise order
  outputQuad[0] = Point2f( 0,0 );
  outputQuad[1] = Point2f( src.cols-1,0);
  outputQuad[2] = Point2f( src.cols-1,src.rows-1);
  outputQuad[3] = Point2f( 0,src.rows-1  );

  // Get the Perspective Transform Matrix i.e. lambda
  lambda = getPerspectiveTransform( inputQuad, outputQuad );
  // Apply the Perspective Transform just found to the src image
  warpPerspective(src,output,lambda,output.size() );

  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );
  imwrite( basename + "_perspective.png", output);
}
