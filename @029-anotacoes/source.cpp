#include <iostream>

using namespace std;

class Note {
    string tittle;
    string content;
public:
    Note(string tittle, string content) : tittle(tittle), content(content)
    {
    }

    string getTittle() const { return this->tittle; }
    string getContent() const { return this->content; }

    friend ostream& operator<<(ostream&, const Note&);
};
ostream& operator<<(ostream& out, const Note& note) {
    out << "[ " << note.tittle << ": (" << note.content << ") ]\n";
    return out;    
}

#include <vector>
#include <memory>

template <typename T>
using vecptr = vector<shared_ptr<T>>;

class User {
    string username;
    string password;
    vecptr<Note> notes;
public:
    User(string username, string password) : username(username), password(password)
    {
    }

    string getUsername() const { return this->username; }
    vecptr<Note> getNotes() const { return this->notes; }

    void addNote(string tittle, string content) {
        this->notes.push_back(make_shared<Note>(tittle, content));
    }

    bool rmNote(int index) {
        if (notes.empty()) {
            cout << "Sem notas para remover\n";
            return false;
        }
        if (index < 0 || index >= (int) notes.size()) {
            cout << "Index invalido\n";
            return false;
        }
        notes.erase(notes.begin() + index);
        cout << "Nota removida com sucesso\n";
        return true;
    }

    friend ostream& operator<<(ostream&, const User&);
};
ostream& operator<<(ostream& out, const User& user) {
    out << user.username << "\n";
    for (auto& note : user.notes) {
        out << *note;
    }
    return out;
}

#include <map>
template <typename A> using mapptr = map<string, shared_ptr<A>>;

class Login {
    mapptr<User> users;
    User * currentUser;
public:
    Login(mapptr<User> users) : users(users)
    {
    }

    
};

class Sys {
    mapptr<User> users;
    Login mainLogin;
public:

};


int main() {
    
}