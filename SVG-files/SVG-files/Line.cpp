#include "Line.h"
#pragma warning (disable : 4996)

Line::Line(double x1, double y1, double x2, double y2, char* color) : Shape(4)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
	setColor(color);
}

double Line::getArea() const
{
	std::cout << "Line do not have an area." << std::endl;
	return 0;
}

double Line::getPer() const
{
	std::cout << "Line do not have a perimeter." << std::endl;
	return 0;
}

bool Line::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.y >= getPointAtIndex(1).x &&
		p.y <= getPointAtIndex(0).y && p.y >= getPointAtIndex(2).y;
}

Shape* Line::clone() const
{
	Shape* copy = new Line(*this);
	return copy;
}

void Line::print()
{
	std::cout << " line ";
	point p1 = getPointAtIndex(0);
	std::cout << p1.x << " " << p1.y << " ";
	point p2 = getPointAtIndex(1);
	std::cout << p2.x << " " << p2.y << " ";
	std::cout << getColor();
}

void Line::erase()
{
	std::cout << "Erased a line!" << std::endl;
}

bool Line::within(Shape& region)
{
	auto* rectangle = dynamic_cast<Rectangle*>(&region);
	auto* circle = dynamic_cast<Circle*>(&region);

	if (rectangle != nullptr) {
		point currentPoint1 = getPointAtIndex(0);
		point currentPoint2 = getPointAtIndex(1);
		if (rectangle->isPointIn(currentPoint1.x, currentPoint1.y) && rectangle->isPointIn(currentPoint2.x, currentPoint2.y))
		{
			return true;
		}
		else return false;
	}

	if (circle != nullptr)
	{
		point currentPoint1 = getPointAtIndex(0);
		point currentPoint2 = getPointAtIndex(1);
		if (circle->isPointIn(currentPoint1.x, currentPoint1.y) && circle->isPointIn(currentPoint2.x, currentPoint2.y))
		{
			return true;
		}
		else return false;
	}
}

void Line::translate(double vertical, double horizontal)
{
	point currentPoint1 = getPointAtIndex(0);
	point currentPoint2 = getPointAtIndex(1);
	currentPoint1.x += horizontal;
	currentPoint1.y += vertical;
	currentPoint2.x += horizontal;
	currentPoint2.y += vertical;
	setPoint(0, currentPoint1.x, currentPoint1.y);
	setPoint(1, currentPoint2.x, currentPoint2.y);
}
