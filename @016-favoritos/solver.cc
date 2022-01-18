#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>

struct Fone {
    std::string telefonNumber;
    std::string company;

    Fone(std::string telefonNumber, std::string company) : 
    telefonNumber(telefonNumber), company(company) {}

    std::string getNumber() const {
        return this->telefonNumber;
    }

    std::string getCompany() const {
        return this->company;
    }

    bool toCheck() const {
        if (telefonNumber.empty()) {
            std::cout << "Telefon number is empty" << std::endl;
            return false;
        }

        std::string rightCaracters { "0123456789+()-. " };
        
        for (auto i : telefonNumber) 
        {
            if (std::find(
            rightCaracters.begin(),
            rightCaracters.end(), 
            i) == rightCaracters.end()) 
            {
                std::cout << "Wrong caracter in number" << std::endl;
                return false;
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fone& fone)
    {
        os << "[" << fone.telefonNumber << ":" << fone.company << "]";
        return os;
    }
};

class Contact {
    std::string contactName;
    std::vector<std::shared_ptr<Fone>> contacts;
    bool flag { false };
public:
    Contact(std::string name) : contactName(name) {}

    std::string getName() const 
    {
        return this->contactName;
    }

    bool isStar() const 
    {
        return this->flag;
    }

    bool insertFone(const std::shared_ptr<Fone>& fone)
    {
        if (fone == nullptr) 
        {
            std::cout << "Fone is nullptr" << std::endl;
            return false;
        }

        if (fone->toCheck()) 
        {
            contacts.push_back(fone);
            std::cout << "Fone inserted" << std::endl;
            return true;
        }
        return false;
    }

    bool removeFone(int index) 
    {
        if (contacts.empty()) 
        {
            std::cout << "Contacts is empty" << std::endl;
            return false;
        }

        if (index < 0 || index >= (int) contacts.size()) 
        {
            std::cout << "Index is out of range" << std::endl;
            return false;
        }

        contacts.erase(contacts.begin() + index);
        std::cout << "Fone removed" << std::endl;
        return true;
    }

    void changeStar() {
        this->flag = !this->flag;
    }

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact)
    {   
        if (contact.flag) 
        {
            os << "@ " << contact.contactName << ": ";
        } else
        {
            os << "- " << contact.contactName << ": ";
        }
        for (auto i : contact.contacts) {
            os << *i << " ";
        }
        return os;
    }
};

class PhoneBook {
    std::map<std::string, std::shared_ptr<Contact>> contactsInfors;
public:

    PhoneBook() {}

    bool insertContact(const std::shared_ptr<Contact>& contact)
    {
        if (contact == nullptr) 
        {
            std::cout << "Contact is nullptr" << std::endl;
            return false;
        }

        if (contactsInfors.find(contact->getName()) != contactsInfors.end()) 
        {
            std::cout << "Contact already exists" << std::endl;
            return false;
        }

        contactsInfors[contact->getName()] = contact;
        std::cout << "Contact inserted" << std::endl;
        return true;
    }
};

int main() {
   PhoneBook phonebook;
   auto contact = std::make_shared<Contact>("John");
    contact->insertFone(std::make_shared<Fone>("+380(66)1234567", "Vodafone"));
    contact->insertFone(std::make_shared<Fone>("+380(66)1234567", "Vodafone"));
    contact->insertFone(std::make_shared<Fone>("+380(66)1234567", "Vodafone"));
   phonebook.insertContact(contact);
}