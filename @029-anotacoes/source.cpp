#include <iostream>
#include <vector>
#include <map>
#include <memory>

using namespace std;

struct NOTE {
    string tittle;
    string content;

    NOTE(string tittle, string content) : tittle(tittle), content(content)
    {
    }

    friend ostream& operator<<(ostream&, const NOTE&);
};
ostream& operator<<(ostream& output, const NOTE& note) {
    output << "[" << note.tittle << ": " << note.content << "]\n";
    return output;
}

class USER {
    string userName;
    string id;
    std::vector<std::shared_ptr<NOTE>> notes;
public:
    USER(string user, string password) : userName(user), id(password)
    {
    }

    string getUserName() const {
        return userName;
    }

    string getId() const {
        return id;
    }

    void addNote(string tittle, string content) {
        notes.push_back(std::make_shared<NOTE>(tittle, content));
    }

    bool rmNote(int index) {
        if (notes.empty()) return false;

        if (index < 0 || index >= (int) notes.size()) return false;

        notes.erase(notes.begin() + index); return true;
    }

    friend ostream& operator<<(ostream&, const USER&);
};
ostream& operator<<(ostream& output, const USER& user) {
    output << "- " << user.userName << "\n";
    for (auto note : user.notes) {
        output << *note;
    }
    return output;
}

class LOGINMANAGER {
    USER * currentUser { nullptr };
    map<string, std::shared_ptr<USER>> users;
public:
    LOGINMANAGER(map<string, std::shared_ptr<USER>> users) : users(users)
    {
    }

    USER * getCurrentUser() { return currentUser; }

    USER * getUser(string name) { 
        auto it = users.find(name);
        if (it == users.end()) return nullptr;
        return it->second.get();
    }

    bool login(string username, string password) {
        auto it = users.find(username);
        if (it == users.end()) return false;
        if (it->second->getId() != password) {
            cout << "ERROR: Wrong password\n";
            return false;
        }
        return true;
    }

    void logout() {
        if (currentUser == nullptr) {
            cout << "ERROR: No current user\n";
            return;
        }
        currentUser = nullptr;
    }
};

class SYSTEM {
    LOGINMANAGER loginManager;
    map<string, std::shared_ptr<USER>> users;
public:
    SYSTEM()
    {
    }
};


int main() {
    USER userOne("joa", "paocomgoiaba");
    userOne.addNote("requeijão", "eu não gosto de requeijão");

    cout << userOne;
}