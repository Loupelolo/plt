#include "Couche.h"

namespace render {

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



}