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

BOOST_AUTO_TEST_CASE(TestStateActionSuppOff)
{
  {
    // Test d'ActionSuppOff ()
    ActionSuppOff actionSuppOfftest;
    BOOST_CHECK_EQUAL(actionSuppOfftest.getNom(), "Action");
    BOOST_CHECK_EQUAL(actionSuppOfftest.getStat(), 0);
    BOOST_CHECK_EQUAL(actionSuppOfftest.getStatut(), SNONE);
  }

  {
    // Test d'ActionSuppOff (std::string nom, int stat, Statut statut)
    ActionSuppOff actionSuppOfftest("nomTest", 9, CONFUS);
    BOOST_CHECK_EQUAL(actionSuppOfftest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(actionSuppOfftest.getStat(), 9);
    BOOST_CHECK_EQUAL(actionSuppOfftest.getStatut(), CONFUS);
  }

  {
    // Test d'ActionSuppOff (const ActionSuppOff &p)
    ActionSuppOff actionSuppOfftest1("nomTest", 9, CONFUS);
    ActionSuppOff actionSuppOfftest2(actionSuppOfftest1);
    BOOST_CHECK_EQUAL(actionSuppOfftest2.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(actionSuppOfftest2.getStat(), 9);
    BOOST_CHECK_EQUAL(actionSuppOfftest2.getStatut(), CONFUS);
  }

  {
    // Test de setStatut (Statut statut) et getStatut ()
    ActionSuppOff actionSuppOffTest;
    actionSuppOffTest.setStatut(CONFUS);
    Statut testedStatut = actionSuppOffTest.getStatut();
    BOOST_CHECK_EQUAL(testedStatut, CONFUS);
  }

  {
    // Test d'effectuerAction (Entite* cible)
    ActionSuppOff actionSuppOffTest("nomTest", 5, SNONE);
    Entite entiteTest;
    entiteTest.setPV(10);
    actionSuppOffTest.effectuerAction(&entiteTest);
    BOOST_CHECK_EQUAL(entiteTest.getPV(), 5);
  }
}

BOOST_AUTO_TEST_CASE(TestStateDecor)
{
  {
    // Test de Decor (std::vector<TypeTerrain> map)
    std::vector<TypeTerrain> mapTest{TNON, SOL, MUR};
    Decor decorTest(mapTest);
    std::vector<TypeTerrain> testedMap = decorTest.getMap();
    BOOST_CHECK_EQUAL(testedMap[0], TNON);
    BOOST_CHECK_EQUAL(testedMap[1], SOL);
    BOOST_CHECK_EQUAL(testedMap[2], MUR);
  }

  {
    // Test de Decor (int largeur, int hauteur, std::vector<TypeTerrain> map)
    std::vector<TypeTerrain> mapTest{TNON, SOL, MUR};
    Decor decorTest(9, 8, mapTest);
    std::vector<TypeTerrain> testedMap = decorTest.getMap();
    BOOST_CHECK_EQUAL(decorTest.getLargeur(), 9);
    BOOST_CHECK_EQUAL(decorTest.getHauteur(), 8);
    BOOST_CHECK_EQUAL(testedMap[0], TNON);
    BOOST_CHECK_EQUAL(testedMap[1], SOL);
    BOOST_CHECK_EQUAL(testedMap[2], MUR);
  }

  {
    // Test de Decor (int largeur, int hauteur, std::vector<TypeTerrain> map, std::vector<int> meteo, std::vector<int> lumiere)
    std::vector<TypeTerrain> mapTest{TNON, SOL, MUR};
    std::vector<int> meteoTest = {0, 1, 2};
    std::vector<int> lumiereTest = {0, 1, 2};
    Decor decorTest(9, 8, mapTest, meteoTest, lumiereTest);
    std::vector<TypeTerrain> testedMap = decorTest.getMap();
    std::vector<int> testedMeteo = decorTest.getMeteo();
    std::vector<int> testedLumiere = decorTest.getLumiere();
    BOOST_CHECK_EQUAL(decorTest.getLargeur(), 9);
    BOOST_CHECK_EQUAL(decorTest.getHauteur(), 8);
    BOOST_CHECK_EQUAL(testedMap[0], TNON);
    BOOST_CHECK_EQUAL(testedMap[1], SOL);
    BOOST_CHECK_EQUAL(testedMap[2], MUR);
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedMeteo[i], i);
      BOOST_CHECK_EQUAL(testedLumiere[i], i);
    }
  }

  {
    // Test de Decor (const Decor &p)
    std::vector<TypeTerrain> mapTest{TNON, SOL, MUR};
    std::vector<int> meteoTest = {0, 1, 2};
    std::vector<int> lumiereTest = {0, 1, 2};
    Decor decorTest1(9, 8, mapTest, meteoTest, lumiereTest);
    Decor decorTest2(decorTest1);
    std::vector<TypeTerrain> testedMap = decorTest2.getMap();
    std::vector<int> testedMeteo = decorTest2.getMeteo();
    std::vector<int> testedLumiere = decorTest2.getLumiere();
    BOOST_CHECK_EQUAL(decorTest2.getLargeur(), 9);
    BOOST_CHECK_EQUAL(decorTest2.getHauteur(), 8);
    BOOST_CHECK_EQUAL(testedMap[0], TNON);
    BOOST_CHECK_EQUAL(testedMap[1], SOL);
    BOOST_CHECK_EQUAL(testedMap[2], MUR);
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedMeteo[i], i);
      BOOST_CHECK_EQUAL(testedLumiere[i], i);
    }
  }

  {
    // Test de setLargeur(int largeur) et getLargeur ()
    Decor decorTest;
    decorTest.setLargeur(9);
    int testedLargeur = decorTest.getLargeur();
    BOOST_CHECK_EQUAL(testedLargeur, 9);
  }

  {
    // Test de setHauteur(int hauteur) et getHauteur ()
    Decor decorTest;
    decorTest.setHauteur(9);
    int testedHauteur = decorTest.getHauteur();
    BOOST_CHECK_EQUAL(testedHauteur, 9);
  }

  {
    // Test de setMap(std::vector<TypeTerrain> map) et getMap ()
    Decor decorTest;
    decorTest.setMap({TNON, SOL, MUR});
    std::vector<TypeTerrain> testedMap = decorTest.getMap();
    BOOST_CHECK_EQUAL(testedMap[0], TNON);
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

  /*{
    // Test d'action ()
  }*/
}

BOOST_AUTO_TEST_CASE(TestStateEnnemi)
{
  {
    // Test d'Ennemi ()
    Ennemi ennemiTest;
    BOOST_CHECK_EQUAL(ennemiTest.getNom(), "John Doe");
    BOOST_CHECK_EQUAL(ennemiTest.getType(), 0);
    BOOST_CHECK_EQUAL(ennemiTest.getNiveau(), 1);
    BOOST_CHECK_EQUAL(ennemiTest.getPositionX(), 0);
    BOOST_CHECK_EQUAL(ennemiTest.getPositionY(), 0);
    BOOST_CHECK_EQUAL(ennemiTest.getPV(), 100);
    BOOST_CHECK_EQUAL(ennemiTest.getPM(), 100);
    BOOST_CHECK(ennemiTest.getEquipement().empty());
    BOOST_CHECK(ennemiTest.getAutresActions().empty());
    std::vector<int> testedStats = ennemiTest.getStats();
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], 0);
    }
    std::vector<bool> testedStatutsSubis = ennemiTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
    BOOST_CHECK_EQUAL(ennemiTest.getRace(), ORC);
    BOOST_CHECK_EQUAL(ennemiTest.getActif(), false);
  }

  {
    // Test d'Ennemi (std::string nom, Race race)
    Ennemi ennemiTest("nomTest", SERPENT);
    BOOST_CHECK_EQUAL(ennemiTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(ennemiTest.getType(), 0);
    BOOST_CHECK_EQUAL(ennemiTest.getNiveau(), 1);
    BOOST_CHECK_EQUAL(ennemiTest.getPositionX(), 0);
    BOOST_CHECK_EQUAL(ennemiTest.getPositionY(), 0);
    BOOST_CHECK_EQUAL(ennemiTest.getPV(), 100);
    BOOST_CHECK_EQUAL(ennemiTest.getPM(), 100);
    BOOST_CHECK(ennemiTest.getEquipement().empty());
    BOOST_CHECK(ennemiTest.getAutresActions().empty());
    std::vector<int> testedStats = ennemiTest.getStats();
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], 0);
    }
    std::vector<bool> testedStatutsSubis = ennemiTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
    BOOST_CHECK_EQUAL(ennemiTest.getRace(), SERPENT);
    BOOST_CHECK_EQUAL(ennemiTest.getActif(), false);
  }

  {
    // Test d'Ennemi (std::string nom, Race race, int niveau, int positionX, int positionY, std::vector<Equipement> equipement, std::vector<ActionSupp> autresActions)
    Equipement equipementTest1;
    std::vector<Equipement> equipementTest = {equipementTest1};
    ActionSupp autresActionsTest1;
    std::vector<ActionSupp> autresActionsTest = {autresActionsTest1};
    Ennemi ennemiTest("nomTest", SERPENT, 9, 8, 7, equipementTest, autresActionsTest);
    BOOST_CHECK_EQUAL(ennemiTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(ennemiTest.getType(), 0);
    BOOST_CHECK_EQUAL(ennemiTest.getNiveau(), 9);
    BOOST_CHECK_EQUAL(ennemiTest.getPositionX(), 8);
    BOOST_CHECK_EQUAL(ennemiTest.getPositionY(), 7);
    BOOST_CHECK_EQUAL(ennemiTest.getPV(), 100);
    BOOST_CHECK_EQUAL(ennemiTest.getPM(), 100);
    BOOST_CHECK_EQUAL(ennemiTest.getEquipement()[0].getNom(), "no name");
    BOOST_CHECK_EQUAL(ennemiTest.getAutresActions()[0].getNom(), "Action");
    std::vector<int> testedStats = ennemiTest.getStats();
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], 0);
    }
    std::vector<bool> testedStatutsSubis = ennemiTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
    BOOST_CHECK_EQUAL(ennemiTest.getRace(), SERPENT);
    BOOST_CHECK_EQUAL(ennemiTest.getActif(), false);
  }

  {
    // Test d'Ennemi (const Ennemi &p)
    Equipement equipementTest1;
    std::vector<Equipement> equipementTest = {equipementTest1};
    ActionSupp autresActionsTest1;
    std::vector<ActionSupp> autresActionsTest = {autresActionsTest1};
    Ennemi ennemiTest1("nomTest", SERPENT, 9, 8, 7, equipementTest, autresActionsTest);
    Ennemi ennemiTest(ennemiTest1);
    BOOST_CHECK_EQUAL(ennemiTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(ennemiTest.getType(), 0);
    BOOST_CHECK_EQUAL(ennemiTest.getNiveau(), 9);
    BOOST_CHECK_EQUAL(ennemiTest.getPositionX(), 8);
    BOOST_CHECK_EQUAL(ennemiTest.getPositionY(), 7);
    BOOST_CHECK_EQUAL(ennemiTest.getPV(), 100);
    BOOST_CHECK_EQUAL(ennemiTest.getPM(), 100);
    BOOST_CHECK_EQUAL(ennemiTest.getEquipement()[0].getNom(), "no name");
    BOOST_CHECK_EQUAL(ennemiTest.getAutresActions()[0].getNom(), "Action");
    std::vector<int> testedStats = ennemiTest.getStats();
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], 0);
    }
    std::vector<bool> testedStatutsSubis = ennemiTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
    BOOST_CHECK_EQUAL(ennemiTest.getRace(), SERPENT);
    BOOST_CHECK_EQUAL(ennemiTest.getActif(), false);
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

  /*{
    // Test d'activer ()
  }*/

  /*{
    // Test d'initialisation ()
  }*/
}

BOOST_AUTO_TEST_CASE(TestStateEntite)
{
  /*{
    // Test d'Entite ()
  }*/

  {
    //  Test d'Entite (std::string nom)
    Entite entiteTest("nomTest");
    BOOST_CHECK_EQUAL(entiteTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(entiteTest.getType(), 0);
    BOOST_CHECK_EQUAL(entiteTest.getNiveau(), 1);
    BOOST_CHECK_EQUAL(entiteTest.getPositionX(), 0);
    BOOST_CHECK_EQUAL(entiteTest.getPositionY(), 0);
    BOOST_CHECK_EQUAL(entiteTest.getPV(), 100);
    BOOST_CHECK_EQUAL(entiteTest.getPM(), 100);
    BOOST_CHECK(entiteTest.getEquipement().empty());
    BOOST_CHECK(entiteTest.getAutresActions().empty());
    std::vector<int> testedStats = entiteTest.getStats();
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], 0);
    }
    std::vector<bool> testedStatutsSubis = entiteTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
  }

  {
    //  Test d'Entite (const Entite &p)
    Entite entiteTest1("nomTest");
    Entite entiteTest(entiteTest1);
    BOOST_CHECK_EQUAL(entiteTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(entiteTest.getType(), 0);
    BOOST_CHECK_EQUAL(entiteTest.getNiveau(), 1);
    BOOST_CHECK_EQUAL(entiteTest.getPositionX(), 0);
    BOOST_CHECK_EQUAL(entiteTest.getPositionY(), 0);
    BOOST_CHECK_EQUAL(entiteTest.getPV(), 100);
    BOOST_CHECK_EQUAL(entiteTest.getPM(), 100);
    BOOST_CHECK(entiteTest.getEquipement().empty());
    BOOST_CHECK(entiteTest.getAutresActions().empty());
    std::vector<int> testedStats = entiteTest.getStats();
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], 0);
    }
    std::vector<bool> testedStatutsSubis = entiteTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
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
    // Test d'initialisation ()
    Entite entiteTest("nomTest");
    entiteTest.initialisation();
    BOOST_CHECK_EQUAL(entiteTest.getStat(0), 10);
  }

  {
    // Test de deplacement (int dx, int dy)
    Entite entiteTest("nomTest");
    entiteTest.setPositionX(1);
    entiteTest.setPositionY(0);
    entiteTest.deplacement(9, -8);
    BOOST_CHECK_EQUAL(entiteTest.getPositionX(), 10);
    BOOST_CHECK_EQUAL(entiteTest.getPositionY(), -8);
  }

  {
    // Test d'attaque (Entite* cible) 
    Entite entiteOff("nomOff");
    Entite entiteDef("nomDef");
    entiteOff.initialisation();
    entiteOff.attaque(&entiteDef);
    BOOST_CHECK_EQUAL(entiteDef.getPV(), 90);
  }

  {
    // Test d'effectuerActionSupp (ActionSupp* action, Entite* cible)
    Entite entiteOff("nomOff");
    Entite entiteDef("nomDef");
    ActionSuppOff actionSuppOffTest("nomTest", 50, SNONE);
    entiteOff.effectuerActionSupp(&actionSuppOffTest, &entiteDef);
    BOOST_CHECK_EQUAL(entiteDef.getPV(), 50);
    // Bon prototype? Le paramètre ActionSupp* action rend inutile m_equipement des entités
  }

  {
    // Test de degats (int degatsSubis, int statutsSubis)
    Entite entiteTest("nomTest");
    entiteTest.degats(50, 1);
    BOOST_CHECK_EQUAL(entiteTest.getPV(), 50);
    BOOST_CHECK_EQUAL(entiteTest.getStatutSubi(1), true);
  }

  {
    // Test de soin (int pvRecup, bool soigneStatuts)
    Entite entiteTest("nomTest");
    entiteTest.setStat(PVMAX, 100);
    entiteTest.setPV(50);
    entiteTest.setStatutSubi(1, true);
    entiteTest.soin(25, false); // Test du regain de PV
    BOOST_CHECK_EQUAL(entiteTest.getPV(), 75);
    std::vector<bool> testedStatutsSubis = entiteTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    BOOST_CHECK_EQUAL(testedStatutsSubis[1], true);
    for (unsigned int i = 2; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
    entiteTest.soin(0, true); // Test du soin de statuts
    BOOST_CHECK_EQUAL(entiteTest.getPV(), 75);
    testedStatutsSubis = entiteTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
  }

  /*{
    // Test de mort () 
  }*/
}

BOOST_AUTO_TEST_CASE(TestStateEquipement)
{
  {
    // Test d'Equipement ()
    Equipement equipementTest;
    BOOST_CHECK_EQUAL(equipementTest.getNom(), "no name");
    std::vector<int> testedBonusStat = equipementTest.getBonusStat();
    for (unsigned int i = 0; i < testedBonusStat.size(); i++) {
      BOOST_CHECK_EQUAL(testedBonusStat[i], 0);
    }
    BOOST_CHECK_EQUAL(equipementTest.getStatutInflige(), SNONE);
  }

  {
    // Test d'Equipement (std::string nom)
    Equipement equipementTest("nomTest");
    BOOST_CHECK_EQUAL(equipementTest.getNom(), "nomTest");
    std::vector<int> testedBonusStat = equipementTest.getBonusStat();
    for (unsigned int i = 0; i < testedBonusStat.size(); i++) {
      BOOST_CHECK_EQUAL(testedBonusStat[i], 0);
    }
    BOOST_CHECK_EQUAL(equipementTest.getStatutInflige(), SNONE);
  }

  {
    // Test d'Equipement (std::string nom, Statut statutInflige, std::vector<int> bonusStat)
    std::vector<int> bonusStatTest = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Equipement equipementTest("nomTest", CONFUS, bonusStatTest);
    BOOST_CHECK_EQUAL(equipementTest.getNom(), "nomTest");
    std::vector<int> testedBonusStat = equipementTest.getBonusStat();
    for (unsigned int i = 0; i < testedBonusStat.size(); i++) {
      BOOST_CHECK_EQUAL(testedBonusStat[i], i);
    }
    BOOST_CHECK_EQUAL(equipementTest.getStatutInflige(), CONFUS);
  }

  {
    // Test d'Equipement (const Equipement &p)
    std::vector<int> bonusStatTest = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Equipement equipementTest1("nomTest", CONFUS, bonusStatTest);
    Equipement equipementTest(equipementTest1);
    BOOST_CHECK_EQUAL(equipementTest.getNom(), "nomTest");
    std::vector<int> testedBonusStat = equipementTest.getBonusStat();
    for (unsigned int i = 0; i < testedBonusStat.size(); i++) {
      BOOST_CHECK_EQUAL(testedBonusStat[i], i);
    }
    BOOST_CHECK_EQUAL(equipementTest.getStatutInflige(), CONFUS);
  }

  {
    // Test d'operator==(Equipement equip)
    Equipement equipementTest1("nomTest");
    Equipement equipementTest2("nomTest");
    Equipement equipementTest3("nomTest3");
    BOOST_CHECK(equipementTest1 == equipementTest2);
    BOOST_CHECK(!(equipementTest1 == equipementTest3));
  }

  {
    // Test d'operator!=(Equipement equip)
    Equipement equipementTest1("nomTest");
    Equipement equipementTest2("nomTest");
    Equipement equipementTest3("nomTest3");
    BOOST_CHECK(equipementTest1 != equipementTest3);
    BOOST_CHECK(!(equipementTest1 != equipementTest2));
  }
  
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
    // Test de Heros ()
    Heros herosTest;
    BOOST_CHECK_EQUAL(herosTest.getNom(), "Jane Doe");
    BOOST_CHECK_EQUAL(herosTest.getClasse(), ARCHER);
    BOOST_CHECK_EQUAL(herosTest.getType(), 0);
    BOOST_CHECK_EQUAL(herosTest.getNiveau(), 1);
    BOOST_CHECK_EQUAL(herosTest.getPositionX(), 0);
    BOOST_CHECK_EQUAL(herosTest.getPositionY(), 0);
    BOOST_CHECK_EQUAL(herosTest.getPV(), 100);
    BOOST_CHECK_EQUAL(herosTest.getPM(), 100);
    BOOST_CHECK(herosTest.getEquipement().empty());
    BOOST_CHECK(herosTest.getAutresActions().empty());
    std::vector<int> testedStats = herosTest.getStats();
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], 0);
    }
    std::vector<bool> testedStatutsSubis = herosTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
  }

  {
    // Test de Heros (std::string nom, Classe classe)
    Heros herosTest("nomTest", MAGE);
    BOOST_CHECK_EQUAL(herosTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(herosTest.getClasse(), MAGE);
    BOOST_CHECK_EQUAL(herosTest.getType(), 0);
    BOOST_CHECK_EQUAL(herosTest.getNiveau(), 1);
    BOOST_CHECK_EQUAL(herosTest.getPositionX(), 0);
    BOOST_CHECK_EQUAL(herosTest.getPositionY(), 0);
    BOOST_CHECK_EQUAL(herosTest.getPV(), 90);
    BOOST_CHECK_EQUAL(herosTest.getPM(), 50);
    BOOST_CHECK(herosTest.getEquipement().empty());
    BOOST_CHECK(herosTest.getAutresActions().empty());
    std::vector<int> testedStats = herosTest.getStats();
    std::vector<int> statsMage = {70, 30, 10, 10, 90, 50, 2, 8, 5};
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], statsMage[i]);
    }
    std::vector<bool> testedStatutsSubis = herosTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
  }

  {
    // Test de Heros (const Heros &p)
    Heros herosTest1("nomTest", MAGE);
    Heros herosTest(herosTest1);
    BOOST_CHECK_EQUAL(herosTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(herosTest.getClasse(), MAGE);
    BOOST_CHECK_EQUAL(herosTest.getType(), 0);
    BOOST_CHECK_EQUAL(herosTest.getNiveau(), 1);
    BOOST_CHECK_EQUAL(herosTest.getPositionX(), 0);
    BOOST_CHECK_EQUAL(herosTest.getPositionY(), 0);
    BOOST_CHECK_EQUAL(herosTest.getPV(), 90);
    BOOST_CHECK_EQUAL(herosTest.getPM(), 50);
    BOOST_CHECK(herosTest.getEquipement().empty());
    BOOST_CHECK(herosTest.getAutresActions().empty());
    std::vector<int> testedStats = herosTest.getStats();
    std::vector<int> statsMage = {70, 30, 10, 10, 90, 50, 2, 8, 5};
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], statsMage[i]);
    }
    std::vector<bool> testedStatutsSubis = herosTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    for (unsigned int i = 1; i < testedStatutsSubis.size(); i++) {
      BOOST_CHECK_EQUAL(testedStatutsSubis[i], false);
    }
  }

  {
    // Test de setClasse (Classe classe) et getClasse ()
    Heros herosTest;
    herosTest.setClasse(ARCHER);
    Classe testedClasse = herosTest.getClasse();
    BOOST_CHECK_EQUAL(testedClasse, ARCHER);
    
  }

  {
    // Test d'initialisation ()
    Heros herosTest;
    herosTest.initialisation();
    std::vector<int> statsArcher = {40, 40, 30, 25, 60, 30, 10, 30, 8};
    std::vector<int> testedStats = herosTest.getStats();
    for (unsigned int i = 0; i < testedStats.size(); i++) {
      BOOST_CHECK_EQUAL(testedStats[i], statsArcher[i]);
    }
    BOOST_CHECK_EQUAL(herosTest.getPV(), statsArcher[PVMAX]);
    BOOST_CHECK_EQUAL(herosTest.getPM(), statsArcher[PMMAX]);
  }

  {
    // Test d'obtenirEquipement (Equipement newEquipement)
    Heros herosTest;
    Equipement equipementTest1("nomTest1");
    herosTest.setEquipement({equipementTest1});
    Equipement equipementTest2("nomTest2");
    herosTest.obtenirEquipement(equipementTest2);
    BOOST_CHECK(herosTest.getEquipement()[1] == equipementTest2);
  }

  {
    // Test de lacherEquipement (Equipement oldEquipement)
    Heros herosTest;
    Equipement equipementTest("nomTest");
    herosTest.setEquipement({equipementTest});
    herosTest.lacherEquipement(equipementTest);
    BOOST_CHECK(herosTest.getEquipement().empty());
  }
  {
    // Test d'obtenirActionSupp (ActionSupp newActionSupp) 
    Heros herosTest;
    ActionSupp actionSuppTest1("nomTest1");
    herosTest.setAutresActions({actionSuppTest1});
    ActionSupp actionSuppTest2("nomTest2");
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

  /*{
    // Test de setEntites (std::vector<Entite> entites) et getEntites ()
    Entite entiteTest1("nomTest1");
    Entite entiteTest2("nomTest2");
    State stateTest;
    stateTest.setEntites({entiteTest1, entiteTest2});
    std::vector<Entite> testedEntites = stateTest.getEntites();
    BOOST_CHECK_EQUAL(testedEntites[0].getNom(), "nomTest1");
    BOOST_CHECK_EQUAL(testedEntites[1].getNom(), "nomTest2");
  }*/

  {
    // Test de setOrdreTour (std::vector<Entite*> ordreTour) et getOrdreTour ()
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

  /*{
    // Test de nouveauTour ()
  }*/

  /*{
    // Test de joueurSuivant ()
  }*/

  /*{
    // Test d'actualiserEntite ()
  }*/
}

/* vim: set sw=2 sts=2 et : */