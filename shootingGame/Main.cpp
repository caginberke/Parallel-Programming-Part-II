#include"icb_gui.h"
void ICGUI_Create()
{
	ICG_MWTitle("Shooting Game");
	ICG_MWSize(700, 700);
	ICG_MWPosition(0, 0);
}


int keypressed = 0;
int FRM1;

void* gameStart(PVOID lpParam)
{

	ICBYTES map;
	CreateImage(map, 560, 620, ICB_UINT);
	int x = 230, y = 590;
	int* data = (int*)lpParam;

	while (TRUE)
	{
		FillRect(map, x, y, 20, 6, 0xffff00);

		DisplayImage(FRM1, map);
		Sleep(10);
		FillRect(map, x, y, 30, 30, 0);
		if (keypressed == 39)
			x++;
		else if (keypressed == 37)
			x--;
		
	}
	return(NULL);
}


void* bulletStart(PVOID lpParam)
{

	while (TRUE)
	{
		if (keypressed == 32) {


		}
	}
	return(NULL);
}

void WhenKeyPressed(int k)
{
	keypressed = k;
}

void Start(void* arg)
{
	DWORD dw;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)gameStart, arg, 0, &dw);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bulletStart, arg, 0, &dw);

	SetFocus(ICG_GetMainWindow());
}
void ICGUI_main()
{
	int localData = 42;

	ICG_TButton(570, 5, 100, 25, "BAÞLAT", Start, &localData);
	FRM1 = ICG_FrameMedium(5, 5, 560, 620);
	ICG_SetOnKeyPressed(WhenKeyPressed);
}