#include <iostream>
#include <fstream>
#include <cassert>

const std::size_t MAX_NAME_SIZE = 64;

enum class PokemonType
{
    UNKNOWN,
    NORMAL, 
    FIRE, 
    WATER, 
    GRASS, 
    ELECTRIC, 
    GHOST, 
    FLYING
};

struct Pokemon
{
    char name[MAX_NAME_SIZE + 1];
    PokemonType type;
    unsigned int power;
};

bool save(const Pokemon* pokemons, std::size_t size, const char* file); 

struct PokemonHandler
{
    std::ifstream in;
    std::size_t size;
};

bool initialize(PokemonHandler& handler, const char* file);

const char* toString(PokemonType pokemonType);

void printPokemon(const Pokemon& pokemon);

Pokemon at(PokemonHandler& handler, std::size_t i);

int main ()
{
    Pokemon pokemons[] = {Pokemon{"Pikachu", PokemonType::ELECTRIC, 90},
                          Pokemon{"Turtwig", PokemonType::GRASS, 75},
                          Pokemon{"Piplup", PokemonType::WATER, 70},
                          Pokemon{"Chimchar", PokemonType::FIRE, 95}};

    std::size_t size = sizeof(pokemons) / sizeof(pokemons[0]);

    const char* fileName = "pokemons.bin";

    if (!save(pokemons, size, fileName))
    {
        return 1;
    }

    PokemonHandler handler;
    if (!initialize(handler, fileName))
    {
        return 1;
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        printPokemon(at(handler, i));
    }

    // printPokemon(at(handler, 100));

    handler.in.close();

    return 0;
}

bool save(const Pokemon* pokemons, std::size_t size, const char* file)
{
    std::ofstream out(file);
    if (!out)
    {
        std::cout << "Problem while opening the file!" << std::endl;
        return false;
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        out.write(reinterpret_cast<const char*>(&pokemons[i]), sizeof(Pokemon));
    }

    out.close();
    return true;
}

bool initialize(PokemonHandler& handler, const char* file)
{
    handler.in.open(file);

    if (!handler.in)
    {
        std::cout << "Problem while opening the file!" << std::endl;
        return false;
    }

    std::size_t initialPosition = handler.in.tellg();

    handler.in.seekg(0, std::ios::end);
    std::size_t fileSize = handler.in.tellg();

    handler.in.seekg(initialPosition);

    handler.size = fileSize / sizeof(Pokemon);

    return true;
}

const char* toString(PokemonType pokemonType)
{
    switch (pokemonType)
    {
    case PokemonType::UNKNOWN:
        return "Unknown";
    case PokemonType::NORMAL:
        return "Normal";
    case PokemonType::FIRE:
        return "Fire";
    case PokemonType::WATER:
        return "Water";
    case PokemonType::GRASS:
        return "Grass";
    case PokemonType::ELECTRIC:
        return "Electric";
    case PokemonType::GHOST:
        return "Ghost";
    case PokemonType::FLYING:
        return "Flying";
    default:
        return nullptr;
    }
}

void printPokemon(const Pokemon& pokemon)
{
    std::cout << "Name: " << pokemon.name << std::endl;
    std::cout << "Type: " << toString(pokemon.type) << std::endl;
    std::cout << "Power: " << pokemon.power << std::endl;
}

Pokemon at(PokemonHandler& handler, std::size_t i)
{
    assert(i < handler.size);

    handler.in.seekg(i * sizeof(Pokemon));

    Pokemon result;
    handler.in.read(reinterpret_cast<char*>(&result), sizeof(Pokemon));

    return result;
}