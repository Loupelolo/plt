#include "Couche.h"

namespace render {

// Constructeur & destructeur

Couche::Couche(){
   m_police.loadFromFile("./res/alagard_by_pix3m-d6awiwp.ttf");
}

Couche::Couche(int posX, int posY, int hauteur, int largeur){
   m_police.loadFromFile("./res/alagard_by_pix3m-d6awiwp.ttf");
   this->m_posX = posX;
   this->m_posY = posY;
   this->m_hauteur = hauteur;
   this->m_largeur = largeur;
}

Couche::~Couche(){

}



// Setters & Getters

int Couche::getPosX () {
   return m_posX;
}

int Couche::getPosY () {
   return m_posY;
}

void Couche::setPos (int x, int y) {
   m_posX = x;
   m_posY = y;
}

int Couche::getHauteur () {
   return m_hauteur;
}

int Couche::getLargeur () {
   return m_largeur;
}

void Couche::setDimensions (int hauteur, int largeur) {
   this->m_hauteur = hauteur;
   this->m_largeur = largeur;
}



// Méthodes

void Couche::draw(sf::RenderTarget& target, sf::RenderStates states) const { //méthode virtuel de Drawable à redéfinir
   // on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
   states.transform *= getTransform(); // getTransform() est définie par sf::Transformable

   // on applique la texture
   states.texture = &m_texture;

   // on peut aussi surcharger states.shader ou states.blendMode si nécessaire

   // on dessine le tableau de vertex
   target.draw(m_vertices, states);
}



}