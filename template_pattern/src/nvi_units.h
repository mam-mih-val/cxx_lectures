#ifndef _MATH_VECTOR_H_
#define _MATH_VECTOR_H_

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cassert>
#include <exception>
#include <initializer_list>
#include <math.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>

using pos_type = std::array<int, 2>;
using stats_type = int;

const std::string KNIGHT_NAME = "Knight";
const stats_type KNIGHT_MAX_HEALTH = 55;
const stats_type KNIGHT_STRENGTH = 12;
const stats_type KNIGHT_RANGE = 1;
const stats_type KNIGHT_ARMOUR_DURABILITY = 3;
const stats_type KNIGHT_ARMOUR_STRENGTH = 5;

const std::string GOBLIN_NAME = "Goblin";
const stats_type GOBLIN_MAX_HEALTH = 40;
const stats_type GOBLIN_STRENGTH = 10;
const stats_type GOBLIN_RANGE = 2;

class Unit;

inline double Distance( Unit* unit1, Unit* unit2 );

class Unit{
public:
    Unit( std::string type, 
        pos_type pos, 
        stats_type health, 
        stats_type attack_strength, 
        stats_type attack_range ) : 
        type_( std::move(type) ),
        position_{ std::move(pos) }, 
        health_( health ),
        attack_strength_( attack_strength ),
        attack_range_( attack_range ) 
        { n_units_++; }
    virtual ~Unit() { n_units_--; };
    void CombatTurn( std::vector< Unit* > units ) {
        if( health_ <= 0 ){
            std::cout << " ---------------------------------- " << "\n";
            std::cout << type_ << " " << id_ << " have succumbed of their wounds" << "\n";
            return;
        }
        std::cout << " ---------------------------------- " << "\n";
        std::cout << type_ << " " << id_ << " turn to move " << "\n";
        std::cout << "x=" << position_.at(0) << " y=" << position_.at(1) << "\n"; 
        std::cout << "Health: " << health_ << "\n"; 
        std::vector<double> unit_distances;
        auto self_it = std::find_if( units.begin(), units.end(), [this]( Unit* unit ){ 
            return unit->GetId() == this->GetId();
        } );
        units.erase( self_it );
        auto closest_opponent = std::min_element( units.begin(), units.end(), [this]( Unit* unit1, Unit* unit2 ){
            auto d1 = Distance( unit1, this );
            auto d2 = Distance( unit2, this );
            return d1 < d2;
        } );
        if( health_ < 5 ){
            RetreatFrom( (*closest_opponent) );
            return;
        }
        if( Distance(this, *closest_opponent) < attack_range_ ){
            auto strength = Attack();
            (*closest_opponent)->GetAttacked( strength );
            return;
        }
        else{
            MoveTo( (*closest_opponent) );
            return;
        };
    }
    const pos_type& GetPosition() const { return position_; };
    size_t GetId() const { return id_; }
    stats_type GetCurrentHealth() { return health_; }
    
private:
    const std::string type_;
    virtual void GetAttacked( stats_type damage ) = 0;
    virtual void MoveTo( Unit* ) = 0;
    virtual stats_type Attack() = 0;
    virtual void RetreatFrom( Unit* unit ) = 0;

protected:
    static size_t n_units_;
    const size_t id_{n_units_};
    pos_type position_{};
    stats_type health_{};
    stats_type attack_strength_{};
    stats_type attack_range_{};
};


inline double Distance( Unit* unit1, Unit* unit2 ){
    auto x1 = unit1->GetPosition().at(0);
    auto y1 = unit1->GetPosition().at(1);
    
    auto x2 = unit2->GetPosition().at(0);
    auto y2 = unit2->GetPosition().at(1);
    
    auto dx = x1 - x2;
    auto dy = y1 - y2;
    auto distance = sqrt( dx*dx + dy*dy );
    return distance;
}

class Knight : public Unit{
public:
    Knight( pos_type pos ) : Unit(KNIGHT_NAME, pos, KNIGHT_MAX_HEALTH, KNIGHT_STRENGTH, KNIGHT_RANGE) {};
    ~Knight() = default;
    
    void MoveTo( Unit* unit ) override {
        auto curr_x = position_.at(0);
        auto curr_y = position_.at(1);
        auto to_x = unit->GetPosition().at(0);
        auto to_y = unit->GetPosition().at(1);
        auto dx = to_x - curr_x;
        auto dy = to_y - curr_y;
        if( dx != 0 )
            position_.at(0) += dx / abs( dx );
        if( dy != 0 )
            position_.at(1) += dy / abs( dy );
        std::cout << "Knight " << id_ << " moved towards " << unit->GetId() << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
    }

    stats_type Attack() override {
        return attack_strength_;
    }
    
    void RetreatFrom( Unit* unit ) override { 
        auto curr_x = position_.at(0);
        auto curr_y = position_.at(1);
        auto from_x = unit->GetPosition().at(0);
        auto from_y = unit->GetPosition().at(1);
        auto dx = from_x - curr_x;
        auto dy = from_y - curr_y;
        if( dx != 0 )
            position_.at(0) -= dx/abs( dx );
        if( dy != 0 )
            position_.at(1) -= dy/abs( dy );
        std::cout << "Knight " << id_ << " retreats from " << unit->GetId() << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
    };

    void GetAttacked( stats_type damage ) override { 
        if( armour_durability_ > 0 ){
            damage -= armour_strength_;
        }
        health_ -= damage > 0 ? damage : 0;
        std::cout << "Knight " << id_ << " is attacked; health: " << health_ << "\n";
    }

private:
    stats_type armour_durability_{ KNIGHT_ARMOUR_DURABILITY };
    stats_type armour_strength_{ KNIGHT_ARMOUR_STRENGTH };
};

class Goblin : public Unit{
public:
    Goblin( pos_type pos ) : Unit(GOBLIN_NAME, pos, GOBLIN_MAX_HEALTH, GOBLIN_STRENGTH, GOBLIN_RANGE) {};
    
    ~Goblin() = default;

    void MoveTo( Unit* unit ) override { 
        auto curr_x = position_.at(0);
        auto curr_y = position_.at(1);
        auto to_x = unit->GetPosition().at(0);
        auto to_y = unit->GetPosition().at(1);
        auto dx = to_x - curr_x;
        auto dy = to_y - curr_y;
        if( dx != 0 )
            position_.at(0) += dx/abs( dx );
        if( dy != 0 )
            position_.at(1) += dy/abs( dy );
        std::cout << "Goblin " << id_ << " moved towards " << unit->GetId() << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
    }

    stats_type Attack() override { 
        return attack_strength_;
    }
    
    void RetreatFrom( Unit* unit ) override { 
        auto curr_x = position_.at(0);
        auto curr_y = position_.at(1);
        auto from_x = unit->GetPosition().at(0);
        auto from_y = unit->GetPosition().at(1);
        auto dx = from_x - curr_x;
        auto dy = from_y - curr_y;
        if( dx != 0 )
            position_.at(0) -= dx/abs( dx );
        if( dy != 0 )
            position_.at(1) -= dy/abs( dy );
        std::cout << "Goblin " << id_ << " retreats from " << unit->GetId() << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
    };

    void GetAttacked( stats_type damage ) override { 
        health_ -= damage;
        std::cout << "Goblin " << id_ << " is attacked; health: " << health_ << "\n";
    }
};


#endif // _MATH_VECTOR_H_