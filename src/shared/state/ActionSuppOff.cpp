#include "ActionSuppOff.h"

namespace state {

    // Constructeur & destructeur

    ActionSuppOff::ActionSuppOff () {
        m_nom = "Action";
        m_stat = 0;
        m_portee = 0;
        m_statut = SNONE;
    }

    ActionSuppOff::ActionSuppOff (std::string nom, int stat, int portee, Statut statut) {
        m_nom = nom;
        m_stat = stat;
        m_portee = portee;
        m_statut = statut;
    }

    ActionSuppOff::ActionSuppOff (const ActionSuppOff &p) {
        m_nom = p.m_nom;
        m_stat = p.m_stat;
        m_portee = p.m_portee;
        m_statut = p.m_statut;
    }

    ActionSuppOff::~ActionSuppOff () {

    }



    // Setters & Getters

    Statut ActionSuppOff::getStatut () {
        return m_statut;
    }

    void ActionSuppOff::setStatut (Statut statut) {
        m_statut = statut;
    }



    // Méthodes

    void ActionSuppOff::effectuerAction (Entite* cible) {
        //attaque avec l'arme offensive
        cible->Entite::degats(m_stat, m_statut);
    }



}