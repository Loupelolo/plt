#include <engine.h>
#include <state.h>

namespace engine {

    Commande::Commande () {
        m_commandeTypeId = Deplacement;
    }

    Commande::~Commande () {
    
    }

    CommandeTypeId Commande::getCommandeTypeId(){
        return m_commandeTypeId;
    }

    state::Entite* Commande::getCible() {

    }


    bool Commande::handleDeplacement (state::State* etat){
        return false;
    }


    bool Commande::handleAttaque (state::State* state){
        return false;
    }

    bool Commande::handleActionSupplementaire (state::Entite perso){
        return false;
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