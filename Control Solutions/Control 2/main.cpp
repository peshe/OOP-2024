#include "Warrior.hpp"
#include "Mage.hpp"
#include "Necromancer.hpp"
#include "PlayerCollection.hpp"
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(){

    srand(time(nullptr));

    try{

        PlayerCollection pc;
        Necromancer necromancer("Sir Jameson the magician", Player::Weapon::WAND, 50, "Ice bomb", 0.8);
        Mage mage("Magical Bob", Player::Weapon::STAFF, 20, "Fireball", 0.3, { 10, 15 });
        Warrior warrior("Sir Lancelot", Player::Weapon::SWORD, 30, 100, 30, { 10, 20 });

        pc.AddPlayer(&necromancer);
        pc.AddPlayer(&mage);
        pc.AddPlayer(&warrior);

        for(size_t i = 0; i < pc.Size(); ++i){

            pc[i] -> Print();
            std::cout << "\n\n";

        }
        std::cout << "\n\n";

        for(size_t i = 0; i < pc.Size() - 1; ++i)
            for(size_t j = i + 1; j < pc.Size(); ++j){

                Point toMove = pc.At(j) -> GetPosition();
                ++toMove.x;

                pc.At(i) -> Move(toMove);
                pc.At(i) -> Attack(pc.At(j));

                if(!pc[j] -> GetHealth()) pc.RemovePlayer(pc[j--] -> GetName());

            }

        for(size_t i = 0; i < pc.Size(); ++i){

            pc[i] -> Print();
            std::cout << "\n\n";

        }

    }
    catch(std::bad_alloc &){
        std::cerr << "Bad alloc\n";
    }
    catch(std::invalid_argument const &ex){
        std::cerr << ex.what() << '\n';
    }
    catch(std::out_of_range const &ex){
        std::cerr << ex.what() << '\n';
    }
    catch(std::exception const &ex){
        std::cerr << ex.what() << '\n';
    }
    catch(...){
        std::cerr << "Exception occurred\n";
    }

    return 0;

}