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

const stats_type KNIGHT_MAX_HEALTH = 100;
const stats_type GOBLIN_MAX_HEALTH = 60;

class Unit{
public:
    Unit( pos_type pos, stats_type health ) : position_{ std::move(pos) }, health_( health ) { n_units_++; }
    virtual ~Unit() { n_units_--; };
    const pos_type& GetPosition() const { return position_; };
    size_t GetId() const { return id_; }
    stats_type GetCurrentHealth() { return health_; }
    virtual void GetAttacked( stats_type damage ) = 0;
    virtual void CombatTurn( std::vector< Unit* > units ) = 0;
protected:
    static size_t n_units_;
    const size_t id_{n_units_};
    pos_type position_{};
    stats_type health_{};
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
    Knight( pos_type pos ) : Unit(pos, KNIGHT_MAX_HEALTH) {};
    ~Knight() override = default;
    void CombatTurn( std::vector< Unit* > units ) override {
        if( health_ <= 0 ){
            std::cout << " ---------------------------------- " << "\n";
            std::cout << "Knight " << id_ << " have succumbed of their wounds" << "\n";
            return;
        }
        std::cout << " ---------------------------------- " << "\n";
        std::cout << "Knight's " << id_ << " turn to move " << "\n";
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
        if( health_ < 0.1 * KNIGHT_MAX_HEALTH ){
            RetreatFrom( (*closest_opponent) );
            return;
        }
        if( Distance(this, *closest_opponent) < atack_range_ ){
            Attack( *closest_opponent );
            return;
        }
        else{
            MoveTo( (*closest_opponent) );
            return;
        };
    }

    void MoveTo( Unit* unit ){
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

        std::cout << "Knight " << id_ << " moved towards " << id_ << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
    }

    void Attack( Unit* unit ){
        std::cout << "Knight " << id_ << " is attacking " << "\n";
        unit->GetAttacked(atack_stat_); 
    }
    
    void RetreatFrom( Unit* unit ){ 
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
        std::cout << "Knight " << id_ << " retreats from " << id_ << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
    };

    void GetAttacked( stats_type damage ) override { 
        health_ -= damage;
        std::cout << "Knight " << id_ << " is attacked; health: " << health_ << "\n";
    }
    

private:
    const stats_type atack_range_{2};
    stats_type atack_stat_{60};
};

class Goblin : public Unit{
public:
    Goblin( pos_type pos ) : Unit(pos, GOBLIN_MAX_HEALTH) {};
    ~Goblin() override = default;
    void CombatTurn( std::vector< Unit* > units ) override {
        if( health_ <= 0 ){
            std::cout << " ---------------------------------- " << "\n";
            std::cout << "Goblin " << id_ << " have succumbed of their wounds" << "\n";
            return;
        }
        std::cout << " ---------------------------------- " << "\n";
        std::cout << "Goblin's " << id_ << " turn to move " << "\n";
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
        if( health_ < 0.2 * KNIGHT_MAX_HEALTH ){
            RetreatFrom( (*closest_opponent)->GetPosition() );
            return;
        }
        if( Distance(this, *closest_opponent) < atack_range_ ){
            Attack( *closest_opponent );
            return;
        }
        else{
            MoveTo( (*closest_opponent)->GetPosition() );
            return;
        };
    }

    void MoveTo( pos_type to_pos ){ 
        auto curr_x = position_.at(0);
        auto curr_y = position_.at(1);
        auto to_x = to_pos.at(0);
        auto to_y = to_pos.at(1);
        
        auto dx = to_x - curr_x;
        auto dy = to_y - curr_y;
        if( dx != 0 )
            position_.at(0) += dx/abs( dx );
        if( dy != 0 )
            position_.at(1) += dy/abs( dy );
        std::cout << "Goblin " << id_ << " moved towards " << id_ << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
    }

    void Attack( Unit* unit ){ 
        std::cout << "Goblin " << id_ << " is attacking" << "\n";
        unit->GetAttacked(atack_stat_); 
    }
    
    void RetreatFrom( pos_type from_pos ){ 
        auto curr_x = position_.at(0);
        auto curr_y = position_.at(1);
        auto from_x = from_pos.at(0);
        auto from_y = from_pos.at(1);
        auto dx = from_x - curr_x;
        auto dy = from_y - curr_y;
        if( dx != 0 )
            position_.at(0) -= dx/abs( dx );
        if( dy != 0 )
            position_.at(1) -= dy/abs( dy );
        std::cout << "Goblin " << id_ << " retreats from " << id_ << " to x=" << position_.at(0) << " y=" << position_.at(1) << "\n";
    };

    void GetAttacked( stats_type damage ) override { 
        health_ -= damage;
        std::cout << "Goblin " << id_ << " is attacked; health: " << health_ << "\n";
    }

private:
    const stats_type atack_range_{4};
    stats_type atack_stat_{40};
};


#endif // _MATH_VECTOR_H_