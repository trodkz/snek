/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Board.h"
#include <random>
#include "Snake.h"
#include "Goal.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawBorder();
	void DrawBoard();
	void Scorer(int score, int x, int y, Graphics& gfx);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Board brd;
	std::mt19937 rng;
	Location snekLoc = { 4,4 };
	Snake snek;	
	Goal goal;
	Location delta_loc = { 1,0 };
	int snekMovePeriod = 48;
	int snekMoveCounter = 0;
	static constexpr int snekMovePeriodMin = 4;
	int score = 0;
	int moveIncrementer = 1;
	bool gameIsStarted = false;
	bool gameIsOver = false;
	bool gameIsPaused = false;
	bool tInhibitor = false;
	bool pInhibitor = false;
	const Location downDelta = { 0, 1 };
	const Location upDelta = { 0, -1 };
	const Location rightDelta = { 1,0 };
	const Location leftDelta = { -1,0 };
	/********************************/
};