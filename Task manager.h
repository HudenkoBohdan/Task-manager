#pragma once

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sstream>
#include <regex>
#include <tuple>
#include <fstream>


using namespace std;

struct Task
{
    string title;
    string description;
    string due_date; //format (dd-mm-yy)
    string add_date;
    string status;
    int priority;
    int id;
    Task(string t, string d, string d_d, string a_d, string s, int p, int i) : title(t), description(d), due_date(d_d), add_date(a_d), status(s), priority(p), id(i) {}

    tuple<int, int, int> parseData() const 
    {
        int day, mounth, year;
        char dash = '-';
        stringstream ss(due_date);
        ss >> day >> dash >> mounth >> dash >> year;
        year += (year < 50) ? 2000 : 1900;

        return make_tuple(year, mounth, day);
    }

    string toCSV() const 
    {
        stringstream ss;
        ss << id << "," << title << "," << description << "," << due_date << "," << add_date << "," << status << "," << priority;
        return ss.str();
    }

    friend ostream& operator<<(ostream& os, const Task& task) 
    {
        os << "Title: " << task.title << "\n"
            << "Description: " << task.description << "\n"
            << "Due date (dd-mm-yy): " << task.due_date << "\n"
            << "Add date (dd-mm-yy): " << task.add_date << "\n"
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
    bool date_verification(string date);
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
    void edit_commands_list();
    void complite(TaskList<Task>& list);
    void save_to_csv(TaskList<Task>& list);

public:

    void request(TaskList<Task>& list);

};
