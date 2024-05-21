#ifndef __WARRIOR_HPP_
#define __WARRIOR_HPP_

#include "Player.hpp"

class Warrior : public Player{

public:
    Warrior(char const *name, Weapon weapon, unsigned attackDamage, unsigned armor, unsigned attackIncreasePercent, Point spawnPosition = { 0, 0 });

public:
    void HandleAttack(unsigned damage) override;
    void Print() const override;

public:
    Player *Clone() const override;

private:
    unsigned m_Armor = 0;

};

#endif