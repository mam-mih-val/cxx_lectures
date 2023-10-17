#include <exception>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>

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

    std::vector<MathVector<double, 3>> math_vectors;
    math_vectors.push_back(vec1);
    math_vectors.push_back(vec2);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end-start;
    std::cout << "Elapsed time: " << std::chrono::duration<double, std::deca>(duration).count() << " (s)" << std::endl;
    return 0;
}