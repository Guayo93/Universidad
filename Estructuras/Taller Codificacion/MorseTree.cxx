#include "MorseTree.h"

#include <cstdlib>
#include <fstream>
#include <sstream>

// -------------------------------------------------------------------------
MorseTree::Node::
Node( )
  : m_Value( '_' ),
    m_Left( NULL ),
    m_Right( NULL )
{
}

// -------------------------------------------------------------------------
MorseTree::Node::
~Node( )
{
  if( this->m_Left != NULL )
    delete this->m_Left;
  if( this->m_Right != NULL )
    delete this->m_Right;
}

// -------------------------------------------------------------------------
bool MorseTree::Node::
IsLeaf( ) const
{
  return( this->m_Left == NULL && this->m_Right == NULL );
}

// -------------------------------------------------------------------------
void MorseTree::Node::
AddCharacter( const char& c, std::queue< char >& queue_code )
{
  // TODO #1
  // use the symbols in the queue as a route to traverse the tree
  // at the end of the route, add the character to the tree
}

// -------------------------------------------------------------------------
char MorseTree::Node::
Decode( std::queue< char >& code_queue ) const
{
  // TODO #2
  // use the symbols in the queue as a route to traverse the tree
  // at the end of the route, return the found character
}

// -------------------------------------------------------------------------
std::string MorseTree::Node::
Encode( char character ) const
{
  // TODO #3
  // traverse the tree in search of the character, keeping the route
  // when found, return the route followed to reach the character
}

// -------------------------------------------------------------------------
std::string MorseTree::Node::
PrintAsPNG( ) const
{
  std::stringstream str;

  if( this->m_Left != NULL )
  {
    str
      << ( unsigned long )( this ) << "->"
      << ( unsigned long )( this->m_Left ) << " "
      << ( unsigned long )( this )
      << " [label=" << this->m_Value << "]; "
      << ( unsigned long )( this->m_Left )
      << " [label=" << this->m_Left->m_Value << "]; "
      << this->m_Left->PrintAsPNG( );

  } // fi

  if( this->m_Right != NULL )
  {
    str
      << ( unsigned long )( this ) << "->"
      << ( unsigned long )( this->m_Right ) << " "
      << ( unsigned long )( this )
      << " [label=" << this->m_Value << "]; "
      << ( unsigned long )( this->m_Right )
      << " [label=" << this->m_Right->m_Value << "]; "
      << this->m_Right->PrintAsPNG( );

  } // fi
  return( str.str( ) );
}

// -------------------------------------------------------------------------
MorseTree::
MorseTree( )
  : m_Root( NULL )
{
}

// -------------------------------------------------------------------------
MorseTree::
~MorseTree( )
{
  this->Clear( );
}

// -------------------------------------------------------------------------
bool MorseTree::
IsValid( ) const
{
  return( this->m_Root != NULL );
}

// -------------------------------------------------------------------------
char MorseTree::
Decode( const std::string& code ) const
{
  if( this->m_Root != NULL )
  {
    std::queue< char > code_queue;
    for(
      std::string::const_iterator cIt = code.begin( );
      cIt != code.end( );
      ++cIt
      )
      code_queue.push( *cIt );
    return( this->m_Root->Decode( code_queue ) );
  }
  else
    return( '\0' );
}

// -------------------------------------------------------------------------
std::string MorseTree::
Encode( char character ) const
{
  if( this->m_Root != NULL )
    return( this->m_Root->Encode( character ) );
  else
    return( "" );
}

// -------------------------------------------------------------------------
void MorseTree::
Clear( )
{
  if( this->m_Root != NULL )
    delete this->m_Root;
}

// -------------------------------------------------------------------------
bool MorseTree::
LoadFromFile( const std::string& filename )
{
  this->Clear( );
  std::ifstream input( filename.c_str( ) );
  if( !input )
    return( false );

  while( !input.eof( ) )
  {
    char character;
    std::string code;
    input >> character >> code;
    if( code != "" )
      this->AddCharacter( character, code );

  } // elihw

  input.close( );
  return( true );
}

// -------------------------------------------------------------------------
void MorseTree::
AddCharacter( const char& c, const std::string& code )
{
  if( this->m_Root == NULL )
    this->m_Root = new Node( );

  std::queue< char > code_queue;
  for(
    std::string::const_iterator cIt = code.begin( );
    cIt != code.end( );
    ++cIt
    )
    code_queue.push( *cIt );
  this->m_Root->AddCharacter( c, code_queue );
}

// -------------------------------------------------------------------------
void MorseTree::
PrintAsPNG( const std::string& filename ) const
{
  // PrintAsPNG requires Linux package graphviz and/or graphviz-doc
  std::stringstream str;
  str << "echo \"digraph G{";
  if( this->m_Root != NULL )
  {
    if( this->m_Root->IsLeaf( ) )
      str << this->m_Root->m_Value << " ";
    else
      str << this->m_Root->PrintAsPNG( );

  } // fi
  str << "}\" | dot -Tpng > " << filename;
  std::system( str.str( ).c_str( ) );
}

// eof - MorseTree.cxx
