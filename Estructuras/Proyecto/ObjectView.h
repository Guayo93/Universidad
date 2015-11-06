#ifndef __OBJECTVIEW__H__
#define __OBJECTVIEW__H__

#include <map>
#include <vector>

/**
 */
class ObjectView
{
public:
  ObjectView( );
  virtual ~ObjectView( );

  void SetColor( float r, float g, float b );

  const float& GetMinX( ) const;
  const float& GetMinY( ) const;
  const float& GetMinZ( ) const;
  const float& GetMaxX( ) const;
  const float& GetMaxY( ) const;
  const float& GetMaxZ( ) const;

  void ClearVertices( );
  void AddVertex( const float& x, const float& y, const float& z );
  void ClearCells( );

  template< class I >
  void AddCell( const I& begin, const I& end );

  void AddCell( const unsigned int& size, ... );

  void Draw( );

protected:
  std::vector< float > m_Vertices;
  std::vector< unsigned short > m_Indices;
  std::vector< unsigned short > m_CellSizes;

  typedef std::map< unsigned short, bool >    TAdjRow;
  typedef std::map< unsigned short, TAdjRow > TAdjMatrix;
  TAdjMatrix m_Adjacency;

  float m_Shininess;
  float m_DiffuseColor[ 3 ];
  float m_SpecularColor[ 4 ];

  float m_MinX, m_MaxX;
  float m_MinY, m_MaxY;
  float m_MinZ, m_MaxZ;
};

#include "ObjectView.hxx"

#endif // __OBJECTVIEW__H__

// eof - ObjectView.h
