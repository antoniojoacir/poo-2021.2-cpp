#include <iostream>
#include <set>
#include <map>
#include <memory>

using namespace std;

class Tweet {
    int id;
    string username;
    string mensage;
    set<string> likes;
public:
    Tweet(int id, string username, string mensage)
    : id(id), username(username), mensage(mensage) {}

    friend ostream& operator<<(ostream&, const Tweet&);
};

class Inbox {
    map<int, shared_ptr<Tweet>> timeline;
    map<int, shared_ptr<Tweet>> myTweets;
public:
    Inbox() {}

    friend ostream& operator<<(ostream&, const Inbox&);
};

class User;
class Controler {
    int nextIdTweet;
    map<string, shared_ptr<User>> users;
    map<int, shared_ptr<Tweet>> tweets;
public:
    Controler() : nextIdTweet(0) {}

};

class User {
    string username;
    Inbox inbox;
    map<string, shared_ptr<User>> followers;
    map<string, shared_ptr<User>> following;
public:
    User(string username) : username(username) {}

    friend ostream& operator<<(ostream&, const User&);
};