// #include "../../src/client/render/Couche.h"
// #include "../../src/client/render/CoucheMenu.h"
// #include "../../src/client/render/CoucheTerrain.h"
// #include "../../src/client/render/Scene.h"

#include <boost/test/unit_test.hpp>

//#include <SFML/Graphics.hpp>


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}
<<<<<<< HEAD

=======
/*
BOOST_AUTO_TEST_CASE(TestSFML)
{
  {
    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int> {});
  }
}
>>>>>>> master




<<<<<<< HEAD




=======
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
}*/
>>>>>>> master

/*

----- PAS TESTÉ ----- 
getters et setters d'attributs de types provenant de la librairie SFML
méthodes autres que les getters et setters
setCasesAccessibles et getCasesAccessibles de CoucheTerrain
---------------------

*/

/* vim: set sw=2 sts=2 et : */
