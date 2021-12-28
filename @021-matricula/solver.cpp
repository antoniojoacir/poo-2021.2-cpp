#include <iostream>
#include <map>
#include <memory>

template <typename T>
using sptr = std::shared_ptr<T>;

class Aluno {
    std::string IDalunos;
    std::map<std::string, Discp> disciplinas;
public:

};


class Discp {
    std::string IDdisciplinas;
    std::map<std::string, Aluno> alunos;
public:
};

int main() {

}