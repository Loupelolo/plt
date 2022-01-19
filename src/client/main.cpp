#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <unordered_map>

#include <json/json.h>

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

        static std::unordered_map<std::string,Classe> const nomsClasse = { {"ARCHER",Classe::ARCHER}, {"ASSASSIN",Classe::ASSASSIN}, {"DRUIDE",Classe::DRUIDE}, {"GUERRIER",Classe::GUERRIER}, {"MAGE",Classe::MAGE}, {"PRETRE",Classe::PRETRE} };
        static std::unordered_map<std::string,Statut> const nomsStatut = { {"SNONE",Statut::SNONE}, {"CONFUS",Statut::CONFUS}, {"EMPOISONNE",Statut::EMPOISONNE}, {"GLACE",Statut::GLACE}, {"PARALYSE",Statut::PARALYSE}, {"BRULE",Statut::BRULE}};
        

        // Informations modifiables pour changer l'état
        //création des personnages

        ifstream jHeros("json/heros.json");
        Json::Reader readerHeros;
        Json::Value objHeros;
        readerHeros.parse(jHeros, objHeros);

        vector<Entite*> persoJeu;
        vector<Heros> herosJeu(6);
        vector<vector<Equipement>> equipementsHeros(6);
        vector<ActionSuppDef> actionSuppDefsHeros;
        vector<ActionSuppOff> actionSuppOffsHeros;

        for(unsigned int indHeros; indHeros<6;indHeros++){
            string nom = objHeros[indHeros]["nom"].asString();
            Classe classe = nomsClasse.find(objHeros[indHeros]["classe"].asString())->second;
            int positionX = objHeros[indHeros]["positionX"].asUInt();
            int positionY = objHeros[indHeros]["positionY"].asUInt();

            const Json::Value& equipement = objHeros[indHeros]["equipement"];
            equipementsHeros[indHeros].resize(equipement.size());
           // vector<Equipement*> equipements(equipement.size());
            for (unsigned int indEquip = 0; indEquip < equipement.size(); indEquip++){
                string nomEquip = equipement[indEquip]["nom"].asString();
                Statut statutEquip = nomsStatut.find(equipement[indEquip]["statut"].asString())->second;
                vector<int> statEquip(9);
                for(unsigned int indStat = 0; indStat<9;indStat++) statEquip[indStat] = equipement[indEquip]["stat"][indStat].asUInt();
                Equipement equip(nomEquip, statutEquip, statEquip);
                equipementsHeros[indHeros][indEquip] =equip;
                //equipements[indEquip] = &equipementsHeros[indHeros][indEquip];
            }

            const Json::Value& actionSupp = objHeros[indHeros]["actionSupp"];
            vector<ActionSupp*> actionSupps(actionSupp.size());
            for (unsigned int indActionSupp = 0; indActionSupp < actionSupp.size(); indActionSupp++){
                if(actionSupp[indActionSupp]["type"].asString() == "Def"){
                    string nomActionSupp = actionSupp[indActionSupp]["nom"].asString();
                    int statActionSupp = actionSupp[indActionSupp]["stat"].asUInt();
                    int porteeActionSupp = actionSupp[indActionSupp]["portee"].asUInt();
                    bool statutActionSupp = actionSupp[indActionSupp]["statut"].asBool();
                    ActionSuppDef actionSupp(nomActionSupp, statActionSupp, porteeActionSupp, statutActionSupp);
                    actionSuppDefsHeros.push_back(actionSupp);
                    actionSupps[indActionSupp] = &actionSuppDefsHeros[actionSuppDefsHeros.size()-1];
                } else {
                    string nomActionSupp = actionSupp[indActionSupp]["nom"].asString();
                    int statActionSupp = actionSupp[indActionSupp]["stat"].asUInt();
                    int porteeActionSupp = actionSupp[indActionSupp]["portee"].asUInt();
                    Statut statutActionSupp = nomsStatut.find(actionSupp[indActionSupp]["statut"].asString())->second;
                    ActionSuppOff actionSupp(nomActionSupp, statActionSupp, porteeActionSupp, statutActionSupp);
                    actionSuppOffsHeros.push_back(actionSupp);
                    actionSupps[indActionSupp] = &actionSuppOffsHeros[actionSuppOffsHeros.size()-1];
                }
            }

            Heros herosAct(nom, classe, 1, positionX, positionY, equipementsHeros[indHeros], actionSupps);
            herosJeu[indHeros] = herosAct;
            persoJeu.push_back(&herosJeu[indHeros]);
        }

        /*Entite entite2("Charles");
        entite2.setPositionX(2);
        entite2.setPositionY(1);
        entite2.setPV(70);
        entite2.setStat(PVMAX, 30);
        entite2.setStat(DEPLACEMENT, 4);
        entite2.setPM(3);
        entite1.setType(1);

        Entite entite3("Elisabeth");
        entite3.setPositionX(7);
        entite3.setPositionY(0);
        entite2.setStat(DEPLACEMENT, 2);
        entite3.setPV(300);
        entite3.setPM(500);
        entite3.setType(2);*/

        //entite1.effectuerActionSupp(&action1, &entite2);
        //entite1.effectuerActionSupp(&action2, &entite2);


        //exportation de la carte depuis le json
        ifstream jMap("json/map.json");
        Json::Reader reader;
        Json::Value obj;
        reader.parse(jMap, obj);

        const Json::Value& layer = obj["layers"]; // tableau de layers

        int nbLargeur = layer[0]["width"].asUInt();
        int nbLongueur = layer[0]["height"].asUInt();

        int tailleMap = nbLargeur*nbLongueur;

        const Json::Value& data = layer[0]["data"]; // tableau de data

        std::vector<TypeTerrain> map(tailleMap);
        for (unsigned int i = 0; i < data.size(); i++){
            map[i] = static_cast<TypeTerrain>(data[i].asUInt());
        }

        //création de la map
        /*std::vector<TypeTerrain> map = //maximum 18 de largeur et 9 de hauteur
          {
            MUR , MUR , MUR , MUR , MUR , MUR , MUR , SOL , MUR , MUR , MUR , MUR , MUR ,
            PORT, SOL , SOL , SOL , SOL , SOL , SOL , SOL , OBST, SOL , SOL , SOL , SECR,
            MUR , EAU , SOL , SOL , SOL , SOL , PIEG, SOL , SOL , SOL , SOL , TRES, MUR ,
            MUR , EAU , SOL , EAU , EAU , EAU , EAU , EAU , EAU , EAU , EAU , EAU , EAU 
          };
        int nbLargeur = 13;
        int nbLongueur = 4;*/

        //informations non-modifiables
        Decor decor(nbLargeur, nbLongueur, map);
        //decor.action(6, 2, &entite1);
        
        //implémentation dans le state
        state.setDecor(decor);
        state.setDe(6);
        state.setEntites({persoJeu.begin(), persoJeu.begin()+6});
        state.nouveauTour();
      
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
        std::vector<CoucheTerrain> terrains = {coucheDecor, couchePerso};

        //engine
        Engine engine(state);

        //CommandeDeplacement dep1(3,1);
        //CommandeAttaque att1(&entite2);
        //CommandeActionSupplementaire act1(&entite2, entite1.getAutresActions()[1]);

        sf::Clock clkEngine;
        /*bool depl1Fait = false;
        bool att1Fait = false;
        bool act1Fait = false;*/
        bool fenetre = true;
        
        Scene scene(hauteurFenetre,largeurFenetre);

        scene.setState(&engine.getState());
        scene.setCaseActuelle(sf::Vector2f(2,1));
        scene.setMenus(menus);
        scene.setTerrains(terrains);
        scene.chargerFenetre();
        fenetre = scene.afficherFenetre(); 

        while(fenetre){
            
            /*sf::Time actuEngine = clkEngine.getElapsedTime();

            if(actuEngine >= sf::seconds(5) && !depl1Fait){
                cout<<"depl"<<endl;
                engine.executerCommande(dep1);
                depl1Fait = true;
            }
            
            if(actuEngine >= sf::seconds(10) && !att1Fait){
                cout<<"att"<<endl;
                engine.executerCommande(att1);
                att1Fait = true;
            }
            
            if(actuEngine >= sf::seconds(15) && !act1Fait){
                cout<<"act"<<endl;
                engine.executerCommande(act1);
                act1Fait = true;
            }*/

            scene.setState(&engine.getState());
            scene.setCaseActuelle(sf::Vector2f(2,1));
            scene.setMenus(menus);
            scene.setTerrains(terrains);
            fenetre = scene.afficherFenetre(); 
        }
    }
    else if (strcmp(argv[1],"testRandomAi")==0)
    {
        State stateTest;
        Heros herosTest("Diana", ARCHER);
        herosTest.setPositionX(0);
        herosTest.setPositionY(0);
        Ennemi ennemiTest("Paparazzi", ORC);
        ennemiTest.setPositionX(12);
        ennemiTest.setPositionY(3);
        Heros herosTest2("Charles", ARCHER);
        herosTest2.setPositionX(12);
        herosTest2.setPositionY(2);
        Ennemi ennemiTest2("Alma", ORC);
        ennemiTest2.setPositionX(11);
        ennemiTest2.setPositionY(2);
        stateTest.setEntites({&herosTest, &ennemiTest, &ennemiTest2, &herosTest2});

        std::vector<TypeTerrain> mapTest = //maximum 18 de largeur et 9 de hauteur
          {
            SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL ,
            SOL, SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL, SOL , SOL , SOL , SOL,
            SOL , SOL , SOL , SOL , SOL , SOL , SOL, SOL , SOL , SOL , SOL , SOL, SOL ,
            SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL , SOL 
          };
        int nbLargeur = 13;
        Decor decorTest(nbLargeur, 4, mapTest);
        stateTest.setDecor(decorTest);
        stateTest.setOrdreTour({&herosTest, &ennemiTest, &ennemiTest2, &herosTest2});

        Engine engineTest(stateTest);

        // Tests de l'IA aléatoire
        //RandomAI randomAItest(stateTest);
        //randomAItest.run(stateTest, engineTest);


        // Test de l'IA heuristique
        HeuristiqueAI HeuristiqueAItest(stateTest);
        HeuristiqueAItest.run(stateTest, engineTest);
    }
    else
    {
        cout << "Veuillez entrer une commande" << endl << "Commandes disponibles : hello, state, render" << endl;
    }
    return 0;
}
