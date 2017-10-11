#include <iostream>
#include <string>
#include <vector>

std::string Palindrome( std::string S ){
  int max_size = 1;
  int max_pos = 0;
  int s = S.size();
  std::vector<std::vector<int> > M(s, std::vector<int>(s,-1));
  for( int i = 0 ; i < s ; i++ ){
    M[i][i] = 1;
  }
  for( int currLen = 2 ; currLen <= s ; currLen ++ ){
    if ( currLen == 2){
      for (int i = 0; i < s-1; i++) {
        if (S[i] == S[i+1]) {
          M[i][i+1] = 2;
          max_pos = i;
          max_size = 2;
        }
      }
    }else{
      for( int i = 0 ; i < s-currLen+1 ; i++ ){
        int j = i+currLen-1;
        if ( S[i] == S[j] && M[i+1][j-1] != -1 ) {
          M[i][j] = currLen;
          max_pos = i;
          max_size = currLen;
        }
      }
    }
  }
  return S.substr(max_pos,max_size);
}


int main(int argc, char const *argv[]) {
  std::cout << Palindrome("ABCCCACCHG") << std::endl;
  std::cout << Palindrome("BABABA") << std::endl;
  std::cout << Palindrome("BABA") << std::endl;
  std::cout << Palindrome("ABCDFG") << std::endl;
  return 0;
}
