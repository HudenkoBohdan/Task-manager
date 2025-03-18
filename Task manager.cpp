/*
Функционал проекта
🔹 Основные возможности :
✅ Добавление новой задачи(заголовок, описание, срок выполнения, приоритет)
✅ Просмотр списка задач(отображение активных, выполненных)
✅ Редактирование задачи(изменение параметров)
✅ Удаление задачи
✅ Пометка задачи как выполненной
✅ Сохранение задач в файле(или базе данных)
✅ Сортировка задач(по сроку, приоритету)

🔹 Дополнительные возможности :
✨ Напоминания(например, если срок выполнения истекает)
✨ Категории задач(например, "Работа", "Учёба", "Личное")
✨ Экспорт задач в JSON / CSV
✨ Графический интерфейс(например, на Qt или SFML)
*/

#include <iostream>
#include "Task manager.h"

template <class T>
void TaskList<T>::push_back(T data) {
    nodes.push_back(data);
}

template <class T>
void TaskList<T>::push_front() {

    string title, description, due_date, status;
    int priority;

    cout << "Enter title: " << endl;
    getline(cin, title);
    cout << endl;

    cout << "Enter description: " << endl;
    getline(cin, description);
    cout << endl;

    cout << "Enter due date (dd-mm-yy): " << endl;
    getline(cin, due_date);
    cout << endl;

    //cout << "Status (1 - Complite, 2 - Active): " << endl;
    //cin >> status;
    //cout << endl;
    //if (status == "1")
    //    status = "Complite";
    //else
    //    status = "Active";
    status = "Active";

    cout << "Enter priority: " << endl;
    cin >> priority;
    cin.ignore();
    cout << endl;

    nodes.push_front(T(title, description, due_date, status, priority, id));

    id++;
}

template <class T>
void TaskList<T>::print_forward() {
    for (auto& data : nodes) {
        cout << data << endl;
        cout << endl;
    }
}

template <class T>
void TaskList<T>::help() {
    cout << "\n=========== COMMANDS LIST ===========\n"
        << "Add Task     : add\n"
        << "Task List    : print\n"
        << "Delete Task  : del\n"
        << "Sort Task    : sort\n"
        << "Help         : help\n"
        << "Exit         : exit\n"
        << "=====================================\n\n";
}

template <class T>
void TaskList<T>::request(TaskList<Task>& list) {

    string word = "";

    help();

    while (word != "exit") 
    {
        cin.clear();
        cin >> word;
        cin.ignore();

        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (word == "add")
        {
            list.push_front();
            word = "";
        }
        else if (word == "print")
            list.print_forward();
        else if (word == "sort") 
        {
            list.sort_by_priority();
            list.sort_id();
        }
        else if (word == "help")
            help();
        else if (word == "del")
            del(list);

    }
     
}

template <class T>
void TaskList<T>::del(TaskList<Task>& list) {
    int task_id;
    cout << "Enter task Id to delete: ";
    cin >> task_id;
    cin.ignore();

    auto it = nodes.begin();
    while(it != nodes.end())
    {
        if (it->id == task_id)
        {
            it = nodes.erase(it);
            cout << "Task with Id " << task_id << " deleted.\n";
            id--;

            auto it = nodes.rbegin();

            while(it->id < task_id) 
            {
                it++;
            }

            while (it != nodes.rend()) 
            {
                it->id--;
                it++;
            }

            return;
        }
        else 
        {
            ++it;
        }
    }
    cout << "Task with ID " << task_id << " not found.\n";

}

template<class T>
void TaskList<T>::sort_by_priority()
{
    nodes.sort([](const Task& a, const Task& b) {
        return a.priority < b.priority;
        });
}

template<class T>
void TaskList<T>::sort_id()
{
    int new_id = id - 1;
    for (auto i = nodes.begin(); i != nodes.end(); i++)
    {
        i->id = new_id;
        new_id--;
    }
}

int main() {

    TaskList<Task> list;

    list.request(list);

    return 0;
}