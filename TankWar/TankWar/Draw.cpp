#include "Draw.h"


int data1[W][H] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},		//1
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},		//5
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},		//10
	{0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1},
	{0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,3,3},
	{0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,3,3},
	{0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1},		//15
	{0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0},		//20
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},		
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},		//25
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0}
};
					
int data2[W][H] = {
	{0,0,0,2,2,2,1,1,1,0,0,0,1,1,0,0,4,4,0,0,0,0,1,1,1,0},		//1
	{0,0,0,2,2,2,1,1,1,0,0,0,1,1,0,0,4,4,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,4,4,0,0,0,0,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,4,4,0,0,0,0,1,1,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,4,4,0,0,0,0,1,0,0,0},		//5
	{0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,4,4,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{1,1,1,1,0,0,1,1,1,0,4,4,4,4,4,4,4,4,0,1,1,1,0,0,0,0},
	{1,1,1,1,0,0,1,1,1,0,4,4,4,4,4,4,4,4,0,1,1,1,0,0,0,0},		//10
	{1,1,0,0,0,0,0,0,0,0,4,4,1,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,4,4,1,1,0,0,0,0,0,0,1,0,0,1,1,1},
	{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,2,2,0,0,1,0,0,1,3,3},
	{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,2,2,0,0,1,0,0,1,3,3},
	{0,0,0,0,0,0,1,1,0,0,4,4,1,1,0,0,0,0,0,0,1,0,0,1,1,1},		//15
	{0,0,0,0,0,0,1,1,0,0,4,4,1,1,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,2,0,0,0,0,0,0,0,4,4,1,1,0,0,1,1,0,0,1,1,0,0,0,0},
	{0,0,2,0,0,0,0,0,0,0,4,4,0,0,0,0,1,1,0,0,1,1,0,0,0,0},
	{0,0,2,0,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
	{0,0,2,0,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,1,1,0,0,0},		//20
	{0,0,2,2,0,0,4,4,0,0,0,0,0,0,2,2,2,2,2,2,0,0,1,1,0,0},
	{0,0,2,2,0,0,4,4,0,0,0,0,0,0,2,2,0,0,0,0,0,0,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,4,4,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0},		//25
	{0,0,0,0,0,0,4,4,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0}
};

int data3[W][H]= {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,1,1,0,0,1,1,0,0},		//1
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,4,4,0,0,1,1,0,0,4,4,0,0,1,1,0,0,0,0,0,0},
	{0,0,1,1,0,0,4,4,0,0,1,1,0,0,4,4,0,0,1,1,0,0,0,0,0,0},
	{0,0,1,1,0,0,4,4,0,2,1,1,0,0,4,4,0,0,1,1,1,1,0,0,0,0},		//5
	{0,0,1,1,0,0,4,4,0,2,1,1,0,0,4,4,0,0,1,1,1,1,0,0,0,0},
	{0,0,1,1,0,0,4,4,0,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,4,4,0,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,4,4,0,2,1,1,2,2,4,4,0,0,0,0,2,0,0,0,0,0},
	{0,0,0,1,1,1,4,4,0,2,1,1,2,2,4,4,0,0,0,0,2,0,0,0,0,0},		//10
	{0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,1,1,0,0,2,0,0,0,0,0},
	{0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,1,1,0,0,2,0,0,1,1,1},
	{0,0,0,1,1,0,0,0,0,0,4,4,0,0,1,1,2,0,0,0,0,0,0,1,3,3},
	{0,0,0,1,1,0,0,0,0,0,4,4,0,0,1,1,2,0,0,0,0,0,0,1,3,3},
	{1,1,0,0,0,0,1,1,1,1,4,4,0,0,1,1,2,0,0,0,0,0,0,1,1,1},		//15
	{1,1,0,0,0,0,1,1,1,1,4,4,0,0,1,1,2,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,2,2,4,4,4,4,4,4,4,4,0,0,1,1,1,1,0,0},
	{1,1,1,1,0,0,0,0,2,2,4,4,4,4,4,4,4,4,0,0,1,1,1,1,0,0},		//20
	{0,0,0,0,0,0,0,0,2,2,1,1,2,0,0,0,4,4,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,1,2,0,0,0,4,4,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,4,4,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,4,4,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},		//25
	{0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0}
};

//????????????x,y????????????Draw::map[x][y]
//0-????????1-??????????2-????,3-????,4-????
int Draw::map[W][H] ;
int Draw::pro[W][H];
Draw::Draw(int x):checkpoint(x)

{
	if (checkpoint == 1)
	{
		for (int i = 0; i < W; i++)
			for (int j = 0; j < H; j++)
				Draw::map[i][j] = data1[i][j];
		for (int i = 0; i < W; i++)
			for (int j = 0; j < H; j++)
				Draw::pro[i][j] = 0;
	}
	else if(checkpoint==2)
	{
		for (int i = 0; i < W; i++)
			for (int j = 0; j < H; j++)
				Draw::map[i][j] = data2[i][j];
		for (int i = 0; i < W; i++)
			for (int j = 0; j < H; j++)
				Draw::pro[i][j] = 0;
	}
	else if (checkpoint == 3)
	{
		for (int i = 0; i < W; i++)
			for (int j = 0; j < H; j++)
				Draw::map[i][j] = data3[i][j];
		for (int i = 0; i < W; i++)
			for (int j = 0; j < H; j++)
				Draw::pro[i][j] = 0;
	}

	init_image();
}


void Draw::init_image()
{
	loadimage(&wall, _T("img//wall.gif"), 30, 30);
	loadimage(&steel, _T("img//steel.gif"), 30, 30);
	loadimage(&base, _T("img//base.jpg"), 60, 60);
	loadimage(&bomb, _T("img//bomb.gif"), 30, 30);
	loadimage(&timer, _T("img//timer.gif"), 30, 30);
	loadimage(&water, _T("img//water.gif"), 30, 30);
	loadimage(&mintank, _T("img//mintank.gif"), 30, 30);
	loadimage(&star, _T("img//star.gif"), 30, 30);
}

void Draw::draw()
{


	for(int i=0;i<W;i++)
		for (int j = 0; j < H; j++)
		{
			if (Draw::map[i][j] == 1)
			{
				putimage(i * S, j * S, &wall);
			}
			else if (Draw::map[i][j] == 2)
			{
				putimage(i * S, j * S, &steel);
			}
			else if (Draw::map[i][j] == 4)
			{
				putimage(i * S, j * S, &water);
			}
			else if (Draw::map[i][j] == 3)
			{
				if (i == H - 1)
					continue;
				if (i == W - 1)
					continue;
				if (Draw::map[i][j + 1] == 3 && Draw::map[i + 1][j] == 3 && Draw::map[i + 1][j + 1] == 3)
					putimage(i * S, j * S, &base);
			}
		}

	for (int i = 0; i < W; i++)
		for (int j = 0; j < H; j++)
		{
			if (Draw::pro[i][j] == 1)
			{
				putimage(i * S, j * S, &bomb);
			}
			else if(Draw::pro[i][j] == 2)
			{ 
				putimage(i * S, j * S, &timer);
			}
			else if (Draw::pro[i][j] == 3)
			{
				putimage(i * S, j * S, &mintank);
			}
			else if (Draw::pro[i][j] == 4)
			{
				putimage(i * S, j * S, &star);
			}
		}
}

