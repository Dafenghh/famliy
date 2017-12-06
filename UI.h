#ifndef UI_H
#define UI_H

#include<iostream>
#include<string>
#include<fstream>
#include "Person.h"
using namespace std;

Family family;
/*辅助函数*/
void printTitle();
bool checkLessNumber(string str, int min, int max);
int getOpinion(int min, int max);
/*创建一个家谱*/
void createFamily();
/*读取已有数据*/
void readFamily();
/*结婚*/
void marry();
/*生子*/
void generate();
/*离婚*/
void divorce();
/*去世*/
void die();
/*成员变更菜单*/
void change();
/*查询某人是家谱里的第几代 */
void queryGeneration();
/*查询两人的亲属程度*/
void queryDegreeOfConsanguinity();
/*查询两个人最近公共祖先*/
void queryLCA();
/*查询某人的详细信息*/
void queryInfo();
/*查询菜单*/
void query();
/*打印完整家谱*/
void showAll();
/*从一个人为根开始打印*/
void showFromPerson();
/*打印菜单*/
void print();
/*主菜单*/
void menu();
/*保存家谱*/
void save();
/*给main.cpp的接口进入程序*/
bool init();
#endif // !UI_H

