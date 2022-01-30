#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <unordered_map>

#include <json/json.h>
#include <thread>

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


void exportationPerso(string fichierJson, string type, vector<Heros>& herosJeu, vector<Ennemi>& ennemiJeu, vector<ActionSuppDef>& actionSuppDefs, vector<ActionSuppOff>& actionSuppOffs){
    static std::unordered_map<std::string,Classe> const nomsClasse = { {"ARCHER",Classe::ARCHER}, {"ASSASSIN",Classe::ASSASSIN}, {"DRUIDE",Classe::DRUIDE}, {"GUERRIER",Classe::GUERRIER}, {"MAGE",Classe::MAGE}, {"PRETRE",Classe::PRETRE} };
    static std::unordered_map<std::string,Race> const nomsRace = { {"ORC",Race::ORC}, {"ARAIGNEE",Race::ARAIGNEE}, {"SQUELETTE",Race::SQUELETTE}, {"FANTOME",Race::FANTOME}, {"ZOMBIE",Race::ZOMBIE}, {"SERPENT",Race::SERPENT} };
    static std::unordered_map<std::string,Statut> const nomsStatut = { {"SNONE",Statut::SNONE}, {"CONFUS",Statut::CONFUS}, {"EMPOISONNE",Statut::EMPOISONNE}, {"GLACE",Statut::GLACE}, {"PARALYSE",Statut::PARALYSE}, {"BRULE",Statut::BRULE}};
    
    ifstream jPerso(fichierJson);
    Json::Reader readerPerso;
    Json::Value obj;
    readerPerso.parse(jPerso, obj);

    Json::Value& objPerso = obj[type];

    for(unsigned int indPerso = 0; indPerso<objPerso.size();indPerso++){
        string nom = objPerso[indPerso]["nom"].asString();
        int positionX = objPerso[indPerso]["positionX"].asUInt();
        int positionY = objPerso[indPerso]["positionY"].asUInt();
        int niveau = objPerso[indPerso]["niveau"].asUInt();

        const Json::Value& equipement = objPerso[indPerso]["equipement"];
        vector<Equipement> equipementsPerso;
        // vector<Equipement*> equipements(equipement.size());
        for (unsigned int indEquip = 0; indEquip < equipement.size(); indEquip++){
            string nomEquip = equipement[indEquip]["nom"].asString();
            Statut statutEquip = nomsStatut.find(equipement[indEquip]["statut"].asString())->second;
            vector<int> statEquip(9);
            for(unsigned int indStat = 0; indStat<9;indStat++) statEquip[indStat] = equipement[indEquip]["stat"][indStat].asUInt();
            Equipement equip(nomEquip, statutEquip, statEquip);
            equipementsPerso.push_back(equip);
        }

        const Json::Value& actionSupp = objPerso[indPerso]["actionSupp"];
        vector<ActionSupp*> actionSupps(actionSupp.size());
        for (unsigned int indActionSupp = 0; indActionSupp < actionSupp.size(); indActionSupp++){
            if(actionSupp[indActionSupp]["type"].asString() == "Def"){
                string nomActionSupp = actionSupp[indActionSupp]["nom"].asString();
                int statActionSupp = actionSupp[indActionSupp]["stat"].asUInt();
                int porteeActionSupp = actionSupp[indActionSupp]["portee"].asUInt();
                bool statutActionSupp = actionSupp[indActionSupp]["statut"].asBool();
                ActionSuppDef actionSupp(nomActionSupp, statActionSupp, porteeActionSupp, statutActionSupp);
                actionSuppDefs.push_back(actionSupp);
                actionSupps[indActionSupp] = &actionSuppDefs[actionSuppDefs.size()-1];
            } else {
                string nomActionSupp = actionSupp[indActionSupp]["nom"].asString();
                int statActionSupp = actionSupp[indActionSupp]["stat"].asUInt();
                int porteeActionSupp = actionSupp[indActionSupp]["portee"].asUInt();
                Statut statutActionSupp = nomsStatut.find(actionSupp[indActionSupp]["statut"].asString())->second;
                ActionSuppOff actionSupp(nomActionSupp, statActionSupp, porteeActionSupp, statutActionSupp);
                actionSuppOffs.push_back(actionSupp);
                actionSupps[indActionSupp] = &actionSuppOffs[actionSuppOffs.size()-1];
            }
        }

        if(type == "HEROS"){
            Classe classe = nomsClasse.find(objPerso[indPerso]["classe"].asString())->second;
            Heros herosAct(nom, classe, niveau, positionX, positionY, equipementsPerso, actionSupps);
            herosJeu.push_back(herosAct);
        } else {
            Race race = nomsRace.find(objPerso[indPerso]["race"].asString())->second;
            Ennemi ennemiAct(nom, race, niveau, positionX, positionY, equipementsPerso, actionSupps);
            ennemiJeu.push_back(ennemiAct);
        }
    }
}


void actualiserEngine(Engine* engine){
    sf::Clock clkEngine;
    sf::Time elapsed = clkEngine.getElapsedTime();
    engine->actualiser();
    while(elapsed<sf::milliseconds(10)){
        elapsed = clkEngine.getElapsedTime();
    }
    actualiserEngine(engine);
}


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

        vector<Entite*> persoJeu;
        vector<Heros> herosJeu;
        vector<Ennemi> ennemiJeu;
        //vector<vector<Equipement>> equipementsHeros(6);
        vector<ActionSuppDef> actionSuppDefs;
        vector<ActionSuppOff> actionSuppOffs;

        exportationPerso("json/heros.json", "HEROS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<herosJeu.size();i++) persoJeu.push_back(&herosJeu[i]);
        exportationPerso("json/ennemis.json", "ENNEMIS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<ennemiJeu.size();i++) persoJeu.push_back(&ennemiJeu[i]);


        //exportation de la carte depuis le json
        state.chargerMap("json/map.json");
        int nbLargeur = state.getDecor().getLargeur();
        int nbHauteur = state.getDecor().getHauteur();
        /*ifstream jMap("json/map.json");
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
        }*/


        //création de la map

        //informations non-modifiables
        //Decor decor(nbLargeur, nbLongueur, map);
        
        //implémentation dans le state
        //state.setDecor(decor);
        state.setDe(6);
        state.setEntites(persoJeu);
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
        CoucheTerrain coucheDecor(largeurColonne1, 0, nbHauteur, nbLargeur, 30);
        CoucheTerrain couchePerso(largeurColonne1, 0, nbHauteur, nbLargeur, 30);

        std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};  
        std::vector<CoucheTerrain> terrains = {coucheDecor, couchePerso};

        //engine
        Engine engine(&state);


        //CommandeDeplacement dep1(3,1);
        //CommandeAttaque att1(&entite2);
        //CommandeActionSupplementaire act1(&entite2, entite1.getAutresActions()[1]);


        sf::Clock clkEngine;
        /*bool depl1Fait = false;
        bool att1Fait = false;
        bool act1Fait = false;*/
        bool fenetre = true;
        
        Scene scene(hauteurFenetre,largeurFenetre);

        scene.setState(engine.getState());
        scene.setCaseActuelle(sf::Vector2f(2,1));
        scene.setMenus(menus);
        scene.setTerrains(terrains);
        scene.chargerFenetre();
        HeuristiqueAI heuristiqueAI(*engine.getState());
        RandomAI randomAI(*engine.getState());
        fenetre = scene.afficherFenetre(0); 

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

            /*scene.setState(&engine.getState());
            scene.setCaseActuelle(sf::Vector2f(2,1));
            scene.setMenus(menus);
            scene.setTerrains(terrains);*/
            fenetre = scene.afficherFenetre(0); 
            heuristiqueAI.run(*engine.getState(), engine);
            //if(engine.getState()->getOrdreTour()[0]->getType() <6)heuristiqueAI.run(*engine.getState(), engine);
            //else randomAI.run(*engine.getState(), engine);
        }
    }
    else if (strcmp(argv[1],"randomVSheur")==0)
    {
        State state;

        // Informations modifiables pour changer l'état
        //création des personnages

        vector<Entite*> persoJeu;
        vector<Heros> herosJeu;
        vector<Ennemi> ennemiJeu;
        //vector<vector<Equipement>> equipementsHeros(6);
        vector<ActionSuppDef> actionSuppDefs;
        vector<ActionSuppOff> actionSuppOffs;

        exportationPerso("json/heros.json", "HEROS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<herosJeu.size();i++) persoJeu.push_back(&herosJeu[i]);
        exportationPerso("json/ennemis.json", "ENNEMIS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<ennemiJeu.size();i++) persoJeu.push_back(&ennemiJeu[i]);


        //exportation de la carte depuis le json
        state.chargerMap("json/map.json");
        int nbLargeur = state.getDecor().getLargeur();
        int nbHauteur = state.getDecor().getHauteur();
    
        //création de la map

        state.setDe(6);
        state.setEntites(persoJeu);
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
        CoucheTerrain coucheDecor(largeurColonne1, 0, nbHauteur, nbLargeur, 30);
        CoucheTerrain couchePerso(largeurColonne1, 0, nbHauteur, nbLargeur, 30);

        std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};  
        std::vector<CoucheTerrain> terrains = {coucheDecor, couchePerso};

        //engine
        Engine engine(&state);


        sf::Clock clkEngine;
        bool fenetre = true;
        
        Scene scene(hauteurFenetre,largeurFenetre);

        scene.setState(engine.getState());
        scene.setCaseActuelle(sf::Vector2f(2,1));
        scene.setMenus(menus);
        scene.setTerrains(terrains);
        scene.chargerFenetre();
        HeuristiqueAI heuristiqueAI(*engine.getState());
        RandomAI randomAI(*engine.getState());
        fenetre = scene.afficherFenetre(1); 

        while(fenetre){
            
            fenetre = scene.afficherFenetre(1); 
            if(engine.getState()->getOrdreTour()[0]->getType() <6)heuristiqueAI.run(*engine.getState(), engine);
            else randomAI.run(*engine.getState(), engine);
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

        Engine engineTest(&stateTest);

        // Tests de l'IA aléatoire
        //RandomAI randomAItest(stateTest);
        //randomAItest.run(stateTest, engineTest);


        // Test de l'IA heuristique
        HeuristiqueAI HeuristiqueAItest(stateTest);
        HeuristiqueAItest.run(stateTest, engineTest);

    }
    else if (strcmp(argv[1],"heuristic_ai")==0)
    {
        State state;

        // Informations modifiables pour changer l'état
        //création des personnages

        vector<Entite*> persoJeu;
        vector<Heros> herosJeu;
        vector<Ennemi> ennemiJeu;
        //vector<vector<Equipement>> equipementsHeros(6);
        vector<ActionSuppDef> actionSuppDefs;
        vector<ActionSuppOff> actionSuppOffs;

        exportationPerso("json/heros.json", "HEROS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<herosJeu.size();i++) persoJeu.push_back(&herosJeu[i]);
        exportationPerso("json/ennemis.json", "ENNEMIS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<ennemiJeu.size();i++) persoJeu.push_back(&ennemiJeu[i]);


        //exportation de la carte depuis le json
        state.chargerMap("json/map.json");
        int nbLargeur = state.getDecor().getLargeur();
        int nbHauteur = state.getDecor().getHauteur();
    
        //création de la map

        state.setDe(6);
        state.setEntites(persoJeu);
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
        CoucheTerrain coucheDecor(largeurColonne1, 0, nbHauteur, nbLargeur, 30);
        CoucheTerrain couchePerso(largeurColonne1, 0, nbHauteur, nbLargeur, 30);

        std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};  
        std::vector<CoucheTerrain> terrains = {coucheDecor, couchePerso};

        //engine
        Engine engine(&state);


        sf::Clock clkEngine;
        bool fenetre = true;
        
        Scene scene(hauteurFenetre,largeurFenetre);

        scene.setState(engine.getState());
        scene.setCaseActuelle(sf::Vector2f(2,1));
        scene.setMenus(menus);
        scene.setTerrains(terrains);
        scene.chargerFenetre();
        HeuristiqueAI heuristiqueAI(*engine.getState());
        fenetre = scene.afficherFenetre(1); 

        while(fenetre){
            
            fenetre = scene.afficherFenetre(1); 
            heuristiqueAI.run(*engine.getState(), engine);
        }
    }
    else if (strcmp(argv[1],"para")==0)
    {
        State state;

        remove("json/commande.json");

        // Informations modifiables pour changer l'état
        //création des personnages

        vector<Entite*> persoJeu;
        vector<Heros> herosJeu;
        vector<Ennemi> ennemiJeu;
        //vector<vector<Equipement>> equipementsHeros(6);
        vector<ActionSuppDef> actionSuppDefs;
        vector<ActionSuppOff> actionSuppOffs;

        exportationPerso("json/heros.json", "HEROS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<herosJeu.size();i++) persoJeu.push_back(&herosJeu[i]);
        exportationPerso("json/ennemis.json", "ENNEMIS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<ennemiJeu.size();i++) persoJeu.push_back(&ennemiJeu[i]);


        //exportation de la carte depuis le json
        state.chargerMap("json/map.json");
        int nbLargeur = state.getDecor().getLargeur();
        int nbHauteur = state.getDecor().getHauteur();
        
        //implémentation dans le state
        state.setDe(6);
        state.setEntites(persoJeu);
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
        CoucheTerrain coucheDecor(largeurColonne1, 0, nbHauteur, nbLargeur, 30);
        CoucheTerrain couchePerso(largeurColonne1, 0, nbHauteur, nbLargeur, 30);

        std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};  
        std::vector<CoucheTerrain> terrains = {coucheDecor, couchePerso};

        //engine
        Engine engine(&state);

        
        /*bool depl1Fait = false;
        bool att1Fait = false;
        bool act1Fait = false;*/
        bool fenetre = true;
        
        Scene scene(hauteurFenetre,largeurFenetre);

        scene.setState(engine.getState());
        scene.setCaseActuelle(sf::Vector2f(2,1));
        scene.setMenus(menus);
        scene.setTerrains(terrains);
        scene.chargerFenetre();
        HeuristiqueAI heuristiqueAI(*engine.getState());
        RandomAI randomAI(*engine.getState());
        fenetre = scene.afficherFenetrePara(0); 

        thread t(actualiserEngine, &engine);
        t.detach();

        while(fenetre){
            fenetre = scene.afficherFenetrePara(0); 
            if(engine.getState()->getOrdreTour()[0]->getType()>=6) {
                sf::Clock attente;
                heuristiqueAI.runPara(*engine.getState(), engine);
                sf::Time elapsed = attente.getElapsedTime();
                while(elapsed < sf::milliseconds(300)){
                    elapsed = attente.getElapsedTime();
                }
            }
            //if(engine.getState()->getOrdreTour()[0]->getType() <6)heuristiqueAI.run(*engine.getState(), engine);
            //else randomAI.run(*engine.getState(), engine);
        }
    }
    else if (strcmp(argv[1],"thread")==0)
    {
        State state;

        remove("json/commande.json");

        // Informations modifiables pour changer l'état
        //création des personnages

        vector<Entite*> persoJeu;
        vector<Heros> herosJeu;
        vector<Ennemi> ennemiJeu;
        //vector<vector<Equipement>> equipementsHeros(6);
        vector<ActionSuppDef> actionSuppDefs;
        vector<ActionSuppOff> actionSuppOffs;

        exportationPerso("json/heros.json", "HEROS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<herosJeu.size();i++) persoJeu.push_back(&herosJeu[i]);
        exportationPerso("json/ennemis.json", "ENNEMIS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<ennemiJeu.size();i++) persoJeu.push_back(&ennemiJeu[i]);


        //exportation de la carte depuis le json
        state.chargerMap("json/map.json");
        int nbLargeur = state.getDecor().getLargeur();
        int nbHauteur = state.getDecor().getHauteur();
        
        //implémentation dans le state
        state.setDe(6);
        state.setEntites(persoJeu);
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
        CoucheTerrain coucheDecor(largeurColonne1, 0, nbHauteur, nbLargeur, 30);
        CoucheTerrain couchePerso(largeurColonne1, 0, nbHauteur, nbLargeur, 30);

        std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};  
        std::vector<CoucheTerrain> terrains = {coucheDecor, couchePerso};

        //engine
        Engine engine(&state);

        
        /*bool depl1Fait = false;
        bool att1Fait = false;
        bool act1Fait = false;*/
        bool fenetre = true;
        
        Scene scene(hauteurFenetre,largeurFenetre);

        scene.setState(engine.getState());
        scene.setCaseActuelle(sf::Vector2f(2,1));
        scene.setMenus(menus);
        scene.setTerrains(terrains);
        scene.chargerFenetre();
        HeuristiqueAI heuristiqueAI(*engine.getState());
        RandomAI randomAI(*engine.getState());
        fenetre = scene.afficherFenetrePara(0); 

        thread t(actualiserEngine, &engine);
        t.detach();

        while(fenetre){
            fenetre = scene.afficherFenetrePara(1); 
            heuristiqueAI.runPara(*engine.getState(), engine);
        }
    }
    else if (strcmp(argv[1],"replay")==0)
    {
        State state;

        // Informations modifiables pour changer l'état
        //création des personnages

        vector<Entite*> persoJeu;
        vector<Heros> herosJeu;
        vector<Ennemi> ennemiJeu;
        //vector<vector<Equipement>> equipementsHeros(6);
        vector<ActionSuppDef> actionSuppDefs;
        vector<ActionSuppOff> actionSuppOffs;

        exportationPerso("json/heros.json", "HEROS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<herosJeu.size();i++) persoJeu.push_back(&herosJeu[i]);
        exportationPerso("json/ennemis.json", "ENNEMIS", herosJeu, ennemiJeu, actionSuppDefs,actionSuppOffs);
        for(unsigned int i = 0; i<ennemiJeu.size();i++) persoJeu.push_back(&ennemiJeu[i]);


        //exportation de la carte depuis le json
        state.chargerMap("json/map.json");
        int nbLargeur = state.getDecor().getLargeur();
        int nbHauteur = state.getDecor().getHauteur();
        
        //implémentation dans le state
        state.setDe(6);
        state.setEntites(persoJeu);
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
        CoucheTerrain coucheDecor(largeurColonne1, 0, nbHauteur, nbLargeur, 30);
        CoucheTerrain couchePerso(largeurColonne1, 0, nbHauteur, nbLargeur, 30);

        std::vector<CoucheMenu> menus = {menuOrdre,menuPerso,menuAction,menuCaseActuelle,menuDes};  
        std::vector<CoucheTerrain> terrains = {coucheDecor, couchePerso};

        //engine
        Engine engine(&state);

        
        /*bool depl1Fait = false;
        bool att1Fait = false;
        bool act1Fait = false;*/
        bool fenetre = true;
        
        Scene scene(hauteurFenetre,largeurFenetre);

        scene.setState(engine.getState());
        scene.setCaseActuelle(sf::Vector2f(2,1));
        scene.setMenus(menus);
        scene.setTerrains(terrains);
        scene.chargerFenetre();
        fenetre = scene.afficherFenetre(1); 

        std::ifstream jCommande("json/commande.json");
        Json::Reader readerCommande;
        Json::Value commandeJsonValue;
        readerCommande.parse(jCommande, commandeJsonValue);

        int nbCommande = commandeJsonValue.size();

        while(fenetre){
            fenetre = scene.afficherFenetre(1); 
            engine.actualiser();
            engine.getState()->setIndiceCommande(engine.getState()->getIndiceCommande() +1);
            if(engine.getState()->getIndiceCommande()>nbCommande) fenetre = false;
        }
    }
    
    else
    {
        cout << "Veuillez entrer une commande" << endl << "Commandes disponibles : hello, state, render" << endl;
    }
    return 0;
}
