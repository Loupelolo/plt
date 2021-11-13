#include "State.h"
#include <iostream>

namespace state {
    State::State () {

    }

    State::~State () {

    }

    void State::nouveauTour (){
        //initialisation d'un nouveau tour
    }

    void State::joueurSuivant (){
        //passage au personnage suivant
    }

    int State::getNbTour (){
        return m_nbTour;
    }

    void State::setNbTour (int nbTour){
        m_nbTour = nbTour;
    }

    std::vector<Decor> State::getDecors (){
        return m_terrain;
    }

    void State::setDecors (std::vector<Decor> decors){
        m_terrain = decors;
    }

    std::vector<Entite> State::getEntites (){
        return m_entites;
    }

    void State::setEntites (std::vector<Entite> entites){
        m_entites = entites;
    }

    std::vector<Entite> State::getOrdreTour (){
        return m_ordreTour;
    }

    void State::setOrdreTour (std::vector<Entite> ordreTour){
        m_ordreTour = ordreTour;
    }

    int State::getIndiceTour (){
        return m_indiceTour;
    }

    void State::setIndiceTour (int indiceTour){
        m_indiceTour = indiceTour;
    }

    int State::getDe (){
        return m_de;
    }

    void State::setDe (int de){
        m_de = de;
    }

    void State::setTerrain (std::vector<int> map){
        std::vector<Decor> decor;
        m_terrain.resize(map.size());
        for(unsigned int i=0; i<map.size();i++){
            m_terrain[i].setType(map[i]);
            m_terrain[i].setPositionX(i%4);
            m_terrain[i].setPositionY(i/4);
        }
    }
}
