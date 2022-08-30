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
	rng(rd()),
	xDist(0, gfx.ScreenWidth-1),
	yDist(0, gfx.ScreenHeight-1),
	vDist(0, 3)
{
	for (int i = 0; i < enemyCount; i++)
		enemies[i].Init(gfx, xDist(rng), 14, 14, yDist(rng), vDist(rng));
	curs.Init(gfx);
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
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		wnd.Kill();

	bool isAllKilled = false;
	for (int i = 0; i < enemyCount; i++)
	{
		if (enemies[i].killed == true)
		{
			isAllKilled = true;
		}
		else
		{
			isAllKilled = false;
			break;
		}
	}
	
	if (isAllKilled)
		curs.ChgColor(0, 255, 0);

	for (int i = 0; i < enemyCount; i++)
		if (curs.isOverlapped(enemies[i]))
			enemies[i].killed = true;

	const float dt = ft.Mark();
	for (int i = 0; i < enemyCount; i++)
		enemies[i].Update(dt);
	curs.Update(wnd.kbd, dt);
}

void Game::ComposeFrame()
{
	for (int i = 0; i < enemyCount; i++)
		enemies[i].Draw();
	curs.Draw();
}
