#include <exception>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

#include "polymorphic_table.h"

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    
    std::random_device rnd_dev;
    std::mt19937 rnd_engine{rnd_dev()};
    std::uniform_real_distribution<double> uniform_distribution{-10, 10};

    auto data = TableType<double, 3>{};
    data.reserve(10);

    // Filling the table contents
    for( size_t i=0; i<10; ++i ){
        auto x = uniform_distribution( rnd_engine );
        auto y = uniform_distribution( rnd_engine );
        auto z = uniform_distribution( rnd_engine );
        data.push_back( {x, y, z} );
    }

    // Constructing the table
    auto table = MagnitudeClassifier<double, 3>( data );
    // Printing the table
    for( size_t i=0; i<table.NEntries(); ++i ){
        auto [x, y, z] = table[i];
        std::cout << std::setprecision(2) << "x=" << x << " y=" << y << " z=" << z << " class=" << table.Classification(i) << "\n"; 
    }
    std::cout << "\n"; 

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end-start;
    std::cout << "Elapsed time: " << std::chrono::duration<double, std::deca>(duration).count() << " (s)" << std::endl;
    return 0;
}