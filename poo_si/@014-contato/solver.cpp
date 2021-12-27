#include <iostream>
#include <vector>
#include <memory>

template <typename T>
using vetptr = std::vector<std::shared_ptr<T>>;

template <typename T>
using ptr = std::shared_ptr<T>;

class Infors {
    std::string idLabel;
    std::string telefonNumber;
public:

    Infors(std::string label="", std::string number="") :
    idLabel(label), telefonNumber(number) {}

    friend std::ostream& operator<<(std::ostream& os, const Infors& infors);

    std::string getName() const { return idLabel; }

    std::string getNumber() const { return telefonNumber; }

    bool isValid(std::string number) {
        if (number.empty()) {
            std::cout << "Ei, você não digitou nada!\n";
            return false;
        }
        std::string isFone { "0123456789.()- " };
        for (auto c : number) {
            if (isFone.find(c) == std::string::npos) {
                std::cout << "Ei, você digitou algo errado!\n";
                return false;
            }
        }
        return true;
    }
};
std::ostream& operator<<(std::ostream& os, const Infors& infors) {
    os << infors.idLabel << ":" << infors.telefonNumber;
    return os;
}

class Contact {
    vetptr<Infors> infors;
    std::string idName;
    bool isValidIndex(int index) {
        if (index < 0 || index >= (int) infors.size()) {
            std::cout << "Opa, esse indice está errado!\n";
            return false;
        }
        return true;
    }
public:
    Contact(std::string name="") :
    idName(name) {}

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact);

    void addInfor(const ptr<Infors>& infors) {
        if(infors->isValid(infors->getNumber())) {
            this->infors.push_back(infors);
        }
    }

    bool removerInfor(int index) {
        if (isValidIndex(index)) {
            infors.erase(infors.begin() + index);
            return true;
        }
        return false;
    }
};
std::ostream& operator<<(std::ostream& os, const Contact& contact) {
    os << contact.idName << ": [ ";
    for (auto i = 0 ; i < (int) contact.infors.size() ; i++) {
        os << "[" << i << "]" << *contact.infors[i];
        if (i < (int) contact.infors.size() - 1) {
            os << " | ";
        }
    }
    os << " ]\n";
    return os;
}

int main() {
    Contact contact("Joa");
    contact.addInfor(std::make_shared<Infors>("OI", "99999999"));
    contact.addInfor(std::make_shared<Infors>("Vivo", "88a88888"));
    contact.addInfor(std::make_shared<Infors>("Tim", "77777777"));

    std::cout << contact;

    contact.removerInfor(1);

    std::cout << contact;
}