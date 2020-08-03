#include <iostream>
#include <string>
#include <time.h>
#include "speechManager.h"
using namespace std;

int main()
{
	srand(time(NULL));
	speechManager sm;
	//���ڴ洢�û�������
	int choice = 0; 
	while (1)
	{
		sm.show_Menu();
		cout << "����������ѡ��";
		cin >> choice;
		switch (choice)
		{
		//��ʼ����
		case 1:
			sm.startSpeech();
			break;
		//�鿴���������¼
		case 2:
			sm.showRecord();
			break;
		//��ձ�����¼
		case 3:
			sm.clearRecord();
			break;
		//�˳���������
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