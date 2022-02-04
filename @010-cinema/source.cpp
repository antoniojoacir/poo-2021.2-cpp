#include <iostream>
#include <memory>
#include <map>
#include <vector>

using namespace std;

class Person {
    int spot;
    string key;
    string telefonNumber;
public:
    Person(int spot, string key, string number) :
    spot(spot), key(key), telefonNumber(number) {}

    int getSpot() const { return this->spot; }

    string getKey() const { return this->key; }
    
    string getNumber() const { return this->telefonNumber; }

    bool foneValidade() {
        string isRight { "0123456789 ().-" };
        return std::all_of(telefonNumber.begin(), telefonNumber.end(), [&](char c) {
            return isRight.find(c) != std::string::npos;
        });
    }

    friend ostream& operator<<(ostream& os, const Person& person);
};
ostream& operator<<(ostream& os, const Person& person) {
    os << "(" << person.spot << ") " << "[" << person.key << ":" << person.telefonNumber << "]";
    return os;
}

class Cine {
    map<int, shared_ptr<Person>> chairs;
    int maxSize;
    bool validadeIndex(int index) {
        return index < 0 || index >= maxSize ? false : true;
    }
public: 
    Cine(int size) : maxSize(size) {}

    bool addPerson(int spot, string name, string number) {
        if (!validadeIndex(spot)) {
            cout << "Spot invalid" << endl;
            return false;
        }
        if ((int) this->chairs.size() == this->maxSize) {
            cout << "Cine is full" << endl;
            return false;
        }
        if (this->chairs.find(spot) != this->chairs.end()) {
            cout << "Spot already taken" << endl;
            return false;
        }
        for (auto& person : this->chairs) {
            if (person.second->getKey() == name) {
                cout << "Name already taken" << endl;
                return false;
            }
        }
        auto person = make_shared<Person>(spot, name, number);
        if (!person->foneValidade()) {
            cout << "Invalid number" << endl;
            return false;
        }
        this->chairs.insert(make_pair(spot, person));
        return true;
    }

    bool cancelar(int spot) {
        if (!validadeIndex(spot)) {
            cout << "Spot invalid" << endl;
            return false;
        }
        if (this->chairs.find(spot) == this->chairs.end()) {
            cout << "Spot not found" << endl;
            return false;
        }
        this->chairs.erase(spot);
        return true;
    }

    friend ostream& operator<<(ostream&, const Cine&);
};
ostream& operator<<(ostream& os, const Cine& cine) {
    os << "spots available: " << cine.maxSize - (int) cine.chairs.size() << endl;
    for (auto& [ key, person] : cine.chairs) 
        os << *person << endl;
    return os;
}
int main() {
    Cine cine(10);
    cine.addPerson(2, "Juan", "123456a89");
    cine.addPerson(1, "Pedro", "123456789");
    cine.addPerson(2, "Juan", "123456789");
    cine.addPerson(3, "Juan", "123456789");
    cout << cine << endl;
}