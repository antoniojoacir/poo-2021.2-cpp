#include <iostream>
#include "message.hpp"

using namespace std;

int main() {
    MESSAGE message(1, "John", "Hello, world!");
    message.addLike("Alice");
    message.addLike("Bob");
    message.addLike("Charlie");

    cout << message << endl;
}