#include "ActionSuppOff.h"

namespace state {
    ActionSuppOff::ActionSuppOff () {

    }

    ActionSuppOff::~ActionSuppOff () {

    }

    void ActionSuppOff::attaque (Entite cible){
        //attaque avec l'arme offensive
    }

    std::vector<bool> ActionSuppOff::getStatuts (){
        return m_statuts;
    }

    void ActionSuppOff::setStatuts (std::vector<bool> statuts){
        m_statuts = statuts;
    }
}
