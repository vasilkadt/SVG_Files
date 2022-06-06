#pragma once
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

class Line : public Shape
{
public:
	Line(double x1, double y1, double x2, double y2, char* color);

	void print() override;
	void erase() override;
	void translate(double vertical, double horizontal) override;
	bool within(Shape& region) override;
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
};