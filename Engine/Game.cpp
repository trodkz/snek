/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	snek(snekLoc),
	goal(rng, brd, snek)
{
	snek.MoveBy(delta_loc);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
		gameIsStarted = true;
	}
	if (wnd.kbd.KeyIsPressed('P') && !gameIsOver && gameIsStarted) {
		if (!pInhibitor)
		{
			if (gameIsPaused && wnd.kbd.KeyIsPressed('P')) {
				gameIsPaused = false;
				pInhibitor = true;
			}
			else
			{
				gameIsPaused = true;
				pInhibitor = true;
			}
		}
	}
	else
	{
		pInhibitor = false;
	}
	

	if (!gameIsOver && !gameIsPaused && gameIsStarted)
	{
		
		if (wnd.kbd.KeyIsPressed(VK_UP) && delta_loc != downDelta)
		{
			delta_loc = { 0, -1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN) && delta_loc != upDelta) {
			delta_loc = { 0, 1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT) && delta_loc != rightDelta) {
			delta_loc = { -1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && delta_loc != leftDelta) {
			delta_loc = { 1,0 };
		}

		/*if (snek.isInTile(goal.GetLocation())) {
			goal.Respawn(rng, brd, snek);
			snek.Grow();
		}*/ // investigate why this didn't work

		
		snekMoveCounter++;
		if (snekMoveCounter >= snekMovePeriod) {
			snekMoveCounter = 0;
			const Location next = snek.getNextHeadLocation(delta_loc);
			if (!brd.isInsideBoard(next)
				|| snek.eatingBody(next)) {
				gameIsOver = true;
			}
			else
			{
				bool eating = next == goal.GetLocation();
				if (eating) {
					snek.Grow();
					score++;
					snekMovePeriod = std::max(snekMovePeriod - 2, snekMovePeriodMin);
					
				}
				snek.MoveBy(delta_loc);
				if (eating)
				{
					goal.Respawn(rng, brd, snek);
				}
			}
		}
	}
	
	if (wnd.kbd.KeyIsPressed('T')) {
		if (!tInhibitor)
		{
			gameIsOver = false;
			gameIsStarted = true;
			goal.Respawn(rng, brd, snek);
			snek = Snake(snekLoc);
			delta_loc = { 1,0 };
			snekMovePeriod = 48;
			snekMoveCounter = 0;
			score = 0;
			tInhibitor = true;
		}		
	}
	else
	{
		tInhibitor = false;
	}
	
}



void Game::ComposeFrame()
{
	DrawBoard();
	brd.DrawBorder();
	Scorer(score, 60, 3, gfx);
	
	if (gameIsStarted)
	{
		snek.Draw(brd);
		goal.Draw(brd);
		if (gameIsPaused) {
			SpriteCodex::DrawPause(320, 248, gfx);
		}
		if (gameIsOver) {
			SpriteCodex::DrawGameOver(360, 260, gfx);
		}
	}
	else {
		SpriteCodex::DrawTitle(300, 210, gfx);
	}
}


void Game::DrawBoard() {
	Color c = { 186, 199, 0 };
	for (int x = 0; x < brd.getGridWidth(); x++)
	{
		for (int y = 0; y < brd.getGridHeight(); y++)
		{
			Location loc = { x, y };
			brd.DrawCell(loc, c);
		}
	}
}

void Game::Scorer(int score, int x, int y, Graphics& gfx)
{
	SpriteCodex::DrawScore(16, 3, gfx);
	int xlimit;
	for (int i = 0; i < score; i++)
	{
		xlimit = x + 10;
		for (; x < xlimit; x++)
		{
			for (int j = y; j < y + 10; j++)
			{
				gfx.PutPixel(x, j, 111, 96, 1);
			}
		}
		x += 5;
	}
	

	//for (int i = 0; i < score; i++) { DrawScore(15 * (i + 1), 20); }
}


