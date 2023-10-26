#include <exception>
#include <iostream>
#include <ostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

#include "nvi_units.h"

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    
    std::random_device rnd_dev;
    std::mt19937 rnd_engine{rnd_dev()};
    std::uniform_int_distribution<int> uniform_distribution{-10, 10};

    std::vector< std::unique_ptr<Unit> > units;
    units.emplace_back( new Knight( {uniform_distribution(rnd_engine), uniform_distribution(rnd_engine)} ) );
    units.emplace_back( new Goblin( {uniform_distribution(rnd_engine), uniform_distribution(rnd_engine)} ) );
    units.emplace_back( new Goblin( {uniform_distribution(rnd_engine), uniform_distribution(rnd_engine)} ) );

    std::vector< Unit* > alive_units;
    for( const auto& unit : units ){
        alive_units.push_back( unit.get() );
    }

    size_t round{1};
    while ( alive_units.size() > 1 ) {
        std::cout << "\n";
        std::cout << "**************************** " << "\n";
        std::cout << "Round " << round << "\n";
        std::cout << "Number of Units alive is: " << alive_units.size() << "\n";
        std::cout << "**************************** " << "\n";

        for( const auto& unit : alive_units  ){
            unit->CombatTurn( alive_units );
        }
        alive_units.erase(
            std::remove_if( 
                alive_units.begin(), 
                alive_units.end(), 
            []( Unit* unit ){ return unit->GetCurrentHealth() < 0; } ), alive_units.end() );
        round++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end-start;
    std::cout << "Elapsed time: " << std::chrono::duration<double, std::deca>(duration).count() << " (s)" << std::endl;
    return 0;
}