#include "Scene.h"

namespace render {

// Constructeur & destructeur

Scene::Scene(){
    m_window.create(sf::VideoMode(800, 500), "Les Dee & Di");
}

Scene::Scene(int h, int l){
    m_window.create(sf::VideoMode(l,h), "Les Dee & Di");
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

state::State Scene::getState () {
   return m_state;
} 

void Scene::setState (state::State state) {
   m_state = state;
}

sf::Vector2f Scene::getCaseActuelle(){
    return m_caseActuelle;
}

void Scene::setCaseActuelle(sf::Vector2f caseActuelle){
    m_caseActuelle = caseActuelle;
}



// Méthodes

bool Scene::afficherFenetre(std::vector<CoucheMenu> menus, std::vector<CoucheTerrain> terrains){
    
    for(unsigned int i=0; i<menus.size();i++ ){
        if (!menus[i].load()) //préparation affichage des menus
        return -1;
    }

    terrains[0].loadDecor("./res/terrainTilesetTest.png", sf::Vector2u(32, 32), m_state.getDecor()); //préparation affichage des décors
    terrains[1].loadPerso("./res/roguelikecreatures.png", sf::Vector2u(16, 16), m_state.getEntites()); //préparation affichage des perso


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

        m_window.draw(terrains[0]); //affichage des décors
        m_window.draw(terrains[1]); //affichage des perso

        for(unsigned int i=0; i<menus.size();i++ ){
            m_window.draw(menus[i]); //affichage de l'arrière-plan des menus
            m_window.draw(menus[i].getTitre()); //affichage des titres des menus
            std::vector<sf::Text> nouveau = menus[i].update(m_state,m_caseActuelle);
            for(unsigned int j =0; j<nouveau.size(); j++ ){
                m_window.draw(nouveau[j]); //affichage des textes des menus
            }
        }
        m_window.display();
    }
    return 0;
}


}