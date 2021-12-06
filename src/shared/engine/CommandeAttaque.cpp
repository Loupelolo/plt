#include <engine.h>
#include <state.h>
#include <iostream>

namespace engine {

    CommandeAttaque::CommandeAttaque() {
        m_commandeTypeId = Attaque;
    }

    CommandeAttaque::CommandeAttaque(state::Entite* cible) {
        m_commandeTypeId = Attaque;
        m_cible = cible;
    }

    CommandeAttaque::~CommandeAttaque(){
        
    }

    state::Entite* CommandeAttaque::getCible() {
        return m_cible;
    }

    bool CommandeAttaque::handleAttaque (state::Entite perso){
        int portee = perso.getStat(state::PORTEE);
        int posX = perso.getPositionX();
        int posY = perso.getPositionY();
        int cibleX = m_cible->getPositionX();
        int cibleY = m_cible->getPositionY();
        if (abs(cibleX-posX)+abs(cibleY-posY)<=portee){
                return true;
        }
        return false;
    }


    bool CommandeAttaque::execute (state::State* state){
        //state::State& st = engine->getState();
        state::Entite *prs = state->getOrdreTour()[0];
        prs->attaque(m_cible);
        //st.actualiserEntite(m_cible);
        //engine->setState(st);
        return true;
    }

    Json::Value CommandeAttaque::serialize(){
        Json::Value value;
        value["test"] = "test";
        return value;
    }
}