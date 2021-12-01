#include "Equipement.h"

namespace state {

    // Constructeur & destructeur

    Equipement::Equipement () {
        m_nom = "no name";
        m_bonusStat = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        m_statutInflige = SNONE;
    }

    Equipement::Equipement (std::string nom) {
        m_nom = nom;
        m_bonusStat = {0,0,0,0,0,0,0,0,0};
        m_statutInflige = SNONE;
    }

    Equipement::Equipement (std::string nom, Statut statutInflige, std::vector<int> bonusStat) {
        m_nom = nom;
        m_bonusStat = bonusStat;
        m_statutInflige = statutInflige;
    }

    Equipement::Equipement (const Equipement &p) {
        m_nom = p.m_nom;
        m_bonusStat = p.m_bonusStat;
        m_statutInflige = p.m_statutInflige;
    }

    Equipement::~Equipement () {
        
    }

    bool Equipement::operator==(Equipement equip){
        bool resultat = true;
        if(m_nom != equip.getNom() || m_bonusStat != equip.getBonusStat() || m_statutInflige != equip.getStatutInflige()) resultat = false;    
        return resultat;
    }

    bool Equipement::operator!=(Equipement equip){
        bool resultat = true;
        if(m_nom == equip.getNom() && m_bonusStat == equip.getBonusStat() && m_statutInflige == equip.getStatutInflige()) resultat = false;    
        return resultat;
    }



    // Setters & Getters

    std::string Equipement::getNom (){
        return m_nom;
    }

    void Equipement::setNom (std::string nom){
        m_nom = nom;
    }

    Statut Equipement::getStatutInflige (){
        return m_statutInflige;
    }

    void Equipement::setStatutInflige (Statut statutInflige){
        m_statutInflige = statutInflige;
    }

    std::vector<int> Equipement::getBonusStat (){
        return m_bonusStat;
    }

    void Equipement::setBonusStat (std::vector<int> bonusStat){
        m_bonusStat = bonusStat;
    }
}
