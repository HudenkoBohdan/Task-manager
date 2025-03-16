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

#include "Task manager.h"

template <class T>
void TaskList<T>::push_back(T data) {
    nodes.push_back(data);
}

template <class T>
void TaskList<T>::push_front(T data) {
    nodes.push_front(data);
}

template <class T>
void TaskList<T>::push_back(T data) {
    nodes.push_back(data);
}

template <class T>
void TaskList<T>::print_forward() {
    for (auto data& : nodes) {
        cout << data << endl;
    }
}