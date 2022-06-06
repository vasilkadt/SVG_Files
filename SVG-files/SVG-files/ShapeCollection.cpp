#include "ShapeCollection.h"
#include <stdexcept> 
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include <fstream>
#pragma warning (disable : 4996)

void ShapeCollection::free()
{
	for (size_t i = 0; i < shapesCount; i++)
		delete shapes[i];
	delete[] shapes;
}

void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	shapes = new Shape * [other.shapesCount];
	shapesCount = other.shapesCount;
	capacity = other.capacity;

	for (size_t i = 0; i < shapesCount; i++)
	{
		shapes[i] = other.shapes[i]->clone();
	}
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];
	for (size_t i = 0; i < shapesCount; i++)
		newCollection[i] = shapes[i];
	delete[] shapes;
	shapes = newCollection;
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	shapesCount = 0;
	shapes = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}

ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::addShape(Shape* shape)
{
	if (shapesCount == capacity)
		resize();
	shapes[shapesCount++] = shape;
}

void  ShapeCollection::deleteShape(size_t index)
{
	for (size_t i = index - 1; i < shapesCount; i++)
	{
		shapes[i] = shapes[i + 1];
	}
	shapesCount--;
}

void ShapeCollection::addRectangle(double x1, double y1, double x3, double y3, char* color)
{
	Rectangle* rect = new Rectangle(x1, y1, x3, y3, color);
	addShape(rect);
}

void ShapeCollection::addCircle(double x1, double y1, double r, char* color)
{
	Circle* circlce = new Circle(x1, y1, r, color);
	addShape(circlce);

}

void ShapeCollection::addLine(double x1, double y1, double x2, double y2, char* color)
{
	Line* line = new Line(x1, y1, x2, y2, color);
	addShape(line);
}

double ShapeCollection::getPerOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->getPer();
}

double ShapeCollection::getAreaOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->getArea();
}

double ShapeCollection::getIfPointInShapeByIndex(size_t ind, double x, double y) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->isPointIn(x, y);
}

int ShapeCollection::toSeparator(const char* command)
{
	int counter = 0;
	while (*command != '=' && *command != ' ' && *command != '\n' && *command != '\0')
	{
		counter++;
		command++;
	}
	return counter;
}

int ShapeCollection::toSeparatorFile(const char* command)
{
	int counter = 0;
	while (*command != '\"' && *command != '\n' && *command != '\0')
	{
		counter++;
		command++;
	}
	return counter;
}

void ShapeCollection::getInfoFromFile(const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "Error opening the file!";
	}
	else
	{
		std::cout << "Successfully opened " << fileName << std::endl;
		int counterLines = 1;
		while (!file.eof())
		{
			char line[BUFFER_LINE_SIZE] = "";
			file.getline(line, BUFFER_LINE_SIZE);
			counterLines++;
			if (counterLines > 1) 
			{
				char firstX[BUFFER_LINE_SIZE] = "";
				char secondX[BUFFER_LINE_SIZE] = "";
				char firstY[BUFFER_LINE_SIZE] = "";
				char secondY[BUFFER_LINE_SIZE] = "";
				char color[BUFFER_LINE_SIZE] = "";
				char radius[BUFFER_LINE_SIZE] = "";
				double x1 = 0;
				double x2 = 0;
				double y1 = 0;
				double y2 = 0;
				double rad = 0;
				if (line[1] == 'r')
				{
					int i = 0;
					int countPoint = 1;
					int j = 0;

					while (line[i] != '\0')
					{
						if (line[i] == '"') {
							i++;
							j = 0;
							while (line[i] != '"')
							{
								if (countPoint == 1) {
									firstX[j] = line[i];
								}
								else if (countPoint == 2) {
									firstY[j] = line[i];
								}
								else if (countPoint == 3) {
									secondX[j] = line[i];
								}
								else if (countPoint == 4) {
									secondY[j] = line[i];
								}
								else if (countPoint == 5) {
									color[j] = line[i];
								}
								i++;
								j++;
							}
							countPoint++;
						}
						i++;
					}
					x1 = atof(firstX);
					x2 = atof(secondX);
					y1 = atof(firstY);
					y2 = atof(secondY);
					addRectangle(x1, y1, x2, y2, color);
				}
				else if (line[1] == 'c') {
					int i = 0;
					int countPoint = 1;
					int j = 0;

					while (line[i] != '\0')
					{
						if (line[i] == '"') {
							i++;
							j = 0;
							while (line[i] != '"')
							{
								if (countPoint == 1) {
									firstX[j] = line[i];
								}
								else if (countPoint == 2) {
									firstY[j] = line[i];
								}
								else if (countPoint == 3) {
									radius[j] = line[i];
								}
								else if (countPoint == 4) {
									color[j] = line[i];
								}
								i++;
								j++;
							}
							countPoint++;
						}
						i++;
					}
					x1 = atof(firstX);
					y1 = atof(firstY);
					rad = atof(radius);
					addCircle(x1, y1, rad, color);
				}
				else if (line[1] == 'l') {
					int i = 0;
					int countPoint = 1;
					int j = 0;

					while (line[i] != '\0')
					{
						if (line[i] == '"') {
							i++;
							j = 0;
							while (line[i] != '"')
							{
								if (countPoint == 1) {
									firstX[j] = line[i];
								}
								else if (countPoint == 2) {
									firstY[j] = line[i];
								}
								else if (countPoint == 3) {
									secondX[j] = line[i];
								}
								else if (countPoint == 4) {
									secondY[j] = line[i];
								}
								else if (countPoint == 5) {
									color[j] = line[i];
								}
								i++;
								j++;
							}
							countPoint++;
						}
						i++;
					}
					x1 = atof(firstX);
					x2 = atof(secondX);
					y1 = atof(firstY);
					y2 = atof(secondY);
					addLine(x1, y1, x2, y2, color);
				}
			}
		}
	}
}

void ShapeCollection::saveToFile(const char* fileName)
{
	std::ofstream file(fileName, std::ios::trunc);
	if (!file.is_open())
	{
		std::cout << "Error opening the file!";
	}
	else
	{
		file << "<svg>" << std::endl;
		std::cout << "Successfully saved the changes to " << fileName;
		for (size_t i = 0; i < shapesCount; i++)
		{
			auto* rectangle = dynamic_cast<Rectangle*>(this->shapes[i]);
			auto* circle = dynamic_cast<Circle*>(shapes[i]);
			auto* line = dynamic_cast<Line*>(shapes[i]);

			if (rectangle != nullptr) {
				file << "<rect x=\"" << rectangle->getPointAtIndex(0).x << "\" y=\"" <<
					rectangle->getPointAtIndex(0).y<<"\" width=\""<< rectangle->getPointAtIndex(1).x<<
					"\" height=\""<<rectangle->getPointAtIndex(1).y<<"\" fill=\""<<
					rectangle->getColor() << "\"/>" << std::endl;
			}
			if (circle != nullptr) {
				file << "<circle cx=\"" << circle->getPointAtIndex(0).x << "\" cy=\"" <<
					circle->getPointAtIndex(0).y << "\" r=\"" << circle->getRadius() <<
					 "\" fill=\"" << circle->getColor() << "\"/>"<<std::endl;
			}
			if (line != nullptr) {
				file << "<line x1=\"" << line->getPointAtIndex(0).x << "\" y1=\"" <<
					line->getPointAtIndex(0).y << "\" x2=\"" << line->getPointAtIndex(1).x <<
					"\" y2=\"" << line->getPointAtIndex(1).y <<
					"\" fill=\"" << line->getColor()<<"\"/>" << std::endl;
			}
		}
		file << "</svg>";
	}
}

void ShapeCollection::interface()
{

	char commandLine[BUFFER_LINE_SIZE] = "";
	while (true)
	{
		std::cout << ">";
		std::cin.getline(commandLine, BUFFER_LINE_SIZE);

		if (commandLine == " " || commandLine == "\0")
		{
			continue;
		}

		int len = strlen(commandLine);

		int firstArgSize = toSeparator(commandLine);
		char* commandFirstArg = new char[firstArgSize + 1];

		for (int i = 0; i < firstArgSize; i++)
			commandFirstArg[i] = commandLine[i];
		commandFirstArg[firstArgSize] = '\0';

		bool flag = false;
		if (len == firstArgSize)
		{
			flag = true;
			if (strcmp(commandFirstArg, "print") == 0)
			{
				for (size_t i = 0; i < shapesCount; i++)
				{
					std::cout << i + 1 << ".";
					shapes[i]->print();
					std::cout << std::endl;
				}
			}
			else if (strcmp(commandFirstArg, "save") == 0)
			{
				saveToFile("figures.svg");
				std::cout << std::endl;
			}
			else if (strcmp(commandFirstArg, "exit") == 0)
			{
				break;
			}
		}
		int secondArgSize = len - firstArgSize - 1;
		char* commandSecondArg = new char[secondArgSize + 1];

		for (int i = 0; i < secondArgSize; i++)
		{
			commandSecondArg[i] = commandLine[i + firstArgSize + 1];
		}
		commandSecondArg[secondArgSize] = '\0';

		if (flag == true)
		{
			continue;
		}

		if (strcmp(commandFirstArg, "erase") == 0)
		{
			int numberOfFigureToErase = atoi(commandSecondArg);
			if (numberOfFigureToErase > shapesCount)
			{
				std::cout << "There is no figure number " << numberOfFigureToErase << "!" << std::endl;
			}
			else
			{
				shapes[numberOfFigureToErase - 1]->erase();
				deleteShape(numberOfFigureToErase);
			}
		}
		else if (strcmp(commandFirstArg, "open") == 0)
		{
			getInfoFromFile(commandSecondArg);
		}
		else if (strcmp(commandFirstArg, "create") == 0)
		{
			int figureTypeLen = toSeparator(commandSecondArg);
			char* figureType = new char[figureTypeLen + 1];

			for (int i = 0; i < figureTypeLen; i++)
				figureType[i] = commandSecondArg[i];
			figureType[figureTypeLen] = '\0';

			int thirdArgSize = secondArgSize - figureTypeLen - 1;
			char* commandThirdArg = new char[thirdArgSize + 1];
			for (int i = 0; i < thirdArgSize; i++)
			{
				commandThirdArg[i] = commandSecondArg[i + figureTypeLen + 1];
			}
			commandThirdArg[thirdArgSize] = '\0';

			if (strcmp(figureType, "line") == 0)
			{
				//take x1
				int x1Len = toSeparator(commandThirdArg);
				char* point1 = new char[x1Len + 1];

				for (int i = 0; i < x1Len; i++)
					point1[i] = commandThirdArg[i];
				point1[x1Len] = '\0';
				double x1 = atof(point1);

				//take y1
				int forthArgSize = thirdArgSize - x1Len - 1;
				char* commandForthArg = new char[forthArgSize + 1];
				for (int i = 0; i < forthArgSize; i++)
				{
					commandForthArg[i] = commandThirdArg[i + x1Len + 1];
				}
				commandForthArg[forthArgSize] = '\0';
				int y1Len = toSeparator(commandForthArg);
				char* point2 = new char[y1Len + 1];

				for (int i = 0; i < y1Len; i++)
					point2[i] = commandForthArg[i];
				point2[y1Len] = '\0';
				double y1 = atof(point2);

				//take x2
				int fifthArgSize = forthArgSize - y1Len - 1;
				char* commandFifthArg = new char[fifthArgSize + 1];
				for (int i = 0; i < fifthArgSize; i++)
				{
					commandFifthArg[i] = commandForthArg[i + y1Len + 1];
				}
				commandFifthArg[fifthArgSize] = '\0';
				int x2Len = toSeparator(commandFifthArg);
				char* point3 = new char[x2Len + 1];

				for (int i = 0; i < x2Len; i++)
					point3[i] = commandFifthArg[i];
				point3[x2Len] = '\0';
				double x2 = atof(point3);

				//take y2
				int sixArgSize = fifthArgSize - x2Len - 1;
				char* commandSixArg = new char[sixArgSize + 1];
				for (int i = 0; i < sixArgSize; i++)
				{
					commandSixArg[i] = commandFifthArg[i + x2Len + 1];
				}
				commandSixArg[sixArgSize] = '\0';
				int y2Len = toSeparator(commandSixArg);
				char* point4 = new char[y2Len + 1];

				for (int i = 0; i < y2Len; i++)
					point4[i] = commandSixArg[i];
				point4[y2Len] = '\0';
				double y2 = atof(point4);

				//take color
				int sevenArgSize = sixArgSize - y2Len - 1;
				char* commandSevenArg = new char[sevenArgSize + 1];
				for (int i = 0; i < sevenArgSize; i++)
				{
					commandSevenArg[i] = commandSixArg[i + y2Len + 1];
				}
				commandSevenArg[sevenArgSize] = '\0';
				int colorLen = toSeparator(commandSevenArg);
				char* color = new char[colorLen + 1];

				for (int i = 0; i < colorLen; i++)
					color[i] = commandSevenArg[i];
				color[colorLen] = '\0';

				addLine(x1, y1, x2, y2, color);
				std::cout << "Successfully created line" << std::endl;
			}
			else if (strcmp(figureType, "circle") == 0)
			{
				//take x1
				int x1Len = toSeparator(commandThirdArg);
				char* point1 = new char[x1Len + 1];

				for (int i = 0; i < x1Len; i++)
					point1[i] = commandThirdArg[i];
				point1[x1Len] = '\0';
				double x1 = atof(point1);

				//take y1
				int forthArgSize = thirdArgSize - x1Len - 1;
				char* commandForthArg = new char[forthArgSize + 1];
				for (int i = 0; i < forthArgSize; i++)
				{
					commandForthArg[i] = commandThirdArg[i + x1Len + 1];
				}
				commandForthArg[forthArgSize] = '\0';
				int y1Len = toSeparator(commandForthArg);
				char* point2 = new char[y1Len + 1];

				for (int i = 0; i < y1Len; i++)
					point2[i] = commandForthArg[i];
				point2[y1Len] = '\0';
				double y1 = atof(point2);

				//take r
				int fifthArgSize = forthArgSize - y1Len - 1;
				char* commandFifthArg = new char[fifthArgSize + 1];
				for (int i = 0; i < fifthArgSize; i++)
				{
					commandFifthArg[i] = commandForthArg[i + y1Len + 1];
				}
				commandFifthArg[fifthArgSize] = '\0';
				int rLen = toSeparator(commandFifthArg);
				char* point3 = new char[rLen + 1];

				for (int i = 0; i < rLen; i++)
					point3[i] = commandFifthArg[i];
				point3[rLen] = '\0';
				double r = atof(point3);

				//take color
				int sixArgSize = fifthArgSize - rLen - 1;
				char* commandSixArg = new char[sixArgSize + 1];
				for (int i = 0; i < sixArgSize; i++)
				{
					commandSixArg[i] = commandFifthArg[i + rLen + 1];
				}
				commandSixArg[sixArgSize] = '\0';
				int colorLen = toSeparator(commandSixArg);
				char* color = new char[colorLen + 1];

				for (int i = 0; i < colorLen; i++)
					color[i] = commandSixArg[i];
				color[colorLen] = '\0';

				addCircle(x1, y1, r, color);
				std::cout << "Successfully created circle" << std::endl;
			}
			else if (strcmp(figureType, "rectangle") == 0)
			{
				//take x1
				int x1Len = toSeparator(commandThirdArg);
				char* point1 = new char[x1Len + 1];

				for (int i = 0; i < x1Len; i++)
					point1[i] = commandThirdArg[i];
				point1[x1Len] = '\0';
				double x1 = atof(point1);

				//take y1
				int forthArgSize = thirdArgSize - x1Len - 1;
				char* commandForthArg = new char[forthArgSize + 1];
				for (int i = 0; i < forthArgSize; i++)
				{
					commandForthArg[i] = commandThirdArg[i + x1Len + 1];
				}
				commandForthArg[forthArgSize] = '\0';
				int y1Len = toSeparator(commandForthArg);
				char* point2 = new char[y1Len + 1];

				for (int i = 0; i < y1Len; i++)
					point2[i] = commandForthArg[i];
				point2[y1Len] = '\0';
				double y1 = atof(point2);

				//take x3
				int fifthArgSize = forthArgSize - y1Len - 1;
				char* commandFifthArg = new char[fifthArgSize + 1];
				for (int i = 0; i < fifthArgSize; i++)
				{
					commandFifthArg[i] = commandForthArg[i + y1Len + 1];
				}
				commandFifthArg[fifthArgSize] = '\0';
				int x3Len = toSeparator(commandFifthArg);
				char* point3 = new char[x3Len + 1];

				for (int i = 0; i < x3Len; i++)
					point3[i] = commandFifthArg[i];
				point3[x3Len] = '\0';
				double x3 = atof(point3);

				//take y2
				int sixArgSize = fifthArgSize - x3Len - 1;
				char* commandSixArg = new char[sixArgSize + 1];
				for (int i = 0; i < sixArgSize; i++)
				{
					commandSixArg[i] = commandFifthArg[i + x3Len + 1];
				}
				commandSixArg[sixArgSize] = '\0';
				int y3Len = toSeparator(commandSixArg);
				char* point4 = new char[y3Len + 1];

				for (int i = 0; i < y3Len; i++)
					point4[i] = commandSixArg[i];
				point4[y3Len] = '\0';
				double y3 = atof(point4);

				//take color
				int sevenArgSize = sixArgSize - y3Len - 1;
				char* commandSevenArg = new char[sevenArgSize + 1];
				for (int i = 0; i < sevenArgSize; i++)
				{
					commandSevenArg[i] = commandSixArg[i + y3Len + 1];
				}
				commandSevenArg[sevenArgSize] = '\0';
				int colorLen = toSeparator(commandSevenArg);
				char* color = new char[colorLen + 1];

				for (int i = 0; i < colorLen; i++)
					color[i] = commandSevenArg[i];
				color[colorLen] = '\0';

				addRectangle(x1, y1, x3, y3, color);
				std::cout << "Successfully created rectangle" << std::endl;
			}
		}
		else if (strcmp(commandFirstArg, "within") == 0)
		{
			int figureTypeLen = toSeparator(commandSecondArg);
			char* figureType = new char[figureTypeLen + 1];

			for (int i = 0; i < figureTypeLen; i++)
				figureType[i] = commandSecondArg[i];
			figureType[figureTypeLen] = '\0';

			int thirdArgSize = secondArgSize - figureTypeLen - 1;
			char* commandThirdArg = new char[thirdArgSize + 1];
			for (int i = 0; i < thirdArgSize; i++)
			{
				commandThirdArg[i] = commandSecondArg[i + figureTypeLen + 1];
			}
			commandThirdArg[thirdArgSize] = '\0';

			if (strcmp(figureType, "circle") == 0)
			{
				//take x1
				int x1Len = toSeparator(commandThirdArg);
				char* point1 = new char[x1Len + 1];

				for (int i = 0; i < x1Len; i++)
					point1[i] = commandThirdArg[i];
				point1[x1Len] = '\0';
				double x1 = atof(point1);

				//take y1
				int forthArgSize = thirdArgSize - x1Len - 1;
				char* commandForthArg = new char[forthArgSize + 1];
				for (int i = 0; i < forthArgSize; i++)
				{
					commandForthArg[i] = commandThirdArg[i + x1Len + 1];
				}
				commandForthArg[forthArgSize] = '\0';
				int y1Len = toSeparator(commandForthArg);
				char* point2 = new char[y1Len + 1];

				for (int i = 0; i < y1Len; i++)
					point2[i] = commandForthArg[i];
				point2[y1Len] = '\0';
				double y1 = atof(point2);

				//take r
				int fifthArgSize = forthArgSize - y1Len - 1;
				char* commandFifthArg = new char[fifthArgSize + 1];
				for (int i = 0; i < fifthArgSize; i++)
				{
					commandFifthArg[i] = commandForthArg[i + y1Len + 1];
				}
				commandFifthArg[fifthArgSize] = '\0';
				int rLen = toSeparator(commandFifthArg);
				char* point3 = new char[rLen + 1];

				for (int i = 0; i < rLen; i++)
					point3[i] = commandFifthArg[i];
				point3[rLen] = '\0';
				double r = atof(point3);

				Circle circle(x1, y1, r);
				int counter = 1;
				bool validWithin = false;

				for (size_t i = 0; i < shapesCount; i++)
				{
					if (shapes[i]->within(circle))
					{
						validWithin = true;
						std::cout << counter << ".";
						shapes[i]->print();
						std::cout << std::endl;
						counter++;
					}
				}
				if (!validWithin)
				{
					std::cout << "No figures are located within";
					circle.print();
					std::cout << std::endl;
				}
			}
			else if (strcmp(figureType, "rectangle") == 0)
			{
				//take x1
				int x1Len = toSeparator(commandThirdArg);
				char* point1 = new char[x1Len + 1];

				for (int i = 0; i < x1Len; i++)
					point1[i] = commandThirdArg[i];
				point1[x1Len] = '\0';
				double x1 = atof(point1);

				//take y1
				int forthArgSize = thirdArgSize - x1Len - 1;
				char* commandForthArg = new char[forthArgSize + 1];
				for (int i = 0; i < forthArgSize; i++)
				{
					commandForthArg[i] = commandThirdArg[i + x1Len + 1];
				}
				commandForthArg[forthArgSize] = '\0';
				int y1Len = toSeparator(commandForthArg);
				char* point2 = new char[y1Len + 1];

				for (int i = 0; i < y1Len; i++)
					point2[i] = commandForthArg[i];
				point2[y1Len] = '\0';
				double y1 = atof(point2);

				//take x3
				int fifthArgSize = forthArgSize - y1Len - 1;
				char* commandFifthArg = new char[fifthArgSize + 1];
				for (int i = 0; i < fifthArgSize; i++)
				{
					commandFifthArg[i] = commandForthArg[i + y1Len + 1];
				}
				commandFifthArg[fifthArgSize] = '\0';
				int x3Len = toSeparator(commandFifthArg);
				char* point3 = new char[x3Len + 1];

				for (int i = 0; i < x3Len; i++)
					point3[i] = commandFifthArg[i];
				point3[x3Len] = '\0';
				double x3 = atof(point3);

				//take y2
				int sixArgSize = fifthArgSize - x3Len - 1;
				char* commandSixArg = new char[sixArgSize + 1];
				for (int i = 0; i < sixArgSize; i++)
				{
					commandSixArg[i] = commandFifthArg[i + x3Len + 1];
				}
				commandSixArg[sixArgSize] = '\0';
				int y3Len = toSeparator(commandSixArg);
				char* point4 = new char[y3Len + 1];

				for (int i = 0; i < y3Len; i++)
					point4[i] = commandSixArg[i];
				point4[y3Len] = '\0';
				double y3 = atof(point4);

				Rectangle rectangle(x1, y1, x3, y3);
				int counter = 1;
				bool validWithin = false;

				for (size_t i = 0; i < shapesCount; i++)
				{

					if (shapes[i]->within(rectangle))
					{
						validWithin = true;
						std::cout << counter << ".";
						shapes[i]->print();
						std::cout << std::endl;
						counter++;
					}

				}
				if (!validWithin)
				{
					std::cout << "No figures are located within";
					rectangle.print();
					std::cout << std::endl;
				}
			}
		}
		else if (strcmp(commandFirstArg, "translate") == 0)
		{
			int positionLen = toSeparator(commandSecondArg);
			char* position = new char[positionLen + 1];

			for (int i = 0; i < positionLen; i++)
				position[i] = commandSecondArg[i];
			position[positionLen] = '\0';

			int thirdArgSize = secondArgSize - positionLen - 1;
			char* commandThirdArg = new char[thirdArgSize + 1];
			for (int i = 0; i < thirdArgSize; i++)
			{
				commandThirdArg[i] = commandSecondArg[i + positionLen + 1];
			}
			commandThirdArg[thirdArgSize] = '\0';

			if (strcmp(position, "vertical") == 0)
			{
				//take x1
				int x1Len = toSeparator(commandThirdArg);
				char* point1 = new char[x1Len + 1];

				for (int i = 0; i < x1Len; i++)
					point1[i] = commandThirdArg[i];
				point1[x1Len] = '\0';
				double x1 = atof(point1);

				//take position2
				int forthArgSize = thirdArgSize - x1Len - 1;
				char* commandForthArg = new char[forthArgSize + 1];
				for (int i = 0; i < forthArgSize; i++)
				{
					commandForthArg[i] = commandThirdArg[i + x1Len + 1];
				}
				commandForthArg[forthArgSize] = '\0';
				int position2Len = toSeparator(commandForthArg);
				char* position2 = new char[position2Len + 1];

				for (int i = 0; i < position2Len; i++)
					position2[i] = commandForthArg[i];
				position2[position2Len] = '\0';

				//take x2
				int fifthArgSize = forthArgSize - position2Len - 1;
				char* commandFifthArg = new char[fifthArgSize + 1];
				for (int i = 0; i < fifthArgSize; i++)
				{
					commandFifthArg[i] = commandForthArg[i + position2Len + 1];
				}
				commandFifthArg[fifthArgSize] = '\0';
				int x2Len = toSeparator(commandFifthArg);
				char* point2 = new char[x2Len + 1];

				for (int i = 0; i < x2Len; i++)
					point2[i] = commandFifthArg[i];
				point2[x2Len] = '\0';
				double x2 = atof(point2);

				for (size_t i = 0; i < shapesCount; i++)
				{
					shapes[i]->translate(x1, x2);
				}
				std::cout << "Translated all figures!" << std::endl;
			}
			else if (strcmp(position, "horizontal") == 0)
			{
				//take x1
				int x1Len = toSeparator(commandThirdArg);
				char* point1 = new char[x1Len + 1];

				for (int i = 0; i < x1Len; i++)
					point1[i] = commandThirdArg[i];
				point1[x1Len] = '\0';
				double x1 = atof(point1);

				//take position2
				int forthArgSize = thirdArgSize - x1Len - 1;
				char* commandForthArg = new char[forthArgSize + 1];
				for (int i = 0; i < forthArgSize; i++)
				{
					commandForthArg[i] = commandThirdArg[i + x1Len + 1];
				}
				commandForthArg[forthArgSize] = '\0';
				int position2Len = toSeparator(commandForthArg);
				char* position2 = new char[position2Len + 1];

				for (int i = 0; i < position2Len; i++)
					position2[i] = commandForthArg[i];
				position2[position2Len] = '\0';

				//take x2
				int fifthArgSize = forthArgSize - position2Len - 1;
				char* commandFifthArg = new char[fifthArgSize + 1];
				for (int i = 0; i < fifthArgSize; i++)
				{
					commandFifthArg[i] = commandForthArg[i + position2Len + 1];
				}
				commandFifthArg[fifthArgSize] = '\0';
				int x2Len = toSeparator(commandFifthArg);
				char* point2 = new char[x2Len + 1];

				for (int i = 0; i < x2Len; i++)
					point2[i] = commandFifthArg[i];
				point2[x2Len] = '\0';
				double x2 = atof(point2);

				for (size_t i = 0; i < shapesCount; i++)
				{
					shapes[i]->translate(x2, x1);
				}
				std::cout << "Translated all figures!" << std::endl;
			}
		}
		else if (strcmp(commandFirstArg, "get") == 0)
		{
			int infoLen = toSeparator(commandSecondArg);
			char* info = new char[infoLen + 1];

			for (int i = 0; i < infoLen; i++)
				info[i] = commandSecondArg[i];
			info[infoLen] = '\0';
			if (strcmp(info, "areas") == 0)
			{
				for (size_t i = 0; i < shapesCount; i++)
				{
					std::cout << i + 1 << ". ";
					std::cout << shapes[i]->getArea();
					std::cout << std::endl;
				}
			}
			else if (strcmp(info, "perimeters") == 0)
			{
				for (size_t i = 0; i < shapesCount; i++)
				{
					std::cout << i + 1;
					std::cout << shapes[i]->getPer();
					std::cout << std::endl;
				}
			}
		}
		else if (strcmp(commandFirstArg, "pointIn") == 0)
		{
			int x1Len = toSeparator(commandSecondArg);
			char* point1 = new char[x1Len + 1];

			for (int i = 0; i < x1Len; i++)
				point1[i] = commandSecondArg[i];
			point1[x1Len] = '\0';
			double x1 = atof(point1);

			int thirdArgSize = secondArgSize - x1Len - 1;
			char* commandThirdArg = new char[thirdArgSize + 1];
			for (int i = 0; i < thirdArgSize; i++)
			{
				commandThirdArg[i] = commandSecondArg[i + x1Len + 1];
			}
			commandThirdArg[thirdArgSize] = '\0';
			int y1Len = toSeparator(commandSecondArg);
			char* point2 = new char[x1Len + 1];

			for (int i = 0; i < x1Len; i++)
				point2[i] = commandSecondArg[i];
			point2[x1Len] = '\0';
			double y1 = atof(point1);

			bool isPointIn = false;
			for (size_t i = 0; i < shapesCount; i++)
			{
				if (shapes[i]->isPointIn(x1, y1))
				{
					isPointIn = true;
					std::cout << i + 1;
					shapes[i]->print();
					std::cout << std::endl;
				}
			}
			if (!isPointIn)
			{
				std::cout << "No shape contains this point.";
				std::cout << std::endl;
			}
		}
		else
		{
			std::cout << "Invalid command! Try again!" << std::endl;
		}
	}
}