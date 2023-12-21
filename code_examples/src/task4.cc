#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <vector>

size_t fibb(size_t n){
  if( n == 0 )
    return 1;
  if( n == 1 )
    return 1;
  return fibb( n-1 ) + fibb( n-2 );
}

class MyClass{
public:
  MyClass( size_t number ) : number_{ new size_t{ number } } {}
  ~MyClass(){ delete number_; };
  size_t* GetNumber(){ return number_; }
private:
  size_t* number_;
};

int main(){
  MyClass extra_class{0};
  // some code
  {
    std::vector<MyClass> vec_my_class;
    for( int i=0; i<1000; ++i ){
      vec_my_class.push_back( fibb(i) );
    }
    extra_class = vec_my_class.at(101);
  }
  std::cout << *extra_class.GetNumber() << std::endl;
  return 0;
}