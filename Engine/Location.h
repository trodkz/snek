#pragma once
struct Location
{
	int x;
	int y;
public: 
	
	void Add(Location& val) {
		x = x + val.x;
		y = y + val.y;
	}

	bool operator== (const Location& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!= (const Location& rhs) const {
		return x != rhs.x || y != rhs.y;
	}
};

