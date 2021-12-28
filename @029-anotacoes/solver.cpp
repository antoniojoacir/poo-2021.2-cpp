#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <memory>


using namespace std;

template <typename AnswerType>
using vec_t = std::vector<std::shared_ptr<AnswerType>>;

template <typename Type, typename T>
using map_t = std::map<Type, std::shared_ptr<T>>;

class Note {
    string title;
    string content;
public:
    Note(string title= "", string content= "") : 
    title(title), content(content) {}

    friend std::ostream& operator<<(std::ostream& os, const Note& note);
    
    string getTitle() {
        return title;
    }

    string getContent() {
        return content;
    }
};
std::ostream& operator<<(std::ostream& os, const Note& note) {
    os << "Title: " << note.title << endl;
    os << "Content: " << note.content << endl;
    return os;
}

class User {
    string userName;
    string password;
    vec_t<Note> notes;
public:

    User(string name, string pass) :
    userName(name), password(pass) {}

    string getUserName() const { return userName; }

    string getPassword() const { return password; }

    vec_t<Note> getNotes() const { return notes; }

    void addNote(string title, string content) {
        notes.push_back(std::make_shared<Note>(title, content));
        cout << "Added note\n";
    }   

    bool rmNote(int index) {
        if (index < 0 || index >= (int) notes.size()) {
            cout << "Invalid index\n";
            return false;
        }
        if (notes.empty()) {
            cout << "No notes to remove\n";
            return false;
        }
        notes.erase(notes.begin() + index);
        cout << "Removed note\n";
        return true;
    }
};

class LoginManeger {
    map_t<string, User> usersLogins;
    User * currentUser;
public:

    LoginManeger(User * user, map_t<string, User> usersLog) :
    currentUser(user), usersLogins(usersLog) {}

    
};

class System {
    map_t<string, User> users;
    LoginManeger * loginManeger;
public:

    System() {}

    void addUser(string name, string pass) {
        if(users.end() == users.find(name)) {
            users.insert(make_pair(name, make_shared<User>(name, pass)));
            cout << "User added\n";
        } else {
            cout << "User already exists\n";
        }
    }

    bool addNote(string name, string title, string content) {
        if(users.end() == users.find(name)) {
            cout << "User does not exist\n";
            return false;
        }
        users[name]->addNote(title, content);
        return true;
    }

    User * getUser(string name) {
        if(users.end() == users.find(name)) {
            cout << "User does not exist\n";
            return nullptr;
        }
        return users[name].get();
    }
};

int main() {

}