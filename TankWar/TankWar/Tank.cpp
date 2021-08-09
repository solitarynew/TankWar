#include "Tank.h"

Tank::Tank(int _x, int _y) :x(_x),lx(_x), y(_y),ly(_y) ,d(UP),e(NULL),HP(1),live(true),speed(30),bulletspeed(2),attack(1) { mkpos(); }

Bullet* Tank::getbullet()
{
	return e;
}

void Tank::setbullet(Bullet* b)
{
	e = b;
}

void Tank::reduceHP()
{
	HP--;
}
bool Tank::is_live()
{
	if (HP <=0)
		live = false;
	return live;
}

bool access_move_y(int i, int j)
{
	if (Draw::map[i][j] == 0&& Draw::map[i + 1][j] == 0)
		return true;
	else
		return false;
}

bool access_move_x(int i, int j)
{
	if (Draw::map[i][j] == 0 && Draw::map[i][j + 1] == 0)
		return true;
	else
		return false;
}

OwnTank::OwnTank(int _x, int _y):Tank(_x,_y)
{
	HP = 10;
	l = 0;
	IMAGE i;
	//载入四个图像，分别为上下左右
	loadimage(&i, _T("img//p1tankU.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//p1tankD.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//p1tankL.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//p1tankR.gif"));
	image.push_back(i);


}

void OwnTank::Draw()
{
//	if (d == 0)
//	{
//		for (int i = 0; i < (ly - y) * S; i++)
//		{
//			putimage(lx * S, ly * S-i, &(image[d]));
//			Sleep(1);
//			clearrectangle(lx * S, ly * S - i, lx * S + 2 * S, ly * S - i + 2 * S);
//		}
//;
//	}
//	if (d == 1)
//	{
//		for (int i = 0; i < (y - ly) * S; i++)
//		{
//			putimage(lx * S, ly * S + i, &(image[d]));
//			Sleep(1);
//			clearrectangle(lx * S, ly * S + i, lx * S + 2 * S, ly * S + i + 2 * S);
//		}
//	}
//	if (d == 2)
//	{
//		for (int i = 0; i < (lx - x) * S; i++)
//		{
//			putimage(lx * S-i, ly * S, &(image[d]));
//			Sleep(1);
//			clearrectangle(lx * S-i, ly * S, lx * S-i + 2 * S, ly * S + 2 * S);
//		}
//	}
//	if (d == 3)
//	{
//		for (int i = 0; i < (x - lx) * S; i++)
//		{
//			putimage(lx * S + i, ly * S, &(image[d]));
//			Sleep(1);
//			clearrectangle(lx * S + i, ly * S, lx * S + i + 2 * S, ly * S + 2 * S);
//		}
//	}

	clearrectangle(lx * S, ly * S, lx * S + 2 * S, ly * S + 2 * S);

	putimage(x * S, y * S, &(image[d]));
	
}

void OwnTank::move()
{
	lx = x;
	ly = y;
	char ch;
	if (_kbhit())
	{

		ch = _getch();
		switch (ch)
		{
		case 'w':
			if (d == UP) { if (y > 0 && access_move_y(x, y - 1)) { rmpos(); y--; mkpos(); } }
			else { d = UP; }
			break;
		case 's':
			if (d == DOWN) { if (y < H - 2 && access_move_y(x, y + 2)) { rmpos(); y++; mkpos(); } }
			else { d = DOWN; }
			break;
		case 'a':
			if (d == LEFT) { if (x > 0 && access_move_x(x - 1, y)) { rmpos(); x--; mkpos(); } }
			else { d = LEFT; }
			break;
		case 'd':
			if (d == RIGHT) { if (x < W - 2 && access_move_x(x + 2, y)) { rmpos(); x++; mkpos(); } }
			else { d = RIGHT; }
			break;
		case 'j':
			shoot();
			break;
		default:
			break;
			
		}
	}
}

void OwnTank::shoot()
{
	//已有子弹
	if (e != NULL)
		return;
	//所在位置不能发子弹
	if (d == UP && y == 0) { return; }
	if (d == DOWN && y == H - 2) { return; }
	if (d == LEFT && x == 0) { return; }
	if (d == RIGHT && x == W - 2) { return; }
	switch (d)
	{
	case 0:
		e = new Bullet(x, y-1, UP, 0);
		break;
	case 1:
		e = new Bullet(x,y+1, DOWN, 0);
		break;
	case 2:
		e = new Bullet(x-1, y, LEFT, 0);
		break;
	case 3:
		e = new Bullet(x+1, y, RIGHT, 0);
		break;
	}
}

EnemyTank::EnemyTank(int _x, int _y):Tank(_x,_y),num(0)
{
	IMAGE i;
	loadimage(&i, _T("img//enemy1U.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy1D.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy1L.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy1R.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy2U.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy2D.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy2L.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy2R.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy3U.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy3D.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy3L.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy3R.gif"));
	image.push_back(i);
	this->d = DOWN;
}

void EnemyTank::move()
{
	lx = x;
	ly = y;
	num++;
	bool temp = false;
	switch (d)
	{
	case 0:
		if (d == UP) { if (y > 0 && access_move_y(x, y - 1)) { rmpos(); y--; mkpos(); } else temp = true; }
		else{d = UP;}
		break;
	case 1:
		if (d == DOWN) { if (y < H - 2 && access_move_y(x, y + 2)) { rmpos(); y++; mkpos(); } else temp = true; }
		else{d = DOWN;}
		break;
	case 2:
		if (d == LEFT) { if (x > 0 && access_move_x(x - 1, y)) { rmpos(); x--; mkpos(); } else temp = true; }
		else{d = LEFT;}
		break;
	case 3:
		if (d == RIGHT) { if (x < W - 2 && access_move_x(x + 2, y)) { rmpos();x++; mkpos(); } else temp = true; }
		else{d = RIGHT;}
		break;
	default:
		break;
	}
	shoot();
	if ( !temp&&num%20!=0)
	{
		return;
	}
	while (true)
	{
		int a = rand() % 4;
		if (a != d)
		{
			if (a == 0) d = UP;
			if (a == 1) d = DOWN;
			if (a == 2) d = LEFT;
			if (a == 3) d = RIGHT;
			break;
		}
	}
}

Enemy1::Enemy1(int _x, int _y, DIR _d):EnemyTank(_x,_y)
{
	l = 1;
	d = _d;
}

void EnemyTank::Draw()
{
	int index = 0;
	if (HP == 1)
		index = 0;
	else if (HP == 2)
		index = 1;
	else if (HP == 3)
		index = 2;
		

	//if (d == 0)
	//{
	//	for (int i = 0; i < (ly - y) * S; i++)
	//	{
	//		putimage(lx * S, ly * S - i, &(image[d+4*index]));
	//		Sleep(1);
	//		clearrectangle(lx * S, ly * S - i, lx * S + 2 * S, ly * S - i + 2 * S);
	//	}
	//	;
	//}
	//if (d == 1)
	//{
	//	for (int i = 0; i < (y - ly) * S; i++)
	//	{
	//		putimage(lx * S, ly * S + i, &(image[d + 4 * index]));
	//		Sleep(1);
	//		clearrectangle(lx * S, ly * S + i, lx * S + 2 * S, ly * S + i + 2 * S);
	//	}
	//}
	//if (d == 2)
	//{
	//	for (int i = 0; i < (lx - x) * S; i++)
	//	{
	//		putimage(lx * S - i, ly * S, &(image[d + 4 * index]));
	//		Sleep(1);
	//		clearrectangle(lx * S - i, ly * S, lx * S - i + 2 * S, ly * S + 2 * S);
	//	}
	//}
	//if (d == 3)
	//{
	//	for (int i = 0; i < (x - lx) * S; i++)
	//	{
	//		putimage(lx * S + i, ly * S, &(image[d + 4 * index]));
	//		Sleep(1);
	//		clearrectangle(lx * S + i, ly * S, lx * S + i + 2 * S, ly * S + 2 * S);
	//	}
	//}

	clearrectangle(lx * S , ly * S, lx * S  + 2 * S, ly * S + 2 * S);
	putimage(x * S, y * S, &(image[d+4*index]));
}

void EnemyTank::shoot()
{
	//已有子弹
	if (e != NULL)
		return;
	//所在位置不能发子弹
	if (d == UP && y == 0) { return; }
	if (d == DOWN && y == H - 2) { return; }
	if (d == LEFT && x == 0) { return; }
	if (d == RIGHT && x == W - 2) { return; }
	switch (d)
	{
	case 0:
		e = new Bullet(x, y - 1, UP, 1);
		break;
	case 1:
		e = new Bullet(x, y + 1, DOWN, 1);
		break;
	case 2:
		e = new Bullet(x - 1, y, LEFT, 1);
		break;
	case 3:
		e = new Bullet(x + 1, y, RIGHT, 1);
		break;
	}
}

Enemy2::Enemy2(int _x, int _y, DIR _d):EnemyTank(_x,_y)
{
	l = 1;
	HP = 2;
	d = _d;
	bulletspeed = 5;
}

Enemy3::Enemy3(int _x, int _y, DIR _d) :EnemyTank(_x,_y)
{
	l = 1;
	HP = 3;
	d = _d;
}


