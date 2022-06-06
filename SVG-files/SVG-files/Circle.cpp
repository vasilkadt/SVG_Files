#include "Circle.h"
#pragma warning (disable : 4996)

const double PI = 3.1415;

Circle::Circle(double x, double y, double radius, char* color) : Shape(1), radius(radius)
{
	setPoint(0, x, y);
	setColor(color);
}

Circle::Circle(double x, double y, double radius) : Shape(1), radius(radius)
{
	setPoint(0, x, y);
	setColor(nullptr);
}

double Circle::getArea() const
{
	return PI * radius * radius;
}

double Circle::getPer() const
{
	return 2 * PI * radius;
}

bool Circle::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	return p.getDist(getPointAtIndex(0)) <= radius;
}

Shape* Circle::clone() const
{
	Shape* copy = new Circle(*this);
	return copy;
}

double Circle::getRadius() const
{
	return radius;
}

void Circle::print()
{
	std::cout << " circle ";
	Shape::point p1 = getPointAtIndex(0);
	std::cout << p1.x << " " << p1.y << " " << radius << " ";
	if (getColor() != nullptr)
	{
		std::cout << getColor();
	}
}

void Circle::erase()
{
	std::cout << "Erased a circle" << std::endl;
}

bool Circle::within(Shape& region)
{
	auto* rectangle = dynamic_cast<Rectangle*>(&region);
	auto* circle = dynamic_cast<Circle*>(&region);

	if (rectangle != nullptr) {
		point rightPoint1 = { getPointAtIndex(0).x + radius, getPointAtIndex(0).y };
		point leftPoint2 = { getPointAtIndex(0).x - radius, getPointAtIndex(0).y };
		point upperPoint3 = { getPointAtIndex(0).x, getPointAtIndex(0).y + radius };
		point lowerPoint4 = { getPointAtIndex(0).x, getPointAtIndex(0).y - radius };

		if (rectangle->isPointIn(rightPoint1.x, rightPoint1.y) && rectangle->isPointIn(leftPoint2.x, leftPoint2.y)
			&& rectangle->isPointIn(upperPoint3.x, upperPoint3.y) && rectangle->isPointIn(lowerPoint4.x, lowerPoint4.y))
		{
			return true;
		}
		return false;
	}

	if (circle != nullptr) {
		if (this->getPointAtIndex(0).x + this->radius <= circle->getPointAtIndex(0).x + circle->getRadius() &&
			this->getPointAtIndex(0).x - this->radius >= circle->getPointAtIndex(0).x - circle->getRadius() &&
			this->getPointAtIndex(0).y + this->radius <= circle->getPointAtIndex(0).y + circle->getRadius() &&
			this->getPointAtIndex(0).y - this->radius >= circle->getPointAtIndex(0).y - circle->getRadius()) {
			return true;
		}
		else return false;
	}
}

void Circle::translate(double vertical, double horizontal)
{
	point currentPoint1 = getPointAtIndex(0);
	currentPoint1.x += horizontal;
	currentPoint1.y += vertical;
	setPoint(0, currentPoint1.x, currentPoint1.y);
}
