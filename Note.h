#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>

class Note {
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    int birthday[3];
public:
    Note();
    Note(std::string fName, std::string lName, std::string phone, int day, int month, int year);
    Note(const Note& other);

    ~Note();

    // Сеттеры
    void setFirstName(const std::string fName);
    void setLastName(const std::string lName);
    void setPhoneNumber(const std::string phone);
    void setBirthday(int day, int month, int year);

    // Геттеры
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhoneNumber() const;
    const int* getBirthday() const;

    // Перегрузка операторов ввода и вывода
    friend std::istream& operator>>(std::istream& is, Note& note);
    friend std::ostream& operator<<(std::ostream& os, const Note& note);

    // Перегрузка оператора присваивания
    Note& operator=(const Note& other);
};

#endif
