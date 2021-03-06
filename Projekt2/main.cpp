
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include "Box.h"
#include <stdio.h>


int main(int argc, char** argv)
{
	struct coOrdinates
	{
		float32 x = 0;
		float32 y = 0;
		float32 width = 0;
		float32 height = 0;

	};
	/////////////Graphics 

	coOrdinates dynamicRectCoordinates =
	{
		0,
		0,
		10,
		10,
	};
	coOrdinates groundRectCoordinates =
	{
		50,
		100,
		500,
		50,
	};
	

	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
	sf::RectangleShape dynamicRect(sf::Vector2f(dynamicRectCoordinates.width, dynamicRectCoordinates.height));
	dynamicRect.setFillColor(sf::Color::Green);
	dynamicRect.setPosition(dynamicRectCoordinates.x - dynamicRectCoordinates.width / 2, dynamicRectCoordinates.y - dynamicRectCoordinates.height / 2);

	sf::RectangleShape groundRect(sf::Vector2f(groundRectCoordinates.width, groundRectCoordinates.height));
	groundRect.setFillColor(sf::Color::Red);
	groundRect.setPosition(groundRectCoordinates.x - groundRectCoordinates.width / 2, groundRectCoordinates.y - groundRectCoordinates.height / 2);


	b2Vec2 rightForce(2.0f, 0.0f);
	b2Vec2 leftForce(-2.0f, 0.0f);
	b2Vec2 upForce(0.0f, -2.0f);
	b2Vec2 downForce(0.0f, 2.0f);

	b2Vec2 centre(dynamicRectCoordinates.width / 2, dynamicRectCoordinates.height / 2);
	float32 angle1 = 0.0f;

	//gravity vector;
	b2Vec2 myGravity(0.0f, 0.5f);
	//adding gravity to my world;
	b2World myWorld(myGravity);

	//CLASSS
	MyBox pudlo;

	pudlo.bodyDef.type = b2_dynamicBody;
	pudlo.bodyDef.position.Set(0, 0);

	pudlo.body = myWorld.CreateBody(&pudlo.bodyDef);

	pudlo.vertex[0].Set(0.0f, 0.0f);
	pudlo.vertex[1].Set(10.0f, 0.0f);
	pudlo.vertex[2].Set(10.0f, 10.0f);
	pudlo.vertex[3].Set(0.0f, 10.0f);

	pudlo.polygon.Set(pudlo.vertex, pudlo.countVert);

	pudlo.fixtureDef.shape = &pudlo.polygon;
	pudlo.fixtureDef.density = 2.0f;
	pudlo.fixtureDef.friction = 1.0f;

	pudlo.body->CreateFixture(&pudlo.fixtureDef);

	pudlo.Convex.setPointCount(4);

	pudlo.Convex.setPoint(0, sf::Vector2f(0.0f, 0.0f));
	pudlo.Convex.setPoint(1, sf::Vector2f(10.0f, 0.0f));
	pudlo.Convex.setPoint(2, sf::Vector2f(10.0f, 10.0f));
	pudlo.Convex.setPoint(3, sf::Vector2f(0.0f, 10.0f));

	pudlo.Convex.setFillColor(sf::Color::Magenta);
	pudlo.Convex.setPosition(0, 0);



	//EEEND

	//creating a static body (they are static by default)

	// ground body definition
	b2BodyDef myGroundBodyDef;
	// setting initial position for body
	myGroundBodyDef.position.Set(groundRectCoordinates.x, groundRectCoordinates.y);
	// passed definition to the world
	b2Body* myGroundBody = myWorld.CreateBody(&myGroundBodyDef);
	//creating a ground polygon
	b2PolygonShape myGroundBox;
	//setting width (2x50) and height (2x50)
	myGroundBox.SetAsBox(groundRectCoordinates.width / 2, groundRectCoordinates.height / 2);
	//creating fixture with a shortcut 'cause we do not need any specific properties (density, mass, ect.)  to this body
	myGroundBody->CreateFixture(&myGroundBox, 0.0f);


	//creating the box shape

	//same as above
	b2BodyDef myDynamicBodyDef;
	myDynamicBodyDef.type = b2_dynamicBody;
	myDynamicBodyDef.position.Set(dynamicRectCoordinates.x, dynamicRectCoordinates.y);
	b2Body* myDynamicBody = myWorld.CreateBody(&myDynamicBodyDef);

	b2PolygonShape DynamicBody;
	DynamicBody.SetAsBox((dynamicRectCoordinates.width) / 2, (dynamicRectCoordinates.height) / 2, centre, angle1);


	//creating fixture definition using the box
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &DynamicBody;
	myFixtureDef.density = 0.2f;
	myFixtureDef.friction = 0.2f;

	//creating fixture
	myDynamicBody->CreateFixture(&myFixtureDef);

	//NEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEW

	b2BodyDef vertBodyDef;
	vertBodyDef.type = b2_dynamicBody;
	vertBodyDef.position.Set(30, 30);
	b2Body* vertDynamic = myWorld.CreateBody(&vertBodyDef);

	b2Vec2 vertices[3];
	vertices[0].Set(0.0f, 0.0f);
	vertices[1].Set(10.0f, 0.0f);
	vertices[2].Set(0.0f, 10.0f);
	int32 count = 3;

	b2PolygonShape vertPolygon;
	vertPolygon.Set(vertices, count);


	b2FixtureDef vertFixture;
	vertFixture.shape = &vertPolygon;
	vertFixture.density = 1.0f;
	vertFixture.friction = 0.5f;		

	vertDynamic->CreateFixture(&vertFixture);


	sf::ConvexShape convex;

	convex.setPointCount(3);

	convex.setPoint(0, sf::Vector2f(0.0f, 0.0f));
	convex.setPoint(1, sf::Vector2f(10.0f, 0.0f));
	convex.setPoint(2, sf::Vector2f(0.0f, 10.0f));

	convex.setFillColor(sf::Color::White);

	convex.setPosition(30, 30);
	//EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEND

	//creating a simulation

	//creating timestep
	float32 timeStep = 1.0f / 60.0f;
	int remainingJumpSteps = 0;

	//solving constraints iterations
	int32 myVelocityIterations = 6;
	int32 myPositonIterations = 2;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//game loop
		
		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{

			myWorld.Step(timeStep, myVelocityIterations, myPositonIterations);

			b2Vec2 myPosition = myDynamicBody->GetPosition();
			float32 myAngle = myDynamicBody->GetAngle();

			b2Vec2 vertPosition = vertDynamic->GetPosition();
			float32 vertAngle = vertDynamic->GetAngle();

			b2Vec2 ConvexPosition = pudlo.body->GetPosition();
			float32 ConvexAngle = pudlo.body->GetAngle();


			printf("%4.2f %4.2f %4.2f %4.2f %4.2f %4.2f  \n", myPosition.x, myPosition.y, myAngle, vertPosition.x, vertPosition.y, vertAngle);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				myDynamicBody->SetLinearVelocity(rightForce);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				myDynamicBody->SetLinearVelocity(leftForce);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				myDynamicBody->SetLinearVelocity(upForce);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				myDynamicBody->SetLinearVelocity(downForce);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				remainingJumpSteps = 6;

			if (remainingJumpSteps > 0)
			{
				float force = myDynamicBody->GetMass()*10 / (1 / 60);
				force /= 6.0;
				myDynamicBody->ApplyForce(b2Vec2(0, -force), myDynamicBody->GetWorldCenter(),0);
				remainingJumpSteps--;
			}



			//Graphics

			dynamicRect.setPosition(myPosition.x, myPosition.y);
			dynamicRect.setRotation(myAngle*(180 / 3.14));

			convex.setPosition(vertPosition.x, vertPosition.y);
			convex.setRotation(vertAngle*(180 / 3.14));

			pudlo.Convex.setPosition(ConvexPosition.x, ConvexPosition.y);
			pudlo.Convex.setRotation(ConvexAngle*(180 / 3.14));

			//displaying
			window.clear();
			window.draw(dynamicRect);
			window.draw(groundRect);
			window.draw(convex);
			window.draw(pudlo.Convex);
			window.display();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
	}
	printf("----------------------------------------------------\n");
	return 0;
}
