#include "Player.hpp"
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <utility>
#include <cmath>

Player::Player(char const *name, Weapon weapon, unsigned attackDamage, Point spawnPosition){

    if(!name) throw std::invalid_argument("Name must not be nullptr");

    m_Name = new char[strlen(name)];
    strcpy(m_Name, name);

    m_Position = spawnPosition;
    m_Weapon = weapon;
    m_AttackDamage = attackDamage;

}

Player::Player(Player const &other){

    m_Name = new char[strlen(other.m_Name) + 1];
    Copy(other);

}

Player::Player(Player &&other){
    MoveObject(std::move(other));
}

Player::~Player(){
    Free();
}

Player &Player::operator =(Player const &other){

    if(this == &other) return *this;

    char *name = new char[strlen(other.m_Name) + 1];
    Free();
    m_Name = name;
    Copy(other);

    return *this;

}

Player &Player::operator =(Player &&other){

    if(this == &other) return *this;

    Free();
    MoveObject(std::move(other));

    return *this;    

}

void Player::Move(Point position){
    m_Position = position;
}

char const *Player::GetName() const{
    return m_Name;
}

Point Player::GetPosition() const{
    return m_Position;
}

unsigned Player::GetHealth() const{
    return m_Health;
}

Player::Weapon Player::GetWeapon() const{
    return m_Weapon;
}

void Player::HandleAttack(unsigned damage){

    if(m_Health >= damage){

        m_Health -= damage;
        return;

    }

    m_Health = 0;

}

void Player::Attack(Player * const enemy){

    if(IsInRange(enemy -> m_Position))
        enemy -> HandleAttack(GetAttackPower());

}

unsigned Player::GetAttackPower() const{
    return m_AttackDamage;
}

void Player::Print() const{

    std::cout << m_Name
        << "\nAttack power: " << m_AttackDamage
        << "\nWeapon: " << m_Weapon
        << "\nPosition: " << m_Position
        << "\nHealth: " << m_Health;

}

bool Player::IsInRange(Point point) const{
    return abs(m_Position.y - point.y) + abs(m_Position.x - point.x) == 1;
}

void Player::Copy(Player const &other){

    strcpy(m_Name, other.m_Name);
    m_AttackDamage = other.m_AttackDamage;
    m_Position = other.m_Position;
    m_Health = other.m_Health;

}

void Player::MoveObject(Player &&other){

    m_Name = std::exchange(other.m_Name, nullptr);
    m_AttackDamage = other.m_AttackDamage;
    m_Position = other.m_Position;
    m_Health = other.m_Health;

}

void Player::Free(){
    delete[] m_Name;
}

std::ostream &operator <<(std::ostream &os, Point point){
    return os << '(' << point.x << ", " << point.y << ')';
}

std::ostream &operator <<(std::ostream &os, Player::Weapon weapon){

    switch (weapon){

        case Player::Weapon::AXE: return os << "axe";
        case Player::Weapon::STAFF: return os << "staff";
        case Player::Weapon::WAND: return os << "wand";
        case Player::Weapon::SWORD: return os << "sword";

    }

    return os;

}