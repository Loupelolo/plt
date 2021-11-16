#include "ActionSuppOff.h"

namespace state {

// Constructeur & destructeur

ActionSuppOff::ActionSuppOff () {

}

ActionSuppOff::~ActionSuppOff () {

}



// Setters & Getters

std::vector<bool> ActionSuppOff::getStatuts (){
    return m_statuts;
}

void ActionSuppOff::setStatuts (std::vector<bool> statuts){
    m_statuts = statuts;
}



// Méthodes

void ActionSuppOff::attaque (Entite cible){
    //attaque avec l'arme offensive
}



}
