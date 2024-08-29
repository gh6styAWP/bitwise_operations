#include <iostream>
#include <string>
using namespace std;

// функция для перевода short int в двоичный вид
string shortToBit(short int number) {
    if (number == 0) return "0"; // особый случай для 0

    string bin = "";
    bool isNegative = (number < 0);

    if (isNegative)
        number = -number; // преобразуем в положительное число для обработки

    while (number > 0) {
        bin = (number % 2 == 0 ? "0" : "1") + bin;
        number /= 2;
    }

    // если число было отрицательным, возвращаем его в дополнительном коде
    if (isNegative) {
        for (char& c : bin)
            c = (c == '0') ? '1' : '0';

        // добавляем 1
        bool carry = true;
        for (int i = bin.length() - 1; i >= 0 && carry; i--) {
            if (bin[i] == '0') {
                bin[i] = '1';
                carry = false;
            }
            else {
                bin[i] = '0';
            }
        }
        if (carry) {
            bin = "1" + bin;
        }
    }
    return bin;
}
// Функция для установки бита
short int setBit(short int number, int bitPosition) {
    return number | (1 << bitPosition);
}
// Функция для сброса бита
short int resetBit(short int number, int bitPosition) {
    return number & ~(1 << bitPosition);
}
// Функция для изменения бита
short int changeBit(short int number, int bitPosition) {
    return number ^ (1 << bitPosition);
}
// Функция для опроса бита
short int surveyBit(short int number, int bitPosition) {
    return (number >> bitPosition) & 1;
}

int main() {
    setlocale(LC_ALL, "Ru");
    short int x;
    int choice, bitPosition;

    cout << "Введите число типа short: ";

    // Проверка корректности введенного значения
    while (!(cin >> x)) {
        cout << "Некорректный ввод. \nПожалуйста, введите целое число типа short: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string binary = shortToBit(x);
    cout << "Двоичный вид числа: " << binary << endl;

    cout << "\nЧто будем делать с числом?";
    cout << "\n1 - Установить бит, 2 - Сбросить бит, 3 - Изменить бит, 4 - Опросить бит\n";
    cout << "Ваш выбор: ";
    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cout << "Некорректный выбор. Пожалуйста, выберите действие от 1 до 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введите номер бита (0-15): ";
    while (!(cin >> bitPosition) || bitPosition < 0 || bitPosition > 15) {
        cout << "Некорректный ввод. Пожалуйста, введите номер бита от 0 до 15: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (choice) {
    case 1:
        x = setBit(x, bitPosition);
        break;
    case 2:
        x = resetBit(x, bitPosition);
        break;
    case 3:
        x = changeBit(x, bitPosition);
        break;
    case 4:
        cout << "Значение бита: " << surveyBit(x, bitPosition) << endl;
        break;
    }

    // Если действие не было опросом бита, выводим обновленное значение
    if (choice != 4) {
        binary = shortToBit(x);
        cout << "Обновленное двоичное представление числа: " << binary << endl;
        cout << "Обновленное число в десятичной системе: " << x << endl;
    }

    return 0;
}
