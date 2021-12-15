#include <ai.h>
#include <engine.h>
#include <random>
#include <iostream>

namespace ai {

    RandomAI::RandomAI (const state::State &state) : AI(state) 
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        m_mt = mt;
    }

    RandomAI::~RandomAI () 
    {
    
    }

    void RandomAI::run (state::State& state, engine::Engine& engine)
    {
        /*Initializing a random number generator*/
        std::random_device rd;
        //std::mt19937 mt(rd());
        std::uniform_real_distribution<double> noCommande (0.00, 1.99); // After (int) cast, generates number beetween 0 and 1 included

        int commandeChoisie = (int)noCommande(m_mt);

        switch(commandeChoisie)
        {
            case(0): // Déplacement
            {
                // Instanciation de générateurs de nombres aléatoires
                int deplacementXMax = state.getDecor().getLargeur();
                int deplacementYMax = state.getDecor().getHauteur();
                std::uniform_real_distribution<double> deplacementX (-deplacementXMax, deplacementXMax);
                std::uniform_real_distribution<double> deplacementY (-deplacementYMax, deplacementYMax);

                // Tentative de deplacement jusqu'à ce que l'IA y parvienne
                bool deplacementReussi = false;
                while(!deplacementReussi)
                {
                    engine::CommandeDeplacement testDeplacement((int)deplacementX(m_mt), (int)deplacementY(m_mt));
                    deplacementReussi = engine.executerCommande(testDeplacement);
                }
            }
                break;
            case(1): // Attaque
            {
                std::vector<state::Entite*> entitesDispo = state.getEntites();

                // Tentatives d'attaque
                bool attaqueReusie = false;
                int nbCiblesPossibles = entitesDispo.size();

                while((!attaqueReusie) && (nbCiblesPossibles != 0))
                {
                    std::uniform_real_distribution<double> indexCible (0.00, ((double)nbCiblesPossibles - 0.01));
                    int indexEntiteCiblee = (int)indexCible(m_mt);
                    engine::CommandeAttaque testAttaque(entitesDispo[indexEntiteCiblee]);
                    attaqueReusie = engine.executerCommande(testAttaque);
                    entitesDispo.erase(entitesDispo.begin() + indexEntiteCiblee);
                    nbCiblesPossibles = entitesDispo.size();
                }
            }
                break;
            default:
                std::cout << "Je n'ai pas de chance" << std::endl;
                break;
        }
    }
}
