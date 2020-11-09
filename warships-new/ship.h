#pragma once

#include "point.h"
#include "ship-state.h"

class Ship {
	private:
		Point shipPoint = Point();
		ShipState shipState = ShipState::STATE_EMPTY; // By default, field is empty

	public:
		Ship(Point newPoint = Point(0, 0), ShipState newState = ShipState::STATE_EMPTY);
		~Ship();

		Point getPoint();
		ShipState getShipState();

		void setPoint(Point newPoint = Point());
		void setShipState(ShipState newState = ShipState::STATE_EMPTY);
};