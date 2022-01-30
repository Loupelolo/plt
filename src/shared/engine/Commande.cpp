#include <engine.h>
#include <state.h>
#include <iostream>

namespace engine {

    Commande::Commande () {
        m_commandeTypeId = Deplacement;
    }

    Commande::~Commande () {
    
    }

    CommandeTypeId Commande::getCommandeTypeId(){
        return m_commandeTypeId;
    }

    std::vector<bool> Commande::getMapLib(){
        return m_mapLib;
    }


    bool Commande::handleDeplacement (state::State* etat){
        return false;
    }


    bool Commande::handleAttaque (state::State* state){
        return false;
    }

    bool Commande::handleActionSupplementaire (state::State* etat){
        return false;
    }

    void Commande::ActuMapLib (state::State* etat){
        
    }

    bool Commande::execute (state::State* state){
        return true;
    }

    Json::Value Commande::serialize(){
        Json::Value value;
        value["test"] = "test";
        return value;
    }
}