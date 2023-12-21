#include <functional>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<float> SortArray( std::vector<float> vec ){
  for( size_t i=0; i<vec.size() - 1; ++i ){
    for( size_t ii=0; ii<vec.size() - 1 - i; ++ii ){
      if( vec[ii] > vec[ii+1] ){
        auto tmp = vec[ii+1];
        vec[ii+1] = vec[ii];
        vec[ii] = tmp; 
      }
    }
  }
  return vec;
}

std::vector<double> SortArray( std::vector<double> vec ){
  for( size_t i=0; i<vec.size() - 1; ++i ){
    for( size_t ii=0; ii<vec.size() - 1 - i; ++ii ){
      if( vec[ii] > vec[ii+1] ){
        auto tmp = vec[ii+1];
        vec[ii+1] = vec[ii];
        vec[ii] = tmp; 
      }
    }
  }
  return vec;
}

int main(){
  std::vector<float> vec{ 3, 5, 1, 9, 6, 5, 3, 4 };
  std::sort( vec.begin(), vec.end(), std::greater<float>() );
  float arr[] = { 3.f, 5.f, 1.f, 9.f, 6.f, 5.f, 3.f, 4.f };
  vec = SortArray(vec);
  // arr = SortArray(arr, 7);
  for( auto num : vec ){
    std::cout << num << " ";
  }
  std::cout << std::endl;

  return 0;
}