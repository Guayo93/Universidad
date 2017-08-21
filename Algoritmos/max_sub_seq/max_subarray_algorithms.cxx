#include "max_subarray_algorithms.h"
#include <limits>

subarray::subarray(int low , int high, int value){
  this->high = high;
  this->low = low;
  this->value = value;
}

bool subarray::operator <( const subarray& rhs ) const
{
  return (this->value < rhs.value);
}

bool subarray::operator <=( const subarray& rhs ) const
{
  return (this->value <= rhs.value);
}

bool subarray::operator ==( const subarray& rhs ) const
{
  return ( (this->value == rhs.value) && (this->low == rhs.low) && (this->high == rhs.high) );
}

bool subarray::valid(){
  return (this->low < this->high);
}

subarray max_subarray_recursive( std::vector<int> A , int low , int high )
{
  if( high <= low ){
    subarray sub(low,high,A[low]);
    return sub;
  }else{
    int mid = (low + high)/2;
    subarray lm = max_subarray_recursive(A , low , mid);
    subarray mh = max_subarray_recursive(A , mid+1 , high);
    subarray cross = max_cross_subarray(A , low , high , mid );
    if( mh < lm && cross < lm ){
      return lm;
    }
    if( lm < mh && cross < mh){
      return mh;
    }
    if( lm < cross && mh < cross){
      return cross;
    }
  }
}

subarray max_cross_subarray( std::vector<int> A , int low , int high , int mid )
{
  int vl = std::numeric_limits<int>::min();
  int s = 0;
  int ml;
  for( int i = mid ; i >= low ; i-- ){
    s += A[i];
    if( s > vl ){
      vl = s;
      ml = i;
    }
  }
  int vr = std::numeric_limits<int>::min();
  s = 0;
  int mr;
  for( int i = mid+1 ; i <= high ; i++ ){
    s += A[i];
    if( s > vr ){
      vr = s;
      mr = i;
    }
  }
  subarray subarr( ml , mr , vl + vr );
  return subarr;
}
