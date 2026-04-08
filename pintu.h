#pragma once
#ifndef PUZZLE_GAME_H
#define PUZZLE_GAME_H

#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

// 音乐功能
#include <mmsystem.h>  // 包含 MCI 头文件
#pragma comment(lib, "winmm.lib")  // 链接库

// 游戏常量定义
#define IMAGE_PATH L"images\\"  // 图片存储路径
#define BLOCK_SIZE 200          // 拼图块尺寸
#define CANVAS_WIDTH 4          // 画布列数
#define CANVAS_HEIGHT 4         // 画布行数
#define MARGIN_X 30             // 水平边距
#define MARGIN_Y 30             // 垂直边距
#define WINDOW_WIDTH (BLOCK_SIZE * CANVAS_WIDTH + MARGIN_X * 2 + 200)  // 右侧预留200像素用于显示时间/步数
#define WINDOW_HEIGHT (BLOCK_SIZE * CANVAS_HEIGHT + MARGIN_Y * 2)      // 窗口总高度
#define LEFT_WINDOW_X 350
#define RIGHT_WINDOW_X 750 
// 游戏全局变量声明
extern IMAGE g_Block[16];       // 拼图块（0-14对应图片，15为空白）
extern byte g_Map[4][4];        // 游戏地图
extern byte g_EmptyX, g_EmptyY; // 空格坐标
extern long g_timeStart;        // 开始时间
extern int moveCount;           // 移动次数
extern int selected;

// 函数声明
void InitBlock(int picNum);
void Draw();
void MoveTo(int newx, int newy);
void RandMap();
bool IsWin();
void Play();
void Win();
void GotoXY(int x, int y);
void HideCursor();
void Help();
void About();
void ShowMenu();
int ChoosePic();
bool PauseMenu();
void PlayBGM();
void StopBGM();

#endif    #pragma once
