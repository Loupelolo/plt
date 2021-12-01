#include "Decor.h"
#include <iostream>

namespace state {

    // Constructeur & destructeur

    Decor::Decor () {
    }

    Decor::Decor (std::vector<TypeTerrain> map) {
        m_map = map;
    }

    Decor::Decor (int largeur, int hauteur, std::vector<TypeTerrain> map) {
        m_hauteur = hauteur;
        m_largeur = largeur;
        m_map = map;
    }

    Decor::Decor (int largeur, int hauteur, std::vector<TypeTerrain> map, std::vector<int> meteo, std::vector<int> lumiere) {
        m_hauteur = hauteur;
        m_largeur = largeur;
        m_map = map;
        m_meteo = meteo;
        m_lumiere = lumiere;
    }

    Decor::Decor (const Decor &p) {
        m_hauteur = p.m_hauteur;
        m_largeur = p.m_largeur;
        m_map = p.m_map;
        m_meteo = p.m_meteo;
        m_lumiere = p.m_lumiere;
    }

    Decor::~Decor () {

    }



    // Setters & Getters

    int Decor::getLargeur(){
        return m_largeur;
    }

    void Decor::setLargeur(int largeur){
        m_largeur = largeur;
    }

    int Decor::getHauteur(){
        return m_hauteur;
    }

    void Decor::setHauteur(int hauteur){
        m_hauteur = hauteur;
    }

    std::vector<TypeTerrain> Decor::getMap(){
        return m_map;
    }

    void Decor::setMap(std::vector<TypeTerrain> map){
        m_map = map;
    }

    std::vector<int> Decor::getMeteo(){
        return m_meteo;
    }

    void Decor::setMeteo(std::vector<int> meteo){
        m_meteo = meteo;
    }

    std::vector<int> Decor::getLumiere(){
        return m_lumiere;
    }

    void Decor::setLumiere(std::vector<int> lumiere){
        m_lumiere = lumiere;
    }



    // Méthodes

    void Decor::action (int posX, int posY, Entite* aEntite){
        //declenche l'action de la case
        int indiceMap = posX + m_largeur*posY;
        
        switch(m_map[indiceMap])
        {
            case  TNON: 
                //cas impossible
                std::cout<<"None"<<std::endl;
                break;

            case SOL: 
                //aucune action
                std::cout<<"Sol"<<std::endl;
                break;

            case MUR: 
                //cas impossible
                std::cout<<"Mur"<<std::endl;
                break;

            case EAU: 
                //cas impossible
                std::cout<<"eau"<<std::endl;
                break;

            case OBST: 
                //cas impossible
                std::cout<<"obstacle"<<std::endl;
                break;

            case PORT: 
                //ouverture de la porte
                m_map[indiceMap] = SOL;
                std::cout<<"porte"<<std::endl;
                break;

            case  SECR: 
                //obtention d'un equipement ou sort
                m_map[indiceMap] = MUR;
                std::cout<<"secret"<<std::endl;
                break;

            case PIEG: 
                aEntite->Entite::degats(10, 0);
                std::cout<<"piege"<<std::endl;
                break;

            case TRES: 
                //obtention d'un equipement ou sort
                m_map[indiceMap] = SOL;
                std::cout<<"tres"<<std::endl;
                break;

            default: 
                //erreur
                std::cout<<"Problème"<<std::endl;
        }
    }
}
