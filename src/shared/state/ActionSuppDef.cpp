#include "ActionSuppDef.h"
#include <iostream>

namespace state {

    // Constructeur & destructeur

    ActionSuppDef::ActionSuppDef () {
        m_nom = "Action";
        m_stat = 0;
        m_soigneStatuts = false;
    }

    ActionSuppDef::ActionSuppDef (std::string nom, int stat, bool soigneStatuts) {
        m_nom = nom;
        m_stat = stat;
        m_soigneStatuts = soigneStatuts;
    }

    ActionSuppDef::ActionSuppDef (const ActionSuppDef &p) {
        m_nom = p.m_nom;
        m_stat = p.m_stat;
        m_soigneStatuts = p.m_soigneStatuts;
    }

    ActionSuppDef::~ActionSuppDef () {

    }
        


    // Setters & Getters

    bool ActionSuppDef::getSoigneStatuts () {
        return m_soigneStatuts;
    }

    void ActionSuppDef::setSoigneStatuts (bool soigneStatuts) {
        m_soigneStatuts = soigneStatuts;
    }



    // Méthodes

    void ActionSuppDef::effectuerAction (Entite* cible) {
        //soin d'une cible
        cible->Entite::soin(m_stat, m_soigneStatuts);
    }
}
