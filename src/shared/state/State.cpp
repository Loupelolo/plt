#include "State.h"
#include "Decor.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <json/json.h>


namespace state {

    // Constructeur & destructeur

    State::State () {
        m_nbTour = 0;
        m_niveau = 1;
        m_niveauFini=false;
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

    int State::getNiveau (){
        return m_niveau;
    }

    void State::setNiveau (int niveau){
        m_niveau = niveau;
    }

    bool State::getNiveauFini (){
        return m_niveauFini;
    }

    void State::setNiveauFini (bool niveauFini){
        m_niveauFini = niveauFini;
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
        std::vector<Entite*> tampon;

        for(int i =  m_entites.size()-1; i>=0;i--){
            //suppression des morts dans entites
            if(!m_entites[i]->getEstVivant()){
                m_entites.erase(m_entites.begin() + i);
            //ajout des personnages du niveau dans un vector tampon
            } else if(m_entites[i]->getNiveau() == m_niveau){
                tampon.push_back(m_entites[i]);
            }
        }
        //initialisation d'un nouveau tour
        unsigned int taille = tampon.size();
        m_ordreTour.resize(taille);
        for(unsigned int indiceOrdre = 0; indiceOrdre<taille; indiceOrdre++){
            int indiceEnt = 0;
            int max = tampon[indiceEnt]->getStat(INITIATIVE);
            for(unsigned int indiceRecherche=0; indiceRecherche < taille-indiceOrdre; indiceRecherche++ ){
                int stat = tampon[indiceRecherche]->getStat(INITIATIVE);
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
        //suppression des morts dans ordreTour
        for(unsigned int i = 0; i<m_ordreTour.size();i++){
            if(!m_ordreTour[i]->getEstVivant()){
                m_ordreTour.erase(m_ordreTour.begin()+i);
            }
        }
        //passage au personnage suivant
        if (m_ordreTour.size()>1) {
            m_ordreTour.erase(m_ordreTour.begin());
        } else {
            this->nouveauTour();
        }
        m_aAttaque = false;
        m_aBouge = false;

        //verifie si le niveau est fini
        bool ennemisReste = false;
        for (unsigned int i=0; i<m_entites.size();i++) {
            if(m_entites[i]->getType()>=6 && m_entites[i]->getNiveau() == m_niveau && m_entites[i]->getEstVivant()) ennemisReste = true;
        }
        if(!ennemisReste) m_niveauFini = true;
    }

    bool State::effectuerAction(int commandeAEffectuer){
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
        return false;
    }

    void State::niveauSuivant(){
        m_niveau++;
        if(m_niveau>=4){
        } else {
            m_niveauFini=false;
            for (unsigned int i=0; i<m_entites.size();i++){
                if(m_entites[i]->getType()<6){
                    m_entites[i]->setNiveau(m_entites[i]->getNiveau()+1);
                    if(m_niveau == 2){
                        m_entites[i]->setPositionX(8+i%3);
                        m_entites[i]->setPositionY(7+i/3);
                    } else if(m_niveau == 3){
                        m_entites[i]->setPositionX(6+i%3);
                        m_entites[i]->setPositionY(8+i/3);
                    }
                }
            }
            this->chargerMap("json/map.json");
            this->nouveauTour();
        }
    }

    void State::chargerMap(std::string fichierJson){
        std::ifstream jMap(fichierJson);
        Json::Reader reader;
        Json::Value obj;
        reader.parse(jMap, obj);

        const Json::Value& layer = obj["layers"]; // tableau de layers

        int nbLargeur = layer[m_niveau - 1]["width"].asUInt();
        int nbLongueur = layer[m_niveau - 1]["height"].asUInt();

        int tailleMap = nbLargeur*nbLongueur;

        const Json::Value& data = layer[m_niveau - 1]["data"]; // tableau de data

        std::vector<TypeTerrain> map(tailleMap);
        for (unsigned int i = 0; i < data.size(); i++){
            map[i] = static_cast<TypeTerrain>(data[i].asUInt());
        }
        
        Decor decor(nbLargeur, nbLongueur, map);
        if(m_niveau == 1) decor.setType(0);
        else decor.setType(1);
        m_decor = decor;
    }

}
