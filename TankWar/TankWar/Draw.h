#pragma once
#include<easyx.h>
#include<conio.h>


//��Ϸ��������С����Ϊ780*780
//780=26*30
//ÿ30*30��Ϊһ����Ч��Ԫ
//̹��ռ��4����Ԫ��ǽ��ռ��һ����Ԫ

#define S 30		//��Ч��Ԫ�����ű���
#define W 26		//��
#define H 26		//��




class Draw
{
public:
	//0Ϊ�޽�����1Ϊľǽ��2Ϊ��ǽ��3Ϊ���أ�4Ϊ����
	static int map[W][H];
	//1Ϊը������,2Ϊʱͣ����,3ΪС̹�ˣ�����������,4Ϊ���ǣ��������ӹ�����1�㣩
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
