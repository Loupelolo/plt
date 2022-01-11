#include "State.h"
#include "Decor.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

namespace state {

    // Constructeur & destructeur

    State::State () {
        m_nbTour = 1;
        std::srand(std::time(nullptr)); // use current time as seed for random generator
        
    }

    State::~State () {

    }



    // Setters & Getters

    int State::getNbTour (){
        return m_nbTour;
    }

    void State::setNbTour (int nbTour){
        m_nbTour = nbTour;
    }

    Decor State::getDecor (){
        return m_decor;
    }

    void State::setDecor (Decor decors){
        m_decor = decors;
    }

    std::vector<Entite*> State::getEntites (){
        return m_entites;
    }

    void State::setEntites (std::vector<Entite*> entites){
        m_entites = entites;
    }

    std::vector<Entite*> State::getOrdreTour (){
        return m_ordreTour;
    }

    void State::setOrdreTour (std::vector<Entite*> ordreTour){
        m_ordreTour = ordreTour;
    }

    int State::getDe (){
        return m_de;
    }

    void State::setDe (int de){
        m_de = de;
    }

    bool State::getABouge (){
        return m_aBouge;
    }

    void State::setABouge (bool aBouge){
        m_aBouge = aBouge;
    }

    bool State::getAAttaque (){
        return m_aAttaque;
    }

    void State::setAAttaque (bool aAttaque){
        m_aAttaque = aAttaque;
    }



    // Méthodes

    void State::nouveauTour (){
        //initialisation d'un nouveau tour
        unsigned int taille = m_entites.size();
        m_ordreTour.resize(taille);
        std::vector<Entite*> tampon(m_entites.size());
        copy(m_entites.begin(), m_entites.end(), tampon.begin());
        for(unsigned int indiceOrdre = 0; indiceOrdre<taille; indiceOrdre++){
            int indiceEnt = 0;
            int max = tampon[indiceEnt]->getStat(INITIATIVE);
            for(unsigned int indiceRecherche; indiceRecherche < taille-indiceOrdre; indiceRecherche++ ){
                int stat = tampon[indiceEnt]->getStat(INITIATIVE);
                if(stat>max){
                    indiceEnt = indiceRecherche;
                    max = stat;
                }
            }
            m_ordreTour[indiceOrdre] = tampon[indiceEnt];
            tampon.erase(tampon.begin() +indiceEnt);
        }
        m_nbTour++;
    }

    void State::joueurSuivant (){
        //passage au personnage suivant
        std::cout<<m_ordreTour.size()<<std::endl;
        if (m_ordreTour.size()>1) {
            m_ordreTour.erase(m_ordreTour.begin());
            std::cout<<"tour suivant"<<std::endl;
        } else {
            this->nouveauTour();
        }
        m_aAttaque = false;
        m_aBouge = false;
    }

    bool State::effectuerAction(int commandeAEffectuer){
        std::cout<<"bouh"<<std::endl;
        if (commandeAEffectuer == 1)
        {
            if(!m_aBouge){
                m_aBouge =true;
                m_de = 1 + std::rand()/((RAND_MAX + 1u)/6);
                return true;
            }
        } else if (commandeAEffectuer > 1) {
            if(!m_aAttaque){
                m_aAttaque =true;
                m_de = 1 + std::rand()/((RAND_MAX + 1u)/6);
                return true;
            }            
        }
        std::cout<<"aaa"<<std::endl;
        return false;
    }

}
