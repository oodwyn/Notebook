#include "Keeper.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

Keeper::Keeper() {
    this->capacity = 4;
    this->size = 0;
    this->data = new Note*[this->capacity];
    std::cout << ">> Keeper: Контейнер создан" << std::endl;
}

Keeper::~Keeper() {
    for (int i = 0; i < this->size; ++i) {
        delete this->data[i];
    }
    delete[] this->data;
    std::cout << "<< Keeper: Контейнер уничтожен, память очищена" << std::endl;
}

// Публичные методы

void Keeper::showAll() {
    if (this->size == 0) {
        std::cout << "\nЗаписная книжка пуста" << std::endl;
        return;
    }

    std::cout << "\n========== ЗАПИСНАЯ КНИЖКА ==========" << std::endl;
    for (int i = 0; i < this->size; ++i) {
        // Используем наш перегруженный оператор << для Note
        std::cout << "Запись #" << i + 1 << ": " << *(this->data[i]) << std::endl;
    }
    std::cout << "=====================================" << std::endl;
}

void Keeper::add() {
    // Проверяем место и расширяем массив, если надо
    if (this->size >= this->capacity) {
        std::cout << "!! Keeper: Вместимость хранилища недостаточна. Расширяем..." << std::endl;
        int newCapacity = this->capacity * 2;
        Note** newData = new Note*[newCapacity];
        for (int i = 0; i < this->size; ++i) {
            newData[i] = this->data[i];
        }
        delete[] this->data;
        this->data = newData;
        this->capacity = newCapacity;
    }

    // Создаем новый объект Note в динамической памяти
    Note* newNote = new Note();

    // Заполняем его данными с помощью перегруженного >>
    std::cin >> *newNote;

    // Добавляем указатель на новый объект в массив
    this->data[this->size] = newNote;
    this->size++;

    // Сортируем
    this->sort();

    std::cout << ">> Keeper: Новая запись успешно добавлена и отсортирована" << std::endl;
}

// Приватный метод сортировки

void Keeper::sort() {
    for (int i = 1; i < this->size; ++i) {

        Note* current = this->data[i];

        int currentPrefix = 0;
        std::string currentPhone = current->getPhoneNumber();
        if (currentPhone.length() >= 3) {
            try { // Добавляем try-catch на случай, если в номере будут не цифры
                currentPrefix = std::stoi(currentPhone.substr(0, 3));
            } catch (const std::invalid_argument& e) {
                currentPrefix = 0;
            }
        }

        int j = i - 1;

        while (j >= 0) {
            std::string leftPhone = this->data[j]->getPhoneNumber();
            int leftPrefix = 0;
            if (leftPhone.length() >= 3) {
                try {
                    leftPrefix = std::stoi(leftPhone.substr(0, 3));
                } catch (const std::invalid_argument& e) {
                    leftPrefix = 0;
                }
            }

            if (leftPrefix > currentPrefix) {
                this->data[j + 1] = this->data[j];
                j--;
            } else {
                break;
            }
        }

        this->data[j + 1] = current;
    }
}

void Keeper::searchByLastName() {
    if (this->size == 0) { std::cout << "Список пуст" << std::endl; return; }

    std::string searchName;
    std::cout << "Введите фамилию для поиска: ";
    std::cin >> searchName;

    bool found = false;
    for(int i=0; i < this->size; i++) {
        if(this->data[i]->getLastName() == searchName) {
            std::cout << "\nНайдено (Запись #" << i+1 << "):" << std::endl;
            std::cout << *(this->data[i]) << std::endl;
            found = true;
        }
    }
    if(!found) std::cout << "Человек с такой фамилией не найден" << std::endl;
}

// Метод удаления
void Keeper::remove() {
    if (this->size == 0) {
        // Исключение
        throw std::runtime_error("Записная книжка пуста, удалять нечего");
    }

    this->showAll();

    int index;
    std::cout << "Введите номер записи для удаления: ";
    std::cin >> index;

    if(std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(32767, '\n');
        throw std::invalid_argument("Введено не число!");
    }

    index--;

    if (index < 0 || index >= this->size) {
        throw std::out_of_range("Неверный номер записи (выход за пределы массива).");
    }

    delete this->data[index];
    for (int i = index; i < this->size - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    this->size--;
    std::cout << ">> Запись #" << index + 1 << " успешно удалена." << std::endl;
}

// Редактирование
void Keeper::editNote() {
    if (this->size == 0) {
        std::cout << "!! Список пуст, редактировать некого." << std::endl;
        return;
    }

    this->showAll();

    int index;
    std::cout << "Введите номер записи для редактирования: ";
    std::cin >> index;

    // Проверка на ошибки ввода
    if (std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(32767, '\n');
        std::cout << "!! Ошибка ввода числа." << std::endl;
        return;
    }

    index--;

    if (index < 0 || index >= this->size) {
        std::cout << "!! Неверный номер записи." << std::endl;
        return;
    }

    Note* currentNote = this->data[index];
    int fieldChoice;

    do {
        std::cout << "\n--- Редактирование записи #" << index + 1 << " ---" << std::endl;
        std::cout << "Текущие данные: " << *currentNote << std::endl;
        std::cout << "Выберите поле для изменения:" << std::endl;
        std::cout << "1. Фамилия" << std::endl;
        std::cout << "2. Имя" << std::endl;
        std::cout << "3. Номер телефона" << std::endl;
        std::cout << "4. Дата рождения" << std::endl;
        std::cout << "0. Завершить редактирование" << std::endl;
        std::cout << "Ваш выбор: ";

        std::cin >> fieldChoice;
        std::cin.ignore(32767, '\n'); // Очистка буфера

        switch (fieldChoice) {
            case 1: {
                std::string newLastName;
                std::cout << "Введите новую фамилию: ";
                std::cin >> newLastName;
                currentNote->setLastName(newLastName);
                std::cout << ">> Фамилия изменена" << std::endl;
                break;
            }
            case 2: {
                std::string newFirstName;
                std::cout << "Введите новое имя: ";
                std::cin >> newFirstName;
                currentNote->setFirstName(newFirstName);
                std::cout << ">> Имя изменено" << std::endl;
                break;
            }
            case 3: {
                std::string newPhone;
                std::cout << "Введите новый телефон: ";
                std::cin >> newPhone;
                currentNote->setPhoneNumber(newPhone);
                std::cout << ">> Телефон изменен" << std::endl;
                break;
            }
            case 4: {
                int d, m, y;
                std::cout << "Введите новую дату рождения (Д М Г через пробел): ";
                std::cin >> d >> m >> y;
                currentNote->setBirthday(d, m, y);
                std::cout << ">> Дата изменена" << std::endl;
                break;
            }
            case 0:
                std::cout << "Завершение редактирования" << std::endl;
                break;
            default:
                std::cout << "!! Неверный выбор" << std::endl;
        }

    } while (fieldChoice != 0);

    // Сортировка
    this->sort();
    std::cout << ">> Список пересортирован" << std::endl;
}

// Метод копирования
void Keeper::copy() {
    if (this->size == 0) {
        throw std::runtime_error("Список пуст, копировать нечего");
    }

    // Расширение памяти
    if (this->size >= this->capacity) {
        int newCapacity = this->capacity * 2;
        Note** newData = new Note*[newCapacity];
        for (int j = 0; j < this->size; ++j) newData[j] = this->data[j];
        delete[] this->data;
        this->data = newData;
        this->capacity = newCapacity;
    }

    this->showAll();
    int index;
    std::cout << "Введите номер записи для копирования: ";
    std::cin >> index;

    if(std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(32767, '\n');
        throw std::invalid_argument("Введено не число!");
    }

    index--;

    if (index < 0 || index >= this->size) {
        throw std::out_of_range("Неверный номер записи");
    }

    Note* newCopy = new Note(*(this->data[index])); // Конструктор копирования
    this->data[this->size] = newCopy;
    this->size++;
    this->sort();

    std::cout << ">> Копия создана" << std::endl;
}

// Сохранение в файл
void Keeper::saveToFile() {
    std::string filename;
    std::cout << "Введите имя файла для сохранения (например, notebook.txt): ";
    std::getline(std::cin, filename);
    if (filename.empty()) filename = "notebook_data.txt";

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "!! ОШИБКА: Не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }
    // Проходим по всем записям
    for (int i = 0; i < this->size; ++i) {
        outFile << "--- Note ---" << std::endl;
        outFile << "FirstName: " << this->data[i]->getFirstName() << std::endl;
        outFile << "LastName: " << this->data[i]->getLastName() << std::endl;
        outFile << "Phone: " << this->data[i]->getPhoneNumber() << std::endl;

        const int* bd = this->data[i]->getBirthday();
        outFile << "Birthday: " << bd[0] << "." << bd[1] << "." << bd[2] << std::endl;

        outFile << "--- End ---" << std::endl;
    }

    outFile.close();
    std::cout << ">> Данные успешно сохранены в " << filename << std::endl;
}

// Загружаем из файла
void Keeper::loadFromFile() {
    std::string filename;
    std::cout << "Введите имя файла для загрузки: ";
    std::getline(std::cin, filename);

    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cout << "!! ОШИБКА: Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    // Спрашиваем, очистить ли текущий список
    if (this->size > 0) {
        int choice;
        std::cout << "\n!! В памяти уже есть данные.\n1. Добавить к ним\n2. Заменить (удалить старые)\nВаш выбор: ";
        std::cin >> choice;
        std::cin.ignore(32767, '\n');

        if (choice == 2) {
            for (int i = 0; i < this->size; ++i) delete this->data[i];
            this->size = 0;
            std::cout << ">> Старые данные очищены" << std::endl;
        }
    }

    std::string line;

    // Временные переменные
    std::string tempFName, tempLName, tempPhone;
    int tempD = 0, tempM = 0, tempY = 0;

    bool insideNote = false;

    while (std::getline(inFile, line)) {
        // Убираем возможный символ возврата каретки \r
        if (!line.empty() && line.back() == '\r') line.pop_back();

        if (line == "--- Note ---") {
            insideNote = true;
            // Сбрасываем переменные
            tempFName = ""; tempLName = ""; tempPhone = "";
            tempD = 0; tempM = 0; tempY = 0;
            continue;
        }

        if (line == "--- End ---") {
            if (insideNote) {
                if (this->size >= this->capacity) {
                    int newCapacity = this->capacity * 2;
                    Note** newData = new Note*[newCapacity];
                    for (int j = 0; j < this->size; ++j) newData[j] = this->data[j];
                    delete[] this->data;
                    this->data = newData;
                    this->capacity = newCapacity;
                }

                Note* newNote = new Note(tempFName, tempLName, tempPhone, tempD, tempM, tempY);

                this->data[this->size] = newNote;
                this->size++;

                insideNote = false;
            }
            continue;
        }

        if (insideNote) {
            // Ищем ключевые слова и вырезаем значения
            // substr(N) берет строку начиная с N-го символа
            if (line.find("FirstName: ") == 0) {
                tempFName = line.substr(11);
            }
            else if (line.find("LastName: ") == 0) {
                tempLName = line.substr(10);
            }
            else if (line.find("Phone: ") == 0) {
                tempPhone = line.substr(7);
            }
            else if (line.find("Birthday: ") == 0) {
                std::string dateStr = line.substr(10);
                sscanf(dateStr.c_str(), "%d.%d.%d", &tempD, &tempM, &tempY);
            }
        }
    }

    inFile.close();
    // Сортируем после загрузки
    this->sort();

    std::cout << ">> Данные загружены. Всего записей: " << this->size << std::endl;
}

// Для запуска задания
void Keeper::run() {
    int choice;
    do {
        std::cout << "\n--- МЕНЮ ЗАПИСНОЙ КНИЖКИ (Keeper) ---\n";
        std::cout << "1. Добавить новую запись\n";
        std::cout << "2. Показать все записи\n";
        std::cout << "3. Удалить запись\n";
        std::cout << "4. Создать копию записи\n";
        std::cout << "5. Сохранить в файл\n";
        std::cout << "6. Загрузить из файла\n";
        std::cout << "7. Поиск по фамилии\n";
        std::cout << "0. Назад в главное меню\n";
        std::cout << "Ваш выбор: ";

        std::cin >> choice;
        if(std::cin.fail()) {
            std::cin.clear(); std::cin.ignore(32767, '\n');
            choice = -1;
        } else {
            std::cin.ignore(32767, '\n'); // Очистка буфера
        }

        switch (choice) {
            case 1: add(); break;
            case 2: showAll(); break;
            case 3: remove(); break;
            case 4: copy(); break;
            case 5: saveToFile(); break;
            case 6: loadFromFile(); break;
            case 7: searchByLastName(); break;
            case 0: break;
            default: std::cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}