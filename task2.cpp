#include "Task2.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void runTask2() {
    cout << "\n=== ЗАДАНИЕ 2: Замена цифр и форматирование ===\n";

    string filename;
    cout << "Введите имя файла для чтения (например, text.txt): ";
    cin >> filename;

    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "!! Ошибка: Не удалось открыть файл '" << filename << "'.\n";
        cout << "Убедитесь, что файл существует и находится в папке с проектом\n";
        return;
    }

    cout << "\n--- Результат обработки ---\n";

    // Массив слов для замены
    const string digitNames[] = {
            "ноль", "один", "два", "три", "четыре",
            "пять", "шесть", "семь", "восемь", "девять"
    };

    char ch;
    bool isNewSentence = true; // Флаг, чтобы убирать пробелы в начале новых строк

    while (inFile >> noskipws >> ch) {

        // Если встретили цифру
        if (isdigit(ch)) {
            int digit = ch - '0';
            cout << digitNames[digit];
            isNewSentence = false;
        }
            // Если встретили конец предложения (. ! ?)
        else if (ch == '.' || ch == '!' || ch == '?') {
            cout << ch << endl;
            isNewSentence = true;
        }
            // Любой другой символ
        else {
            if (isNewSentence && (ch == ' ' || ch == '\n' || ch == '\t')) {
                continue;
            }
            cout << ch;
            isNewSentence = false;
        }
    }

    inFile.close();
    cout << "\n\n=== Конец выполнения ===\n";
}