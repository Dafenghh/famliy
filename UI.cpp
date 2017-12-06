#include "UI.h"

void printTitle() {
	for (int i = 0; i < 20; ++i) cout << "-";
	cout << "家谱管理系统";
	for (int i = 0; i < 20; ++i) cout << "-";
	cout << endl;
}
bool checkLessNumber(string str, int min, int max) {
	int len = 0, tp = max;
	while (tp > 0) ++len, tp /= 10;
	if (str.size() > len) return false;
	int num = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (!isdigit(str[i])) return false;
		num = num * 10 + str[i] - '0';
	}
	if (num <= max && num >= min) return true;
	else return false;
}
int getOpinion(int min, int max) {
	string opt;
	cout << "请输入" << min << "-" << max << "的数字选择操作" << endl;
	cin >> opt;
	while (!checkLessNumber(opt, min, max)) {
		cout << "输入错误！请输入" << min << "-" << max << "的数字选择操作" << endl;
		cin >> opt;
	}
	int num = 0;
	for (int i = 0; i < opt.size(); ++i) {
		num = num * 10 + opt[i] - '0';
	}
	return num;
}
void createFamily() {
	cout << "*** 创建新的家谱 ***" << endl;
	cout << "请输入祖先的名字:   " ;
	string ancestor;
	cin >> ancestor;
	cout << "请输入祖先的出生年份：";
	int year;
	cin >> year;
	family.addRoot(ancestor,year);
	cout << "家谱创建成功！" << endl;
}

void readFamily() {
	cout << "请输入要家谱的文件名：";
	string filename;
	cin >> filename;
	ifstream in(filename);
	in >> family;
	cout << "读取家谱成功！" << endl;
}
void marry() {
	cout << "请输入男方名字： ";
	string husband;
	cin >> husband;
	cout << "请输入女方名字：";
	string wife;
	cin >> wife;
	if (family.addAWifeByName(husband, wife))cout << "操作成功！" << endl;
	else cout << "操作失败！" << endl;
}

void generate() {
	cout << "请输入父亲名字：";
	string father;
	cin >> father;
	cout << "请输入孩子的名字：";
	string child;
	cin >> child;
	cout << "请输入孩子的性别(男-1 女-2)：";
	int sex;
	cin >> sex;
	while (sex != 1 && sex != 2) {
		cout << "输入错误！请输入孩子的性别(男-1 女-2)：";
		cin >> sex;
	}
	Gender gender = (sex == 1) ? Male : Female;
	cout << "请输入孩子的出生年份：";
	int year;
	cin >> year;
	if (family.addAChildByName(father, child, gender, year))cout << "操作成功！" << endl;
	else cout << "操作失败！" << endl;
}

void divorce() {
	cout << "请输入男方名字： ";
	string husband;
	cin >> husband;
	cout << "请输入女方名字：";
	string wife;
	cin >> wife;
	if (family.addAWifeByName(husband, "")) cout << "操作成功！" << endl;
	else cout << "操作失败！" << endl;
}

void die() {

}

void change() {
	while (true)
	{
		printTitle();
		cout << "[1]  结婚    [2]  生子" << endl;
		cout << "[3]  离婚    [4]  离世" << endl;
		cout << "[5]  保存并退出" << endl;
		int opt = getOpinion(1, 5);
		switch (opt)
		{
		case 1:marry(); break;
		case 2:generate(); break;
		case 3:divorce(); break;
		case 4:die(); break;
		default:
			return;
		}
	}
}

void queryGeneration() {
	cout << "输入被查询者姓名：";
	string name;
	cin >> name;
	int generation = family.getGenerationByName(name);
	if (generation == -1) cout << "查询失败！" << endl;
	else cout << name << "为家族中第" << generation << "代" << endl;
}

void queryDegreeOfConsanguinity() {
	cout << "输入第一位被查询者姓名：";
	string name1;
	cin >> name1;
	cout << "输入第二位被查询者姓名：";
	string name2;
	cin >> name2;
	int degree= family.getDegreeOfConsanguinity(name1, name2);
	if (degree == -1) cout << "查询失败！" << endl;
	else cout <<name1<<"和"<<name2<<"的血缘亲近程度为"<<degree<<endl 
		<< "提示：数字越小表示两人的血缘关系越亲近" << endl;
}

void queryLCA() {
	cout << "输入第一位被查询者姓名：";
	string name1;
	cin >> name1;
	cout << "输入第二位被查询者姓名：";
	string name2;
	cin >> name2;
	Person person = family.findLCA(name1, name2);
	if (person.getId() == -1) cout << "查询失败！" << endl;
	else cout << name1 << "和" << name2 << "的最近公共祖先为" << person.getName() << endl;
}

void queryInfo() {
	cout << "请输入被查询者姓名：";
	string name;
	cin >> name;
	Person res = family.queryInfoByName(name);
	if (res.getId() == -1) cout << "查询失败！" << endl;
	else {
		cout << "-----------------------------------------" << endl;
		cout << "姓名：" << res.getName() << endl;
		cout << "性别：" << res.getSex() << endl;
		cout << "父亲：" << family[res.getFatherId()].getName() << endl;
		if (res.getWifeName().size() > 0) {
			cout << "婚姻状况：已婚" << endl << "配偶：" << res.getWifeName() << endl;
		}
		else cout << "婚姻状况：单身" << endl << "配偶：无" << endl;
		cout << "出生年份：" << res.getBirthYear()<<endl;
		cout << "过世年份：";
		if (res.getDeathYear() != -1) cout << res.getDeathYear() << endl;
		else  cout << " - " << endl;
	}
}

void query() {
	while (true)
	{
		printTitle();
		cout << "[1]  某人是家族中第几代    [2]  两个人的血缘亲近程度" << endl;
		cout << "[3]  两个人最近公共祖先    [4]	 某人的信息" << endl;
		cout << "[5]  退出" << endl;
		int opt = getOpinion(1, 5);
		switch (opt)
		{
		case 1:queryGeneration(); break;
		case 2:queryDegreeOfConsanguinity(); break;
		case 3:queryLCA(); break;
		case 4:queryInfo(); break;
		default:
			return;
		}
	}
}
void showAll() {
	cout << "**完整家谱**" << endl;
	family.printFromRoot();
}

void showFromPerson() {
	cout << "请输入谁一系的家谱：";
	string name;
	cin >> name;
	cout << "**"<<name<<"系家谱**" << endl;
	if (family.printByName(name) == false) cout << "操作失败!"<<endl;
}

void print() {
	while (true)
	{
		printTitle();
		cout << "[1]  打印总家谱    [2]  打印某人一系的家谱" << endl;
		cout << "[3]  退出" << endl;
		int opt = getOpinion(1, 3);
		switch (opt)
		{
		case 1:showAll(); break;
		case 2:showFromPerson(); break;
		default:
			return;
		}
	}
}

void menu() {
	while (true)
	{
		printTitle();
		cout << "[1]  成员关系变更      [2]查询" << endl;
		cout << "[3]  打印家谱          [4]退出" << endl;
		int opt = getOpinion(1, 4);
		switch (opt)
		{
		case 1:change(); break;
		case 2:query(); break;
		case 3:print(); break;
		default:
			return;
		}
	}
}
void save() {
	cout << "请输入要保存家谱的文件名：";
	string filename;
	cin >> filename;
	ofstream out(filename);
	out << family;
}
bool init() {
	printTitle();
	cout << "[1]  读取已有家谱" << endl
		<< "[2]  创建新的家谱" << endl
		<< "[3]  退出系统" << endl;
	int opt = getOpinion(1, 3);
	switch (opt)
	{
	case 1:readFamily(); break;
	case 2:createFamily(); break;
	case 3:return false;
	default:
		break;
	}
	menu();

	return true;
}