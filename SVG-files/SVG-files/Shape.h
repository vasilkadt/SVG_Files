#pragma once
#include <iostream>


class Shape
{
protected:
	struct point
	{
		double x;
		double y;

		point() :x(0), y(0) {}
		point(double x, double y) :x(x), y(y) {}
		double getDist(const point& other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}
	};
private:
	point* points;
	size_t pointsCount;
	char* color;

	void copyFrom(const Shape& other);
	void free();

public:
	Shape(size_t pointsCount);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape();

	void setPoint(size_t pointIndex, double x, double y);
	void setColor(char* color);

	const point& getPointAtIndex(size_t index) const;
	const char* getColor() const;

	virtual void print() = 0;
	virtual void erase() = 0;
	virtual void translate(double vertical, double horizontal) = 0;
	virtual bool within(Shape& region) = 0;
	virtual double getArea() const = 0;
	virtual double getPer()  const = 0;
	virtual bool isPointIn(double x, double y) const = 0;
	virtual Shape* clone() const = 0;
};