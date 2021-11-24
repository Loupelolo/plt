#include <engine.h>
#include <state.h>

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
        Json::Value value;
        value["test"] = "test";
        return value;
    }
}