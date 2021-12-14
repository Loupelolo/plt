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

    void RandomAI::run (state::State& state, engine::Engine& engine)
    {
        /*Initializing a random number generator*/
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> noCommande (0.00, 1.99); // After (int) cast, generates number beetween 0 and 1 included

        //int commandeChoisie = (int)noCommande(mt);
        int commandeChoisie = 0;

        switch(commandeChoisie)
        {
            case(0): // Déplacement
            {
                std::cout << "L'IA se déplace" << std::endl;
                
                // Instanciation de générateurs de nombres aléatoires
                double deplacementMax = (double)state.getOrdreTour()[0]->getStat(8) + 0.99;
                std::uniform_real_distribution<double> deplacementX (-deplacementMax, deplacementMax);
                std::uniform_real_distribution<double> deplacementY (-deplacementMax, deplacementMax);

                // Tentative de deplacement jusqu'à ce que l'IA y parvienne
                bool deplacementReussi = false;
                while(!deplacementReussi)
                {
                    engine::CommandeDeplacement testDeplacement((int)deplacementX(mt), (int)deplacementY(mt));
                    deplacementReussi = engine.executerCommande(testDeplacement);
                }
            }
                break;
            default:
                std::cout << "Je n'ai pas de chance" << std::endl;
                break;
        }
    }
}
