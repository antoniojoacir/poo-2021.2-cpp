#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <memory>

class Person {
    std::string idName;
public:

    Person(std::string name= "") : idName(name) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& person);

    std::string getId() const {
        return idName;
    }
};
std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.idName;
    return os;
}

class Mercantil {
    std::vector<std::shared_ptr<Person>> emAtendimento;
    std::list<std::shared_ptr<Person>> emEspera;
    bool validadeIndex(int index) {
        if (emAtendimento.empty()) {
            return false;
        }
        if (index < 0 || index >= (int) emAtendimento.size()) {
            return false;
        }
        return true;
    }
public:

    Mercantil(int size) : emAtendimento(size, nullptr) {}

    friend std::ostream& operator<<(std::ostream& os, const Mercantil& mercantil);

    void chegar(const std::shared_ptr<Person>& person) {
        emEspera.push_back(person);
    }

    bool chamar(int index) {
        if (!validadeIndex(index)) {
            std::cout << "Index invalido\n";
            return false;
        }
        if (this->emAtendimento[index] != nullptr) {
            std::cout << "Caixa ocupado\n";
            return false;
        }
        this->emAtendimento[index] = this->emEspera.front();
        this->emEspera.pop_front();
        return true;
    }

    Person * finalizar(int index) {
        if (emAtendimento.empty()) {
            return nullptr;
        }
        if (!validadeIndex(index)) {
            std::cout << "Index invalido\n";
            return nullptr;
        }
        if (this->emAtendimento[index] == nullptr) {
            std::cout << "Caixa vazio\n";
            return nullptr;
        }
        Person * person = this->emAtendimento[index].get();
        this->emAtendimento[index] = nullptr;
        return person;
    }
};
std::ostream& operator<<(std::ostream& os, const Mercantil& mercantil) {
    os << "Em atendimento: \n";
    for (auto& person : mercantil.emAtendimento) {
        if (person != nullptr) {
            os << *person << " | ";
        }
        else {
            os << "nullptr ";
        }
    }
    os << "\nEm espera: \n";
    for (auto& person : mercantil.emEspera) {
        os << *person << " ";
    }
    return os;
}

int main() {
    Mercantil mercantil(4);
    mercantil.chegar(std::make_shared<Person>("Joao"));
    mercantil.chegar(std::make_shared<Person>("Maria"));
    mercantil.chegar(std::make_shared<Person>("Pedro"));
    mercantil.chegar(std::make_shared<Person>("Jose"));

    std::cout << mercantil << "\n\n";

    mercantil.chamar(0);
    mercantil.chamar(1);
    mercantil.chamar(2);
    mercantil.chamar(3);

    std::cout << mercantil << "\n\n";

    mercantil.finalizar(0);
    mercantil.finalizar(2);

    std::cout << mercantil << "\n";
}