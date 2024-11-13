#include <iostream>
#include <string>
#define MAX 1000//定义最大人数
using namespace std;

struct Person//联系人结构体
{
	string name;
	string sex;
	int age;
	string phone;
	string mail;
};

struct AddressBook
{
	Person personArray[MAX];
	int m_size;
};

int isExist(AddressBook *abs, string name)//查找数据是否存在
{
	int i;
	for(i=0;i < abs->m_size; i++)
	{
		if (abs->personArray[i].name == name)
		{
			break;
		}
	}
	if (i == abs->m_size)
	{
		return -1;
	}
	else
	{
		return i;
	}
};

void showmenu()//通讯录菜单
{
	cout<<"************************"<<endl;
	cout<<"*****1、新建联系人*****"<<endl;
	cout<<"*****2、显示联系人*****"<<endl;
	cout<<"*****3、删除联系人*****"<<endl;
	cout<<"*****4、查找联系人*****"<<endl;
	cout<<"*****5、修改联系人*****"<<endl;
	cout<<"*****6、清空联系人*****"<<endl;
	cout<<"*****0、退出通讯录*****"<<endl;
	cout<<"************************"<<endl;
};

void showmodifymenu()//修改联系人菜单
{
	cout<<"**********************"<<endl;
	cout<<"*****1、修改姓名*****"<<endl;
	cout<<"*****2、修改年龄*****"<<endl;
	cout<<"*****3、修改电话*****"<<endl;
	cout<<"*****4、修改邮箱*****"<<endl;
	cout<<"*****5、退出修改*****"<<endl;
	cout<<"**********************"<<endl;
}

void addPerson(AddressBook * abs)//添加联系人
{
	if (abs->m_size == MAX)
	{
		cout<<"通讯录已满，无法添加"<<endl;
		return ;
	}
	else
	{
		int age;
		string name,sex,phone,mail;

		cout<<"请输入姓名:"<<endl;
		cin>>name;
		cout<<"请输入性别:"<<endl;
		cin>>sex;	
		cout<<"请输入年龄:"<<endl;
		cin>>age;	
		cout<<"请输入电话:"<<endl;
		cin>>phone;		
		cout<<"请输入邮箱:"<<endl;
		cin>>mail;		
		abs->personArray[abs->m_size]={name,sex,age,phone,mail};
		abs->m_size++;
		cout<<"已添加联系人:"<<name<<endl;		
	}
};

void showPerson(AddressBook *abs)//显示联系人
{
	if (abs->m_size == 0)
	{
		cout<<"空，请添加"<<endl;
		return;
	}
	else
	{
		for (int i = 0;i < abs->m_size; i++)
		{
			cout<<"姓名:"<<abs->personArray[i].name<<"  性别:"<<abs->personArray[i].sex<<"  年龄:"<<abs->personArray[i].age<<"  电话:"<<abs->personArray[i].phone<<"  邮箱:"<<abs->personArray[i].mail<<endl;
		}
	}
};

void deletePerson(AddressBook *abs)//删除联系人
{
	if (abs->m_size == 0)
	{
		cout<<"空，请添加"<<endl;
		return;
	}
	else
	{
		string name;;
		cout<<"删除联系人的姓名："<<endl;
		cin>>name;

		int ret = isExist(abs,name);
		if (ret == -1)
		{
			cout<<"没有该联系人"<<endl;
		}
		else
		{
			int select;
			cout<<"你确定要删除吗？ Yes--1 or No--0"<<endl;
			cin>>select;
			switch (select)
			{
			case 1:
				for (int i = ret;i < abs->m_size;i++)
				{
					abs->personArray[i]=abs->personArray[i+1];
				}
				abs->m_size--;
				cout<<"删除成功"<<endl;
				break;
			case 0:
				return;
				break;
			default:
				break;
			}
		}
	}
};

void findPerson(AddressBook *abs)//查找联系人
{
	if (abs->m_size == 0)
	{
		cout<<"空，请添加"<<endl;
		return;
	}
	else
	{
		string name;;
		cout<<"查找联系人的姓名："<<endl;
		cin>>name;

		int ret = isExist(abs,name);
		if (ret == -1)
		{
			cout<<"没有该联系人"<<endl;
		}
		else
		{
			cout<<"姓名:"<<abs->personArray[ret].name<<"性别:"<<abs->personArray[ret].sex<<"年龄:"<<abs->personArray[ret].age<<endl;
			cout<<"电话"<<abs->personArray[ret].phone<<endl;
			cout<<"邮箱"<<abs->personArray[ret].mail<<endl;
		}
	}
};

void modifyPerson(AddressBook *abs)//修改联系人
{
	if (abs->m_size == 0)
	{
		cout<<"空，请添加"<<endl;
		return;
	}
	else
	{
		string name;;
		cout<<"修改联系人的姓名："<<endl;
		cin>>name;

		int ret = isExist(abs,name);
		if (ret == -1)
		{
			cout<<"没有该联系人"<<endl;
		}
		else
		{
			int age;
			string name,sex,phone,mail;
			int select = 0;
			while (true)
			{
				showmodifymenu();
				cin>>select;
				switch(select)
				{
				case 1:
					cout<<"修改后的姓名："<<endl;
					cin>>name;
					abs->personArray[ret].name = name;
					break;
				case 2:
					cout<<"修改后的年龄："<<endl;
					cin>>age;
					abs->personArray[ret].age = age;
					break;
				case 3:
					cout<<"修改后的电话："<<endl;
					cin>>phone;
					abs->personArray[ret].phone = phone;
					break;
				case 4:
					cout<<"修改后的邮箱："<<endl;
					cin>>mail;
					abs->personArray[ret].mail = mail;
					break;
				case 5:				
					cout << "退出修改... ..." << endl;
					return ;
					break;
				default:
					break;
				}
			}
			
		}
	}
};

void clearPerson(AddressBook *abs)//清空通讯录
{
	int select;
	cout<<"你确定要清空通讯录吗？ Yes--1 or No--0"<<endl;
	cin>>select;
	switch (select)
	{
	case 1:
		abs->m_size = 0;
		cout<<"已清空"<<endl;
		break;
	case 0:
		return;
		break;
	default:
		break;
	}
};

int main()
{
	AddressBook abs;
	abs.m_size = 0;
	int select = 0;

	while(true)
	{
		showmenu();
		cin >> select;

		switch(select)//通讯录操作
		{
			case 1:
				addPerson(&abs);
				break;
			case 2:
				showPerson(&abs);
				break;
			case 3:
				deletePerson(&abs);
				break;
			case 4:
				findPerson(&abs);
				break;
			case 5:
				modifyPerson(&abs);
				break;
			case 6:
				clearPerson(&abs);
				break;
			case 0:
				cout << "退出通讯录... ..." << endl;
				return 0;
				break;
			default:
				break;
		}
	}

	return 0;
}
