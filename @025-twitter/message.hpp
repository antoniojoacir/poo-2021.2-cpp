#pragma once

#include <iostream>
#include <set>

using namespace std;

class MESSAGE {
    int idNumber;
    string userNameSender;
    string textRecieved;
    set<string> likesRecieved;
public:
    MESSAGE(int number, string name, string txt) : 
    idNumber(number), userNameSender(name), textRecieved(txt)
    {
    }

    int getId() const { return idNumber; }

    void addLike(string name) { likesRecieved.insert(name); }

    friend ostream& operator<<(ostream&, const MESSAGE&);
};
ostream& operator<<(ostream& output, const MESSAGE& message) {
    output << message.idNumber << ":" << message.userNameSender << "\n";
    output << "[" << message.textRecieved << "]";
    if (!message.likesRecieved.empty()) {
        output << " ♥️ ~ ";
        for (auto it = message.likesRecieved.begin(); it != message.likesRecieved.end(); ++it) {
            output << *it << " ";
        }
    }
    return output;
}