#include <engine.h>
#include <state.h>
#include <iostream>
#include <fstream>

#include <json/json.h>

namespace engine {


    Engine::Engine () {
        
    }

    Engine::Engine (state::State* currentState) {
        m_currentState = currentState;
        m_indiceCommande = 0;
    }

    Engine::~Engine () {
        
    }

    void Engine::init (){
        
    }

    state::State* Engine::getState (){
        return m_currentState;
    }

    Json::Value Engine::getRecord (){
        return m_record;
    }

    void Engine::setState(state::State* currentState){
        m_currentState = currentState;
    }

    void Engine::setRecord(Json::Value record){
        m_record = record;
    }

    bool Engine::executerCommande (Commande& cmd){

        switch(cmd.getCommandeTypeId()){
            case Deplacement :
                if (cmd.handleDeplacement(m_currentState)){
                    cmd.execute(this->getState());
                    return true;
                }    
                break;

            case Attaque :
                if(cmd.handleAttaque(m_currentState)){
                    cmd.execute(this->getState());
                    return true;
                }
                break;

            case ActionSupplementaire :
                if(cmd.handleActionSupplementaire(m_currentState)){
                    cmd.execute(this->getState());
                    return true;
                }
                break;
            default : 
                return false;
                break;
        }


        return false;
    }

    void Engine::actualiser(){
        std::ifstream jCommande("json/commande.json");
        Json::Reader readerCommande;
        Json::Value obj;
        readerCommande.parse(jCommande, obj);

        if(m_indiceCommande<m_currentState->getIndiceCommande()){
            Json::Value& commandeActuelle = obj[m_indiceCommande];
            std::string idCommandeActuelle = commandeActuelle["TypeId"].asString();

            if(idCommandeActuelle == "Deplacement"){
                int x = commandeActuelle["x"].asInt();
                int y = commandeActuelle["y"].asInt();
                CommandeDeplacement depl(x,y);
                this->executerCommande(depl);

            } else if(idCommandeActuelle == "Attaque"){
                std::string nomCible = commandeActuelle["Cible"].asString();
                state::Entite* cible;
                for (size_t i = 0; i < m_currentState->getEntites().size() ; i++){
                    if(m_currentState->getEntites()[i]->getNom() == nomCible){
                        cible = m_currentState->getEntites()[i];
                    }
                }
                CommandeAttaque att(cible);
                this->executerCommande(att);

            } else if(idCommandeActuelle == "Action Supp"){
                std::string nomCible = commandeActuelle["Cible"].asString();
                std::string nomActionSupp = commandeActuelle["Action"].asString();
                state::Entite* cible;
                state::ActionSupp* actionSupp;

                for (size_t i = 0; i < m_currentState->getEntites().size() ; i++){
                    if(m_currentState->getEntites()[i]->getNom() == nomCible){
                        cible = m_currentState->getEntites()[i];
                    }
                }

                for(long unsigned int i = 0; i < m_currentState->getOrdreTour()[0]->getAutresActions().size(); i++){
                    if (m_currentState->getOrdreTour()[0]->getAutresActions()[i]->getNom() == nomActionSupp){
                        actionSupp = m_currentState->getOrdreTour()[0]->getAutresActions()[i];
                    }
                }
                CommandeActionSupplementaire act(cible,actionSupp);
                this->executerCommande(act);

            } else if(idCommandeActuelle == "Passer"){
                m_currentState->joueurSuivant();

            } else {
                this->actualiser();
            }
            m_record[m_indiceCommande] = obj;
            m_indiceCommande++;
        }
        //this->actualiser();
    }

}