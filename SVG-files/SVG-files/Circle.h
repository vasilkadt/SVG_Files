#pragma once
#include "Shape.h"
#include "Rectangle.h"

class Circle : public Shape
{
	double radius;

public:
	Circle(double x, double y, double radius, char* color);
	Circle(double x, double y, double radius);

	void print() override;
	void erase() override;
	void translate(double vertical, double horizontal) override;
	bool within(Shape& region) override;
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;

	double getRadius() const;
};
