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


bool Scene::afficherFenetre(std::vector<CoucheMenu> menus){
    std::vector<sf::Color> couleur = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Blue};
    
    for(unsigned int i=0; i<menus.size();i++ ){
        if (!menus[i].load(couleur[i]))
        return -1;
    }

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

        for(unsigned int i=0; i<menus.size();i++ ){
            m_window.draw(menus[i]);
            m_window.draw(menus[i].getTitre());
        }
        m_window.display();
    }
    return 0;
}



// Setters and Getters

/* void Scene::setState (state::State state) {
   m_state = state;
}

state::State Scene::getState () {
   return state;
} */

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



}