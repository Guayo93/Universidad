#include "ObjectView.h"
#include <cstdarg>
#include <vector>
#include <GL/gl.h>

// -------------------------------------------------------------------------
ObjectView::
ObjectView( )
{
  this->m_Shininess = float( 15 );
  this->m_DiffuseColor[ 0 ] = float( 0.929524 );
  this->m_DiffuseColor[ 1 ] = float( 0.796542 );
  this->m_DiffuseColor[ 2 ] = float( 0.178823 );
  this->m_SpecularColor[ 0 ] = float( 1 );
  this->m_SpecularColor[ 1 ] = float( 0.980392 );
  this->m_SpecularColor[ 2 ] = float( 0.549020 );
  this->m_SpecularColor[ 3 ] = float( 1 );

  this->m_MinX = this->m_MaxX = float( 0 );
  this->m_MinY = this->m_MaxY = float( 0 );
  this->m_MinZ = this->m_MaxZ = float( 0 );

  this->ClearVertices( );
  this->ClearCells( );
}

// -------------------------------------------------------------------------
ObjectView::
~ObjectView( )
{
}

// -------------------------------------------------------------------------
void ObjectView::
SetColor( float r, float g, float b )
{
  this->m_DiffuseColor[ 0 ] = r;
  this->m_DiffuseColor[ 1 ] = g;
  this->m_DiffuseColor[ 2 ] = b;
}

// -------------------------------------------------------------------------
const float& ObjectView::GetMinX( ) const
{
  return( this->m_MinX );
}

// -------------------------------------------------------------------------
const float& ObjectView::
GetMinY( ) const
{
  return( this->m_MinY );
}

// -------------------------------------------------------------------------
const float& ObjectView::
GetMinZ( ) const
{
  return( this->m_MinZ );
}

// -------------------------------------------------------------------------
const float& ObjectView::
GetMaxX( ) const
{
  return( this->m_MaxX );
}

// -------------------------------------------------------------------------
const float& ObjectView::
GetMaxY( ) const
{
  return( this->m_MaxY );
}

// -------------------------------------------------------------------------
const float& ObjectView::
GetMaxZ( ) const
{
  return( this->m_MaxZ );
}

// -------------------------------------------------------------------------
void ObjectView::
ClearVertices( )
{
  this->m_Vertices.clear( );
}

// -------------------------------------------------------------------------
void ObjectView::
AddVertex( const float& x, const float& y, const float& z )
{
  this->m_Vertices.push_back( x );
  this->m_Vertices.push_back( y );
  this->m_Vertices.push_back( z );

  if( this->m_Vertices.size( ) > 3 )
  {
    this->m_MinX = ( x < this->m_MinX )? x: this->m_MinX;
    this->m_MinY = ( y < this->m_MinY )? y: this->m_MinY;
    this->m_MinZ = ( z < this->m_MinZ )? z: this->m_MinZ;

    this->m_MaxX = ( x > this->m_MaxX )? x: this->m_MaxX;
    this->m_MaxY = ( y > this->m_MaxY )? y: this->m_MaxY;
    this->m_MaxZ = ( z > this->m_MaxZ )? z: this->m_MaxZ;
  }
  else
  {
    this->m_MinX = this->m_MaxX = x;
    this->m_MinY = this->m_MaxY = y;
    this->m_MinZ = this->m_MaxZ = z;

  } // fi
}

// -------------------------------------------------------------------------
void ObjectView::
ClearCells( )
{
  this->m_Indices.clear( );
  this->m_CellSizes.clear( );
  this->m_Adjacency.clear( );
}

// -------------------------------------------------------------------------
void ObjectView::
AddCell( const unsigned int& size, ... )
{
  va_list vl;
  va_start( vl, size );
  std::vector< unsigned short > f( size );
  for( unsigned int i = 0; i < size; ++i )
    f[ i ] = ( unsigned short )( va_arg( vl, int ) );
  this->AddCell( f.begin( ), f.end( ) );
  va_end( vl );
}

// -------------------------------------------------------------------------
void ObjectView::
Draw( )
{
  glColor3fv( this->m_DiffuseColor );

  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, this->m_Vertices.data( ) );

  unsigned short j = 0;
  for( unsigned short i = 0; i < this->m_CellSizes.size( ); ++i )
  {
    GLsizei cell_size = this->m_CellSizes[ i ];
    if( cell_size > 0 )
    {
      GLenum mode;
      if     ( cell_size == 1 ) mode = GL_POINTS;
      else if( cell_size == 2 ) mode = GL_LINES;
      else if( cell_size == 3 ) mode = GL_TRIANGLES;
      else if( cell_size >  3 ) mode = GL_POLYGON;
      glDrawElements(
        mode, cell_size, GL_UNSIGNED_SHORT, &( this->m_Indices[ j ] )
        );
      j += cell_size;

    } // fi

  } // rof
  glDisableClientState( GL_VERTEX_ARRAY );
}

// eof - ObjectView.cxx
