#include "worker_manager.h"

Worker_Manager::Worker_Manager(void)
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())                       //文件不存在
	{
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return ;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())                            //文件为空
	{
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];     //开辟空间
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
	cout << "**********欢迎使用职工管理系统！**********" << endl;
	cout << "**************0.退出管理程序**************" << endl;
	cout << "**************1.增加职工信息**************" << endl;
	cout << "**************2.显示职工信息**************" << endl;
	cout << "**************3.删除职工信息**************" << endl;
	cout << "**************4.修改职工信息**************" << endl;
	cout << "**************5.查找职工信息**************" << endl;
	cout << "**************6.按照编号排序**************" << endl;
	cout << "**************7.清空所有文档**************" << endl;
	cout << "******************************************" << endl;
}
void Worker_Manager::exit_System(void)
{
	cout << "欢迎下次使用" << endl;
	exit(0);
}
void Worker_Manager::add_Emp(void)
{
	cout << "请输入添加职工的数量" << endl;
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
			cout << "请输入第" << i + 1 << "个新员工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新员工姓名" << endl;
			cin >> name;
			cout << "请选择职工的岗位" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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
		this->m_EmpArray = newSpace;         //更新指向
		this->m_EmpNum = newSize;            //更新人数
		this->m_FileIsEmpty = false;         //更新文件标志
		cout << "成功添加" << addNum << "名新职工" << endl;
		this->save();
	}
	else
	{
		cout << "添加失败" << endl;
	}
	system("pause");
	system("cls");
}
void Worker_Manager::save(void)
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);                     //写入
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
		this->m_EmpArray[index] = worker;                     //存入数据
		index++;
	}
	ifs.close();
}
void Worker_Manager::show_Emp(void)
{
	if (this->m_FileIsEmpty)                                  //为空
	{
		cout << "文件不存在或为空" << endl;
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
		cout << "文件为空或不存在" << endl;
	else
	{
		cout << "请输入要删除的职工的编号" << endl;
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
			cout << "删除成功" << endl;
		}
		else
			cout << "删除失败，职工不存在" << endl;
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
		cout << "文件不存在或为空" << endl;
	else
	{
		cout << "请输入要修改员工的编号" << endl;
		int id, index;
		cin >> id;
		index = this->is_Exist(id);
		if (index != -1)
		{
			delete this->m_EmpArray[index];
			int newid;
			string name;
			int did;
			cout << "请输入新的员工编号值" << endl;
			cin >> newid;
			cout << "请输入新的员工姓名" << endl;
			cin >> name;
			cout << "请输入新的岗位" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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
			cout << "修改成功" << endl;
			this->save();
		}
		else
			cout << "员工编号不存在,修改失败" << endl;
	}
	system("pause");
	system("cls");
}
void Worker_Manager::find_Emp(void)
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或为空" << endl;
	else
	{
		cout << "请输入查找的方式" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			int id, index;
			cout << "请输入职工编号" << endl;
			cin >> id;
			index = this->is_Exist(id);
			if (index != -1)
			{
				cout << "查找成功，信息如下" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
				cout << "查无此人" << endl;
		}
		else if (select == 2)
		{
			string name;
			bool flag = false;
			cout << "请输入职工姓名" << endl;
			cin >> name;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，信息如下" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
				cout << "查找失败，查无此人" << endl;
		}
		else
			cout << "输入错误" << endl;
	}
	system("pause");
	system("cls");
}
void Worker_Manager::sort_Emp(void)
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或者不存在" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << "1.按照职工编号进行升序" << endl;
		cout << "2.按照职工编号进行降序" << endl;
		int select;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrmax = i;
			for (int j = i+1; j < this->m_EmpNum; j++)
			{
				if (select == 1)                 //升序
				{
					if (this->m_EmpArray[minOrmax]->m_ID > this->m_EmpArray[j]->m_ID)
						minOrmax = j;
				}
				else                             //降序
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
		cout << "排序成功，结果如下" << endl;
		this->save();
		this->show_Emp();
	}
}
void Worker_Manager::clean_Emp(void)
{
	cout << "确认情况吗？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);       //删除文件后重新创建
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
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}