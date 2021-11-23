#include "Ennemi.h"

namespace state {

// Constructeur & destructeur

Ennemi::Ennemi () {
    m_nom = "John Doe";
    m_type = 0;
    m_niveau = 1;
    m_positionX = 0;
    m_positionY = 0;
    m_PV = 100;
    m_PM = 100;
    m_equipement = {};
    m_autresActions = {};
    m_stats = {0,0,0,0,0,0,0,0,0};
    m_statutsSubis = {false, false, false, false, false};

    m_race = ORC;
    m_actif = false;
}

Ennemi::Ennemi (std::string nom, Race race){
    m_nom = nom;
    m_type = 0;
    m_niveau = 1;
    m_positionX = 0;
    m_positionY = 0;
    m_PV = 100;
    m_PM = 100;
    m_equipement = {};
    m_autresActions = {};
    m_stats = {0,0,0,0,0,0,0,0,0};
    m_statutsSubis = {false, false, false, false, false};

    m_race = race;
    m_actif = false;
}

Ennemi::Ennemi (const Ennemi &p){
    m_nom = p.m_nom;
    m_type = p.m_type;
    m_niveau = p.m_niveau;
    m_positionX = p.m_positionX;
    m_positionY = p.m_positionY;
    m_PV = p.m_PV;
    m_PM = p.m_PM;
    m_equipement = p.m_equipement;
    m_autresActions = p.m_autresActions;
    m_stats = p.m_stats;
    m_statutsSubis = p.m_statutsSubis;

    m_race = p.m_race;
    m_actif = p.m_actif;
}

Ennemi::~Ennemi () {

}



// Setters & Getters

Race Ennemi::getRace (){
    return m_race;
}

void Ennemi::setRace (Race race){
    m_race = race;
}

bool Ennemi::getActif (){
    return m_actif;
}

void Ennemi::setActif (bool actif){
    m_actif = actif;
}



// Méthodes

void Ennemi::activer (){
    //activer l'ennemi lorsque les joueurs sont suffisamment proche de lui
}


}
