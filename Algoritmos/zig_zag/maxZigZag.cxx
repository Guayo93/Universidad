#include <iostream>
#include <queue>
#include <climits>

int maxZigZag( int s[ ], int n )
{
  int max = INT_MIN, maxIndex = INT_MIN;

  int** difference = new int* [ n ];
  for( int i = 0; i < n;  i++ )
  {
    difference[ i ] = new int [ 2 ];
  }

  std::queue< int > r[ n ];

  for( int i = 0; i < n; i++ )
  {
    difference[ i ][ 0 ] = 1;
    difference[ 0 ][ i ] = 1;

    for( int j = 0; j < i; j++ )
    {
      if( s[ i ] > s[ j ] )
      {
        difference[ i ][ 0 ] = std::max( difference[ j ][ 1 ] + 1, difference[ i ][ 0 ] );
        r[ i ].push( s[ j ] );
      }
      else if( s[ i ] < s[ j ] )
      {
        difference[ i ][ 1 ] = std::max( difference[ j ][ 0 ] + 1, difference[ i ][ 1 ] );
        r[ i ].push( s[ j ] );
      }
    }

    r[ i ].push( s[ i ] );
  }

  for( int i = 0; i < n; i++ )
  {
    if( max < difference[ i ][ 0 ] )
    {
      max = difference[ i ][ 0 ];
      maxIndex = i;
    }

    if( max < difference[ i ][ 1 ] )
    {
      max = difference[ i ][ 1 ];
      maxIndex = i;
    }
  }

  while( !r[ maxIndex ].empty( ) )
  {
    std::cout << r[ maxIndex ].front( ) << " ";
    r[ maxIndex ].pop( );
  }

  return max;
}

int main( )
{
  int s[ ] = { 1, 7, 4, 9, 2, 5 }, n = 6;
  std::cout << "MaxZigZag: " << maxZigZag( s, n ) << std::endl;
  return 0;
}
