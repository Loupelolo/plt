#include <ai.h>
#include <engine.h>
#include <iostream>
#include <json/json.h>
#include <fstream>
#include <memory>

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
            if(state.getEntites()[i]->getType()/6!=state.getOrdreTour()[0]->getType()/6 && state.getEntites()[i]->getNiveau()==state.getNiveau() && state.getEntites()[i]->getEstVivant()) listeEntites.push_back(state.getEntites()[i]);
        }
        if(listeEntites.size()>0){
            state::Entite* plusProcheEntite = listeEntites[0];
            int positionXEntite = state.getOrdreTour()[0]->getPositionX();
            int positionYEntite = state.getOrdreTour()[0]->getPositionY();
            int plusPetiteDistance = abs(listeEntites[0]->getPositionX() - positionXEntite) + abs(listeEntites[0]->getPositionY() - positionYEntite);

            for (unsigned int i = 0; i < listeEntites.size(); i++) 
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

     void HeuristiqueAI::runPara (state::State& state, engine::Engine& engine)
    {
        std::ifstream jCommande("json/commande.json");
        Json::Reader readerCommande;
        Json::Value commandeJsonValue;
        readerCommande.parse(jCommande, commandeJsonValue);

        // D'abord, l'IA recherche quelle entité du camp adverse (Heros) est la plus proche
        std::vector<state::Entite*> listeEntites;
        for(unsigned int i=0; i<state.getEntites().size();i++){
            if(state.getEntites()[i]->getType()/6!=state.getOrdreTour()[0]->getType()/6 && state.getEntites()[i]->getNiveau()==state.getNiveau() && state.getEntites()[i]->getEstVivant()) listeEntites.push_back(state.getEntites()[i]);
        }
        if(listeEntites.size()>0){
            state::Entite* plusProcheEntite = listeEntites[0];
            int positionXEntite = state.getOrdreTour()[0]->getPositionX();
            int positionYEntite = state.getOrdreTour()[0]->getPositionY();
            int plusPetiteDistance = abs(listeEntites[0]->getPositionX() - positionXEntite) + abs(listeEntites[0]->getPositionY() - positionYEntite);

            for (unsigned int i = 0; i < listeEntites.size(); i++) 
            {
                int distanceEntite = abs(listeEntites[i]->getPositionX() - positionXEntite) + abs(listeEntites[i]->getPositionY() - positionYEntite);
                if (distanceEntite < plusPetiteDistance)
                {
                    plusPetiteDistance = distanceEntite;
                    plusProcheEntite = listeEntites[i];
                }
            }

            //Tentative d'attaque sur l'entité la plus proche
            engine::CommandeAttaque attaque(plusProcheEntite);

            if(attaque.handleAttaque(&state)){
                if(state.effectuerAction(2)){
                    commandeJsonValue[state.getIndiceCommande()]["TypeId"] = "Attaque";
                    commandeJsonValue[state.getIndiceCommande()]["Cible"] = plusProcheEntite->getNom();
                    state.setIndiceCommande(state.getIndiceCommande() +1);

                    Json::StreamWriterBuilder builder;
                    builder["commentStyle"] = "None";
                    builder["indentation"] = "   ";
                    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                    std::ofstream outputFileStream("json/commande.json");
                    writer -> write(commandeJsonValue, &outputFileStream);

                    return;
                }
            }

            if (!state.getAAttaque())
            {
                // Tentative de déplacement vers l'entité la plus proche
                

                if (abs(plusProcheEntite->getPositionX() - positionXEntite) > abs(plusProcheEntite->getPositionY() - positionYEntite))
                {
                    // Ce qui se passe si la distance qui sépare de l'entité la plus proche est majoritairement sur l'axe X
                    if (positionXEntite < plusProcheEntite->getPositionX())
                    {
                        // Si l'entité dont c'est le tour est à gauche de l'entité la plus proche
                        for (unsigned int i = 0; i < abs(plusProcheEntite->getPositionX() - positionXEntite); i++)
                        {
                            if (!state.getABouge())
                            {
                                engine::CommandeDeplacement deplacement((plusProcheEntite->getPositionX() - i), positionYEntite);
                                //deplacementReussi = engine.executerCommande(deplacement);
                                if(deplacement.handleDeplacement(&state)){
                                    if(state.effectuerAction(1)){
                                        commandeJsonValue[state.getIndiceCommande()]["TypeId"] = "Deplacement";
                                        commandeJsonValue[state.getIndiceCommande()]["x"] = plusProcheEntite->getPositionX() - i;
                                        commandeJsonValue[state.getIndiceCommande()]["y"] = positionYEntite;
                                        state.setIndiceCommande(state.getIndiceCommande() +1);

                                        Json::StreamWriterBuilder builder;
                                        builder["commentStyle"] = "None";
                                        builder["indentation"] = "   ";
                                        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                                        std::ofstream outputFileStream("json/commande.json");
                                        writer -> write(commandeJsonValue, &outputFileStream);

                                        return;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        // Si l'entité dont c'est le tour est à droite de l'entité la plus proche
                        for (unsigned int i = 0; i < abs(plusProcheEntite->getPositionX() - positionXEntite); i++)
                        {
                            /*if (!deplacementReussi)
                            {
                                engine::CommandeDeplacement deplacement((plusProcheEntite->getPositionX() + i), positionYEntite);
                                deplacementReussi = engine.executerCommande(deplacement);
                            }*/
                            if (!state.getABouge())
                            {
                                engine::CommandeDeplacement deplacement((plusProcheEntite->getPositionX() + i), positionYEntite);
                                //deplacementReussi = engine.executerCommande(deplacement);
                                if(deplacement.handleDeplacement(&state)){
                                    if(state.effectuerAction(1)){
                                        commandeJsonValue[state.getIndiceCommande()]["TypeId"] = "Deplacement";
                                        commandeJsonValue[state.getIndiceCommande()]["x"] = plusProcheEntite->getPositionX() + i;
                                        commandeJsonValue[state.getIndiceCommande()]["y"] = positionYEntite;
                                        state.setIndiceCommande(state.getIndiceCommande() +1);

                                        Json::StreamWriterBuilder builder;
                                        builder["commentStyle"] = "None";
                                        builder["indentation"] = "   ";
                                        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                                        std::ofstream outputFileStream("json/commande.json");
                                        writer -> write(commandeJsonValue, &outputFileStream);

                                        return;
                                    }
                                }
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
                            /*if (!deplacementReussi)
                            {
                                engine::CommandeDeplacement deplacement(positionXEntite, (plusProcheEntite->getPositionY() - i));
                                deplacementReussi = engine.executerCommande(deplacement);
                            }*/
                            if (!state.getABouge())
                            {
                                engine::CommandeDeplacement deplacement((positionXEntite), plusProcheEntite->getPositionY() - i);
                                //deplacementReussi = engine.executerCommande(deplacement);
                                if(deplacement.handleDeplacement(&state)){
                                    if(state.effectuerAction(1)){
                                        commandeJsonValue[state.getIndiceCommande()]["TypeId"] = "Deplacement";
                                        commandeJsonValue[state.getIndiceCommande()]["x"] = positionXEntite;
                                        commandeJsonValue[state.getIndiceCommande()]["y"] = plusProcheEntite->getPositionY() - i;
                                        state.setIndiceCommande(state.getIndiceCommande() +1);

                                        Json::StreamWriterBuilder builder;
                                        builder["commentStyle"] = "None";
                                        builder["indentation"] = "   ";
                                        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                                        std::ofstream outputFileStream("json/commande.json");
                                        writer -> write(commandeJsonValue, &outputFileStream);

                                        return;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        // Si l'entité dont c'est le tour est au dessous de l'entité la plus proche
                        for (unsigned int i = 0; i < abs(plusProcheEntite->getPositionY() - positionYEntite); i++)
                        {
                            /*if (!deplacementReussi)
                            {
                                engine::CommandeDeplacement deplacement(positionXEntite, (plusProcheEntite->getPositionY() + i));
                                deplacementReussi = engine.executerCommande(deplacement);
                            }*/
                            if (!state.getABouge())
                            {
                                engine::CommandeDeplacement deplacement((positionXEntite), (plusProcheEntite->getPositionY() + i));
                                //deplacementReussi = engine.executerCommande(deplacement);
                                if(deplacement.handleDeplacement(&state)){
                                    if(state.effectuerAction(1)){
                                        commandeJsonValue[state.getIndiceCommande()]["TypeId"] = "Deplacement";
                                        commandeJsonValue[state.getIndiceCommande()]["x"] = positionXEntite;
                                        commandeJsonValue[state.getIndiceCommande()]["y"] = (plusProcheEntite->getPositionY() + i);
                                        state.setIndiceCommande(state.getIndiceCommande() +1);

                                        Json::StreamWriterBuilder builder;
                                        builder["commentStyle"] = "None";
                                        builder["indentation"] = "   ";
                                        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                                        std::ofstream outputFileStream("json/commande.json");
                                        writer -> write(commandeJsonValue, &outputFileStream);

                                        return;
                                    }
                                }
                            }
                        }
                    }                
                }

                engine::CommandeAttaque attaqueUltime(plusProcheEntite);

                if(attaqueUltime.handleAttaque(&state)){
                    if(state.effectuerAction(2)){
                        commandeJsonValue[state.getIndiceCommande()]["TypeId"] = "Attaque";
                        commandeJsonValue[state.getIndiceCommande()]["Cible"] = plusProcheEntite->getNom();
                        state.setIndiceCommande(state.getIndiceCommande() +1);

                        Json::StreamWriterBuilder builder;
                        builder["commentStyle"] = "None";
                        builder["indentation"] = "   ";
                        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                        std::ofstream outputFileStream("json/commande.json");
                        writer -> write(commandeJsonValue, &outputFileStream);

                        return;
                    }
                }
            } 
            commandeJsonValue[state.getIndiceCommande()]["TypeId"] = "Passer";    

            state.setIndiceCommande(state.getIndiceCommande() +1);

            Json::StreamWriterBuilder builder;
            builder["commentStyle"] = "None";
            builder["indentation"] = "   ";
            std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
            std::ofstream outputFileStream("json/commande.json");
            writer -> write(commandeJsonValue, &outputFileStream);    
        }
    }
}
