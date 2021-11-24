#include <iostream>

#include <state.h>
#include <engine.h>

using namespace std;
using namespace state;
using namespace engine;

int main(int argc,char* argv[])
{
    State state;

    // Informations modifiables pour changer l'état
    //création des personnages
    Entite entite1("Diana");
    entite1.setPositionX(4);
    entite1.setPositionY(2);
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

    Entite entite3("Elisabeth");
    entite3.setPositionX(7);
    entite3.setPositionY(0);
    entite3.setPV(300);
    entite3.setPM(500);
    entite3.setType(2);

    // valeur de deplacement
    entite1.setStats({0,0,0,0,0,0,0,0,3});
    entite2.setStats({0,0,0,0,0,0,0,0,4});
    entite3.setStats({0,0,0,0,0,0,0,0,2});

    //création de la map
    // 5 = mur 4 = mur 3 = route 1 = eau 0 = herbe
    std::vector<int> map = //maximum 18 de largeur et 9 de hauteur
        {
            5, 5, 5, 5, 5, 5, 5, 3, 5, 5, 5, 5, 5,
            4, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
            4, 1, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 4,
            4, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        };
    int nbLargeur = 13;

    //implémentation dans le state
    state.setDe(6);
    state.setEntites({entite1,entite2,entite3});
    state.setOrdreTour({&entite1,&entite2,&entite3});

    //définition de l'affichage des menus
    // int largeurColonne1 = 150;
    // int largeurColonne2 = 600;
    // int largeurColonne3 = 150;
    // int largeurFenetre = largeurColonne1+largeurColonne2+largeurColonne3;

    // int hauteurLigne1 = 300;
    // int hauteurLigne2 = 150;
    // int hauteurFenetre = hauteurLigne1+hauteurLigne2;

    cout << entite1.getStat(8) << endl;

    Engine engine(state);

    //engine.setState(state);

    //state::Entite persoActuel = *state.getOrdreTour()[0];    

    CommandeDeplacement dep1(3,1);

    if (dep1.handleDeplacement(*state.getOrdreTour()[0], map, nbLargeur) && dep1.handleCollision(state.getEntites())){
       cout << "je peux y aller" << endl;
       if(dep1.execute(&engine)){
           cout << "fonctionne " << endl;
       }
    }
    else{
        cout << "je peux pas y aller" << endl;
    }

    cout << entite1.getPositionX() << endl << entite1.getPositionY() << endl;

    engine.addCommande(dep1);

   
    return 0;
}