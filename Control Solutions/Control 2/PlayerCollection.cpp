#include "PlayerCollection.hpp"
#include <stdexcept>
#include <cstring>
#include <utility>

PlayerCollection::PlayerCollection(){
    m_Data = new Player *[m_Capacity];
}

PlayerCollection::PlayerCollection(PlayerCollection const &other){
    Copy(other);
}

PlayerCollection::PlayerCollection(PlayerCollection &&other){
    Move(std::move(other));
}

PlayerCollection::~PlayerCollection(){
    Free(m_Size);
}

PlayerCollection &PlayerCollection::operator =(PlayerCollection const &other){

    if(this == &other) return *this;

    *this = PlayerCollection(other);

    return *this;

}

PlayerCollection &PlayerCollection::operator =(PlayerCollection &&other){

    if(this == &other) return *this;

    Free(m_Size);
    Move(std::move(other));

    return *this;    

}

Player const * const PlayerCollection::operator [](size_t index) const{

    if(index >= m_Size) throw std::out_of_range("Index out of range");
    return m_Data[index];

}

void PlayerCollection::AddPlayer(Player *player){

    if(Find(player -> GetName()) != m_Size) return;
    if(m_Size == m_Capacity) Resize();
    m_Data[m_Size++] = player -> Clone();

}

void PlayerCollection::RemovePlayer(char const *name){

    if(!name) return;

    size_t found = Find(name);

    if(found == m_Size) return;

    delete m_Data[found];
    for(size_t i = found; i < m_Size - 1; ++i)
        m_Data[i] = m_Data[i + 1];

    --m_Size;

}

Player * const PlayerCollection::At(size_t index) const{

    if(index >= m_Size) throw std::out_of_range("Index out of range");
    return m_Data[index];

}

size_t PlayerCollection::Size() const{
    return m_Size;
}

size_t PlayerCollection::Find(char const *name) const{

    for(size_t i = 0; i < m_Size; ++i)
        if(!strcmp(name, m_Data[i] -> GetName()))
            return i;

    return m_Size;

}

void PlayerCollection::Resize(){

    Player **temp = new Player *[m_Capacity *= 2];
    for(size_t i = 0; i < m_Size; ++i)
        temp[i] = m_Data[i];
    delete[] m_Data;
    m_Data = temp;

}

void PlayerCollection::Copy(PlayerCollection const &other){

    m_Data = new Player *[other.m_Capacity];
    m_Capacity = other.m_Capacity;
    m_Size = other.m_Size;
    for(size_t i = 0; i < other.m_Size; ++i)
        try{ m_Data[i] = other.m_Data[i] -> Clone(); }
        catch(std::bad_alloc const &ex){

            Free(i);
            throw;

        }

}

void PlayerCollection::Move(PlayerCollection &&other){

    m_Data = std::exchange(other.m_Data, nullptr);
    m_Capacity = other.m_Capacity;
    m_Size = other.m_Size;

}

void PlayerCollection::Free(size_t size){

    for(size_t i = 0; i < size; ++i)
        delete m_Data[i];
    delete[] m_Data;

}