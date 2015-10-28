#include <iostream>
#include <locale>
#include <string>
#include <sstream>

#include "MorseTree.h"

int main( int argc, char* argv[] )
{
  MorseTree tree;
  std::string command;
  do
  {
    // Get command line
    std::string line = "";
    std::cout << "> ";
    std::cout.flush( );
    std::getline( std::cin, line );

    // Tokenize command line
    std::istringstream command_tokenizer( line );

    // Get command
    command_tokenizer >> command;
    if( command == "load" )
    {
      std::string filename;
      command_tokenizer >> filename;
      if( tree.LoadFromFile( filename ) )
        // PrintAsPNG requires Linux package graphviz and/or graphviz-doc
        tree.PrintAsPNG( "loaded_baudot_tree.png" );
      else
        std::cerr << "Error loading \"" << filename << "\"" << std::endl;
    }
    else if( command == "encode" )
    {
      if( tree.IsValid( ) )
      {
        while( !( command_tokenizer.eof( ) ) )
        {
          std::string token;
          command_tokenizer >> token;
          for(
            std::string::const_iterator tIt = token.begin( );
            tIt != token.end( );
            ++tIt
            )
            std::cout << tree.Encode( std::toupper( *tIt ) ) << " ";
          std::cout << std::endl;

        } // elihw
      }
      else
        std::cerr << "No tree loaded." << std::endl;
    }
    else if( command == "decode" )
    {
      if( tree.IsValid( ) )
      {
        while( !( command_tokenizer.eof( ) ) )
        {
          std::string token;
          command_tokenizer >> token;
          std::cout << tree.Decode( token );

        } // elihw
        std::cout << " ";
      }
      else
        std::cerr << "No tree loaded.";
      std::cout << std::endl;
    }
    else if( command == "exit" )
    {
      // Do nothing
    }
    else
      std::cerr << "Unknown command \"" << command << "\"" << std::endl;

  } while( command != "exit" );
  return( 0 );
}

// eof - taller_4_codificacion.cxx
