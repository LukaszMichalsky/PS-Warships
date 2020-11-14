#pragma once

enum class ShipState {
	STATE_EMPTY = 0x10, // Field is empty (no ship in it)
	STATE_INVALID = 0x20, // An error occured, for example try to get ship from field with invalid coordinates
	STATE_MISSED_HIT = 0x30, // Field which was tried to hit, but there was no ship.
	STATE_NOT_HIT = 0x40, // Field contains ship which is not hit yet
	STATE_HIT = 0x50 // Field contains ship after being hit
};