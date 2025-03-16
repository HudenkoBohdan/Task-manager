#pragma once

#include <iostream>
#include <list>
#include <string>

using namespace std;

template <class T>
class TaskList {
private:
    std::list<T> nodes;

public:
    void push_back(T data);
    void push_front(T data);
    void print_forward();

};

int main() {

    TaskList<string> list;
    string a;
    getline(cin, a);

    return 0;
}