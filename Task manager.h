#pragma once

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>


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
    int hide_active = 0;
    int hide_complited = 0;

    string getCurrentDate();
    void push_front();
    void push_front(string title, string description, string due_date, int priority);
    void random_task(TaskList<Task>& list);// Для тестов
    void print_forward(int hide_active, int hide_complited);
    void help();
    void del(TaskList<Task>& list);
    void sort_by_priority();
    void sort_by_status();
    void sort_id();
    void sort_by_date(TaskList<Task>& list);
    void edit(TaskList<Task>& list);
    void complite(TaskList<Task>& list);

public:

    void request(TaskList<Task>& list);

};
