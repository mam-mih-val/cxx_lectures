#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <vector>

class MyClass1{
public:
  MyClass1() : number_{ nullptr } {}
  ~MyClass1(){ delete number_; };
  size_t* GetNumber(){ return number_; }
  void SetNumber(size_t* num){ number_ = num; }
private:
  size_t* number_;
};

class MyClass2{
public:
  MyClass2( size_t number ){ 
    auto ptr_num = new size_t(number);
    copy1_.SetNumber(ptr_num);
    copy2_.SetNumber(ptr_num);
  }
  ~MyClass2() = default;
private:
  MyClass1 copy1_;
  MyClass1 copy2_;
};


int main(){
  std::vector<MyClass2> vec_my_class;
  for( size_t i=0; i<1000; ++i ){
    vec_my_class.push_back(i*i);
  }
  return 0;
}