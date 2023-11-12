#ifndef _VISUALIZER_H_
#define _VISUALIZER_H_

#include "units.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <vector>
#include <iostream>

#include "game_constants.h"

constexpr size_t DIMENSIONS_X = X_MAX+1;
constexpr size_t DIMENSIONS_Y = Y_MAX+1;

class FieldState{
public:
  FieldState() = default;
  ~FieldState() = default;
  FieldState& SetKnightPos( std::array<size_t, 2> pos ){ 
    knight_pos_ = std::move( pos );
    return *this;
  }
  FieldState& SetVecGoblinPos( std::vector<std::array<size_t, 2>> vec_pos ){ 
    vec_goblin_pos_ = std::move( vec_pos );
    return *this;
  }
  const std::array<size_t, 2>& GetKnightPos(){ return knight_pos_; }
  const std::vector<std::array<size_t, 2>>& GetVecGoblinPos(){ return vec_goblin_pos_; }
private:
  std::array<size_t, 2> knight_pos_{};
  std::vector<std::array<size_t, 2>> vec_goblin_pos_{}; 
};

class Visualizer{
public:
  Visualizer() = default;
  ~Visualizer() = default;
  void Update(  std::vector<Unit*> units ){
    Clear();
    for( auto u : units ){
      DrawCharacter(u);
    }
    Print();
  }
private:
  void Clear(){
    [[maybe_unused]] auto ret_val =  system("clear");
    for( auto& line : field_ ){
      line.fill( ' ' );
    }
  }
  void Print(){
    for( size_t y = 0; y < DIMENSIONS_Y; ++y ){
      for( size_t x = 0; x < DIMENSIONS_X; ++x ){
        std::cout << field_.at(y).at(x);
      }
      std::cout << "\n";
    }
  }
  void DrawCharacter( Unit* u ){
    auto [x, y] = u->GetPosition();
    if( u->GetCurrentHealth() < 0 ){
      field_.at(y).at(x) = 'x';
      return;
    }
    if( u->GetType() == Unit::UNIT_TYPE::KNIGHT )
      field_.at(y).at(x) = 'k';
    if( u->GetType() == Unit::UNIT_TYPE::GOBLIN )
      field_.at(y).at(x) = 'g';
  }
  std::array< std::array<char, DIMENSIONS_X>, DIMENSIONS_Y > field_{};
};

#endif // _VISUALIZER_H_