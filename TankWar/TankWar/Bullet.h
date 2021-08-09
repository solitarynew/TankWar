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
	DIR d;		//���ڵ�Ϊ����ռ��60*30��Ϊ����ռ��30*60
	int l;		//��ʶ����0Ϊ�Լ����ڵ���1Ϊ�з����ڵ�
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