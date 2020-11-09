#pragma once

#include "point.h"
#include "ship-state.h"

class Ship {
	private:
		Point shipPoint = Point(0, 0);
		ShipState shipState = ShipState::STATE_NOT_HIT; // By default, new ship is not hit

	public:
		Ship(Point newPoint = Point(0, 0), ShipState newState = ShipState::STATE_NOT_HIT);
		~Ship();

		Point getPoint();
		ShipState getShipState();

		void setPoint(Point newPoint = Point(0, 0));
		void setShipState(ShipState newState = ShipState::STATE_NOT_HIT);
};