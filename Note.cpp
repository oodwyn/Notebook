#include "Note.h"

// Конструктор без параметров
Note::Note() {
    std::cout << "Вызван конструктор без параметров для объекта Note" << std::endl;
    firstName="";
    lastName="";
    phoneNumber="";
    birthday[0] = 0;
    birthday[1] = 0;
    birthday[2] = 0;
}

// Конструктор с параметрами
Note::Note(std::string fName, std::string lName, std::string phone, int day, int month, int year) {
    std::cout << "Вызван конструктор с параметрами для объекта Note" << std::endl;
    firstName = fName;
    lastName = lName;
    phoneNumber = phone;
    birthday[0] = day;
    birthday[1] = month;
    birthday[2] = year;
}

// Конструктор копирования
Note::Note(const Note& other) {
    std::cout << "Вызван конструктор копирования для объекта Note" << std::endl;
    firstName = other.firstName;
    lastName = other.lastName;
    phoneNumber = other.phoneNumber;
    birthday[0] = other.birthday[0];
    birthday[1] = other.birthday[1];
    birthday[2] = other.birthday[2];
}

// Деструктор
Note::~Note() {
    std::cout << "Вызван деструктор для объекта Note: " << lastName << std::endl;
}

// Сеттеры
void Note::setFirstName(std::string fName) {
    firstName = fName;
}

void Note::setLastName(std::string lName) {
    lastName = lName;
}

void Note::setPhoneNumber(std::string phone) {
    phoneNumber = phone;
}

void Note::setBirthday(int day, int month, int year) {
    birthday[0] = day;
    birthday[1] = month;
    birthday[2] = year;
}

// Геттеры
std::string Note::getFirstName() const { return firstName; }
std::string Note::getLastName() const { return lastName; }
std::string Note::getPhoneNumber() const { return phoneNumber; }
const int* Note::getBirthday() const { return birthday; }

// Оператор присваивания
Note& Note::operator=(const Note& other) {
    std::cout << "Вызван оператор присваивания для Note" << std::endl;
    if (this != &other) { // Защита от самоприсваивания
        firstName = other.firstName;
        lastName = other.lastName;
        phoneNumber = other.phoneNumber;
        birthday[0] = other.birthday[0];
        birthday[1] = other.birthday[1];
        birthday[2] = other.birthday[2];
    }
    return *this;
}

// Перегрузка вывода (cout << note)
std::ostream& operator<<(std::ostream& os, const Note& note) {
    os << "Фамилия: " << note.lastName
       << ", Имя: " << note.firstName
       << ", Телефон: " << note.phoneNumber
       << ", ДР: " << note.birthday[0] << "." << note.birthday[1] << "." << note.birthday[2];
    return os;
}

// Перегрузка ввода (cin >> note)
std::istream& operator>>(std::istream& is, Note& note) {
    std::cout << "Введите Фамилию: ";
    is >> note.lastName;
    std::cout << "Введите Имя: ";
    is >> note.firstName;
    std::cout << "Введите Номер телефона: ";
    is >> note.phoneNumber;
    std::cout << "Введите День рождения (День, Месяц, Год через пробел): ";
    is >> note.birthday[0] >> note.birthday[1] >> note.birthday[2];
    is.ignore(32767, '\n');

    return is;
}