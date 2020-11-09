#pragma once
class Point {
	private:
		short X = 0;
		short Y = 0;

	public:
		Point(short newX = 0, short newY = 0);
		~Point();

		short getX();
		short getY();

		void setX(short newX = 0);
		void setY(short newY = 0);
};