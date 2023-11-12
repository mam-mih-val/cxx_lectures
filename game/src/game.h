#ifndef _GAME_H_
#define _GAME_H_

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "units.h"
#include "visualizer.h"

class Game{
public:
    Game() = default;
    ~Game() = default;

    void Play(){
      StartGame();
      size_t round{};
      
      while ( goblins_.size() > 0 && knights_.size() > 0 ) {
        auto alive_units = knights_;
        alive_units.insert( alive_units.end(), goblins_.begin(), goblins_.end() );
        
        visualizer.Update(alive_units);

        std::cout << "\n";
        std::cout << "**************************** " << "\n";
        std::cout << "Round " << round << "\n";
        std::cout << "Number of Units alive is: " << alive_units.size() << "\n";
        std::cout << "**************************** " << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds( 1000 ));
        for( const auto& unit : alive_units  ){
            visualizer.Update(alive_units);
            if( unit->GetType() == Unit::UNIT_TYPE::KNIGHT ){
              unit->CombatTurn( goblins_ );
            }
            if( unit->GetType() == Unit::UNIT_TYPE::GOBLIN ){
              unit->CombatTurn( knights_ );
            }
            std::this_thread::sleep_for(std::chrono::milliseconds( 1000 ));
        }

        RemoveDead();
        // GenerateKnights();
        // GenerateGoblins();
      }
    }
  
private:
    void StartGame();
    void GenerateGoblins();
    void GenerateKnights();
    void RemoveDead();

    std::vector<std::unique_ptr<Unit>> units_{};
    std::vector<Unit*> knights_{};
    std::vector<Unit*> goblins_{};
    Visualizer visualizer{};
};

#endif // _GAME_H_