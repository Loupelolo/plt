#include "Entite.h"

//ordre des stats : attaque, defense, esquive, coupCritique, PVMax, PMMax, portée, initiative, deplacement

namespace state {

// Constructeur & destructeur

Entite::Entite () {

}

Entite::Entite (std::string nom) {
    m_nom = nom;
    m_statutsSubis = {false, false, false, false, false};
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



// Méthodes

void Entite::initialisation (){
    //initialisation d'une entite
}

void Entite::deplacement (int dx, int dy){
    //deplacement de l'entite
}

void Entite::attaque (Entite cible){
    //attaque basique d'une autre entite
}

void Entite::effectuerActionSupp (ActionSupp action){
    //effectuer une action particulière
}

void Entite::degats (int degatsSubis, int statutsSubis){
    //infliger des degats
}

void Entite::mort (){
    // mort de l'entite
}


}
