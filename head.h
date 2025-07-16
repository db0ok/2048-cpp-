#pragma once

#include <vector>
#include <windows.h>

const int MAX_GRID = 4;
const int GRID_WIDTH = 100;
const int INTERVAL = 15;
const int WINDOW_WIDTH = MAX_GRID * GRID_WIDTH + 5 * INTERVAL;
const int WINDOW_HEIGHT = MAX_GRID * GRID_WIDTH + 5 * INTERVAL + 165;

// 枚举颜色
enum Color
{
    zero = RGB(216, 209, 196),
    twoTo1 = RGB(238, 228, 218),
    twoTo2 = RGB(237, 224, 200),
    twoTo3 = RGB(242, 177, 121),
    twoTo4 = RGB(245, 149, 99),
    twoTo5 = RGB(246, 124, 95),
    twoTo6 = RGB(246, 94, 59),
    twoTo7 = RGB(242, 177, 121),
    twoTo8 = RGB(237, 204, 97),
    twoTo9 = RGB(255, 0, 128),
    twoTo10 = RGB(145, 0, 72),
    twoTo11 = RGB(242, 17, 158),
    back = RGB(187, 173, 160),
    text = RGB(119, 110, 101)
};

// 格子类
class Box 
{
public:
    int x;
    int y;
    int index;
};

class Game
{
public:
    Game();
    void start();
    void init();
    void draw();
    void control();
    void judge();
    bool isGameWon();
    bool isGameOver();
    void updateHighScore();
    void drawScore();
    void BeginScreen();
    void BeginDraw();

private:
    std::vector<std::vector<Box>> b;
    std::vector<Color> arr;
    bool flag;
    int currentScore;
    int highScore;

    int twoOrfour();
    void putIn();

    template<typename Direction>
    void move(Direction dir);
};
