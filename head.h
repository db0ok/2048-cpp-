#pragma once

#define MAX_GRID 4
#define GRID_WIDTH 100
#define INTERVAL 15
#define WINDOW_WIDTH MAX_GRID*GRID_WIDTH+5*INTERVAL

// 枚举定义
enum Color 
{ // 枚举格子颜色
    zero = RGB(216, 209, 196),     // 0的颜色
    twoTo1 = RGB(238, 228, 218),   // 2的颜色
    twoTo2 = RGB(237, 224, 200),   // 4的颜色
    twoTo3 = RGB(242, 177, 121),   // 8的颜色
    twoTo4 = RGB(245, 149, 99),    // 16的颜色
    twoTo5 = RGB(246, 124, 95),    // 32的颜色
    twoTo6 = RGB(246, 94, 59),     // 64的颜色
    twoTo7 = RGB(242, 177, 121),   // 128的颜色
    twoTo8 = RGB(237, 204, 97),    // 256的颜色
    twoTo9 = RGB(255, 0, 128),     // 512的颜色
    twoTo10 = RGB(145, 0, 72),     // 1024的颜色
    twoTo11 = RGB(242, 17, 158),   // 2048的颜色
    back = RGB(187, 173, 160)      // 背景颜色
};
extern Color arr[13];// 全局变量颜色数组声明

//创建类对象：格子
class box
{
public:
    //这是左上角的坐标
    int x;
    int y;
    //格子的数值
    int index;
};
extern box b[MAX_GRID][MAX_GRID];//全局box类对象b的声明

//判断标志
extern bool flag;

//函数声明
void game_init();
void game_draw();
int twoOrfour();        //随机返回2和4
void putIn();           //放进随机格子里
void game_control();    //键盘控制移动
void judge();           //判断函数

//移动函数
void moveup();          //上移
void movedown();        //下移
void moveleft();        //左移
void moveright();       //右移