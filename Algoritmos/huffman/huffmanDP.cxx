#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>

void printMatrix( std::vector< std::vector< double > > mat )
{
  for( double i = 0; i < mat.size( ); i++ )
  {
    for( double j = 0; j < mat[ i ].size( ); j++ )
    {
      std::cout << mat[ i ][ j ] << "  ";

      if( j + 1 == mat[ i ].size( ) )
      {
        std::cout << std::endl;
      }
    }
  }

  std::cout << std::endl;
}

double getProb( std::vector< std::pair< double, double > > s, double posI, double posJ )
{
  double sum = 0;

  for( double i = posI; i <= posJ; i++ )
  {
    sum += s[ i ].first;
  }

  for( double i = posI - 1; i <= posJ; i++ )
  {
    sum += s[ i ].second;
  }

  return sum;
}

double minProbBottom( std::vector< std::pair< double, double > > s, int numWords )
{
  std::vector< std::vector< double > > probMatrix( numWords + 2, std::vector< double >( numWords + 2, std::numeric_limits< double >::max( ) ) );

  for( unsigned int i = 1; i < probMatrix.size( ); i++ )
  {
      probMatrix[ i ][ i ] = s[ i - 1 ].second;
  }

  for( unsigned int i = probMatrix.size( ); i >= 1; i-- )
  {
      for( unsigned int j = i; j < probMatrix[ 0 ].size( ) - 1; j++ )
      {
          for( unsigned int r = i; r <= j; r++ )
          {
              double ret = probMatrix[i][r] + probMatrix[r + 1][j + 1] + getProb(s, i, j);
              if( ret < probMatrix[ i ][ j + 1 ] )
              {
                  probMatrix[ i ][ j + 1 ] = ret;
              }
          }
      }
  }

  return probMatrix[ 1 ][ numWords + 1 ];
}

double minProbMemoized( std::vector< std::pair< double, double > > s, double posI, double posJ, std::vector< std::vector< double > > &calcProbs )
{
  if( calcProbs[ posI ][ posJ ] == std::numeric_limits< double >::max( ) )
  {
    if( posJ == posI - 1 )
    {
      calcProbs[ posI ][ posJ ] = s[ posI - 1 ].second;
    }
    else
    {
      double min = std::numeric_limits<double>::max( );

      for( double i = posI; i <= posJ; i++ )
      {
        double temp = minProbMemoized( s, posI, i - 1, calcProbs ) + minProbMemoized( s, i + 1, posJ, calcProbs ) + getProb( s, posI, posJ );

        if( temp < min )
        {
          min = temp;
        }
      }

      calcProbs[ posI ][ posJ ] = min;
    }
  }

  return calcProbs[ posI ][ posJ ];
}

double minProbNaive( std::vector< std::pair< double, double > > s, double posI, double posJ )
{
  if( posJ == posI - 1 )
  {
    return s[ posI - 1 ].second;
  }
  else
  {
    double min = std::numeric_limits<double>::max( );

    for( double i = posI; i <= posJ; i++ )
    {
      double temp = minProbNaive( s, posI, i - 1 ) + minProbNaive( s, i + 1, posJ ) + getProb( s, posI, posJ );

      if( temp < min )
      {
        min = temp;
      }
    }

    return min;
  }
}

std::vector< std::vector< double > > probsMatrixInitialization( std::vector< std::vector< double > > s, double size )
{
  for( double i = 0; i < size; i++ )
  {
    for( double j = 0; j < size; j++ )
    {
      s[ i ][ j ] = std::numeric_limits<double>::max( );
    }
  }

  return s;
}

std::vector< std::pair< double, double > > fillProbsMatrix( std::vector< std::pair< double, double > > s, std::vector< std::pair< std::string, double > > histogram, double succesRatio, double failureRatio )
{
  double numWords = 0;

  for( double i = 0; i < histogram.size( ); i++ )
  {
    numWords += histogram[ i ].second;
  }

  for( double i = 0; i < histogram.size( ); i++ )
  {
    s[ i ].first = ( histogram[ i ].second / numWords ) * succesRatio;
    s[ i ].second = failureRatio / ( numWords + 1);
  }

  return s;
}

int main()
{
  double numWords = 5;
  double pf = 0.5f / ( numWords + 1 );
  std::vector< std::pair< double, double > > h( numWords + 1, std::make_pair( 0.0f, pf ) );
  h[ 1 ].first = 0.05;
  h[ 2 ].first = 0.10;
  h[ 3 ].first = 0.20;
  h[ 4 ].first = 0.05;
  h[ 5 ].first = 0.10;

  std::vector< std::vector< double > > memoizedMatrix( numWords + 2 );

  for( unsigned int i = 0; i < memoizedMatrix.size( ); i++ )
  {
    memoizedMatrix[ i ] = std::vector< double >( numWords + 2, std::numeric_limits< double >::max( ) );
  }

  std::cout << minProbNaive( h, 1, numWords ) << std::endl;
  std::cout << minProbMemoized( h, 1, numWords, memoizedMatrix ) << std::endl;
  std::cout << minProbBottom( h, numWords ) << std::endl;

  return 0;
}
