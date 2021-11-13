#include "ElementTab.h"

namespace state {
    ElementTab::ElementTab () {
        m_hauteur =4;
        m_largeur =4;
    }

    ElementTab::~ElementTab () {

    }

    void ElementTab::addElement (Element e){
        //ajouter un element au tableau d'element elementTab
    }

    std::vector<Element> ElementTab::getElements (){
        return m_elements;
    }

    void ElementTab::setElements (std::vector<Element> elements){
        m_elements = elements;
    }


    unsigned int ElementTab::getHauteur () {
        return m_hauteur;
    }

    void ElementTab::setHauteur (unsigned int hauteur) {
        m_hauteur = hauteur;
    }

    unsigned int ElementTab::getLargeur (){
        return m_largeur;
    }

    void ElementTab::setLargeur (unsigned int largeur){
        m_largeur = largeur;
    }

    /* void ElementTab::setDecors (std::vector<int> map, int texture , int environnement ){
        std::vector<Decor> decor;
        decor.resize(map.size());
        for(unsigned int i=0; i<map.size();i++){
            decor[i].setType(map[i]);
            decor[i].setTexture(texture);
            decor[i].setEnvironnement(environnement);
        }
    } */

}
