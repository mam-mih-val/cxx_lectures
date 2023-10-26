#ifndef _MATH_VECTOR_H_
#define _MATH_VECTOR_H_

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cassert>
#include <exception>
#include <initializer_list>
#include <math.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>

template<class Derived>
class Logger{
    Logger(){ std::cout << "Constructed " << typeid(Derived).name() << std::endl; }
    ~Logger(){ std::cout << "Destructed " << typeid(Derived).name() << std::endl; }
    
    bool operator!=( Logger<Derived> other ){ ! dynamic_cast<Derived>(this)->operator==(other); }
    bool operator<( Logger<Derived> other ){ ! dynamic_cast<Derived>(this)->operator>(other); }
    static size_t number_of_copyies_;
    size_t id_;
};


class Unit{ 
    virtual void Attack(){ }
};

class Knight : public Unit, Logger<Knight> { 
    Knight(  ) : Logger<Knight> {}
    ~Knight(  ) : Logger<Knight> {}
    void Attack() override {  }
};

class Goblin : public Unit, Logger<Goblin> { 
    Goblin(  ) : Logger<Knight> {}
    ~Goblin(  ) : Logger<Knight> {}
    void Attack() override {  }
};

Unit<Knignt>* p = new Knight;
p->Attack();


#endif // _MATH_VECTOR_H_