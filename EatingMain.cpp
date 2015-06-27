//htdc= GetWindowDC( GetTopWindow(hwnd) ); 


// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  

#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <mmsystem.h> //needed to play a sound using windows also need to insert winmm.lib
					  //C:\Program Files\Microsoft Visual Studio\VC98\Lib


// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME "WINCLASS1"  // class name

// MACROS /////////////////////////////////////////////////

// these read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// PROTOTYPES /////////////////////////////////////////////
void DrawBug1(HDC hdc, HPEN, HPEN, HBRUSH); 

// GLOBALS ////////////////////////////////////////////////

HWND main_window_handle = NULL; // save the window handle
HINSTANCE main_instance = NULL; // save the instance
char buffer[80];                // used to print text
HPEN white_pen; //creates a white pen
HPEN black_pen; //creates a black pen
HPEN green_pen; //creates a green pen
HBRUSH green_brush; //creates a brush

// FUNCTIONS //////////////////////////////////////////////

//\\\\\\\\\\\\\\\\\\\\\\\\\ WinProc ///////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT	ps;		   // used in WM_PAINT
	HDC			hdc;	   //creates a handle to the device context

	//find out what the message is
	switch(msg)
	{	
	
	case WM_CREATE: //called when window is created
		{// do initialization stuff here
			
			white_pen= CreatePen(PS_SOLID,0,RGB(255,255,255)); //adds a color to the pen
			black_pen= CreatePen(PS_SOLID,0,RGB(0,0,0));
			green_pen= CreatePen(PS_SOLID,0,RGB(0,255,0));
			green_brush= CreateSolidBrush(RGB(0,255,0));
			return(0);
		} break;

	case WM_PAINT: //called when window needs repainting
		{//simply validate the window
		    
			//ValidateRect(hwnd, NULL);
			hdc = BeginPaint(hwnd,&ps);
		    EndPaint(hwnd,&ps);
			
			return(0);
		} break;
	case WM_KEYDOWN:
		{
			int virtual_code= (int)wparam;
			int key_bits= (int)lparam;
			
			switch(virtual_code)
			{
			case VK_ESCAPE :
				{
					PostQuitMessage(0);
					break;
				}
			}
			return(0);//let windows know u handled the message
		}
	case WM_DESTROY: 
		{// kill the application			
			
			//delete pens, if you dont delete all pens you'll get resource leeks
			DeleteObject(white_pen);
			DeleteObject(black_pen);
			DeleteObject(green_pen);
			DeleteObject(green_brush);

			//close the program
			PostQuitMessage(0);
			return(0);
		} break;

	default:break;

    } // end main switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

//\\\\\\\\\\\\\\\\\\\\\\\\ WINMAIN ////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{

	WNDCLASS winclass;	// this will hold the class created
	HWND	 hwnd;		// generic window handle
	MSG		 msg;		// generic message
	HDC		 hmdc;      //holds a device context for the whole screen	

	//fill in the window class stucture
	winclass.style			= CS_DBLCLKS | CS_OWNDC;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	winclass.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDR_MENU1);
	winclass.lpszClassName	= WINDOW_CLASS_NAME;

	// register the window class
	if (!RegisterClass(&winclass))
		return(0);

	// create the window
	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME, // class
							  "Eating the Desktop",	 // title
							  WS_VISIBLE, //Flags for window style WS
						 	  0,0,	   // x,y
							  0,  // width
						      0, // height
							  NULL,	   // handle to parent 
							  NULL,	   // handle to menu
							  hinstance,// instance
							  NULL)))	// creation parms
	{
		MessageBox(hwnd, "Window Could not be Created", NULL, MB_OK); //NULL is default for Error
		return(0);
	}

	// save the window handle and instance in a global
	main_window_handle = hwnd;
	main_instance      = hinstance;

	
	// enter main event loop
	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) //get the first message on the Queue
		{ 
			// test if this is a quit message
			if (msg.message == WM_QUIT)
				break;
	
			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		
    	//Get the device context of the parent window of the window being created by this
		//program. Which seems to be the desktop. But it draws over any acvtive or inactive
		//window
		hmdc= GetWindowDC( GetDesktopWindow() ); 
										   
		DrawBug1(hmdc,  black_pen, green_pen, green_brush);

		//slow things down a bit
		Sleep(50);
		ReleaseDC(GetDesktopWindow(), hmdc); //Release the device context

	} // end while

	

	// return to Windows like this
	return(msg.wParam);

} // end WinMain

