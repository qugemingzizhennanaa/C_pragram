#pragma once //防止头文件重复包含

#include <fstream>
#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS 1
#define FILENAME "workermanager.txt"

using namespace std;

class Worker {
public:
  //显示个人信息
  virtual void showInfo() = 0;
  //获取单位信息
  virtual string getDepartment() = 0;

  int m_ID;      //职工编号
  string m_Name; //姓名
  int m_DepID;   //部门ID
};

class Employee : public Worker {
public:
  Employee(int ID, string Name, int DepID);

  void showInfo();

  string getDepartment();
};

class Manager : public Worker {
public:
  Manager(int ID, string Name, int DepID);

  void showInfo();

  string getDepartment();
};

class Boss : public Worker {
public:
  Boss(int ID, string Name, int DepID);

  void showInfo();

  string getDepartment();
};

class WorkerManager {
public:
  WorkerManager(); //构造函数

  void ShowMenu(); //展示菜单

  int m_EmpNum; //记录职工人数

  Worker **m_EmpArray; //职工数组指针

  void Add_Emp(); //添加职工

  void save_Data(); //保存数据

  bool m_FileIsEmpty; //文件是否为空

  int get_EmpNum(); //获取员工人数

  void init_Emp(); //初始化员工

  void Show_Emp(); //展示职工

  int get_Worker(int ID); //通过编号判断员工是否存在

  int get_Worker(string Name); //通过名字判断员工是否存在

  void Delete_Emp(); //删除员工

  void Modify_Emp(); //修改员工

  void Find_Emp(); //查找员工

  void Sort_Emp(); //按照编号排序

  void Clear_File(); //清空文档

  ~WorkerManager(); //析构函数
};