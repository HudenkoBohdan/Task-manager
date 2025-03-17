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

    cout << "Status (1 - Complite, 2 - Active): " << endl;
    cin >> status;
    cout << endl;
    if (status == "1")
        status = "Complite";
    else
        status = "Active";

    cout << "Enter priority: " << endl;
    cin >> priority;
    cin.ignore();
    cout << endl;

    nodes.push_front(T(title, description, due_date, status, priority));
}

template <class T>
void TaskList<T>::print_forward() {
    for (auto& data : nodes) {
        cout << data << endl;
        cout << endl;
    }
}

template <class T>
void TaskList<T>::print_backward() {
    for (auto data = nodes.rbegin(); data != nodes.rend(); ++data) {
        cout << *data << endl;
        cout << endl;
    }
}

template <class T>
void TaskList<T>::help() {
    cout << "Commands List:" << endl
        << "Add Task(add)" << endl
        << "Print List(print)" << endl
        << "Help(help)" << endl
        << "Exit(exit)" << endl;

}

template <class T>
void TaskList<T>::request(TaskList<Task>& list) {

    string word = "";

    help();

    while (word != "exit") 
    {
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
        else if (word == "help")
            help();

    }
     
}


int main() {

    TaskList<Task> list;

    list.request(list);

    //list.push_front();
    //list.push_front();

    //list.print_forward();
    //list.print_backward();

    return 0;
}