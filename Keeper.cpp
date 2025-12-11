#include "Keeper.h"
#include <iostream>
#include <string>
#include <fstream>

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

// Метод удаления
void Keeper::remove() {
    if (this->size == 0) {
        std::cout << "!! Записная книжка пуста, удалять нечего" << std::endl;
        return;
    }
    showAll();
    int index;
    std::cout << "Введите номер записи для удаления: ";
    std::cin >> index;
    std::cin.ignore(32767, '\n');
    index--;

    if (index < 0 || index >= this->size) {
        std::cout << "!! Неверный номер записи" << std::endl;
        return;
    }

    delete this->data[index];

    for (int i = index; i < this->size - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    this->size--;
    std::cout << ">> Запись #" << index + 1 << " успешно удалена." << std::endl;
}

// Метод копирования
void Keeper::copy() {
    if (this->size == 0) {
        std::cout << "!! Список пуст, копировать нечего" << std::endl;
        return;
    }
    if (this->size >= this->capacity) {
        std::cout << "!! Вместимость хранилища недостаточна. Расширяем..." << std::endl;
        int newCapacity = this->capacity * 2;
        Note** newData = new Note*[newCapacity];
        for (int j = 0; j < this->size; ++j) { newData[j] = this->data[j]; }
        delete[] this->data;
        this->data = newData;
        this->capacity = newCapacity;
    }

    showAll();
    int index;
    std::cout << "Введите номер записи, которую нужно скопировать: ";
    std::cin >> index;
    std::cin.ignore(32767, '\n');
    index--;

    if (index < 0 || index >= this->size) {
        std::cout << "!! Неверный номер записи" << std::endl;
        return;
    }

    Note* original = this->data[index];

    // Вызываем конструктор копирования Note
    Note* newCopy = new Note(*original);

    this->data[this->size] = newCopy;
    this->size++;

    // После добавления копии нужно снова отсортировать массив
    this->sort();

    std::cout << ">> Копия успешно создана, добавлена и отсортирована" << std::endl;
}

// Сохранение в файл
void Keeper::saveToFile() {

    std::string filename;
    std::cout << "Введите имя файла для сохранения (например, notebook.txt): ";
    std::getline(std::cin, filename);
    if (filename.empty()) filename = "notebook_data.txt";

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cout << "!! ОШИБКА: Не удалось создать/открыть файл для записи: " << filename << std::endl;
        return;
    }

    // Записываем сначала количество записей
    outFile << this->size << std::endl;

    for (int i = 0; i < this->size; ++i) {
        outFile << this->data[i]->getLastName() << std::endl;
        outFile << this->data[i]->getFirstName() << std::endl;
        outFile << this->data[i]->getPhoneNumber() << std::endl;
        const int* bd = this->data[i]->getBirthday();
        outFile << bd[0] << " " << bd[1] << " " << bd[2] << std::endl;
    }

    outFile.close();
    std::cout << ">> Данные успешно сохранены в файл " << filename << std::endl;
}

void Keeper::loadFromFile() {
#include <fstream>

    std::string filename;
    std::cout << "Введите имя файла для загрузки: ";
    std::getline(std::cin, filename);

    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cout << "!! ОШИБКА: Не удалось открыть файл для чтения: " << filename << std::endl;
        return;
    }

    if (this->size > 0) {
        int choice;
        std::cout << "\n!! В памяти уже есть данные.\n1. Добавить\n2. Заменить\n0. Отмена\nВаш выбор: ";
        std::cin >> choice;
        std::cin.ignore(32767, '\n');

        if (choice == 2) {
            for (int i = 0; i < this->size; ++i) { delete this->data[i]; }
            this->size = 0;
        } else if (choice != 1) {
            std::cout << ">> Загрузка отменена" << std::endl;
            inFile.close();
            return;
        }
    }

    int recordCount;
    inFile >> recordCount;
    if (inFile.fail()) {
        std::cout << ">> Файл пуст или поврежден" << std::endl;
        inFile.close();
        return;
    }
    inFile.ignore();

    for (int i = 0; i < recordCount; ++i) {
        if (this->size >= this->capacity) { // Расширение
            int newCapacity = this->capacity * 2;
            Note** newData = new Note*[newCapacity];
            for (int j = 0; j < this->size; ++j) { newData[j] = this->data[j]; }
            delete[] this->data;
            this->data = newData;
            this->capacity = newCapacity;
        }

        std::string lName, fName, phone;
        int d, m, y;

        std::getline(inFile, lName);
        std::getline(inFile, fName);
        std::getline(inFile, phone);
        inFile >> d >> m >> y;
        inFile.ignore();

        if (inFile.fail()) continue; // Если чтение не удалось, пропускаем запись

        this->data[this->size++] = new Note(lName, fName, phone, d, m, y);
    }

    // После загрузки всех данных ОБЯЗАТЕЛЬНО сортируем весь массив
    this->sort();

    inFile.close();
    std::cout << ">> Данные успешно загружены и отсортированы." << std::endl;
}