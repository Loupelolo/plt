#include <ai.h>
#include <engine.h>
#include <random>
#include <iostream>

namespace ai {

    RandomAI::RandomAI (const state::State &state) : AI(state) 
    {

    }

    RandomAI::~RandomAI () 
    {
    
    }

    void RandomAI::run (const state::State& state, engine::Engine& engine)
    {
        /*Initializing a random number generator*/
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> noCommande (0.00, 1.99); // After (int) cast, generates number beetween 0 and 1 included

        int commandeChoisie = (int)noCommande(mt);

        switch(commandeChoisie)
        {
            case(0): // Déplacement
            {
                std::cout << "L'IA va se déplacer" << std::endl;

                // Instanciation de générateurs de nombres aléatoires
                std::uniform_real_distribution<double> deplacementX (-11.99, 11.99);
                std::uniform_real_distribution<double> deplacementY (-11.99, 11.99);

                // Tentative de deplacement jusqu'à ce que l'IA y parvienne
                bool deplacementReussi = false;
                while(!deplacementReussi)
                {
                    engine::CommandeDeplacement deplacementTest((int)deplacementX(mt), (int)deplacementY(mt));
                    deplacementReussi = engine.executerCommande(deplacementTest);
                }
            }
                break;
            default:
                std::cout << "Je n'ai pas de chance" << std::endl;
                break;
        }
    }
}
