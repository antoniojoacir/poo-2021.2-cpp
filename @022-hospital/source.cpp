#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Medico;

class Paciente {
    map<string, Medico*> medicos;
    string name;
    string diagnostico;
public:
    Paciente(string name, string diagnostico);
    
    map<string, Medico*> getMedicos() const;
    
    string getName() const;

    string getDiagnostico() const;
    
    bool addMedico(Medico * medico);

    bool rmMedico(string nome_medico);

    friend ostream& operator<<(ostream&, const Paciente&);
};

class Medico {
    map<string, Paciente*> pacientes;
    string name;
    string especialidade;
public:
    Medico(string name, string especialidade);

    string getName() const;

    string getEspecialidade() const;

    map<string, Paciente*> getPacientes() const;

    bool addPaciente(Paciente * paciente) {
        if (this->pacientes.find(paciente->getName()) == this->pacientes.end()) {
            this->pacientes.insert(pair<string, Paciente*>(paciente->getName(), paciente));
            paciente->addMedico(this);
            return true;
        }
        return false;
    }

    bool rmPaciente(string name) {
        auto it = this->pacientes.find(name);
        if (it != this->pacientes.end()) {
            auto pac = it->second;
            this->pacientes.erase(it);
            pac->rmMedico(this->name);
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& out, Medico medico) {
        out << "Medi " << medico.getName() << " [" << medico.getEspecialidade() << "] Pacientes: ";
        for (const auto& pair : medico.pacientes)
            out << " " << pair.first << ":" << pair.second->getDiagnostico();
        out << endl; 
        return out;
    }
};

Medico::Medico(string name, string especialidade) :
name{name}, especialidade{especialidade}
{
}

string Medico::getName() const {
    return name;
}

string Medico::getEspecialidade() const {
    return especialidade;
}

map<string, Paciente*> Medico::getPacientes() const {
    return pacientes;
}

// ! começa aqui a implementação da classe Paciente

Paciente::Paciente(string name, string diagnostico) : 
name{name}, diagnostico{diagnostico}
{
}

map<string, Medico*> Paciente::getMedicos() const {
    return medicos;
}

string Paciente::getName() const {
    return name;
}

string Paciente::getDiagnostico() const {
    return diagnostico;
}

bool Paciente::addMedico(Medico * medico) {
    if (medicos.find(medico->getName()) != medicos.end()) {
        return false;
    }
    for (const auto& pair : medicos) {
        if (pair.second->getEspecialidade() == medico->getEspecialidade()) {
            return false;
        }
    }
    medicos.insert(pair<string, Medico*>(medico->getName(), medico));
    medico->addPaciente(this);
    return true;
}

bool Paciente::rmMedico(string nome_medico) {
    auto it = medicos.find(nome_medico);
    if (it != medicos.end()) {
        auto med = it->second;
        medicos.erase(it);
        med->rmPaciente(this->name);
        return true;
    }
    return false;
}

ostream& operator<<(ostream& out, const Paciente& paciente) {
    out << "Paci " << paciente.getName() << " [" << paciente.getDiagnostico() << "] Medicos: ";
    for (const auto& pair : paciente.medicos)
        out << " " << pair.first << ":" << pair.second->getEspecialidade();
    out << endl;
    return out;
}

// ! termina aqui a implementação da classe Paciente

class Hospital {
    map<string, Medico*> medicos_cadastrados;
    map<string, Paciente*> pacientes_cadastrados;
public:
    Hospital() {
    }

    void addMedicoH(Medico * medico) {
        this->medicos_cadastrados.insert(pair<string, Medico*>(medico->getName(), medico));
    }

    void addPacienteH(Paciente * paciente) {
        this->pacientes_cadastrados.insert(pair<string, Paciente*>(paciente->getName(), paciente));
    }

    void rmMedicoH(string nome_medico) {
        auto it = medicos_cadastrados.find(nome_medico);
        if (it != medicos_cadastrados.end()) {
            auto med = it->second;
            medicos_cadastrados.erase(it);
            for (const auto& pair : med->getPacientes()) {
                pair.second->rmMedico(med->getName());
            }
        }
    }

    void rmPacienteH(string nome_paciente) {
        auto it = pacientes_cadastrados.find(nome_paciente);
        if (it != pacientes_cadastrados.end()) {
            auto pac = it->second;
            pacientes_cadastrados.erase(it);
            for (const auto& pair : pac->getMedicos()) {
                pair.second->rmPaciente(pac->getName());
            }
        }
    }

    void vincular(string nameMedico, string namePaciente) {
        auto it = pacientes_cadastrados.find(namePaciente);
        if (it == pacientes_cadastrados.end()) {
            cout << "Paciente nao encontrado" << endl;
            return;
        }
        auto pac = it->second;
        auto it2 = medicos_cadastrados.find(nameMedico);
        if (it2 == medicos_cadastrados.end()) {
            cout << "Medico nao encontrado" << endl;
            return;
        }
        auto med = it2->second;
        if (med->addPaciente(pac)) {
            cout << "Paciente " << namePaciente << " vinculado ao medico " << nameMedico << endl;
        } else {
            cout << "Medico " << nameMedico << " ja trabalha com esse paciente" << endl;
        }
    }

    void desvincular(string nameMedico, string namePaciente) {
        auto it = pacientes_cadastrados.find(namePaciente);
        if (it == pacientes_cadastrados.end()) {
            cout << "Paciente nao encontrado" << endl;
            return;
        }
        auto pac = it->second;
        auto it2 = medicos_cadastrados.find(nameMedico);
        if (it2 == medicos_cadastrados.end()) {
            cout << "Medico nao encontrado" << endl;
            return;
        }
        auto med = it2->second;
        if (med->rmPaciente(pac->getName())) {
            cout << "Paciente " << namePaciente << " desvinculado do medico " << nameMedico << endl;
        } else {
            cout << "Medico " << nameMedico << " nao trabalha com esse paciente" << endl;
        }
    }

    void show() {
        for (const auto& pair : medicos_cadastrados) {
            cout << *pair.second;
        }
        cout << endl;
        for (const auto& pair : pacientes_cadastrados) {
            cout << *pair.second;
        }
    }
};

int main() {
    Hospital hospital;
    Medico joao("Joao", "Cardiologia");
    Medico maria("Maria", "Anestesiologia");
    Medico pedro("Pedro", "Hematologia");

    hospital.addMedicoH(&joao);
    hospital.addMedicoH(&maria);
    hospital.addMedicoH(&pedro);

    //hospital.show();

    Paciente patata("patata", "Cancer");
    Paciente patati("patati", "Gripe");
    Paciente galinhapintadinha("galinhapintadinha", "Tuberculose");

    hospital.addPacienteH(&patata);
    hospital.addPacienteH(&patati);
    hospital.addPacienteH(&galinhapintadinha);

    //hospital.show();

    hospital.vincular("Maria", "patata");
    hospital.vincular("Maria", "patati");
    hospital.vincular("Maria", "galinhapintadinha");


   // hospital.show();

    hospital.rmMedicoH("Pedro");
    hospital.rmPacienteH("patati");

    //hospital.show();

    hospital.desvincular("Maria", "patata");

    hospital.show();

    return 0;
}