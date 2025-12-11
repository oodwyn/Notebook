#include <iostream>
#include "Keeper.h"

void showMenu() {
    std::cout << "\n--- МЕНЮ ЗАПИСНОЙ КНИЖКИ ---\n";
    std::cout << "1. Добавить новую запись\n";
    std::cout << "2. Показать все записи\n";
    std::cout << "3. Удалить запись\n";
    std::cout << "4. Создать копию записи\n";
    std::cout << "5. Сохранить в файл\n";
    std::cout << "6. Загрузить из файла\n";
    // Пункт 7 для поиска добавим позже
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    Keeper notebook;
    int choice;

    while (true) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "!! Ошибка: введите число.\n";
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            continue;
        }

        std::cin.ignore(32767, '\n');

        switch (choice) {
            case 1: notebook.add(); break;
            case 2: notebook.showAll(); break;
            case 3: notebook.remove(); break;
            case 4: notebook.copy(); break;
            case 5: notebook.saveToFile(); break;
            case 6: notebook.loadFromFile(); break;
            case 0:
                std::cout << "Завершение программы...\n";
                return 0;
            default:
                std::cout << "!! Неверный пункт меню.\n";
                break;
        }
    }
}