#include <iostream>
#include <string>
#include <time.h>
#include "speechManager.h"
using namespace std;

int main()
{
	srand(time(NULL));
	speechManager sm;
	//用于存储用户的输入
	int choice = 0; 
	while (1)
	{
		sm.show_Menu();
		cout << "请输入您的选择：";
		cin >> choice;
		switch (choice)
		{
		//开始比赛
		case 1:
			sm.startSpeech();
			break;
		//查看往届比赛记录
		case 2:
			sm.showRecord();
			break;
		//清空比赛记录
		case 3:
			sm.clearRecord();
			break;
		//退出比赛程序
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}