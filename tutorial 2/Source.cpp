#include <Windows.h>
using namespace std;

const char g_szClassName[]="myWinClass";

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg)
	{
	case WM_LBUTTONDOWN:{
		char szFileName[MAX_PATH];
		HINSTANCE hInstance = GetModuleHandle(NULL);

		GetModuleFileName(hInstance, szFileName, MAX_PATH);
		MessageBox(hWnd, szFileName, "This prog is:", MB_OK| MB_ICONINFORMATION);
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,msg, wParam, lParam);
		break;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	WNDCLASSEX wc;
	HWND hWnd;
	MSG msg;

	//Step 1: Registering the Window Class
	wc.cbSize =			sizeof(WNDCLASSEX);
	wc.style =			0;
	wc.lpfnWndProc =	WndProc;
	wc.cbClsExtra =		0;
	wc.cbWndExtra =		0;
	wc.hInstance =		hInstance;
	wc.hIcon =			LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor =		LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground =	(HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName =	NULL;
	wc.lpszClassName =	g_szClassName;
	wc.hIconSm =		LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc) ){
		MessageBox(NULL, "Window reg failed!", "Error!", MB_ICONEXCLAMATION| MB_OK);
		return 0;
	}

	//step 2: Creating the Window

	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my win",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, hInstance, NULL);

	if(hWnd == NULL){
		MessageBox(NULL, "Win creation failed!", "Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//Step 3: The Message Loop

	while(GetMessage(&msg, NULL, 0, 0)>0){
		TranslateMessage (&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
