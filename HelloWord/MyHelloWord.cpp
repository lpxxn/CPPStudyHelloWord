#include<Windows.h>
#include <tchar.h>
#include<iostream>
//LRESULT CALLBACK WinProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK WinProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		hDC=BeginPaint(hwnd,&ps);
		TextOut(hDC,200,0,_T("Pain V c"),strlen("Pain V c"));
		EndPaint(hwnd,&ps);
		break;
	case WM_CLOSE:
		if(IDYES==MessageBox(hwnd,_T("over"),_T("pro"),MB_YESNO))
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam);
		break;
	}
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
	
	//return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wcx;
	wcx.cbClsExtra =0;
	wcx.cbWndExtra=0;
	wcx.hbrBackground= static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH)); //窗口背景为白色
	wcx.hCursor=LoadCursor(NULL,IDC_ARROW);
	wcx.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	
	wcx.hInstance=hInstance;
	wcx.lpfnWndProc=WinProc;
	
	
	wcx.lpszClassName=TEXT("MainWClass");									//这里MainWClass要一至
	wcx.lpszMenuName=TEXT("MainMenu");
	wcx.style=CS_HREDRAW|CS_VREDRAW;
	if(!RegisterClass(&wcx))
	{
		MessageBox(NULL,TEXT("error"),_T("Error"),NULL);
		return 1;

	}

	HWND hwnd; //声明窗口句柄
	hwnd=CreateWindow(
		TEXT("MainWClass"),													//这里MainWClass要一至
		TEXT("WindowTitle"),
		WS_OVERLAPPEDWINDOW,
		200,200,
		600,400,
		(HWND)NULL,(HMENU)NULL,wcx.hInstance,
		(LPVOID)NULL);
	//hwnd = CreateWindow( 
 //       TEXT("MainWClass"),        // name of window class 
 //       TEXT("Sample"),            // title-bar string 
 //       WS_OVERLAPPEDWINDOW, // top-level window 
 //       CW_USEDEFAULT,       // default horizontal position 
 //       CW_USEDEFAULT,       // default vertical position 
 //       CW_USEDEFAULT,       // default width 
 //       CW_USEDEFAULT,       // default height 
 //       (HWND) NULL,         // no owner window 
 //       (HMENU) NULL,        // use class menu 
 //       wcx.hInstance,           // handle to application instance 
 //       (LPVOID) NULL);      // no window-creation data 
	if(hwnd)
	{
	ShowWindow(hwnd,SW_SHOWNORMAL);
	}
	else
	{
		MessageBox(NULL,_T("error"),_T("Error"),NULL);
		return 1;
	}
	UpdateWindow(hwnd);

	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


