#include <iostream>
#include <random>
#include <chrono>

#include "math_vector.h"

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    
    const size_t vec_size{3};
    std::random_device rnd_dev;
    std::mt19937 rnd_engine{rnd_dev()};
    std::uniform_real_distribution<double> uniform_distribution{0, 1};

    MathVector vec1(vec_size);
    MathVector vec2(vec_size);
    for( size_t i=0; i<vec_size; i++ ){
        vec1[i] = uniform_distribution( rnd_engine );
        vec2[i] = uniform_distribution( rnd_engine );
    }

    MathVector vec3 = vec1 + vec2;
    MathVector vec4{ std::move(vec3) };
    // std::move() is just a cast to rvalue-reference
    // try to insert (const MathVector&) before the std::move(vec3)
    // or instead of std::move(vec3) paste (MathVector&&) vec3

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
    for( size_t i=0; i<vec3.Size(); ++i ){
        std::cout << vec3[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "vec4:" << std::endl;
    for( size_t i=0; i<vec4.Size(); ++i ){
        std::cout << vec4[i] << ", ";
    }
    std::cout << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end-start;
    std::cout << "Elapsed time: " << std::chrono::duration<double, std::deca>(duration).count() << " (s)" << std::endl;
    return 0;
}