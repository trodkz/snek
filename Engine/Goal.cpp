#include "Goal.h"

Goal::Goal(std::mt19937& rng, Board& brd, const Snake& snek)
{
	Respawn(rng, brd, snek);
}

void Goal::Respawn(std::mt19937& rng,  Board& brd, const Snake& snek)
{
	std::uniform_int_distribution<int> xPos(0, brd.getGridWidth() - 1);
	std::uniform_int_distribution<int> yPos(0, brd.getGridHeight() - 1);
	
	Location newloc;
	do
	{
		newloc.x = xPos(rng);
		newloc.y = yPos(rng);
	} while (snek.isInTile(newloc) || newloc.x == 0 || newloc.x >= 39 || newloc.y == 0 || newloc.y >= 28);

	loc = newloc;
}

void Goal::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Goal::GetLocation() const
{
	return loc;
}
