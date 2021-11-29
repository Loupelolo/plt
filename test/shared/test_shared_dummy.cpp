#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/ActionSupp.h"
#include "../../src/shared/state/ActionSuppDef.h"
#include "../../src/shared/state/ActionSuppOff.h"
#include "../../src/shared/state/Decor.h"
#include "../../src/shared/state/Ennemi.h"
#include "../../src/shared/state/Entite.h"
#include "../../src/shared/state/Equipement.h"
#include "../../src/shared/state/Heros.h"
#include "../../src/shared/state/State.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}
/*
BOOST_AUTO_TEST_CASE(TestStateActionSupp)
{
  {
    //Test du constructeur actionSUppTest(std::string nom)
    ActionSupp actionSuppTest("testName");
    BOOST_CHECK_EQUAL(actionSuppTest.getNom(), "testName");
  }

  {
    //Test de setNom et getNom
    ActionSupp actionSuppTest("testName");
    actionSuppTest.setNom("testName2");
    std::string testedNom = actionSuppTest.getNom();
    BOOST_CHECK_EQUAL(testedNom, "testName2");
  }

  {
    //Test de setStats et getStats
    ActionSupp actionSuppTest;
    actionSuppTest.setStats({0, 1, 2});
    std::vector<int> testedStats = actionSuppTest.getStats();
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedStats[i], i);
    }
  }
}

BOOST_AUTO_TEST_CASE(TestStateActionSuppDef)
{
  
}

BOOST_AUTO_TEST_CASE(TestStateActionSuppOff)
{
  {
    //Test de setStatuts et getStatuts
    ActionSuppOff actionSuppOffTest;
    actionSuppOffTest.setStatuts({true, false});
    std::vector<bool> testedStatuts = actionSuppOffTest.getStatuts();
    BOOST_CHECK_EQUAL(testedStatuts[0], true);
    BOOST_CHECK_EQUAL(testedStatuts[1], false);
  }
}

BOOST_AUTO_TEST_CASE(TestStateDecor)
{
  /*{
    //Test du constructeur Decor(std::vector<int> map)
    std::vector<TypeTerrain> mapTest{TNON, SOL, MUR};
    Decor decorTest(mapTest);
    std::vector<TypeTerrain> testedMap = decorTest.getMap();
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedMap[i], i);
    }
  }

  {
    //Test de setHauteur et getHauteur
    Decor decorTest;
    decorTest.setHauteur(9);
    int testedHauteur = decorTest.getHauteur();
    BOOST_CHECK_EQUAL(testedHauteur, 9);
  }

  {
    //Test de setLargeur et getLargeur
    Decor decorTest;
    decorTest.setLargeur(9);
    int testedLargeur = decorTest.getLargeur();
    BOOST_CHECK_EQUAL(testedLargeur, 9);
  }

  {
    //Test de setMeteo et getMeteo
    Decor decorTest;
    decorTest.setMeteo({0, 1, 2});
    std::vector<int> testedMeteo = decorTest.getMeteo();
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedMeteo[i], i);
    }
  }

  {
    //Test de setLumiere et getLumiere
    Decor decorTest;
    decorTest.setLumiere({0, 1, 2});
    std::vector<int> testedLumiere = decorTest.getLumiere();
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedLumiere[i], i);
    }
  }
}

BOOST_AUTO_TEST_CASE(TestStateEnnemi)
{
  {
    //Test du constructeur Ennemi (std::string nom, std::string race)
    Ennemi ennemiTest("nomTest", "raceTest");
    BOOST_CHECK_EQUAL(ennemiTest.getNom(), "nomTest");
    BOOST_CHECK_EQUAL(ennemiTest.getRace(), "raceTest");
  }

  {
    //Test de setRace et getRace
    Ennemi ennemiTest;
    ennemiTest.setRace("raceTest");
    std::string testedRace = ennemiTest.getRace();
    BOOST_CHECK_EQUAL(testedRace, "raceTest");
  }

  {
    //Test de setActif et getActif
    Ennemi ennemiTest;
    ennemiTest.setActif(false);
    bool testedActif = ennemiTest.getActif();
    BOOST_CHECK_EQUAL(testedActif, false);
  }
}

BOOST_AUTO_TEST_CASE(TestStateEntite)
{
  {
    // Test du constructeur Entite (std::string nom)
    Entite entiteTest("nomTest");
    BOOST_CHECK_EQUAL(entiteTest.getNom(), "nomTest");
  }

  {
    //Test de setNom et getNom
    Entite entiteTest;
    entiteTest.setNom("nomTest");
    std::string testedNom = entiteTest.getNom();
    BOOST_CHECK_EQUAL(testedNom, "nomTest");
  }

  {
    //Test de setType et getType
    Entite entiteTest;
    entiteTest.setType(9);
    int testedType = entiteTest.getType();
    BOOST_CHECK_EQUAL(testedType, 9);
  }

  {
    //Test de setNiveau et getNiveau
    Entite entiteTest;
    entiteTest.setNiveau(9);
    int testedNiveau = entiteTest.getNiveau();
    BOOST_CHECK_EQUAL(testedNiveau, 9);
  }

  {
    //Test de setPositionX et getPositionX
    Entite entiteTest;
    entiteTest.setPositionX(9);
    int testedPositionX = entiteTest.getPositionX();
    BOOST_CHECK_EQUAL(testedPositionX, 9);
  }

  {
    //Test de setPositionY et getPositionY
    Entite entiteTest;
    entiteTest.setPositionY(9);
    int testedPositionY = entiteTest.getPositionY();
    BOOST_CHECK_EQUAL(testedPositionY, 9);
  }

  {
    //Test de setPV et getPV
    Entite entiteTest;
    entiteTest.setPV(9);
    int testedPV = entiteTest.getPV();
    BOOST_CHECK_EQUAL(testedPV, 9);
  }

  {
    //Test de setPM et getPM
    Entite entiteTest;
    entiteTest.setPM(9);
    int testedPM = entiteTest.getPM();
    BOOST_CHECK_EQUAL(testedPM, 9);
  }

  {
    //Test de setEquipement et getEquipement
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
    //Test de setAutresActions et getAutresActions
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
    //Test de setStats et getStats
    Entite entiteTest;
    entiteTest.setStats({0, 1, 2});
    std::vector<int> testedStats = entiteTest.getStats();
    for (unsigned int i = 0; i < 3; i++) 
    {
      BOOST_CHECK_EQUAL(testedStats[i], i);
    }
  }

  {
    //Test de setStatutsSubis et getStatutsSubis
    Entite entiteTest;
    entiteTest.setStatutsSubis({true, false});
    std::vector<bool> testedStatutsSubis = entiteTest.getStatutsSubis();
    BOOST_CHECK_EQUAL(testedStatutsSubis[0], true);
    BOOST_CHECK_EQUAL(testedStatutsSubis[1], false);
  }
}

BOOST_AUTO_TEST_CASE(TestStateEquipement)
{
  {
    //Test de setNom et getNom
    Equipement equipementTest;
    equipementTest.setNom("testName");
    std::string testedNom = equipementTest.getNom();
    BOOST_CHECK_EQUAL(testedNom, "testName");
  }
*/
  /*
    //Test de setStatutInflige et getStatutInflige
    Equipement equipementTest;
    equipementTest.setStatutInflige(CONFUS);
    int testedStatutInflige = equipementTest.getStatutInflige();
    BOOST_CHECK_EQUAL(testedStatutInflige, 9);
  }*/
/*
  {
    //Test de setBonusStat et getBonusStat
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
  /*{
    //Test du constructeur Heros (std::string nom, std::string classe)
    Heros herosTest("testNom", MAGE);
    BOOST_CHECK_EQUAL(herosTest.getNom(), "testNom");
    BOOST_CHECK_EQUAL(herosTest.getClasse(), MAGE);
  }

  /*{
    //Test de setClasse et getClasse
    Heros herosTest;
    herosTest.setClasse(MAGE);
    Classe testedClasse = herosTest.getClasse();
    BOOST_CHECK_EQUAL(testedClasse, MAGE);
  }
}

BOOST_AUTO_TEST_CASE(TestStateState)
{
  {
    //Test de setNbTour et getNbTour
    State stateTest;
    stateTest.setNbTour(9);
    int testedNbTour = stateTest.getNbTour();
    BOOST_CHECK_EQUAL(testedNbTour, 9);
  }
  
  {
    //Test de setDecor et getDecor
    Decor decorTest;
    decorTest.setHauteur(9);
    State stateTest;
    stateTest.setDecor(decorTest);
    Decor testedDecor = stateTest.getDecor();
    BOOST_CHECK_EQUAL(testedDecor.getHauteur(), 9);
  }

  {
    //Test de setEntites et getEntites
    Entite entiteTest1("nomTest1");
    Entite entiteTest2("nomTest2");
    State stateTest;
    stateTest.setEntites({entiteTest1, entiteTest2});
    std::vector<Entite> testedEntites = stateTest.getEntites();
    BOOST_CHECK_EQUAL(testedEntites[0].getNom(), "nomTest1");
    BOOST_CHECK_EQUAL(testedEntites[1].getNom(), "nomTest2");
  }
  
  {
    //Test de setDe et getDe
    State stateTest;
    stateTest.setDe(9);
    int testedDe = stateTest.getDe();
    BOOST_CHECK_EQUAL(testedDe, 9);
  }
}
*/

/*

----- PAS TESTÉ ----- 
getStat et setStat de Entite
getOrdreTour et setOrdreTour de State
---------------------

*/

/* vim: set sw=2 sts=2 et : */
