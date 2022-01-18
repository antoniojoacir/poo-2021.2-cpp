#pragma once

#include <iostream>
#include <map>
#include <memory>
#include "message.hpp"

class INBOX {
    map<int, shared_ptr<MESSAGE>> allMessages;
    map<int, shared_ptr<MESSAGE>> unreads;
public:
    INBOX()
    {
    }

    map<int, shared_ptr<MESSAGE>> getAllMessages() const {
        return allMessages;
    }
    
    map<int, shared_ptr<MESSAGE>> getUnReads() const {
        return unreads;
    }

    shared_ptr<MESSAGE> * getTweet(int id) {
        auto it = allMessages.find(id);
        if (it != allMessages.end()) {
            return &it->second;
        }
        cout << "ERROR: Wrong id number\n";
        return nullptr;
    }

    void receiverNewTweet(const shared_ptr<MESSAGE>& newMessage) {
        if(newMessage != nullptr) {
            unreads.insert(make_pair(newMessage->getId(), newMessage));
            return;
        }
        cout << "ERROR: New tweet is null\n";
    }

    void storage(const shared_ptr<MESSAGE>& message) {
        static int nextID = 0;
        if(message != nullptr) {
            allMessages.insert(make_pair(nextID, message));
            unreads.insert(make_pair(nextID++, message));
            return;
        }
        cout << "ERROR: Message is null\n";
    }

    friend ostream& operator<<(ostream&, const INBOX&);
};