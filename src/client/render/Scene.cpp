#include "Scene.h"
#include "state.h"
#include <iostream>

namespace render {

// Constructeur & destructeur

Scene::Scene(){
    m_window.create(sf::VideoMode(800, 500), "Les Dee & Di");
    m_actionSelectionnee = 0;
}

Scene::Scene(int h, int l){
    m_window.create(sf::VideoMode(l,h), "Les Dee & Di");
    m_actionSelectionnee = 0;
}

Scene::~Scene(){

}



// Setters & Getters

int Scene::getJoueurID(){
    return m_joueurID;
}

void Scene::setJoueurID(int joueurID){
    m_joueurID = joueurID;
}

int Scene::getActionSelectionnee () {
    return m_actionSelectionnee;
}

void Scene::setActionSelectionnee (int actionSelectionnee) {
    m_actionSelectionnee = actionSelectionnee;
}

int Scene::getSceneID(){
    return m_sceneID;
}

void Scene::setSceneID(int sceneID){
    m_sceneID = sceneID;
}

state::State* Scene::getState () {
   return m_state;
} 

void Scene::setState (state::State* state) {
   m_state = state;
}

sf::Vector2f Scene::getCaseActuelle(){
    return m_caseActuelle;
}

void Scene::setCaseActuelle(sf::Vector2f caseActuelle){
    m_caseActuelle = caseActuelle;
}

std::vector<CoucheMenu> Scene::getMenus(){
    return m_menus;
}

void Scene::setMenus(std::vector<CoucheMenu> menus){
    m_menus = menus;
}

std::vector<CoucheTerrain> Scene::getTerrains(){
    return m_terrains;
}

void Scene::setTerrains(std::vector<CoucheTerrain> terrains){
    m_terrains = terrains;
}



// Méthodes

bool Scene::chargerFenetre(){
    for(unsigned int i=0; i<m_menus.size();i++ ){
        if (!m_menus[i].load()) //préparation affichage des m_menus
        return -1;
    }

    m_terrains[0].loadDecor("./res/terrainTilesetTest.png", sf::Vector2u(32, 32), m_state->getDecor()); //préparation affichage des décors
    m_terrains[1].loadPerso("./res/roguelikecreatures.png", sf::Vector2u(16, 16), m_state->getEntites()); //préparation affichage des perso
  
}

bool Scene::afficherFenetre(){
    sf::Clock clock;
    sf::Clock clock2;

    while (m_window.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();
        sf::Time elapsed2 = clock2.getElapsedTime();

        if(elapsed >= sf::milliseconds(16)){
            /*for(unsigned int i=0; i<m_menus.size();i++ ){
                if (!m_menus[i].load()) //actualisation affichage des m_menus
                return false;
            }*/
            m_terrains[0].loadDecor("./res/terrainTilesetTest.png", sf::Vector2u(32, 32), m_state->getDecor()); //préparation affichage des décors
            m_terrains[1].loadPerso("./res/roguelikecreatures.png", sf::Vector2u(16, 16), m_state->getEntites()); //préparation affichage des perso
            clock.restart();
            if(elapsed2 >= sf::seconds(1)){
                clock2.restart();
                //std::cout<<"ping"<<std::endl;
                //return true;
            }
        }

        

        // on gère les évènements
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;
                    if (mouseX >= m_menus[2].getPosX() && mouseX<= m_menus[2].getPosX() + m_menus[2].getLargeur()){
                        if(mouseY >= m_menus[0].getHauteur() ){
                            int actSel = selectAction(mouseX, mouseY);
                            if( actSel != -1) m_actionSelectionnee = actSel;
                        } else{
                            //selectCase
                        }
                    }
                    std::cout<<"action Select : "<<m_actionSelectionnee<<std::endl;
                }
            }
        }

        // on dessine le niveau
        m_window.clear();

        m_window.draw(m_terrains[0]); //affichage des décors
        m_window.draw(m_terrains[1]); //affichage des perso

        for(unsigned int i=0; i<m_menus.size();i++ ){
            m_window.draw(m_menus[i]); //affichage de l'arrière-plan des m_menus
            m_window.draw(m_menus[i].getTitre()); //affichage des titres des m_menus
            m_menus[i].update(m_state,m_caseActuelle);
            for(unsigned int j =0; j<m_menus[i].getTexts().size(); j++ ){
                m_window.draw(m_menus[i].getTexts()[j]); //affichage des textes des m_menus
            }

        }
        m_window.display();
    }
    return false;
}

int Scene::selectAction (int x, int y) {
    std::cout<<"pos souris "<<x<<","<<y<<std::endl;

    for(int i = 0; i < (int) (m_menus[2].getTexts()).size() ; i++){
        int debutX = m_menus[2].getPosX() + 30 + (i%3)*200;
        int finX = debutX + 200;
        int debutY = m_menus[2].getPosY() + 50 + (i/3) * 40;
        int finY = debutY + 30;
        std::cout<<debutX<<","<<debutY<<"->"<<finX<<","<<finY<<std::endl;

        if(x >= debutX && x <= finX && y >= debutY && y <= finY){
            return i;
        }
    }
    return -1;
}


}