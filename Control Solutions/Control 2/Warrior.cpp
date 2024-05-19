#include "Warrior.hpp"
#include <iostream>

Warrior::Warrior(char const *name, Weapon weapon, unsigned attackDamage, unsigned armor, unsigned attackIncreasePercent, Point spawnPosition): Player(name, weapon, attackDamage, spawnPosition){
    m_Armor = armor;
}

void Warrior::HandleAttack(unsigned damage){

    if(m_Armor >= damage){

        m_Armor -= damage;
        return;

    }

    damage -= m_Armor;
    m_Armor = 0;

    Player::HandleAttack(damage);

}

void Warrior::Print() const{

    std::cout << "Warrior: ";
    Player::Print();
    std::cout << "\nArmor: " << m_Armor;

}

Player *Warrior::Clone() const{
    return new Warrior(*this);
}