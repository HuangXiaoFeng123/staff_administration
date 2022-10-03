#include "worker_manager.h"

Worker_Manager::Worker_Manager(void)
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())                       //�ļ�������
	{
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return ;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())                            //�ļ�Ϊ��
	{
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];     //���ٿռ�
	this->init_Emp();
}
Worker_Manager::~Worker_Manager(void)
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}	
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
void Worker_Manager::show_Menu(void)
{
	cout << "******************************************" << endl;
	cout << "**********��ӭʹ��ְ������ϵͳ��**********" << endl;
	cout << "**************0.�˳��������**************" << endl;
	cout << "**************1.����ְ����Ϣ**************" << endl;
	cout << "**************2.��ʾְ����Ϣ**************" << endl;
	cout << "**************3.ɾ��ְ����Ϣ**************" << endl;
	cout << "**************4.�޸�ְ����Ϣ**************" << endl;
	cout << "**************5.����ְ����Ϣ**************" << endl;
	cout << "**************6.���ձ������**************" << endl;
	cout << "**************7.��������ĵ�**************" << endl;
	cout << "******************************************" << endl;
}
void Worker_Manager::exit_System(void)
{
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}
void Worker_Manager::add_Emp(void)
{
	cout << "���������ְ��������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int idSelect;
			cout << "�������" << i + 1 << "����Ա�����" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����Ա������" << endl;
			cin >> name;
			cout << "��ѡ��ְ���ĸ�λ" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> idSelect;
			Worker* worker = NULL;
			switch (idSelect)
			{
				case 1:
					worker = new Employee(id, name, 1);
					break;
				case 2:
					worker = new Manager(id, name, 2);
					break;
				case 3:
					worker = new Boss(id, name, 3);
					break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;         //����ָ��
		this->m_EmpNum = newSize;            //��������
		this->m_FileIsEmpty = false;         //�����ļ���־
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
		this->save();
	}
	else
	{
		cout << "���ʧ��" << endl;
	}
	system("pause");
	system("cls");
}
void Worker_Manager::save(void)
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);                     //д��
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << "  "
			<< this->m_EmpArray[i]->m_Name << "  "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	ofs.close();
}
int Worker_Manager::get_EmpNum(void)
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	return num;
}
void Worker_Manager::init_Emp(void)
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker* worker = NULL;
		if (did == 1)
			worker = new Employee(id, name, did);
		else if (did == 2)
			worker = new Manager(id, name, did);
		else
			worker = new Boss(id, name, did);
		this->m_EmpArray[index] = worker;                     //��������
		index++;
	}
	ifs.close();
}
void Worker_Manager::show_Emp(void)
{
	if (this->m_FileIsEmpty)                                  //Ϊ��
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
void Worker_Manager::del_Emp(void)
{
	if (this->m_FileIsEmpty)
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
	else
	{
		cout << "������Ҫɾ����ְ���ı��" << endl;
		int id, index;
		cin >> id;
		index = this->is_Exist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
			cout << "ɾ��ʧ�ܣ�ְ��������" << endl;
	}
	system("pause");
	system("cls");
}
int Worker_Manager::is_Exist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
void Worker_Manager::mod_Emp(void)
{
	if (this->m_FileIsEmpty)
		cout << "�ļ������ڻ�Ϊ��" << endl;
	else
	{
		cout << "������Ҫ�޸�Ա���ı��" << endl;
		int id, index;
		cin >> id;
		index = this->is_Exist(id);
		if (index != -1)
		{
			delete this->m_EmpArray[index];
			int newid;
			string name;
			int did;
			cout << "�������µ�Ա�����ֵ" << endl;
			cin >> newid;
			cout << "�������µ�Ա������" << endl;
			cin >> name;
			cout << "�������µĸ�λ" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> did;
			Worker* worker = NULL;
			switch (did)
			{
				case 1:
					worker = new Employee(newid, name, 1);
					break;
				case 2:
					worker = new Manager(newid, name, 2);
					break;
				case 3:
					worker = new Boss(newid, name, 3);
					break;
			}
			this->m_EmpArray[index] = worker;
			cout << "�޸ĳɹ�" << endl;
			this->save();
		}
		else
			cout << "Ա����Ų�����,�޸�ʧ��" << endl;
	}
	system("pause");
	system("cls");
}
void Worker_Manager::find_Emp(void)
{
	if (this->m_FileIsEmpty)
		cout << "�ļ������ڻ�Ϊ��" << endl;
	else
	{
		cout << "��������ҵķ�ʽ" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��ְ����������" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			int id, index;
			cout << "������ְ�����" << endl;
			cin >> id;
			index = this->is_Exist(id);
			if (index != -1)
			{
				cout << "���ҳɹ�����Ϣ����" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
				cout << "���޴���" << endl;
		}
		else if (select == 2)
		{
			string name;
			bool flag = false;
			cout << "������ְ������" << endl;
			cin >> name;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ�����Ϣ����" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
				cout << "����ʧ�ܣ����޴���" << endl;
		}
		else
			cout << "�������" << endl;
	}
	system("pause");
	system("cls");
}
void Worker_Manager::sort_Emp(void)
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��߲�����" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << "1.����ְ����Ž�������" << endl;
		cout << "2.����ְ����Ž��н���" << endl;
		int select;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrmax = i;
			for (int j = i+1; j < this->m_EmpNum; j++)
			{
				if (select == 1)                 //����
				{
					if (this->m_EmpArray[minOrmax]->m_ID > this->m_EmpArray[j]->m_ID)
						minOrmax = j;
				}
				else                             //����
				{
					if (this->m_EmpArray[minOrmax]->m_ID < this->m_EmpArray[j]->m_ID)
						minOrmax = j;
				}
			}
			if (minOrmax != i)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
				this->m_EmpArray[minOrmax] = temp;
			}
		}
		cout << "����ɹ����������" << endl;
		this->save();
		this->show_Emp();
	}
}
void Worker_Manager::clean_Emp(void)
{
	cout << "ȷ�������" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);       //ɾ���ļ������´���
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}