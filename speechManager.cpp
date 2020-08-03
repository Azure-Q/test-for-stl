#include "speechManager.h"

//���캯��
speechManager::speechManager()
{
	//��ʼ������������
	this->initSpeech();
	//����ѡ��
	this->createSpeaker();
	//���������¼
	this->loadRecord();
}

//�˵�����
void speechManager::show_Menu()
{
	cout << "***************************************" << endl;
	cout << "*********** ��ӭ�μ��ݽ����� **********" << endl;
	cout << "*********** 1.��ʼ�ݽ����� ************" << endl;
	cout << "*********** 2.�鿴�����¼ ************" << endl;
	cout << "*********** 3.��ձ�����¼ ************" << endl;
	cout << "*********** 0.�˳��������� ************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void speechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

//��ʼ������������
void speechManager::initSpeech()
{
	//���������
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();

	//��ʼ����������
	this->m_Index = 1;
	//��ʼ����¼����(ÿ��Ļ�ʤ��)
	this->m_Record.clear();
}

//����12���ݽ���
void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++)
			sp.m_Score[i] = 0;

		this->v1.push_back(i + 10001);
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

//�������̿���(һ��ı���)
void speechManager::startSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ�������
	this->showScore();

	//�ڶ��ֱ���
	this->m_Index++;
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ���ս��
	this->showScore();
	//4������������ļ���
	this->saveRecord();

	cout << "���������ϣ�" << endl;

	//��ʼ������������
	this->initSpeech();
	//����ѡ��
	this->createSpeaker();
	//���������¼
	this->loadRecord();
	system("pause");
	system("cls");
}

//��ǩ
void speechManager::speechDraw()
{
	cout << "��" << this->m_Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1)   //��һ�ֱ���
	{
		//ʹ��random_shuffle���������м�����������(���)
		random_shuffle(v1.begin(),v1.end());
		for (auto it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else    //�ڶ��ֱ���
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

//��ʼ����
void speechManager::speechContest()
{
	cout << "------------��" << this->m_Index << "����ʽ������ʼ-----------"<<endl;
	multimap<double, int, greater<int> > groupScore;
	int num = 0;    //��¼��Ա��Ŀ��6��һ��
	vector<int> v_Src;  //��������Ա����
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
		d.pop_front();  //ȥ����߷�
		d.pop_back();   //ȥ����ͷ�

		double sum = accumulate(d.begin(),d.end(),0.0f);
		double avg = sum / (double)d.size();
		this->m_speaker[*it].m_Score[this->m_Index - 1] = avg;
		groupScore.insert(make_pair(avg,*it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "�� ������"<< this->m_speaker[it->second].m_Name << "�� �ɼ���" << this->m_speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			//ȡÿ�����ǰ����������һ�ֱ���
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
	cout << "------------ ��" << this->m_Index << "�ֱ����Ѿ�����-----------" << endl;
	system("pause");
}

//ѡ�ֽ���
void speechManager::showScore()
{
	if(this->m_Index==1)
		cout << "-----------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
	else
		cout << "-----------���ջ�ʤѡ����Ϣ���£�-----------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
		v = v2;         //��һ�ֽ����ķ���v2����
	else
		v = vVictory;   //�ڶ���ʤ�ķ���vVictory����
	for(auto it=v.begin();it!=v.end();it++)
		cout << "ѡ�ֱ�ţ�" << *it<< "������" << m_speaker[*it].m_Name << "�ɼ���" << m_speaker[*it].m_Score[this->m_Index - 1] << endl;
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//����ѡ�ַ���
void speechManager::saveRecord()
{
	//�ӳ���������ļ�
	ofstream ofs;     
	//������ķ�ʽ��׷�ӵķ�ʽ���ļ�
	ofs.open("speech.csv",ios::out|ios::app);
	for (auto it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�Ѿ����棡" << endl;
	this->fileIsEmpty = false;
}

//��ȡ������¼
void speechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);  //���ļ����뵽��ʾ��
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;      //�ȶ�ȡһ�����ݿ��Ƿ�Ϊ�����ж��Ƿ�������
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);     //�������������ݷŻ�ȥ
	string data;
	int index = 0;
	while (ifs>>data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);   //��start��ʼ����","
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

//�鿴������¼
void speechManager::showRecord()
{
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout<<"��"<<i+1<<"��"<<
			"�ھ����:\t" << this->m_Record[i][0] << ", ����: " << this->m_Record[i][1] <<" "
			"\t�Ǿ����;" << this->m_Record[i][2] << ", ������" << this->m_Record[i][3] << " "
			"\t�������;" << this->m_Record[i][4] << ", ������" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void speechManager::clearRecord()
{
	cout << "�Ƿ�ȷ������ļ���" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv",ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeech();
		//����ѡ��
		this->createSpeaker();
		//���������¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

//��������
speechManager::~speechManager() {}