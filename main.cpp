#include<stdio.h>
#include<graphics.h>                 //ͼ�ο�ͷ�ļ�
#include"head.h"                     //�Ǳ�׼��ͷ�ļ�

Color arr[13]=
{
	zero, twoTo1, twoTo2, twoTo3, twoTo4,
		twoTo5, twoTo6, twoTo7, twoTo8, twoTo9,
		twoTo10, twoTo11, back
};//ȫ�ֱ�����ɫ���鶨��

box b[MAX_GRID][MAX_GRID]{};//ȫ���������

bool flag = false;    //ȫ�ֲ����ͱ�����־���壨�����Ϊf һ���ƶ�������ֵΪt ���жϺ����й�λ��

int main()
{
	//����
	//b[3][2].index = 32;

	//��������
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