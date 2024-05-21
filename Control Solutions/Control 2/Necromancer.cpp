#include "Necromancer.hpp"
#include <iostream>

Necromancer::Necromancer(char const *name, Weapon weapon, unsigned attackDamage, char const *ability, double healthReductionCoefficient, Point spawnPosition):
    Mage(name, weapon, attackDamage, ability, healthReductionCoefficient, spawnPosition){}

void Necromancer::Print() const{
    
    std::cout << "Necromancer: ";
    Player::Print();
    std::cout << "\nAbility: " << GetAbility();
    std::cout << "\nHealth reduction coefficient: " << GetCoefficient();
    std::cout << "\nNumber of killed players: " << m_KilledPlayers.Size();
    for(size_t i = 0; i < m_KilledPlayers.Size(); ++i)
        std::cout << "\n\t" << m_KilledPlayers[i] -> GetName();

}

void Necromancer::Attack(Player * const enemy){

    if(IsInRange(enemy -> GetPosition())){

        Mage::Attack(enemy);
        if(m_KilledPlayers.Size()) m_KilledPlayers.At(rand() % m_KilledPlayers.Size()) -> Attack(enemy);

        if(!enemy -> GetHealth()){
            
            m_KilledPlayers.AddPlayer(enemy);
            m_KilledPlayers.At(m_KilledPlayers.Size() - 1) -> Move(GetPosition());

        }

    }

}

void Necromancer::Move(Point position){

    Player::Move(position);
    for(size_t i = 0; i < m_KilledPlayers.Size(); ++i)
        m_KilledPlayers.At(i) -> Move(position);

}

Player *Necromancer::Clone() const{
    return new Necromancer(*this);
}