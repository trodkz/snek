#pragma once
#include "Board.h"
class Snake
{
private:
	class Segment {
		Location loc;
		Color c;
	public:
		void InitHead(const Location& loc);
		void InitBody(Color c);
		void Follow(const Segment& next);
		void MoveBy(Location& delta_loc);
		void DrawSeg(Board& brd);
		Location getLocation() const;
		int index;
		
	};

	static constexpr Color headColor = Colors::Gray;
	static constexpr Color bodyColor = Colors::White;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;


public:
	Snake(Location& loc);
	void MoveBy(Location& deltaLoc);
	void Grow();
	void Draw(Board& brd);
	Location getNextHeadLocation( Location loc) const;
	bool eatingBody(const Location& nextHeadLocation) const;
	bool isInTile(const Location& nextHeadLocation) const;
	
};

