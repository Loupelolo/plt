#include "Decor.h"

namespace state {

// Constructeur & destructeur

Decor::Decor () {
}

Decor::Decor (std::vector<int> map) {
    m_map = map;
}

Decor::~Decor () {

}



// Setters & Getters

int Decor::getHauteur(){
    return m_hauteur;
}

void Decor::setHauteur(int hauteur){
    m_hauteur = hauteur;
}

int Decor::getLargeur(){
    return m_largeur;
}

void Decor::setLargeur(int largeur){
    m_largeur = largeur;
}

std::vector<int> Decor::getMap(){
    return m_map;
}

void Decor::setMap(std::vector<int> map){
    m_map = map;
}

std::vector<int> Decor::getMeteo(){
    return m_meteo;
}

void Decor::setMeteo(std::vector<int> meteo){
    m_meteo = meteo;
}

std::vector<int> Decor::getLumiere(){
    return m_lumiere;
}

void Decor::setLumiere(std::vector<int> lumiere){
    m_lumiere = lumiere;
}



// Méthodes

void Decor::action (){
    //declenche l'action de la case
}



}
