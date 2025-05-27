#pragma once

#define MAX_GRID 4
#define GRID_WIDTH 100
#define INTERVAL 15
#define WINDOW_WIDTH MAX_GRID*GRID_WIDTH+5*INTERVAL

// ö�ٶ���
enum Color 
{ // ö�ٸ�����ɫ
    zero = RGB(216, 209, 196),     // 0����ɫ
    twoTo1 = RGB(238, 228, 218),   // 2����ɫ
    twoTo2 = RGB(237, 224, 200),   // 4����ɫ
    twoTo3 = RGB(242, 177, 121),   // 8����ɫ
    twoTo4 = RGB(245, 149, 99),    // 16����ɫ
    twoTo5 = RGB(246, 124, 95),    // 32����ɫ
    twoTo6 = RGB(246, 94, 59),     // 64����ɫ
    twoTo7 = RGB(242, 177, 121),   // 128����ɫ
    twoTo8 = RGB(237, 204, 97),    // 256����ɫ
    twoTo9 = RGB(255, 0, 128),     // 512����ɫ
    twoTo10 = RGB(145, 0, 72),     // 1024����ɫ
    twoTo11 = RGB(242, 17, 158),   // 2048����ɫ
    back = RGB(187, 173, 160)      // ������ɫ
};
extern Color arr[13];// ȫ�ֱ�����ɫ��������

//��������󣺸���
class box
{
public:
    //�������Ͻǵ�����
    int x;
    int y;
    //���ӵ���ֵ
    int index;
};
extern box b[MAX_GRID][MAX_GRID];//ȫ��box�����b������

//�жϱ�־
extern bool flag;

//��������
void game_init();
void game_draw();
int twoOrfour();        //�������2��4
void putIn();           //�Ž����������
void game_control();    //���̿����ƶ�
void judge();           //�жϺ���

//�ƶ�����
void moveup();          //����
void movedown();        //����
void moveleft();        //����
void moveright();       //����