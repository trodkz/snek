#pragma once

#include "Graphics.h"

class SpriteCodex
{
public:
	static void DrawGameOver( int x,int y,Graphics& gfx );
	static void DrawTitle( int x,int y,Graphics& gfx );
	static void DrawPause(int x, int y, Graphics& gfx);
	static void DrawScore(int x, int y, Graphics& gfx);
};