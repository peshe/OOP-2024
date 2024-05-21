#ifndef __PLAYER_COLLECTION_HPP_
#define __PLAYER_COLLECTION_HPP_

#include "Player.hpp"
#include <cstddef>

class PlayerCollection{

public:
    PlayerCollection();
    PlayerCollection(PlayerCollection const &other);
    PlayerCollection(PlayerCollection &&other);
    ~PlayerCollection();

    PlayerCollection &operator =(PlayerCollection const &other);
    PlayerCollection &operator =(PlayerCollection &&other);

public:
    Player const * const operator [](size_t index) const;

public:
    void AddPlayer(Player *player);
    void RemovePlayer(char const *name);
    Player * const At(size_t index) const;
    size_t Size() const;

private:
    size_t Find(char const *name) const;
    void Resize();
    void Copy(PlayerCollection const &other);
    void Move(PlayerCollection &&other);
    void Free(size_t size);

private:
    size_t m_Size = 0, m_Capacity = 0;
    Player **m_Data;

};

#endif