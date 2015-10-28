#ifndef __OBJECTVIEW__HXX__
#define __OBJECTVIEW__HXX__

// -------------------------------------------------------------------------
template< class I >
void ObjectView::
AddCell( const I& begin, const I& end )
{
  unsigned short count = 0;
  I it = begin;
  I jt = it;
  jt++;
  for( ; it != end; ++it, ++jt, ++count )
  {
    this->m_Indices.push_back( *it );
    if( jt != end )
    {
      this->m_Adjacency[ *it ][ *jt ] = true;
      this->m_Adjacency[ *jt ][ *it ] = true;

    } // fi

  } // rof
  this->m_CellSizes.push_back( count );
}

#endif // __OBJECTVIEW__HXX__

// eof - ObjectView.hxx
