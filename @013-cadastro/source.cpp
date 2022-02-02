#include <iostream>
#include <memory>
#include <list>
#include <map>

using namespace std;

class Account {
protected:
    float balance = 0;
    int id; // ? interador da agenda
    string key; // ! por meio dela que vou achar as contas
    string type; // ! type of account
public:
    Account(int id, string name, string type) : id(id), key(name), type(type)
    {
    }

    float getBalance() const { return this->balance; }

    int getId() const { return this->id; }

    string getClientId() const { return this->key; }

    string getType() const { return this->type; }

    virtual void mothyUpdate() = 0;

    void deposit(float value) {
        if(value < 0) {   
            cout <<"Error: Value cannot be negative\n";
            return;
        }
        cout << "Success: Operation performed successfully\n";
        this->balance += value;
    }

    bool transfer(Account * other, float value) {
        if(value < 0) {   
            cout <<"Error: Value cannot be negative\n";
            return false;
        }
        if(this->balance < value) {
            cout << "Error: Amount greater than the account balance\n";
            return false;
        }
        other->deposit(value);
        this->balance -= value;
        cout << "Success: Operation performed successfully\n";
        return true;
    }

    bool withdraw(float value) {
        if(value < 0) {   
            cout <<"Error: Value cannot be negative\n";
            return false;
        }
        if(this->balance < value) {
            cout << "Error: Amount greater than the account balance\n";
            return false;
        }
        this->balance -= value;
        cout << "Success: Operation performed successfully\n";
        return true;
    }

    friend ostream& operator<<(ostream&, const Account&);
};
ostream& operator<<(ostream& out, const Account& account) {
    out << account.id << ":" << account.key << " [" << account.balance << "R$:" << account.type << "]\n";
    return out;
}

class Cheking : public Account {
public:
    Cheking(int id, string name) : Account(id, name, "CC")
    {
    }

    void mothyUpdate() override {
        // ? cada vez que essa função for chamada ela vai subtrair 20 reais do saldo
        this->balance -= 20;
        cout << "Success: Operation performed successfully\n";
    }
};

class Saving : public Account {
public:
    Saving(int id, string name) : Account(id, name, "CP")
    {
    }

    void mothyUpdate() override {
        // ? cada vez que essa função for chamada ela vai acrescentar 1% ao saldo
        this->balance = this->balance + (this->balance * 0.01);
        cout << "Success: Operation performed successfully\n";
    }
};

class Client {
    list<shared_ptr<Account>> accounts;
    string nameId;
public:
    Client(string nameId) : nameId(nameId)
    {
    }
    
    friend ostream& operator<<(ostream&, const Client&);

    list<shared_ptr<Account>> getAccounts() {
        return this->accounts;
    }

    string getNameId() {
        return this->nameId;
    }

    void addAccount(shared_ptr<Account> account) {
        this->accounts.push_back(account);
    }
};
ostream& operator<<(ostream& out, const Client& client) {
    out << client.nameId << ": ";
    for(auto account : client.accounts) {
        out << *account;
    }
    return out;
}

class Bank {
    map<int, shared_ptr<Account>> accounts; 
    map<string, shared_ptr<Client>> clients;
    int nextId { 0 };
    Account* getAccount(int id) {
        auto it = this->accounts.find(id);
        if(it == this->accounts.end()) {
            return nullptr;
        }
        return it->second.get();
    }
public:
    Bank() {}

    void addClient(string nameId) {
        auto it = this->clients.find(nameId);
        if(it != this->clients.end()) {
            it->second->addAccount(make_shared<Cheking>(this->nextId++, nameId));
            it->second->addAccount(make_shared<Saving>(this->nextId++, nameId));
            auto accounts = it->second->getAccounts();
            for(auto account : accounts) {
                this->accounts.insert(pair<int, shared_ptr<Account>>(account->getId(), account));
            }
            return;
        } else {
            auto client = make_shared<Client>(nameId);
            client->addAccount(make_shared<Cheking>(this->nextId++, nameId));
            client->addAccount(make_shared<Saving>(this->nextId++, nameId));
            this->clients.insert(make_pair(nameId, client));
            auto accounts = client->getAccounts();
            for(auto account : accounts) {
                this->accounts.insert(pair<int, shared_ptr<Account>>(account->getId(), account));
            }
        }
    }

    bool deposit(int id, float value) {
        auto account = this->getAccount(id);
        if(account == nullptr) {
            cout << "Error: Account not found\n";
            return false;
        }
        account->deposit(value);
        return true;
    }

    bool transfer(int id, int id2, float value) {
        auto youSent = this->getAccount(id);
        auto hasReceived = this->getAccount(id2);
        if(youSent == nullptr || hasReceived == nullptr) {
            cout << "Error: Account not found\n";
            return false;
        }
        return youSent->transfer(hasReceived, value);
    }

    bool whitdraw(int id, float value) {
        auto account = this->getAccount(id);
        if(account == nullptr) {
            cout << "Error: Account not found\n";
            return false;
        }
        return account->withdraw(value);
    }
    
    void mothyUpdate() {
        for(auto& account : this->accounts) {
            account.second->mothyUpdate();
        }
    }

    friend ostream& operator<<(ostream&, const Bank&);
};
ostream& operator<<(ostream& out, const Bank& bank) {
    out << "Clients: " << endl;
    for(auto client : bank.clients) {
        out << client.first << endl;
    }
    out << "Accounts: " << endl;
    for(auto account : bank.accounts) {
        out << *account.second;
    }
    return out;
}


int main() {
    Bank bank;
    bank.addClient("Joao");
    bank.addClient("Maria");
    bank.addClient("Joao");

    bank.deposit(1, 100);
    bank.transfer(1, 2, 50);
    bank.whitdraw(2, 25);
    bank.mothyUpdate();
    cout << bank << endl;
}