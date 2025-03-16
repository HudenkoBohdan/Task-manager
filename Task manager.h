#pragma once

#include <iostream>
#include <list>
#include <string>

using namespace std;

struct Task
{
    string title;
    string description;
    string due_date; //format (dd-mm-yy)
    int priority;
    Task(string t, string d, string d_d, int p) : title(t), description(d), due_date(d_d), priority(p) {}

    friend ostream& operator<<(ostream& os, const Task& task) 
    {
        os << "Tittle: " << task.title << "\n"
            << "Description: " << task.description << "\n"
            << "Due date (dd-mm-yy): " << task.due_date << "\n"
            << "Priority: " << task.priority;
        return os;

    }

};

template <class T>
class TaskList {
private:
    std::list<T> nodes;


public:
    void push_back(T data);
    void push_front();
    void print_forward();
    void print_backward();

};
