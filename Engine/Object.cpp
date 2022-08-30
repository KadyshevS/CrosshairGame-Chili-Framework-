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

void Crosshair::UpdateWallCollisionX()
{
	if (collLUp.x < 0)
	{
		isCollidedLeft = true;
		pos.x += -collLUp.x;
		FixCollision();
	}
	else
	{
		isCollidedLeft = false;
	}
	if (collRDown.x > gfx->ScreenWidth - 1)
	{
		isCollidedRight = true;
		pos.x += (gfx->ScreenWidth - 1) - collRDown.x;
		FixCollision();
	}
	else
	{
		isCollidedRight = false;
	}
}
void Crosshair::UpdateWallCollisionY()
{
	if (collLUp.y < 0)
	{
		isCollidedUp = true;
		pos.y += -collLUp.y;
		FixCollision();
	}
	else
	{
		isCollidedUp = false;
	}
	if (collRDown.y > gfx->ScreenHeight - 1)
	{
		isCollidedDown = true;
		pos.y += (gfx->ScreenHeight - 1) - collRDown.y;
		FixCollision();
	}
	else
	{
		isCollidedDown = false;
	}
}

void Crosshair::MoveUp(const float dt) noexcept
{
	const int speed = int(vel.y * dt);
	pos.y -= speed;
	FixCollision();
	UpdateWallCollisionY();
}
void Crosshair::MoveDown(const float dt) noexcept
{
	const int speed = int(vel.y * dt);
	pos.y += speed;
	FixCollision();
	UpdateWallCollisionY();
}
void Crosshair::MoveLeft(const float dt) noexcept
{
	const int speed = int(vel.x * dt);
	pos.x -= speed;
	FixCollision();
	UpdateWallCollisionX();
}
void Crosshair::MoveRight(const float dt) noexcept
{
	const int speed = int(vel.x * dt);
	pos.x += speed;
	FixCollision();
	UpdateWallCollisionX();
}
void Crosshair::Sprint() noexcept
{
	vel.x = vel.x == 3 * 60.0f ? 10 * 60.0f : 3 * 60.0f;
	vel.y = vel.y == 3 * 60.0f ? 10 * 60.0f : 3 * 60.0f;
}

bool Crosshair::isOverlapped(const Crosshair& other)
{
	return
		(collLUp.x >= other.collLDown.x && collLUp.x <= other.collRDown.x && collLUp.y >= other.collRUp.y   && collLUp.y <= other.collRDown.y)   ||
		(collLDown.x >= other.collLUp.x && collLDown.x <= other.collRUp.x && collLDown.y >= other.collRUp.y && collLDown.y <= other.collRDown.y) ||
		(collRUp.x >= other.collLDown.x && collRUp.x <= other.collRDown.x && collRUp.y >= other.collRUp.y   && collRUp.y <= other.collRDown.y)   ||
		(collRDown.x >= other.collLUp.x && collRDown.x <= other.collRUp.x && collRDown.y >= other.collRUp.y && collRDown.y <= other.collRDown.y) ;
}
void Crosshair::ChgColor(const short R, const short G, const short B)
{
	color.r = R;
	color.g = G;
	color.b = B;
}

void Crosshair::FixCollision() noexcept
{
	collLUp.x = pos.x;
	collLUp.y = pos.y;

	collRUp.x = pos.x + width;
	collRUp.y = pos.y;

	collLDown.x = pos.x;
	collLDown.y = pos.y + height;

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

/******************************/
/* Crosshair Enemy			  */
/******************************/

CrosshairEnemy::CrosshairEnemy(
	Graphics& Gfx, 
	const int X, 
	const int Y, 
	const int width, 
	const int height,
	StartDirection StartDir)
{
	Init(Gfx, X, Y, width, height, StartDir);
}

void CrosshairEnemy::Init(
	Graphics& Gfx, 
	const int X, 
	const int Y, 
	const int Width, 
	const int Height,
	StartDirection StartDir) noexcept
{
	gfx = &Gfx;

	pos.Init(X, Y);
	width = Width;
	height = Height;
	FixCollision();

	startDir = StartDir;

	color.r = 255;
	color.g = 0;
	color.b = 0;

	vel.x = 3 * 60.0f;
	vel.y = 3 * 60.0f;

	isInit = true;
}

//void CrosshairEnemy::Draw() {}
void CrosshairEnemy::Update(Keyboard& kbd, const float dt) noexcept {}
void CrosshairEnemy::Update(const float dt) noexcept
{
	switch (startDir)
	{
	case LUp:
		MoveLeft(dt);
		MoveUp(dt);
		break;
	case LDown:
		MoveLeft(dt);
		MoveDown(dt);
		break;
	case RUp:
		MoveRight(dt);
		MoveUp(dt);
		break;
	case RDown:
		MoveRight(dt);
		MoveDown(dt);
		break;
	}

	if (isCollidedLeft || isCollidedRight)
		vel.x = -vel.x;
	if (isCollidedUp || isCollidedDown)
		vel.y = -vel.y;
}
