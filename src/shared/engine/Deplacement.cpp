#include "Deplacement.h"

namespace engine {

    Deplacement::Deplacement(state::Entite perso, int cibleX, int cibleY) {
        perso.deplacement(cibleX-perso.getPositionX(), cibleY-perso.getPositionY());
    }

    Deplacement::~Deplacement() {
    
    }

    bool Deplacement::handleDeplacement (state::Entite perso, std::vector<int> map, int cibleX, int cibleY){
        int mouvement = perso.getStat(8);
        int posX = perso.getPositionX();
        int posY = perso.getPositionY();

        if (abs(cibleX-posX)+abs(cibleY-posY)<=mouvement){
            if (map[cibleX,cibleY]==0 || map[cibleX,cibleY]==3){
                return true;
            }
        }
        return false;
    }

    bool Deplacement::execute (Engine* engine){
        return true;
    }

    Json::Value Deplacement::serialize(){
        
    }
}