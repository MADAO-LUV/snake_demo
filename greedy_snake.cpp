#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define SNAKE_NUM 500 //�궨�� �ߵ�������
enum DIR // ö�ٳ�ʼ������---��
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
//�ߵĽṹ
struct Snake
{
	int size;//�ߵĳ���
	int dir;//�ߵķ���
	int speed;//�ƶ��ٶ�
	POINT coor[SNAKE_NUM];//���� 
}snake;

//ʳ��ṹ
struct Food
{
	int x;
	int y;
	int r;  //ʳ���С
	bool flag; //ʳ���Ƿ񱻳�
	DWORD color; //ʳ����ɫ
}food;


//���ݵĳ�ʼ��
void GameInit()
{

	//init ��ʼ�� graph ͼ�δ���
	initgraph(640, 480);
	//������������� GetTickCount ��ȡϵͳ�������������������ĺ�����
	srand(GetTickCount());
	//��ʼ���� һ��ʼ����3��
	snake.size = 3;
	snake.speed = 5;
	snake.dir = RIGHT;
	//ѭ��
	for (int i = 0; i < snake.size;i++) {
		snake.coor[i].x = 40 - 10*i;
		snake.coor[i].y = 10;
	}

	//��ʼ��ʳ��;rand()�������һ�����������û��������������ӣ�ÿ�β����Ķ��ǹ̶�������
	//���������������Ҫͷ�ļ�stdlib.h һ���ʱ����Ϊ���ӣ�ʱ���ڱ仯
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}

//������
void GameDraw()
{
	//˫�����ͼ----��ԭ���ǻῨƵ
	//���ñ�����ɫ
	setbkcolor(RGB(28, 115, 119));
	cleardevice();//��ջ�ͼ�豸
	//������
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);//�뾶Ϊ5
	}
	//����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}

//�ƶ���
void snakemove()
{
	//�ƶ���ʲô�����ı䣻����ı�
	for (int i = snake.size; i > 0 ; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	//�ƶ���ʲô�����ı�
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y+10 <= 0) 
		{
			snake.coor[0].y = 640;
		}//����������ı߽�
		break;
	}
	switch (snake.dir)
	{
	case DOWN:
		snake.coor[0].y+=snake.speed;
		if (snake.coor[0].y - 10 >= 640) {
			snake.coor[0].y = 0;
		}
		break;
	}
	switch (snake.dir)
	{
	case LEFT:
		snake.coor[0].x-=snake.speed;
		if (snake.coor[0].x + 10 <= 0) {
			snake.coor[0].x = 640;
 		}
		break;
	}
	switch (snake.dir)
	{
	case RIGHT:
		snake.coor[0].x+=snake.speed;
		if (snake.coor[0].x - 10 >= 640) {
			snake.coor[0].x = 0;
 		}
		break;
	}
	
}

//ͨ����������
void keyControl()
{
	//�ж����ް���
	if (_kbhit()) //����Ƿ��а���
	{
		//72 80 75 77 �������Ҽ�ֵ
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			//�ı䷽��
			if (snake.dir != DOWN) {
				snake.dir = UP;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != UP) {
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT) {
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT) {
				snake.dir = RIGHT;
			}
			break;
		}
	}
}
void EatFood()
{
	if (snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r
		&& snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag){
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
	/*
	���Լ�һ����������һ��ʳ���n��
	*/
}

//��Ϸ��ͣ  ������ѭ����Ϊ��Ϸ��ͣ
void stop()
{
	if (_kbhit() && _getch() == ' ')
	{
			while (1)
			{
				if (_getch() == ' ')
				{
					break;
				}
			}
	}
}



int main()
{
	//�����������ã����ֳ�ʼ�����
	GameInit();

	//��ֹ����
	while (1)
	{
		GameDraw();
		snakemove();
		stop();
		keyControl();
		EatFood();
		Sleep(30);//̫���ˣ��ӳ�
	}
	return 0;
}