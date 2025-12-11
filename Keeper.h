#ifndef LAB2_NOTEBOOK_KEEPER_H
#define LAB2_NOTEBOOK_KEEPER_H
#pragma once
#include "Note.h"

class Keeper {
private:
    Note** data;
    int size;
    int capacity;
    // Метод для сортировки
    void sort();

public:
    Keeper();
    ~Keeper();

    void add();
    void showAll();
    void remove();
    void searchByLastName();

    void saveToFile();
    void loadFromFile();
    void copy();
};
#endif
