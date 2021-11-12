#include <iostream>


// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>
#include <render.h>

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[])
{
//    Exemple exemple;
//    exemple.setX(53);
    int largeurColonne1 = 100;
    int largeurColonne2 = 600;
    int largeurColonne3 = 100;
    int largeurFenetre = largeurColonne1+largeurColonne2+largeurColonne3;

    int hauteurLigne1 = 300;
    int hauteurLigne2 = 100;
    int hauteurFenetre = hauteurLigne1+hauteurLigne2;

    cout << "It works !" << endl;

    //sf::RenderWindow window(sf::VideoMode(largeurFenetre, hauteurFenetre), "Les Dee & Di");

    // on crée la tilemap avec le niveau précédemment défini
    CoucheMenu menuOrdre(0,0,hauteurLigne1,largeurColonne1);
    menuOrdre.setText({"Ordre :"});
    CoucheMenu menuPerso(0,hauteurLigne1,hauteurLigne2,largeurColonne1);
    CoucheMenu menuAction(largeurColonne1,hauteurLigne1,hauteurLigne2,largeurColonne2);
    CoucheMenu menuCaseActuelle(largeurColonne1+largeurColonne2,0,hauteurLigne1,largeurColonne3);
    CoucheMenu menuDes(largeurColonne1+largeurColonne2,hauteurLigne1,hauteurLigne2,largeurColonne3);

    std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};

    Scene scene(hauteurFenetre,largeurFenetre);
    scene.afficherFenetre(menus);
    /* if (!menuOrdre.load(sf::Color::Red))
        return -1;

    if (!menuPerso.load(sf::Color::Blue))
        return -1;

    if (!menuAction.load(sf::Color::Green))
        return -1;
    
    if (!menuCaseActuelle.load(sf::Color::Red))
        return -1;

    if (!menuDes.load(sf::Color::Blue))
        return -1; */

    // on fait tourner la boucle principale
    /* while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // on dessine le niveau
        window.clear();
        window.draw(menuOrdre);
        window.draw(menuPerso);
        window.draw(menuAction);
        window.draw(menuCaseActuelle);
        window.draw(menuDes);
        window.display();
    } */

    return 0;
}
