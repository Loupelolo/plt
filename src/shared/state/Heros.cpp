#include "Heros.h"
#include <iostream>

namespace state {

    // Constructeur & destructeur

    Heros::Heros () {
        m_nom = "Jane Doe";
        m_classe = ARCHER;
        m_type = 0;
        m_niveau = 1;
        m_positionX = 0;
        m_positionY = 0;
        m_PV = 100;
        m_PM = 100;
        m_equipement = {};
        m_autresActions = {};
        m_stats = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        m_statutsSubis = {true, false, false, false, false, false};
    }

    Heros::Heros (std::string nom, Classe classe){
        m_nom = nom;
        m_classe = classe;
        m_type = 0;
        m_niveau = 1;
        m_positionX = 0;
        m_positionY = 0;
        m_PV = 100;
        m_PM = 100;
        m_equipement = {};
        m_autresActions = {};
        m_stats = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        m_statutsSubis = {true, false, false, false, false, false};

        initialisation();
    }

    Heros::Heros (std::string nom, Classe classe, int niveau, int positionX, int positionY, std::vector<Equipement> equipement, std::vector<ActionSupp> autresActions){
        m_nom = nom;
        m_type = classe;
        m_niveau = niveau;
        m_positionX = positionX;
        m_positionY = positionY;
        m_PV = 100;
        m_PM = 100;
        m_equipement = equipement;
        m_autresActions = autresActions;
        m_stats = {0,0,0,0,0,0,0,0,0};
        m_statutsSubis = {true, false, false, false, false, false};
        m_classe = classe;
        this->initialisation();
    }

    Heros::Heros (const Heros &p){
        m_nom = p.m_nom;
        m_type = p.m_type;
        m_niveau = p.m_niveau;
        m_positionX = p.m_positionX;
        m_positionY = p.m_positionY;
        m_PV = p.m_PV;
        m_PM = p.m_PM;
        m_equipement = p.m_equipement;
        m_autresActions = p.m_autresActions;
        m_stats = p.m_stats;
        m_statutsSubis = p.m_statutsSubis;
        m_classe = p.m_classe;
    }

    Heros::~Heros () {

    }



    // Setters & Getters

    Classe Heros::getClasse (){
        return m_classe;
    }

    void Heros::setClasse (Classe classe){
        m_classe = classe;
    }



    // Méthodes

    void Heros::initialisation (){
        switch (m_classe)
        {
        case ARCHER:
            m_stats = {40, 40, 30, 25, 60, 30, 10, 30, 8};
            break;
        case ASSASSIN:
            m_stats = {30, 50, 40, 30, 70, 20, 2, 20, 11};
            break;
        case DRUIDE:
            m_stats = {50, 40, 10, 10, 90, 60, 3, 6, 6};
            break;
        case GUERRIER:
            m_stats = {75, 60, 5, 5, 110, 10, 1, 5, 5};
            break;
        case MAGE:
            m_stats = {70, 30, 10, 10, 90, 50, 2, 8, 5};
            break;
        case PRETRE:
            m_stats = {30, 40, 10, 10, 100, 70, 5, 5, 6};
            break;
        default:
            break;
        }
        m_PV = m_stats[PVMAX];
        m_PM = m_stats[PMMAX];
    }

    void Heros::obtenirEquipement (Equipement newEquipement){
        //obtention d'un equipement
        m_equipement.push_back(newEquipement);
    }

    void Heros::lacherEquipement (Equipement oldEquipement){
        //suppression d'un equipement
        unsigned int i = 0;
        while(i < m_equipement.size() && m_equipement[i] != oldEquipement ){
            i++;
        }
        if (m_equipement[i] == oldEquipement) m_equipement.erase(m_equipement.begin() + i);
        else std::cout<<"equipement non present"<<std::endl;
    }

    void Heros::obtenirActionSupp (ActionSupp newActionSupp){
        //ajout d'une action
        m_autresActions.push_back(newActionSupp);
    }
}
