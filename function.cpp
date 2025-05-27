#include<graphics.h>     //图形库头文件
#include<cmath>
#include<stdio.h>
#include<conio.h>
#include"head.h"

void game_init()
{
    //计算格子坐标
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			b[i][k].x = k * GRID_WIDTH + (k + 1) * INTERVAL;
            b[i][k].y = i * GRID_WIDTH + (i + 1) * INTERVAL;
		}
	}
    srand(GetTickCount());//随机数种子(开机时间)
    //随机生成俩带数字的格子
    for (int p = 0; p < 2; p++)
        putIn();
}

void game_draw()
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        for (int k = 0; k < MAX_GRID; k++)
        {
            //判断格子里的值是多少
            if (b[i][k].index == 0)
                setfillcolor(arr[0]);
            else
            {
                for (int j = 0; j < 12; j++)
                {
                    if (pow(2, j) == b[i][k].index)
                        setfillcolor(arr[j]);
                }
            }
            solidrectangle(b[i][k].x, b[i][k].y, b[i][k].x + GRID_WIDTH, b[i][k].y + GRID_WIDTH);//画格子上色
            if (b[i][k].index != 0)        
            {
                TCHAR number[5];
                settextcolor(RGB(119, 110, 101));
                settextstyle(60, 0,_T("微软雅黑"));
                setbkmode(TRANSPARENT);                               //背景模式透明
                // 格式化要显示的数字
                _stprintf_s(number, _T("%d"), b[i][k].index);

                // 计算文字尺寸
                int textW = textwidth(number);   // 获取文字宽度
                int textH = textheight(number);  // 获取文字高度

                // 计算居中坐标（坐标修正）
                int centerX = b[i][k].x + (GRID_WIDTH - textW) / 2;  // 水平居中
                int centerY = b[i][k].y +(GRID_WIDTH - textH) / 2; // 垂直居中

                // 输出文字（注意：outtextxy的坐标是文字左下角坐标）
                outtextxy(centerX, centerY, number);  
            }  
        }
    }
}
    
int twoOrfour()
{
    if (rand() % 2 == 1)
        return 4;
    else
        return 2;
}

void putIn()
{
    while (1)
    {
        int x = rand() % MAX_GRID;
        int y = rand() % MAX_GRID;

        if (b[x][y].index == 0)
        {
            b[x][y].index = twoOrfour();
            break;
        }
    }
}

void game_control()
{
    char key = _getch();
    switch (key)
    {
    case'w':case'W':case 72:
    {
        moveup();
        printf("up\n");
    }break;
    case's':case'S':case 80:
    {
        movedown();
        printf("down\n");
    }break;
    case'a':case'A':case 75:
    {
        moveleft();
        printf("left\n");
    }break;
    case'd':case'D':case 77:
    {
        moveright();
        printf("right\n");
    }break; 
    }
    
}

void judge()
{
    if (flag)
    {
        putIn();
        flag = false;
    }
}

void moveleft() 
{
    for (int i = 0; i < MAX_GRID; i++)
    {                                            // 遍历每一行
        int temp = 0;                            // 当前行可合并/移动的位置（从左开始）
        for (int begin = 1; begin < MAX_GRID; begin++)
        {                                        // 从第2列开始向右检查
            if (b[i][begin].index != 0)
            {                                    // 当前元素非空
                if (b[i][temp].index == 0)
                {                                // 目标位置为空，直接移动
                    b[i][temp].index = b[i][begin].index;
                    b[i][begin].index = 0;
                }
                else if (b[i][temp].index == b[i][begin].index) 
                {                                // 可合并
                    b[i][temp].index += b[i][begin].index;
                    b[i][begin].index = 0;
                }
                else 
                {                                // 不能合并，移动到temp+1的位置
                    b[i][temp + 1].index = b[i][begin].index;
                    if (temp + 1 != begin) 
                    {                            // 避免原地覆盖
                        b[i][begin].index = 0;
                    }
                                                // 更新可操作位置
                }
                temp++;
                flag = true;                    // 标记状态变化
            }
        }
    }
}

void movedown()
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = MAX_GRID - 1;                    // 当前列可合并/移动的位置（从底部开始）
        for (int begin = MAX_GRID - 2; begin >= 0; begin--)
        {                                           // 从倒数第2行向上检查
            if (b[begin][i].index != 0)
            {                                       // 当前元素非空
                if (b[temp][i].index == 0)
                {                                   // 目标位置为空，直接移动
                    b[temp][i].index = b[begin][i].index;
                    b[begin][i].index = 0;
                }
                else if (b[temp][i].index == b[begin][i].index)
                {                                   // 可合并
                    b[temp][i].index += b[begin][i].index;
                    b[begin][i].index = 0;
                }
                else
                {                                   // 不能合并，移动到temp-1的位置
                    b[temp - 1][i].index = b[begin][i].index;
                    if (temp - 1 != begin)
                    {                               // 避免原地覆盖
                        b[begin][i].index = 0;
                    }
                                                    // 更新可操作位置
                }
                temp--;
                flag = true;                        // 标记状态变化
            }
        }
    }
}

void moveup()
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = 0;
        for (int begin = 1; begin < MAX_GRID; begin++)
        {
            if (b[begin][i].index != 0)
            {
                if (b[temp][i].index == 0)
                {
                    b[temp][i].index = b[begin][i].index;
                    b[begin][i].index = 0;
                }

                else if (b[temp][i].index == b[begin][i].index)
                {
                    b[temp][i].index += b[begin][i].index;
                    b[begin][i].index = 0;
                }

                else
                {
                    b[temp+1][i].index = b[begin][i].index;
                    if (temp + 1 != begin)
                    {
                        b[begin][i].index = 0;
                    }
                }
                temp++;
                flag = true;
            }
        }
    }
}

void moveright()
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = MAX_GRID - 1;
        for (int begin = MAX_GRID - 2; begin >= 0; begin--)
        {
            if (b[i][begin].index != 0)
            {
                if (b[i][temp].index == 0)
                {
                    b[i][temp].index = b[i][begin].index;
                    b[i][begin].index = 0;
                }
                else if (b[i][temp].index == b[i][begin].index)
                {
                    b[i][temp].index += b[i][begin].index;
                    b[i][begin].index = 0;
                }
                else
                {
                    b[i][temp - 1].index = b[i][begin].index;
                    if (temp - 1 != begin)
                    {
                        b[i][begin].index = 0;
                    }
                }
                temp--;
                flag = true;
            }
        }
    }
}