// sgHexGrid2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"sigr.h"
using namespace gh;

int KEY_UP = 2490368; //up
int KEY_DOWN = 2621440; //down
int KEY_LEFT = 2424832; //left
int KEY_RIGHT = 2555904; //right


int main()
{
	sigr si(600, 800, 12, 16);
	si.draw();
	si.b.Rand();

	//resizeWindow(si.name(), 500, 500);
	//String name = si.name();
	//setMouseCallback(si.name(), on_MouseMain, (void*) &si.c);
	//RECT w;

	int key = '0';
	while(1)
	{
		key = '0';
		si.b.Rand();
		si.draw();

		//////

		//GetClientRect(si.handle(), &w);
		//cout << w.bottom << " " << w.left << " " << w.right << " " << w.top << endl;
		//GetWindowRect(si.handle(), &w);
		//cout << w.bottom << " " << w.left << " " << w.right << " " << w.top << endl;
		//cout << w.bottom - w.top - 41 << " " << w.right - w.left - 18 << endl;
		///*401 658*/
		///*360 640*/
		///* 41  18*/

		//cout << IsWindow(si.handle()) << endl;
		/*cout << si.c.R() << endl;*/


		//////
		key = waitKeyEx(100);
		if (key == ' ')
			break;
		else if (key == '+')
			si.c.setR(si.c.r() + 1);
		else if (key == '-')
			si.c.setR(si.c.r() - 1);
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
			resizeWindow(si.name(), 500, 500);
		}

	}
	cout << IsWindow(si.handle()) << endl;
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
