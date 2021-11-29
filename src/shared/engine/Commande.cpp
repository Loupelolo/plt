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


<<<<<<< HEAD
    bool Commande::handleDeplacement (state::Entite perso, std::vector<int> map, int largeur){
=======
    bool Commande::handleDeplacement (state::Entite perso, std::vector<state::TypeTerrain> map, int largeur){
>>>>>>> master
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