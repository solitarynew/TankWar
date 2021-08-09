#pragma once
#include<vector>
#include<iostream>
#include<easyx.h>
#include"Draw.h"

using namespace std;
enum DIR ;

#define S 30
#define W 26
#define H 26

class Bullet
{
private:
	int lx;
	int ly;
	int x;
	int y;
	DIR d;		//若炮弹为横向，占据60*30，为纵向，占据30*60
	int l;		//标识符，0为自己的炮弹，1为敌方的炮弹
	bool live;
	vector<IMAGE> image;
	
public:
	Bullet(int _x,int _y,DIR d,int _l);
	void Draw();
	void move();
	DIR getdir();
	bool is_live();
	int getl();
	int getx();
	int gety();
};