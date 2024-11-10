#include "icb_gui.h"


enum HitPos
{
    None,
    Left,
    Middle,
    Right,
    End
};
struct MyStruct
{
    bool gameOver;
    int shipX, shipY;
    bool boxActive;
    HitPos boxHit;
    int boxX, boxY;

    void Restart()
    {
        gameOver = false;
        shipY = 590;
        shipX = 280;
        boxActive = true;
        boxHit = None;
        boxX = rand() % (540 - 0 + 1) + 0;;
        boxY = 0;
    }
};


void ICGUI_Create()
{
    ICG_MWTitle("Shooting Game");
    ICG_MWSize(700, 700);
    ICG_MWPosition(0, 0);
}

int keypressed = 0;
int FRM1;
ICBYTES map;


void* ShipThread(PVOID lpParam)
{
    MyStruct* data = (MyStruct*)lpParam;

    while (TRUE)
    {

        FillRect(map, data->shipX, data->shipY, 20, 6, 0xffff00);
        DisplayImage(FRM1, map);
        Sleep(10);
        FillRect(map, data->shipX, data->shipY, 20, 6, 0);

        if (keypressed == 39 && data->shipX < 540)
            data->shipX++;  

        else if (keypressed == 37 && data->shipX > 0)
            data->shipX--;
    }
    return NULL;
}

void* BoxThread(PVOID lpParam)
{
    MyStruct* data = (MyStruct*)lpParam;
    while (TRUE)
    {
        switch (data->boxHit)
        {
        case None:
            data->boxY++;
            if (data->boxY > 620)
                data->boxHit = End;
            break;

        case Left:
            if (--data->boxY <= 1 || --data->boxX <= 1)
                data->boxHit = End;
            break;

        case Middle:
            if (--data->boxY <= 1)
                data->boxHit = End;
            break;

        case Right:
            if (--data->boxY <= 1 || ++data->boxX >= 560)
                data->boxHit = End;
            break;

        case End:
            data->boxHit = None;
            data->boxX = rand() % (540 - 0 + 1) + 0;
            data->boxY = 0;
            break;

        }
        FillRect(map, data->boxX, data->boxY, 20, 20, 0xffff00);
        DisplayImage(FRM1, map);
        Sleep(10);
        FillRect(map, data->boxX, data->boxY, 20, 20, 0);
    }
    return NULL;
}

void* BulletThread(PVOID lpParam)
{

    MyStruct* data = (MyStruct*)lpParam;

    int bulletX;
    int bulletY;
    bool bulletActive = false; 


    while (TRUE)
    {

        if (keypressed == 32 && !bulletActive) 
        {
            bulletActive = true;
            bulletX = data->shipX+9;
            bulletY = 580;
        }

        if (bulletActive)
        {

            FillRect(map, bulletX, bulletY, 3, 10, 0xFF0000);
            DisplayImage(FRM1, map);
            Sleep(20);
            FillRect(map, bulletX, bulletY, 3, 10, 0); 

            bulletY -= 10;

            if (bulletY < 0)
            {
                bulletActive = false;
                keypressed = 0;

            }

            if (bulletY - 20 < data->boxY && data->boxHit == None)
            {
                if (bulletX <= data->boxX + 3 && bulletX >= data->boxX - 4)
                {
                    data->boxHit = Middle;
                }
                else if(bulletX<data->boxX - 4 && bulletX>data->boxX - 10)
                {
                    data->boxHit = Left;
                }
                else if (bulletX>data->boxX + 3 && bulletX<data->boxX + 10)
                {
                    data->boxHit = Right;
                }

            }
            

            
        }
    }
}




void Start(void* arg);
void WhenKeyPressed(int k) { keypressed = k; }

void ICGUI_main()
{
    MyStruct* gameData = new MyStruct;

    ICG_Button(570, 5, 100, 25, "BAÞLAT", Start, gameData);
    FRM1 = ICG_FrameMedium(5, 5, 560, 620);
    ICG_SetOnKeyPressed(WhenKeyPressed);
}

void Start(void* arg)
{
    SetFocus(ICG_GetMainWindow());

    // Init Game Data
    ((MyStruct*)arg)->Restart();

    // Init Game Screen
    CreateImage(map, 560, 620, ICB_UINT);


    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ShipThread, arg, 0, 0);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)BulletThread, arg, 0, 0);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)BoxThread, arg, 0, 0);
    // TODO: BoxThread

}
