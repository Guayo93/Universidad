#ifndef __VIEW__HXX__
#define __VIEW__HXX__

#include <cmath>

// -------------------------------------------------------------------------
template< class TVector >
ObjectView* View::
AddBoundingBox( const TVector& min, const TVector& max, 
  const float& r, const float& g, const float& b )
{
  ObjectView* bb = new ObjectView( );
  bb->AddVertex( min[ 0 ], min[ 1 ], min[ 2 ] );
  bb->AddVertex( min[ 0 ], min[ 1 ], max[ 2 ] );
  bb->AddVertex( max[ 0 ], min[ 1 ], max[ 2 ] );
  bb->AddVertex( max[ 0 ], min[ 1 ], min[ 2 ] );
  bb->AddVertex( min[ 0 ], max[ 1 ], min[ 2 ] );
  bb->AddVertex( min[ 0 ], max[ 1 ], max[ 2 ] );
  bb->AddVertex( max[ 0 ], max[ 1 ], max[ 2 ] );
  bb->AddVertex( max[ 0 ], max[ 1 ], min[ 2 ] );
  bb->AddCell( 4, 3, 2, 1, 0 );
  bb->AddCell( 4, 4, 5, 6, 7 );
  bb->AddCell( 4, 1, 2, 6, 5 );
  bb->AddCell( 4, 0, 4, 7, 3 );
  bb->AddCell( 4, 1, 5, 4, 0 );
  bb->AddCell( 4, 2, 3, 7, 6 );

  View::AddObject( bb, r, g, b );
  return( bb );
}

// -------------------------------------------------------------------------
template< class TVector >
ObjectView* View::
AddOrientedBoundingBox( TVector pnts[ 8 ], 
  const float& r, const float& g, const float& b )
{
  ObjectView* bb = new ObjectView( );
  bb->AddVertex( pnts[ 0 ][ 0 ], pnts[ 0 ][ 1 ], pnts[ 0 ][ 2 ] );
  bb->AddVertex( pnts[ 1 ][ 0 ], pnts[ 1 ][ 1 ], pnts[ 1 ][ 2 ] );
  bb->AddVertex( pnts[ 2 ][ 0 ], pnts[ 2 ][ 1 ], pnts[ 2 ][ 2 ] );
  bb->AddVertex( pnts[ 3 ][ 0 ], pnts[ 3 ][ 1 ], pnts[ 3 ][ 2 ] );
  bb->AddVertex( pnts[ 4 ][ 0 ], pnts[ 4 ][ 1 ], pnts[ 4 ][ 2 ] );
  bb->AddVertex( pnts[ 5 ][ 0 ], pnts[ 5 ][ 1 ], pnts[ 5 ][ 2 ] );
  bb->AddVertex( pnts[ 6 ][ 0 ], pnts[ 6 ][ 1 ], pnts[ 6 ][ 2 ] );
  bb->AddVertex( pnts[ 7 ][ 0 ], pnts[ 7 ][ 1 ], pnts[ 7 ][ 2 ] );
  bb->AddCell( 4, 3, 2, 1, 0 );
  bb->AddCell( 4, 4, 5, 6, 7 );
  bb->AddCell( 4, 1, 2, 6, 5 );
  bb->AddCell( 4, 0, 4, 7, 3 );
  bb->AddCell( 4, 1, 5, 4, 0 );
  bb->AddCell( 4, 2, 3, 7, 6 );

  View::AddObject( bb, r, g, b );
  return( bb );
}

// -------------------------------------------------------------------------
template< class TMatrix, class TVector >
ObjectView* View::
AddEllipsoid( const TMatrix& pm, const TVector& mean, const TVector& radii, 
  const float& r, const float& g, const float& b )
{
  ObjectView* sphere = new ObjectView( );

  float Pi = float( 3.141592 );
  float _2Pi = float( 2 ) * Pi;
  int M = 20;
  int N = 20;
  float _2PiN = _2Pi / float( N );
  int nVerts = 0;
  for( unsigned int m = 0; m < M; ++m )
  {
    float vm = Pi * float( m ) / M;
    float sm = std::sin( vm );
    float cm = std::cos( vm );
    for( unsigned int n = 0; n < N; ++n )
    {
      float x = float( radii[ 0 ] ) * sm * std::cos( _2PiN * float( n ) );
      float y = float( radii[ 1 ] ) * sm * std::sin( _2PiN * float( n ) );
      float z = float( radii[ 2 ] ) * cm;
      float rx =
        ( pm[ 0 ][ 0 ] * x ) + ( pm[ 0 ][ 1 ] * y ) + ( pm[ 0 ][ 2 ] * z );
      float ry =
        ( pm[ 1 ][ 0 ] * x ) + ( pm[ 1 ][ 1 ] * y ) + ( pm[ 1 ][ 2 ] * z );
      float rz =
        ( pm[ 2 ][ 0 ] * x ) + ( pm[ 2 ][ 1 ] * y ) + ( pm[ 2 ][ 2 ] * z );
      sphere->AddVertex(
        rx + float( mean[ 0 ] ),
        ry + float( mean[ 1 ] ),
        rz + float( mean[ 2 ] )
        );
      nVerts++;
      if( nVerts > 1 )
        sphere->AddCell( 2, nVerts - 2, nVerts - 1 );
      if( m > 0 )
        sphere->AddCell( 2, nVerts - N - 1, nVerts - 1 );

    } // rof

  } // rof

  View::AddObject( sphere, r, g, b );
  return( sphere );
}

// -------------------------------------------------------------------------
template< class TVector >
ObjectView* View::
AddSphere( const TVector& mean, const double& radii, 
  const float& r, const float& g, const float& b )
{
  double pm[ 3 ][ 3 ], rad[ 3 ];

  pm[ 0 ][ 0 ] = 1.0; pm[ 0 ][ 1 ] = 0.0; pm[ 0 ][ 2 ] = 0.0;
  pm[ 1 ][ 0 ] = 0.0; pm[ 1 ][ 1 ] = 1.0; pm[ 1 ][ 2 ] = 0.0;
  pm[ 2 ][ 0 ] = 0.0; pm[ 2 ][ 1 ] = 0.0; pm[ 2 ][ 2 ] = 1.0;

  rad[ 0 ] = radii;
  rad[ 1 ] = radii;
  rad[ 2 ] = radii;

  ObjectView* sphere = View::AddEllipsoid( pm, mean, rad, r, g, b );
  return( sphere );
}


#endif // __VIEW__HXX__

// eof - View.hxx
