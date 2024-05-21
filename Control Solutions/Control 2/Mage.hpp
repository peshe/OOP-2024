#ifndef __MAGE_HPP_
#define __MAGE_HPP_

#include "Player.hpp"

class Mage : public Player{

public:
    Mage(char const *name, Weapon weapon, unsigned attackDamage, char const *ability, double healthReductionCoefficient, Point spawnPosition = { 0, 0 });
    Mage(Mage const &other);
    Mage(Mage &&other);
    ~Mage();

    Mage &operator =(Mage const &other);
    Mage &operator =(Mage &&other);

public:
    void Attack(Player * const enemy) override;
    void Print() const override;

public:
    Player *Clone() const override;

protected:
    char const *GetAbility() const;
    double GetCoefficient() const;

private:
    void Copy(Mage const &other);
    void MoveObject(Mage &&other);
    void Free();

private:
    char *m_Ability = nullptr;
    double m_HealthReductionCoefficient = 0;

};

#endif