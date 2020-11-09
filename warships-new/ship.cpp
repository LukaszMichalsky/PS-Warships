#include "ship.h"

Ship::Ship(Point newPoint, ShipState newState) : shipPoint(newPoint), shipState(newState) {
	// Ship constructor, no additional code needed
}

Ship::~Ship() {
	// Ship destructor, no additional code needed
}

Point Ship::getPoint() {
	return shipPoint;
}

ShipState Ship::getShipState() {
	return shipState;
}

void Ship::setPoint(Point newPoint) {
	shipPoint = newPoint;
}

void Ship::setShipState(ShipState newState) {
	shipState = newState;
}