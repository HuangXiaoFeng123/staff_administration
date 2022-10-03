#include "worker_manager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main(void)
{
	Worker_Manager wm;
	int choice;
	while (1)
	{
		wm.show_Menu();
		cout << "请输入功能选择" << endl;
		cin >> choice;
		switch (choice)
		{
			case 0:
				wm.exit_System();
				break;
			case 1:
				wm.add_Emp();
				break;
			case 2:
				wm.show_Emp();
				break;
			case 3:
				wm.del_Emp();
				break;
			case 4:
				wm.mod_Emp();
				break;
			case 5:
				wm.find_Emp();
				break;
			case 6:
				wm.sort_Emp();
				break;
			case 7:
				wm.clean_Emp();
				break;
			default:
				system("cls");
				break;
		}
	}
	return 0;
}