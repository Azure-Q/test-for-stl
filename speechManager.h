#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <deque>
#include <algorithm>
#include <numeric>
#include <string>
#include "speaker.h"
using namespace std;

//����ݽ�������
class speechManager
{
public:
	//���캯��
	speechManager();

	//�˵�����
	void show_Menu();

	//��ʼ������������
	void initSpeech();

	//�����һ�ֱ���ѡ�ֵı��
	vector<int> v1;

	//�����һ�ֽ�����ѡ�ֵı��
	vector<int> v2;

	//����ʤ����ǰ����ѡ�ֱ��
	vector<int> vVictory;

	//��ű�ż���Ӧѡ�ֱ��������speaker��һ����
	map<int, speaker> m_speaker;

	//��ű���������
	int m_Index;

	//��ʼ������12��ѡ��
	void createSpeaker();

	//�������̿���
	void startSpeech();

	//��ǩ
	void speechDraw();

	//��ʼ����
	void speechContest();

	//��ʾ��������
	void showScore();

	//�������
	void saveRecord();

	//��ȡ������¼
	void loadRecord();

	//�鿴������¼
	void showRecord();

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//����������������
	map<int, vector<string>> m_Record;

	//����ļ�
	void clearRecord();

	//�˳�ϵͳ
	void exitSystem();

	//��������
	~speechManager();
};