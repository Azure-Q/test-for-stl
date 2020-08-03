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

//设计演讲管理类
class speechManager
{
public:
	//构造函数
	speechManager();

	//菜单功能
	void show_Menu();

	//初始化容器和属性
	void initSpeech();

	//保存第一轮比赛选手的编号
	vector<int> v1;

	//保存第一轮晋级的选手的编号
	vector<int> v2;

	//保存胜出的前三名选手编号
	vector<int> vVictory;

	//存放编号及对应选手编号容器，speaker是一个类
	map<int, speaker> m_speaker;

	//存放比赛的轮数
	int m_Index;

	//初始化创建12名选手
	void createSpeaker();

	//比赛流程控制
	void startSpeech();

	//抽签
	void speechDraw();

	//开始比赛
	void speechContest();

	//显示比赛分数
	void showScore();

	//保存分数
	void saveRecord();

	//读取分数记录
	void loadRecord();

	//查看分数记录
	void showRecord();

	//判断文件是否为空
	bool fileIsEmpty;

	//存放往届分数的容器
	map<int, vector<string>> m_Record;

	//清空文件
	void clearRecord();

	//退出系统
	void exitSystem();

	//析构函数
	~speechManager();
};