#pragma once
#include "Box2D/Box2D.h"

class MyClass
{
public:
	MyClass();
	~MyClass();

private:
	b2BodyDef BodyDef;
};

MyClass::MyClass()
{
	BodyDef.type = b2_dynamicBody;
}

MyClass::~MyClass()
{
}