#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>

using namespace std;

class Note {
private:
    string firstName;
    string lastName;
    string phoneNumber;
    int birthday[3];
public:
    Note();
    Note(string fName, string lName, string phone, int day, int month, int year);
    Note(const Note& other);

    ~Note();

    // Сеттеры
    void setFirstName(string fName);
    void setLastName(string lName);
    void setPhoneNumber(string phone);
    void setBirthday(int day, int month, int year);

    // Геттеры
    string getFirstName() const;
    string getLastName() const;
    string getPhoneNumber() const;
    const int* getBirthday() const;

    // Перегрузка операторов ввода и вывода
    friend istream& operator>>(istream& is, Note& note);
    friend ostream& operator<<(ostream& os, const Note& note);

    // Перегрузка оператора присваивания
    Note& operator=(const Note& other);
};

#endif
