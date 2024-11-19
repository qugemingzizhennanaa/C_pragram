#include "workermanager.cpp"
#include "workermanager.h"

int main() {
  WorkerManager wm;
  int select = 0;
  while (true) {
    wm.ShowMenu();
    cout << "请输入你的操作：" << endl;
    cin >> select;

    switch (select) {
    case 0: //退出系统
      cout << "成功退出系统... ..." << endl;
      return 0;
      break;
    case 1: //增加职工
      wm.Add_Emp();
      /*for (int i=0;i<wm.m_EmpNum;i++)
      {
          cout<<wm.m_EmpArray[i]->m_ID<<endl;
      }*///测试
      break;
    case 2: //显示职工
      wm.Show_Emp();
      break;
    case 3: //删除职工
      wm.Delete_Emp();
      break;
    case 4: //修改职工
      wm.Modify_Emp();
      break;
    case 5: //查找职工
      wm.Find_Emp();
      break;
    case 6: //排序职工
      wm.Sort_Emp();
      break;
    case 7: //清空文档
      wm.Clear_File();
      break;
    default:
      break;
    }
  }

  return 0;
}