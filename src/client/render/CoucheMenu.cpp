#include "CoucheMenu.h"

namespace render {

CoucheMenu::CoucheMenu(){
    m_texture.loadFromFile("./res/parchemin.png");
}

CoucheMenu::CoucheMenu(int posX, int posY, int hauteur, int largeur){
   m_texture.loadFromFile("./res/parchemin.png");
   this->m_posX = posX;
   this->m_posY = posY;
   this->m_hauteur = hauteur;
   this->m_largeur = largeur;
}

CoucheMenu::~CoucheMenu(){

}

void CoucheMenu::setTexts(std::vector<sf::Text> texts){
    m_texts = texts;
}

std::vector<sf::Text> CoucheMenu::getTexts(){
    return m_texts;
}

void CoucheMenu::setTitre(std::string texte, int tailleFont){

    m_titre.setPosition(m_posX+15, m_posY+15);

    // choix de la police à utiliser
    m_titre.setFont(m_police); // font est un sf::Font

    // choix de la chaîne de caractères à afficher
    m_titre.setString(texte);

    // choix de la taille des caractères
    m_titre.setCharacterSize(tailleFont); // exprimée en pixels, pas en points !

    // choix de la couleur du texte
    m_titre.setFillColor(sf::Color::Black);

    // choix du style du texte
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

}

sf::Text CoucheMenu::getTitre(){
    return m_titre;
}

bool CoucheMenu::load(sf::Color couleur){

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4 * 4);

    sf::Vertex* carre = &m_vertices[0];
    // on définit la position des sommets du carre
    carre[0].position = sf::Vector2f(m_posX, m_posY);
    carre[1].position = sf::Vector2f(m_posX+m_largeur, m_posY);
    carre[2].position = sf::Vector2f(m_posX+m_largeur, m_posY+m_hauteur);
    carre[3].position = sf::Vector2f(m_posX, m_posY+m_hauteur);

    // on définit la couleur des sommets du carre
    carre[0].texCoords = sf::Vector2f(0, 0);
    carre[1].texCoords = sf::Vector2f(m_texture.getSize().x, 0);
    carre[2].texCoords = sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y);
    carre[3].texCoords = sf::Vector2f(0, m_texture.getSize().y);

    return true;
}





}