#include <iostream>
#include <map>
#include <memory>
#include <list>
#include <algorithm>

using namespace std;

class FONE {
    string company;
    string telefon_number;
public:
    FONE(string name, string number) :
    company(name), telefon_number(number) 
    {
    }

    string getIdName() const { return this->company; }

    string getFoneNumber() const { return this->telefon_number; }

    bool validateNumber(string number) {
        string isdigit { "0123456789()-.+ " };
        return all_of(number.begin(), number.end(), [&isdigit](char c) { return isdigit.find(c) != string::npos; });
    }

    friend ostream& operator<<(ostream&, const FONE&);
};
ostream& operator<<(ostream& output, const FONE& fone) {
    output << "[" << fone.company << ":" << fone.telefon_number << "]";
    return output;
}

class CONTACT {
    string name;
    list<shared_ptr<FONE>> fones;
public:
    CONTACT(string name) : name(name)
    {
    }

    string getId() const { return this->name; }

    list<shared_ptr<FONE>> getFones() const { return this->fones; }

    void addFone(shared_ptr<FONE> fone) {
        if (fone->validateNumber(fone->getFoneNumber())) {
            this->fones.push_back(fone);
            return;
        }
        cout << "Fone number " << fone->getFoneNumber() << " is not valid\n";
    }

    bool rmFone(int index) {
        if (this->fones.empty()) {
            cout << "No fones to remove\n";
            return false;
        }

        if (index < 0 || index >= (int) this->fones.size()) {
            cout << "Index " << index << " is out of range\n";
            return false;
        }
        auto it = this->fones.begin();
        advance(it, index);
        this->fones.erase(this->fones.begin(), it);
        return true;
    }

    friend ostream& operator<<(ostream&, const CONTACT&);
}; 
ostream& operator<<(ostream& output, const CONTACT& contact) {
    output << contact.name << ": ";
    for (auto fone : contact.fones) 
        output << *fone << " ";
    return output;
}

class PHONEBOOK {
    map<string, shared_ptr<CONTACT>> contacts;
public:
    PHONEBOOK()
    {
    }

    void addContact(shared_ptr<CONTACT> contact) {
        auto it = this->contacts.find(contact->getId());
        if (it != this->contacts.end()) {
            auto fones = contact->getFones();
            for (auto fone : fones) 
                it->second->addFone(fone);
        } else 
            this->contacts.insert(make_pair(contact->getId(), contact));
    }

    bool rmContact(string name) {
        auto it = this->contacts.find(name);
        if (it == this->contacts.end()) {
            cout << "Contact " << name << " not found\n";
            return false;
        }
        this->contacts.erase(it);
        return true;
    }

    CONTACT * getContact(string name) {
        auto it = this->contacts.find(name);
        if (it == this->contacts.end()) 
            return nullptr;
        return it->second.get();
    }

    bool searchContact(string partten) {
        for(auto& [ first, second ] : this->contacts) {
            if (first.find(partten)) {
                cout << *second << "\n";
            }
            for(auto& fone : second->getFones()) {
                if (fone->getFoneNumber().find(partten)) {
                    cout << *second << "\n";
                    break;
                }
            }
        }
        return false;
    }

    friend ostream& operator<<(ostream&, const PHONEBOOK&);
};
ostream& operator<<(ostream& output, const PHONEBOOK& phonebook) {
    for (auto contact : phonebook.contacts) {
        output << *contact.second << "\n";
    }
    return output;
}

int main() {
    PHONEBOOK phonebook;
    auto contact = make_shared<CONTACT>("ava");
    contact->addFone(make_shared<FONE>("Apple", "(+1) 123-456-7890"));
    contact->addFone(make_shared<FONE>("Google", "(+1) 234-567-8901"));
    phonebook.addContact(contact);

    auto contactTwo = make_shared<CONTACT>("evo");
    contactTwo->addFone(make_shared<FONE>("Microsoftware", "(+1) 123-456-7890"));
    contactTwo->addFone(make_shared<FONE>("Linux", "(+1) 234-567-8911"));
    phonebook.addContact(contactTwo);

    phonebook.searchContact("va");
    phonebook.searchContact("911");
    //cout << phonebook << "\n";
    return 0;
}
