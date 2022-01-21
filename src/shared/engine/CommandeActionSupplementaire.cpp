#include <engine.h>
#include <state.h>
#include <iostream>

namespace engine {


    CommandeActionSupplementaire::CommandeActionSupplementaire (){
        m_commandeTypeId = ActionSupplementaire;
    }

    CommandeActionSupplementaire::CommandeActionSupplementaire (state::Entite* cible, state::ActionSupp* action){
        m_commandeTypeId = ActionSupplementaire;
        m_cible = cible;
        m_action = action;
    }

    CommandeActionSupplementaire::~CommandeActionSupplementaire (){

    }

    void CommandeActionSupplementaire::setAction(state::ActionSupp* action){
        m_action = action;
    }


    bool CommandeActionSupplementaire::handleActionSupplementaire (state::State* etat){
        int cibleX = m_cible->getPositionX();
        int cibleY = m_cible->getPositionY();

        int largeur = etat->getDecor().getLargeur();

        this->ActuMapLib(etat);

        if(m_mapLib[cibleX + cibleY *largeur]){
            return true;
        }

        return false;
    }

    void CommandeActionSupplementaire::ActuMapLib (state::State* etat){
        int largeur = etat->getDecor().getLargeur();
        int total = etat->getDecor().getMap().size();
        std::vector<bool> mapLib(total,false);
        
        int posX = 0;
        int posY = 0;


        for(long unsigned int i = 0; i < etat->getOrdreTour()[0]->getAutresActions().size(); i++){
            if (etat->getOrdreTour()[0]->getAutresActions()[i]->getNom() == m_action->getNom()){
                posX = etat->getOrdreTour()[0]->getPositionX();
                posY = etat->getOrdreTour()[0]->getPositionY();
                break;
            }
        }

        int portee = m_action->getPortee();

        int posInit = posX+largeur*posY;
        int posTemp = posInit;

        int cX = 0;
        int cY = 0;

        for (size_t j = 0; j < etat->getEntites().size() ; j++){
            if(etat->getEntites()[j]->getEstVivant() && etat->getNiveau() == etat->getEntites()[j]->getNiveau()){
                cX = etat->getEntites()[j]->getPositionX();
                cY = etat->getEntites()[j]->getPositionY();
                if (abs(cX - posX) + abs(cY - posY) <= portee){
                    mapLib[cX + cY * largeur] = true;
                    /*if (cY == posY && cX > posX){
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
                    }*/
                }
            }
        }

 
        // for(int i = 0; i < total; i++){
        //      std::cout << mapLib[i] << " // ";
        //}

        m_mapLib = mapLib;
    }

    bool CommandeActionSupplementaire::execute (state::State* state){
        state::Entite *prs = state->getOrdreTour()[0];
        prs->effectuerActionSupp(m_action,m_cible);
        return true;
    }

    Json::Value CommandeActionSupplementaire::serialize (){
        Json::Value value;
        value["test"] = "test";
        return value;
    }
    // Setters and Getters
  

}


