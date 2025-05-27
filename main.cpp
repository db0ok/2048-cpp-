#include<stdio.h>
#include<graphics.h>                 //图形库头文件
#include"head.h"                     //非标准库头文件

Color arr[13]=
{
	zero, twoTo1, twoTo2, twoTo3, twoTo4,
		twoTo5, twoTo6, twoTo7, twoTo8, twoTo9,
		twoTo10, twoTo11, back
};//全局变量颜色数组定义

box b[MAX_GRID][MAX_GRID]{};//全局类对象定义

bool flag = false;    //全局布尔型变量标志定义（最初设为f 一次移动发生后赋值为t 在判断函数中归位）

int main()
{
	//测试
	//b[3][2].index = 32;

	//创建窗口
	initgraph(WINDOW_WIDTH, WINDOW_WIDTH,1);
	setbkcolor(arr[12]);
	cleardevice();
	
	game_init();
	while (1)
	{
		game_draw();
		game_control();
		judge();
	}
	getchar();
	return 0;
}