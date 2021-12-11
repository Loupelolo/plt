#include <engine.h>
#include <state.h>
#include <iostream>

namespace engine {


    CommandeActionSupplementaire::CommandeActionSupplementaire (){
        m_commandeTypeId = ActionSupplementaire;
    }

    CommandeActionSupplementaire::CommandeActionSupplementaire (state::Entite* cible, state::ActionSupp action){
        m_commandeTypeId = ActionSupplementaire;
        m_cible = cible;
        m_action = action;
    }

    CommandeActionSupplementaire::~CommandeActionSupplementaire (){

    }


    bool CommandeActionSupplementaire::handleActionSupplementaire (state::Entite perso){
        for(long unsigned int i = 0; i < perso.getAutresActions().size(); i++){
            if (perso.getAutresActions()[i].getNom() == m_action.getNom()){
                int portee = m_action.getPortee();
                int posX = perso.getPositionX();
                int posY = perso.getPositionY();
                int cibleX = m_cible->getPositionX();
                int cibleY = m_cible->getPositionY();
                if (abs(cibleX-posX)+abs(cibleY-posY)<=portee){
                        return true;
                }
            }
        }
        return false;
    }

    bool CommandeActionSupplementaire::execute (state::State* state){
        state::Entite *prs = state->getOrdreTour()[0];
        prs->effectuerActionSupp(&m_action,m_cible);
        return true;
    }

    Json::Value CommandeActionSupplementaire::serialize (){
        Json::Value value;
        value["test"] = "test";
        return value;
    }
    // Setters and Getters
  

}


