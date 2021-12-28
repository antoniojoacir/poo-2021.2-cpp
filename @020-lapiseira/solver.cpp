#include <iostream>
#include <list>
#include <algorithm>
#include <memory>

using namespace std;

template <typename T>
using lptr = std::list<std::shared_ptr<T>>;

template <typename T>
using ptr = std::shared_ptr<T>;

class Lead {
    std::string hardness;
    int size;
    float thickness;
public:

    Lead(std::string hardness= "", int size= 0, float thickness= 0) :
    hardness(hardness), size(size), thickness(thickness) {}

    friend std::ostream& operator<<(std::ostream& os, const Lead& grafite);

    bool usagePerSheet(int loop) {
        while (loop > 0) {
            if (size <= 10) {
                std::cout << "Folha imcompleta\n";
                return false;
            }
            size--;
            loop--;
        }
        return true;
    }

    std::string getHardness() const {
        return hardness;
    }

    int getSize() const {
        return size;
    }

    float getThickness() const {
        return thickness;
    }
};
std::ostream& operator<<(std::ostream& os, const Lead& grafite) {
    os << "[" << grafite.hardness << ":" << grafite.size << "mm:" << grafite.thickness << "]";
    return os;
}

class Pensil {
    lptr<Lead> leads;
    float thickness;
    Lead * bico { nullptr };
public:

    Pensil(float thickness= 0) :
    thickness(thickness) {}

    friend std::ostream& operator<<(std::ostream& os, const Pensil& pensil);

    bool addLead(const ptr<Lead>& lead) {
        if (lead->getThickness() != this->thickness) {
            std::cout << "Tamanho errado\n";
            return false;
        }
        leads.push_back(lead);
        return true;
    }

    Lead * remove() {
        if (this->bico == nullptr) {
            std::cout << "Não há grafite para retirar\n";
            return nullptr;
        }
        if (this->bico->getSize() > 10) {
            std::cout << "Grafite reaproveitado\n";
            leads.push_back(std::make_shared<Lead>(this->bico->getHardness(),
            this->bico->getSize(),
            this->bico->getThickness()));
            return std::exchange(this->bico, nullptr);
        }
        return std::exchange(this->bico, nullptr);
    }

    bool pull() {
        if (leads.empty()) {
            std::cout << "Não há grafite para retirar\n";
            return false;
        }
        this->bico = leads.front().get();
        leads.pop_front();
        return true;
    }

    bool write() {
        if (this->bico->getSize() <= 10) {
            std::cout << "Grafite pequeno para escrever!\n";
            return false;
        }
        if (this->bico->getHardness() == "HB") {
            this->bico->usagePerSheet(1);
        }
        else if (this->bico->getHardness() == "2B") {
            this->bico->usagePerSheet(2);
        }
        else if (this->bico->getHardness() == "4B") {
            this->bico->usagePerSheet(4);
        }
        else if (this->bico->getHardness() == "6B") {
            this->bico->usagePerSheet(6);
        }
        return true;
    }
};
std::ostream& operator<<(std::ostream& os, const Pensil& pensil) {
    os << "Thickness: " << pensil.thickness << " - in use : ";
    if (pensil.bico)
        os << *pensil.bico << "\n";
    else
        os << "NULL\n";
    os << "graffit availabe: ";
    for (auto lead : pensil.leads) {
        if (lead)
            os << *lead << " ";
        else
            os << "NULL ";
    }
    return os;
}


int main() {
    Pensil pensil(1.5);

    pensil.addLead(std::make_shared<Lead>("HB", 12, 1.5));
    pensil.addLead(std::make_shared<Lead>("2B", 10, 1.5));
    pensil.addLead(std::make_shared<Lead>("4B", 10, 2.5));
    pensil.addLead(std::make_shared<Lead>("6B", 10, 1.5));

    pensil.pull();
    cout << pensil << endl;
    pensil.remove();
    cout << pensil << endl;
}