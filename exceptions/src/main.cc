#include <exception>
#include <iostream>
#include <random>
#include <chrono>

#include "math_vector.h"

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    
    constexpr size_t vec_size{3};
    std::random_device rnd_dev;
    std::mt19937 rnd_engine{rnd_dev()};
    std::uniform_real_distribution<double> uniform_distribution{0, 10};

    MathVector<double, vec_size> vec1;
    MathVector<double, vec_size> vec2;
    for( size_t i=0; i<vec_size; i++ ){
        vec1[i] = uniform_distribution( rnd_engine );
        vec2[i] = uniform_distribution( rnd_engine );
    }

    auto vec3 = vec1 + vec2;

    std::cout << "vec1:" << std::endl;
    for( size_t i=0; i<vec1.Size(); ++i ){
        std::cout << vec1[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "vec2:" << std::endl;
    for( size_t i=0; i<vec2.Size(); ++i ){
        std::cout << vec2[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "vec3:" << std::endl;
    for( size_t i=0; i<4; ++i ) {
        std::cout << vec3[i] << ", ";
    }
    std::cout << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end-start;
    std::cout << "Elapsed time: " << std::chrono::duration<double, std::deca>(duration).count() << " (s)" << std::endl;
    return 0;
}