#include "Scene.h"

namespace render {

Scene::Scene(){
    m_window.create(sf::VideoMode(800, 500), "Les Dee & Di");
}

Scene::Scene(int h, int l){
    m_window.create(sf::VideoMode(l,h), "Les Dee & Di");
}

Scene::~Scene(){

}


bool Scene::afficherFenetre(std::vector<CoucheMenu> menus, std::vector<CoucheTerrain> terrains){
    
    for(unsigned int i=0; i<menus.size();i++ ){
        if (!menus[i].load())
        return -1;
    }

    terrains[0].load("./res/terrainTilesetTest.png", sf::Vector2u(32, 32), m_state, 0);
    terrains[1].load("./res/roguelikecreatures.png", sf::Vector2u(32, 32), m_state, 1);


    while (m_window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                m_window.close();
        }

        // on dessine le niveau
        m_window.clear();

        m_window.draw(terrains[0]);
        m_window.draw(terrains[1]);

        for(unsigned int i=0; i<menus.size();i++ ){
            m_window.draw(menus[i]);
            m_window.draw(menus[i].getTitre());
            std::vector<sf::Text> nouveau = menus[i].update(m_state,m_caseActuelle);
            for(unsigned int j =0; j<nouveau.size(); j++ ){
                m_window.draw(nouveau[j]);
            }
        }
        m_window.display();
    }
    return 0;
}



// Setters and Getters

 void Scene::setState (state::State state) {
   m_state = state;
}

state::State Scene::getState () {
   return m_state;
} 

void Scene::setActionSelectionnee (int actionSelectionnee) {
   m_actionSelectionnee = actionSelectionnee;
}

int Scene::getActionSelectionnee () {
   return m_actionSelectionnee;
}

int Scene::getJoueurID(){
    return m_joueurID;
}

void Scene::setJoueurID(int joueurID){
    m_joueurID = joueurID;
}

int Scene::getSceneID(){
    return m_sceneID;
}

void Scene::setSceneID(int sceneID){
    m_sceneID = sceneID;
}

sf::Vector2f Scene::getCaseActuelle(){
    return m_caseActuelle;
}

void Scene::setCaseActuelle(sf::Vector2f caseActuelle){
    m_caseActuelle = caseActuelle;
}



}