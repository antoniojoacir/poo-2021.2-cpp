#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <tuple>
#include <algorithm>
using namespace std;

template <typename T>
using ptr = shared_ptr<T>;

//guardar o texto e o usuario
//Interface
class IMsg {
public:
    virtual string getSender() = 0;
    virtual string getText() = 0;
    virtual ~IMsg() {}
    friend ostream& operator<<(ostream& os, IMsg& msg);
};
ostream& operator<<(ostream& os, IMsg& msg) {
    os << msg.getSender() << ": " << msg.getText();
    return os;
}

class Msg : public IMsg {
    string sender;
    string text;
public:
    Msg(string sender, string text) {
        this->sender = sender;
        this->text = text;
    }
    virtual string getSender() override {
        return sender;
    }
    virtual string getText() override {
        return text;
    }
};

//guardar, recuperar e enviar as mensagens
class User {
    string username;
    vector<ptr<IMsg>> inbox;
    vector<ptr<IMsg>> sent;
public:
    User(string username) : username(username) {}

    void sendMsg(User& receiver, string text) {
        auto msg = make_shared<IMsg>(this->username, text);
        receiver.inbox.push_back(msg);
        this->sent.push_back(msg);
    }

    string getInbox() {
        stringstream ss;
        for (auto msg : this->inbox)
            ss << msg << endl;
        this->inbox.clear();
        return ss.str();
    }

    string getSent() {
        stringstream ss;
        for (auto msg : this->sent)
            ss << msg << endl;
        return ss.str();
    }

    virtual ~User() {}
};

//encontrar e gerenciar os usuarios
class UserManager {
    map<string, ptr<User>> users;

public:
    UserManager() {}

    void addUser(string username) {
        if (users.find(username) == users.end()) {
            users[username] = make_shared<User>(username);
        } else {
            throw runtime_error("User " + username + " already exists");
        }
    }

    string getUsernames() {
        string result;
        for (auto& user : users) {
            result += user.first + " ";
        }
        return result;
    }

    User* findUser(string username) {
        auto it = users.find(username);
        if (it == users.end())
            throw runtime_error("User " + username + " not found");
        return it->second.get();
    }

    void sendMsg(string sender, string receiver, string text) {
        auto senderUser = findUser(sender);
        auto receiverUser = findUser(receiver);
        senderUser->sendMsg(*receiverUser, text);
    }
};

template <typename T>
T read(stringstream& ss) {
    T t;
    ss >> t;
    return t;
}

template <typename... Args>
auto parse(std::istream& is) {
    std::tuple<Args...> t;
    std::apply([&is](auto&&... args) {((is >> args), ...);}, t);
    return t;
}

int main(){
    UserManager um;

    while(true) {
        std::string line{}, cmd{};
        std::getline(std::cin, line);
        std::stringstream ss(line);
        ss >> cmd;
        std::cout << "$" << line << '\n';
        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            cout << um.getUsernames() << endl;
        } else if (cmd == "add") {
            um.addUser(read<string>(ss));
        } else if (cmd == "send") {//sender receiver texto a ser enviado
            string sender = read<string>(ss);
            string receiver = read<string>(ss);
            string text{};
            getline(ss, text);
            um.sendMsg(sender, receiver, text.substr(1));
        } else if (cmd == "sent") {
            cout << um.findUser(read<string>(ss))->getSent() << endl;
        } else if (cmd == "inbox") {
            cout << um.findUser(read<string>(ss))->getInbox() << endl;
        } else {
            std::cout << "fail: comando invalido" << '\n';
        }
    }
    return 0;
}