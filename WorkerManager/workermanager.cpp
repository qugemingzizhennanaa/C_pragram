#include "workermanager.h"
#include <iostream>
using namespace std;

WorkerManager::WorkerManager() {
  //文件不存在
  ifstream ifs;
  ifs.open(FILENAME, ios::in); //读文件

  if (!ifs.is_open()) {
    cout << "文件不存在" << endl;
    //初始化属性
    this->m_EmpNum = 0; //初始化人数

    this->m_EmpArray = NULL; //初始化输出

    this->m_FileIsEmpty = true; //初始化文件为空

    ifs.close();
    return;
  }
  //文件存在，数据为空
  char ch;
  ifs >> ch;
  if (ifs.eof()) {
    cout << "文件为空" << endl;
    //初始化属性
    this->m_EmpNum = 0; //初始化人数

    this->m_EmpArray = NULL; //初始化输出

    this->m_FileIsEmpty = true; //初始化文件为空

    ifs.close();
    return;
  }
  //文件存在
  ifs.close();
  int num = this->get_EmpNum();
  cout << "职工人数为" << num << endl;
  this->m_EmpNum = num;
  this->m_EmpArray = new Worker *[this->m_EmpNum]; //开辟空间
  this->init_Emp();                                //将文件存到数组中

  /*for (int i = 0; i < this->m_EmpNum; i++)
  {
    cout << this->m_EmpArray[i]->m_ID << endl;
  };*///测试
};

void WorkerManager::Add_Emp() //添加员工
{
  cout << "请输入添加职工数量:" << endl;

  int addNum;
  cin >> addNum;

  if (addNum > 0) {
    //添加
    //计算添加新空间大小
    int newSize = this->m_EmpNum + addNum;

    Worker **newSpace = new Worker *[newSize]; //开辟新空间

    if (this->m_EmpArray != NULL) //将原来空间下的数据，拷贝到新空间
    {
      for (int i = 0; i < this->m_EmpNum; i++) {
        newSpace[i] = this->m_EmpArray[i];
      }
    }

    Worker *worker = NULL;
    int ID, DepID;
    string Name;
    for (int i = 0; i < addNum; i++) {
    flag:
      cout << "请输入第" << i + 1 << "个员工的编号为：" << endl;
      cin >> ID;
      if (this->get_Worker(ID) != -1) {
        cout << "该编号已经存在，请重新输入" << endl;
        goto flag;
      }
      cout << "请输入第" << i + 1 << "个员工的姓名为：" << endl;
      cin >> Name;
      cout << "请输入第" << i + 1
           << "个员工的部门编号为：(1、普通员工;2、部门经理;3、老板)" << endl;
      cin >> DepID;

      switch (DepID) //创建员工
      {
      case 1:
        worker = new Employee(ID, Name, 1);
        break;
      case 2:
        worker = new Manager(ID, Name, 2);
        break;
      case 3:
        worker = new Boss(ID, Name, 3);
        break;
      default:
        cout << "输入有误，请重新输入!" << endl;
        i--;
        break;
      }

      newSpace[this->m_EmpNum + i] = worker;
    }

    delete[] this->m_EmpArray;   //释放空间
    this->m_EmpArray = newSpace; //更新指向
    this->m_EmpNum = newSize;    //更新个数
    this->m_FileIsEmpty = false; //文件不为空

    cout << "成功添加" << addNum << "个员工" << endl;
    this->save_Data();

  } else {
    cout << "输入数据有误" << endl;
  }
}

void WorkerManager::save_Data() //保存数据
{
  ofstream ofs;
  ofs.open(FILENAME, ios::out); //写文件

  for (int i = 0; i < this->m_EmpNum; i++) {
    ofs << this->m_EmpArray[i]->m_ID << " " << this->m_EmpArray[i]->m_Name
        << " " << this->m_EmpArray[i]->m_DepID << endl;
  }

  ofs.close();
}

void WorkerManager::ShowMenu() //展示菜单
{
  cout << "*************************************************" << endl;
  cout << "************  欢迎使用职工管理系统！  ***********" << endl;
  cout << "****************  0.退出管理程序  ***************" << endl;
  cout << "****************  1.增加职工信息  ***************" << endl;
  cout << "****************  2.显示职工信息  ***************" << endl;
  cout << "****************  3.删除离职职工  ***************" << endl;
  cout << "****************  4.修改职工信息  ***************" << endl;
  cout << "****************  5.查找职工信息  ***************" << endl;
  cout << "****************  6.按照编号排序  ***************" << endl;
  cout << "****************  7.清空所有文档  ***************" << endl;
  cout << "*************************************************" << endl;
  cout << endl;
};

int WorkerManager::get_EmpNum() //获取职工人数
{
  ifstream ifs;
  ifs.open(FILENAME, ios::in); //读文件

  int ID, DepID;
  string Name;
  int num = 0;

  while (ifs >> ID && ifs >> Name && ifs >> DepID) {
    num++; //统计人数
  }
  ifs.close();
  return num;
}

void WorkerManager::init_Emp() //初始化员工
{
  ifstream ifs;
  ifs.open(FILENAME, ios::in); //读文件

  int ID, DepID;
  string Name;
  int index = 0;

  while (ifs >> ID && ifs >> Name && ifs >> DepID) {
    Worker *worker = NULL;

    if (DepID == 1) //普通员工
    {
      worker = new Employee(ID, Name, DepID);
    } else if (DepID == 2) //部门经理
    {
      worker = new Manager(ID, Name, DepID);
    } else //老板
    {
      worker = new Boss(ID, Name, DepID);
    }

    this->m_EmpArray[index] = worker;
    index++;
  }

  ifs.close();
}

void WorkerManager::Show_Emp() //显示员工
{
  if (this->m_FileIsEmpty) {
    cout << "这里没有任何员工信息，请创建！" << endl;
  } else {
    string position;

    for (int i = 0; i < this->m_EmpNum; i++) {
      position = this->m_EmpArray[i]->getDepartment();
      cout << "|职工编号：" << this->m_EmpArray[i]->m_ID << "| ";
      cout << "|职工姓名：" << this->m_EmpArray[i]->m_Name << "| ";
      cout << "|职工部门是：" << this->m_EmpArray[i]->m_DepID << "| ";
      cout << "|职工职位是：" << position << "|" << endl;
    }
  }
}

int WorkerManager::get_Worker(int ID) //通过编号判断员工是否存在
{
  if (this->m_FileIsEmpty) {
    return -1;
  } else {
    for (int i = 0; i < this->m_EmpNum; i++) {
      if (this->m_EmpArray[i]->m_ID == ID) {
        return i; //返回员工所在位置
      }
    }
    return -1;
  }
};

int WorkerManager::get_Worker(string Name) //通过编号判断员工是否存在
{
  if (this->m_FileIsEmpty) {
    return -1;
  } else {
    for (int i = 0; i < this->m_EmpNum; i++) {
      if (this->m_EmpArray[i]->m_Name == Name) {
        cout << "该员工编号为：" << this->m_EmpArray[i]->m_ID
             << " 你确定吗(0,不是;1、是)" << endl;
        int select;
        cin >> select;
        if (select == 1) {
          return i; //返回员工所在位置
        }
      }
    }
    cout << "该员工不存在！" << endl;
    return -1;
  }
};

void WorkerManager::Delete_Emp() //删除员工
{
  cout << "你想如何查找该员工的信息:1、编号;2、姓名" << endl;
  int select, comfirm;
  int ID, DepID;
  string Name;
  cin >> select;
  int judge, i;
  switch (select) {
  case 1:
    cout << "请输入员工编号：" << endl;
    cin >> ID;
    judge = this->get_Worker(ID);
    if (judge != -1) {
      cout << "你确定删除吗？(0、不是;1、是)" << endl;
      cin >> comfirm;
      switch (comfirm) {
      case 0:
        break;
      case 1:
        for (i = judge; i < this->m_EmpNum - 1; i++) {
          this->m_EmpArray[i] = this->m_EmpArray[i + 1]; //数据前移
        }
        this->m_EmpNum--;               //更新人数
        delete this->m_EmpArray[judge]; //释放储存删除职工信息的内存
        this->m_EmpArray[judge] = nullptr; //将指针设置为nullptr，防止悬挂指针
        this->save_Data();                 //同步更新到文件
        cout << "成功删除！" << endl;
        if (this->m_EmpNum == 0) {
          this->m_FileIsEmpty = true;
        }
        break;
      default:
        break;
      }
    } else {
      cout << "查无此人！" << endl;
    }
    break;
  case 2:
    cout << "请输入员工姓名：" << endl;
    cin >> Name;
    judge = this->get_Worker(Name);
    if (judge != -1) {
      cout << "你确定删除吗？(0、不是;1、是)" << endl;
      cin >> comfirm;
      switch (comfirm) {
      case 0:
        break;
      case 1:
        for (i = judge; i < this->m_EmpNum - 1; i++) {
          this->m_EmpArray[i] = this->m_EmpArray[i + 1]; //数据前移
        }
        this->m_EmpNum--;               //更新人数
        delete this->m_EmpArray[judge]; //释放储存删除职工信息的内存
        this->m_EmpArray[judge] = nullptr; //将指针设置为nullptr，防止悬挂指针
        this->save_Data();                 //同步更新到文件
        cout << "成功删除！" << endl;
        if (this->m_EmpNum == 0) {
          this->m_FileIsEmpty = true;
        }
        break;
      default:
        break;
      }
    } else {
      cout << "查无此人！" << endl;
    }
    break;
  default:
    break;
  }
};

void WorkerManager::Modify_Emp() //修改员工
{
  cout << "你想如何查找该员工的信息:1、编号;2、姓名" << endl;
  int select, comfirm;
  int ID, DepID;
  string Name;
  cin >> select; //选择方式
  int judge, index;
  Worker *worker = NULL; //生成一个新Worker
  switch (select) {
  case 1: //通过员工ID查询
    cout << "请输入员工编号：" << endl;
    cin >> ID;
    judge = this->get_Worker(ID);
    if (judge != -1) {
      cout << "请选择你要修改的信息(1、编号;2、姓名;3、部门编号):" << endl;
      cin >> index;
      switch (index) {
      case 1: //修改编号
        cout << "该员工原编号为：" << this->m_EmpArray[judge]->m_ID
             << " 现修改为： ";
        cin >> ID;
        this->m_EmpArray[judge]->m_ID = ID;
        break;
      case 2: //修改姓名
        cout << "该员工原姓名为：" << this->m_EmpArray[judge]->m_Name
             << " 现修改为： ";
        cin >> Name;
        this->m_EmpArray[judge]->m_Name = Name;
        break;
      case 3: //修改部门编号
        cout << "该员工原部门编号为：" << this->m_EmpArray[judge]->m_DepID
             << " 现修改为(1、普通职工;2、部门经理;3、老板): ";
        cin >> DepID;
        if (DepID == 1) //普通职工
        {
          worker = new Employee(this->m_EmpArray[judge]->m_ID,
                                this->m_EmpArray[judge]->m_Name,
                                this->m_EmpArray[judge]->m_DepID);
          this->m_EmpArray[judge] = worker;
        } else if (DepID == 2) //部门经理
        {
          worker = new Manager(this->m_EmpArray[judge]->m_ID,
                               this->m_EmpArray[judge]->m_Name,
                               this->m_EmpArray[judge]->m_DepID);
          this->m_EmpArray[judge] = worker;
        } else if (DepID == 3) //老板
        {
          worker = new Boss(this->m_EmpArray[judge]->m_ID,
                            this->m_EmpArray[judge]->m_Name,
                            this->m_EmpArray[judge]->m_DepID);
          this->m_EmpArray[judge] = worker;
        }
        break;
      default:
        break;
      }
      this->save_Data(); //同步更新到文件
    } else {
      cout << "查无此人！" << endl;
    }
    break;
  case 2: //通过姓名查询
    cout << "请输入员工姓名：" << endl;
    cin >> Name;
    judge = this->get_Worker(Name);
    if (judge != -1) {
      cout << "请选择你要修改的信息(1、编号;2、姓名;3、部门编号):" << endl;
      cin >> index;
      switch (index) {
      case 1: //修改编号
        cout << "该员工原编号为：" << this->m_EmpArray[judge]->m_ID
             << " 现修改为： ";
        cin >> ID;
        this->m_EmpArray[judge]->m_ID = ID;
        break;
      case 2: //修改姓名
        cout << "该员工原姓名为：" << this->m_EmpArray[judge]->m_Name
             << " 现修改为： ";
        cin >> Name;
        this->m_EmpArray[judge]->m_Name = Name;
        break;
      case 3: //修改部门编号
        cout << "该员工原部门编号为：" << this->m_EmpArray[judge]->m_DepID
             << " 现修改为(1、普通职工;2、部门经理;3、老板): ";
        cin >> DepID;
        if (DepID == 1) //普通职工
        {
          worker = new Employee(this->m_EmpArray[judge]->m_ID,
                                this->m_EmpArray[judge]->m_Name,
                                this->m_EmpArray[judge]->m_DepID);
          this->m_EmpArray[judge] = worker;
        } else if (DepID == 2) //部门经理
        {
          worker = new Manager(this->m_EmpArray[judge]->m_ID,
                               this->m_EmpArray[judge]->m_Name,
                               this->m_EmpArray[judge]->m_DepID);
          this->m_EmpArray[judge] = worker;
        } else if (DepID == 3) //老板
        {
          worker = new Boss(this->m_EmpArray[judge]->m_ID,
                            this->m_EmpArray[judge]->m_Name,
                            this->m_EmpArray[judge]->m_DepID);
          this->m_EmpArray[judge] = worker;
        }
        break;
      default:
        break;
      }
      this->save_Data(); //同步更新到文件
    } else {
      cout << "查无此人！" << endl;
    }
    break;
  default:
    break;
  }
}

void WorkerManager::Find_Emp() //查找员工
{
  cout << "你想如何查找该员工的信息:1、编号;2、姓名" << endl;
  int select;
  int ID, DepID;
  string Name;
  cin >> select;
  int judge;
  switch (select) {
  case 1:
    cout << "请输入员工编号：" << endl;
    cin >> ID;
    judge = this->get_Worker(ID);
    if (judge != -1) {
      this->m_EmpArray[judge]->showInfo(); //显示数据
    } else {
      cout << "未找到该员工，请重新确认！" << endl;
    }
    break;
  case 2:
    cout << "请输入员工姓名：" << endl;
    cin >> Name;
    judge = this->get_Worker(Name);
    if (judge != -1) {
      this->m_EmpArray[judge]->showInfo(); //显示数据
    } else {
      cout << "未找到该员工，请重新确认！" << endl;
    }
    break;

  default:
    break;
  }
}

void WorkerManager::Sort_Emp() //按照编号排序
{
  if (this->m_FileIsEmpty) {
    cout << "这里没有任何员工信息，请创建！" << endl;
  } else {
    Worker *worker = NULL;
    for (int i = 0; i < this->m_EmpNum - 1; i++) {
      if (this->m_EmpArray[i]->m_ID > this->m_EmpArray[i + 1]->m_ID) {
        //交换位置
        worker = this->m_EmpArray[i];
        this->m_EmpArray[i] = this->m_EmpArray[i + 1];
        this->m_EmpArray[i + 1] = worker;
      }
    }
    this->save_Data(); //同步更新数据
  }
}

void WorkerManager::Clear_File() //清空文档
{
  cout << "你确认清空吗！一旦清空不可找回！(0、取消;1、确定)" << endl;
  int comfirm;
  cin >> comfirm;
  switch (comfirm) {
  case 0:
    cout << "已取消！" << endl;
    break;
  case 1:
    this->m_EmpArray = NULL;
    this->m_EmpNum = 0;
    cout << "已清空!" << endl;
    this->save_Data();
    this->m_FileIsEmpty = true;
    break;
  default:
    break;
  }
}

WorkerManager::~WorkerManager() {
  if (this->m_EmpArray != NULL) {
    delete[] this->m_EmpArray;
    this->m_EmpArray = NULL;
  }
};

Employee::Employee(int ID, string Name, int DepID) {
  this->m_ID = ID;
  this->m_Name = Name;
  this->m_DepID = DepID;
}

void Employee::showInfo() {
  cout << "该员工编号是" << this->m_ID << endl;
  cout << "该员工姓名是" << this->m_Name << endl;
  cout << "该员工部门编号是" << this->m_DepID << endl;
  cout << "该员工职位是普通职工!" << endl;
}

string Employee::getDepartment() { return "普通员工"; }

Manager::Manager(int ID, string Name, int DepID) {
  this->m_ID = ID;
  this->m_Name = Name;
  this->m_DepID = DepID;
}

void Manager::showInfo() {
  cout << "该员工编号是" << this->m_ID << endl;
  cout << "该员工姓名是" << this->m_Name << endl;
  cout << "该员工部门编号是" << this->m_DepID << endl;
  cout << "该员工职位是部门经历！" << endl;
}

string Manager::getDepartment() { return "部门经理"; }

Boss::Boss(int ID, string Name, int DepID) {
  this->m_ID = ID;
  this->m_Name = Name;
  this->m_DepID = DepID;
}

void Boss::showInfo() {
  cout << "该员工编号是 " << this->m_ID << endl;
  cout << "该员工姓名是 " << this->m_Name << endl;
  cout << "该员工部门编号是 " << this->m_DepID << endl;
  cout << "该员工职位是老板!" << endl;
}

string Boss::getDepartment() { return "老板"; }
