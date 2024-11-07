#include"icb_gui.h"
void ICGUI_Create()
{
	ICG_MWTitle("Shooting Game");
	ICG_MWSize(700, 700);
}

ICBYTES Bullet;
ICBYTES Square;
int keypressed = 0;
int FRM1, BTN;
void* gameStart(PVOID lpParam)
{
	// CreateMatrix(Bullet, X, Y, Z, W, ICB_UINT);
	// CreateMatrix(Square, X, Y, Z, W, ICB_UINT);
	//RandomUniform(mat, x,y,z)
	ICBYTES map;
	CreateImage(map, 560, 620, ICB_UINT);
	int x = 230, y = 590;
	while (TRUE)
	{
		FillRect(map, x, y, 20, 6, 0xffff00);

		DisplayImage(FRM1, map);
		Sleep(10);
		FillRect(map, x, y , 30, 30, 0);
		if (keypressed == 39)
			x++;
		else if (keypressed == 37)
			x--;
	}
	return(NULL);
}
void WhenKeyPressed(int k)
{
	keypressed = k;
}

void Start()
{ 
	DWORD dw;

	ICG_SetWindowText(BTN, "TIKLAMA");
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)gameStart, NULL, 0, &dw);

	SetFocus(ICG_GetMainWindow());
}
void ICGUI_main()
{
	BTN = ICG_Button(570, 5, 100, 25, "BAÞLAT", Start);
	FRM1 = ICG_FrameMedium(5, 5, 560, 620);
	ICG_SetOnKeyPressed(WhenKeyPressed);
}