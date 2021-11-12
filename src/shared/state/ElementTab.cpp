#include "ElementTab.h"

namespace state {
    ElementTab::ElementTab () {

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
}
