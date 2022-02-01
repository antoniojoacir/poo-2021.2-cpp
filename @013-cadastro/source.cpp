#include <iostream>
#include <memory>
#include <list>

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

    bool transfer(shared_ptr<Account>& other, float value) {
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
        this->balance *= 0.01;
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
    
};
