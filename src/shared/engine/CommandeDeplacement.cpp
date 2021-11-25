#include <engine.h>
#include <state.h>
#include <iostream>

namespace engine {

    CommandeDeplacement::CommandeDeplacement() {
        m_commandeTypeId = Deplacement;
    }

    CommandeDeplacement::CommandeDeplacement(int x, int y) {
        m_commandeTypeId = Deplacement;
        m_x=x;
        m_y=y;
    }

    CommandeDeplacement::~CommandeDeplacement(){
        
    }

    bool CommandeDeplacement::handleDeplacement (state::Entite perso, std::vector<int> map, int largeur){
        int mouvement = perso.getStat(8);
        int posX = perso.getPositionX();
        int posY = perso.getPositionY();

        if (abs(m_x-posX)+abs(m_y-posY)<=mouvement){
            if (map[m_x+m_y*largeur]==0 || map[m_x+m_y*largeur]==3){
                return true;
            }
        }
        return false;
    }

    bool CommandeDeplacement::handleCollision (std::vector<state::Entite> listeEntites){
        int length = listeEntites.size();
        for (int i = 0; i < length ; i++){
            if ((listeEntites[i].getPositionX() == m_x) && (listeEntites[i].getPositionY() == m_y)){
                return false;
            }
        }
        return true;
    }

    bool CommandeDeplacement::execute (Engine* engine){
        state::State& st = engine->getState();
        state::Entite perso = *st.getOrdreTour()[0];
        perso.deplacement(m_x,m_y);
        *st.getOrdreTour()[0] = perso;
        engine->setState(st);
        return true;
    }

    Json::Value CommandeDeplacement::serialize(){
        Json::Value value;
        value["test"] = "test";
        return value;
    }
}