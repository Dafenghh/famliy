#ifndef UI_H
#define UI_H

#include<iostream>
#include<string>
#include<fstream>
#include "Person.h"
using namespace std;

Family family;
/*��������*/
void printTitle();
bool checkLessNumber(string str, int min, int max);
int getOpinion(int min, int max);
/*����һ������*/
void createFamily();
/*��ȡ��������*/
void readFamily();
/*���*/
void marry();
/*����*/
void generate();
/*���*/
void divorce();
/*ȥ��*/
void die();
/*��Ա����˵�*/
void change();
/*��ѯĳ���Ǽ�����ĵڼ��� */
void queryGeneration();
/*��ѯ���˵������̶�*/
void queryDegreeOfConsanguinity();
/*��ѯ�����������������*/
void queryLCA();
/*��ѯĳ�˵���ϸ��Ϣ*/
void queryInfo();
/*��ѯ�˵�*/
void query();
/*��ӡ��������*/
void showAll();
/*��һ����Ϊ����ʼ��ӡ*/
void showFromPerson();
/*��ӡ�˵�*/
void print();
/*���˵�*/
void menu();
/*�������*/
void save();
/*��main.cpp�Ľӿڽ������*/
bool init();
#endif // !UI_H

