#include "state.h"

namespace state {

// Constructeur & destructeur

Heros::Heros () {
    m_nom = "Jane Doe";
    m_classe = ARCHER;
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

}

Heros::Heros (std::string nom, Classe classe){
    m_nom = nom;
    m_classe = classe;
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
}

Heros::Heros (const Entite &p){
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

    m_classe = p.m_classe;
}

Heros::~Heros () {

}



// Setters & Getters

Classe Heros::getClasse (){
    return m_classe;
}

void Heros::setClasse (Classe classe){
    m_classe = classe;
}



// Méthodes

void Heros::obtenirEquipement (Equipement newEquipement){
    //obtention d'un equipement
    m_equipement.push_back(newEquipement);
}

void Heros::lacherEquipement (Equipement oldEquipement){
    //suppression d'un equipement
    m_equipement.erase(oldEquipement);
}

void Heros::obtenirActionSupp (ActionSupp newActionSupp){
    //ajout d'une action
    m_autresActions.push_back(newActionSupp);
}


}
