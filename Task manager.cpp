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

    string title, description, due_date;
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

    cout << "Enter priority: " << endl;
    cin >> priority;
    cin.ignore();
    cout << endl;

    nodes.push_front(T(title, description, due_date, priority));
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

int main() {

    TaskList<Task> list;

    list.push_front();
    list.push_front();

    list.print_forward();
    list.print_backward();

    return 0;
}