#include "CoucheTerrain.h"

namespace render{
    CoucheTerrain::CoucheTerrain (){

    }

    CoucheTerrain::CoucheTerrain (int x, int y){
        m_posX = x;
        m_posY = y;
    }

    CoucheTerrain::~CoucheTerrain (){

    }

    void CoucheTerrain::setCasesAccessibles (std::vector<std::vector<int>> casesAccessibles){
        m_casesAccesibles = casesAccessibles;
    }

    std::vector<std::vector<int>> CoucheTerrain::getCasesAccessibles (){
        return m_casesAccesibles;
    }

    void CoucheTerrain::setTailleTuile (int tailleTuile){
        m_tailleTuile = tailleTuile;
    }

    int CoucheTerrain::getTailleTuile (){
        return m_tailleTuile;
    }

    void CoucheTerrain::actualisationCasesAccessibles (){
        //defini les cases accesibles selon la portée
    }


bool CoucheTerrain::load(const std::string& tileset, sf::Vector2u tileSize, state::State state, int indice)
    {
        std::vector<state::Decor> tiles1;
        std::vector<state::Entite> tiles2;
        unsigned int taille;

        int decalX = m_posX + 12 + tileSize.x*(18-m_largeur)/2;

        if(indice==0) {
            tiles1 = state.getDecors();
            taille = tiles1.size();
        }
        else {
            tiles2 = state.getEntites();
            taille = tiles2.size();
        }
        // on charge la texture du tileset
        if (!m_texture.loadFromFile(tileset))
            return false;

        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(taille * 4);

        int tv = 0;


        for(unsigned int i=0; i<taille;i++){
            sf::Vertex* quad = &m_vertices[(i) * 4];
            int tu, posX, posY;
            if(indice == 0){
            posX = tiles1[i].getPositionX();
            posY = tiles1[i].getPositionY();
            tu = tiles1[i].getType();
            }
            else{
            posX = tiles2[i].getPositionX();
            posY = tiles2[i].getPositionY();
            tu = tiles2[i].getType();
            tv=1;
            }
            

            quad[0].position = sf::Vector2f(posX * tileSize.x +decalX, posY * tileSize.y+m_posY);
            quad[1].position = sf::Vector2f((posX + 1) * tileSize.x+decalX, posY * tileSize.y+m_posY);
            quad[2].position = sf::Vector2f((posX + 1) * tileSize.x+decalX, (posY + 1) * tileSize.y+m_posY);
            quad[3].position = sf::Vector2f(posX * tileSize.x+decalX, (posY + 1) * tileSize.y+m_posY);
            // on définit ses quatre coordonnées de texture

            if(indice==1) tileSize =sf::Vector2u(tileSize.x/2, tileSize.y/2);
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            if(indice==1) tileSize =sf::Vector2u(tileSize.x*2, tileSize.y*2);
        }
        

        return true;
    }

}