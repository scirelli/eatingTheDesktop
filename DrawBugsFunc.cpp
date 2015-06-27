//Draws the bugs

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <math.h>

//defines
#define BUG_RADIUS 10


void DrawBug1(HDC hmdc, HPEN black_pen, HPEN green_pen, HBRUSH green_brush)
{
	static RECT rect;
	static int x=250,
			   y=200;
	static float j=0.0995f,
				 k=1.0f;


	//fill in rect struct for erasing bug
	rect.left = x - BUG_RADIUS;
	rect.right = x + BUG_RADIUS;
	rect.top = y - BUG_RADIUS;
	rect.bottom = y + BUG_RADIUS;
	
	//Draw erasing bug
	//SelectObject(hmdc, black_pen);
	//SelectObject(hmdc, GetStockObject(BLACK_BRUSH));
	//Ellipse(hmdc,rect.left, rect.top, rect.right, rect.bottom);
	
	//move the bug
	//x++;
	
	//Redraw the ball in its new position
	//fill in rect struct for drawing ball
	rect.left = x - BUG_RADIUS;
	rect.right = x + BUG_RADIUS;
	rect.top = y - BUG_RADIUS;
	rect.bottom = y + BUG_RADIUS;
		
	//Draw the ball in its new spot
	SelectObject(hmdc, green_pen);
	SelectObject(hmdc, green_brush);
	Ellipse(hmdc,rect.left, rect.top, rect.right, rect.bottom);
	
	return;
}