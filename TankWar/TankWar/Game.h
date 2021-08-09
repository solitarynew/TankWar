#pragma once
#include<iostream>
#include<easyx.h>
#include<conio.h>
#include<Windows.h>
#include<vector>
#include <sys/timeb.h>
#include<time.h>
#include"Tank.h"
#include"Draw.h"
#include"Bullet.h"

using namespace std;
extern enum DIR;


class Game
{
private:
	vector<Tank*> t;
	vector<IMAGE> image;
	int HP;
	int record[3];
	bool suspended;
	int suspendednum;
	int baseHP;
	bool p[3];
	int checkpoint;
public:
	Game();
	void exec();
	void movetank();
	void movebullet(int i);
	void is_bullet_tank();
	void killbullet();
	void killtank();
	void drawtank();
	void drawbullet();
	void is_bullet_bullet();
	void is_bullet_steel();
	void drawbar();
	void welcome();
	bool is_tank_pro();
	bool have_pro();
	void moveowntank();
	void gameover();
	void isdead();
	void vectory();
};
