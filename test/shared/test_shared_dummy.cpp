#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestStateActionSupp)
{
  {
    // Test d'ActionSupp ()
    ActionSupp actionSuppTest;
    BOOST_CHECK_EQUAL(actionSuppTest.getNom(), "Action");
    BOOST_CHECK_EQUAL(actionSuppTest.getStat(), 0);
  }
  
  {
    // Test d'ActionSuppTest(std::string nom)
    ActionSupp actionSuppTest("nomTest");
    BOOST_CHECK_EQUAL(actionSuppTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(actionSuppTest.getStat(), 0);
  }

  {
    // Test d'ActionSupp (const ActionSupp &p)
    ActionSupp actionSuppTest1;
    actionSuppTest1.setNom("nomTest");
    actionSuppTest1.setStat(9);
    ActionSupp actionSuppTest2(actionSuppTest1);
    BOOST_CHECK_EQUAL(actionSuppTest2.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(actionSuppTest2.getStat(), 9);
  }

  {
    // Test de setNom (std::string nom) et getNom ()
    ActionSupp actionSuppTest("nomTest");
    actionSuppTest.setNom("nomTest2");
    std::string testedNom = actionSuppTest.getNom();
    BOOST_CHECK_EQUAL(testedNom, "nomTest2");
  }

  {
    // Test de setStat (int stat) et getStat ()
    ActionSupp actionSuppTest;
    actionSuppTest.setStat(9);
    int testedStat = actionSuppTest.getStat();
    BOOST_CHECK_EQUAL(testedStat, 9);
  }

  /*{
    // Test d'effectuerAction (Entite* cible)
  }*/
}

BOOST_AUTO_TEST_CASE(TestStateActionSuppDef)
{
  {
    // Test d'ActionSuppDef ()
    ActionSuppDef actionSuppDeftest;
    BOOST_CHECK_EQUAL(actionSuppDeftest.getNom(), "Action");
    BOOST_CHECK_EQUAL(actionSuppDeftest.getStat(), 0);
    BOOST_CHECK_EQUAL(actionSuppDeftest.getSoigneStatuts(), false);
  }

  {
    // Test d'ActionSuppDef (std::string nom, int stat, bool soigneStatuts)
    ActionSuppDef actionSuppDeftest("nomTest", 9, true);
    BOOST_CHECK_EQUAL(actionSuppDeftest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(actionSuppDeftest.getStat(), 9);
    BOOST_CHECK_EQUAL(actionSuppDeftest.getSoigneStatuts(), true);
  }

  {
    // Test d'ActionSuppDef (const ActionSuppDef &p)
    ActionSuppDef actionSuppDeftest1("nomTest", 9, true);
    ActionSuppDef actionSuppDeftest2(actionSuppDeftest1);
    BOOST_CHECK_EQUAL(actionSuppDeftest2.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(actionSuppDeftest2.getStat(), 9);
    BOOST_CHECK_EQUAL(actionSuppDeftest2.getSoigneStatuts(), true);
  }

  {
    // Test de setSoigneStatuts (bool soigneStatuts) et getSoigneStatuts ()
    ActionSuppDef actionSuppDeftest;
    actionSuppDeftest.setSoigneStatuts(true);
    bool testedSoigneStatuts = actionSuppDeftest.getSoigneStatuts();
    BOOST_CHECK_EQUAL(testedSoigneStatuts, true);
  }

{
    // Test d'effectuerAction (Entite* cible)
    ActionSuppDef actionSuppDeftest("nomTest", 0, true);
    Entite entiteTest;
    entiteTest.setStats({false, false, false, false, false, false});
    actionSuppDeftest.effectuerAction(&entiteTest);
    BOOST_CHECK_EQUAL(entiteTest.getStatutSubi(0), true);
  }
}
/*
BOOST_AUTO_TEST_CASE(TestStateActionSuppOff)
{
  {
    // Test de setStatuts (std::vector<bool> statuts) et getStatuts ()
    ActionSuppOff actionSuppOffTest;
    actionSuppOffTest.setStatuts({true, false});
    std::vector<bool> testedStatuts = actionSuppOffTest.getStatuts();
    BOOST_CHECK_EQUAL(testedStatuts[0], true);
    BOOST_CHECK_EQUAL(testedStatuts[1], false);
  }

  {
    // -----Test d'attaque (Entite cible)
    BOOST_CHECK(1);
  }
}
/*
BOOST_AUTO_TEST_CASE(TestStateDecor)
{
  {
    // Test du constructeur Decor (std::vector<TypeTerrain> map)
    std::vector<TypeTerrain> mapTest{NONE, SOL, MUR};
    Decor decorTest(mapTest);
    std::vector<TypeTerrain> testedMap = decorTest.getMap();
    BOOST_CHECK_EQUAL(testedMap[0], NONE);
    BOOST_CHECK_EQUAL(testedMap[1], SOL);
    BOOST_CHECK_EQUAL(testedMap[2], MUR);
  }

  {
    // Test de setHauteur(int hauteur) et getHauteur ()
    Decor decorTest;
    decorTest.setHauteur(9);
    int testedHauteur = decorTest.getHauteur();
    BOOST_CHECK_EQUAL(testedHauteur, 9);
  }

  {
    // Test de setLargeur(int largeur) et getLargeur ()
    Decor decorTest;
    decorTest.setLargeur(9);
    int testedLargeur = decorTest.getLargeur();
    BOOST_CHECK_EQUAL(testedLargeur, 9);
  }

  {
    // Test de setMap(std::vector<TypeTerrain> map) et getMap ()
    Decor decorTest;
    decorTest.setMap({NONE, SOL, MUR});
    std::vector<TypeTerrain> testedMap = decorTest.getMap();
    BOOST_CHECK_EQUAL(testedMap[0], NONE);
    BOOST_CHECK_EQUAL(testedMap[1], SOL);
    BOOST_CHECK_EQUAL(testedMap[2], MUR);
  }

  {
    // Test de setMeteo(std::vector<int> meteo) et getMeteo ()
    Decor decorTest;
    decorTest.setMeteo({0, 1, 2});
    std::vector<int> testedMeteo = decorTest.getMeteo();
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedMeteo[i], i);
    }
  }

  {
    // Test de setLumiere(std::vector<int> lumiere) et getLumiere ()
    Decor decorTest;
    decorTest.setLumiere({0, 1, 2});
    std::vector<int> testedLumiere = decorTest.getLumiere();
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedLumiere[i], i);
    }
  }

  {
    // -----Test d'action ()
    BOOST_CHECK(1);
  }
}

BOOST_AUTO_TEST_CASE(TestStateEnnemi)
{
  {
    // Test du constructeur Ennemi (std::string nom, Race race)
    Ennemi ennemiTest("nomTest", ORC);
    BOOST_CHECK_EQUAL(ennemiTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(ennemiTest.getRace(), ORC);
  }

  {
    // Test de setRace (Race race) et getRace ()
    Ennemi ennemiTest;
    ennemiTest.setRace(ORC);
    Race testedRace = ennemiTest.getRace();
    BOOST_CHECK_EQUAL(testedRace, ORC);
  }

  {
    // Test de setActif (bool actif) et getActif ()
    Ennemi ennemiTest;
    ennemiTest.setActif(false);
    bool testedActif = ennemiTest.getActif();
    BOOST_CHECK_EQUAL(testedActif, false);
  }

  {
    // -----Test d'activer ()
    BOOST_CHECK(1);
  }
}

BOOST_AUTO_TEST_CASE(TestStateEntite)
{
  {
    //  Test de Entite (std::string nom)
    Entite entiteTest("nomTest");
    BOOST_CHECK_EQUAL(entiteTest.getNom(), "nomTest");
  }

  {
    // Test de setNom (std::string nom) et getNom ()
    Entite entiteTest;
    entiteTest.setNom("nomTest");
    std::string testedNom = entiteTest.getNom();
    BOOST_CHECK_EQUAL(testedNom, "nomTest");
  }

  {
    // Test de setType (int type) et getType ()
    Entite entiteTest;
    entiteTest.setType(9);
    int testedType = entiteTest.getType();
    BOOST_CHECK_EQUAL(testedType, 9);
  }

  {
    // Test de setNiveau (int niveau) et getNiveau ()
    Entite entiteTest;
    entiteTest.setNiveau(9);
    int testedNiveau = entiteTest.getNiveau();
    BOOST_CHECK_EQUAL(testedNiveau, 9);
  }

  {
    // Test de setPositionX (int positionX) et getPositionX ()
    Entite entiteTest;
    entiteTest.setPositionX(9);
    int testedPositionX = entiteTest.getPositionX();
    BOOST_CHECK_EQUAL(testedPositionX, 9);
  }

  {
    // Test de setPositionY (int positionY) et getPositionY ()
    Entite entiteTest;
    entiteTest.setPositionY(9);
    int testedPositionY = entiteTest.getPositionY();
    BOOST_CHECK_EQUAL(testedPositionY, 9);
  }

  {
    // Test de setPV (int PV) et getPV ()
    Entite entiteTest;
    entiteTest.setPV(9);
    int testedPV = entiteTest.getPV();
    BOOST_CHECK_EQUAL(testedPV, 9);
  }

  {
    // Test de setPM (int PM) et getPM ()
    Entite entiteTest;
    entiteTest.setPM(9);
    int testedPM = entiteTest.getPM();
    BOOST_CHECK_EQUAL(testedPM, 9);
  }

  {
    // Test de setEquipement (std::vector<Equipement> equipement) et getEquipement ()
    Equipement equipementTest1;
    equipementTest1.setNom("nomTest1");
    Equipement equipementTest2;
    equipementTest2.setNom("nomTest2");
    Entite entiteTest;
    entiteTest.setEquipement({equipementTest1, equipementTest2});
    std::vector<Equipement> testedEquipement = entiteTest.getEquipement();
    BOOST_CHECK_EQUAL(testedEquipement[0].getNom(), "nomTest1");
    BOOST_CHECK_EQUAL(testedEquipement[1].getNom(), "nomTest2");
  }

  {
    // Test de setAutresActions (std::vector<ActionSupp> autresActions) et getAutresActions ()
    ActionSupp actionSuppTest1;
    actionSuppTest1.setNom("nomTest1");
    ActionSupp actionSuppTest2;
    actionSuppTest2.setNom("nomTest2");
    Entite entiteTest;
    entiteTest.setAutresActions({actionSuppTest1, actionSuppTest2});
    std::vector<ActionSupp> testedActionSupp = entiteTest.getAutresActions();
    BOOST_CHECK_EQUAL(testedActionSupp[0].getNom(), "nomTest1");
    BOOST_CHECK_EQUAL(testedActionSupp[1].getNom(), "nomTest2");
  }

  {
    // Test de setStat (int index, int stat) et getStat (int index)
    Entite entiteTest;
    entiteTest.setStats({0, 1, 2});
    entiteTest.setStat(0, 9);
    int testedStat = entiteTest.getStat(0);
    BOOST_CHECK_EQUAL(testedStat, 9);
  }

  {
    // Test de setStats (std::vector<int> stats) et getStats ()
    Entite entiteTest;
    entiteTest.setStats({0, 1, 2});
    std::vector<int> testedStats = entiteTest.getStats();
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedStats[i], i);
    }
  }

  {
    // Test de setStatutSubi (int index, bool statutSubi) et getStatutSubi (int index)
    Entite entiteTest;
    entiteTest.setStatutsSubis({true, false});
    entiteTest.setStatutSubi(0, false);
    bool testedStatutSubi = entiteTest.getStatutSubi(0);
    BOOST_CHECK_EQUAL(testedStatutSubi, false);
  }

  {
    // Test de setStatutsSubis (std::vector<bool> statutsSubis) et getStatutsSubis ()
    Entite entiteTest;
    entiteTest.setStatutsSubis({true, false});
    std::vector<bool> testedStatutsSubis = entiteTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    BOOST_CHECK_EQUAL(testedStatutsSubis[1], false);
  }

  {
    // -----Test d'initialisation ()
    BOOST_CHECK(1);
  }

  {
    // Test de deplacement (int dx, int dy)
    Entite entiteTest;
    entiteTest.setPositionX(0);
    entiteTest.setPositionY(0);
    entiteTest.deplacement(9, -8);
    BOOST_CHECK_EQUAL(entiteTest.getPositionX(), 9);
    BOOST_CHECK_EQUAL(entiteTest.getPositionY(), -8);
  }

  {
    // -----Test de attaque (Entite cible) 
    BOOST_CHECK(1);
  }

  {
    // -----Test d'effectuerActionSupp (ActionSupp action) 
    BOOST_CHECK(1);
  }

  {
    // -----Test de degats (int degatsSubis, int statutsSubis) 
    BOOST_CHECK(1);
  }

  {
    // -----Test de mort () 
    BOOST_CHECK(1);
  }
}

BOOST_AUTO_TEST_CASE(TestStateEquipement)
{
  {
    // Test de setNom (std::string nom) et getNom ()
    Equipement equipementTest;
    equipementTest.setNom("nomTest");
    std::string testedNom = equipementTest.getNom();
    BOOST_CHECK_EQUAL(testedNom, "nomTest");
  }

  {
    // Test de setStatutInflige (Statut statutInflige) et getStatutInflige ()
    Equipement equipementTest;
    equipementTest.setStatutInflige(CONFUS);
    Statut testedStatutInflige = equipementTest.getStatutInflige();
    BOOST_CHECK_EQUAL(testedStatutInflige, CONFUS);
  }

  {
    // Test de setBonusStat (std::vector<int> bonusStat) et getBonusStat ()
    Equipement equipementTest;
    equipementTest.setBonusStat({0, 1, 2});
    std::vector<int> testedBonusStat = equipementTest.getBonusStat();
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedBonusStat[i], i);
    }
  }
}

BOOST_AUTO_TEST_CASE(TestStateHeros)
{
  {
    // Test de Heros (std::string nom, Classe classe)
    Heros herosTest("testNom", ARCHER);
    BOOST_CHECK_EQUAL(herosTest.getNom(), "testNom");
    BOOST_CHECK_EQUAL(herosTest.getClasse(), ARCHER);
  }

  {
    // Test de setClasse (Classe classe) et getClasse ()
    Heros herosTest;
    herosTest.setClasse(ARCHER);
    Classe testedClasse = herosTest.getClasse();
    BOOST_CHECK_EQUAL(testedClasse, ARCHER);
  }

  {
    // Test de obtenirEquipement (Equipement newEquipement)
    Heros herosTest;
    Equipement equipementTest1;
    equipementTest1.setNom("nomTest1");
    herosTest.setEquipement({equipementTest1});
    Equipement equipementTest2;
    equipementTest2.setNom("nomTest2");
    herosTest.obtenirEquipement(equipementTest2);
    BOOST_CHECK_EQUAL(herosTest.getEquipement()[1].getNom(), "nomTest2");
  }

  {
    // -----Test de lacherEquipement (Equipement oldEquipement)
    BOOST_CHECK(1);
  }

  {
    // Test d'obtenirActionSupp (ActionSupp newActionSupp) 
    Heros herosTest;
    ActionSupp actionSuppTest1;
    actionSuppTest1.setNom("nomTest1");
    herosTest.setAutresActions({actionSuppTest1});
    ActionSupp actionSuppTest2;
    actionSuppTest2.setNom("nomTest2");
    herosTest.obtenirActionSupp(actionSuppTest2);
    BOOST_CHECK_EQUAL(herosTest.getAutresActions()[1].getNom(), "nomTest2");
  }
}

BOOST_AUTO_TEST_CASE(TestStateState)
{
  {
    // Test de setNbTour (int nbTour) et getNbTour ()
    State stateTest;
    stateTest.setNbTour(9);
    int testedNbTour = stateTest.getNbTour();
    BOOST_CHECK_EQUAL(testedNbTour, 9);
  }

  {
    // Test de setDecor (Decor decors) et getDecor ()
    Decor decorTest;
    decorTest.setHauteur(9);
    State stateTest;
    stateTest.setDecor(decorTest);
    Decor testedDecor = stateTest.getDecor();
    BOOST_CHECK_EQUAL(testedDecor.getHauteur(), 9);
  }

  {
    // Test de setEntites (std::vector<Entite> entites) et getEntites ()
    Entite entiteTest1("nomTest1");
    Entite entiteTest2("nomTest2");
    State stateTest;
    stateTest.setEntites({entiteTest1, entiteTest2});
    std::vector<Entite> testedEntites = stateTest.getEntites();
    BOOST_CHECK_EQUAL(testedEntites[0].getNom(), "nomTest1");
    BOOST_CHECK_EQUAL(testedEntites[1].getNom(), "nomTest2");
  }

  {
    // -----Test de setOrdreTour (std::vector<Entite*> ordreTour) et getOrdreTour ()
    State stateTest;
    Entite entiteTest1;
    Entite entiteTest2;
    stateTest.setOrdreTour({&entiteTest1, &entiteTest2});
    std::vector<Entite*> testedOrdreTour = stateTest.getOrdreTour();
    BOOST_CHECK_EQUAL(testedOrdreTour[0], &entiteTest1);
  }
  
  {
    // Test de setDe (int de) et getDe ()
    State stateTest;
    stateTest.setDe(9);
    int testedDe = stateTest.getDe();
    BOOST_CHECK_EQUAL(testedDe, 9);
  }

  {
    // -----Test de nouveauTour ()
    BOOST_CHECK(1);
  }

  {
    // -----Test de joueurSuivant ()
    BOOST_CHECK(1);
  }
}
*/

/* vim: set sw=2 sts=2 et : */