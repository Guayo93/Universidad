#include <iostream>
#include <stdlib.h>

#include <opencv2/opencv.hpp>

using namespace cv;

void colorReduce(cv::Mat &image, int div=64) {
 int nl= image.rows; // number of lines
 // total number of elements per line
 int nc= image.cols * image.channels();

 for (int j=0; j<nl; j++) {
 // get the address of row j
 uchar* data= image.ptr<uchar>(j);
 for (int i=0; i<nc; i++) {
 // process each pixel ---------------------

 data[i]= data[i]/div*div + div/2;
 // end of pixel processing ----------------
 } // end of line
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
}
