#ifndef ENABLE_BLEND
#define ENABLE_BLEND 0x00000040
#endif

#ifndef ENABLE_HIGHDPI
#define ENABLE_HIGHDPI 0x00000080
#endif

#include <graphics.h>
#include <cmath>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <ctime>
#include "head.h"

// 方向函数对象

struct Up 
{
    static const bool isVertical = true;
    static const bool isIncreasing = false;
    int next(int i) const { return i - 1; }
    bool isValid(int i) const { return i > 0; }
};

struct Down 
{
    static const bool isVertical = true;
    static const bool isIncreasing = true;
    int next(int i) const { return i + 1; }
    bool isValid(int i) const { return (i < MAX_GRID - 1); }
};

struct Left
{
    static const bool isVertical = false;
    static const bool isIncreasing = false;
    int next(int i) const { return i - 1; }
    bool isValid(int i) const { return i > 0; }
};

struct Right 
{
    static const bool isVertical = false;
    static const bool isIncreasing = true;
    int next(int i) const { return i + 1; }
    bool isValid(int i) const { return i < MAX_GRID - 1; }
};

Game::Game() : flag(false), currentScore(0), highScore(0) 
{
    arr = { zero, twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11, back };
    b.resize(MAX_GRID, std::vector<Box>(MAX_GRID));
}

void Game::start()
{
    std::ifstream inFile("highscore.dat");
    if (inFile) 
    {
        inFile >> highScore;
        inFile.close();
    }

    BeginScreen();

    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT, SHOWCONSOLE | ENABLE_BLEND | ENABLE_HIGHDPI);
    setbkcolor(arr[12]);
    cleardevice();

    // 设置绘图目标为内存缓冲区
    SetWorkingImage(NULL);      // 确保绘制到屏幕
    BeginBatchDraw();           // 开始批量绘制

    init();
    while (1) 
    {
        draw();
        drawScore();
        FlushBatchDraw(); // 刷新批量绘制
        control();
        judge();

        if (isGameOver())
        {
            printf("game over");
            break;
        }
        if (isGameWon()) 
        {
            printf("You Win!");
            break;
        }
        Sleep(10); // 添加短暂延迟减少CPU占用
    }
    EndBatchDraw(); // 结束批量绘制
    getchar();
    closegraph();
}

void Game::init() 
{
    currentScore = 0;

    for (int i = 0; i < MAX_GRID; ++i)
    {
        for (int k = 0; k < MAX_GRID; ++k)
        {
            b[i][k].x = k * GRID_WIDTH + (k + 1) * INTERVAL;
            b[i][k].y = i * GRID_WIDTH + (i + 1) * INTERVAL + 50;
        }
    }
    srand(static_cast<unsigned int>(GetTickCount()));
   
    for (int p = 0; p < 2; ++p) 
    {
        putIn();
    }
}

void Game::draw() 
{
    setfillcolor(back);
    solidrectangle(0, 50, WINDOW_WIDTH, WINDOW_HEIGHT - 100);

    for (int i = 0; i < MAX_GRID; ++i)
    {
        for (int k = 0; k < MAX_GRID; ++k) 
        {
            // 只重绘有变化的格子
            if (b[i][k].index == 0)
            {
                setfillcolor(arr[0]);
            }
            else 
            {
                for (int j = 0; j < 12; ++j)
                {
                    if (std::pow(2, j) == b[i][k].index)
                    {
                        setfillcolor(arr[j]);
                        break; // 找到颜色后立即跳出循环
                    }
                }
            }

            solidrectangle(b[i][k].x, b[i][k].y, b[i][k].x + GRID_WIDTH, b[i][k].y + GRID_WIDTH);

            if (b[i][k].index != 0)
            {
                TCHAR number[5];
                settextcolor(RGB(119, 110, 101));
                settextstyle(60, 0, _T("微软雅黑"));
                setbkmode(TRANSPARENT);
                _stprintf_s(number, _T("%d"), b[i][k].index);

                int textW = textwidth(number);
                int textH = textheight(number);

                int centerX = b[i][k].x + (GRID_WIDTH - textW) / 2;
                int centerY = b[i][k].y + (GRID_WIDTH - textH) / 2;

                outtextxy(centerX, centerY, number);
            }
        }
    }
}

int Game::twoOrfour()
{
    return (rand() % 2 == 1) ? 4 : 2;
}

void Game::putIn()
{
    while (true)
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

void Game::control() 
{
    static DWORD lastInputTime = 0;
    DWORD currentTime = GetTickCount();

    // 添加输入延迟，防止处理过快
    if (currentTime - lastInputTime < 100)
    { // 100毫秒延迟
        return;
    }

    if (_kbhit())
    {
        char key = _getch();
        lastInputTime = currentTime;

        switch (key)
        {
        case 'w': case 'W': case 72:
            move(Up());
            break;
        case 's': case 'S': case 80:
            move(Down());
            break;
        case 'a': case 'A': case 75:
            move(Left());
            break;
        case 'd': case 'D': case 77:
            move(Right());
            break;
        case 'r': case 'R': // 添加重新开始功能
            init();
            break;
        case 27: // ESC键退出
            exit(0);
        }
    }
}

template<typename Direction>
void Game::move(Direction dir)
{
    flag = false;

    // 根据方向确定外层和内层循环
    for (int outer = 0; outer < MAX_GRID; ++outer) 
    {
        // 对于垂直移动(上下)，处理每一列
        // 对于水平移动(左右)，处理每一行
        for (int inner = (dir.isIncreasing ? MAX_GRID - 2 : 1);(dir.isIncreasing ? inner >= 0 : inner < MAX_GRID);(dir.isIncreasing ? inner-- : inner++))
        {

            int i = dir.isVertical ? inner : outer;
            int j = dir.isVertical ? outer : inner;

            if (b[i][j].index == 0) continue;

            int current = dir.isVertical ? i : j;
            int nextPos = dir.next(current);

            while (dir.isValid(current))
            {
                int next_i = dir.isVertical ? nextPos : i;
                int next_j = dir.isVertical ? j : nextPos;

                if (b[next_i][next_j].index == 0)
                {
                    // 移动到空位置
                    b[next_i][next_j].index = b[i][j].index;
                    b[i][j].index = 0;
                    i = next_i;
                    j = next_j;
                    current = nextPos;
                    nextPos = dir.next(current);
                    flag = true;
                }
                else if (b[next_i][next_j].index == b[i][j].index) 
                {
                    // 合并相同数字
                    b[next_i][next_j].index *= 2;
                    b[i][j].index = 0;
                    currentScore += b[next_i][next_j].index;
                    flag = true;
                    break;
                }
                else
                {
                    // 不能移动或合并
                    break;
                }
            }
        }
    }
}
void Game::judge()
{
    if (flag)
    {
        putIn();
        flag = false;
        updateHighScore();
    }
}

bool Game::isGameWon()
{
    for (int i = 0; i < MAX_GRID; ++i) 
    {
        for (int j = 0; j < MAX_GRID; ++j)
        {
            if (b[i][j].index == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool Game::isGameOver()
{
    // 检查是否有空格
    for (int i = 0; i < MAX_GRID; ++i)
    {
        for (int j = 0; j < MAX_GRID; ++j) 
        {
            if (b[i][j].index == 0) 
            {
                return false;
            }
        }
    }

    // 检查是否有可合并的相邻格子
    for (int i = 0; i < MAX_GRID; ++i)
    {
        for (int j = 0; j < MAX_GRID; ++j) 
        {
            if (i < MAX_GRID - 1 && b[i][j].index == b[i + 1][j].index)
            {
                return false;
            }
            if (j < MAX_GRID - 1 && b[i][j].index == b[i][j + 1].index)
            {
                return false;
            }
        }
    }

    return true;
}

void Game::updateHighScore()
{
    if (currentScore > highScore)
    {
        highScore = currentScore;
        std::ofstream outFile("highscore.dat");
        if (outFile)
        {
            outFile << highScore;
            outFile.close();
        }
    }
}

void Game::drawScore() 
{
    setfillcolor(back);
    solidrectangle(0, WINDOW_HEIGHT - 100, WINDOW_WIDTH, WINDOW_HEIGHT);

    settextstyle(30, 0, _T("微软雅黑"));
    settextcolor(text);
    setbkmode(TRANSPARENT);

    TCHAR scoreText[50];
    _stprintf_s(scoreText, _T("当前得分: %d"), currentScore);
    outtextxy(INTERVAL, WINDOW_HEIGHT - 80, scoreText);

    _stprintf_s(scoreText, _T("最高分: %d"), highScore);
    outtextxy(WINDOW_WIDTH / 2 + INTERVAL, WINDOW_HEIGHT - 80, scoreText);
}

void  Game::BeginDraw()
{
    int num = highScore;
    TCHAR highscore0[50];
    _stprintf_s(highscore0, _T("%d"), num);
    setbkcolor(back);
    cleardevice();
    settextcolor(RGB(119, 110, 101));
    settextstyle(50, 0, _T("΢���ź�"));
    setbkmode(TRANSPARENT);//设置背景模式透明
    outtextxy(GRID_WIDTH * 2, GRID_WIDTH / 2, _T("2048"));
    outtextxy(GRID_WIDTH / 4 * 3, GRID_WIDTH * 2, _T("最高分:"));
    outtextxy(GRID_WIDTH / 2 * 5, GRID_WIDTH * 2, highscore0);
    settextstyle(25, 0, _T("΢���ź�"));
    outtextxy(GRID_WIDTH * 3 / 2, GRID_WIDTH * 3, _T("按f键开始游戏"));
}
void Game::BeginScreen()
{

    initgraph(MAX_GRID * GRID_WIDTH + 5 * INTERVAL, MAX_GRID * GRID_WIDTH + 5 * INTERVAL);
    BeginDraw();
    while (1)
    {

        char a = _getch();
        if (a == 'f' || a == 'F')
        {
            closegraph();
            break;
        }
    }

}
