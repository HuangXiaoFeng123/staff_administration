#include "boss.h"

Boss::Boss(int id, string name, int did)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = did;
}
void Boss::showInfo(void)
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ���쵼ȫ����Ա" << endl;
}
string Boss::getDeptName(void)
{
	return string("�ϰ�");
}