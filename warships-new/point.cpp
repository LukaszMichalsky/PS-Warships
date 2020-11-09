#include "point.h"

Point::Point(short newX, short newY) : X(newX), Y(newY) {
	// Point constructor, no additional code needed
}

Point::~Point() {
	// Point destructor, no additional code needed
}

short Point::getX() {
	return X;
}

short Point::getY() {
	return Y;
}

void Point::setX(short newX) {
	X = newX;
}

void Point::setY(short newY) {
	Y = newY;
}