#include <iostream>
#include <vector>
#include <memory>
#include <map>

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

    vetptr<Infors> getInfors() const { return infors; }

    std::string getId() const { return idName; }

};
std::ostream& operator<<(std::ostream& os, const Contact& contact) {
    os << contact.idName << ":";
    for (auto i = 0 ; i < (int) contact.infors.size() ; i++) {
        os << "[" << i << "]" << *contact.infors[i];
        if (i < (int) contact.infors.size() - 1) {
            os << " | ";
        }
    }
    os << " ]\n";
    return os;
}

class Agend {
    std::map<std::string, ptr<Contact>> contacts;
    
public:

    Agend() {}

    friend std::ostream& operator<<(std::ostream& os, const Agend& agend);

    // caso existe alguem com o mesmo nome, adiciona o telefone ao contato
    bool addContact(const ptr<Contact>& contact) {
        for (auto& it : contacts) {
             if (it.first == contact->getId()) {
                for (auto size = 0 ; size < (int) contact->getInfors().size() ; size++) {
                    it.second->addInfor(contact->getInfors()[size]);
                }
                return true;
            }
        }
        contacts.insert(std::make_pair(contact->getId(), contact));
        return true;
    }

    bool removerContact(std::string id) {
        for (auto& it : contacts) {
            if (it.first == id) {
                contacts.erase(it.first);
                return true;
            }
        }
        return false;
    }
};
std::ostream& operator<<(std::ostream& os, const Agend& agend) {
    for (auto& it : agend.contacts) {
        os << *it.second;
    }
    return os;
}

int main() {
    auto agenda = std::make_shared<Agend>();
    auto personOne = std::make_shared<Contact>("Joao");
    personOne->addInfor(std::make_shared<Infors>("Casa", "11-1222-9993"));
    personOne->addInfor(std::make_shared<Infors>("Trabalho", "11-2372-4433"));
    personOne->addInfor(std::make_shared<Infors>("Celular", "11-2222-3553"));

    agenda->addContact(personOne);

    auto personTwo = std::make_shared<Contact>("Maria");
    personTwo->addInfor(std::make_shared<Infors>("oi", "999999999"));
    personTwo->addInfor(std::make_shared<Infors>("tim", "9923223552"));
    personTwo->addInfor(std::make_shared<Infors>("Claro", "32314232"));

    agenda->addContact(personTwo);

    auto personThree = std::make_shared<Contact>("Joao");
    personThree->addInfor(std::make_shared<Infors>("VIVO", "11-0001-6666"));

    agenda->addContact(personThree);


    std::cout << *agenda;
}