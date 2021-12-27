#include <iostream> 
#include <algorithm>

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


class Pencil {
    float thickness;
    Lead * lead;
public:

    Pencil(float thickness= 0, Lead * lead= nullptr) :
    thickness(thickness), lead(lead) {}

    friend std::ostream& operator<<(std::ostream& os,const Pencil& pencil);

    bool addLead(Lead * lead) {
        if (this->lead != nullptr) {
            std::cout << "Já tem um grafite!\n";
            return false;
        }
        if (lead->getThickness() != thickness) {
            std::cout << "O grafite tem uma espessura diferente da caneta!\n";
            return false;
        }
        this->lead = lead;
        return true;
    }

    Lead * removeLead() {
        if (this->lead == nullptr) {
            std::cout << "Não tem grafite!\n";
            return nullptr;
        }
        return std::exchange(this->lead, nullptr);
    }

    bool write() {
        if (this->lead->getSize() <= 10) {
            std::cout << "Grafite pequeno para escrever!\n";
            return false;
        }
        if (this->lead->getHardness() == "HB") {
            this->lead->usagePerSheet(1);
        }
        else if (this->lead->getHardness() == "2B") {
            this->lead->usagePerSheet(2);
        }
        else if (this->lead->getHardness() == "4B") {
            this->lead->usagePerSheet(4);
        }
        else if (this->lead->getHardness() == "6B") {
            this->lead->usagePerSheet(6);
        }
        return true;
    }
};
std::ostream& operator<<(std::ostream& os, const Pencil& pencil) {
    os << "[ Thickeness - " << pencil.thickness << "] : [ ";
    if (pencil.lead)
        os << *pencil.lead << " ]\n";
    else
        os << "No lead! ]\n";
    return os;
}

int main() {
    Lead lead("HB", 10, 0.5);
    Pencil pencil(0.5, &lead);
    std::cout << pencil;
    Lead lead2("2B", 11, 0.5);
    pencil.addLead(&lead2);
    std::cout << pencil;
    pencil.removeLead();
    std::cout << pencil;

    pencil.addLead(&lead2);
    pencil.write();
    pencil.write();
    
    std::cout << pencil;

}