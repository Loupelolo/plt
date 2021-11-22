#include "../../src/client/render/Couche.h"
#include "../../src/client/render/CoucheMenu.h"
#include "../../src/client/render/CoucheTerrain.h"
#include "../../src/client/render/Scene.h"

#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>

using namespace render;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestSFML)
{
  {
    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int> {});
  }
}

BOOST_AUTO_TEST_CASE(TestRenderCouche)
{
  {
    //Test du constructeur Couche(int posX, int posY, int hauteur, int largeur)
    Couche coucheTest(9, 8, 7, 6);
    BOOST_CHECK_EQUAL(coucheTest.getPosX(), 9);
    BOOST_CHECK_EQUAL(coucheTest.getPosY(), 8);
    BOOST_CHECK_EQUAL(coucheTest.getHauteur(), 7);
    BOOST_CHECK_EQUAL(coucheTest.getLargeur(), 6);
  }

  {
    //Test de setPos, getPosX et getPosY
    Couche coucheTest;
    coucheTest.setPos(9, 8);
    int testedPosX = coucheTest.getPosX();
    int testedPosY = coucheTest.getPosY();
    BOOST_CHECK_EQUAL(testedPosX, 9);
    BOOST_CHECK_EQUAL(testedPosY, 8);
  }

  {
    //Test de setDimensions, getHauteur et getLargeur
    Couche coucheTest;
    coucheTest.setDimensions(9, 8);
    int testedHauteur = coucheTest.getHauteur();
    int testedLargeur = coucheTest.getLargeur();
    BOOST_CHECK_EQUAL(testedHauteur, 9);
    BOOST_CHECK_EQUAL(testedLargeur, 8);
  }
}

BOOST_AUTO_TEST_CASE(TestRenderCoucheMenu)
{
  {
    //Test du constructeur CoucheMenu(int type, int posX, int posY, int hauteur, int largeur)
    CoucheMenu coucheMenuTest(10, 9, 8, 7, 6);
    BOOST_CHECK_EQUAL(coucheMenuTest.getType(), 10);
    BOOST_CHECK_EQUAL(coucheMenuTest.getPosX(), 9);
    BOOST_CHECK_EQUAL(coucheMenuTest.getPosY(), 8);
    BOOST_CHECK_EQUAL(coucheMenuTest.getHauteur(), 7);
    BOOST_CHECK_EQUAL(coucheMenuTest.getLargeur(), 6);
  }

  {
    //Test de setType et getType
    CoucheMenu coucheMenuTest;
    coucheMenuTest.setType(9);
    int testedType = coucheMenuTest.getType();
    BOOST_CHECK_EQUAL(testedType, 9);
  }
}

BOOST_AUTO_TEST_CASE(TestRenderCoucheTerrain)
{
  {
    //Test du constructeur CoucheTerrain (int x, int y)
    CoucheTerrain coucheTerrainTest(9, 8);
    BOOST_CHECK_EQUAL(coucheTerrainTest.getPosX(), 9);
    BOOST_CHECK_EQUAL(coucheTerrainTest.getPosY(), 8);
  }

  {
    //Test du constructeur CoucheTerrain (int x, int y, int h, int l, int tailleTuile)
    CoucheTerrain coucheTerrainTest(9, 8, 7, 6, 5);
    BOOST_CHECK_EQUAL(coucheTerrainTest.getPosX(), 9);
    BOOST_CHECK_EQUAL(coucheTerrainTest.getPosY(), 8);
    BOOST_CHECK_EQUAL(coucheTerrainTest.getHauteur(), 7);
    BOOST_CHECK_EQUAL(coucheTerrainTest.getLargeur(), 6);
    BOOST_CHECK_EQUAL(coucheTerrainTest.getTailleTuile(), 5);
  }

  {
    //Test de setTailleTuile et getTailleTuile
    CoucheTerrain coucheTerrainTest;
    coucheTerrainTest.setTailleTuile(9);
    int testedTailleTuile = coucheTerrainTest.getTailleTuile();
    BOOST_CHECK_EQUAL(testedTailleTuile, 9);
  }
}

BOOST_AUTO_TEST_CASE(TestRenderScene)
{
  {
    //Test de setJoueurID et getJoueurID
    Scene sceneTest;
    sceneTest.setJoueurID(9);
    int testedJoueurID = sceneTest.getJoueurID();
    BOOST_CHECK_EQUAL(testedJoueurID, 9);
  }

  {
    //Test de setActionSelectionnee et getActionSelectionnee
    Scene sceneTest;
    sceneTest.setActionSelectionnee(9);
    int testedActionSelectionnee = sceneTest.getActionSelectionnee();
    BOOST_CHECK_EQUAL(testedActionSelectionnee, 9);
  }

  {
    //Test de setSceneID et getSceneID
    Scene sceneTest;
    sceneTest.setSceneID(9);
    int testedSceneID = sceneTest.getSceneID();
    BOOST_CHECK_EQUAL(testedSceneID, 9);
  }

  {
    //Test de setState et getState
    State stateTest;
    stateTest.setNbTour(9);
    Scene sceneTest;
    sceneTest.setState(stateTest);
    State testedState = sceneTest.getState();
    BOOST_CHECK_EQUAL(testedState.getNbTour(), 9);
  }
}

/*

----- PAS TESTÉ ----- 
getters et setters d'attributs de types provenant de la librairie SFML
méthodes autres que les getters et setters
setCasesAccessibles et getCasesAccessibles de CoucheTerrain
---------------------

*/

/* vim: set sw=2 sts=2 et : */
