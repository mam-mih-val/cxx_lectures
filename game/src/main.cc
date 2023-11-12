#include <exception>
#include <iostream>
#include <ostream>
#include <random>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>

#include "game.h"

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    auto game = Game{};
    game.Play();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end-start;
    std::cout << "Elapsed time: " << std::chrono::duration<double, std::deca>(duration).count() << " (s)" << std::endl;
    return 0;
}