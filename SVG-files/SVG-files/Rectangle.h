#pragma once
#include "Shape.h"
#include "Circle.h"
#include "Line.h"
class Rectangle : public Shape
{
private:
	double width;
	double height;
public:
	Rectangle(double x1, double y1, double width, double height, char* color);
	Rectangle(double x1, double y1, double width, double height);

	void print() override;
	void erase() override;
	void translate(double vertical, double horizontal) override;
	void setWidth(double inputWidth);
	void setHeight(double inputHeight);
	bool within(Shape& region) override;
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
};