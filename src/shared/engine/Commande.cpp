#include "Commande.h"

namespace engine {

    Commande::Commande () {

    }

    Commande::~Commande () {
    
    }

    CommandeTypeId Commande::getCommandeTypeId(){
        return m_commandeTypeId;
    }

    bool Commande::execute (Engine* engine){
        return true;
    }

    Json::Value Commande::serialize(){
        
    }
}