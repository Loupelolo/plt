#include <iostream>
#include <cstring>
#include <unistd.h>

#include <state.h>
#include <render.h>
#include <engine.h>
#include <ai.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML


using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;


int main(int argc,char* argv[])
{
    if(strcmp(argv[1],"hello")==0)
    {
        cout << "Hello World!" << endl;
    }
    else if (strcmp(argv[1],"state")==0)
    {
        cout << "Entrez 'make test' dans un terminal pour lancer une série de tests unitaires." << endl;
    }
    else if (strcmp(argv[1],"render")==0)
    {
        State state;

        // Informations modifiables pour changer l'état
        //création des personnages
        Heros entite1("Diana", ARCHER);
        entite1.setPositionX(4);
        entite1.setPositionY(2);
        entite1.setType(0);
        ActionSuppOff action1("Boule de feu", 50, BRULE);
        ActionSuppDef action2("Soin", 20, false);
        Equipement equip1("Epee");
        Equipement equip2("Bouclier");
        entite1.setAutresActions({action1, action2});
        entite1.setEquipement({equip1,equip2});

        Entite entite2("Charles");
        entite2.setPositionX(2);
        entite2.setPositionY(1);
        entite2.setPV(70);
        entite2.setStat(PVMAX, 30);
        entite2.setPM(3);
        entite1.setType(1);

        Entite entite3("Elisabeth");
        entite3.setPositionX(7);
        entite3.setPositionY(0);
        entite3.setPV(300);
        entite3.setPM(500);
        entite3.setType(2);

        entite1.effectuerActionSupp(&action1, &entite2);
        entite1.effectuerActionSupp(&action2, &entite2);

        // valeur de deplacement
        //entite1.setStats({0,0,0,0,0,0,0,0,3});
        entite2.setStats({0,0,0,0,0,0,0,0,4});
        entite3.setStats({0,0,0,0,0,0,0,0,2});

        //création de la map
        std::vector<TypeTerrain> map = //maximum 18 de largeur et 9 de hauteur
          {
            MUR , MUR , MUR , MUR , MUR , MUR , MUR , SOL , MUR , MUR , MUR , MUR , MUR ,
            PORT, SOL , SOL , SOL , SOL , SOL , SOL , SOL , OBST, SOL , SOL , SOL , SECR,
            MUR , EAU , SOL , SOL , SOL , SOL , PIEG, SOL , SOL , SOL , SOL , TRES, MUR ,
            MUR , EAU , SOL , EAU , EAU , EAU , EAU , EAU , EAU , EAU , EAU , EAU , EAU 
          };
        int nbLargeur = 13;

        //informations non-modifiables
        Decor decor(nbLargeur, 4, map);
        decor.action(6, 2, &entite1);
        
        //implémentation dans le state
        state.setDecor(decor);
        state.setDe(6);
        state.setEntites({&entite1,&entite2,&entite3});
        state.setOrdreTour({&entite1,&entite2,&entite3});
      
        //définition de l'affichage des menus
        int largeurColonne1 = 150;
        int largeurColonne2 = 600;
        int largeurColonne3 = 150;
        int largeurFenetre = largeurColonne1+largeurColonne2+largeurColonne3;

        int hauteurLigne1 = 300;
        int hauteurLigne2 = 150;
        int hauteurFenetre = hauteurLigne1+hauteurLigne2;


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

        //définition de l'affichage du terrain
        CoucheTerrain coucheDecor(largeurColonne1, 0, map.size()/nbLargeur, nbLargeur, 32);
        CoucheTerrain couchePerso(largeurColonne1, 0, map.size()/nbLargeur, nbLargeur, 32);

        std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};

        //définition de l'affichage
        Scene scene(hauteurFenetre,largeurFenetre);
        scene.setState(state);
        scene.setCaseActuelle(sf::Vector2f(2,1));

        //Affichage
        scene.afficherFenetre(menus,{coucheDecor,couchePerso});        

        //engine
        Engine engine(state);
        CommandeDeplacement dep1(3,1);
        engine.executerCommande(dep1);

        //définition de l'affichage
        Scene scene2(hauteurFenetre,largeurFenetre);
        scene2.setState(engine.getState());
        scene2.setCaseActuelle(sf::Vector2f(2,1));

        //Affichage
        scene2.afficherFenetre(menus,{coucheDecor,couchePerso});

        CommandeAttaque att1(&entite2);
        engine.executerCommande(att1);

        //définition de l'affichage
        Scene scene3(hauteurFenetre,largeurFenetre);
        scene3.setState(engine.getState());
        scene3.setCaseActuelle(sf::Vector2f(2,1));

        //Affichage
        scene3.afficherFenetre(menus,{coucheDecor,couchePerso});

        CommandeActionSupplementaire act1(&entite2, entite1.getAutresActions()[1]);
        engine.executerCommande(act1);

        //définition de l'affichage
        Scene scene4(hauteurFenetre,largeurFenetre);
        scene4.setState(engine.getState());
        scene4.setCaseActuelle(sf::Vector2f(2,1));

        //Affichage
        scene4.afficherFenetre(menus,{coucheDecor,couchePerso});


    }
    else if (strcmp(argv[1],"testRandomAi")==0)
    {
        State stateTest;
        Heros herosTest("Diana", ARCHER);
        herosTest.setPositionX(1);
        herosTest.setPositionY(1);
        Ennemi ennemiTest("Alma", ORC);
        ennemiTest.setPositionX(12);
        ennemiTest.setPositionY(1);
        stateTest.setEntites({&herosTest, &ennemiTest});

        std::vector<TypeTerrain> mapTest = //maximum 18 de largeur et 9 de hauteur
          {
            MUR , MUR , MUR , MUR , MUR , MUR , MUR , SOL , MUR , MUR , MUR , MUR , MUR ,
            PORT, SOL , SOL , SOL , SOL , SOL , SOL , SOL , OBST, SOL , SOL , SOL , SECR,
            MUR , EAU , SOL , SOL , SOL , SOL , PIEG, SOL , SOL , SOL , SOL , TRES, MUR ,
            MUR , EAU , SOL , EAU , EAU , EAU , EAU , EAU , EAU , EAU , EAU , EAU , EAU 
          };
        int nbLargeur = 13;
        Decor decorTest(nbLargeur, 4, mapTest);
        stateTest.setDecor(decorTest);
        stateTest.setOrdreTour({&herosTest, &ennemiTest});

        Engine engineTest(stateTest);

        RandomAI randomAItest(stateTest);

        randomAItest.run(stateTest, engineTest);
    }
    else
    {
        cout << "Veuillez entrer une commande" << endl << "Commandes disponibles : hello, state, render" << endl;
    }
    return 0;
}

//Modification d'engine.dia : executerCommande dans Engine