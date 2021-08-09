#pragma once
#include<vector>
#include<easyx.h>
#include<conio.h>
#include<time.h>
#include"Bullet.h"
#include"Draw.h"

using namespace std;

#define S 30		//有效单元格缩放比例
#define W 26		//宽
#define H 26		//高

enum DIR
{
	UP=0,DOWN,LEFT,RIGHT
};


class Tank
{
protected:
	int lx;
	int ly;
	int x;
	int y;
	DIR d;
	Bullet* e;
	int speed;
	int bulletspeed;
	int attack;
	int l; //标识符，0为自己，1为敌方
	int HP;
	bool live;
public:
	Tank(int _x, int _y);
	void mkpos()
	{
		Draw::map[x][y] = -1;
		Draw::map[x + 1][y] = -1;
		Draw::map[x][y + 1] = -1;
		Draw::map[x + 1][y + 1] = -1;
	}
	void rmpos()
	{
		Draw::map[x][y] = 0;
		Draw::map[x + 1][y] = 0;
		Draw::map[x][y + 1] = 0;
		Draw::map[x + 1][y + 1] = 0;
	}
	virtual void Draw() = 0;
	virtual void move() = 0;
	virtual void shoot() = 0;
	Bullet* getbullet();
	void setbullet(Bullet* b);
	int getHp(){return HP;}
	void reduceHP();
	void addHP(int x){HP += x;}
	bool is_live();
	int getl()
	{
		return l;
	}
	int getx()
	{
		return x;
	}
	int gety(){return y;}
	bool is_be_hit(int _x,int _y)
	{
		if ((_x == x && _y == y) || (_x == (x + 1) && _y == y) || (_x == x && _y == (y + 1)) || ((_x == (x + 1)) && (_y == (y + 1))))
			return true;
		else
			return false;
	}
	int getbulletspeed(){return bulletspeed;}
	int getattack(){return attack;}
	void addattack() { if(attack<2)attack++; }
};


class OwnTank :public Tank
{
private:
	vector<IMAGE> image;
public:
	OwnTank(int _x, int _y);
	void Draw();
	void move();
	void shoot();

};

class EnemyTank :public Tank
{
protected:
	vector<IMAGE> image;
	int num;
public:
	EnemyTank(int _x, int _y);
	void move();
	void shoot();
	void Draw();
};

class Enemy1 :public EnemyTank
{
public:
	Enemy1(int _x, int _y,DIR _d);
};

class Enemy2 :public EnemyTank
{
public:
	Enemy2(int _x, int _y, DIR _d);
};

class Enemy3 :public EnemyTank
{
public:
	Enemy3(int _x, int _y, DIR _d);
};