#include "Mage.hpp"
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <utility>
#include <cmath>

Mage::Mage(char const *name, Weapon weapon, unsigned attackDamage, char const *ability, double healthReductionCoefficient, Point spawnPosition): Player(name, weapon, attackDamage, spawnPosition){

    if(!ability) throw std::invalid_argument("Ability should not be nullptr");
    if(healthReductionCoefficient < 0 || 1 < healthReductionCoefficient) throw std::invalid_argument("Health reduction coefficient should be between 0 and 1");

    m_Ability = new char[strlen(ability) + 1];
    strcpy(m_Ability, ability);

    m_HealthReductionCoefficient = healthReductionCoefficient;

}

Mage::Mage(Mage const &other): Player(other){
    Copy(other);
}

Mage::Mage(Mage &&other): Player(std::move(other)){
    MoveObject(std::move(other));
}

Mage::~Mage(){
    Free();
}

Mage &Mage::operator =(Mage const &other){

    if(this == &other) return *this;

    *this = Mage(other);

    return *this;

}

Mage &Mage::operator =(Mage &&other){

    if(this == &other) return *this;

    Player::operator =(std::move(other));
    Free();
    MoveObject(std::move(other));

    return *this;

}

void Mage::Attack(Player * const enemy){

    if(IsInRange(enemy -> GetPosition()))
        enemy -> HandleAttack(GetAttackPower() + enemy -> GetHealth() * m_HealthReductionCoefficient);

}

void Mage::Print() const{

    std::cout << "Mage: ";
    Player::Print();
    std::cout << "\nAbility: " << m_Ability;
    std::cout << "\nHealth reduction coefficient: " << m_HealthReductionCoefficient;

}

Player *Mage::Clone() const{
    return new Mage(*this);
}

char const *Mage::GetAbility() const{
    return m_Ability;
}

double Mage::GetCoefficient() const{
    return m_HealthReductionCoefficient;
}

void Mage::Copy(Mage const &other){

    m_Ability = new char[strlen(other.m_Ability) + 1];
    strcpy(m_Ability, other.m_Ability);

    m_HealthReductionCoefficient = other.m_HealthReductionCoefficient;

}

void Mage::MoveObject(Mage &&other){

    m_Ability = std::exchange(other.m_Ability, nullptr);
    m_HealthReductionCoefficient = other.m_HealthReductionCoefficient;

}

void Mage::Free(){
    delete[] m_Ability;
}