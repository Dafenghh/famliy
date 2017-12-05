#include <string>
#include <vector>
using std::string;
using std::vector;

typedef enum{Male, Female} Gender; 
class Person {
    int id;
    string name;
    Gender sex;
    int birthYear, deadYear;//未死亡为-1
    int father_id;
    
    vector<int> children_ids;
    string wife_name;//单身则为空串
    int generation;
public:
    Person(){id = -1;} //空标志为id==-1
    Person(int id, string name, Gender sex, int birthYear, int generation, int father_id = -1, int mother_id = -1, int couple_id = -1):
        id(id), name(name), sex(sex), birthYear(birthYear), generation(generation), father_id(father_id), mother_id(mother_id), couple_id(couple_id)
        {
            deadYear = -1;
        }
    
    int getGeneration()const {
        return generation;
    }

    Gender getSex() const {
        return sex;
    }
    
    vector<int> getChildrenIds() const {
        return children_ids;
    }

    int getId() const{
        return id;
    }

    void addChild(int child_id) {
        children_ids.push_back(child_id);
    } 

    string getName() const {
        return name;
    }

    void setName(string new_name) {
        name = new_name;
    }

    int getFatherId() const {
        return father_id;
    }

    void setFatherId(int new_father_id) {
        father_id = new_father_id;
    }

    string getWifeName() const{
        return wife_name;
    }                               

    void setWifeName(string new_wife_name) {
        wife_name = new_wife_name;
    }



};

class Family {
    vector<Person> vec;
    void addParChildRelation(int id1, int id2) // id1 is id2's parent
    {
        vec[id1].addChild(id2);
        vec[id2].setFatherId(id1);
    }
    int addNewMember(string name, Gender sex, int birthYear, int generation) {
        int id = vec.size();
        vec.push_back(Person(id, name, sex, birthYear, generation));
        return id;
    }
    int getMemberIdByName(string name) const{
        for (auto i: vec) {
            if (i.getName() == name) return i.getId();
        }
        return -1;
    }

    void print(int id, int indent){
        for (int i = 0; i < indent; i++) cout << "-";
        cout << " " << vec[i].getName();
        if (vec[i].getWifeName() != "") cout << " (" << vec[i].getWifeName() << ")" ;
        cout << endl;
        vector<int> children_ids = vec[i].getChildrenIds();
        for (int i = 0; i < children_ids.size(); i++) print(children_ids[i], indent+2);
    }
public:
    Family(string name, Gender sex, int birthYear) {
        vec.push_back(Person(0, name, sex, birthYear, 1));
    }


    bool addAChildByName(string par_name, string child_name, Gender child_sex, int child_birthYear) {
        int par_id = getMemberIdByName(par_name);
        if (par_id == -1) {
            cerr << "Par name not found!" << endl;
            return false;
        }
        int child_id = addNewMember(child_name, child_sex, child_birthYear, vec[par_id].getGeneration() + 1);
        addParChildRelation(par_id, child_id);
        return true;
    }

    bool addAWifeByName(string member_name, string wife_name) {
        int member_id = getMemberIdByName(member_name);
        if (member_id == -1) {
            cerr << "Member name not found!" << endl;
            return false;
        }
        vec[member_id].setWifeName(wife_name);
        return true;
    }

    int getGenerationByName(string member_name) {
        int member_id = getMemberIdByName(member_name);
        if (member_id == -1) {
            cerr << "Member name not found!" << endl;
            return -1;
        }
        return vec[member_id].getGeneration();
    }

    Person queryInfoByName(string member_name) {
        int member_id = getMemberIdByName(member_name);
        if (member_id == -1) {
            cerr << "Member name not found!" << endl;
            return Person();
        } 
        return vec[member_id];
    }
    Person findLCA(string name1, string name2) //血缘亲近程度 type -1 用户名不存在； 0 直系 1 旁系
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


    void printFromRoot() {
        print(0, 0);
    }

    void printByName(string member_name) {
        int member_id = getMemberIdByName(member_name);
        if (member_id == -1) {
            cerr << "Member name not found!" << endl;
        } 
        print(member_id, 0);
    }



};