#include <memory>
#include <random>

#include "game.h"
#include "game_constants.h"
#include "units.h"

void Game::StartGame(){
  GenerateGoblins();
  GenerateKnights();
}

void Game::GenerateGoblins(){
    std::random_device dev{};
    std::mt19937 engine{dev()};
    std::poisson_distribution<size_t> poisson{ 2 };
    
    std::uniform_int_distribution<stats_type> x_coord_distribution{ X_MIN, X_MAX };
    std::uniform_int_distribution<stats_type> y_coord_distribution{ Y_MIN, Y_MAX };
  
    auto n_goblins = poisson(engine);

    for( size_t i=0; i<n_goblins; ++i ){
    auto x = x_coord_distribution(engine);
    auto y = y_coord_distribution(engine);
    units_.emplace_back( new Goblin({x, y}) );
    goblins_.push_back( units_.back().get() );
  }
}

void Game::GenerateKnights(){
    std::random_device dev{};
    std::mt19937 engine{dev()};
    std::poisson_distribution<size_t> poisson{ 2 };
    
    std::uniform_int_distribution<stats_type> x_coord_distribution{ X_MIN, X_MAX };
    std::uniform_int_distribution<stats_type> y_coord_distribution{ Y_MIN, Y_MAX };
  
    auto n_knights = poisson(engine);

    for( size_t i=0; i<n_knights; ++i ){
    auto x = x_coord_distribution(engine);
    auto y = y_coord_distribution(engine);
    units_.emplace_back( new Knight({x, y}) );
    knights_.push_back( units_.back().get() );
  }
}

void Game::RemoveDead(){
    knights_.clear();
    goblins_.clear();
    units_.erase(
            std::remove_if(
                units_.begin(), 
                units_.end(), 
            []( const std::unique_ptr<Unit>& unit ){ return unit->GetCurrentHealth() < 0; } ), units_.end() );
    knights_.reserve( units_.size() );
    goblins_.reserve( units_.size() );
    for( const auto& u : units_ ){
        if( u->GetType() == Unit::UNIT_TYPE::KNIGHT )
          knights_.push_back( u.get() );
        if( u->GetType() == Unit::UNIT_TYPE::GOBLIN )
          goblins_.push_back( u.get() );
    }
}