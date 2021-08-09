#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

Game::Game() :suspended(false), suspendednum(0),baseHP(5),checkpoint(1)
{
	p[0] = false;
	p[1] = false;
	p[2] = false;
	initgraph(780+180, 780);
	record[0] = 0;
	record[1] = 0;
	record[2] = 0;
	IMAGE i;
	loadimage(&i, _T("img//enemy1U.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy2U.gif"));
	image.push_back(i);
	loadimage(&i, _T("img//enemy3U.gif"));
	image.push_back(i);
}

void Game::exec()
{
	struct _timeb timebuffer;//定义一个结构
	_ftime(&timebuffer);//初始化timebuffer
	srand(timebuffer.millitm);//timebuffer.millitm获得毫秒

	Draw d(checkpoint);
	OwnTank o(8, 24);
	t.push_back(&o);
	EnemyTank* e=NULL;
	bool temp = true;
	while (true)
	{
		vectory();
		while (t.size() < 4)
		{

			int r = rand() % 10;
			int d = rand() % 3;
			DIR D;
			if (d == 0)D = UP;
			if (d == 1)D = DOWN;
			if (d == 2)D = LEFT;
			if (d == 3)D = RIGHT;
			int x = rand() % (W - 2);
			int y = rand() % (7);

			while ((Draw::map[x][y] != 0 || Draw::map[x + 1][y] != 0 || Draw::map[x][y + 1] != 0 || Draw::map[x + 1][y + 1] != 0))
			{
				x = rand() % (W - 2);
				y = rand() % (7);
			}
			if (r>=0&&r<=5)e = new Enemy1(x, y, D);
			if (r>=6&&r<=8)e = new Enemy2(x, y, D);
			if (r == 9)e = new Enemy3(x, y, D);
			t.push_back(e);
		}
		HP = t[0]->getHp();
		if ((record[0] + record[1] + record[2]) % 10 == 0&& (record[0] + record[1] + record[2])!=0&&temp&& p[(record[0] + record[1] + record[2]) / 10 - 1] == false)
		{	
			int x = rand() % 26;
			int y = rand() % 26;
			while (Draw::map[x][y] != 0)
			{
				x = rand() % 26;
				y = rand() % 26;
			}
			int z = rand() % 4;
			if(z==0)Draw::pro[x][y] = 1;
			if (z == 1)Draw::pro[x][y] = 2;
			if (z == 2)Draw::pro[x][y] = 3;
			if (z == 3)Draw::pro[x][y] = 4;
			temp = false;
			p[(record[0] + record[1] + record[2]) / 10 - 1] = true;
		}
		if (have_pro())temp = is_tank_pro();	
		cleardevice();
		d.draw();
		drawbar();

		if (suspendednum == 30)suspended = false;
		//移动坦克
		if (!suspended)
		{
			movetank();
			suspendednum = 0;
		}
		else
		{
			moveowntank();
			suspendednum++;
		}
		


		for(int i=0;i<5;i++)
		{
		//移动子弹
		movebullet(i);

		//生命结束的子弹设为NULL
		killbullet();

		//子弹是否击中坦克
		is_bullet_tank();

		//生命结束的子弹设为NULL
		killbullet();

		//子弹是否击中子弹
		is_bullet_bullet();

		//生命结束的子弹设为NULL
		killbullet();

		//子弹是否击中铁墙
		is_bullet_steel();

		//生命结束的子弹设为NULL
		killbullet();

		//去除死亡的坦克
		killtank();

		//画出子弹
		drawbullet();

		//自己是否死亡
		isdead();
		}
		//画出坦克
		drawtank();

		Sleep(160);

	}
}

void Game::movetank()
{
	for (int i = 0; i < t.size(); i++)
	{
		//if (typeid(*t[i]) == typeid(Enemy2) || typeid(*t[i]) == typeid(OwnTank))
		//{
		//	t[i]->move();
		//	t[i]->move();
		//	t[i]->move();
		//}
		t[i]->move();
	}
}

void Game::movebullet(int x)
{
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i]->getbullet() != NULL&&t[i]->getbulletspeed()>x)
		{
			t[i]->getbullet()->move();
		}
	}
}

void Game::is_bullet_tank()
{
	for (int i = 0; i < t.size(); i++)
	{
		for (int j = 0; j < t.size(); j++)
		{
			if (t[j]->getbullet() != NULL && (t[j]->getbullet()->getl() != t[i]->getl()))
			{
				int x = t[j]->getbullet()->getx();
				int y = t[j]->getbullet()->gety();
				DIR d = t[j]->getbullet()->getdir();
				if ((d == 0 || d == 1) && (t[i]->is_be_hit(x, y) || t[i]->is_be_hit(x + 1, y)))
				{
					t[j]->setbullet(NULL);
					if(t[j]->getattack()>=2)
						t[i]->reduceHP();
					t[i]->reduceHP();
					continue;
				}
				if ((d == 2 || d == 3) && (t[i]->is_be_hit(x, y) || t[i]->is_be_hit(x, y + 1)))
				{
					t[j]->setbullet(NULL);
					if (t[j]->getattack()>= 2)
						t[i]->reduceHP();
					t[i]->reduceHP();
					continue;
				}

			}
		}
	}
}

void Game::killbullet()
{
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i]->getbullet() != NULL && !t[i]->getbullet()->is_live())
		{
			t[i]->setbullet(NULL);
		}
	}
}

void Game::killtank()
{
	for (auto i = t.begin(); i != t.end();)
	{
		if ((*i)->is_live())
			++i;
		else
		{
			if (typeid(**i) == typeid(Enemy1))
				record[0]++;
			if (typeid(**i) == typeid(Enemy2))
				record[1]++;
			if (typeid(**i) == typeid(Enemy3))
				record[2]++;
			(*i)->rmpos();
			i = t.erase(i);
		}
	}
}

void Game::drawtank()
{
	for (int i = 0; i < t.size(); i++)
	{
		t[i]->Draw();
	}
}

void Game::drawbullet()
{
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i]->getbullet() != NULL)
		{

			t[i]->getbullet()->Draw();
		}
	}
}

void Game::is_bullet_bullet()
{
	for (int i = 0; i < t.size(); i++)
	{
		for (int j = i+1; j < t.size(); j++)
		{
			if (t[i]->getbullet() != NULL && t[j]->getbullet() != NULL&& t[i]->getbullet()->is_live() && t[j]->getbullet()->is_live())
			{
				DIR d1 = t[i]->getbullet()->getdir();
				DIR d2 = t[j]->getbullet()->getdir();
				int x1 = t[i]->getbullet()->getx();
				int y1 = t[i]->getbullet()->gety();
				int x2 = t[j]->getbullet()->getx();
				int y2 = t[j]->getbullet()->gety();
				if (((d1==UP||d1==DOWN)&&(d2==UP||d2==DOWN))||((d1==LEFT||d1==RIGHT)&&(d2==LEFT||d2==RIGHT)))
				{
					if (x1==x2&&y1==y2)
					{
						t[i]->setbullet(NULL);
						t[j]->setbullet(NULL);
					}

				}
				else
				{
					if (d1 == UP || d1 == DOWN)
					{
						if ((x1 == x2 || x1 == (x2 - 1)) && (y1 == y2 || y1 == (y2 + 1)))
						{
							t[i]->setbullet(NULL);
							t[j]->setbullet(NULL);
						}

					}
					else
					{
						if ((x1 == x2 || x1 == (x2 + 1)) && (y1 == y2 || y1 == (y2 - 1)))
						{
							t[i]->setbullet(NULL);
							t[j]->setbullet(NULL);
						}
					}
				}
			}
		}
	}
}

void Game::is_bullet_steel()
{
	for (int i = 0; i < t.size(); i++)
	{
		if (t[i]->getbullet() != NULL&&t[i]->getbullet()->is_live())
		{
			int x = t[i]->getbullet()->getx();
			int y = t[i]->getbullet()->gety();
			DIR d = t[i]->getbullet()->getdir();
			if (d == 0 || d == 1)
			{
				if (Draw::map[x][y] == 2) { if(t[i]->getl() == 1 && t[i]->getHp() >= 3)Draw::map[x][y] = 0; t[i]->setbullet(NULL); }
				if (Draw::map[x + 1][y] == 2) { if (t[i]->getl() == 1 && t[i]->getHp() >= 3) Draw::map[x+1][y] = 0; t[i]->setbullet(NULL);}
			}
			else
			{
				if (Draw::map[x][y] == 2) { if (t[i]->getl() == 1 && t[i]->getHp() >= 3)Draw::map[x][y] = 0; t[i]->setbullet(NULL); }
				if (Draw::map[x][y + 1] == 2) { if (t[i]->getl() == 1 && t[i]->getHp() >= 3) Draw::map[x][y+1] = 0; t[i]->setbullet(NULL); }
			}
			if (d == 0 || d == 1)
			{
				if (Draw::map[x][y] == 3) { baseHP--; t[i]->setbullet(NULL); continue; }
				if (Draw::map[x+1][y] == 3) { baseHP--; t[i]->setbullet(NULL); continue;}
			}
			else
			{
				if (Draw::map[x][y] == 3) { baseHP--; t[i]->setbullet(NULL); continue;}
				if (Draw::map[x][y+1] == 3) { baseHP--; t[i]->setbullet(NULL); continue;}
			}
		}
	}
}

void Game::drawbar()
{
	//打印出生命
	char s[20];
	sprintf(s, "坦克生命：%d", HP);
	outtextxy(780 + 30*2,30*17+15,s);

	//打印出基地生命
	sprintf(s, "基地生命：%d", baseHP);
	outtextxy(780 + 30 * 2, 30 * 18+15, s);
	
	//打印出坦克攻击力
	sprintf(s, "坦克攻击力：%d", t[0]->getattack());
	outtextxy(780 + 30 * 2, 30 * 19+15, s);

	//打印出战绩
	putimage(780 + 30 * 2, 30 * 2, &(image[0]));
	sprintf(s, "已击败:%d", record[0]);
	outtextxy(780 + 30 * 2, 30 * 4+15, s);

	//打印出战绩
	putimage(780 + 30 * 2, 30 * 6, &(image[1]));
	sprintf(s, "已击败:%d", record[1]);
	outtextxy(780 + 30 * 2, 30 * 8 + 15, s);

	//打印出战绩
	putimage(780 + 30 * 2, 30 * 10, &(image[2]));
	sprintf(s, "已击败:%d", record[2]);
	outtextxy(780 + 30 * 2, 30 * 12 + 15, s);

	//打印出战绩
	putimage(780 + 30 * 2, 30 * 10, &(image[2]));
	sprintf(s, "仍需击败:%d", 30-record[0]-record[1]-record[2]);
	outtextxy(780 + 30 * 2, 30 * 16 + 15, s);
}

void Game::welcome()
{
	t.clear();
	baseHP = 5;
	p[0] = false;
	p[1] = false;
	p[2] = false;
	record[0] = 0;
	record[1] = 0;
	record[2] = 0;
	checkpoint = 1;
	cleardevice();
	IMAGE welcome,tip1;
	loadimage(&welcome, _T("img//welcome.png"));
	putimage(90, 200, &welcome);
	loadimage(&tip1, _T("img//tip1.png"));
	putimage(780 + 25, 200, &tip1);


	char s[20];
	sprintf(s, "关卡  %d", checkpoint);
	outtextxy(370 ,500, s);
	outtextxy(320, 530, "上一关");
	outtextxy(400, 530, "下一关");
	while (true)
	{
		MOUSEMSG m;
		if (MouseHit())
		{
			m = GetMouseMsg();
			if (m.mkLButton)
			{
				if (m.x >= (90 + 198) && m.x <= (90 + 198 + 191) && m.y >= (200 + 261) && m.y <= (200 + 261 + 25))
					exec();
				else if (m.x>=(320)&&m.x<=(320+70)&&m.y>=(530)&&m.y<=(530+30))
				{
					if (checkpoint >1)
						checkpoint--;
					sprintf(s, "关卡  %d", checkpoint);
					outtextxy(370, 500, s);
				}
				else if (m.x >= (400) && m.x <= (400 + 70) && m.y >= (530) && m.y <= (530 + 30))
				{
					if (checkpoint < 3)
						checkpoint++;
					sprintf(s, "关卡  %d", checkpoint);
					outtextxy(370, 500, s);
				}
			}	
		}
	}


	
}

bool Game::is_tank_pro()
{
	int x = t[0]->getx();
	int y = t[0]->gety();
	bool temp1 = false;
	bool temp2 = false;
	bool temp3 = false;
	bool temp4 = false;
	if (Draw::pro[x][y] == 1){ Draw::pro[x][y] = 0; temp1 = true; }
	if (Draw::pro[x+1][y] == 1) { Draw::pro[x+1][y] = 0; temp1 = true; }
	if (Draw::pro[x][y+1] == 1) { Draw::pro[x][y+1] = 0; temp1 = true; }
	if (Draw::pro[x+1][y+1] == 1) { Draw::pro[x+1][y+1] = 0; temp1 = true; }
	if (Draw::pro[x][y] == 2) { Draw::pro[x][y] = 0; temp2 = true; }
	if (Draw::pro[x + 1][y] == 2) { Draw::pro[x + 1][y] = 0; temp2 = true; }
	if (Draw::pro[x][y + 1] == 2){ Draw::pro[x][y + 1] = 0; temp2 = true; }
	if (Draw::pro[x + 1][y + 1] ==2){ Draw::pro[x + 1][y + 1] = 0; temp2 = true; }
	if (Draw::pro[x][y] == 3) { Draw::pro[x][y] = 0; temp3 = true; }
	if (Draw::pro[x + 1][y] == 3) { Draw::pro[x + 1][y] = 0; temp3 = true; }
	if (Draw::pro[x][y + 1] == 3) { Draw::pro[x][y + 1] = 0; temp3 = true; }
	if (Draw::pro[x + 1][y + 1] == 3) { Draw::pro[x + 1][y + 1] = 0; temp3 = true; }
	if (Draw::pro[x][y] == 4) { Draw::pro[x][y] = 0; temp4 = true; }
	if (Draw::pro[x + 1][y] == 4) { Draw::pro[x + 1][y] = 0; temp4 = true; }
	if (Draw::pro[x][y + 1] == 4) { Draw::pro[x][y + 1] = 0; temp4 = true; }
	if (Draw::pro[x + 1][y + 1] == 4) { Draw::pro[x + 1][y + 1] = 0; temp4 = true; }
	if (temp1)
	{
		for (int i = 1; i < t.size(); i++)
		{
			t[i]->reduceHP();
			t[i]->reduceHP();
			t[i]->reduceHP();
		}
	}
	if (temp2)
	{
		suspended = true;
	}

	if (temp3)
	{
		t[0]->addHP(3);
	}

	if (temp4)
	{
		t[0]->addattack();
	}
	
	return temp1||temp2||temp3||temp4;
}

bool Game::have_pro()
{
	bool temp = false;
	for(int i=0;i<W;i++)
		for (int j = 0; j < H; j++)
		{
			if (Draw::pro[i][j] !=0)
				temp = true;
		}

	return temp;
}

void Game::moveowntank()
{
	t[0]->move();
}

void Game::gameover()
{
	IMAGE over;
	loadimage(&over, _T("img//over.gif"),300,200);
	cleardevice();
	putimage(350, 200, &over);
	_getch();
	exit(0);
}

void Game::isdead()
{
	if (typeid(*t[0]) != typeid(OwnTank))
	{
		gameover();
	}
	else if (t[0]->getHp()<=0)
	{
		gameover();
	}
	else if (baseHP <= 0)
	{
		gameover();
	}
}

void Game::vectory()
{
	if ((record[0] + record[1] + record[2] >= 30))
	{
		IMAGE v;
		loadimage(&v, _T("img//vectory.jpg"),1000,600);
		cleardevice();
		putimage(0, 100, &v);
		_getch();
		welcome();
	}
}






