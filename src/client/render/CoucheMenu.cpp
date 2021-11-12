#include "CoucheMenu.h"

namespace render {

CoucheMenu::CoucheMenu(){

}

CoucheMenu::~CoucheMenu(){

}

bool CoucheMenu::load(){

    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(3 * 4);

    sf::Vertex* triangle = &m_vertices[0];
    // on définit la position des sommets du triangle
    triangle[0].position = sf::Vector2f(10, 10);
    triangle[1].position = sf::Vector2f(100, 10);
    triangle[2].position = sf::Vector2f(100, 100);

    // on définit la couleur des sommets du triangle
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

    return true;
}

}