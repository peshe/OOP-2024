#ifndef __PLAYER_HPP_
#define __PLAYER_HPP_

#include <iosfwd>

struct Point{
    unsigned x, y;
};

class Player{

public:
    enum class Weapon : unsigned char{

        SWORD,
        WAND,
        STAFF,
        AXE

    };


public:
    Player(char const *name, Weapon weapon, unsigned attackDamage, Point spawnPosition = { 0, 0 });
    Player(Player const &other);
    Player(Player &&other);
    virtual ~Player();

    Player &operator =(Player const &other);
    Player &operator =(Player &&other);

public:
    char const *GetName() const;
    Point GetPosition() const;
    unsigned GetHealth() const;
    Weapon GetWeapon() const;

public:
    virtual void HandleAttack(unsigned damage);
    virtual void Attack(Player * const enemy);
    virtual unsigned GetAttackPower() const;
    virtual void Move(Point position);
    virtual void Print() const;

public:
    virtual Player *Clone() const = 0;

protected:
    bool IsInRange(Point point) const;

private:
    void Copy(Player const &other);
    void MoveObject(Player &&other);
    void Free();

private:
    char *m_Name = nullptr;
    Point m_Position = { 0, 0 };
    unsigned m_Health = 100, m_AttackDamage = 1;
    Weapon m_Weapon = Weapon::STAFF;

};

std::ostream &operator <<(std::ostream &os, Point point);
std::ostream &operator <<(std::ostream &os, Player::Weapon weapon);

#endif