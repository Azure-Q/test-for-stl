#include "speechManager.h"

//构造函数
speechManager::speechManager()
{
	//初始化容器和属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();
}

//菜单功能
void speechManager::show_Menu()
{
	cout << "***************************************" << endl;
	cout << "*********** 欢迎参加演讲比赛 **********" << endl;
	cout << "*********** 1.开始演讲比赛 ************" << endl;
	cout << "*********** 2.查看往届记录 ************" << endl;
	cout << "*********** 3.清空比赛记录 ************" << endl;
	cout << "*********** 0.退出比赛程序 ************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}

//退出系统
void speechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//初始化容器和属性
void speechManager::initSpeech()
{
	//容器都清空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();

	//初始化比赛轮数
	this->m_Index = 1;
	//初始化记录容器(每届的获胜者)
	this->m_Record.clear();
}

//创建12名演讲者
void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++)
			sp.m_Score[i] = 0;

		this->v1.push_back(i + 10001);
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

//比赛流程控制(一届的比赛)
void speechManager::startSpeech()
{
	//第一轮比赛
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示晋级结果
	this->showScore();

	//第二轮比赛
	this->m_Index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示最终结果
	this->showScore();
	//4、保存分数到文件中
	this->saveRecord();

	cout << "本届比赛完毕！" << endl;

	//初始化容器和属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();
	system("pause");
	system("cls");
}

//抽签
void speechManager::speechDraw()
{
	cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1)   //第一轮比赛
	{
		//使用random_shuffle函数对序列记性重新排序(随机)
		random_shuffle(v1.begin(),v1.end());
		for (auto it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else    //第二轮比赛
	{
		random_shuffle(v2.begin(), v2.end());
		for (auto it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------------------------------------------------" << endl;
	system("pause");
	cout << endl;
}

//开始比赛
void speechManager::speechContest()
{
	cout << "------------第" << this->m_Index << "轮正式比赛开始-----------"<<endl;
	multimap<double, int, greater<int> > groupScore;
	int num = 0;    //记录人员数目，6人一组
	vector<int> v_Src;  //比赛的人员容器
	if (this->m_Index == 1)
		v_Src = v1;
	else
		v_Src = v2;

	for (auto it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();  //去掉最高分
		d.pop_back();   //去掉最低分

		double sum = accumulate(d.begin(),d.end(),0.0f);
		double avg = sum / (double)d.size();
		this->m_speaker[*it].m_Score[this->m_Index - 1] = avg;
		groupScore.insert(make_pair(avg,*it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "， 姓名："<< this->m_speaker[it->second].m_Name << "， 成绩：" << this->m_speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			//取每个组的前三名进入下一轮比赛
			int count = 0;    
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
					v2.push_back((*it).second);
				else
					vVictory.push_back((*it).second);
			}
			groupScore.clear();
		}
	}
	cout << "------------ 第" << this->m_Index << "轮比赛已经结束-----------" << endl;
	system("pause");
}

//选手晋级
void speechManager::showScore()
{
	if(this->m_Index==1)
		cout << "-----------第" << this->m_Index << "轮晋级选手信息如下：-----------" << endl;
	else
		cout << "-----------最终获胜选手信息如下：-----------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
		v = v2;         //第一轮晋级的放在v2里面
	else
		v = vVictory;   //第二获胜的放在vVictory里面
	for(auto it=v.begin();it!=v.end();it++)
		cout << "选手编号：" << *it<< "姓名：" << m_speaker[*it].m_Name << "成绩：" << m_speaker[*it].m_Score[this->m_Index - 1] << endl;
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//保存选手分数
void speechManager::saveRecord()
{
	//从程序输出到文件
	ofstream ofs;     
	//以输出的方式或追加的方式打开文件
	ofs.open("speech.csv",ios::out|ios::app);
	for (auto it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存！" << endl;
	this->fileIsEmpty = false;
}

//读取分数记录
void speechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);  //从文件输入到显示器
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;      //先读取一个数据看是否为空来判断是否有数据
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);     //将读出来的数据放回去
	string data;
	int index = 0;
	while (ifs>>data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);   //从start开始查找","
			if (pos == -1)
				break;
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index,v));
		index++;
	}
	ifs.close();
}

//查看分数记录
void speechManager::showRecord()
{
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout<<"第"<<i+1<<"届"<<
			"冠军编号:\t" << this->m_Record[i][0] << ", 分数: " << this->m_Record[i][1] <<" "
			"\t亚军编号;" << this->m_Record[i][2] << ", 分数：" << this->m_Record[i][3] << " "
			"\t季军编号;" << this->m_Record[i][4] << ", 分数：" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

//清空记录
void speechManager::clearRecord()
{
	cout << "是否确定清空文件？" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv",ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();
		//创建选手
		this->createSpeaker();
		//加载往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

//析构函数
speechManager::~speechManager() {}