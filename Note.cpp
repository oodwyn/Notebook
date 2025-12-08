#include "Note.h"

// Конструктор без параметров
Note::Note() {
    cout << "Вызван конструктор без параметров для объекта Note" << endl;
    firstName="";
    lastName="";
    phoneNumber="";
    birthday[0] = 0;
    birthday[1] = 0;
    birthday[2] = 0;
}

// Конструктор с параметрами
Note::Note(string fName, string lName, string phone, int day, int month, int year) {
    cout << "Вызван конструктор с параметрами для объекта Node" << endl;
    firstName = fName;
    lastName = lName;
    phoneNumber = phone;
    birthday[0] = day;
    birthday[1] = month;
    birthday[2] = year;
}

// Конструктор копирования
Note::Note(const Note& other) {
    cout << "Вызван конструктор копирования для объекта Note" << endl;
    firstName = other.firstName;
    lastName = other.lastName;
    phoneNumber = other.phoneNumber;
    birthday[0] = other.birthday[0];
    birthday[1] = other.birthday[1];
    birthday[2] = other.birthday[2];
}

// Деструктор
Note::~Note() {
    cout << "Вызван деструктор для объекта Note: " << lastName << endl;
}

// Сеттеры
void Note::setFirstName(std::string fName) {
    firstName = fName;
}

void Note::setLastName(string lName) {
    lastName = lName;
}

void Note::setPhoneNumber(string phone) {
    phoneNumber = phone;
}

void Note::setBirthday(int day, int month, int year) {
    birthday[0] = day;
    birthday[1] = month;
    birthday[2] = year;
}

// Геттеры
string Note::getFirstName() const { return firstName; }
string Note::getLastName() const { return lastName; }
string Note::getPhoneNumber() const { return phoneNumber; }
const int* Note::getBirthday() const { return birthday; }

// Оператор присваивания
Note& Note::operator=(const Note& other) {
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
ostream& operator<<(ostream& os, const Note& note) {
    os << "Фамилия: " << note.lastName
       << ", Имя: " << note.firstName
       << ", Телефон: " << note.phoneNumber
       << ", ДР: " << note.birthday[0] << "." << note.birthday[1] << "." << note.birthday[2];
    return os;
}

// Перегрузка ввода (cin >> note)
istream& operator>>(istream& is, Note& note) {
    cout << "Введите Фамилию: ";
    is >> note.lastName;
    cout << "Введите Имя: ";
    is >> note.firstName;
    cout << "Введите Номер телефона: ";
    is >> note.phoneNumber;
    cout << "Введите День рождения (День, Месяц, Год через пробел): ";
    is >> note.birthday[0] >> note.birthday[1] >> note.birthday[2];
    return is;
}