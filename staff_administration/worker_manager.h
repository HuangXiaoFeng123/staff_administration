#pragma once
#include <iostream>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;
#define FILENAME "filename.txt"

class Worker_Manager
{
public:
	int m_EmpNum;                //记录原来职工人数
	Worker** m_EmpArray;         //职工数组指针
	bool m_FileIsEmpty;
	Worker_Manager(void);
	~Worker_Manager(void);
	void show_Menu(void);
	void exit_System(void);
	void add_Emp(void);
	void save(void);
	int get_EmpNum(void);
	void init_Emp(void);
	void show_Emp(void);
	void del_Emp(void);
	int is_Exist(int id);
	void mod_Emp(void);
	void find_Emp(void);
	void sort_Emp(void);
	void clean_Emp(void);
};