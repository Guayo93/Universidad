#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;

#define PI 3.14159265
int manas = 0, quietas = 0, ataque = 0, defensa = 0, tapped = 0, untapped = 0;

void definirTipo( int val, Mat &dst, std::vector<Point> points )
{
  int size = static_cast<int>(points.size());
  Mat pointsMat = Mat(size, 2, CV_64FC1);
  for (int i = 0; i < pointsMat.rows; ++i)
  {
      pointsMat.at<double>(i, 0) = points[i].x;
      pointsMat.at<double>(i, 1) = points[i].y;
  }

  PCA pcaAnalisis(pointsMat, Mat(), CV_PCA_DATA_AS_ROW);

  Point cntr = Point(static_cast<int>(pcaAnalisis.mean.at<double>(0, 0)),
                    static_cast<int>(pcaAnalisis.mean.at<double>(0, 1)));

  if( ( val <= 5 && val >= 1 ) || ( val <= 17 && val >= 13 ) )
  {
    putText(dst, "Tierra", cntr, CV_FONT_HERSHEY_COMPLEX, 3, Scalar( 0, 0, 255 ), 5, 8 );
    manas++;
  }
  else if( val == 6 || val == 11 || val == 12 )
  {
    putText(dst, "Estatica", cntr, CV_FONT_HERSHEY_COMPLEX, 3, Scalar( 0, 0, 255 ), 5, 8 );
    quietas++;
  }
  else if( val == 7 || val == 8 )
  {
    putText(dst, "Defensa", cntr, CV_FONT_HERSHEY_COMPLEX, 3, Scalar( 0, 0, 255 ), 5, 8 );
    defensa++;
  }
  else
  {
    putText(dst, "Ataque", cntr, CV_FONT_HERSHEY_COMPLEX, 3, Scalar( 0, 0, 255 ), 5, 8 );
    ataque++;
  }
}

double getOrientation(const std::vector<Point> &points, Mat &img, int cont)
{
  int size = static_cast<int>(points.size());
  Mat pointsMat = Mat(size, 2, CV_64FC1);
  for (int i = 0; i < pointsMat.rows; ++i)
  {
      pointsMat.at<double>(i, 0) = points[i].x;
      pointsMat.at<double>(i, 1) = points[i].y;
  }

  PCA pcaAnalisis(pointsMat, Mat(), CV_PCA_DATA_AS_ROW);

  Point cntr = Point(static_cast<int>(pcaAnalisis.mean.at<double>(0, 0)),
                    static_cast<int>(pcaAnalisis.mean.at<double>(0, 1)));

  std::vector<Point2d> eigen_vecs(2);
  std::vector<double> eigen_val(2);
  for (int i = 0; i < 2; ++i)
  {
      eigen_vecs[i] = Point2d(pcaAnalisis.eigenvectors.at<double>(i, 0),
                              pcaAnalisis.eigenvectors.at<double>(i, 1));

      eigen_val[i] = pcaAnalisis.eigenvalues.at<double>(0, i);
  }

  std::stringstream ss( "" );
  ss << cont;
  putText(img, ss.str( ), cntr, CV_FONT_HERSHEY_COMPLEX, 3, Scalar( 0, 0, 255 ), 5, 8 );

  double angle = atan2(eigen_vecs[0].y, eigen_vecs[0].x); // orientation in radians

  return angle;
 }

int main( int argc, char** argv )
{
  if( argc < 2 )
  {
    std::cerr << "Ayuda: " << std::endl << argv[ 0 ] << " archivo_imagen" << std::endl;
    return( -1 );
  }

  Mat src, dst;

  src = imread( argv[ 1 ], 1 );

  if( !src.data )
  {
    std::cerr << "Error: La imagen no existe." << std::endl;
    return( -1 );
  }
  
  Mat srcGray, srcBin;
  cvtColor( src, srcGray, COLOR_BGR2GRAY );
  threshold( srcGray, srcBin, 128, 255, CV_THRESH_BINARY );

  imwrite( "source.png", src );
  Mat conts, numeration;
  src.copyTo( conts );
  src.copyTo( numeration );
  std::vector< Vec4i > hierarchy;
  std::vector< std::vector< Point > > contours;
  findContours( srcBin, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );
  int cont = 0;

  for( int i = 0; i < contours.size(); i++ )
  {
    double area = contourArea( contours[ i ] );

    if( area > 110000 && area < 200000 )
    {
      cont++;
      drawContours( conts, contours, static_cast<int>(i), Scalar( 0, 0, 255 ), 2, 8, hierarchy, 0 );
      double angle = getOrientation( contours[ i ], numeration, cont );
      angle = angle * 180 / PI;

      if( angle >= 80 && angle <= 100 )
      {
        untapped++;
      }
      else
      {
        tapped++;
      }

      definirTipo( cont, src, contours[ i ] );
    }
  }

  std::cout << "Hubo " << manas << " cartas de Tierra." << std::endl
    << "Hubo " << quietas << " cartas de Criatura Estaticas." << std::endl
    << "Hubo " << ataque << " cartas de Criatura Atacando." << std::endl
    << "Hubo " << defensa << " cartas de Criatura Defendiendo." << std::endl;

  imwrite( "contours.png", conts );
  imwrite( "numeration.png", numeration );
  imwrite( "final.png", src );

  return 0;
}
