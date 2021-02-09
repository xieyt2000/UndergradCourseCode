#pragma once
#include "new_shape.h"
#include"shape.h"
#include<iostream>
#include<string>
class NewShape2Shape : public Shape
{
private:
	NewShape* newShape;
public:
	NewShape2Shape(NewShape* data) : newShape(data) {};
	void draw()
	{
		newShape->drawShape();
	}
	void resize()
	{
		std::cout << newShape->description() << " can't be resized. Please create new one with required values." << std::endl;
	}
	std::string description()
	{
		return newShape->description();
	}
};