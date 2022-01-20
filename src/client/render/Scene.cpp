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

std::vector<bool> Scene::getCasesAccessibles (){
    return m_casesAccessibles;
}

void Scene::setCasesAccessibles (std::vector<bool> casesAccessibles){
    m_casesAccessibles = casesAccessibles;
}



// Méthodes

bool Scene::chargerFenetre(){
    for(unsigned int i=0; i<m_menus.size();i++ ){
        if (!m_menus[i].load()) //préparation affichage des m_menus
        return false;
    }

    m_terrains[0].loadDecor("./res/terrainTilesetTest.png", sf::Vector2u(32, 32), m_state->getDecor(),0,m_state->getNiveauFini()); //préparation affichage des décors
    m_terrains[1].loadPerso("./res/creatures.png", sf::Vector2u(16, 16), m_state->getEntites()); //préparation affichage des perso
    return true;
}

bool Scene::afficherFenetre(){
    sf::Clock clock;
    sf::Clock clock2;
    engine::Commande* commande = NULL;

    actualiserCasesAccessibles();

    while (m_window.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();
        sf::Time elapsed2 = clock2.getElapsedTime();

        if(elapsed >= sf::milliseconds(16)){
            /*for(unsigned int i=0; i<m_menus.size();i++ ){
                if (!m_menus[i].load()) //actualisation affichage des m_menus
                return false;
            }*/
            //std::cout<<"tagada"<<m_state->getEntites().size()<<std::endl;
            m_terrains[0].loadDecor("./res/terrainTilesetTest.png", sf::Vector2u(32, 32), m_state->getDecor(), 0, m_state->getNiveauFini()); //préparation affichage des décors
            m_terrains[1].loadPerso("./res/creatures.png", sf::Vector2u(16, 16), m_state->getEntites()); //préparation affichage des perso
            //std::cout<<"tsointsoin"<<std::endl;
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
                    int mouseX = event.mouseButton.x*900/m_window.getSize().x;
                    int mouseY = event.mouseButton.y*450/m_window.getSize().y;
                    if (mouseX >= m_menus[2].getPosX() && mouseX<= m_menus[2].getPosX() + m_menus[2].getLargeur()){
                    //l'utilisateur a cliquée dans la partie du milieu
                       if(mouseY >= m_menus[0].getHauteur() ){
                            //l'utilisateur a cliquée dans la partie menu
                            int actSel = selectAction(mouseX, mouseY);
                            if( actSel != -1) {
                                if(actSel == m_actionSelectionnee){
                                    //un menu a été désélectionné
                                    m_actionSelectionnee = 0;
                                } else {
                                    //le menu a été selectionné
                                    m_actionSelectionnee = actSel;
                                }
                                //on crée la commande associée à l'action choisie
                                switch(m_actionSelectionnee){
                                    case 1:
                                        {
                                        engine::CommandeDeplacement comDep;
                                        commande = &comDep;
                                        }
                                        break;
                                    case 2 :
                                        {
                                        engine::CommandeAttaque comAtt;
                                        commande = &comAtt;
                                        }
                                        break;
                                    case 4:
                                    case 5:
                                        {
                                        engine::CommandeActionSupplementaire comAct;
                                        commande = &comAct;
                                        }
                                        break;
                                    default :
                                        commande = NULL;
                                        break;
                                }
                                actualiserCasesAccessibles();
                            }
                        } else {
                            //l'utilisateur a cliquée dans la partie plateau
                            m_caseActuelle = selectCase(mouseX, mouseY);
                        }
                    }

                    //l'utilisateur a cliqué sur le bouton executer
                    int largeur = m_terrains[0].getLargeur();
                    if(m_state->getDecor().getMap()[m_caseActuelle.x +m_caseActuelle.y*largeur] == 5 && m_state->getNiveauFini()){
                        m_state->niveauSuivant();
                    }
                    if ((commande!=NULL && m_casesAccessibles[m_caseActuelle.x +m_caseActuelle.y*largeur])||m_actionSelectionnee ==3){
                        if (mouseX >= m_menus[3].getPosX()+20 && mouseX<= m_menus[3].getPosX() + 120){
                            if(mouseY>= m_menus[4].getPosY()-80 && mouseY<= m_menus[4].getPosY()-50){
                                //l'utilisateur souhaite effectuer un deplacement
                                if(m_actionSelectionnee == 1 && !m_state->getABouge()){
                                    std::cout<<"ici"<<std::endl;
                                    engine::CommandeDeplacement comDep(m_caseActuelle.x, m_caseActuelle.y);
                                    commande = &comDep;
                                    if(m_state->effectuerAction(m_actionSelectionnee)){
                                        std::cout<<"la"<<std::endl;
                                        commande->execute(m_state);
                                    } 
                                } else if(m_actionSelectionnee ==2 && !m_state->getAAttaque()){
                                    //l'utilisateur souhaite effectuer une attaque
                                    std::vector<state::Entite*> entites = m_state->getEntites();
                                    for(unsigned int i = 0;i<entites.size() ;i++){
                                        sf::Vector2f posEntite = sf::Vector2f(entites[i]->getPositionX(),entites[i]->getPositionY());
                                        if (m_caseActuelle == posEntite){
                                            engine::CommandeAttaque comAtt(entites[i]);
                                            commande = &comAtt;
                                            if(m_state->effectuerAction(m_actionSelectionnee)) commande->execute(m_state);
                                        }
                                    }
                                } else if(m_actionSelectionnee==3){
                                    //l'utilisateur souhaite passer son tour
                                    m_state->joueurSuivant();
                                    m_caseActuelle.x = m_state->getOrdreTour()[0]->getPositionX();
                                    m_caseActuelle.y = m_state->getOrdreTour()[0]->getPositionY();
                                } else if(m_actionSelectionnee>3 && !m_state->getAAttaque()) {
                                    std::vector<state::Entite*> entites = m_state->getEntites();
                                    for(unsigned int i = 0;i<entites.size() ;i++){
                                        sf::Vector2f posEntite = sf::Vector2f(entites[i]->getPositionX(),entites[i]->getPositionY());
                                        if (m_caseActuelle == posEntite){
                                                engine::CommandeActionSupplementaire comAct(entites[i], m_state->getOrdreTour()[0]->getAutresActions()[m_actionSelectionnee-4]);
                                                commande = &comAct;
                                                if(m_state->effectuerAction(m_actionSelectionnee)) commande->execute(m_state);
                                        }
                                    }
                                }
                                m_actionSelectionnee = 0;
                            }
                        }
                    }
                }
            }
        }
        //std::cout<<"prout"<<std::endl;

        // on dessine le niveau
        m_window.clear();

        m_window.draw(m_terrains[0]); //affichage des décors

        for(unsigned int i=0; i<m_menus.size();i++ ){
            m_window.draw(m_menus[i]); //affichage de l'arrière-plan des m_menus
            m_window.draw(m_menus[i].getTitre()); //affichage des titres des m_menus
            m_menus[i].update(m_state,m_caseActuelle);
            for(unsigned int j =0; j<m_menus[i].getTexts().size(); j++ ){
                m_window.draw(m_menus[i].getTexts()[j]); //affichage des textes des m_menus
            }
            //std::cout<<"super"<<std::endl;
        }

        afficherSelection();

        m_window.draw(m_terrains[1]); //affichage des perso
        //std::cout<<"hum"<<std::endl;


        int largeur = m_terrains[0].getLargeur();
        //dessiner la case "executer"
        if(m_actionSelectionnee ==3){
            afficherExecuter("Passer");
        }

        if (m_casesAccessibles[m_caseActuelle.x +m_caseActuelle.y*largeur]){
            if((m_actionSelectionnee == 1 && !m_state->getABouge())){
                afficherExecuter("Deplacer");
            } else if((m_actionSelectionnee == 2 ||m_actionSelectionnee>3) && !m_state->getAAttaque()){
                afficherExecuter("Attaquer");
            }
            
        }

        m_window.display();
    }
    return false;
}

int Scene::selectAction (int x, int y) {
    int action = -1;
    for(int i = 0; i < (int) (m_menus[2].getTexts()).size() ; i++){
        int debutX = m_menus[2].getPosX() + 30 + (i%3)*200;
        int finX = debutX + 200;
        int debutY = m_menus[2].getPosY() + 50 + (i/3) * 40;
        int finY = debutY + 30;
        //std::cout<<debutX<<","<<debutY<<"->"<<finX<<","<<finY<<std::endl;

        if(x >= debutX && x <= finX && y >= debutY && y <= finY){
            action = i+1;
        }
    }

    return action;
}

sf::Vector2f Scene::selectCase (int x, int y) {
    int largeur = m_terrains[0].getLargeur();
    int hauteur = m_terrains[0].getHauteur();
    int tailleTuile = m_terrains[0].getTailleTuile();

    int debutX = m_terrains[0].getPosX() + 12 + tailleTuile*(18-largeur)/2;
    int finX = debutX + largeur*tailleTuile;
    int debutY = 0;
    int finY = debutY + hauteur*tailleTuile;

    sf::Vector2f resultat = m_caseActuelle;

    if(x >= debutX && x <= finX && y >= debutY && y <= finY){
        resultat.x = (x-debutX)/tailleTuile;
        resultat.y = (y-debutY)/tailleTuile;
    }

    return resultat;
}

void Scene::afficherSelection(){
    int tailleTuile = m_terrains[0].getTailleTuile();
    int largeur = m_terrains[0].getLargeur();
    int hauteur = m_terrains[0].getHauteur();
    int debutX = m_terrains[0].getPosX() + 12 + tailleTuile*(18-largeur)/2;

    //affichage de la surbrillance
    if(m_actionSelectionnee == 0) {
        //affiche en surbrillance la case sélectionnée
        sf::RectangleShape carreCaseSelect(sf::Vector2f(tailleTuile, tailleTuile));
        carreCaseSelect.setPosition(debutX + m_caseActuelle.x*tailleTuile, m_caseActuelle.y*tailleTuile);
        carreCaseSelect.setFillColor(sf::Color(250, 250, 250, 50));
        m_window.draw(carreCaseSelect);
    } else {
        //affiche en surbrillance l'action sélectionnée
        sf::RectangleShape carreActionSelect(sf::Vector2f(170, 30));
        carreActionSelect.setPosition(m_menus[2].getPosX() + 20 + ((m_actionSelectionnee-1)%3)*200, m_menus[2].getPosY() + 50 + ((m_actionSelectionnee-1)/3) * 40);
        carreActionSelect.setFillColor(sf::Color(0, 0, 0, 50));
        m_window.draw(carreActionSelect);

        //affichage des cases disponibles
        sf::Color couleur(0, 0, 0, 100);
        switch (m_actionSelectionnee){
            case 1:
                couleur.g = 100;
                break; 
            case 2:
                couleur.r = 100;
                break; 
            case 4:
            case 5:
                couleur.b = 100;
                break; 
            default :
                break;
        }
        for(int i = 0; i < largeur; i++){
            for(int j=0; j < hauteur; j++){
                if (m_casesAccessibles[i + j* largeur]){
                    sf::RectangleShape carreCaseSelect(sf::Vector2f(tailleTuile, tailleTuile));
                    carreCaseSelect.setPosition(debutX + i*tailleTuile, j*tailleTuile);
                    carreCaseSelect.setFillColor(couleur);
                    m_window.draw(carreCaseSelect);
                }
            }
        }
        //verifie que la case selectionnée soit dans les cases accessibles
        if(m_casesAccessibles[m_caseActuelle.x +m_caseActuelle.y*largeur]){
            //couleur.a = 250;
            couleur.b *=2;
            couleur.g *=2;
            couleur.r *=2;
            sf::RectangleShape carreCaseSelect(sf::Vector2f(tailleTuile, tailleTuile));
            carreCaseSelect.setPosition(debutX + m_caseActuelle.x*tailleTuile, m_caseActuelle.y*tailleTuile);
            carreCaseSelect.setFillColor(couleur);
            m_window.draw(carreCaseSelect);
        }
    }
    
    
}

void Scene::actualiserCasesAccessibles(){
    int largeur = m_terrains[0].getLargeur();
    int hauteur = m_terrains[0].getHauteur();

    m_casesAccessibles.resize(hauteur*largeur);

    state::Entite* entite = m_state->getOrdreTour()[0];
    int depl = entite->getStat(state::DEPLACEMENT);
    int portee = entite->getStat(state::PORTEE);
    int porteeA = 0;
    int posX = entite->getPositionX();
    int posY = entite->getPositionY();
    std::vector<state::TypeTerrain> map = m_state->getDecor().getMap();

    //std::cout<<m_actionSelectionnee<<std::endl;

    switch(m_actionSelectionnee) 
    {
        case 1:
            for(int i = 0; i < largeur; i++){
                for(int j=0; j < hauteur; j++){
                    m_casesAccessibles[i+j*largeur] = false;
                    if (abs(i-posX)+abs(j-posY)<=depl){
                        if (map[i+j*largeur]==state::SOL || map[i+j*largeur]==state::TRES || map[i+j*largeur]==state::SECR){
                            m_casesAccessibles[i+j*largeur] = true;
                        }
                    }
                }
            }
            break;

        case 2:
            for(int i = 0; i < largeur; i++){
                for(int j=0; j < hauteur; j++){
                    m_casesAccessibles[i+j*largeur] = false;
                    if (abs(i-posX)+abs(j-posY)<=portee){
                        if (map[i+j*largeur]==state::SOL || map[i+j*largeur]==state::TRES || map[i+j*largeur]==state::SECR){
                            m_casesAccessibles[i+j*largeur] = true;
                        }
                    }
                }
            }
            break;

        case 4:
        case 5:
            porteeA = entite->getAutresActions()[m_actionSelectionnee-4]->getPortee();
            for(int i = 0; i < largeur; i++){
                for(int j=0; j < hauteur; j++){
                    m_casesAccessibles[i+j*largeur] = false;
                    if (abs(i-posX)+abs(j-posY)<=porteeA){
                        if (map[i+j*largeur]==state::SOL || map[i+j*largeur]==state::TRES || map[i+j*largeur]==state::SECR){
                            m_casesAccessibles[i+j*largeur] = true;
                        }
                    }
                }
            }
            break;
        default :
            for(int i = 0; i < largeur; i++){
                for(int j=0; j < hauteur; j++){
                    m_casesAccessibles[i+j*largeur] = false;
                }
            }
            break;
    }
}

void Scene::afficherExecuter(sf::String texte){
    sf::RectangleShape carreFaireAction(sf::Vector2f(100, 30));
    carreFaireAction.setPosition(m_menus[3].getPosX()+20, m_menus[4].getPosY()-80);
    carreFaireAction.setFillColor(sf::Color(0, 0, 0, 50));
    m_window.draw(carreFaireAction);

    sf::Text text;
    text.setPosition(m_menus[3].getPosX()+35,m_menus[4].getPosY()-75); 
    sf::Font police;
    police.loadFromFile("./res/alagard_by_pix3m-d6awiwp.ttf");
    text.setFont(police); 
    text.setString(texte);
    text.setCharacterSize(15); 
    text.setFillColor(sf::Color::Black);
    m_window.draw(text);
}



}