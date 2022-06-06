#pragma once
#include "Shape.h"

const int BUFFER_LINE_SIZE = 1024;

class ShapeCollection
{
	Shape** shapes;
	size_t shapesCount;
	size_t capacity;

	void free();
	void copyFrom(const ShapeCollection& other);
	void resize();

	void addShape(Shape* shape);
	void deleteShape(size_t index);
	int toSeparator(const char* command);
	int toSeparatorFile(const char* command);
	void getInfoFromFile(const char* fileName);
	void saveToFile(const char* fileName);

public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();

	void addRectangle(double x1, double y1, double x3, double y3, char* color);
	void addCircle(double x1, double y1, double r, char* color);
	void addLine(double x1, double y1, double x2, double y2, char* color);

	double getPerOfFigureByIndex(size_t ind) const;
	double getAreaOfFigureByIndex(size_t ind) const;
	double getIfPointInShapeByIndex(size_t ind, double x, double y) const;

	void interface();
};
