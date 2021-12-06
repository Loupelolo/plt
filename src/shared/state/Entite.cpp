#include "state.h"
#include <iostream>

//ordre des stats : attaque, defense, esquive, coupCritique, PVMax, PMMax, portée, initiative, deplacement

namespace state {

    // Constructeur & destructeur

    Entite::Entite () {

    }

    Entite::Entite (std::string nom) {
        m_nom = nom;
        m_type = 0;
        m_niveau = 1;
        m_positionX = 0;
        m_positionY = 0;
        m_PV = 100;
        m_PM = 100;
        m_equipement = {};
        m_autresActions = {};
        m_stats = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //attaque, defense, esquive, coup critique, pvmax, pmmax, portee, initiative, deplacement
        m_statutsSubis = {true, false, false, false, false, false};
    }

    Entite::Entite (const Entite &p){
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
    }

    Entite::~Entite () {

    }



    // Setters & Getters

    std::string Entite::getNom (){
        return m_nom;
    }

    void Entite::setNom (std::string nom){
        m_nom = nom;
    }

    int Entite::getType(){
        return m_type;
    }

    void Entite::setType(int type){
        m_type = type;
    }

    int Entite::getNiveau (){
        return m_niveau;
    }

    void Entite::setNiveau (int niveau){
        m_niveau = niveau;
    }

    int Entite::getPositionX(){
        return m_positionX;
    }

    void Entite::setPositionX(int positionX){
        m_positionX = positionX;
    }

    int Entite::getPositionY(){
        return m_positionY;
    }

    void Entite::setPositionY(int positionY){
        m_positionY = positionY;
    }

    int Entite::getPV (){
        return m_PV;
    }

    void Entite::setPV (int PV){
        m_PV = PV;
    }

    int Entite::getPM (){
        return m_PM;
    }

    void Entite::setPM (int PM){
        m_PM = PM;
    }

    std::vector<Equipement> Entite::getEquipement (){
        return m_equipement;
    }

    void Entite::setEquipement (std::vector<Equipement> equipement){
        m_equipement = equipement;
    }

    std::vector<ActionSupp> Entite::getAutresActions (){
        return m_autresActions;
    }

    void Entite::setAutresActions (std::vector<ActionSupp> autresActions){
        m_autresActions = autresActions;
    }

    int Entite::getStat (int index){
        return m_stats[index];
    }

    std::vector<int> Entite::getStats (){
        return m_stats;
    }

    void Entite::setStat (int index, int stat){
        m_stats[index] = stat;
    }

    void Entite::setStats (std::vector<int> stats){
        m_stats = stats;
    }

    bool Entite::getStatutSubi (int index){
        return m_statutsSubis[index];
    }

    std::vector<bool> Entite::getStatutsSubis (){
        return m_statutsSubis;
    }

    void Entite::setStatutSubi (int index, bool statutSubi){
        m_statutsSubis[index] = statutSubi;
    }

    void Entite::setStatutsSubis (std::vector<bool> statutsSubis){
        m_statutsSubis = statutsSubis;
    }

    void Entite::attaque (Entite* cible){
        //attaque basique d'une autre entite
        std::cout<<m_stats[ATTAQUE]<<std::endl;
        cible->degats(m_stats[ATTAQUE], 0);
    }
  
    // Méthodes

    void Entite::initialisation (){
        //initialisation d'une entite
        m_stats[0] = 10;
    }

    void Entite::deplacement (int dx, int dy){
        //deplacement de l'entite
        m_positionX += dx;
        m_positionY += dy;
    }

    void Entite::attaque (Entite* cible){
        //attaque basique d'une autre entite
        std::cout<<m_stats[0]<<std::endl;
        cible->degats(m_stats[0], 0);
    }

    void Entite::effectuerActionSupp (ActionSupp* action, Entite* cible){
        //effectuer une action particulière
        action->effectuerAction(cible);
    }

    void Entite::degats (int degatsSubis, int statutsSubis){
        //infliger des degats
        std::cout<<"je suis dans degats"<<std::endl;
        std::cout<<m_PV<<std::endl;
        m_PV = m_PV - degatsSubis;
        std::cout<<m_PV<<std::endl;
        if(statutsSubis != 0) m_statutsSubis[statutsSubis] = true;
    }

    void Entite::soin (int pvRecup, bool soigneStatuts){
        //soigner des degats
        std::cout<<"je suis dans soin"<<std::endl;
        std::cout<<"PV ="<<m_PV<<std::endl;
        std::cout<<"PVMax ="<<m_stats[PVMAX]<<std::endl;

        if(m_PV + pvRecup < m_stats[PVMAX]){
            m_PV += pvRecup;
        } else {
            m_PV = m_stats[PVMAX];
        }
        std::cout<<m_PV<<std::endl;
        if(soigneStatuts) m_statutsSubis = {true, false, false, false, false, false};
    }

    void Entite::mort (){
        // mort de l'entite
    }
}
