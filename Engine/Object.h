#pragma once
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Vec2.h"
#include "Color_m.h"

class Object
{
protected:
	Vec2 pos;

public:
	Object() = default;
	Object(const int X, const int Y);
};

class Crosshair : public Object
{
protected:
	Graphics* gfx;

	int width, height;
	Color_m color;

	Vec2
		collLUp,
		collLDown,
		collRUp,
		collRDown;

	unsigned int
		keyUp,
		keyDown,
		keyLeft,
		keyRight;

	Vec2 vel;
	bool inhibitSprint = false;
	bool isCollidedUp = false;
	bool isCollidedDown = false;
	bool isCollidedLeft = false;
	bool isCollidedRight = false;

	bool isInit = false;

public:
	Crosshair() = default;
	Crosshair(
		Graphics& Gfx, 
		const int X = 400, 
		const int Y = 300,
		const int width = 12,
		const int height = 12) noexcept;

	virtual void Init(Graphics& Gfx, 
		const int X = 400, 
		const int Y = 300,
		const int width = 12,
		const int height = 12) noexcept;

protected:
	void UpdateWallCollisionX();
	void UpdateWallCollisionY();
	virtual void MoveUp(const float dt) noexcept;
	virtual void MoveDown(const float dt) noexcept;
	virtual void MoveLeft(const float dt) noexcept;
	virtual void MoveRight(const float dt) noexcept;
	void Sprint() noexcept;

public:
	bool isOverlapped(const Crosshair& other);
	void ChgColor(const short R, const short G, const short B);

protected:
	virtual void FixCollision() noexcept;

public:
	virtual void Draw() noexcept;
	virtual void Update(Keyboard& kbd, const float dt) noexcept;

};


class CrosshairEnemy : public Crosshair
{
public:
	enum StartDirection
	{
		LUp, LDown, RUp, RDown
	};

private:
	StartDirection startDir;

public:
	CrosshairEnemy() = default;
	CrosshairEnemy(
		Graphics& Gfx,
		const int X = 400,
		const int Y = 300,
		const int width = 12,
		const int height = 12,
		StartDirection StartDir = LUp);

	void Init(
		Graphics& Gfx,
		const int X = 400,
		const int Y = 300,
		const int width = 12,
		const int height = 12,
		StartDirection StartDir = LUp) noexcept;

	//void Draw() override;
	void Update(Keyboard& kbd, const float dt) noexcept override;
	void Update(const float dt) noexcept;
};