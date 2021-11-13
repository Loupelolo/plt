#include "Decor.h"

namespace state {
    Decor::Decor () {
        m_type = 0;
    }

    Decor::Decor (int type) {
        m_type = type;
    }

    Decor::~Decor () {

    }

    void Decor::action (){
        //declenche l'action de la case
    }

    int Decor::getTexture (){
        return m_texture;
    }

    void Decor::setTexture (int texture){
        m_texture = texture;
    }

    Environnement Decor::getEnvironnement (){
        return m_environnement;
    }

    void Decor::setEnvironnement (Environnement environnement){
        m_environnement = environnement;
    }
}
