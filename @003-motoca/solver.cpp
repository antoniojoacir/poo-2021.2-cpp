#include <iostream>
#include <algorithm>

class Kid {
    std::string name;
    int age;
public:

    Kid(std::string name= "", int age= 0) :
    name(name), age(age) {}

    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    friend std::ostream& operator<<(std::ostream& os, const Kid& person);
};
std::ostream& operator<<(std::ostream& os, const Kid& person) {
    os << "[" << person.name << ":" << person.age << "]";
    return os;
}

class Bike {
    int power;
    Kid * kid { nullptr };
    int time { 0 };
public:

    Bike(int power= 1) :
    power(power) {}

    friend std::ostream& operator<<(std::ostream& os, const Bike& bike);

    bool enter(Kid * person) {
        if (this->kid != nullptr) {
            std::cout << "Já há uma criança na motocicleta\n";
            return false;
        }
        this->kid = person;
        return true;
    }

    Kid * exit() {
        if (this->kid == nullptr) {
            std::cout << "Não há ninguém na motocicleta\n";
            return nullptr;
        }
        this->time = 0;
        return std::exchange(this->kid, nullptr);
    }

    bool buy(int buy) {
        if (this->kid == nullptr) {
            std::cout << "Não há ninguém para comprar tempo\n";
            return false;
        }
        if (buy < 0) {
            std::cout << "Não é possível comprar tempo negativo\n";
            return false;
        }
        this->time += buy;
        return true;
    }

    void honk() {
        std::cout << 'P';
        for (auto i = 0 ; i < this->power ; i++) {
            std::cout << 'e';
        }
        std::cout << '\n';
    }

    bool drive(int drive) {
        if (this->kid->getAge() > 10) {
            std::cout << "Não é possível dirigir uma criança com mais de 10 anos\n";
            return false;
        }
        if (this->time <= 0) {
            std::cout << "Não há tempo para dirigir\n";
            return false;
        }
        if (drive > time) {
            std::cout << "Andou por " << time << " minutos e não pode andar mais\n";
            return true;
        }
        this->time -= drive;
        std::cout << "Dirigiu por " << drive << " minutos\n";
        return true;
    }

};
std::ostream& operator<<(std::ostream& os, const Bike& bike) {
    os << "Bike(" << bike.power << ") - ";
    if (bike.kid)
        os << *bike.kid << " : Tempo - " << bike.time << "\n";
    else
        os << "(vazia) : Tempo - " << bike.time << "\n";
    return os;
}

int main() {
    Bike bike;

    std::cout << bike;
}