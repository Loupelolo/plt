#include "Equipement.h"

namespace state {

// Constructeur & destructeur

Equipement::Equipement () {

}

Equipement::~Equipement () {
    
}



// Setters & Getters

std::string Equipement::getNom (){
    return m_nom;
}

void Equipement::setNom (std::string nom){
    m_nom = nom;
}

int Equipement::getStatutInflige (){
    return m_statutInflige;
}

void Equipement::setStatutInflige (int statutInflige){
    m_statutInflige = statutInflige;
}

std::vector<int> Equipement::getBonusStat (){
    return m_bonusStat;
}

void Equipement::setBonusStat (std::vector<int> bonusStat){
    m_bonusStat = bonusStat;
}



}
