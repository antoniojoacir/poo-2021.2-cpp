#include <iostream>
#include <map>
#include <memory>

template <typename AnswerType, typename Something>
using map_t = std::map<AnswerType, std::shared_ptr<Something>>;

class Client {
    std::string codeName;
    int balance;
    int limite;
public:

    Client(std::string name= "", int limite= 0) : codeName(name), limite(limite) {}

    friend std::ostream& operator<<(std::ostream& os, const Client& client);

    std::string getName() const {
        return codeName;
    }

    int getBalance() const {
        return balance;
    }

    int getLimite() const {
        return limite;
    }

    void setLimite(int limite) {
        this->limite = limite;
    }

    void setBalance(int balance) {
        this->balance = balance;
    }
};
std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "[" << client.codeName << " - " << client.balance << "/" << client.limite << "]";
    return os;
}

class Transference {
    std::string idCodeName;
    int cash;
public:
    Transference(std::string idCodeName, int value) : 
    idCodeName(idCodeName), cash(value) {}

    friend std::ostream& operator<<(std::ostream& os, const Transference& transference);

    std::string getIdCodeName() const {
        return idCodeName;
    }

    int getCash() const {
        return cash;
    }
};
std::ostream& operator<<(std::ostream& os, const Transference& transference) {
    os << "[" << transference.idCodeName << " - " << transference.cash << "]";
    return os;
}

class Agiota {
    map_t<std::string, Client> clients;
    map_t<int, Transference> transfers;
    int nextId { 0 };
    int balance;
public:

    Agiota(int balance) :
    balance(balance) {}

    friend std::ostream& operator<<(std::ostream& os, const Agiota& agiota);

    bool addClient(std::string name, int limite) {
        if (clients.find(name) == clients.end()) {
            clients[name] = std::make_shared<Client>(name, limite);
            return true;
        }
        std::cout << "Cliente já existe\n";
        return false;
    }

    bool transfer(std::string name, int value) {
        if (value < 0) {
            std::cout << "Não pode ser adicionado um valor negativo\n";
            return false;
        }
        if (clients.find(name) != clients.end()) {
            if (value < this->balance) {
                if (clients[name]->getLimite() >= value) {
                    transfers[this->nextId++] = std::make_shared<Transference>(name, value);
                    clients[name]->setLimite(clients[name]->getLimite() - value);
                    clients[name]->setBalance(clients[name]->getBalance() + value);
                    this->balance -= value;
                    return true;
                }
            }
        }
        std::cout << "Cliente não existe ou valor é maior que o saldo\n";
        return false;
    }

    bool kill(std::string name) {
        if (clients.find(name) != clients.end()) {
            clients.erase(name);
            for (auto& transfer : transfers) {
                if (transfer.second->getIdCodeName() == name) {
                    transfers.erase(transfer.first);
                }
            }
            return true;
        }
        std::cout << "Cliente não existe\n";
        return false;
    }

    bool receive(std::string name, int value) {
        if (clients.find(name) != clients.end()) {
            if (value <= clients[name]->getBalance()) {
                clients[name]->setLimite(clients[name]->getLimite() + value);
                clients[name]->setBalance(clients[name]->getBalance() - value);
                transfers[this->nextId++] = std::make_shared<Transference>(name, -value);
                this->balance += value;
                return true;
            }
        }
        std::cout << "Cliente não existe ou valor é maior que o saldo\n";
        return false;
    }
};
std::ostream& operator<<(std::ostream& os, const Agiota& agiota) {
    os << "Clientes: \n";
    for (auto& client : agiota.clients) {
        os << *client.second << "\n";
    }
    os << "Transferencias: \n";
    for (auto& transfer : agiota.transfers) {
        os << "id[" << transfer.first << "] " << *transfer.second << "\n";
    }
    os << "Balance >> " << agiota.balance << "\n";
    return os;
}

int main() {
    Agiota agiota(200);

    agiota.addClient("João", 100);
    agiota.addClient("Maria", 200);

    agiota.transfer("João", 50);
    agiota.transfer("João", 50);
    agiota.transfer("Maria", 50);

    agiota.receive("João", 50);

    agiota.kill("Maria");

    std::cout << agiota;

}