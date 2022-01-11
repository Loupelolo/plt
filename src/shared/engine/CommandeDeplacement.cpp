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

    void CommandeDeplacement::ActuMapLib (state::State* etat){
        //init
        int largeur = etat->getDecor().getLargeur();
        int total = etat->getDecor().getMap().size();
        std::vector<int> mapLib(total,false);
        

        int mvt = etat->getOrdreTour()[0]->getStat(state::DEPLACEMENT);
        int posX = etat->getOrdreTour()[0]->getPositionX();
        int posY = etat->getOrdreTour()[0]->getPositionY();

        int posInit = posX+largeur*posY;
        int posTemp = posInit;
        mapLib[posInit] = true;


        for (int a=0; a<5; a++){    
            for(int abs=0;abs<=mvt;abs++){
                for(int ord=0;ord<=mvt;ord++){
                    if(abs+ord <=mvt){
                        for(int t=0; t<4; t++){
                            switch(t){
                                case 0 :
                                    posTemp = posInit+abs+ord*largeur;
                                    if((posTemp>=(total-largeur)) || (posTemp%largeur==(largeur-1))) {posTemp=posInit;}
                                    break;   
                                case 1 :
                                    posTemp = posInit+abs-ord*largeur;
                                    if((posTemp<largeur) || (posTemp%largeur==(largeur-1))) {posTemp=posInit;}
                                    break;
                                case 2 :
                                    posTemp = posInit-abs+ord*largeur;
                                    if((posTemp>=(total-largeur)) || (posTemp%largeur==0)) {posTemp=posInit;}
                                    break;
                                case 3 :
                                    posTemp = posInit-abs-ord*largeur;
                                    if((posTemp<largeur) || (posTemp%largeur==0)) {posTemp=posInit;}
                                    break;
                                
                            }
                            if(mapLib[posTemp-1] || mapLib[posTemp-largeur] || mapLib[posTemp+1] || mapLib[posTemp+largeur]){
                                if (etat->getDecor().getMap()[posTemp]==state::SOL || etat->getDecor().getMap()[posTemp]==state::TRES || etat->getDecor().getMap()[posTemp]==state::SECR){
                                    mapLib[posTemp] = true;
                                }
                                for (size_t j = 1; j < etat->getEntites().size() ; j++){
                                    if ((etat->getEntites()[j]->getPositionX() == posTemp%largeur) && (etat->getEntites()[j]->getPositionY() == posTemp/largeur)){
                                        mapLib[posTemp] = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        mapLib[posInit] = false;
       

    //    for(int i = 0; i < total; i++){
    //         std::cout << mapLib[i] << " // ";
    //     }

        m_mapLib = mapLib;
    }

    bool CommandeDeplacement::handleDeplacement (state::State* etat ){
        
        // bool distance = false;
        // bool collision = false;

        
        // int mvt = etat->getOrdreTour()[0]->getStat(8);
        //int posX = etat->getOrdreTour()[0]->getPositionX();
        //int posY = etat->getOrdreTour()[0]->getPositionY();
        int largeur = etat->getDecor().getLargeur();

        this->ActuMapLib(etat);

        if(m_mapLib[m_x + m_y *largeur]){
            return true;
        }

        return false;
        


        // int length = etat->getEntites().size();

        // if (abs(m_x-posX)+abs(m_y-posY)<=mvt){
        //     if (etat->getDecor().getMap()[m_x+m_y*largeur]==state::SOL || etat->getDecor().getMap()[m_x+m_y*largeur]==state::TRES || etat->getDecor().getMap()[m_x+m_y*largeur]==state::SECR){
        //         distance = true;
        //     }
        // }

        // for (int i = 0; i < length ; i++){
        //     if ((etat->getEntites()[i]->getPositionX() == m_x) && (etat->getEntites()[i]->getPositionY() == m_y)){
        //         collision = false;
        //         break;
        //     }
        //     else {collision = true;}
        // }

        // if (distance && collision){
        //     return true;
        // }
        // return false;
    }

    bool CommandeDeplacement::execute (state::State* state){
        //state::State& st = engine->getState();
        state::Entite *prs = state->getOrdreTour()[0];
        prs->deplacement(m_x,m_y);

        //st.actualiserEntite(prs);
        //engine->setState(st);
        return true;
    }

    Json::Value CommandeDeplacement::serialize(){
        Json::Value value;
        value["test"] = "test";
        return value;
    }
}