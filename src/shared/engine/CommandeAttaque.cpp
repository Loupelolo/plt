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

    bool CommandeAttaque::handleAttaque (state::State* state){
        int cibleX = m_cible->getPositionX();
        int cibleY = m_cible->getPositionY();

        int largeur = state->getDecor().getLargeur();

        this->ActuMapLib(state);

        if(m_mapLib[cibleX + cibleY *largeur]){
            return true;
        }

        return false;
    }

    void CommandeAttaque::ActuMapLib (state::State* etat){
        int largeur = etat->getDecor().getLargeur();
        int total = etat->getDecor().getMap().size();
        std::vector<int> mapLib(total,false);
        

        int portee = etat->getOrdreTour()[0]->getStat(state::PORTEE);
        int posX = etat->getOrdreTour()[0]->getPositionX();
        int posY = etat->getOrdreTour()[0]->getPositionY();

        int posInit = posX+largeur*posY;
        int posTemp = posInit;

        int cX = 0;
        int cY = 0;

        for (size_t j = 1; j < etat->getEntites().size() ; j++){
            cX = etat->getEntites()[j]->getPositionX();
            cY = etat->getEntites()[j]->getPositionY();
            if (abs(cX - posX) + abs(cY - posY) <= portee){
                mapLib[cX + cY * largeur] = true;
                if (cY == posY && cX > posX){
                    for(int i = posX + 1; i < cX; i++){
                        posTemp = posInit + i;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                            break;
                        }
                    }
                }
                else if (cY == posY && cX < posX){
                    for(int i = posX - 1; i > cX; i--){
                        posTemp = posInit - i;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                            break;
                        }
                    }
                }
                else if (cX == posX && cY > posY){
                    for(int i = posY + 1; i < cY; i++){
                        posTemp = posInit + i*largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                            break;
                        }
                    }
                }
                else if (cX == posX && cY < posY){
                    for(int i = posY - 1; i > cY; i--){
                        posTemp = posInit - i*largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                            break;
                        }
                    }
                }
                else if (((cX - posX) == (cY - posY)) && (cX < posX)){
                    for(int i = 1; i < abs(cX-posX); i++){
                        posTemp = posInit - i - i*largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                            break;
                        }
                    }
                }
                else if (((cX - posX) == -(cY - posY)) && (cX < posX)){
                    for(int i = 1; i < abs(cX-posX); i++){
                        posTemp = posInit + i - i*largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                            break;
                        }
                    }
                }
                else if (((cX - posX) == (cY - posY)) && (cX > posX)){
                    for(int i = 1; i < abs(cX-posX); i++){
                        posTemp = posInit + i + i*largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                            break;
                        }
                    }
                }
                else if (((cX - posX) == -(cY - posY)) && (cX > posX)){
                    for(int i = 1; i < abs(cX-posX); i++){
                        posTemp = posInit - i + i*largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                            break;
                        }
                    }
                }
                else if (((cX-posX) > 0) && ((cY-posY) > 0)){
                    posTemp = posInit + 1 + largeur;
                    if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                        mapLib[cX + cY * largeur] = false;
                    }
                    if (cX > cY){
                        posTemp = posInit + 1;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                        }
                        for(int a=2;a<cX;a++){
                            for(int o=1;o<=cY;o++){
                                posTemp = posInit + a + o*largeur;
                                if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                                    mapLib[cX + cY * largeur] = false;
                                }
                            }
                        } 
                    }
                    else{
                        posTemp = posInit + largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                        }
                        for(int o=2;o<cY;o++){
                            for(int a=1;a<=cX;a++){
                                posTemp = posInit + a + o*largeur;
                                if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                                    mapLib[cX + cY * largeur] = false;
                                }
                            }
                        }
                    }
                }
                else if (((cX-posX) > 0) && ((cY-posY) < 0)){
                    posTemp = posInit + 1 - largeur;
                    if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                        mapLib[cX + cY * largeur] = false;
                    }
                    if (cX > -cY){
                        posTemp = posInit + 1;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                        }
                        for(int a=2;a<cX;a++){
                            for(int o=-1;o>=-cY;o--){
                                posTemp = posInit + a + o*largeur;
                                if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                                    mapLib[cX + cY * largeur] = false;
                                }
                            }
                        } 
                    }
                    else{
                        posTemp = posInit - largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                        }
                        for(int o=-2;o>-cY;o--){
                            for(int a=1;a<=cX;a++){
                                posTemp = posInit + a + o*largeur;
                                if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                                    mapLib[cX + cY * largeur] = false;
                                }
                            }
                        }
                    }
                }
                else if (((cX-posX) < 0) && ((cY-posY) > 0)){
                    posTemp = posInit - 1 + largeur;
                    if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                        mapLib[cX + cY * largeur] = false;
                    }
                    if (-cX > cY){
                        posTemp = posInit - 1;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                        }
                        for(int a=-2;a>-cX;a--){
                            for(int o=1;o<=cY;o++){
                                posTemp = posInit + a + o*largeur;
                                if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                                    mapLib[cX + cY * largeur] = false;
                                }
                            }
                        } 
                    }
                    else{
                        posTemp = posInit + largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                        }
                        for(int o=2;o<cY;o++){
                            for(int a=-1;a>=-cX;a--){
                                posTemp = posInit + a + o*largeur;
                                if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                                    mapLib[cX + cY * largeur] = false;
                                }
                            }
                        }
                    }
                }
                else if (((cX-posX) < 0) && ((cY-posY) < 0)){
                    posTemp = posInit - 1 - largeur;
                    if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                        mapLib[cX + cY * largeur] = false;
                    }
                }
                if (-cX > -cY){
                        posTemp = posInit - 1;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                        }
                        for(int a=-2;a>-cX;a--){
                            for(int o=-1;o>=-cY;o--){
                                posTemp = posInit + a + o*largeur;
                                if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                                    mapLib[cX + cY * largeur] = false;
                                }
                            }
                        } 
                    }
                    else{
                        posTemp = posInit - largeur;
                        if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                            mapLib[cX + cY * largeur] = false;
                        }
                        for(int o=-2;o>-cY;o--){
                            for(int a=-1;a>=-cX;a--){
                                posTemp = posInit + a + o*largeur;
                                if (etat->getDecor().getMap()[posTemp]==state::MUR || etat->getDecor().getMap()[posTemp]==state::PIEG || etat->getDecor().getMap()[posTemp]==state::PORT || etat->getDecor().getMap()[posTemp]==state::EAU || etat->getDecor().getMap()[posTemp]==state::OBST){
                                    mapLib[cX + cY * largeur] = false;
                                }
                            }
                        }
                    }
            }
        }

 
        // for(int i = 0; i < total; i++){
        //      std::cout << mapLib[i] << " // ";
        // }

        m_mapLib = mapLib;
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