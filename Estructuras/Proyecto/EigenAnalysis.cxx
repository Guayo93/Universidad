#include "EigenAnalysis.h"

#include <cmath>

#define vnl_math_sgn0( x ) ( ( x >= 0 )? 1: -1 )
#define vnl_math_abs( x ) ( std::fabs( x ) )
#define vnl_math_hypot( a, b ) ( std::sqrt( ( a * a ) + ( b * b ) ) )

// -------------------------------------------------------------------------
template< typename S >
unsigned int EigenAnalysis< S >::
Compute( const S A[ 3 ][ 3 ], S eValues[ 3 ], S eVectors[ 3 ][ 3 ] )
{
  double wa1[ 3 ] = { double( 0 ) };
  double wa2[ 9 ] = { double( 0 ) };
  double M[ 9 ] = { double( 0 ) };

  // Copy the input matrix
  unsigned int k = 0;
  for( unsigned int row = 0; row < 3; row++ )
    for( unsigned int col = 0; col < 3; col++ )
      M[ k++ ] = A[ row ][ col ];

  // Compute values
  Self::_Reduce( M, eValues, wa1, wa2 );
  unsigned int err = Self::_EigenDataByQL( eValues, wa1, wa2 );

  // Copy vectors (note the transpose)
  k = 0;
  for( unsigned int row = 0; row < 3; row++ )
    for( unsigned int col = 0; col < 3; col++ )
      eVectors[ col ][ row ] = wa2[ k++ ];

  // Rotate vectors to be right handed
  double det =
    eVectors[ 0 ][ 0 ] * (
      ( eVectors[ 1 ][ 1 ] * eVectors[ 2 ][ 2 ] ) -
      ( eVectors[ 1 ][ 2 ] * eVectors[ 2 ][ 1 ] )
      );
  det -=
    eVectors[ 0 ][ 1 ] * (
      ( eVectors[ 1 ][ 0 ] * eVectors[ 2 ][ 2 ] ) -
      ( eVectors[ 1 ][ 2 ] * eVectors[ 2 ][ 0 ] )
      );
  det +=
    eVectors[ 0 ][ 2 ] * (
      ( eVectors[ 1 ][ 0 ] * eVectors[ 2 ][ 1 ] ) -
      ( eVectors[ 1 ][ 1 ] * eVectors[ 2 ][ 0 ] )
      );
  for( unsigned int d = 0; d < 3; ++d )
    eVectors[ d ][ 2 ] *= det;

  return( err );
}

// -------------------------------------------------------------------------
template< typename S >
void EigenAnalysis< S >::
_Reduce( double*  a, S d[ 3 ], double*  e, double*  z )
{
  double d__1, f, g, h, scale, hh;
  unsigned int i, j, k, l;

  for( i = 0; i < 3; ++i )
    for( j = i; j < 3; ++j )
      z[ j + ( i * 3 ) ] = a[ j + ( i * 3 ) ];
  d[ i ] = a[ 2 + ( i * 3 ) ];

  for( i = 2; i > 0; --i )
  {
    l = i - 1;
    h = double( 0 );
    scale = double( 0 );

    // scale row
    for( k = 0; k <= l; ++k )
      scale += vnl_math_abs( d[ k ] );
    if( scale == double( 0 ) )
    {
      e[ i ] = d[ l ];
      for( j = 0; j <= l; ++j )
      {
        d[ j ] = z[ l + ( j * 3 ) ];
        z[ i + ( j * 3 ) ] = double( 0 );
        z[ j + ( i * 3 ) ] = double( 0 );

      } // rof
    }
    else
    {
      for( k = 0; k <= l; ++k )
      {
        d[ k ] /= scale;
        h += d[ k ] * d[ k ];

      } // rof
      f = d[ l ];
      d__1 = std::sqrt( h );
      g = double( -1 ) * vnl_math_sgn0( f ) * vnl_math_abs( d__1 );
      e[ i ] = scale * g;
      h -= f * g;
      d[ l ] = f - g;

      // form
      for( j = 0; j <= l; ++j )
        e[ j ] = double( 0 );

      for( j = 0; j <= l; ++j )
      {
        f = d[ j ];
        z[ j + ( i * 3 ) ] = f;
        g = e[ j ] + z[ j + ( j * 3 ) ] * f;
        for( k = j + 1; k <= l; ++k )
        {
          g += z[ k + ( j * 3 ) ] * d[ k ];
          e[ k ] += z[ k + ( j * 3 ) ] * f;

        } // rof
        e[ j ] = g;

      } // rof

      // form p
      f = double( 0 );
      for( j = 0; j <= l; ++j )
      {
        e[ j ] /= h;
        f += e[ j ] * d[ j ];

      } // rof
      hh = f / ( h + h );

      // form q
      for( j = 0; j <= l; ++j )
        e[ j ] -= hh * d[ j ];

      // form reduced a
      for( j = 0; j <= l; ++j )
      {
        f = d[ j ];
        g = e[ j ];
        for( k = j; k <= l; ++k )
          z[ k + ( j * 3 ) ] =
            z[ k + ( j * 3 ) ] - ( f * e[ k ] ) - ( g * d[ k ] );
        d[ j ] = z[ l + ( j * 3 ) ];
        z[ i + ( j * 3 ) ] = double( 0 );

      } // rof

    } // fi
    d[ i ] = h;

  } // rof

  // accumulation of transformation matrices
  for( i = 1; i < 3; ++i )
  {
    l = i - 1;
    z[ 2 + ( l * 3 ) ] = z[ l + ( l * 3 )];
    z[ l + ( l * 3 ) ] = double( 1 );
    h = d[ i ];
    if( h != double( 0 ) )
    {
      for( k = 0; k <= l; ++k )
        d[ k ] = z[ k + ( i * 3 ) ] / h;

      for( j = 0; j <= l; ++j )
      {
        g = double( 0 );
        for( k = 0; k <= l; ++k )
          g += z[ k + ( i * 3 ) ] * z[ k + ( j * 3 ) ];

        for( k = 0; k <= l; ++k )
          z[ k + ( j * 3 ) ] -= g * d[ k ];

      } // rof

    } // fi

    for( k = 0; k <= l; ++k )
      z[ k + ( i * 3 ) ] = double( 0 );
    
  } // rof

  for( i = 0; i < 3; ++i )
  {
    d[ i ] = z[ 2 + ( i * 3 ) ];
    z[ 2 + ( i * 3 ) ] = double( 0 );

  } // rof
  z[ 8 ] = double( 1 );
  e[ 0 ] = double( 1 );
}

// -------------------------------------------------------------------------
template< typename S >
  unsigned int EigenAnalysis< S >::
_EigenDataByQL( S d[ 3 ], double* e, double* z )
{
  const double c_b10 = double( 1 );
  double       c, f, g, h;
  double       p, r, s, c2, c3 = double( 0 );
  double       s2 = double( 0 );
  double       dl1, el1;
  double       tst1, tst2;
  unsigned int i, j, k, l, m;
  unsigned int ierr = 0;

  for( i = 1; i < 3; ++i )
    e[ i - 1 ] = e[ i ];

  f = double( 0 );
  tst1 = double( 0 );
  e[ 2 ] = double( 0 );

  for( l = 0; l < 3; ++l )
  {
    j = 0;
    h = vnl_math_abs( d[ l ] ) + vnl_math_abs( e[ l ] );
    if( tst1 < h )
      tst1 = h;

    // look for small sub-diagonal element
    for( m = l; m < 2; ++m )
    {
      tst2 = tst1 + vnl_math_abs( e[ m ] );
      if( tst2 == tst1 )
        break;
      // e(n) is always zero, so there is no exit through the bottom
      // of the loop

    } // rof

    if( m != l )
    {
      do
      {
        if( j == 1000 )
        {
          // set error -- no convergence to an eigenvalue after 1000
          // iterations
          ierr = l + 1;
          return ierr;

        } // fi
        ++j;

        // form shift
        g = d[ l ];
        p = ( d[ l + 1 ] - g ) / ( e[ l ] * double( 2 ) );
        r = vnl_math_hypot( p, c_b10 );
        d[ l ] = e[ l ] / ( p + vnl_math_sgn0( p ) * vnl_math_abs( r ) );
        d[ l + 1 ] = e[ l ] * ( p + vnl_math_sgn0( p ) * vnl_math_abs( r ) );
        dl1 = d[ l + 1 ];
        h = g - d[ l ];

        for( i = l + 2; i < 3; ++i )
          d[ i ] -= h;
        f += h;

        // ql transformation
        p = d[ m ];
        c = double( 1 );
        c2 = c;
        el1 = e[ l + 1 ];
        s = double( 0 );

        for( i = m - 1; i >= l; --i )
        {
          c3 = c2;
          c2 = c;
          s2 = s;
          g = c * e[ i ];
          h = c * p;
          r = vnl_math_hypot( p, e[ i ] );
          e[ i + 1 ] = s * r;
          s = e[ i ] / r;
          c = p / r;
          p = c * d[ i ] - s * g;
          d[ i + 1 ] = h + s * ( c * g + s * d[ i ] );

          // form vector
          for( k = 0; k < 3; ++k )
          {
            h = z[ k + ( ( i + 1 ) * 3 ) ];
            z[ k + ( ( i + 1 ) * 3 ) ] = s * z[ k + ( i * 3 )] + c * h;
            z[ k + ( i * 3 )] = c * z[ k + ( i * 3 ) ] - s * h;

          } // rof
          if ( i == l )
            break;

        } // rof

        p = -s * s2 * c3 * el1 * e[ l ] / dl1;
        e[ l ] = s * p;
        d[ l ] = c * p;
        tst2 = tst1 + vnl_math_abs( e[ l ] );
      } while( tst2 > tst1 );

    } // fi
    d[ l ] += f;

  } // rof

  // order eigenvalues and eigenvectors
  for( i = 0; i < 2; ++i )
  {
    k = i;
    p = d[ i ];
    for( j = i + 1; j < 3; ++j )
    {
      if( d[ j ] >= p )
        continue;
      k = j;
      p = d[ j ];

    } // rof

    if ( k == i )
      continue;
    d[ k ] = d[ i ];
    d[ i ] = p;

    for( j = 0; j < 3; ++j )
    {
      p = z[ j + ( i * 3 ) ];
      z[ j + ( i * 3 ) ] = z[ j + ( k * 3 ) ];
      z[ j + ( k * 3 ) ] = p;

    } // rof

  } // rof
  return( ierr );
}

// -------------------------------------------------------------------------
template class EigenAnalysis< float >;
template class EigenAnalysis< double >;

// eof - EigenAnalysis.cxx
