#include "Useful.h"

int g_click_x, g_click_y;                     // 클릭 받은 위치
int g_click_x_temp = -1, g_click_y_temp = -1; // 클릭 받은 위치 temp값
bool g_sound_option = false;                  // 사운드 옵션
bool g_kill_thread = false;                   // 스레드 삭제

void logo();                           // 시작시 로고 출력
void beforePixelToy();                 // 사이즈 입력
void pixelToy(int size_x, int size_y); // 게임 시작

int main()
{
    SetCursorType(NOCURSOR);            // 커서 삭제
    SetWindow(100, 50);                 // 창크기 설정
    RemoveScrollbar();                  // 스크롤바 삭제
    SetConsoleTitle(TEXT("Pixel Toy")); // 콘솔의 제목을 변경
    srand((unsigned int)time(NULL));    // rand()함수의 시드 변경
    if (g_sound_option == true)
    {
        //PlaySound(TEXT("경로명"), NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
    }
    logo();
}

void clickTemp()
{
    g_click_x_temp = g_click_x;
    g_click_y_temp = g_click_y;
}

unsigned _stdcall clickToStart(void* arg)
{
    int temp = 0;
    while (true)
    {
        if (g_kill_thread == true)
        {
            _endthread();
            break;
        }

        Gotoxy_(30, 21);
        if (temp == 0)
        {
            TextColor(kLPurple);
            printf("Click to Start");
            temp++;
        }
        else
        {
            TextColor(kLWhite);
            printf("Click to Start");
            temp--;
        }
        Sleep(500);

        if (g_kill_thread == true)
        {
            _endthread();
            break;
        }
    }
    return 0;
}

void logo()
{
    g_click_x_temp = -1;
    g_click_y_temp = -1;

    int pixel[7][50] = {
        {1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0} };
    for (int iCount = 0; iCount < 7; iCount++)
    {
        for (int jCount = 0; jCount < 50; jCount++)
        {
            Gotoxy_(iCount + 18, jCount + 4);
            if (pixel[iCount][jCount] == 1)
            {
                TextColor(kLPurple);
            }
            else
            {
                TextColor(kBlack);
            }
            printf("■");
        }
    }

    _beginthreadex(NULL, 0, clickToStart, 0, 0, NULL);

    Click(&g_click_x, &g_click_y);
    g_kill_thread = true;
    clickTemp();
    TextColor(kLWhite);
    system("cls");
    pixelToy(50, 50);
}

void pixelToy(int size_x, int size_y)
{
    size_x = 50, size_y = 50;

    g_click_x_temp = -1;
    g_click_y_temp = -1;
    int iCount, jCount;
    system("cls");
    SetWindow(5, 5); // 에러 해결 위해서 창 크기 변경
    SetWindow(size_x * 2 + 4, size_y + 5);
    RemoveScrollbar();

    TextColor(kLWhite);

    //Click(&g_click_x, &g_click_y);

    iCount = 0, jCount = 0;
    int iCount_max = size_x + 1;
    int jCount_max = size_y + 1;
    int map[52][52] = { 0 };
    int block = 1, rand_;
    bool pause = false;

    const int kErase = 0;
    const int kWater = 1;
    const int kBlock = 2;
    const int kLava = 3;
    const int kMaxBlock = 4;

    for (int i = 0; i < 52; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            if ((i == 0 || i == 51) && (j == 0 || j == 51))
            {
                map[i][j] = kBlock;
            }
        }
    }
    Gotoxy_(iCount_max, 0);
    for (int i = 0; i < 104; i++)
    {
        printf("─");
    }

    Gotoxy_(iCount_max + 1, 1);
    TextColor(kLWhite);
    printf("Water");
    Gotoxy_(iCount_max + 2, 0);
    TextColor(0x0f); //음영 kBlack 글자 kLWhite
    printf("○");
    TextColor(0x89); //음영 kGray 글자 kLBlue
    printf("■");
    TextColor(0x0f); //음영 kBlack 글자 kLWhite
    printf("■");
    TextColor(0x0c); //음영 kBlack 글자 kLRed
    printf("■");
    Gotoxy_(iCount_max + 2, jCount_max - 4);
    TextColor(0x0f); //음영 kBlack 글자 kLWhite
    printf("II");
    Gotoxy_(iCount_max + 2, jCount_max - 2);
    TextColor(0x0f); //음영 kBlack 글자 kLWhite
    printf("종료");

    Click__(&g_click_x, &g_click_y);

    while (true)
    {
        for (iCount = iCount_max - 1; iCount >= 0; iCount--)
        {
            rand_ = rand() % 2;
            if (rand_) // 초기식
            {
                jCount = jCount_max - 1;
            }
            else
            {
                jCount = 0;
            }

            while (true)
            {
                if ((rand_ && !(jCount >= 0)) || (!rand_ && !(jCount <= jCount_max - 1))) // 조건식
                {
                    break;
                }
                if (BeInput())
                {
                    Click__(&g_click_x, &g_click_y);

                    if (g_click_x != g_click_x_temp || g_click_y != g_click_y_temp) // 전에 누른게 아니면
                    {
                        if (g_click_x < iCount_max && g_click_x > 0 && g_click_y < jCount_max && g_click_y > 0) // 박스 내부 클릭
                        {
                            clickTemp();
                            map[g_click_x][g_click_y] = block;
                            Gotoxy_(g_click_x, g_click_y);
                            switch (block)
                            {
                            case kErase: // Erase
                                TextColor(kLWhite);
                                printf("  ");
                                break;
                            case kWater: // Water
                                TextColor(kLBlue);
                                printf("■");
                                break;
                            case kBlock: // Block
                                TextColor(kLWhite);
                                printf("■");
                                break;
                            case kLava: // Lava
                                TextColor(kLRed);
                                printf("■");
                                break;
                            }
                        }
                        else if (g_click_x == iCount_max + 2)
                        {
                            if (g_click_y < kMaxBlock) // 블럭 선택
                            {
                                clickTemp();

                                Gotoxy_(iCount_max + 2, block); // 음영 제거
                                switch (block)
                                {
                                case kErase:
                                    TextColor(0x0f);
                                    printf("○");
                                    break;
                                case kWater:
                                    TextColor(0x09);
                                    printf("■");
                                    break;
                                case kBlock:
                                    TextColor(0x0f);
                                    printf("■");
                                    break;
                                case kLava:
                                    TextColor(0x0c);
                                    printf("■");
                                    break;
                                }

                                block = g_click_y;

                                Gotoxy_(iCount_max + 2, block); // 음영 생성
                                switch (block)
                                {
                                case kErase:
                                    TextColor(0x8f);
                                    printf("○");
                                    Gotoxy_(iCount_max + 1, 1);
                                    TextColor(kLWhite);
                                    printf("Erase     ");
                                    break;
                                case kWater:
                                    TextColor(0x89);
                                    printf("■");
                                    Gotoxy_(iCount_max + 1, 1);
                                    TextColor(kLWhite);
                                    printf("Water     ");
                                    break;
                                case kBlock:
                                    TextColor(0x8f);
                                    printf("■");
                                    Gotoxy_(iCount_max + 1, 1);
                                    TextColor(kLWhite);
                                    printf("Block     ");
                                    break;
                                case kLava:
                                    TextColor(0x8c);
                                    printf("■");
                                    Gotoxy_(iCount_max + 1, 1);
                                    TextColor(kLWhite);
                                    printf("Lava     ");
                                    break;
                                }
                            }
                            else if (g_click_y >= jCount_max - 2) // 종료 선택
                            {
                                clickTemp();
                                return;
                            }
                            else if (g_click_y == jCount_max - 4) // 일시정지 선택
                            {
                                clickTemp();

                                if (pause) // 재생을 누른 경우
                                {
                                    pause = false;
                                    Gotoxy_(iCount_max + 2, jCount_max - 4);
                                    TextColor(kLWhite);
                                    printf("II");
                                }
                                else // 멈춤을 누른 경우
                                {
                                    pause = true;
                                    Gotoxy_(iCount_max + 2, jCount_max - 4);
                                    TextColor(kLWhite);
                                    printf("▷");
                                }
                            }
                        }
                    }
                }

                if ((map[iCount][jCount] != kErase && map[iCount][jCount] != kBlock) && pause == false) // 블럭 움직임 연산
                {
                    if (map[iCount + 1][jCount] == kErase) // 떨어짐
                    {
                        switch (map[iCount][jCount])
                        {
                        case kWater: // 물의 경우
                            if (iCount < iCount_max - 1) {
                                map[iCount + 1][jCount] = kWater;
                                Gotoxy_(iCount + 1, jCount);
                                TextColor(kLBlue);
                                printf("■");
                            }
                            map[iCount][jCount] = kErase;
                            Gotoxy_(iCount, jCount);
                            TextColor(kBlack);
                            printf("  ");
                            break;
                        case kLava: // 용암의 경우
                            if (iCount < iCount_max - 1) {
                                map[iCount + 1][jCount] = kLava;
                                Gotoxy_(iCount + 1, jCount);
                                TextColor(kLRed);
                                printf("■");
                            }
                            map[iCount][jCount] = kErase;
                            Gotoxy_(iCount, jCount);
                            TextColor(kBlack);
                            printf("  ");
                            break;
                        }
                    }
                    else if ((map[iCount + 1][jCount] == kBlock || map[iCount + 1][jCount] == map[iCount][jCount] || iCount == iCount_max - 1) && (map[iCount][jCount - 1] == kErase || map[iCount][jCount + 1] == kErase)) // 옆으로 흐를 때
                    {
                        /*
                            자기 밑 물질이 블럭이거나, 자기 자신 (용암은 용암, 물은 물)이거나, 막힌 경우 &&
                            양 옆중 하나라도 빈 공간 일 때 옆으로 흐른다.
                        */
                        const int all = 0, left = 1, right = 2;

                        int blankwhere = all; // all: 둘다 빔, left: 왼쪽 빔, right: 오른쪽 빔
                        if (map[iCount][jCount - 1] == kErase && map[iCount][jCount + 1] == kErase)
                        {
                            blankwhere = all;
                        }
                        else if (map[iCount][jCount - 1] == kErase)
                        {
                            blankwhere = left;
                        }
                        else if (map[iCount][jCount + 1] == kErase)
                        {
                            blankwhere = right;
                        }
                        else
                        {
                            continue;
                        }


                        if ((rand() % 2 && blankwhere != left) || blankwhere == right) // 오른쪽으로 이동
                        {
                            switch (map[iCount][jCount])
                            {
                            case kWater: // 물의 경우
                                map[iCount][jCount + 1] = kWater;
                                Gotoxy_(iCount, jCount + 1);
                                TextColor(kLBlue);
                                printf("■");
                                map[iCount][jCount] = kErase;
                                Gotoxy_(iCount, jCount);
                                TextColor(kBlack);
                                printf("  ");
                                break;
                            case kLava: // 용암의 경우
                                map[iCount][jCount + 1] = kLava;
                                Gotoxy_(iCount, jCount + 1);
                                TextColor(kLRed);
                                printf("■");
                                map[iCount][jCount] = kErase;
                                Gotoxy_(iCount, jCount);
                                TextColor(kBlack);
                                printf("  ");
                                break;
                            }
                        }
                        else if ((rand() % 2 && blankwhere != right) || blankwhere == left) // 왼쪽으로 이동
                        {
                            switch (map[iCount][jCount])
                            {
                            case kWater: // 물의 경우
                                map[iCount][jCount - 1] = kWater;
                                Gotoxy_(iCount, jCount - 1);
                                TextColor(kLBlue);
                                printf("■");
                                map[iCount][jCount] = kErase;
                                Gotoxy_(iCount, jCount);
                                TextColor(kBlack);
                                printf("  ");
                                break;
                            case kLava: // 용암의 경우
                                map[iCount][jCount - 1] = kLava;
                                Gotoxy_(iCount, jCount - 1);
                                TextColor(kLRed);
                                printf("■");
                                map[iCount][jCount] = kErase;
                                Gotoxy_(iCount, jCount);
                                TextColor(kBlack);
                                printf("  ");
                                break;
                            }
                        }
                    }
                    if (map[iCount][jCount] == kLava || map[iCount == kWater])
                    {
                        int plus = 0;

                        if (map[iCount][jCount] == kLava)
                        {
                            if (map[iCount - 1][jCount] == kWater)
                            {
                                plus++;
                                map[iCount - 1][jCount] = kBlock;
                                Gotoxy_(iCount - 1, jCount);
                                TextColor(kGray);
                                printf("■");
                            }
                            if (map[iCount + 1][jCount] == kWater)
                            {
                                plus++;
                                map[iCount + 1][jCount] = kBlock;
                                Gotoxy_(iCount + 1, jCount);
                                TextColor(kGray);
                                printf("■");
                            }
                            if (map[iCount][jCount - 1] == kWater)
                            {
                                plus++;
                                map[iCount][jCount - 1] = kBlock;
                                Gotoxy_(iCount, jCount - 1);
                                TextColor(kGray);
                                printf("■");
                            }
                            if (map[iCount][jCount + 1] == kWater)
                            {
                                plus++;
                                map[iCount][jCount + 1] = kBlock;
                                Gotoxy_(iCount, jCount + 1);
                                TextColor(kGray);
                                printf("■");
                            }
                        }

                        else if(map[iCount][jCount] == kWater)
                        {
                            if (map[iCount - 1][jCount] == kLava)
                            {
                                plus++;
                                map[iCount - 1][jCount] = kBlock;
                                Gotoxy_(iCount - 1, jCount);
                                TextColor(kGray);
                                printf("■");
                            }
                            if (map[iCount + 1][jCount] == kLava)
                            {
                                plus++;
                                map[iCount + 1][jCount] = kBlock;
                                Gotoxy_(iCount + 1, jCount);
                                TextColor(kGray);
                                printf("■");
                            }
                            if (map[iCount][jCount - 1] == kLava)
                            {
                                plus++;
                                map[iCount][jCount - 1] = kBlock;
                                Gotoxy_(iCount, jCount - 1);
                                TextColor(kGray);
                                printf("■");
                            }
                            if (map[iCount][jCount + 1] == kLava)
                            {
                                plus++;
                                map[iCount][jCount + 1] = kBlock;
                                Gotoxy_(iCount, jCount + 1);
                                TextColor(kGray);
                                printf("■");
                            }

                        }

                        if (plus > 0)
                        {
                            map[iCount][jCount] = kBlock;
                            Gotoxy_(iCount, jCount);
                            TextColor(kGray);
                            printf("■");
                        }
                    }
                }
                if (rand_)
                {
                    jCount--;
                }
                else
                {
                    jCount++;
                }
            }
        }
        iCount = iCount_max - 1;
    }
}