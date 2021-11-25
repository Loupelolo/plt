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


    bool Commande::handleDeplacement (state::Entite perso, std::vector<int> map, int largeur){
        return false;
    }
    bool Commande::handleCollision (std::vector<state::Entite> listeEntites){
        return false;
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