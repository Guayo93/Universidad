#ifndef __MAX_SUBARRAY__
#define  __MAX_SUBARRAY__

#include <vector>

struct subarray{
  int value;
  int low;
  int high;
  subarray(int low , int high, int value);
  bool operator <( const subarray& rhs ) const;
  bool operator <=( const subarray& rhs ) const;
  bool operator ==( const subarray& rhs ) const;
  bool valid();
};

subarray max_subarray_brute( std::vector<int> A );
subarray max_subarray_recursive( std::vector<int> A , int low , int high );
subarray max_cross_subarray( std::vector<int> A , int low , int high , int mid);

#include "max_subarray_algorithms.cxx"

#endif
