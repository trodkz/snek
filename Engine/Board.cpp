#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	//assert(loc.x >= 0);
	assert(loc.x <= width);
	assert(loc.y >= 0);
	assert(loc.y <= height);
	gfx.DrawRectDim(loc.x * dimension + cellPadding, loc.y * dimension + cellPadding, dimension - (cellPadding * 2), dimension - (cellPadding * 2), c);
}

int Board::getGridHeight()
{
	return height;
}

int Board::getGridWidth()
{
	return width;
}

bool Board::isInsideBoard(const Location& loc) const
{
	return loc.x > 0 && loc.x < (width - 1) &&
		loc.y > 0 && loc.y < (height - 1);
}

void Board::DrawBorder() const
{
	int cellFourth = (dimension / 4) * 3;
	
	for (int x = cellFourth; x < (width * dimension) - cellFourth; x++)
	{
		for (int y = cellFourth; y < dimension; y++)
		{
			gfx.PutPixel(x, y, 111, 96, 1);
		}
		for (int y = ((height - 1) * dimension); y < (height * dimension) - cellFourth; y++)
		{
			gfx.PutPixel(x, y, 111, 96, 1);
		}
	}

	for (int y = dimension; y < ((height - 1) * dimension); y++)
	{
		for (int x = cellFourth; x < dimension; x++)
		{
			gfx.PutPixel(x, y, 111, 96, 1);
		}
		for (int x = ((width - 1) * dimension); x < (width * dimension) - cellFourth; x++)
		{
			gfx.PutPixel(x, y, 111, 96, 1);
		}
	}
}
