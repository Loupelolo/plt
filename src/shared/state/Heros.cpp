#include "Heros.h"

namespace state {

// Constructeur & destructeur

Heros::Heros () {

}

Heros::Heros (std::string nom, Classe classe){
    m_nom = nom;
    m_classe = classe;
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
}

void Heros::lacherEquipement (Equipement oldEquipement){
    //suppression d'un equipement
}

void Heros::obtenirActionSupp (ActionSupp newActionSupp){
    //ajout d'une action
}


}
