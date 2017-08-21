#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <chrono>
#include "max_subarray_algorithms.h"

subarray bruteForce( std::vector<int> vec )
{
  subarray maxSubSeq( 0, 0, std::numeric_limits< int >::min() );

  for( int i = 0; i < vec.size( ); i++ )
  {
    int partialSum = vec[ i ];
    int j = i+1;
    bool flag = true;

    while( flag && j < vec.size( ) )
    {
      if(vec[ j ] >= vec[ i ])
      {
        partialSum += vec[ j ];
      }
      else
      {
        flag = false;
      }

      j++;
    }

    if( partialSum > maxSubSeq.value )
    {
      maxSubSeq.low = i;
      maxSubSeq.high = j-1;
      maxSubSeq.value = partialSum;
    }
  }

  return maxSubSeq;
}

int main(int argc, char const *argv[])
{
  srand( time( NULL ) );

  if( argc != 2 )
  {
    std::cerr << "Error: Usage " << argv[0] << " [n elements in array]" << std::endl;
    return -1;
  }

  int n = std::atoi(argv[1]);
  std::vector<int> v(n , 0);

  for( int i = 0 ; i < n ; i++ )
  {
    v[i] = std::rand() % 100;
    if( std::rand() % 2 == 0 )
    {
      v[i] *= -1;
    }
  }

  long inicioBrute = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now(  ).time_since_epoch(  ) ).count( );
  subarray sa = bruteForce( v );
  long finBrute = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );

  long inicioDC = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now(  ).time_since_epoch(  ) ).count( );
  subarray sb = max_subarray_recursive( v, 0, n-1 );
  long finDC = std::chrono::duration_cast< std::chrono::milliseconds > ( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );

  std::cout << finBrute - inicioBrute << " " << sa.low << " " << sa.high << " " << sa.value << " " << finDC - inicioDC << " "<< sb.low << " " << sb.high << " " << sb.value << std::endl;

  return( 0 );
}
