#include "Environnement.h"

namespace state {
    Environnement::Environnement () {

    }

    Environnement::~Environnement () {
        
    }

    int Environnement::getMeteo (){
        return m_meteo;
    }

    void Environnement::setMeteo (int meteo){
        m_meteo = meteo;
    }

    int Environnement::getLumiere (){
        return m_lumiere;
    }

    void Environnement::setLumiere (int lumiere){
        m_lumiere = lumiere;
    }
}
