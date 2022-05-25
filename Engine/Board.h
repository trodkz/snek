#pragma once
#include "Graphics.h"
#include "Location.h"
class Board
{
	static constexpr int dimension = 20;
	static constexpr int height = 30;
	static constexpr int width = 40;
	static constexpr int cellPadding = 0;
	Graphics& gfx;

public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int getGridHeight();
	int getGridWidth();
	bool isInsideBoard(const Location& loc) const;
	void DrawBorder() const;

};

