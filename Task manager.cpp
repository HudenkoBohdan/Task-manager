/*
Функционал проекта
🔹 Основные возможности :
✅ Добавление новой задачи(заголовок, описание, срок выполнения, приоритет) - Сделанно
✅ Просмотр списка задач(отображение активных, выполненных) - Сделанно !!!(Можно добавить режим скрития активных или выполненых)
✅ Редактирование задачи(изменение параметров) - Сделанно
✅ Удаление задачи - Сделанно
✅ Пометка задачи как выполненной - Сделанно !!!(Можно сделать через отдельную функцию)
✅ Сохранение задач в файле(или базе данных) - Не сделанно !!!
✅ Сортировка задач(по сроку, приоритету) - Сделано по приоритету !!!

🔹 Дополнительные возможности :
✨ Напоминания(например, если срок выполнения истекает) - Надо посмотреть !!!
✨ Категории задач(например, "Работа", "Учёба", "Личное") - Надо сделать!!!
✨ Экспорт задач в JSON / CSV - Можно попробовать реализовать !!!
*/

#include <iostream>
#include "Task manager.h"

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
void TaskList<T>::push_front(string title, string description, string due_date, int priority) {

    string status = "Complited";

    nodes.push_front(T(title, description, due_date, status, priority, id));

    id++;
}

template<class T>
void TaskList<T>::random_task(TaskList<Task>& list)
{
    string title[] = { "Fix bug", "Develop feature", "Write documentation", "Refactor code", "Test application",
        "Review pull request", "Deploy update", "Create design", "Update dependencies", "Implement UI" };

    string description[] = {"Fix critical issue", "Implement a new feature", "Write detailed documentation",
        "Improve code readability", "Test all features", "Review changes made by team",
        "Deploy the latest update", "Design new user interface", "Update all dependencies",
        "Improve UI/UX for better experience"};

    string due_date[] = { "22-03-25", "11-04-25", "04-04-25", "09-04-25", "01-04-25",
        "10-04-25", "28-03-25", "30-03-25", "14-04-25", "02-04-25" };

    //vector<string> titles = {
    //"Fix bug", "Develop feature", "Write documentation", "Refactor code", "Test application",
    //"Review pull request", "Deploy update", "Create design", "Update dependencies", "Implement UI"
    //};

    //vector<string> descriptions = {
    //    "Fix critical issue", "Implement a new feature", "Write detailed documentation",
    //    "Improve code readability", "Test all features", "Review changes made by team",
    //    "Deploy the latest update", "Design new user interface", "Update all dependencies",
    //    "Improve UI/UX for better experience"
    //};

    //vector<string> due_dates = {
    //    "22-03-25", "11-04-25", "04-04-25", "09-04-25", "01-04-25",
    //    "10-04-25", "28-03-25", "30-03-25", "14-04-25", "02-04-25"
    //};


    int priority[] = {3, 5, 5, 3, 3, 4, 2, 4, 1, 5};

    for (int i = 0; i < 10; i++) 
    {
        list.push_front(title[i], description[i], due_date[i], priority[i]);
    }
}

template <class T>
void TaskList<T>::print_forward() {
    for (auto& data : nodes) {
        cout << data << endl;
        cout << "=====================================\n";
    }
}

template <class T>
void TaskList<T>::help() {
    cout << "\n=========== COMMANDS LIST ===========\n"
        << "Add Task       : add\n"
        << "Task List      : print\n"
        << "Delete Task    : del\n"
        << "Sort Task      : sort\n"
        << "Sort by status : sorts\n"
        << "Random Task    : rand\n"
        << "Edit Task      : edit\n"
        << "Clear          : clear\n"
        << "Help           : help\n"
        << "Exit           : exit\n"
        << "=====================================\n\n";
}

template <class T>
void TaskList<T>::request(TaskList<Task>& list) {

    string userChoice = "";

    help();

    while (userChoice != "exit") 
    {
        cin.clear();
        cin >> userChoice;
        cin.ignore();

        transform(userChoice.begin(), userChoice.end(), userChoice.begin(), ::tolower);

        if (userChoice == "add")
        {
            list.push_front();
            userChoice = "";
        }
        else if (userChoice == "print")
            list.print_forward();
        else if (userChoice == "sort")
        {
            list.sort_by_priority();
            list.sort_id();
        }
        else if (userChoice == "sorts")
        {
            list.sort_by_status();
            list.sort_id();
        }
        else if (userChoice == "rand")
            random_task(list);
        else if (userChoice == "edit")
            edit(list);
        else if (userChoice == "clear")
            system("cls");
        else if (userChoice == "help")
            help();
        else if (userChoice == "del")
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
void TaskList<T>::sort_by_status()
{
    nodes.sort([](const Task& a, const Task& b) {
        if (a.status == "Active" && b.status != "Active") 
        {
            return true;
        }
        else if (a.status != "Active" && b.status == "Active") 
        {
            return false;
        }
        else
        {
            return false;
        }
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

template<class T>
void TaskList<T>::edit(TaskList<Task>& list)
{
    int task_id;
    cout << "Enter task id to edit: ";
    cin >> task_id;
    if (task_id > id) 
    {
        cout << "Task with " << task_id << " not found" << endl;
    }
    else
    {
        int selection = 0;
        auto selected_node = nodes.begin();

        for (; selected_node->id != task_id; selected_node++){}

        cout << *selected_node << endl;
        cout << "1 - Change title\n"
             << "2 - Change description\n"
             << "3 - Change due date\n"
             << "4 - Change status\n"
             << "5 - Change priority\n"
             << "6 - Exit\n";

        while (selection != 6) 
        {
            cin >> selection;
            cin.ignore();
            
            if (selection == 1)
            {
                string new_title;
                cout << "Enter new title: ";
                getline(cin, new_title);
                selected_node->title = new_title;
            }

            else if (selection == 2)
            {
                string new_description;
                cout << "Enter new description: ";
                getline(cin, new_description);
                selected_node->description = new_description;
            }

            else if (selection == 3)
            {
                string new_due_date;
                cout << "Enter new due date: ";
                getline(cin, new_due_date);
                selected_node->due_date = new_due_date;
            }

            else if (selection == 4)
            {
                int new_status;
                cout << "Enter new status (1 - Active; 2 - Complited): ";
                cin >> new_status;
                cin.ignore();
                if (new_status == 2)
                {
                    selected_node->status = "Complited";
                }
                else
                {
                    selected_node->status = "Active";
                }
            }

            else if (selection == 5)
            {
                int new_priority;
                cout << "Enter new priority (1 - Hight, 5 - Low): ";
                cin >> new_priority;
                cin.ignore();
                if (new_priority > 5 || new_priority < 1)
                {
                    selected_node->priority = 5;
                }
                else
                {
                    selected_node->priority = new_priority;
                }
            }
        }
    }
}

int main() {

    TaskList<Task> list;

    list.request(list);

    return 0;
}