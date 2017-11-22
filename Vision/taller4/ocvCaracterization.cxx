#include <iostream>
#include <math.h>
#include <queue>

#include <opencv2/opencv.hpp>

using namespace cv;
#define PI 3.14159265

std::queue< std::pair< int, int > > checkNeighbors4( std::queue< std::pair< int, int > > boundary, Mat img, Mat &marks, Mat &resp, uchar cont )
{
  std::pair< int, int > p = boundary.front( );
  int i = p.first;
  int j = p.second;

  std::vector< std::pair< int, int > > pts;

  if( i - 1 > 0)
  {
    pts.push_back( std::make_pair( i-1, j ) );
  }
  if( j - 1 > 0 )
  {
    pts.push_back( std::make_pair( i, j-1 ) );
  }
  if( i + 1 < img.rows)
  {
    pts.push_back( std::make_pair( i+1, j ) );
  }
  if( j+1 < img.rows )
  {
    pts.push_back( std::make_pair( i, j+1 ) );
  }

  for( int k = 0; k < pts.size( ); k++ )
  {
    if( img.at< uchar >( pts[k].first, pts[k].second ) > 0 && marks.at< uchar >(pts[k].first, pts[k].second) == 0 )
    {
      marks.at< uchar >( pts[k].first, pts[k].second ) = 1;
      resp.at< uchar >( pts[k].first, pts[k].second ) = cont;
      boundary.push(pts[k]);
    }
  }

  return boundary;
}

int main( int argc, char** argv )
{
  if( argc < 2 )
    {
      std::cerr << "Ayuda: " << std::endl << argv[ 0 ] << " archivo_imagen" << std::endl;
      return( -1 );
    }

  Mat image, img_gray, img_thresh;
  image = imread( argv[ 1 ], 1 );

  if( !image.data )
    {
      std::cerr << "Error: La image no existe." << std::endl;
      return( -1 );
  }

  cvtColor( image, img_gray, CV_BGR2GRAY );
  threshold( img_gray, img_thresh, 128, 255, 0 );

  imwrite( "thresh.png", img_thresh );

  uchar cont = 1;
  Mat marks = Mat::zeros( image.size( ), img_thresh.type( ) );
  Mat resp = Mat::zeros( image.size( ), img_thresh.type( ) );
  std::queue< std::pair< int, int > > boundary;

  for( int i = 0; i < image.rows; i++ )
  {
    for( int j = 0; j < image.cols; j++ )
    {
      if( img_thresh.at< uchar >( i, j ) > 0 && marks.at< uchar >( i, j ) == 0 )
      {
        std::pair< int, int > point = std::make_pair( i, j );
        boundary.push( point );
        resp.at< uchar >( i, j ) = cont;
        marks.at< uchar >( i, j ) = 1;

        while( !boundary.empty( ) )
        {
          boundary = checkNeighbors4( boundary, img_thresh, marks, resp, cont++ );
          boundary.pop( );
        }
      }
    }
  }

  imwrite( "output.png", resp );

  return 0;
}
