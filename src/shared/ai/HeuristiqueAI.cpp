#include <ai.h>
#include <engine.h>
#include <iostream>

namespace ai {

    HeuristiqueAI::HeuristiqueAI (const state::State &state) : AI(state) 
    {

    }

    HeuristiqueAI::~HeuristiqueAI () 
    {
    
    }

    void HeuristiqueAI::run (state::State& state, engine::Engine& engine)
    {
        // D'abord, l'IA recherche quelle entité du camp adverse (Heros) est la plus proche
        std::vector<state::Entite*> listeEntites;
        for(unsigned int i=0; i<state.getEntites().size();i++){
            if(state.getEntites()[i]->getType()<6 && state.getEntites()[i]->getEstVivant()) listeEntites.push_back(state.getEntites()[i]);
        }
        if(listeEntites.size()>0){
            state::Entite* plusProcheEntite = listeEntites[0];
            int positionXEntite = state.getOrdreTour()[0]->getPositionX();
            int positionYEntite = state.getOrdreTour()[0]->getPositionY();
            int plusPetiteDistance = abs(listeEntites[0]->getPositionX() - positionXEntite) + abs(listeEntites[0]->getPositionY() - positionYEntite);

            for (unsigned int i = 1; i < listeEntites.size(); i++) 
            {
                int distanceEntite = abs(listeEntites[i]->getPositionX() - positionXEntite) + abs(listeEntites[i]->getPositionY() - positionYEntite);
                if (distanceEntite < plusPetiteDistance)
                {
                    plusPetiteDistance = distanceEntite;
                    plusProcheEntite = listeEntites[i];
                }
            }

            //Tentative d'attaque sur l'entité la plus proche
            bool attaqueReusie = false;
            engine::CommandeAttaque testAttaque(plusProcheEntite);
            attaqueReusie = engine.executerCommande(testAttaque);

            if (!attaqueReusie)
            {
                // Tentative de déplacement vers l'entité la plus proche
                
                bool deplacementReussi = false;

                if (abs(plusProcheEntite->getPositionX() - positionXEntite) > abs(plusProcheEntite->getPositionY() - positionYEntite))
                {
                    // Ce qui se passe si la distance qui sépare de l'entité la plus proche est majoritairement sur l'axe X
                    if (positionXEntite < plusProcheEntite->getPositionX())
                    {
                        // Si l'entité dont c'est le tour est à gauche de l'entité la plus proche
                        for (unsigned int i = 0; i < abs(plusProcheEntite->getPositionX() - positionXEntite); i++)
                        {
                            if (!deplacementReussi)
                            {
                                engine::CommandeDeplacement testDeplacement((plusProcheEntite->getPositionX() - i), positionYEntite);
                                deplacementReussi = engine.executerCommande(testDeplacement);
                            }
                        }
                    }
                    else
                    {
                        // Si l'entité dont c'est le tour est à droite de l'entité la plus proche
                        for (unsigned int i = 0; i < abs(plusProcheEntite->getPositionX() - positionXEntite); i++)
                        {
                            if (!deplacementReussi)
                            {
                                engine::CommandeDeplacement testDeplacement((plusProcheEntite->getPositionX() + i), positionYEntite);
                                deplacementReussi = engine.executerCommande(testDeplacement);
                            }
                        }
                    }               
                }
                else
                {
                    // Ce qui se passe si la distance qui sépare de l'entité la plus proche est majoritairement sur l'axe Y                
                    if (positionYEntite < plusProcheEntite->getPositionY())
                    {
                        // Si l'entité dont c'est le tour est au dessus de l'entité la plus proche
                        for (unsigned int i = 0; i < abs(plusProcheEntite->getPositionY() - positionYEntite); i++)
                        {
                            if (!deplacementReussi)
                            {
                                engine::CommandeDeplacement testDeplacement(positionXEntite, (plusProcheEntite->getPositionY() - i));
                                deplacementReussi = engine.executerCommande(testDeplacement);
                            }
                        }
                    }
                    else
                    {
                        // Si l'entité dont c'est le tour est au dessous de l'entité la plus proche
                        for (unsigned int i = 0; i < abs(plusProcheEntite->getPositionY() - positionYEntite); i++)
                        {
                            if (!deplacementReussi)
                            {
                                engine::CommandeDeplacement testDeplacement(positionXEntite, (plusProcheEntite->getPositionY() + i));
                                deplacementReussi = engine.executerCommande(testDeplacement);
                            }
                        }
                    }                
                }

                engine::CommandeAttaque ultimeTestAttaque(plusProcheEntite);
                attaqueReusie = engine.executerCommande(ultimeTestAttaque);  
            } 
            state.joueurSuivant();         
        }
    }
}
