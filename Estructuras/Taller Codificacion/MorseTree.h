#ifndef __MORSETREE__H__
#define __MORSETREE__H__

#include <queue>
#include <string>

class MorseTree
{
protected:

  class Node
  {
  public:
    Node( );
    virtual ~Node( );

    bool IsLeaf( ) const;
    
    void AddCharacter( const char& c, std::queue< char >& queue_code );

    char Decode( std::queue< char >& code_queue ) const;
    std::string Encode( char character ) const;

    std::string PrintAsPNG( ) const;

  public:
    char m_Value;
    Node* m_Left;
    Node* m_Right;
  };

public:
  MorseTree( );
  virtual ~MorseTree( );

  bool IsValid( ) const;
  char Decode( const std::string& code ) const;
  std::string Encode( char character ) const;

  void Clear( );
  bool LoadFromFile( const std::string& filename );
  void AddCharacter( const char& c, const std::string& code );

  void PrintAsPNG( const std::string& filename ) const;

protected:
  Node* m_Root;
};


#endif // __MORSETREE__H__

// eof - MorseTree.h
