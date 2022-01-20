#include "Ennemi.h"

namespace state {

    // Constructeur & destructeur

    Ennemi::Ennemi () {
        m_nom = "John Doe";
        m_estVivant = true;
        m_type = 6;
        m_niveau = 1;
        m_positionX = 0;
        m_positionY = 0;
        m_PV = 100;
        m_PM = 100;
        m_equipement = {};
        m_autresActions = {};
        m_stats = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        m_statutsSubis = {true, false, false, false, false, false};

        m_race = ORC;
        m_actif = false;

        initialisation();
    }

    Ennemi::Ennemi (std::string nom, Race race) {
        m_nom = nom;
        m_estVivant = true;
        m_type = 6 + race;
        m_niveau = 1;
        m_positionX = 0;
        m_positionY = 0;
        m_PV = 100;
        m_PM = 100;
        m_equipement = {};
        m_autresActions = {};
        m_stats = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        m_statutsSubis = {true, false, false, false, false, false};

        m_race = race;
        m_actif = false;

        initialisation();
    }

    Ennemi::Ennemi (std::string nom, Race race, int niveau, int positionX, int positionY, std::vector<Equipement> equipement, std::vector<ActionSupp*> autresActions) {
        m_nom = nom;
        m_estVivant = true;
        m_type = 6 + race;
        m_niveau = niveau;
        m_positionX = positionX;
        m_positionY = positionY;
        m_PV = 100;
        m_PM = 100;
        m_equipement = equipement;
        m_autresActions = autresActions;
        m_stats = {0,0,0,0,0,0,0,0,0};
        m_statutsSubis = {true, false, false, false, false, false};

        m_race = race;
        m_actif = false;

        initialisation();
    }

    Ennemi::Ennemi (const Ennemi &p) {
        m_nom = p.m_nom;
        m_estVivant = p.m_estVivant;
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

        m_race = p.m_race;
        m_actif = p.m_actif;
    }

    Ennemi::~Ennemi () {

    }



    // Setters & Getters

    Race Ennemi::getRace () {
        return m_race;
    }

    void Ennemi::setRace (Race race) {
        m_race = race;
    }

    bool Ennemi::getActif () {
        return m_actif;
    }

    void Ennemi::setActif (bool actif) {
        m_actif = actif;
    }



    // Méthodes

    void Ennemi::activer () {
        //activer l'ennemi lorsque les joueurs sont suffisamment proche de lui
    }

    void Ennemi::initialisation() {
        switch (m_race)
        {
        case SQUELETTE:
            m_stats = {40, 40, 30, 25, 60, 30, 10, 35, 8};
            break;
        case SERPENT:
            m_stats = {30, 50, 40, 30, 70, 20, 2, 25, 7};
            break;
        case ARAIGNEE:
            m_stats = {50, 40, 10, 10, 90, 60, 3, 7, 6};
            break;
        case ORC:
            m_stats = {75, 60, 5, 5, 110, 10, 1, 5, 5};
            break;
        case FANTOME:
            m_stats = {70, 30, 10, 10, 90, 50, 2, 3, 5};
            break;
        case ZOMBIE:
            m_stats = {30, 40, 10, 10, 100, 70, 5, 1, 6};
            break;
        default:
            break;
        }
        m_PV = m_stats[PVMAX];
        m_PM = m_stats[PMMAX];
    }
}
