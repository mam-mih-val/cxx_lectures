#include <stdexcept>
#include <iostream>

int DoSomething( int idx ){
  auto array = new int[10];
  // some calculations
  if( idx >= 10 ){
    throw std::runtime_error{"Index is out of range"};
  }
  auto result = array[idx];
  delete [] array;
  return result;
}

int main(){
  for( int i=0; i<50; ++i ) try {
    auto result = DoSomething(i);
    std::cout << result << std::endl;
  } catch( const std::runtime_error& e){
    std::cout << "Catched an error: " << e.what() << std::endl;
  }
  return 0;
}