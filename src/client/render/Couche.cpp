#include "Couche.h"

namespace render {

Couche::Couche(){

}

Couche::~Couche(){

}

void Couche::setPos (int x, int y) {
   posX = x;
   posY = y;
}

int Couche::getPosX () {
   return posX;
}

int Couche::getPosY () {
   return posY;
}


void Couche::setDimensions (int hauteur, int largeur) {
   this->hauteur = hauteur;
   this->largeur = largeur;
}

int Couche::getHauteur () {
   return hauteur;
}

int Couche::getLargeur () {
   return largeur;
}

void Couche::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
        states.transform *= getTransform(); // getTransform() est définie par sf::Transformable

        // on applique la texture
        states.texture = &m_texture;

        // on peut aussi surcharger states.shader ou states.blendMode si nécessaire

        // on dessine le tableau de vertex
        target.draw(m_vertices, states);
}

}