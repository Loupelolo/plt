#include "CoucheTerrain.h"

namespace render{

// Constructeur & destructeur

CoucheTerrain::CoucheTerrain (){

}

CoucheTerrain::CoucheTerrain (int x, int y){
    m_posX = x;
    m_posY = y;
}

CoucheTerrain::CoucheTerrain (int x, int y, int h, int l, int tailleTuile){
    m_posX = x;
    m_posY = y;
    m_hauteur = h;
    m_largeur = l;
    m_tailleTuile = tailleTuile;
}

CoucheTerrain::~CoucheTerrain (){

}



// Setters & Getters

int CoucheTerrain::getTailleTuile (){
    return m_tailleTuile;
}

void CoucheTerrain::setTailleTuile (int tailleTuile){
    m_tailleTuile = tailleTuile;
}



//Méthodes

bool CoucheTerrain::loadDecor(const std::string& tileset, sf::Vector2u tileSize, state::Decor decor, int ligne, bool porteOuverte){
    int decalX = m_posX + 12 + m_tailleTuile*(18-m_largeur)/2; //décallage vertical pour centrer
    std::vector<state::TypeTerrain> map = decor.getMap();

    // on charge la texture du tileset
    if (!m_texture.loadFromFile(tileset))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(map.size() * 4);

    int tv = ligne;

    for(int i=0; i<m_largeur;i++){
        for(int j=0; j<m_hauteur;j++){
            sf::Vertex* quad = &m_vertices[(i + j*m_largeur) * 4];

            int tu = map[i + m_largeur * j]; //type de texture à afficher
            
            if(tu==5){
                if(porteOuverte) tv = 0;
                else tv = 1;
            }

            quad[0].position = sf::Vector2f(i * m_tailleTuile +decalX, j * m_tailleTuile+m_posY);
            quad[1].position = sf::Vector2f((i + 1) * m_tailleTuile+decalX, j * m_tailleTuile+m_posY);
            quad[2].position = sf::Vector2f((i + 1) * m_tailleTuile+decalX, (j + 1) * m_tailleTuile+m_posY);
            quad[3].position = sf::Vector2f(i * m_tailleTuile+decalX, (j + 1) * m_tailleTuile+m_posY);
            // on définit ses quatre coordonnées de texture

            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            tv = ligne;
        }
    }
    
    return true;
}

bool CoucheTerrain::loadPerso(const std::string& tileset, sf::Vector2u tileSize, std::vector<state::Entite*> entites){
    unsigned int taille = entites.size();
    int decalX = m_posX + 12 + m_tailleTuile*(18-m_largeur)/2; //décallage vertical pour centrer

    // on charge la texture du tileset
    if (!m_texture.loadFromFile(tileset))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(taille * 4);

    int tv = 0;

    for(unsigned int i=0; i<taille;i++){
        sf::Vertex* quad = &m_vertices[(i) * 4];

        int posX = entites[i]->getPositionX();
        int posY = entites[i]->getPositionY();
        int tu = 0;
        if(entites[i]->getEstVivant()) tu = entites[i]->getType();      
        else tu = 12;   

        quad[0].position = sf::Vector2f(posX * m_tailleTuile +decalX, posY * m_tailleTuile+m_posY);
        quad[1].position = sf::Vector2f((posX + 1) * m_tailleTuile+decalX, posY * m_tailleTuile+m_posY);
        quad[2].position = sf::Vector2f((posX + 1) * m_tailleTuile+decalX, (posY + 1) * m_tailleTuile+m_posY);
        quad[3].position = sf::Vector2f(posX * m_tailleTuile+decalX, (posY + 1) * m_tailleTuile+m_posY);
        // on définit ses quatre coordonnées de texture

        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }

    return true;
}

}