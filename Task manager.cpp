/*
Функционал проекта
🔹 Основные возможности :
✅ Добавление новой задачи(заголовок, описание, срок выполнения, приоритет) - Сделанно
✅ Просмотр списка задач(отображение активных, выполненных) - Сделанно (Можно добавить режим скрития активных или выполненых) - Добавил
✅ Редактирование задачи(изменение параметров) - Сделанно
✅ Удаление задачи - Сделанно
✅ Пометка задачи как выполненной - Сделанно (Можно сделать через отдельную функцию) - Сделанно
✅ Сохранение задач в файле(или базе данных) - Сделанно
✅ Сортировка задач(по сроку, приоритету) - Сделано

🔹 Дополнительные возможности :
✨ Напоминания(например, если срок выполнения истекает) - Надо посмотреть !!!
✨ Категории задач(например, "Работа", "Учёба", "Личное") - Надо сделать!!!
✨ Экспорт задач в JSON / CSV - Сделанно с CSV
*/

#include <iostream>
#include "Task manager.h"

template<class T>
string TaskList<T>::getCurrentDate()
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    tm localTime{};
    localtime_s(&localTime, &now_time);

    ostringstream dateStream;
    dateStream << setw(2) << setfill('0') << localTime.tm_mday << "-"
        << setw(2) << setfill('0') << (localTime.tm_mon + 1) << "-"
        << setw(2) << setfill('0') << (localTime.tm_year % 100);

    return dateStream.str();
}

template<class T>
bool TaskList<T>::date_verification(string date)
{

    std::regex datePattern(R"(^(\d{2})-(\d{2})-(\d{2})$)");
    std::smatch match;

    if (!std::regex_match(date, match, datePattern)) {
        return false;
    }

    char dash = '-';
    int day, mounth, year;

    istringstream dateStream(date);
    dateStream >> day >> dash >> mounth >> dash >> year;

    if (mounth < 1 || mounth > 12) return false;
    
    int daysInMouth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (year % 4 == 0) 
    {
        daysInMouth[1] = 29;
    }

    if (day < 1 || day > daysInMouth[mounth - 1]) return false;

    return true;
}

template <class T>
void TaskList<T>::push_front() {

    string title = "", description = "", due_date = "01-01-01", status = "";
    int priority = 0;

    cout << "Enter title: " << endl;
    getline(cin, title);
    cout << endl;

    cout << "Enter description: " << endl;
    getline(cin, description);
    cout << endl;

    while (true) 
    {
        cout << "Enter due date (dd-mm-yy): " << endl;
        getline(cin, due_date);
        cout << endl;
        if (date_verification(due_date))
        {
            break;
        }
        else
        {
            cout << "Invalid due date\n";
        }
    }


    status = "Active";

    cout << "Enter priority (1 - Hight, 5 - Low): " << endl;
    cin >> priority;
    cin.clear();
    cin.ignore();
    cout << endl;

    if (priority > 5 || priority < 1)
    {
        priority = 5;
    }

    nodes.push_front(T(title, description, due_date, getCurrentDate(), status, priority, id));

    id++;
}

template <class T>
void TaskList<T>::push_front(string title, string description, string due_date, int priority) {

    string status = "Complited";

    nodes.push_front(T(title, description, due_date, getCurrentDate(), status, priority, id));

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

    int priority[] = {3, 5, 5, 3, 3, 4, 2, 4, 1, 5};

    for (int i = 0; i < 10; i++) 
    {
        list.push_front(title[i], description[i], due_date[i], priority[i]);
    }
}

template <class T>
void TaskList<T>::print_forward(int hide_active, int hide_complited) {
    if (hide_active == 0 && hide_complited == 0)
    {
        for (auto& data : nodes) 
        {
            cout << data << endl;
            cout << "=====================================\n";
        }
    }

    else if (hide_active == 0 && hide_complited == 1)
    {
        for (auto data = nodes.begin(); data != nodes.end(); data++)
        {
            if (data->status == "Active")
            {
                cout << *data << endl;
                cout << "=====================================\n";
            }

        }
    }
    else if (hide_active == 1 && hide_complited == 0)
    {
        for (auto data = nodes.begin(); data != nodes.end(); data++)
        {
            if (data->status == "Complited")
            {
                cout << *data << endl;
                cout << "=====================================\n";
            }

        }
    }

}

template <class T>
void TaskList<T>::help() {
    cout << "\n=========== COMMANDS LIST ===========\n"
        << "Add Task           : add\n"
        << "Task List          : print\n"
        << "Delete Task        : del\n"
        << "Complite Task      : comp\n"
        << "Sort by priority   : sp\n"
        << "Sort by status     : ss\n"
        << "Sort by due date   : sd\n"
        << "Reverse List       : rt\n"
        << "Random Task        : rd\n"
        << "Edit Task          : edit\n"
        << "Hide Active        : ha\n"
        << "Hide Complited     : hc\n"
        << "Save to File       : sf\n"
        << "Load from File     : lf\n"
        << "Clear              : clear\n"
        << "Help               : help\n"
        << "Exit               : exit\n"
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
            continue;
        }
        else if (userChoice == "print") 
        {
            list.print_forward(hide_active, hide_complited);
            continue;
        }
        else if (userChoice == "del") 
        {
            del(list);
            list.sort_id();
            continue;
        }
        else if (userChoice == "comp")
        {
            complite(list);
            continue;
        }
        else if (userChoice == "sp")
        {
            list.sort_by_priority();
            list.sort_id();
            continue;
        }
        else if (userChoice == "ss")
        {
            list.sort_by_status();
            list.sort_id();
            continue;
        }
        else if (userChoice == "sd")
        {
            sort_by_date(list);
            list.sort_id();
            continue;
        }
        else if (userChoice == "rv")
        {
            nodes.reverse();
        }
        else if (userChoice == "rd")
        {
            random_task(list);
            continue;
        }
        else if (userChoice == "edit") 
        {
            edit(list);
            continue;
        }
        else if (userChoice == "ha")
        {
            if (hide_active == 0)
            {
                cout << "Active tasks are now hidden" << endl;
                hide_active = 1;
            }
            else
            {
                cout << "Active tasks are now displayed" << endl;
                hide_active = 0;
            }
            continue;
        }
        else if (userChoice == "hc")
        {
            if (hide_complited == 0)
            {
                cout << "Complited tasks are now hidden" << endl;
                hide_complited = 1;
            }
            else
            {
                cout << "Complited tasks are now displayed" << endl;
                hide_complited = 0;
            }
            continue;
        }
        else if (userChoice == "sf")
        {
            save_to_csv(list);
            continue;
        } 
        else if (userChoice == "lf")
        {
            load_from_csv(list);
            continue;
        }
        else if (userChoice == "clear") 
        {
            system("cls");
            continue;
        }
        else if (userChoice == "help") 
        {
            help();
            continue;
        }
        else
        {
            cout << "Invalid command, type 'help' for a list of commands\n";
        }


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
void TaskList<T>::sort_by_date(TaskList<Task>& list)
{
    nodes.sort([](const Task& a, const Task& b) {
        return a.parseData() < b.parseData();
        });
}

template<class T>
void TaskList<T>::edit(TaskList<Task>& list)
{
    int task_id;
    cout << "Enter the task id to edit: ";
    cin >> task_id;
    if (task_id > id) 
    {
        cout << "Task with " << task_id << " not found" << endl;
    }
    else
    {
        string selection = "0";
        auto selected_node = nodes.begin();

        for (; selected_node->id != task_id; selected_node++){}

        cout << *selected_node << endl;
        edit_commands_list();

        while (selection != "6")
        {
            cin >> selection;
            cin.ignore();
            
            if (selection == "1")
            {
                string new_title;
                cout << "Enter new title: ";
                getline(cin, new_title);
                selected_node->title = new_title;
            }

            else if (selection == "2")
            {
                string new_description;
                cout << "Enter new description: ";
                getline(cin, new_description);
                selected_node->description = new_description;
            }

            else if (selection == "3")
            {
                string new_due_date;
                cout << "Enter new due date: ";
                getline(cin, new_due_date);
                selected_node->due_date = new_due_date;
            }

            else if (selection == "4")
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

            else if (selection == "5")
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
            else if (selection == "help") 
            {
                edit_commands_list();
            }
            else if (selection != "6")
            {
                cout << "Invalid command, type 'help' for a list of commands\n";
            }
        }
    }
}

template<class T>
void TaskList<T>::edit_commands_list()
{
    cout << "1 - Change title\n"
        << "2 - Change description\n"
        << "3 - Change due date\n"
        << "4 - Change status\n"
        << "5 - Change priority\n"
        << "6 - Exit\n";
}

template<class T>
void TaskList<T>::complite(TaskList<Task>& list)
{
    int task_id;
    cout << "Enter the task id to complite: ";
    cin >> task_id;
    if (task_id > id)
    {
        cout << "Task with " << task_id << " not found" << endl;
    }
    else
    {
        auto selected_node = nodes.begin();

        for (; selected_node->id != task_id; selected_node++) {}

        selected_node->status = "Complited";
    }
}

template<class T>
void TaskList<T>::save_to_csv(TaskList<Task>& list)
{  
    string filename = "file.csv";

    while (true) {
        cout << "Enter file name(latters and numbers): ";
        getline(cin, filename);

        std::regex filenamePattern("^[a-zA-Z0-9_]+$");
        std::smatch match;

        if (!std::regex_match(filename, match, filenamePattern)) {
            cout << "Invalid file name\n";
        }
        else
        {
            break;
        }
    }
    filename += ".csv";

    ofstream file(filename);

    if (!file) 
    {
        cout << "Error: Unable to open file for writing!\n";
        return;
    }

    file << "ID,Title,Description,Due date,Add date,Status,Priority\n";

    for (const auto& task : nodes)
    {
        file << task.toCSV() << endl;
    }

    file.close();
    cout << "Tasks saved to " << filename << "\n";

}

template<class T>
void TaskList<T>::load_from_csv(TaskList<Task>& list)
{
    string filename = "file.csv";

    while (true) {
        cout << "Enter file name(latters and numbers): ";
        getline(cin, filename);

        std::regex filenamePattern("^[a-zA-Z0-9_]+$");
        std::smatch match;

        if (!std::regex_match(filename, match, filenamePattern)) {
            cout << "Invalid file name\n";
        }
        else
        {
            break;
        }
    }

    filename += ".csv";

    ifstream file(filename);

    if (!file)
    {
        cout << "Error: Unable to open file for writing!\n";
        return;
    }

    string line;

    getline(file, line);

    while (getline(file,line)) 
    {
        stringstream ss(line);
        
        string title, description, due_date, add_date, status, priority, id;

        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, description, ',');
        getline(ss, due_date, ',');
        getline(ss, add_date, ',');
        getline(ss, status, ',');
        getline(ss, priority, ',');

        nodes.push_front(T(title, description, due_date, add_date, status, stoi(priority), stoi(id)));
        list.id++;
    }

    file.close();
    cout << "Tasks loaded from " << filename << "\n";

}

int main() {

    TaskList<Task> list;

    list.request(list);

    return 0;
}