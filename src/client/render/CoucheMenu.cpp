#include "CoucheMenu.h"
#include <iostream>

namespace render {

// Constructeur & destructeur

CoucheMenu::CoucheMenu(){
    m_texture.loadFromFile("./res/parchemin.png");
}

CoucheMenu::CoucheMenu(int type, int posX, int posY, int hauteur, int largeur){
   m_texture.loadFromFile("./res/parchemin.png");
   m_type = type;
   m_posX = posX;
   m_posY = posY;
   m_hauteur = hauteur;
   m_largeur = largeur;
}

CoucheMenu::~CoucheMenu(){

}



// Setters & Getters

int CoucheMenu::getType () {
   return m_type;
}

void CoucheMenu::setType (int type) {
   m_type = type;
}

sf::Text CoucheMenu::getTitre(){
    return m_titre;
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
    m_titre.setStyle(sf::Text::Underlined);

}

std::vector<sf::Text> CoucheMenu::getTexts(){
    return m_texts;
}

void CoucheMenu::setTexts(std::vector<sf::Text> texts){
    m_texts = texts;
}



// Méthodes

bool CoucheMenu::load(){

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

std::vector<sf::Text> CoucheMenu::update(state::State* state, sf::Vector2f caseActuelle){
    std::vector<std::string> str;
    std::vector<state::Entite*> ordreEntite = state->getOrdreTour();
    std::vector<state::Entite*> entites = state->getEntites();
    state::Entite persoActuel = *state->getOrdreTour()[0];
    std::vector<state::ActionSupp*> autresActions = persoActuel.getAutresActions();
    bool persoEstPresent = false;

    switch (m_type)
    {
        case 0: //ordre
            int max;
            if(ordreEntite.size()<10) max = ordreEntite.size();
            else max=10;
            m_texts.resize(max+1);
            for(int i = 0; i<max; i++){
                m_texts[i].setPosition(m_posX + 20,m_posY+40+i*15); 
                m_texts[i].setFont(m_police); 
                m_texts[i].setString(std::to_string(i)+"- " + (*ordreEntite[i]).getNom());
                m_texts[i].setCharacterSize(15); 
                m_texts[i].setFillColor(sf::Color::Black);
            } 
            m_texts[max].setPosition(m_posX + 100,m_posY+15); 
            m_texts[max].setFont(m_police); 
            m_texts[max].setString((std::to_string(state->getNbTour())));
            m_texts[max].setCharacterSize(15); 
            m_texts[max].setFillColor(sf::Color::Black);
            break;
        case 1: //perso
            str = {"Nom : "+persoActuel.getNom(),"PV : " +std::to_string(persoActuel.getPV()),"PM : "+std::to_string(persoActuel.getPM()),"Actions restantes :","- Deplacement","- Attaque"};
            if(state->getABouge()){
                str[4] = ("");
            }
            if(state->getAAttaque()){
                str[5] = ("");
            }
            m_texts.resize(6);
            for(int i = 0; i<6; i++){
                m_texts[i].setPosition(m_posX + 20,m_posY+40+i*15); 
                m_texts[i].setFont(m_police); 
                m_texts[i].setString(str[i]);
                m_texts[i].setCharacterSize(15); 
                m_texts[i].setFillColor(sf::Color::Black);
            }
            break;
        case 2: //action
            str = {"Deplacement","Attaque","Passer"};
            m_texts.resize(3+autresActions.size());
            for(int i = 0; i<3; i++){
                m_texts[i].setPosition(m_posX + 30 + i*200, m_posY+50);
                m_texts[i].setFont(m_police); 
                m_texts[i].setString(str[i]);
                m_texts[i].setCharacterSize(25); 
                m_texts[i].setFillColor(sf::Color::Black);
            }

            for(unsigned int i = 0;i<autresActions.size() and i<3;i++){
                str[i] = autresActions[i]->getNom();
            }
            for(unsigned int i = 0; i<3 and i<autresActions.size(); i++){
                m_texts[i+3].setPosition(m_posX + 30 + i*200, m_posY+90);
                m_texts[i+3].setFont(m_police); 
                m_texts[i+3].setString(str[i]);
                m_texts[i+3].setCharacterSize(25); 
                m_texts[i+3].setFillColor(sf::Color::Black);
            }
            break;
        case 3: //caseActuelle
            for(unsigned int i = 0;i<entites.size() ;i++){
                sf::Vector2f posEntite = sf::Vector2f(entites[i]->getPositionX(),entites[i]->getPositionY());
                if (caseActuelle == posEntite){
                    persoEstPresent = true;
                    str = {"Nom : "+entites[i]->getNom(),"PV : " +std::to_string(entites[i]->getPV()),"PM : "+std::to_string(entites[i]->getPM())};
                    m_texts.resize(3);
                    for(int i = 0; i<3; i++){
                        m_texts[i].setPosition(m_posX + 20,m_posY+40+i*15); 
                        m_texts[i].setFont(m_police); 
                        m_texts[i].setString(str[i]);
                        m_texts[i].setCharacterSize(15); 
                        m_texts[i].setFillColor(sf::Color::Black);
                    }
                }
            }
            if(!persoEstPresent){
                m_texts.resize(1);
                m_texts[0].setPosition(m_posX + 20,m_posY+40); 
                m_texts[0].setFont(m_police); 
                m_texts[0].setString("");
                m_texts[0].setCharacterSize(15); 
                m_texts[0].setFillColor(sf::Color::Black);
            }
            break;
        case 4: //des
            m_texts.resize(1);
            m_texts[0].setPosition(m_posX + 40, m_posY+50); 
            m_texts[0].setFont(m_police); 
            m_texts[0].setString(std::to_string(state->getDe()));
            m_texts[0].setCharacterSize(40); 
            m_texts[0].setFillColor(sf::Color::Black);
            break;

    }
    return m_texts;
}




}