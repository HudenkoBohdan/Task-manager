#pragma once

#include <iostream>
#include <list>
#include <string>

using namespace std;

//struct Task
//{
//    string title;
//    string description;
//    string due_date; //format (dd-mm-yy)
//    int priority;
//    Task(string t, string d, string d_d, int p) : title(t), description(d), due_date(d_d), priority(p) {}
//
//};

template <class T>
class TaskList {
private:
    std::list<T> nodes;


public:
    void push_back(T data);
    void push_front(T data);
    void print_forward();
    void print_backward();

};

int main() {

    TaskList<string> list;
    string a;

    getline(cin, a);
    list.push_front(a);

    list.print_forward();
    list.print_backward();

    return 0;
}