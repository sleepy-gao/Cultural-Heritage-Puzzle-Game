#include "pintu.h"

IMAGE g_Block[16];            // 拼图块（0-14对应图片，15为空白）
byte g_Map[4][4];             // 游戏地图
byte g_EmptyX, g_EmptyY;      // 空格坐标
long g_timeStart;             // 开始时间
int moveCount = 0;            // 移动次数
int selected = 0;

static IMAGE menu;
static IMAGE help;
static IMAGE about;
static IMAGE win;




// 操作说明
void Help() {
    int count = 0;
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  // 初始化绘图窗口
    loadimage(&help, L"background2.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);  // 加载背景图 只需要一次

    RECT btn_1 = { LEFT_WINDOW_X - 180, 100, RIGHT_WINDOW_X + 120, 220 };  // 处理标题
    RECT btn_2 = { LEFT_WINDOW_X - 180, 240, RIGHT_WINDOW_X + 120, 310 };
    RECT btns[9];
    for (int i = 0; i < 9; i++) {
        btns[i] = { LEFT_WINDOW_X - 150, 240 + (i + 1) * 60, RIGHT_WINDOW_X + 100, 310 + (i + 1) * 60 };
    }
    // 绘制界面
    cleardevice(); // 必须清屏，防止闪烁残影
    // 设置字体
    settextstyle(50, 0, L"Algerian");
    // 绘制标题
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);  // 把drawtext 的背景模式改为“透明” 否则字体周围会有黑色矩形

    // 把背景图贴到 (0,0)，铺满整个窗口
    putimage(0, 0, &help);

    drawtext(L"Help", &btn_1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //
    settextstyle(42, 0, L"Algerian");
    drawtext(L"【操作方式】", &btn_2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //
    settextstyle(36, 0, L"Algerian");
    drawtext(L"鼠标点击拼图块：与相邻空格换位", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(L"方向键/WASD：控制空格移动方向", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //
    settextstyle(42, 0, L"Algerian");
    drawtext(L"【模式选择】", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //
    settextstyle(36, 0, L"Algerian");
    drawtext(L"1.京剧脸谱 2.中国结 3.剪纸 4.书法", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(L"5.国画 6.陶瓷 7.刺绣 8.皮影", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(L"9.灯笼 10.扇子 11.风筝 12.对联", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(L"13.年画 14.篆刻 15.茶艺 16.围棋", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    drawtext(L"按空格键返回主页面", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    ExMessage msg;
    //检查是否按下键盘且按下空格键
    while (true) {
        if (peekmessage(&msg, EM_KEY)) {
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_SPACE) {
                closegraph();
                return;
            }
        }
    }
}

// 相关信息
void About() {
    int count = 0;
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  // 初始化绘图窗口
    loadimage(&about, L"background2.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);//加载背景图 只需要一次

    RECT btn_1 = { LEFT_WINDOW_X - 180, 100, RIGHT_WINDOW_X + 120, 220 };//处理标题
    RECT btns[9];
    for (int i = 0; i < 9; i++) {
        btns[i] = { LEFT_WINDOW_X - 150, 240 + (i + 1) * 60, RIGHT_WINDOW_X + 100, 310 + (i + 1) * 60 };
    }
    // 绘制界面
    cleardevice(); // 必须清屏，防止闪烁残影
    //设置字体
    settextstyle(50, 0, L"Algerian");
    //绘制标题
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);//把drawtext 的背景模式改为“透明” 否则字体周围会有黑色矩形
    // 把背景图贴到 (0,0)，铺满整个窗口
    putimage(0, 0, &about);
    //标题文本
    drawtext(L"About", &btn_1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //内容文本
    settextstyle(36, 0, L"Algerian");
    drawtext(L"这是一款拼图游戏", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    settextstyle(36, 0, L"Algerian");
    drawtext(L"Authors: 高宇晨  马瑞晨", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    settextstyle(36, 0, L"Algerian");
    drawtext(L"BGM：China-Y", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //退出文本
    drawtext(L"按空格键返回主页面", &btns[count++], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    ExMessage msg;
    //检查是否按下键盘且按下空格键
    while (true) {
        if (peekmessage(&msg, EM_KEY)) {
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_SPACE) {
                closegraph();
                return;
            }
        }
    }
}

// 显示主菜单
void ShowMenu() {

    loadimage(&menu, L"background1.png", WINDOW_WIDTH, WINDOW_HEIGHT);//加载背景图 只需要一次
    //左上角的横纵坐标 右下角的...
    RECT btns[5] = {
        { LEFT_WINDOW_X, 250, RIGHT_WINDOW_X, 320 },  // 开始游戏
        { LEFT_WINDOW_X, 340, RIGHT_WINDOW_X, 410 },  // 操作说明
        { LEFT_WINDOW_X, 430, RIGHT_WINDOW_X, 500 },  // 相关信息
        { LEFT_WINDOW_X, 520, RIGHT_WINDOW_X, 590 },  // 退出游戏
        { LEFT_WINDOW_X - 50, 150, RIGHT_WINDOW_X + 50, 220 }   // 标题
    };
    LPCWSTR labels[4] = { L"New Game", L"Help", L"About", L"Exit" };

    BeginBatchDraw();  // 开启批量绘图（开启双缓冲）

    while (true) {
        // 绘制界面
        cleardevice(); // 必须清屏，防止闪烁残影

        // 把背景图贴到 (0,0)，铺满整个窗口
        putimage(0, 0, &menu);

        settextstyle(36, 0, L"Algerian");
        //绘制标题
        settextcolor(RGB(48, 79, 172));
        setbkmode(TRANSPARENT);//把drawtext 的背景模式改为“透明” 否则字体周围会有黑色矩形
        drawtext(L"Welcome to Puzzle_Game", &btns[4], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        for (int i = 0; i < 4; i++) {
            // 选中项使用不同颜色
            if (i == selected) setfillcolor(RGB(255, 165, 0)); // 橙色
            else setfillcolor(RGB(70, 130, 180)); // 默认蓝色

            settextcolor(WHITE);
            fillrectangle(btns[i].left, btns[i].top, btns[i].right, btns[i].bottom);
            setbkmode(TRANSPARENT);//把drawtext 的背景模式改为“透明”
            drawtext(labels[i], &btns[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }

        FlushBatchDraw();  // 一次性刷新到屏幕，防止闪烁

        // 处理键盘输入
        ExMessage msg;
        if (peekmessage(&msg, EM_KEY)) {
            if (msg.message == WM_KEYDOWN) {
                switch (msg.vkcode) {
                case 'W':
                case VK_UP:
                    selected = (selected + 3) % 4;  // 上移，循环选择
                    break;
                case 'S':
                case VK_DOWN:
                    selected = (selected + 1) % 4;  // 下移，循环选择
                    break;
                case VK_RETURN:

                    EndBatchDraw();  // 离开前关闭双缓冲

                    // 根据当前选中的按钮执行操作
                    switch (selected) {
                    case 0: return; // 开始游戏
                    case 1: return;
                    case 2: return;
                    case 3: exit(0); // 退出游戏
                    }
                    break;
                }
            }
        }

        Sleep(50);
    }
}

// 显示游戏界面
void Draw() {
    loadimage(&menu, L"background1.png", WINDOW_WIDTH, WINDOW_HEIGHT);
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        for (int x = 0; x < CANVAS_WIDTH; x++) {
            if (g_Map[x][y] != 15) {
                putimage(x * BLOCK_SIZE + MARGIN_X, y * BLOCK_SIZE + MARGIN_Y, &g_Block[g_Map[x][y]]);
            }
            else {
                // 空白块绘制黑色矩形
                setfillcolor(BLACK);
                solidrectangle(x * BLOCK_SIZE + MARGIN_X, y * BLOCK_SIZE + MARGIN_Y,
                    x * BLOCK_SIZE + MARGIN_X + BLOCK_SIZE - 1,
                    y * BLOCK_SIZE + MARGIN_Y + BLOCK_SIZE - 1);
            }
        }
    }

    // 只擦文字区（假设背景是纯黑，就用黑色覆盖）  
    setfillcolor(RGB(110, 155, 217));
    // “游戏用时 + 时间” 区域
    solidrectangle(840, 30, 1020, 120);
    // “移动次数 + 步数” 区域
    solidrectangle(840, 120, 1020, 200);
    // “暂停提示” 区域
    solidrectangle(840, 200, 1020, 280);

    // 然后再在上面画文字  
    setbkmode(TRANSPARENT);
    settextstyle(24, 0, L"Algerian");
    settextcolor(WHITE);

    long curtime = clock();
    wchar_t s[20];
    swprintf_s(s, L"%.2f 秒", (curtime - g_timeStart) / (double)CLOCKS_PER_SEC);
    outtextxy(850, 40, L"游戏用时");
    outtextxy(850, 90, s);

    swprintf_s(s, L"%d", moveCount);
    outtextxy(850, 140, L"移动次数");
    outtextxy(850 + (textwidth(L"移动次数") - textwidth(s)) / 2, 180, s);

    outtextxy(850, 240, L"按下空格键暂停");
}

// 游戏暂停
bool PauseMenu() {
    loadimage(&menu, L"background1.png", WINDOW_WIDTH, WINDOW_HEIGHT);      // 加载背景图 只需要一次
    RECT btn = { LEFT_WINDOW_X - 50, 150, RIGHT_WINDOW_X + 50, 220 };      // 标题
    RECT btn1 = { LEFT_WINDOW_X - 150, 200, RIGHT_WINDOW_X + 150, 270 };   // 标题
    cleardevice();
    // 把背景图贴到 (0,0)，铺满整个窗口
    putimage(0, 0, &menu);
    settextstyle(36, 0, L"Algerian");
    // 绘制标题
    settextcolor(RGB(48, 79, 172));
    setbkmode(TRANSPARENT);  // 把drawtext的背景模式改为“透明” 否则字体周围会有黑色矩形
    drawtext(L"您已暂停 是否继续？", &btn, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    settextstyle(36, 0, L"Algerian");
    drawtext(L"按下空格键以继续 按下回车键以退出", &btn1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    FlushBatchDraw();  // 刷新到屏幕

    ExMessage msg;
    //检查是否按下键盘且按下空格键
    while (true) {
        if (peekmessage(&msg, EM_KEY)) {
            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_SPACE) {
                return true;
            }
            else if (msg.message == WM_KEYDOWN && msg.vkcode == VK_RETURN) {
                return false;
            }
        }
        Sleep(10);
    }
}

// 移动拼图块
void MoveTo(int newx, int newy) {
    g_Map[g_EmptyX][g_EmptyY] = g_Map[newx][newy];
    g_Map[newx][newy] = 15;         // 标记新空白块位置
    g_EmptyX = newx;
    g_EmptyY = newy;
}

// 随机打乱拼图
void RandMap() {
    for (int i = 0; i < 16; i++)
        g_Map[i % 4][i / 4] = i;
    g_EmptyX = 3;            // 初始空白块位于右下角
    g_EmptyY = 3;

    srand(time(NULL));
    for (int i = 0; i < 2000; i++) {
        int dir = rand() % 4;
        int dx = 0, dy = 0;
        switch (dir) {
        case 0: dx = -1; break;  // 左
        case 1: dx = 1;  break;  // 右
        case 2: dy = -1; break;  // 上
        case 3: dy = 1;  break;  // 下
        }
        if (g_EmptyX + dx >= 0 && g_EmptyX + dx < 4 && g_EmptyY + dy >= 0 && g_EmptyY + dy < 4) {
            MoveTo(g_EmptyX + dx, g_EmptyY + dy);
        }
    } 
}

// 判断是否胜利
bool IsWin() {
    for (int i = 0; i < 16; i++)
        if (g_Map[i % 4][i / 4] != i)
            return false;
    return true;
}

// 初始化拼图块
void InitBlock(int picNum) {
    loadimage(&menu, L"background1.png", WINDOW_WIDTH, WINDOW_HEIGHT);
    wchar_t s[3], imgPath[20];  // 数字字符串和图片路径
    for (int i = 0; i < 16; i++) {
        g_Block[i].Resize(BLOCK_SIZE, BLOCK_SIZE);
        SetWorkingImage(&g_Block[i]);

        if (i != 15) {  // 非空白块加载图片
            swprintf_s(imgPath, L"%s%dpic%d.png", IMAGE_PATH, picNum, i + 1);
            loadimage(&g_Block[i], imgPath);
        }

        // 在图片上绘制数字
        if (i != 15) {
            settextstyle(64, 0, _T("Arial"), 0, 0, LEFT_WINDOW_X, false, false, false);
            setbkmode(TRANSPARENT);
            settextcolor(WHITE);
            _itow_s(i + 1, s, 10);
            outtextxy((BLOCK_SIZE - textwidth(s)) / 2, 18, s);
        }
    }
    SetWorkingImage(NULL);
}

// 游戏主循环
void Play() {
    ExMessage msg;

    // 开启双缓冲（只调用一次）
    BeginBatchDraw();

    // 只要没拼好，就一直循环
    while (!IsWin()) {
        bool wantPause = false;//用户是否按下空格
        long pauseStart = 0;      // 暂停开始的时刻（clock()）
        bool isWin = false;
        // 处理鼠标/方向键输入，更新 g_Map、moveCount
        while (peekmessage(&msg, EM_MOUSE | EM_KEY)) {
            switch (msg.message) {

            case WM_LBUTTONDOWN:      // 鼠标点击事件
                if (msg.x >= MARGIN_X && msg.x < MARGIN_X + BLOCK_SIZE * CANVAS_WIDTH && msg.y >= MARGIN_Y && msg.y < MARGIN_Y + BLOCK_SIZE * CANVAS_HEIGHT) {
                    int x = (msg.x - MARGIN_X) / BLOCK_SIZE;
                    int y = (msg.y - MARGIN_Y) / BLOCK_SIZE;
                    if (abs(g_EmptyX - x) + abs(g_EmptyY - y) == 1) {
                        MoveTo(x, y);
                        moveCount++;
                    }
                }
                break;

            case WM_KEYDOWN:             // 键盘事件
                switch (msg.vkcode) {
                case VK_LEFT:
                case 'A':
                case 'a':
                    if (g_EmptyX > 0) {
                        MoveTo(g_EmptyX - 1, g_EmptyY);
                        moveCount++;
                    }
                    break;
                case VK_UP:
                case 'W':
                case 'w':
                    if (g_EmptyY > 0) {
                        MoveTo(g_EmptyX, g_EmptyY - 1);
                        moveCount++;
                    }
                    break;
                case VK_RIGHT:
                case 'D':
                case 'd':
                    if (g_EmptyX < CANVAS_WIDTH - 1) {
                        MoveTo(g_EmptyX + 1, g_EmptyY);
                        moveCount++;
                    }
                    break;
                case VK_DOWN:
                case 'S':
                case 's':
                    if (g_EmptyY < CANVAS_HEIGHT - 1) {
                        MoveTo(g_EmptyX, g_EmptyY + 1);
                        moveCount++;
                    }
                    break;
                case VK_SPACE:
                    wantPause = true;
                    pauseStart = clock();
                    break;
                case VK_RETURN:
                    isWin = true;
                }
                break;
            } // end switch(msg.message)
        } // end while peekmessage

        // 测试 实际运行删掉
        if (isWin) return;
        // 检测是否按下空格键，如果有，就退出游戏循环
        // （注意：peekmessage 不阻塞，直接检测键盘队列里有没有消息）
        if (wantPause) {

            // 先把当前一帧的画面刷新到屏幕
            FlushBatchDraw();

            //调用暂停函数
            bool resume = PauseMenu();

            if (resume) {
                // 用户选择“继续游戏”：                     
                // 把暂停期间走过的时钟差，扣掉
                long pauseDuration = clock() - pauseStart;
                g_timeStart += pauseDuration;
                // 结束暂停界面的双缓冲（PauseMenu 中已经调用过 FlushBatchDraw，但并未 EndBatchDraw）
                // 重新开启双缓冲，回到主循环继续
                BeginBatchDraw();
            }
            else {
                moveCount = 0;  // 重置移动次数
                EndBatchDraw();
                closegraph();
                return;
            }
        }

        // 渲染本帧：把 g_Map 画到显存
        Draw();

        // 将显存内容一次性刷新到屏幕
        FlushBatchDraw();

        // 控制帧率，让循环别跑得太快
        Sleep(20);
    }

    // 如果拼图成功，最后再把胜利画面刷新一次到屏幕
    
    FlushBatchDraw();
    EndBatchDraw();
    Win();
}

// 控制台光标操作
void GotoXY(int x, int y) {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cor = { x, y };
    SetConsoleCursorPosition(hout, cor);
}
void HideCursor() {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci = { 1, 0 };
    SetConsoleCursorInfo(hout, &cci);
}


// 选择游戏图片
int ChoosePic() {
    RECT btns[16];
    LPCWSTR labels[16] = { L"京剧脸谱", L"中国结", L"剪纸", L"书法", L"国画", L"陶瓷", L"刺绣", L"皮影", L"灯笼", L"扇子", L"风筝", L"对联", L"年画", L"篆刻", L"茶艺", L"围棋" };
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 2; j++) {
            int x1 = j * (100 + 20) + 400;
            int y1 = i * (50 + 10) + 200;
            int x2 = x1 + 100;
            int y2 = y1 + 50;
            btns[i * 2 + j] = { x1, y1, x2, y2 };
        }
    }
    BeginBatchDraw();  // 开启批量绘图（开启双缓冲）
    int selected = 0;
    bool crys = true;
    while (crys) {
        cleardevice(); // 必须清屏，防止闪烁残影
        settextstyle(25, 0, L"Algerian");

        for (int i = 0; i < 16; i++) {
            // 选中项使用不同颜色
            if (i == selected) setfillcolor(RGB(255, 165, 0)); // 橙色
            else setfillcolor(RGB(70, 130, 180)); // 默认蓝色

            settextcolor(WHITE);
            fillrectangle(btns[i].left, btns[i].top, btns[i].right, btns[i].bottom);
            setbkmode(TRANSPARENT);
            drawtext(labels[i], &btns[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }

        FlushBatchDraw();  // 一次性刷新到屏幕，防止闪烁

        // 处理键盘输入
        ExMessage msg;
        if (peekmessage(&msg, EM_KEY)) {
            if (msg.message == WM_KEYDOWN) {
                switch (msg.vkcode) {
                case 'W':
                case VK_UP:
                    selected = (selected + 14) % 16;  // 上移，循环选择
                    break;
                case 'A':
                case VK_LEFT:
                    selected = (selected + 15) % 16;  // 左移，循环选择
                    break;
                case 'D':
                case VK_RIGHT:
                    selected = (selected + 1) % 16;  // 右移，循环选择
                    break;
                case 'S':
                case VK_DOWN:
                    selected = (selected + 2) % 16;  // 下移，循环选择
                    break;
                case VK_RETURN:

                    EndBatchDraw();  // 离开前关闭双缓冲

                    // 根据当前选中的按钮执行操作
                    switch (selected) {
                    case 0: return 1; // 开始游戏
                    case 1: return 2;
                    case 2: return 3;
                    case 3: return 4;
                    case 4: return 5;
                    case 5: return 6;
                    case 6: return 7;
                    case 7: return 8;
                    case 8: return 9;
                    case 9: return 10;
                    case 10: return 11;
                    case 11: return 12;
                    case 12: return 13;
                    case 13: return 14;
                    case 14: return 15;
                    case 15: return 16;
                    }
                    break;
                }
            }
        }
        Sleep(50);
    }
}



// 胜利处理
void Win() {
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  // 初始化绘图窗口
    loadimage(&win, L"win.jpg", WINDOW_WIDTH, WINDOW_HEIGHT);  //加载背景图 只需要一次    
    putimage(0, 0, &win);
    // 选择关卡或继续游戏

    // 目前直接退出
    // 等待用户按回车
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_KEY)) {
            if (msg.message == WM_KEYDOWN) {
                break;
            }
        }
        Sleep(10); // 减少CPU占用
    }
    moveCount = 0;     // 重置移动次数

    closegraph();  // 关闭图形窗口
}

// 播放背景音乐
void PlayBGM() {
    // 停止当前播放的音乐（避免重复播放）
    StopBGM();

    // 播放音乐
    mciSendStringW(L"open \"chinay.mp3\" type mpegvideo alias BGM", NULL, 0, NULL);
    mciSendStringW(L"set BGM volume 50", NULL, 0, NULL);
    mciSendStringW(L"play BGM repeat", NULL, 0, NULL);
}
// 停止背景音乐
void StopBGM() {
    mciSendStringW(L"close BGM", NULL, 0, NULL);
}

// 主函数
int main() {
    srand(time(NULL));
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  // 初始化绘图窗口
    int end = 1;
    int picNum = 0;

    // 播放音乐
    PlayBGM();

    while (end) {
        ShowMenu();
        loadimage(&menu, L"background.png", WINDOW_WIDTH, WINDOW_HEIGHT);// 加载背景图 只需要一次
        switch (selected) {
        case 0:           // 开始游戏
            moveCount = 0;
            do {
                closegraph();
                initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  // 初始化绘图窗口
                picNum = ChoosePic(); // 图片选择
                InitBlock(picNum);    // 初始化图片和数字
                // 把背景图贴到 (0,0)，铺满整个窗口
                putimage(0, 0, &menu);
                //重新加载拼图块图片到新的绘图上下文
                InitBlock(picNum);
                RandMap();
                flushmessage(EM_MOUSE | EM_KEY);
                g_timeStart = clock();  // 记录开始时间
                Play();
                
            } while (MessageBox(GetHWnd(), L"重新开始？", L"提示", MB_YESNO) == IDYES);

            closegraph();  // 关闭图形窗口
            break;
        case 1:
            closegraph();  // 关闭图形窗口
            Help();
            initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  // 重新打开图形窗口
            break;
        case 2:
            closegraph();
            About();
            initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  // 重新打开图形窗口
            break;
        default: end = 0; break; // 退出
        }
    }
    StopBGM();
    return 0;
}
