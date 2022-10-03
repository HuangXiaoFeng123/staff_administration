#include "manager.h"

Manager::Manager(int id, string name, int did)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = did;
}
void Manager::showInfo(void)
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：完成老板的任务并通知下属" << endl;
}
string Manager::getDeptName(void)
{
	return string("经理");
}