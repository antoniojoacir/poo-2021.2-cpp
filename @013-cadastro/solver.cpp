#include <iostream>
#include <vector>
#include <memory>
#include <map>

class Account {
protected:
    double balance { 0.0 };
    std::string name;
    int id;
    std::string type;
public:

    Account(std::string name="", int id= 0, std::string type="") :
    name(name), id(id), type(type) {}

    virtual void manutecao() = 0;

    friend std::ostream& operator<<(std::ostream& stream, const Account& account);

    std::string getName() const { return name; }

    int getId() const { return id; }

    std::string getType() const { return type; }

    double getBalance() const { return balance; }

    bool setBalance(double balance) {
        if (balance < 0) {
            std::cout << "Valor invalido\n";
            return false;
        }
        this->balance += balance;
        return true;
    }

    bool transfer(Account& account, double value) {
        if (value < 0) {
            std::cout << "Valor invalido\n";
            return false;
        }
        if (this->balance < value) {
            std::cout << "Saldo insuficiente\n";
            return false;
        }
        this->balance -= value;
        account.setBalance(value);
        return true;
    }

    bool withdraw(double value) {
        if (value < 0) {
            std::cout << "Valor invalido\n";
            return false;
        }
        if (this->balance < value) {
            std::cout << "Saldo insuficiente\n";
            return false;
        }
        this->balance -= value;
        return true;
    }
};
std::ostream& operator<<(std::ostream& stream, const Account& account) {
    stream << " [" << account.id << "] [" << account.type << "] - ";
    stream << account.balance << "R$ ]\n";
    return stream;
}


class SavingsAccount : public Account {
public:
    SavingsAccount(std::string name="", int id= 0, std::string type="CP") :
    Account(name, id, type) {}

    void manutecao() override {
        balance += balance * 0.01; // 1% de juros
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(std::string name="", int id= 0, std::string type="CC") :
    Account(name, id, type) {}

    void manutecao() override {
        balance -= 20 ; // 20 reais de manutenção
    }
};

class Client {
    std::string name;
    std::vector<std::shared_ptr<Account>> accounts;
public:
    Client(std::string name="") : name(name) {
    }

    int addAccount(int id) {
        accounts.push_back(std::make_shared<SavingsAccount>(this->name, id++));
        accounts.push_back(std::make_shared<CheckingAccount>(this->name, id++));
        return id;
    }

    std::string getName() const { return name; }

    //retornar accounts
    std::vector<std::shared_ptr<Account>> getAccounts() {
        return accounts;
    }
};

class Bank {
    std::map<std::string, std::shared_ptr<Client>> map_clients;
    int nextId { 0 };
public:
    Bank() {}

    friend std::ostream& operator<<(std::ostream& os, const Bank& bank);

    Account * getAccount(int id) {
        for (auto &client : map_clients) {
            for (auto &account : client.second->getAccounts()) {
                if (account->getId() == id) {
                    return account.get();
                }
            }
        }
        return nullptr;
    }

    void addClient(std::string name) {
        auto client = std::make_shared<Client>(name);
        this->nextId = client->addAccount(nextId);
        map_clients.insert(std::make_pair(name, client));
    }
};
std::ostream& operator<<(std::ostream& os, const Bank& bank) {
    os << "Clients ~\n";
    for (auto &client : bank.map_clients) {
        os << client.second->getName() << " [ ";
        for (auto &account : client.second->getAccounts()) {
            os << account->getId() << " ";
        }
        os << "]\n";
    }
    os << "\nAccounts ~\n";
    for (auto &client : bank.map_clients) {
        for (auto &account : client.second->getAccounts()) {
            os << client.second->getName() << " [";
            os << *account;
        }
    }
    return os;
}

int main() {
    Bank bank;
    bank.addClient("Joao");
    bank.addClient("Maria");
    bank.addClient("Pedro");

    bank.getAccount(1)->setBalance(100);

    bank.getAccount(1)->transfer(*bank.getAccount(5), 200);
    std::cout << bank;

}
