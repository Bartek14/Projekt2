#ifndef BOX_H
#define BOX_H
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>

class MyBox : public b2World
{

public:
	MyBox();
	b2BodyDef bodyDef;
	b2Body* body;
	const int countVert = 4;
	b2Vec2 vertex[4];
	b2PolygonShape polygon;
	b2FixtureDef fixtureDef;

	
	sf::ConvexShape Convex;
};
#endif
