#include "Heros.h"

namespace state {
    Heros::Heros () {

    }

    Heros::Heros (std::string nom, std::string classe){
        m_nom = nom;
        m_classe = classe;
    }

    Heros::~Heros () {

    }

    void Heros::obtenirEquipement (Equipement newEquipement){
        //obtention d'un equipement
    }
    
    void Heros::lacherEquipement (Equipement oldEquipement){
        //suppression d'un equipement
    }

    void Heros::obtenirActionSupp (ActionSupp newActionSupp){
        //ajout d'une action
    }

    std::string Heros::getClasse (){
        return m_classe;
    }

    void Heros::setClasse (std::string classe){
        m_classe = classe;
    }
}
