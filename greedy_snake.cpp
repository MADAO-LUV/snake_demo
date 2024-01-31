#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#define SNAKE_NUM 500 //宏定义 蛇的最大节数
enum DIR // 枚举初始化方向---蛇
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
//蛇的结构
struct Snake
{
	int size;//蛇的长度
	int dir;//蛇的方向
	int speed;//移动速度
	POINT coor[SNAKE_NUM];//坐标 
}snake;

//食物结构
struct Food
{
	int x;
	int y;
	int r;  //食物大小
	bool flag; //食物是否被吃
	DWORD color; //食物颜色
}food;


//数据的初始化
void GameInit()
{

	//init 初始化 graph 图形窗口
	initgraph(640, 480);
	//设置随机数种子 GetTickCount 获取系统开机，到现在所经过的毫秒数
	srand(GetTickCount());
	//初始化蛇 一开始就有3节
	snake.size = 3;
	snake.speed = 5;
	snake.dir = RIGHT;
	//循环
	for (int i = 0; i < snake.size;i++) {
		snake.coor[i].x = 40 - 10*i;
		snake.coor[i].y = 10;
	}

	//初始化食物;rand()随机生成一个整数，如果没有设置随机数种子，每次产生的都是固定的整数
	//设置随机数种子需要头文件stdlib.h 一般把时间作为种子，时间在变化
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}

//绘制蛇
void GameDraw()
{
	//双缓冲绘图----》原因是会卡频
	//设置背景颜色
	setbkcolor(RGB(28, 115, 119));
	cleardevice();//清空绘图设备
	//绘制蛇
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);//半径为5
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}

//移动蛇
void snakemove()
{
	//移动是什么发生改变；坐标改变
	for (int i = snake.size; i > 0 ; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	//移动是什么发生改变
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y+10 <= 0) 
		{
			snake.coor[0].y = 640;
		}//超出了上面的边界
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

//通过按键操作
void keyControl()
{
	//判断有无按键
	if (_kbhit()) //检测是否有按键
	{
		//72 80 75 77 上下左右键值
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			//改变方向
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
	可以加一个分数，吃一个食物，加n分
	*/
}

//游戏暂停  利用死循环作为游戏暂停
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
	//在主函数调用，出现初始化结果
	GameInit();

	//防止闪退
	while (1)
	{
		GameDraw();
		snakemove();
		stop();
		keyControl();
		EatFood();
		Sleep(30);//太快了，延迟
	}
	return 0;
}