#include "ActionSupp.h"

namespace state {
    ActionSupp::ActionSupp () {

    }

    ActionSupp::~ActionSupp () {
        
    }

    std::string ActionSupp::getNom (){
        return m_nom;
    }

    void ActionSupp::setNom (std::string nom){
        m_nom = nom;
    }

    std::vector<int> ActionSupp::getStats (){
        return m_stats;
    }

    void ActionSupp::setStats (std::vector<int> stats){
        m_stats = stats;
    }
}
