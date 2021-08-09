#pragma once
#include<easyx.h>
#include<conio.h>


//游戏区画布大小调整为780*780
//780=26*30
//每30*30作为一个有效单元
//坦克占用4个单元，墙壁占用一个单元

#define S 30		//有效单元格缩放比例
#define W 26		//宽
#define H 26		//高




class Draw
{
public:
	//0为无建筑，1为木墙，2为铁墙，3为基地，4为海洋
	static int map[W][H];
	//1为炸弹道具,2为时停道具,3为小坦克（增加生命）,4为星星（永久增加攻击力1点）
	static int pro[W][H];
private:
	IMAGE wall;
	IMAGE steel;
	IMAGE base;
	IMAGE bomb;
	IMAGE timer;
	IMAGE water;
	IMAGE mintank;
	IMAGE star;
	int checkpoint;

public:
	Draw(int x);
	void init_image();
	void draw();
	

};
