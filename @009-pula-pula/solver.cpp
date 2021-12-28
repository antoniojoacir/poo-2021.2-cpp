#include <iostream>
#include <algorithm>
#include <list>
#include <memory>

template <typename Something>
using lptr = std::list<std::shared_ptr<Something>>;

template <typename Anything>
using ptr = std::shared_ptr<Anything>;

class Kid {
    std::string name;
    int age;
public:

    Kid(std::string name= "", int age= 0) : 
    name(name), age(age) {}

    friend std::ostream& operator<<(std::ostream& os, const Kid& kid);

    std::string getName() const { return name; }

    int getAge() const { return age; }

};
std::ostream& operator<<(std::ostream& os, const Kid& kid) {
    os << "[" << kid.name << ":" << kid.age << "]";
    return os;
}

class Toy {
    lptr<Kid> playing;
    lptr<Kid> waiting;
public:

    Toy() {}

    friend std::ostream& operator<<(std::ostream& os, const Toy& toy);

    void comming(const ptr<Kid>& kid) {
        waiting.push_back(kid);
    }

    bool pull() {
        if (waiting.empty()) {
            std::cout << "Não há ninguém na fila de espera\n";
            return false;
        }
        playing.push_back(waiting.front());
        waiting.pop_front();
        return true;
    }

    bool out() {
        if (playing.empty()) {
            std::cout << "Não há ninguém brincando\n";
            return false;
        }
        waiting.push_back(playing.front());
        playing.pop_front();
        return true;
    }

    bool romove(std::string name) {
        for (auto it = playing.begin(); it != playing.end(); ++it) {
            if ((*it)->getName() == name) {
                playing.erase(it);
                return true;
            }
        }
        for (auto it = waiting.begin(); it != waiting.end(); ++it) {
            if ((*it)->getName() == name) {
                waiting.erase(it);
                return true;
            }
        }
        std::cout << "Não há ninguém com esse nome\n";
        return false;
    }
};
std::ostream& operator<<(std::ostream& os, const Toy& toy) {
    os << "No brinquedo: ";
    for (auto& kid : toy.playing) {
        os << *kid << " ";
    }
    os << "\nEsperando: ";
    for (auto& kid : toy.waiting) {
        os << *kid << " ";
    }
    os << "\n";
    return os;
}
int main() {
    Toy toy;

    toy.comming(std::make_shared<Kid>("João", 10));
    toy.comming(std::make_shared<Kid>("Maria", 5));

    toy.pull();

    std::cout << toy;

    toy.out();

    std::cout << toy;

    toy.romove("Maria");

    std::cout << toy;
}