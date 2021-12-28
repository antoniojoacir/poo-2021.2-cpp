#include <iostream>
#include <algorithm>
#include <memory>

template <typename Anything>
using vetptr = std::vector<std::shared_ptr<Anything>>;

template <typename Something>
using ptr = std::shared_ptr<Something>;

class Person {
    std::string idName;
    int idAge;
public:
    
    Person(std::string name= "", int age= 0) :
    idName(name), idAge(age) {}

    friend std::ostream& operator<<(std::ostream& stream, const Person& person);

    bool isPriority() {
        return idAge > 70;
    }

    std::string getName() {
        return idName;
    }

    int getAge() {
        return idAge;
    }

};
std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "[" << person.idName << ":" << person.idAge << "]";
    return os;
}

class Topic {
    vetptr<Person> preferenciais;
    vetptr<Person> naoPreferenciais;
    bool isValidP(vetptr<Person>& v) {
        if (std::count(v.begin(), v.end(), nullptr) == 0) {
            return false;
        }
        return true;
    }
    int findPosFree(vetptr<Person>& v) {
        for (int i = 0; i < (int) v.size(); i++) {
            if (v[i] == nullptr) {
                return i;
            }
        }
        return -1;
    }
public:

    Topic(int sizePreferenciais, int sizeNaoPreferenciais) : 
    preferenciais(sizePreferenciais, nullptr), naoPreferenciais(sizeNaoPreferenciais, nullptr) {}

    friend std::ostream& operator<<(std::ostream& os, const Topic& topic);

    void addPerson(const ptr<Person>& person) {
        if (person->isPriority()) {
            int pos = findPosFree(preferenciais);
            if (pos != -1) {
                preferenciais[pos] = person;
            }
            else {
                pos = findPosFree(naoPreferenciais);
                if (pos != -1) {
                    naoPreferenciais[pos] = person;
                }
            }
        } else {
            int pos = findPosFree(naoPreferenciais);
            if (pos != -1) {
                naoPreferenciais[pos] = person;
            }
            else {
                pos = findPosFree(preferenciais);
                if (pos != -1) {
                    preferenciais[pos] = person;
                }
            }
        }
    }

    bool remove(std::string id) {
        for (auto it = preferenciais.begin(); it != preferenciais.end(); it++) {
            if ((*it)->getName() == id) {
                preferenciais[it - preferenciais.begin()] = nullptr;
                return true;
            }
        }
        for (auto it = naoPreferenciais.begin(); it != naoPreferenciais.end(); it++) {
            if ((*it)->getName() == id) {
                naoPreferenciais[it - naoPreferenciais.begin()] = nullptr;
                return true;
            }
        }
        std::cout << "Ninguem com esse nome está na Topic\n";
        return false;
    }
};
std::ostream& operator<<(std::ostream& os, const Topic& topic) {
    os << "Preferenciais[" << topic.preferenciais.size() << "]: ";
    for (auto& person : topic.preferenciais) {
        if(person)
            os << *person << " ";
        else
            os << "nullptr ";
    }
    os << std::endl;
    os << "Nao Preferenciais[" << topic.naoPreferenciais.size() << "]: ";
    for (auto& person : topic.naoPreferenciais) {
        if(person)
            os << *person << " ";
        else
            os << "nullptr ";
    }
    os << std::endl;
    return os;
}

int main() {
    Topic topic(2, 3);
    topic.addPerson(std::make_shared<Person>("Joao", 72));
    topic.addPerson(std::make_shared<Person>("Maria", 75));
    topic.addPerson(std::make_shared<Person>("Pedro", 88));

    std::cout << topic;

    topic.remove("Maria");

    std::cout << topic;
}