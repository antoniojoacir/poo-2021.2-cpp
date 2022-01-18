#include <iostream>
#include <map>

//---------------------------------------------------------------------------
//aluno.hpp
//---------------------------------------------------------------------------

class Disciplina; //forward declaration

class Aluno {
    std::string nome;
    std::map<std::string, Disciplina*> disciplinas;
public:
    Aluno(std::string nome);
    void addDisciplina(Disciplina * discp);
    void rmDisciplina(std::string nome_discp);
    std::string getNome() const;

    friend std::ostream& operator<<(std::ostream& os, const Aluno& aluno);
};

//---------------------------------------------------------------------------
//disciplina completa
//---------------------------------------------------------------------------

class Disciplina {
    std::string nome;
    std::map<std::string, Aluno*> alunos;
public:
    Disciplina(std::string nome);
    std::string getNome();

    void addAluno(Aluno * aluno) {
        auto key = aluno->getNome();
        if(this->alunos.find(key) == this->alunos.end()) {
            this->alunos[key] = aluno;
            aluno->addDisciplina(this);
        }
    }

    void rmAluno(std::string nome_aluno) {
        auto it = this->alunos.find(nome_aluno);
        if(it != this->alunos.end()) {
            auto alu = it->second;
            this->alunos.erase(it);
            alu->rmDisciplina(this->nome);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Disciplina discp) {
        os << discp.getNome() << " [ ";
        for (const auto& pair : discp.alunos)
            os << pair.first << " ";
        os << "]";
        return os;
    }
};

Disciplina::Disciplina(std::string nome) : nome {nome}
{
}

std::string Disciplina::getNome() {
    return nome;
}

//---------------------------------------------------------------------------
//aluno.cpp
//---------------------------------------------------------------------------

Aluno::Aluno(std::string nome): nome{nome}
{
}

void Aluno::addDisciplina(Disciplina *discp) {
    auto key = discp->getNome();
    if (this->disciplinas.find(key) == this->disciplinas.end()){
        this->disciplinas[key] = discp;
        discp->addAluno(this);
    }
}

std::string Aluno::getNome() const {
    return this->nome;
}

void Aluno::rmDisciplina(std::string nome_discp) {
    auto it = this->disciplinas.find(nome_discp);
    if(it != this->disciplinas.end()) {
        auto discp = it->second;
        this->disciplinas.erase(it);
        discp->rmAluno(this->nome);
    }
}

std::ostream& operator<<(std::ostream &os, const Aluno& aluno) {
    os << aluno.getNome()  << " [ ";
    for (const auto& pair : aluno.disciplinas)
        os << pair.first << " ";
    os << "]";
    return os;
}

//---------------------------------------------------------------------------
//main
//---------------------------------------------------------------------------

using namespace std;

int main()
{
    Aluno a1("Joao");
    Aluno a2("Maria");
    Aluno a3("Jose");

    Disciplina d1("FUP");
    Disciplina d2("POO");
    Disciplina d3("ED");

    a1.addDisciplina(&d1);
    a1.addDisciplina(&d2);
    a1.addDisciplina(&d3);

    a2.addDisciplina(&d1);

    a3.addDisciplina(&d2);

    cout << a1 << endl;
    cout << d1 << endl;

    a1.rmDisciplina("FUP");

    cout << a1 << endl;
    cout << d1 << endl;

    return 0;
}