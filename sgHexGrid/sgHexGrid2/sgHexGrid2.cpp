// sgHexGrid2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"sigr.h"
using namespace gh;

int KEY_UP = 2490368; //up
int KEY_DOWN = 2621440; //down
int KEY_LEFT = 2424832; //left
int KEY_RIGHT = 2555904; //right

BOOL CALLBACK EnumWindowsProc_0(HWND hWnd, LPARAM IProgress)
{
	if (::FindWindowExA(hWnd, NULL, "SHELLDLL_DefView", NULL) != NULL)
	{
		HWND tempHwnd = ::FindWindowExA(NULL, hWnd, "WorkerW", NULL);
		::ShowWindow(tempHwnd, 0);
	}
	return true;
}

void SetDesktop(char FormName[])
{
	setWindowProperty(FormName, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	HWND hWnd = ::FindWindowA("Progman", NULL);
	HWND my_hWnd = ::FindWindowA(NULL, FormName);

	if (hWnd != NULL && my_hWnd != NULL)
	{
		MoveWindow(my_hWnd, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), true);
		SendMessageTimeout(hWnd, 0x52c, NULL, NULL, 0, 0x3e8, NULL);
		EnumWindows(EnumWindowsProc_0, NULL);
		SetParent(my_hWnd, hWnd);
	}
}

int main()
{
	sigr si(360, 640, 12, 16);
	si.draw();
	si.show();
	//resizeWindow(si.name(), 500, 500);
	//String name = si.name();
	//setMouseCallback(si.name(), on_MouseMain, (void*) &si.c);
	char str[] = "windows1";
	cv::namedWindow("windows1", 0); //创建一个窗口
	HWND hWnd = (HWND) cvGetWindowHandle("windows1");//获取子窗口的HWND
	HWND hParentWnd = ::GetParent(hWnd);//获取父窗口HWND。父窗口是我们要用的

	//::SetWindowPos(hParentWnd, HWND_TOPMOST, 100, 1, 500, 500, SWP_NOSIZE | SWP_NOMOVE); //修改窗口为最顶部

	//隐藏窗口标题栏
	long style = GetWindowLong(hParentWnd, GWL_STYLE);
	style &= ~(WS_CAPTION);
	// style &= ~(WS_MAXIMIZEBOX);
	SetWindowLong(hParentWnd, GWL_STYLE, style);
	SetDesktop(str);
	int key = '0';
	while(1)
	{
		key = '0';

		si.draw();
		si.show();

		//key = waitKey(200);
		key = waitKeyEx(10);
		if (key == ' ')
			break;
		else if (key == '+')
			si.c.setR(si.c.r() + 1);
		else if (key == '-')
			si.c.setR(si.c.r() - 1);
		/*
		Key :2490368 up
		Key :2621440 down
		Key :2424832 left
		Key :2555904 right
		*/
		if (key == KEY_UP)
		{
			si.c.sgTarConY--;
		}
		else if (key == KEY_DOWN)
		{
			si.c.sgTarConY++;
		}
		else if (key == KEY_LEFT)
		{
			si.c.sgTarConX--;
		}
		else if (key == KEY_RIGHT)
		{
			si.c.sgTarConX++;
		}
		//cout << "Key :" << key << endl;

	}
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
