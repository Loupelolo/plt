#include "State.h"

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

    ElementTab State::getDecors (){
        return m_terrain;
    }

    void State::setDecors (ElementTab decors){
        m_terrain = decors;
    }

    ElementTab State::getEntites (){
        return m_entites;
    }

    void State::setEntites (ElementTab entites){
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


}
