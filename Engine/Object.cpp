#include "Object.h"

/******************************/
/* Object				      */
/******************************/
Object::Object(const int X, const int Y)
{
	pos.x = X;
	pos.y = Y;
}

/******************************/
/* Crosshair				  */
/******************************/
Crosshair::Crosshair(
	Graphics& Gfx,
	const int X,
	const int Y,
	const int Width,
	const int Height) noexcept
{
	Init(Gfx, X, Y, Width, Height);
}

void Crosshair::Init(
	Graphics& Gfx,
	const int X,
	const int Y,
	const int Width,
	const int Height) noexcept
{
	gfx = &Gfx;

	pos.Init(X, Y);
	width = Width;
	height = Height;
	FixCollision();

	keyUp = VK_UP;
	keyDown = VK_DOWN;
	keyLeft = VK_LEFT;
	keyRight = VK_RIGHT;

	color.r = 255;
	color.g = 0;
	color.b = 0;

	vel.x = 3 * 60.0f;
	vel.y = 3 * 60.0f;

	isInit = true;
}

void Crosshair::MoveUp(const float dt) noexcept
{
	const int speed = int(vel.y * dt);
	pos.y -= speed;
	FixCollision();
	if (collLUp.y < 0)
	{
		pos.y += -collLUp.y;
		FixCollision();
	}
}
void Crosshair::MoveDown(const float dt) noexcept
{
	const int speed = int(vel.y * dt);
	pos.y += speed;
	FixCollision();
	if (collRDown.y > gfx->ScreenHeight - 1)
	{
		pos.y += (gfx->ScreenHeight - 1) - collRDown.y;
		FixCollision();
	}
}
void Crosshair::MoveLeft(const float dt) noexcept
{
	const int speed = int(vel.x * dt);
	pos.x -= speed;
	FixCollision();
	if (collLUp.x < 0)
	{
		pos.x += -collLUp.x;
		FixCollision();
	}
}
void Crosshair::MoveRight(const float dt) noexcept
{
	const int speed = int(vel.x * dt);
	pos.x += speed;
	FixCollision();
	if (collRDown.x > gfx->ScreenWidth - 1)
	{
		pos.x += (gfx->ScreenWidth - 1) - collRDown.x;
		FixCollision();
	}
}
void Crosshair::Sprint() noexcept
{
	vel.x = vel.x == 3 * 60.0f ? 10 * 60.0f : 3 * 60.0f;
	vel.y = vel.y == 3 * 60.0f ? 10 * 60.0f : 3 * 60.0f;
}

void Crosshair::FixCollision() noexcept
{
	collLUp.x = pos.x;
	collLUp.y = pos.y;
	collRDown.x = pos.x + width;
	collRDown.y = pos.y + height;
}

void Crosshair::Draw() noexcept
{
	gfx->PutPixel(pos.x +  5, pos.y + 5 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  5, pos.y + 4 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  5, pos.y + 3 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  5, pos.y + 2 , color.r, color.g, color.b);
						  
	gfx->PutPixel(pos.x +  5, pos.y + 9 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  5, pos.y + 10, color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  5, pos.y + 11, color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  5, pos.y + 12, color.r, color.g, color.b);
						  
	gfx->PutPixel(pos.x +  0, pos.y + 7 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  1, pos.y + 7 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  2, pos.y + 7 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  3, pos.y + 7 , color.r, color.g, color.b);
						 		   	    
	gfx->PutPixel(pos.x +  7, pos.y + 7 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  8, pos.y + 7 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x +  9, pos.y + 7 , color.r, color.g, color.b);
	gfx->PutPixel(pos.x + 10, pos.y + 7 , color.r, color.g, color.b);
}
void Crosshair::Update(Keyboard& kbd, const float dt) noexcept
{
	if (kbd.KeyIsPressed(VK_SHIFT))
	{
		if(inhibitSprint) {}
		else
		{
			Sprint();
			inhibitSprint = true;
		}
	}
	else
		inhibitSprint = false;

	if (kbd.KeyIsPressed(keyUp))
	{
		MoveUp(dt);
	}
	if (kbd.KeyIsPressed(keyDown))
	{
		MoveDown(dt);
	}
	if (kbd.KeyIsPressed(keyLeft))
	{
		MoveLeft(dt);
	}
	if (kbd.KeyIsPressed(keyRight))
	{
		MoveRight(dt);
	}
}
