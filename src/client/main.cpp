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
    State state;
    Entite entite1("Diana");
    entite1.setPositionX(0);
    entite1.setPositionY(0);
    entite1.setPV(100);
    entite1.setPM(50);
    entite1.setType(0);
    ActionSupp action1("Boule de feu");
    ActionSupp action2("Soin");
    entite1.setAutresActions({action1, action2});

    Entite entite2("Charles");
    entite2.setPositionX(2);
    entite2.setPositionY(1);
    entite2.setPV(70);
    entite2.setPM(3);
    entite1.setType(1);

    std::vector<int> map =
        {
            0, 2, 5, 5,
            0, 0, 4, 4,
            1, 0, 3, 3,
            1, 3, 3, 3,
        };

    state.setTerrain(map);
    state.setEntites({entite1,entite2});
    state.setOrdreTour({entite1,entite2});
    state.setDe(6);


    int largeurColonne1 = 150;
    int largeurColonne2 = 600;
    int largeurColonne3 = 150;
    int largeurFenetre = largeurColonne1+largeurColonne2+largeurColonne3;

    int hauteurLigne1 = 300;
    int hauteurLigne2 = 150;
    int hauteurFenetre = hauteurLigne1+hauteurLigne2;

    cout << "It works !" << endl;

    CoucheMenu menuOrdre(0,0,0,hauteurLigne1,largeurColonne1);
    menuOrdre.setTitre({"Ordre :"},15);
    CoucheMenu menuPerso(1,0,hauteurLigne1,hauteurLigne2,largeurColonne1);
    menuPerso.setTitre({"Personnage :"},15);
    CoucheMenu menuAction(2,largeurColonne1,hauteurLigne1,hauteurLigne2,largeurColonne2);
    menuAction.setTitre({"Actions possibles :"},15);
    CoucheMenu menuCaseActuelle(3,largeurColonne1+largeurColonne2,0,hauteurLigne1,largeurColonne3);
    menuCaseActuelle.setTitre({"Case actuelle :"},15);
    CoucheMenu menuDes(4,largeurColonne1+largeurColonne2,hauteurLigne1,hauteurLigne2,largeurColonne3);
    menuDes.setTitre({"Des :"},15);

    CoucheTerrain decor(largeurColonne1, 0);
    CoucheTerrain perso(largeurColonne1, 0);

    std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};

    Scene scene(hauteurFenetre,largeurFenetre);
    scene.setState(state);
    scene.setCaseActuelle(sf::Vector2f(2,1));
    scene.afficherFenetre(menus,{decor,perso});

    return 0;
}
