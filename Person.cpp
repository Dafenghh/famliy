#include "Person.h"
Person::Person() { id = -1; } //空标志为id==-1
Person::Person(int id, string name, Gender sex, int birth_year, int generation, int father_id = -1) :
	id(id), name(name), sex(sex), birth_year(birth_year), generation(generation), father_id(father_id)
{
	death_year = -1;
}

int Person::getGeneration()const {
	return generation;
}

Gender Person::getSex() const {
	return sex;
}

vector<int> Person::getChildrenIds() const {
	return children_ids;
}

int Person::getId() const {
	return id;
}

void Person::addChild(int child_id) {
	children_ids.push_back(child_id);
}

string Person::getName() const {
	return name;
}

void Person::setName(string new_name) {
	name = new_name;
}

int Person::getFatherId() const {
	return father_id;
}

void Person::setFatherId(int new_father_id) {
	father_id = new_father_id;
}

string Person::getWifeName() const {
	return wife_name;
}

void Person::setWifeName(string new_wife_name) {
	wife_name = new_wife_name;
}

void Person::setDeathYear(int new_death_year) {
	death_year = new_death_year;
}

int Person::getDeathYear() const {
	return death_year;
}

int Person::getBirthYear() const {
	return birth_year;
}
istream& operator >> (istream &in, Person &person) {
	in >> person.id;
	int x;
	in >> x;
	person.sex = (x ? Male : Female);
	in >> person.birth_year >> person.death_year >> person.father_id >> person.generation;
	int n;
	in >> n;
	person.children_ids.clear();
	for (int i = 0; i < n; i++) {
		int child_id;
		in >> child_id;
		person.children_ids.push_back(child_id);
	}
	in >> x;
	if (x) {
		in >> person.name;
	}
	else {
		person.name = "";
	}

	in >> x;
	if (x) {
		in >> person.wife_name;
	}
	else {
		person.wife_name = "";
	}
	return in;
}

ostream& operator << (ostream &out, const Person &person) {
	out << person.id << endl;
	out << (person.sex == Male ? 1 : 0) << endl;
	out << person.birth_year << endl << person.death_year << endl << person.father_id << endl << person.generation << endl;
	out << person.children_ids.size() << endl;
	for (auto i : person.children_ids) {
		out << i << " ";
	}
	out << endl;
	if (person.name != "") cout << "1 " << person.name << endl; else cout << "0" << endl;
	if (person.wife_name != "") cout << "1 " << person.wife_name << endl; else cout << "0" << endl;
	return out;
}

void Family::addParChildRelation(int id1, int id2) // id1 is id2's parent
{
	vec[id1].addChild(id2);
	vec[id2].setFatherId(id1);
}
int Family::addNewMember(string name, Gender sex, int birth_year, int generation) {
	int id = vec.size();
	vec.push_back(Person(id, name, sex, birth_year, generation));
	return id;
}
int Family::getMemberIdByName(string name) const {
	for (auto i : vec) {
		if (i.getName() == name) return i.getId();
	}
	return -1;
}

void Family::print(int id, int indent) {
	for (int i = 0; i < indent; i++) cout << "-";
	cout << " " << vec[id].getName();
	if (vec[id].getWifeName() != "") cout << " (" << vec[id].getWifeName() << ")";
	cout << endl;
	vector<int> children_ids = vec[id].getChildrenIds();
	for (auto i : children_ids) print(i, indent + 2);
}
Family::Family() = default;
void Family::addRoot(string name, int birth_year) {
	vec.push_back(Person(0, name, Male, birth_year, 1));
}


bool Family::addAChildByName(string par_name, string child_name, Gender child_sex, int child_birth_year) {
	int par_id = getMemberIdByName(par_name);
	if (par_id == -1) {
		cerr << "Par name not found!" << endl;
		return false;
	}
	int child_id = addNewMember(child_name, child_sex, child_birth_year, vec[par_id].getGeneration() + 1);
	addParChildRelation(par_id, child_id);
	return true;
}

bool Family::addAWifeByName(string member_name, string wife_name) {
	int member_id = getMemberIdByName(member_name);
	if (member_id == -1) {
		cerr << "Member name not found!" << endl;
		return false;
	}
	vec[member_id].setWifeName(wife_name);
	return true;
}

int Family::getGenerationByName(string member_name) {
	int member_id = getMemberIdByName(member_name);
	if (member_id == -1) {
		cerr << "Member name not found!" << endl;
		return -1;
	}
	return vec[member_id].getGeneration();
}

Person Family::queryInfoByName(string member_name) {
	int member_id = getMemberIdByName(member_name);
	if (member_id == -1) {
		cerr << "Member name not found!" << endl;
		return Person();
	}
	return vec[member_id];
}
Person Family::findLCA(string name1, string name2)
{
	int id1 = getMemberIdByName(name1);
	int id2 = getMemberIdByName(name2);
	if (id1 == -1 || id2 == -1) {
		cerr << "Member name not found!" << endl;

		return Person();
	}
	while (id1 != id2) {
		if (vec[id1].getGeneration() < vec[id2].getGeneration()) id2 = vec[id2].getFatherId();
		else id1 = vec[id1].getFatherId();
	}
	if (id1 < 0) return Person();
	return vec[id1];
}
// print from root
// print from a person

int Family::getDegreeOfConsanguinity(string name1, string name2) {//血缘亲近程度
	int id1 = getMemberIdByName(name1);
	int id2 = getMemberIdByName(name2);
	if (id1 == -1 || id2 == -1) {
		cerr << "Member name not found!" << endl;

		return -1;
	}
	int dist1 = 0, dist2 = 0;
	while (id1 != id2) {
		if (vec[id1].getGeneration() < vec[id2].getGeneration()) id2 = vec[id2].getFatherId(), dist2++;
		else id1 = vec[id1].getFatherId(), dist1++;
		if (max(dist1, dist2) > 1000) return -1;
	}
	return max(dist1, dist2);
}

void Family::printFromRoot() {
	print(0, 0);
}

bool Family::printByName(string member_name) {
	int member_id = getMemberIdByName(member_name);
	if (member_id == -1) {
		cerr << "Member name not found!" << endl;
		return false;
	}
	print(member_id, 0);
	return true;
}

void Family::MemberDied(string member_name, int death_year) {
	int member_id = getMemberIdByName(member_name);
	if (member_id == -1) {
		cerr << "Member name not found!" << endl;
		return;
	}
	if (vec[member_id].getDeathYear() != -1) {
		cerr << "Member has died." << endl;
		return;
	}
	vec[member_id].setDeathYear(death_year);
}

istream& operator >> (istream &in, Family &family) {
	int n;
	in >> n;
	family.vec.clear();
	for (int i = 0; i < n; i++) {
		Person person;
		in >> person;
		family.vec.push_back(person);
	}
	return in;
}

ostream& operator << (ostream &out, const Family &family) {
	out << family.vec.size() << endl;
	for (auto i : family.vec) {
		out << i;
	}
	return out;
}
Person Family::operator [](const int id) {
	return vec[id];
}