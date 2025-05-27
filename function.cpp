#include<graphics.h>     //ͼ�ο�ͷ�ļ�
#include<cmath>
#include<stdio.h>
#include<conio.h>
#include"head.h"

void game_init()
{
    //�����������
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			b[i][k].x = k * GRID_WIDTH + (k + 1) * INTERVAL;
            b[i][k].y = i * GRID_WIDTH + (i + 1) * INTERVAL;
		}
	}
    srand(GetTickCount());//���������(����ʱ��)
    //��������������ֵĸ���
    for (int p = 0; p < 2; p++)
        putIn();
}

void game_draw()
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        for (int k = 0; k < MAX_GRID; k++)
        {
            //�жϸ������ֵ�Ƕ���
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
            solidrectangle(b[i][k].x, b[i][k].y, b[i][k].x + GRID_WIDTH, b[i][k].y + GRID_WIDTH);//��������ɫ
            if (b[i][k].index != 0)        
            {
                TCHAR number[5];
                settextcolor(RGB(119, 110, 101));
                settextstyle(60, 0,_T("΢���ź�"));
                setbkmode(TRANSPARENT);                               //����ģʽ͸��
                // ��ʽ��Ҫ��ʾ������
                _stprintf_s(number, _T("%d"), b[i][k].index);

                // �������ֳߴ�
                int textW = textwidth(number);   // ��ȡ���ֿ��
                int textH = textheight(number);  // ��ȡ���ָ߶�

                // ����������꣨����������
                int centerX = b[i][k].x + (GRID_WIDTH - textW) / 2;  // ˮƽ����
                int centerY = b[i][k].y +(GRID_WIDTH - textH) / 2; // ��ֱ����

                // ������֣�ע�⣺outtextxy���������������½����꣩
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
    {                                            // ����ÿһ��
        int temp = 0;                            // ��ǰ�пɺϲ�/�ƶ���λ�ã�����ʼ��
        for (int begin = 1; begin < MAX_GRID; begin++)
        {                                        // �ӵ�2�п�ʼ���Ҽ��
            if (b[i][begin].index != 0)
            {                                    // ��ǰԪ�طǿ�
                if (b[i][temp].index == 0)
                {                                // Ŀ��λ��Ϊ�գ�ֱ���ƶ�
                    b[i][temp].index = b[i][begin].index;
                    b[i][begin].index = 0;
                }
                else if (b[i][temp].index == b[i][begin].index) 
                {                                // �ɺϲ�
                    b[i][temp].index += b[i][begin].index;
                    b[i][begin].index = 0;
                }
                else 
                {                                // ���ܺϲ����ƶ���temp+1��λ��
                    b[i][temp + 1].index = b[i][begin].index;
                    if (temp + 1 != begin) 
                    {                            // ����ԭ�ظ���
                        b[i][begin].index = 0;
                    }
                                                // ���¿ɲ���λ��
                }
                temp++;
                flag = true;                    // ���״̬�仯
            }
        }
    }
}

void movedown()
{
    for (int i = 0; i < MAX_GRID; i++)
    {
        int temp = MAX_GRID - 1;                    // ��ǰ�пɺϲ�/�ƶ���λ�ã��ӵײ���ʼ��
        for (int begin = MAX_GRID - 2; begin >= 0; begin--)
        {                                           // �ӵ�����2�����ϼ��
            if (b[begin][i].index != 0)
            {                                       // ��ǰԪ�طǿ�
                if (b[temp][i].index == 0)
                {                                   // Ŀ��λ��Ϊ�գ�ֱ���ƶ�
                    b[temp][i].index = b[begin][i].index;
                    b[begin][i].index = 0;
                }
                else if (b[temp][i].index == b[begin][i].index)
                {                                   // �ɺϲ�
                    b[temp][i].index += b[begin][i].index;
                    b[begin][i].index = 0;
                }
                else
                {                                   // ���ܺϲ����ƶ���temp-1��λ��
                    b[temp - 1][i].index = b[begin][i].index;
                    if (temp - 1 != begin)
                    {                               // ����ԭ�ظ���
                        b[begin][i].index = 0;
                    }
                                                    // ���¿ɲ���λ��
                }
                temp--;
                flag = true;                        // ���״̬�仯
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