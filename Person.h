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
    int mother_id;
    vector<int> children_ids;
    int couple_id;
    int generation;
public:
    Person(int id, string name, Gender sex, int birthYear, int father_id = -1, int mother_id = -1, int couple_id = -1):
        id(id), name(name), sex(sex), birthYear(birthYear), father_id(father_id), mother_id(mother_id), couple_id(couple_id)
        {
            deadYear = -1;
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

    int getMotherId() const {
        return mother_id;
    }

    void setMotherId(int new_mother_id) {
        mother_id = new_mother_id;
    }

    int getCoupleId() const{
        return couple_id;
    }

    void setCoupleId(int new_couple_id) {
        couple_id = new_couple_id;
    }

    
};

class PersonManager {
    vector<Person> vec;
public:
    int addNewMember(string name, Gender sex, int birthYear) {
        int id = vec.size();
        vec.push_back(Person(id, name, sex, birthYear));
        return id;
    }

    void addCouple (int id1, int id2){
        vec[id1].setCoupleId(id2);
        vec[id2].setCoupleId(id1);
    }

    void addParChildRelation(int id1, int id2) // id1 is id2's parent
    {
        vec[id1].addChild(id2);
        if (vec[id1].getSex() == Male) vec[id2].setFatherId(id1);
        else vec[id2].setMotherId(id1);
    }

    int getMemberIdByName(string name) const{
        for (auto i: vec) {
            if (i.getName() == name) return i.getId();
        }
        throw ;
    }

    Person queryInfo(string name) {
        return vec[getMemberIdByName(name)];
    }
};