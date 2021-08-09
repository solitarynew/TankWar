#include "Bullet.h"

Bullet::Bullet(int _x, int _y, DIR _d,int _l):x(_x),y(_y),d(_d),l(_l),live(true),lx(_x),ly(_y)
{
	IMAGE i;
	loadimage(&i, _T("img//tankmissile.gif"),30,30);
	image.push_back(i);
	loadimage(&i, _T("img//enemymissile.gif"),30,30);
	image.push_back(i);
	//ÅÐ¶Ï×Óµ¯ÊÇ·ñ»÷ÖÐ½¨Öþ 
	if (d == 0 || d == 1)
	{
		if (Draw::map[x][y] == 1) { Draw::map[x][y] = 0; live = false; }
		if (Draw::map[x + 1][y] == 1) { Draw::map[x + 1][y] = 0; live = false; }
		if (Draw::map[x][y] == 2) { live = false; }
		if (Draw::map[x + 1][y] == 2) { live = false; }
	}
	else
	{
		if (Draw::map[x][y] == 1) { Draw::map[x][y] = 0; live = false; }
		if (Draw::map[x][y + 1] == 1) { Draw::map[x][y + 1] = 0; live = false; }
		if (Draw::map[x][y] == 2) { live = false; }
		if (Draw::map[x][y + 1] == 2) { live = false; }
	}

}

void Bullet::Draw()
{
	if (d == 0 || d == 1)
	{
		//if (Draw::map[x][y] == 5 || Draw::map[x + 1][y] == 5)
		//	return;
		clearrectangle(lx * S + S / 2, ly * S, lx * S + S / 2 + S, ly * S + S);
		putimage(x * S + S / 2, y * S, &(image[l]));
	}
	else
	{
		//if (Draw::map[x][y] == 5 || Draw::map[x][y+1] == 5)
		//	return;
		clearrectangle(lx * S, ly * S+S/2, lx * S  + S, ly * S+S/2 + S);
		putimage(x * S , y * S+S/2, &(image[l]));
	}
}

void Bullet::move()
{
	lx = x;
	ly = y;
	//ÅÐ¶Ï×Óµ¯ÊÇ·ñ×²Ç½
	if (d == 0 && y == 0) { live = false; return; }
	if (d == 1 && y == H - 1) { live = false; return; }
	if (d == 2 && x == 0) { live = false; return; }
	if (d == 3 && x == W - 1) { live = false; return; }

	if (!live) { return; }

	switch (d)
	{
	case 0:if(y>0)y--; break;
	case 1:if(y<H-1)y++; break;
	case 2:if(x>0)x--; break;
	case 3:if(x<W-1)x++; break;
	}

	//ÅÐ¶Ï×Óµ¯ÊÇ·ñ»÷ÖÐ½¨Öþ 
	if (d == 0 || d == 1)
	{
		if (Draw::map[x][y] == 1) { Draw::map[x][y] = 0; live = false; }
		if (Draw::map[x + 1][y] == 1) { Draw::map[x + 1][y] = 0; live = false; }
		if (Draw::map[x][y] == 4) { live = false; }
		if (Draw::map[x + 1][y] == 4) { live = false; }
		//if (Draw::map[x][y] == 2) { live = false; }
		//if (Draw::map[x + 1][y] == 2) { live = false; }
	}
	else
	{
		if (Draw::map[x][y] == 1) { Draw::map[x][y] = 0; live = false; }
		if (Draw::map[x][y + 1] == 1) { Draw::map[x][y + 1] = 0; live = false; }
		if (Draw::map[x][y] == 4) { live = false; }
		if (Draw::map[x][y + 1] == 4) { live = false; }
		//if (Draw::map[x][y] == 2) { live = false; }
		//if (Draw::map[x][y + 1] == 2) { live = false; }
	}
	if (!live) { return; }
}

DIR Bullet::getdir()
{
	return d;
}

bool Bullet::is_live()
{
	return live;
}

int Bullet::getl()
{
	return l;
}

int Bullet::getx()
{
	return x;
}

int Bullet::gety()
{
	return y;
}




