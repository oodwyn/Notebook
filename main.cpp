#include <limits> // Очистка ввода
#include "Keeper.h"
#include "Task2.h"

using namespace std;

void runKeeperMenu(Keeper& notebook) {
    int subChoice;
    do {
        cout << "\n--- [МЕНЮ ЗАДАНИЯ 1: Блокнот] ---\n";
        cout << "1. Добавить запись\n";
        cout << "2. Показать все записи\n";
        cout << "3. Удалить запись\n";
        cout << "4. Копировать запись\n";
        cout << "5. Сохранить в файл\n";
        cout << "6. Загрузить из файла\n";
        cout << "7. Поиск по фамилии\n";
        cout << "8. Редактировать запись\n";
        cout << "0. Назад в главное меню\n";
        cout << "Ваш выбор: ";

        if (!(cin >> subChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            subChoice = -1;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Убираем лишний энтер
        }

        switch (subChoice) {
            case 1: notebook.add(); break;
            case 2: notebook.showAll(); break;
            case 3: notebook.remove(); break;
            case 4: notebook.copy(); break;
            case 5: notebook.saveToFile(); break;
            case 6: notebook.loadFromFile(); break;
            case 7: notebook.searchByLastName(); break;
            case 8: notebook.editNote(); break;
            case 0: cout << "Возврат в главное меню...\n"; break;
            default: cout << "Неверный пункт\n";
        }
    } while (subChoice != 0);
}

int main() {
    setlocale(LC_ALL, "Russian");
    Keeper notebook;

    int mainChoice;
    do {
        cout << "\n====== ГЛАВНОЕ МЕНЮ ======" << endl;
        cout << "1. Задание 1 (Класс Note)" << endl;
        cout << "2. Задание 2 (Обработка текста)" << endl;
        cout << "0. Выход из программы" << endl;
        cout << "Ваш выбор: ";

        if (!(cin >> mainChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mainChoice = -1;
        }

        switch (mainChoice) {
            case 1:
                runKeeperMenu(notebook);
                break;
            case 2:
                runTask2();
                break;
            case 0:
                cout << "До свидания!\n";
                break;
            default:
                cout << "Такого пункта нет.\n";
        }
    } while (mainChoice != 0);

    return 0;
}