#include "Shape.h"
#pragma warning (disable : 4996)

Shape::Shape(size_t pointsCount) : pointsCount(pointsCount)
{
	points = new point[pointsCount];
	color = nullptr;
}

void Shape::copyFrom(const Shape& other)
{
	points = new point[other.pointsCount];

	for (int i = 0; i < other.pointsCount; i++)
		points[i] = other.points[i];

	pointsCount = other.pointsCount;

	color = new char[strlen(other.color) + 1];
	strcpy(color, other.color);
}
void Shape::free()
{
	delete[] color;
	delete[] points;
}

Shape::Shape(const Shape& other)
{
	copyFrom(other);
}
Shape& Shape::operator= (const Shape& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Shape::~Shape()
{
	free();
}

const Shape::point& Shape::getPointAtIndex(size_t index) const
{
	if (index >= pointsCount)
		throw std::exception("Invalid point index!");

	return  points[index];
}

void Shape::setPoint(size_t pointIndex, double x, double y)
{
	if (pointIndex >= pointsCount)
		throw std::exception("Invalid point index!");

	points[pointIndex] = point(x, y);
}

void Shape::setColor(char* color)
{
	if (this->color == color || color == nullptr)
		return;

	delete this->color;
	this->color = new char[strlen(color) + 1];
	strcpy(this->color, color);
}

const char* Shape::getColor() const
{
	return color;
}
