#include "Snake.h"
#include <assert.h>

Snake::Snake(Location& loc)
{
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = {
		{111, 96, 1},
		{131, 114, 1},
		{151, 132, 1},
		{131, 114, 1}
	};
	for (int i = 0; i < nSegmentsMax; i++)
	{
		segments[i].InitBody(bodyColors[i % 4]);
	}
	segments[0].InitHead(loc);
	for (int i = 0; i < nSegments; ++i) {
		segments[i].index = i + 1;
	}
}

void Snake::Segment::InitHead(const Location& loc) {
	this->loc = loc;
	c = { 111, 96, 1 };
}

void Snake::MoveBy(Location& deltaLoc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(deltaLoc);
}
void Snake::Segment::Follow(const Segment& next) {
	loc = next.loc;
}

void Snake::Grow()
{ 
	
	if (nSegments < nSegmentsMax) {
		nSegments += 1;
	}
	
}

void Snake::Segment::InitBody(Color c) {
	this->c = c;
}

void Snake::Draw(Board& brd) 
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].DrawSeg(brd);
	}
}
void Snake::Segment::DrawSeg(Board& brd) {
	brd.DrawCell(loc, c);
}

Location Snake::getNextHeadLocation( Location deltaLoc) const
{
	Location l(segments[0].getLocation());
	l.Add(deltaLoc);
	return l;
}

bool Snake::eatingBody(const Location& nextHeadLocation) const
{
	for (int i = 1; i < (nSegments - 1); i++)
	{
		/*if (nextHeadLocation.x == (segments[i].getLocation()).x &&
			nextHeadLocation.y == (segments[i].getLocation()).y) {
			return true;
		}*/		
		if (nextHeadLocation == segments[i].getLocation()) {
			return true;
		}
	}
	return false;
}

bool Snake::isInTile(const Location& nextHeadLocation) const
{
	for (int i = 1; i < nSegments; i++)
	{
		if (nextHeadLocation == segments[i].getLocation()) {
			return true;
		}
	}
	return false;
}




void Snake::Segment::MoveBy( Location& delta_loc) {
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}


Location Snake::Segment::getLocation() const
{
	return loc;
}
