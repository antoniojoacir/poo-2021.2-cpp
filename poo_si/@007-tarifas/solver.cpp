#include <iostream>
#include <vector>
#include <sstream>


enum class Label{
    ABERTURA,
    SAQUE,
    DEPOSITO,
    TARIFA,
    EXTORNO
};

std::string toString(Label op) {
    switch(op) {
        case Label::ABERTURA:
            return "Opening";
        case Label::SAQUE:
            return "Withdraw";
        case Label::DEPOSITO:
            return "Deposit";
        case Label::TARIFA:
            return "Tariff";
        case Label::EXTORNO:
            return "Reverse";
        default:
            return "";
    }
}

class Operation {
public:
    Label label;
    int index;
    int value;
    int balance;

    Operation(Label label, int index, int value, int balance) :
    label(label), index(index), value(value), balance(balance) {}

    friend std::ostream& operator<<(std::ostream& os, const Operation& op) {
        os << "~" << toString(op.label) << "[" << op.index << "] | Input: " << op.value << " | Balance: " << op.balance << "\n";
        return os;
    }
};

class Account {
    std::vector<Operation> operations;
    int next_index { 0 };
    int balance;
    int number;
public:

    Account(int balance= 0, int number= 0) : balance(balance), number(number) {
    }

    friend std::ostream& operator<<(std::ostream& os, const Account& account) {
        os << "Account Nº" << account.number << "\n";
        for(auto op : account.operations) {
            os << op;
        }
        return os;
    }

    bool init(int value) {
        if (this->number == 0) {
            this->number = value;
            operations.push_back(Operation(Label::ABERTURA, this->next_index++, this->balance, this->balance));
            return true;
        }
        return false;
    }

    bool withdraw(int value) {
        if (value > balance) {
            std::cout << "insufficient funds\n";
            return false;
        }
        if (value < 0) {
            std::cout << "invalid value\n";
            return false;
        }
        balance -= value;
        operations.push_back(Operation(Label::SAQUE, this->next_index++, -value, this->balance));
        return true;
    }

    bool deposit(int value) {
        if (value < 0) {
            std::cout << "invalid value\n";
            return false;
        }
        balance += value;
        operations.push_back(Operation(Label::DEPOSITO, this->next_index++, value, this->balance));
        return true;
    }

    bool tariff(int value) {
        if (value < 0) {
            std::cout << "invalid value\n";
            return false;
        }
        balance -= value;
        operations.push_back(Operation(Label::TARIFA, this->next_index++, -value, this->balance));
        return true;
    }

    void reverse_balance(int index) {
        for (auto i = (int) operations.size() - 1; i >= 0; i--) {
            if (operations[i].index == index) {
                if (operations[i].label == Label::TARIFA) { 
                    this->balance += abs(operations[i].value);
                    operations.push_back(Operation(Label::EXTORNO, this->next_index++, operations[i].value, this->balance));
                    return;
                }
            }
        }
        std::cout << "invalid transaction\n";
    }
};


int main() {
    Account account;
    while (true) {
        std::cout << "$";
        std::string command;
        getline(std::cin, command);
        std::stringstream ss(command);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "init") {
            int value = 0;
            ss >> value;
            if (!account.init(value)) {
                std::cout << "account already initialized\n";
            }
        }
        else if (cmd == "withdraw") {
            int value = 0;
            ss >> value;
            account.withdraw(value);
        }
        else if (cmd == "deposit") {
            int value = 0;
            ss >> value;
            account.deposit(value);
        }
        else if (cmd == "tariff") {
            int value = 0;
            ss >> value;
            account.tariff(value);
        }
        else if (cmd == "reverse") {
            int index = 0;
            ss >> index;
            account.reverse_balance(index);
        }
        else if (cmd == "show") {
            std::cout << account;
        }
        else {
            std::cout << "invalid command: " << cmd << "\n";
        }
    }
    return 0;
}