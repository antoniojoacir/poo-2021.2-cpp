#include <iostream>
#include <algorithm>
#include <memory>

template <typename Anything>
using vptr = std::vector<std::shared_ptr<Anything>>;

template <typename Something>
using ptr = std::shared_ptr<Something>;

class Person {
    std::string idName;
    std::string telefonNumber;
public:

    Person(std::string name= "", std::string number = "") : 
    idName(name), telefonNumber(number) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& person);

    std::string getName() {
        return idName;
    }

    std::string getNumber() {
        return telefonNumber;
    }
};
std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "[" << person.idName << ":" << person.telefonNumber << "]";
    return os;
}

class Cine {
    vptr<Person> chairs;
    bool validadeIndex(int index){
        if (index < 0 || index >= (int) chairs.size()) {
            return false;
        }
        return true;
    }
    bool isValid(std::string number) {
        std::string isRight { "0123456789 ().-" };
        return std::all_of(number.begin(), number.end(), [&](char c) {
            return isRight.find(c) != std::string::npos;
        });
    }
public:

    Cine(int size) :
    chairs(size, nullptr) {}

    friend std::ostream& operator<<(std::ostream& os, const Cine& cine);

    bool reservar(const ptr<Person>& person, int spot) {
        if (!isValid(person->getNumber())) {
            std::cout << "Numero invalido\n";
            return false;
        }
        if (!validadeIndex(spot)) {
            std::cout << "Index invalido\n";
            return false;
        }
        if (chairs[spot] != nullptr) {
            std::cout << "Espaço ocupado\n";
            return false;
        }
        chairs[spot] = person;
        return true;
    }

    bool cancelar(int spot) {
        if (!validadeIndex(spot)) {
            std::cout << "Index invalido\n";
            return false;
        }
        if (chairs[spot] == nullptr) {
            std::cout << "Espaço vazio\n";
            return false;
        }
        chairs[spot] = nullptr;
        return true;
    }
};
std::ostream& operator<<(std::ostream& os, const Cine& cine) {
    os << "Cine - espaços ainda disponiveis: " << std::count(cine.chairs.begin(), cine.chairs.end(), nullptr) << "\n";
    for (int i = 0; i < (int) cine.chairs.size(); i++) {
        if (cine.chairs[i]) {
            os << "[" << i << "] : " << *cine.chairs[i] << "\n";
        }
        else {
            os << "[" << i << "] : vazio\n";
        }
    }
    return os;
}

int main() {
    Cine cine(5);
    cine.reservar(std::make_shared<Person>("Joao", "123456789"), 0);
    cine.reservar(std::make_shared<Person>("Maria", "987654321"), 1);


    std::cout << cine << "\n";

    cine.cancelar(0);

    std::cout << cine << "\n";

}