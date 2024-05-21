#ifndef __NECROMANCER_HPP_
#define __NECROMANCER_HPP_

#include "Mage.hpp"
#include "PlayerCollection.hpp"

class Necromancer : public Mage{

public:
    Necromancer(char const *name, Weapon weapon, unsigned attackDamage, char const *ability, double healthReductionCoefficient, Point spawnPosition = { 0, 0 });

public:
    void Attack(Player * const enemy) override;
    void Move(Point position) override;
    void Print() const override;

public:
    Player *Clone() const override;

private:
    PlayerCollection m_KilledPlayers;

};

#endif