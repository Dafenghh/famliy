#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using std::cerr;
using std::endl;
using std::max;
using std::string;
using std::vector;
using std::cout;
using std::istream;
using std::ostream;

typedef enum { Male, Female } Gender;
class Person {
	int id;
	string name;
	Gender sex;
	int birth_year, death_year;//未死亡为-1
	int father_id;
	vector<int> children_ids;
	string wife_name;//单身则为空串
	int generation;
public:
	Person(); //空标志为id==-1
	Person(int id, string name, Gender sex, int birth_year, int generation, int father_id);
	int getGeneration()const;
	Gender getSex() const;
	vector<int> getChildrenIds() const;
	int getId() const;
	void addChild(int child_id);
	string getName() const;
	void setName(string new_name);
	int getFatherId() const;
	void setFatherId(int new_father_id);
	string getWifeName() const;
	void setWifeName(string new_wife_name);
	void setDeathYear(int new_death_year);
	int getDeathYear() const;
	int getBirthYear() const;
	friend istream& operator >> (istream &in, Person &person);
	friend ostream& operator << (ostream &out, const Person &person);
};

class Family {
	vector<Person> vec;
	void addParChildRelation(int id1, int id2);
	int addNewMember(string name, Gender sex, int birth_year, int generation);
	int getMemberIdByName(string name) const;
	void print(int id, int indent);
public:
	Family();
	void addRoot(string name, int birth_year);
	bool addAChildByName(string par_name, string child_name, Gender child_sex, int child_birth_year);
	bool addAWifeByName(string member_name, string wife_name);
	int getGenerationByName(string member_name);
	Person queryInfoByName(string member_name);
	Person findLCA(string name1, string name2);
	int getDegreeOfConsanguinity(string name1, string name2);//血缘亲近程度
	void printFromRoot();
	bool printByName(string member_name);
	void MemberDied(string member_name, int death_year);// 如果成员不存在或者已死亡将cerr
	friend istream& operator >> (istream &in, Family &family);
	friend ostream& operator << (ostream &out, const Family &family);
	Person operator [](const int id);
};
#endif // !PERSON_H