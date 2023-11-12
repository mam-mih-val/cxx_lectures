#ifndef _MATH_VECTOR_H_
#define _MATH_VECTOR_H_

#include <vector>
#include "game_constants.h"

class Unit;

inline double Distance( Unit* unit1, Unit* unit2 );

class Unit{
public:
    enum class UNIT_TYPE{
        KNIGHT,
        GOBLIN
    };
    Unit(UNIT_TYPE type, pos_type pos, stats_type health );
    virtual ~Unit();
    void CombatTurn( std::vector< Unit* > units );
    const pos_type& GetPosition() const { return position_; };
    size_t GetId() const { return id_; }
    stats_type GetCurrentHealth() { return health_; }
    UNIT_TYPE GetType(){ return type_; }

protected:
    const UNIT_TYPE type_;
    static size_t n_units_;
    const size_t id_{n_units_};
    pos_type position_{};
    stats_type health_{};

    virtual void GetAttacked( stats_type ) = 0;
    virtual void MoveTo(Unit*) = 0;
    virtual bool CanAttack(double distance) const = 0;
    virtual stats_type Attack() = 0;
    virtual bool CanRetreat() const = 0;
    virtual void RetreatFrom( Unit* ) = 0;
    virtual bool CanHeal(double distance) const = 0;
    virtual void Heal() = 0;
    void Move( const pos_type& target );
};

class Knight : public Unit{
public:
    Knight( pos_type pos );
    ~Knight() override = default;
    void MoveTo( Unit* unit ) override;
    bool CanAttack(double distance) const override;
    stats_type Attack() override;
    bool CanRetreat() const override;
    void RetreatFrom( Unit* unit ) override;
    void GetAttacked( stats_type damage ) override;
    bool CanHeal(double distance) const override;
    void Heal() override;
private:
    stats_type shield_durability_{};
};

class Goblin : public Unit{
public:
    public:
    Goblin( pos_type pos );
    ~Goblin() override = default;
    void MoveTo( Unit* unit ) override;
    bool CanAttack(double distance) const override;
    stats_type Attack() override;
    bool CanRetreat() const override;
    void RetreatFrom( Unit* unit ) override;
    void GetAttacked( stats_type damage ) override;
    bool CanHeal( double distance) const override;
    void Heal() override;
};

#endif // _MATH_VECTOR_H_