#pragma once
#include <iostream>
using namespace std;

class Worker                  //人员抽象类
{
public:
	int m_ID;
	string m_Name;
	int m_DeptID;
	virtual void showInfo(void) = 0;
	virtual string getDeptName(void) = 0;
};