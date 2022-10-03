#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Employee:public Worker
{
public:
	Employee(int id,string name,int did);
	void showInfo(void);
	string getDeptName(void);
};