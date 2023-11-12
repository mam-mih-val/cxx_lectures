#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cassert>
#include <exception>
#include <initializer_list>
#include <math.h>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>

#include "units.h"

size_t Unit::n_units_ = 0;

const std::string KNIGHT_NAME = "Knight";
constexpr stats_type KNIGHT_MAX_HEALTH = 55;
constexpr stats_type KNIGHT_HEALING_HEALTH = 40;
constexpr stats_type KNIGHT_HEALING_AMOUNT = 10;
constexpr stats_type KNIGHT_CRITICAL_HEALTH = 15;
constexpr stats_type KNIGHT_STRENGTH = 12;
constexpr stats_type KNIGHT_RANGE = 2;
constexpr stats_type KNIGHT_SHIELD_DURABILITY = 5;
constexpr stats_type KNIGHT_RETREAT_SPEED = 1;
constexpr stats_type KNIGHT_MOVE_SPEED = 4;
constexpr stats_type KNIGHT_BLOCK_CHANCE = 50;
constexpr stats_type KNIGHT_MISS_CHANCE = 30;


const std::string GOBLIN_NAME = "Goblin";
const stats_type GOBLIN_MAX_HEALTH = 40;
const stats_type GOBLIN_CRITICAL_HEALTH = 20;
const stats_type GOBLIN_MISS_CHANCE = 60;
const stats_type GOBLIN_STRENGTH = 10;
const stats_type GOBLIN_RANGE = 1;
const stats_type GOBLIN_RETREAT_SPEED = 4;
const stats_type GOBLIN_MOVE_SPEED = 2;



double Distance( Unit* unit1, Unit* unit2 ){
    auto x1 = unit1->GetPosition().at(0);
    auto y1 = unit1->GetPosition().at(1);
    
    auto x2 = unit2->GetPosition().at(0);
    auto y2 = unit2->GetPosition().at(1);
    
    auto dx = x1 - x2;
    auto dy = y1 - y2;
    auto distance = sqrt( dx*dx + dy*dy );
    return distance;
}

// Unit vector pointing from the first unit towards the second one
pos_type Direction( Unit* unit1, Unit* unit2 ){
    auto x1 = unit1->GetPosition().at(0);
    auto y1 = unit1->GetPosition().at(1);
    
    auto x2 = unit2->GetPosition().at(0);
    auto y2 = unit2->GetPosition().at(1);
    
    auto dx = x2 - x1;
    auto dy = y2 - y1;

    auto vec_x = int{};
    auto vec_y = int{};

    if( dx != 0 )
        vec_x = dx/abs( dx );
    if( dy != 0 )
        vec_y = dy/abs( dy );

    return {vec_x, vec_y};
}

Unit::Unit( UNIT_TYPE type, pos_type pos, stats_type health ) : type_( type ), position_{ std::move(pos) }, health_( health ){ 
  n_units_++; 
}

Unit::~Unit() { n_units_--; }

void Unit::CombatTurn( std::vector< Unit* > units ) {
    std::string str_type = type_ == UNIT_TYPE::KNIGHT ? "Knight" : "Goblin";
    if( health_ <= 0 ){
        std::cout << " ---------------------------------- " << "\n";
        std::cout << str_type << " " << id_ << " have succumbed of their wounds" << "\n";
        return;
    }
    std::cout << " ---------------------------------- " << "\n";
    std::cout << str_type << " " << id_ << " turn to move " << "\n";
    std::cout << "x=" << position_.at(0) << " y=" << position_.at(1) << "\n"; 
    std::cout << "Health: " << health_ << "\n"; 
    std::vector<double> unit_distances;
    auto self_it = std::find_if( units.begin(), units.end(), [this]( Unit* unit ){ 
        return unit->GetId() == this->GetId();
    } );
    if(self_it != units.end())  units.erase( self_it );
    auto closest_opponent = std::min_element( units.begin(), units.end(), [this]( Unit* unit1, Unit* unit2 ){
        auto d1 = Distance( unit1, this );
        auto d2 = Distance( unit2, this );
        return d1 < d2;
    } );
    auto distance_closest_opponent = Distance(this, *closest_opponent);
    if( CanRetreat() ){
        RetreatFrom( (*closest_opponent) );
        return;
    }
    if( CanAttack(distance_closest_opponent) ){
        auto strength = Attack();
        (*closest_opponent)->GetAttacked( strength );
        return;
    }
    else{
        MoveTo( (*closest_opponent) );
        return;
    }
}

void Unit::Move( const pos_type& target ){
    auto [expected_x, expected_y] = target;

    if( expected_x < X_MIN )
        expected_x = X_MIN;
    
    if( expected_x > X_MAX )
        expected_x = X_MAX;
    
    if( expected_y < Y_MIN )
        expected_y = Y_MIN;
    
    if( expected_y > Y_MAX )
        expected_y = Y_MAX;
    
    position_.at(0) = expected_x;
    position_.at(1) = expected_y;
}

Knight::Knight( pos_type pos ) : Unit(UNIT_TYPE::KNIGHT, pos, KNIGHT_MAX_HEALTH ), shield_durability_(KNIGHT_SHIELD_DURABILITY) {}

void Knight::MoveTo( Unit* unit ) {
    auto [dir_x, dir_y] = Direction(this, unit);
    auto [pos_x, pos_y] = position_;

    auto expected_x = pos_x + KNIGHT_MOVE_SPEED * dir_x;
    auto expected_y = pos_y + KNIGHT_MOVE_SPEED * dir_y;
    
    Move({expected_x, expected_y});
    
    std::cout << "Knight " << id_ << " moved towards " << unit->GetId() << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
}

bool Knight::CanAttack(double distance) const {
    if( distance < KNIGHT_RANGE )
        return true;
    return false;
}

stats_type Knight::Attack() {
    if( health_ > KNIGHT_CRITICAL_HEALTH )
        return KNIGHT_STRENGTH;
    
    std::random_device rnd_dev;
    std::mt19937 rnd_engine{rnd_dev()};
    std::uniform_int_distribution<stats_type> uniform_distribution{0, 100};
    auto miss = uniform_distribution(rnd_engine);
    if( miss < KNIGHT_MISS_CHANCE )
        return 0;

    return KNIGHT_STRENGTH;

}

bool Knight::CanRetreat() const {
    if( health_ > KNIGHT_CRITICAL_HEALTH ){
        return false;
    }
    return true;
}

void Knight::RetreatFrom( Unit* unit ) {
    auto [dir_x, dir_y] = Direction(this, unit);
    auto [pos_x, pos_y] = position_;
    
    auto expected_x = pos_x - KNIGHT_RETREAT_SPEED * dir_x;
    auto expected_y = pos_y - KNIGHT_RETREAT_SPEED * dir_y;
    
    Move({expected_x, expected_y});

    std::cout << "Knight " << id_ << " retreats from " << unit->GetId() << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
}

void Knight::GetAttacked( stats_type damage ) { 
    if( shield_durability_ <= 0 ){
        health_ -= damage > 0 ? damage : 0;
        std::cout << "Knight " << id_ << " is attacked; health: " << health_ << "\n";
        return;
    }
    std::random_device rnd_dev;
    std::mt19937 rnd_engine{rnd_dev()};
    std::uniform_int_distribution<stats_type> uniform_distribution{0, 100};
    auto block = uniform_distribution(rnd_engine);
    if( block < KNIGHT_BLOCK_CHANCE ){
        std::cout << "Knight " << id_ << " blocked the atack; health: " << health_ << "\n";
        shield_durability_--;
        return;
    }
    health_ -= damage > 0 ? damage : 0;
    std::cout << "Knight " << id_ << " is attacked; health: " << health_ << "\n";
}

bool Knight::CanHeal(double distance) const {
    if( health_ > KNIGHT_HEALING_HEALTH ){
        return false;
    }
    if( distance < KNIGHT_RANGE ){
        return false;
    }
    return true;
}

void Knight::Heal() {
    health_+=KNIGHT_HEALING_AMOUNT;
    shield_durability_++;
}

Goblin::Goblin( pos_type pos ) : Unit(UNIT_TYPE::GOBLIN, pos, GOBLIN_MAX_HEALTH ) {}

void Goblin::MoveTo( Unit* unit ) {
    auto [dir_x, dir_y] = Direction(this, unit);
    auto [pos_x, pos_y] = position_;

    auto expected_x = pos_x + GOBLIN_MOVE_SPEED * dir_x;
    auto expected_y = pos_y + GOBLIN_MOVE_SPEED * dir_y;
    
    Move({expected_x, expected_y});
    
    std::cout << "Goblin " << id_ << " moved towards " << unit->GetId() << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
}

bool Goblin::CanAttack(double distance) const {
    if( distance < GOBLIN_RANGE )
        return true;
    return false;
}

stats_type Goblin::Attack() {
    if( health_ > GOBLIN_CRITICAL_HEALTH )
        return GOBLIN_STRENGTH;
    
    std::random_device rnd_dev;
    std::mt19937 rnd_engine{rnd_dev()};
    std::uniform_int_distribution<stats_type> uniform_distribution{0, 100};
    auto miss = uniform_distribution(rnd_engine);
    if( miss < GOBLIN_MISS_CHANCE )
        return 0;
    return GOBLIN_STRENGTH;
}

bool Goblin::CanRetreat() const {
    if( health_ > GOBLIN_CRITICAL_HEALTH ){
        return false;
    }
    return true;
}

void Goblin::RetreatFrom( Unit* unit ) {
    auto [dir_x, dir_y] = Direction(this, unit);
    auto [pos_x, pos_y] = position_;
    
    auto expected_x = pos_x - GOBLIN_RETREAT_SPEED * dir_x;
    auto expected_y = pos_y - GOBLIN_RETREAT_SPEED * dir_y;
    
    Move({expected_x, expected_y});

    std::cout << "Goblin " << id_ << " retreats from " << unit->GetId() << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
}

void Goblin::GetAttacked( stats_type damage ) {
    if( health_ < GOBLIN_CRITICAL_HEALTH ){
        damage /= 2;
    }
    health_ -= damage > 0 ? damage : 0;
    std::cout << "Goblin " << id_ << " is attacked; health: " << health_ << "\n";
}

bool Goblin::CanHeal( [[maybe_unused]] double distance) const {
    return false;
}

void Goblin::Heal() {}
