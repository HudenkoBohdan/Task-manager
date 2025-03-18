#pragma once

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>


using namespace std;

struct Task
{
    string title;
    string description;
    string due_date; //format (dd-mm-yy)
    string status;
    int priority;
    int id;
    Task(string t, string d, string d_d, string s, int p, int i) : title(t), description(d), due_date(d_d), status(s), priority(p), id(i) {}

    friend ostream& operator<<(ostream& os, const Task& task) 
    {
        os << "Tittle: " << task.title << "\n"
            << "Description: " << task.description << "\n"
            << "Due date (dd-mm-yy): " << task.due_date << "\n"
            << "Status: " << task.status << "\n"
            << "Priority: " << task.priority << "\n"
            << "Id: " << task.id;
        return os;

    }

};

template <class T>
class TaskList {
private:
    std::list<T> nodes;
    int id = 0;

public:
    void push_back(T data);
    void push_front();
    void push_front(string title, string description, string due_date, int priority);
    void random_task(TaskList<Task>& list);// Для тестов
    void print_forward();
    void help();
    void request(TaskList<Task>& list);
    void del(TaskList<Task>& list);
    void sort_by_priority();
    //void sort_by_status();
    void sort_id();

};
