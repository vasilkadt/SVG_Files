#include "Rectangle.h"
#pragma warning (disable : 4996)

Rectangle::Rectangle(double x1, double y1, double inputWidth, double inputHeight, char* color) : Shape(4)
{
	setPoint(0, x1, y1);
	width = inputWidth;
	height = inputHeight;
	setColor(color);
}

Rectangle::Rectangle(double x1, double y1, double inputWidth, double inputHeight) : Shape(4)
{
	setPoint(0, x1, y1);
	width = inputWidth;
	height = inputHeight;
	setColor(nullptr);
}

void Rectangle::setWidth(double inputWidth) {
	width = inputWidth;
}
void Rectangle::setHeight(double inputHeight) {
	height = inputHeight;
}
double Rectangle::getArea() const
{
	return height * width;
}

double Rectangle::getPer() const
{
	return 2 * (height + width);
}

bool Rectangle::isPointIn(double x, double y) const
{
	Shape::point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.x <= getPointAtIndex(0).x+width &&
		p.y >= getPointAtIndex(0).y && p.y <= getPointAtIndex(0).y+height;
}

Shape* Rectangle::clone() const
{
	Shape* copy = new Rectangle(*this);
	return copy;
}

void Rectangle::print()
{
	std::cout << " rectangle ";
	Shape::point p1 = getPointAtIndex(0);
	std::cout << p1.x << " " << p1.y << " ";
	std::cout << width << " " << height << " ";
	if (getColor() != nullptr)
	{
		std::cout << getColor();
	}
}

void Rectangle::erase()
{
	std::cout << "Erased a rectangle!" << std::endl;
}

bool Rectangle::within(Shape& region)
{
	auto* rectangle = dynamic_cast<Rectangle*>(&region);
	auto* circle = dynamic_cast<Circle*>(&region);

	if (rectangle != nullptr) {
		point currentPoint1 = getPointAtIndex(0);
		if (rectangle->isPointIn(currentPoint1.x, currentPoint1.y) && rectangle->isPointIn(currentPoint1.x+width, currentPoint1.y+height)
		&& rectangle->isPointIn(currentPoint1.x, currentPoint1.y+height) && rectangle->isPointIn(currentPoint1.x+width, currentPoint1.y))
		{
			return true;
		}
		else return false;
	}

	if (circle != nullptr) {
		point currentPoint1 = getPointAtIndex(0);
		point currentPoint2 = { getPointAtIndex(0).x+width,getPointAtIndex(0).y };
		point currentPoint3 = { getPointAtIndex(0).x +width, getPointAtIndex(0).y + height };
		point currentPoint4 = { getPointAtIndex(1).x, getPointAtIndex(0).y + height };
		point* points = new point[]{ currentPoint1, currentPoint2, currentPoint3, currentPoint4 };

		for (size_t i = 0; i < 3; i++)
		{
			if ((circle->getPointAtIndex(0).x - points[i].x) * (circle->getPointAtIndex(0).x - points[i].x)
				+ (circle->getPointAtIndex(0).y - points[i].y) * (circle->getPointAtIndex(0).y - points[i].y)
		> circle->getRadius() * circle->getRadius())
				return false;
		}

		return true;
		delete[] points;
	}
}

void Rectangle::translate(double vertical, double horizontal)
{
	point currentPoint1 = getPointAtIndex(0);
	currentPoint1.x += horizontal;
	currentPoint1.y += vertical;
	setPoint(0, currentPoint1.x, currentPoint1.y);
}