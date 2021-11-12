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
    int largeurColonne1 = 150;
    int largeurColonne2 = 600;
    int largeurColonne3 = 150;
    int largeurFenetre = largeurColonne1+largeurColonne2+largeurColonne3;

    int hauteurLigne1 = 300;
    int hauteurLigne2 = 150;
    int hauteurFenetre = hauteurLigne1+hauteurLigne2;

    cout << "It works !" << endl;

    CoucheMenu menuOrdre(0,0,hauteurLigne1,largeurColonne1);
    menuOrdre.setTitre({"Ordre :"},15);
    CoucheMenu menuPerso(0,hauteurLigne1,hauteurLigne2,largeurColonne1);
    menuPerso.setTitre({"Personnage :"},15);
    CoucheMenu menuAction(largeurColonne1,hauteurLigne1,hauteurLigne2,largeurColonne2);
    menuAction.setTitre({"Actions possibles :"},15);
    CoucheMenu menuCaseActuelle(largeurColonne1+largeurColonne2,0,hauteurLigne1,largeurColonne3);
    menuCaseActuelle.setTitre({"Case actuelle :"},15);
    CoucheMenu menuDes(largeurColonne1+largeurColonne2,hauteurLigne1,hauteurLigne2,largeurColonne3);
    menuDes.setTitre({"Des :"},15);

    std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};

    Scene scene(hauteurFenetre,largeurFenetre);
    scene.afficherFenetre(menus);

    return 0;
}
