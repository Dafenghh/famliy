#include "UI.h"

void printTitle() {
	for (int i = 0; i < 20; ++i) cout << "-";
	cout << "���׹���ϵͳ";
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
	cout << "������" << min << "-" << max << "������ѡ�����" << endl;
	cin >> opt;
	while (!checkLessNumber(opt, min, max)) {
		cout << "�������������" << min << "-" << max << "������ѡ�����" << endl;
		cin >> opt;
	}
	int num = 0;
	for (int i = 0; i < opt.size(); ++i) {
		num = num * 10 + opt[i] - '0';
	}
	return num;
}
void createFamily() {
	cout << "*** �����µļ��� ***" << endl;
	cout << "���������ȵ�����:   " ;
	string ancestor;
	cin >> ancestor;
	cout << "���������ȵĳ�����ݣ�";
	int year;
	cin >> year;
	family.addRoot(ancestor,year);
	cout << "���״����ɹ���" << endl;
}

void readFamily() {
	cout << "������Ҫ���׵��ļ�����";
	string filename;
	cin >> filename;
	ifstream in(filename);
	in >> family;
	cout << "��ȡ���׳ɹ���" << endl;
}
void marry() {
	cout << "�������з����֣� ";
	string husband;
	cin >> husband;
	cout << "������Ů�����֣�";
	string wife;
	cin >> wife;
	if (family.addAWifeByName(husband, wife))cout << "�����ɹ���" << endl;
	else cout << "����ʧ�ܣ�" << endl;
}

void generate() {
	cout << "�����븸�����֣�";
	string father;
	cin >> father;
	cout << "�����뺢�ӵ����֣�";
	string child;
	cin >> child;
	cout << "�����뺢�ӵ��Ա�(��-1 Ů-2)��";
	int sex;
	cin >> sex;
	while (sex != 1 && sex != 2) {
		cout << "������������뺢�ӵ��Ա�(��-1 Ů-2)��";
		cin >> sex;
	}
	Gender gender = (sex == 1) ? Male : Female;
	cout << "�����뺢�ӵĳ�����ݣ�";
	int year;
	cin >> year;
	if (family.addAChildByName(father, child, gender, year))cout << "�����ɹ���" << endl;
	else cout << "����ʧ�ܣ�" << endl;
}

void divorce() {
	cout << "�������з����֣� ";
	string husband;
	cin >> husband;
	cout << "������Ů�����֣�";
	string wife;
	cin >> wife;
	if (family.addAWifeByName(husband, "")) cout << "�����ɹ���" << endl;
	else cout << "����ʧ�ܣ�" << endl;
}

void die() {

}

void change() {
	while (true)
	{
		printTitle();
		cout << "[1]  ���    [2]  ����" << endl;
		cout << "[3]  ���    [4]  ����" << endl;
		cout << "[5]  ���沢�˳�" << endl;
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
	cout << "���뱻��ѯ��������";
	string name;
	cin >> name;
	int generation = family.getGenerationByName(name);
	if (generation == -1) cout << "��ѯʧ�ܣ�" << endl;
	else cout << name << "Ϊ�����е�" << generation << "��" << endl;
}

void queryDegreeOfConsanguinity() {
	cout << "�����һλ����ѯ��������";
	string name1;
	cin >> name1;
	cout << "����ڶ�λ����ѯ��������";
	string name2;
	cin >> name2;
	int degree= family.getDegreeOfConsanguinity(name1, name2);
	if (degree == -1) cout << "��ѯʧ�ܣ�" << endl;
	else cout <<name1<<"��"<<name2<<"��ѪԵ�׽��̶�Ϊ"<<degree<<endl 
		<< "��ʾ������ԽС��ʾ���˵�ѪԵ��ϵԽ�׽�" << endl;
}

void queryLCA() {
	cout << "�����һλ����ѯ��������";
	string name1;
	cin >> name1;
	cout << "����ڶ�λ����ѯ��������";
	string name2;
	cin >> name2;
	Person person = family.findLCA(name1, name2);
	if (person.getId() == -1) cout << "��ѯʧ�ܣ�" << endl;
	else cout << name1 << "��" << name2 << "�������������Ϊ" << person.getName() << endl;
}

void queryInfo() {
	cout << "�����뱻��ѯ��������";
	string name;
	cin >> name;
	Person res = family.queryInfoByName(name);
	if (res.getId() == -1) cout << "��ѯʧ�ܣ�" << endl;
	else {
		cout << "-----------------------------------------" << endl;
		cout << "������" << res.getName() << endl;
		cout << "�Ա�" << res.getSex() << endl;
		cout << "���ף�" << family[res.getFatherId()].getName() << endl;
		if (res.getWifeName().size() > 0) {
			cout << "����״�����ѻ�" << endl << "��ż��" << res.getWifeName() << endl;
		}
		else cout << "����״��������" << endl << "��ż����" << endl;
		cout << "������ݣ�" << res.getBirthYear()<<endl;
		cout << "������ݣ�";
		if (res.getDeathYear() != -1) cout << res.getDeathYear() << endl;
		else  cout << " - " << endl;
	}
}

void query() {
	while (true)
	{
		printTitle();
		cout << "[1]  ĳ���Ǽ����еڼ���    [2]  �����˵�ѪԵ�׽��̶�" << endl;
		cout << "[3]  �����������������    [4]	 ĳ�˵���Ϣ" << endl;
		cout << "[5]  �˳�" << endl;
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
	cout << "**��������**" << endl;
	family.printFromRoot();
}

void showFromPerson() {
	cout << "������˭һϵ�ļ��ף�";
	string name;
	cin >> name;
	cout << "**"<<name<<"ϵ����**" << endl;
	if (family.printByName(name) == false) cout << "����ʧ��!"<<endl;
}

void print() {
	while (true)
	{
		printTitle();
		cout << "[1]  ��ӡ�ܼ���    [2]  ��ӡĳ��һϵ�ļ���" << endl;
		cout << "[3]  �˳�" << endl;
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
		cout << "[1]  ��Ա��ϵ���      [2]��ѯ" << endl;
		cout << "[3]  ��ӡ����          [4]�˳�" << endl;
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
	cout << "������Ҫ������׵��ļ�����";
	string filename;
	cin >> filename;
	ofstream out(filename);
	out << family;
}
bool init() {
	printTitle();
	cout << "[1]  ��ȡ���м���" << endl
		<< "[2]  �����µļ���" << endl
		<< "[3]  �˳�ϵͳ" << endl;
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