#include "ActionSupp.h"
#include <iostream>

    namespace state {

    // Constructeur & destructeur

    ActionSupp::ActionSupp () {
        m_nom = "Action";
        m_stat = 0;
    }

    ActionSupp::ActionSupp (std::string nom) {
        m_nom = nom;
        m_stat = 0;    
    }

    ActionSupp::ActionSupp (const ActionSupp &p) {
        m_nom = p.m_nom;
        m_stat = p.m_stat;
    }

    ActionSupp::~ActionSupp () {
        
    }



    // Setters & Getters

    std::string ActionSupp::getNom () {
        return m_nom;
    }

    void ActionSupp::setNom (std::string nom) {
        m_nom = nom;
    }

    int ActionSupp::getStat () {
        return m_stat;
    }

    void ActionSupp::setStat (int stat) {
        m_stat = stat;
    }

    int ActionSupp::getPortee (){
        return m_portee;
    }

    void ActionSupp::setPortee (int portee) {
        m_portee = portee;
    }

    void ActionSupp::effectuerAction (Entite* cible) {
        std::cout<<"Mais qu'est-ce que je fais la"<<std::endl;
    }
    
}
