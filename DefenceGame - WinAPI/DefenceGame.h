#pragma once
#ifndef DEFENCE_GAME_H_
#define DEFENCE_GAME_H_

#define _USE_MATH_DEFINES

#include "framework.h"
#include <cmath>
#include <vector>

class Structure
{
protected:
	FLOAT x;
	FLOAT y;
	bool _delete = false;
public:
	Structure(FLOAT x, FLOAT y) : x(x), y(y) { _delete = false; }
	FLOAT getx() { return x; }
	FLOAT gety() { return y; }
	void setx(FLOAT x) { this->x = x; }
	void sety(FLOAT y) { this->y = y; }
	bool get_delete() { return _delete; }
	void set_delete(bool a) { _delete = a; }
	virtual bool Collision(Structure*) { return false; }
};

class Cannon : public Structure
{
private:
	FLOAT radian = M_PI * 0.5;
	FLOAT Radius;
public:
	Cannon(FLOAT x, FLOAT y, FLOAT r) : Structure(x, y), Radius(r) {}
	FLOAT getr() { return Radius; }
	FLOAT getradian() { return radian; }
	void setradian(FLOAT radian) { this->radian = radian; }

};

class Bullet : public Structure
{
private:
	FLOAT vx;
	FLOAT vy;
	FLOAT radius;
public:
	Bullet(int x, int y, FLOAT r, FLOAT radian) : Structure(x, y), radius(r)
	{
		vx = 5 * cos(radian);
		vy = 5 * sin(radian);
	}
	FLOAT getvx() { return vx; }
	FLOAT getvy() { return vy; }
	FLOAT getr() { return radius; }
	bool Collision(Structure*);

};

class Enemy : public Structure
{
private:
	FLOAT vx;
	FLOAT vy;
	FLOAT radius;
public:
	Enemy(FLOAT x, FLOAT y, FLOAT vx, FLOAT vy, FLOAT radius) : Structure(x, y), radius(radius), vx(vx), vy(vy) {}
	FLOAT getvx() { return vx; }
	FLOAT getvy() { return vy; }
	FLOAT getr() { return radius; }
	bool Collision(Structure*);


};

class Wall : public Structure
{
private:
	FLOAT width;
	FLOAT height;
public:
	Wall(FLOAT x, FLOAT y, FLOAT width, FLOAT height) : Structure(x, y), width(width), height(height) {}
	FLOAT getw() { return width; }
	FLOAT geth() { return height; }
};


class DefenceGame
{
private:
	TCHAR ID[15] = {0};
	int Score = 0;
	int HP = 0;
	std::vector<Wall*> wall;
	std::vector<Bullet*> bullet;
	std::vector<Enemy*> enemy;
	Cannon *cannon;

public:
	DefenceGame() {memset(ID, 0, sizeof(TCHAR) * 15); }
	~DefenceGame() { 
		for (int i = 0; i < wall.size(); i++)
			delete wall[i];
		for (int i = 0; i < bullet.size(); i++)
			delete bullet[i];
		for (int i = 0; i < enemy.size(); i++)
			delete enemy[i];
		delete cannon;
	}
	TCHAR* set_ID() { return ID; }
	void ID_Screen(HDC &hdc, RECT &rectview, SIZE &size);
	void Game_Screen(HDC &hdc, RECT &rectview);
	void Record_Screen(HDC &hdc, RECT &rectview, TCHAR name[][15], int *score);
	void Update(RECT);
	int getHP() { return HP; }

	void make_Wall(RECT &rectview, FLOAT width, FLOAT height);
	void DrawWall(HDC hdc);
	void make_Cannon(RECT &rectview, FLOAT radius, FLOAT height);
	void DrawCannon(HDC hdc);
	void MoveCannon(bool);
	void ShootCannon(FLOAT);
	void DrawBullet(HDC hdc, int);
	void make_Enemy(RECT &rectview, FLOAT radius);
	void DrawEnemy(HDC hdc, int);

	void Save(TCHAR (*name)[15], int *score);
};




#endif // !DEFENCE_GAME_H_


