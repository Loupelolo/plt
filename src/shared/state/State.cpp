#include "State.h"
#include "Decor.h"
#include <iostream>

namespace state {

// Constructeur & destructeur

State::State () {

}

State::~State () {

}



// Setters & Getters

int State::getNbTour (){
    return m_nbTour;
}

void State::setNbTour (int nbTour){
    m_nbTour = nbTour;
}

Decor State::getDecor (){
    return m_decor;
}

void State::setDecor (Decor decors){
    m_decor = decors;
}

std::vector<Entite> State::getEntites (){
    return m_entites;
}

void State::setEntites (std::vector<Entite> entites){
    m_entites = entites;
}

std::vector<Entite*> State::getOrdreTour (){
    return m_ordreTour;
}

void State::setOrdreTour (std::vector<Entite*> ordreTour){
    m_ordreTour = ordreTour;
}

int State::getDe (){
    return m_de;
}

void State::setDe (int de){
    m_de = de;
}



// Méthodes

void State::nouveauTour (){
    //initialisation d'un nouveau tour
}

void State::joueurSuivant (){
    //passage au personnage suivant
}
}
