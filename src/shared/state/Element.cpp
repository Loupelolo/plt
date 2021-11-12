#include "Element.h"

namespace state {
    Element::Element () {

    }

    Element::~Element () {

    }

    int Element::getPositionX (){
        return m_positionX;
    }

    void Element::setPositionX (int positionX){
        m_positionX = positionX;
    }

    int Element::getPositionY (){
        return m_positionY;
    }

    void Element::setPositionY (int positionY){
        m_positionY = positionY;
    }
}
