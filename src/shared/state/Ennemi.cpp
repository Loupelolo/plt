#include "Ennemi.h"

namespace state {
    Ennemi::Ennemi () {

    }

    Ennemi::Ennemi (std::string nom, std::string race){
        m_nom = nom;
        m_race = race;
    }

    Ennemi::~Ennemi () {

    }

    void Ennemi::activer (){
        //activer l'ennemi lorsque les joueurs sont suffisamment proche de lui
    }

    std::string Ennemi::getRace (){
        return m_race;
    }

    void Ennemi::setRace (std::string race){
        m_race = race;
    }

    bool Ennemi::getActif (){
        return m_actif;
    }

    void Ennemi::setActif (bool actif){
        m_actif = actif;
    }
}
