#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

//функция для перевода short int в двоичный вид
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
//функция для установки бита
short int setBit(short int number, int bitPosition) {
    return number | (1 << bitPosition);
}
//функция для сброса бита
short int resetBit(short int number, int bitPosition) {
    return number & ~(1 << bitPosition);
}
//функция для изменения бита
short int changeBit(short int number, int bitPosition) {
    return number ^ (1 << bitPosition);
}
//функция для опроса бита
short int surveyBit(short int number, int bitPosition) {
    return (number >> bitPosition) & 1;
}
//функция для перевода числа типа long long в двоичный вид
string longLongToBit(long long number) {
    return bitset<64>(number).to_string();
}
//функция для получения обратного кода
string getInverseCode(long long number) {
    if (number >= 0) 
        return longLongToBit(number);   
    else 
        return longLongToBit(~(-number)); // Инверсия всех битов   
}
//функция для получения дополнительного кода
string getComplementaryCode(long long number) {
    if (number >= 0) 
        return longLongToBit(number);
    else 
        return longLongToBit(~(-number) + 1); // Инверсия и добавление 1
}
//функция для вывода dump (внутреннего представления числа в памяти)
void printMemoryDump(long long number) {
    unsigned char* p = (unsigned char*)&number; // Указатель на байты числа
    cout << "Dump (внутреннее представление в памяти):" << endl;
    for (size_t i = 0; i < sizeof(number); ++i) 
        cout << "Byte " << i << ": " << bitset<8>(p[i]) << " " << hex << setw(2) << setfill('0') << static_cast<int>(p[i]) << dec << endl;
}
//функция для вывода dump (внутреннего представления числа в памяти)
template <typename T>
void printMemoryDump(T number) {
    unsigned char* p = (unsigned char*)&number; // Указатель на байты числа
    size_t size = sizeof(number); // Размер типа T в байтах
    cout << "Dump (внутреннее представление в памяти):" << endl;
    for (size_t i = 0; i < size; ++i) {
        cout << "Byte " << i << ": " << bitset<8>(p[i]) << " " << hex << setw(2) << setfill('0') << static_cast<int>(p[i]) << dec << endl;
    }
}
//решето Эратосфена
void sieveOfEratosthenes(int n, const string& filename) {
    vector<int> primes;
    bitset<1000001> isPrime;
    isPrime.set(); //устанавливаем все биты в 1
    isPrime[0] = isPrime[1] = 0; //0 и 1 не являются простыми числами

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = 0; //отмечаем все кратные p как составные
            }
        }
    }

    for (int p = 2; p <= n; p++) {
        if (isPrime[p]) {
            primes.push_back(p);
        }
    }

    //запись в файл
    ofstream outFile(filename);
    if (outFile.is_open()) {
        int count = 0;
        for (int i = 0; i < primes.size(); i++) {
            outFile << primes[i] << " ";
            count++;
            if (count == 100) {
                outFile << endl; //новая строка после каждых 100 чисел
                count = 0;
            }
        }
        outFile.close();
        cout << "Простые числа записаны в файл " << filename << endl;
    }
    else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    short int x;
    long long int y;
    int choice, bitPosition;

    cout << "Введите число типа short: ";

    //проверка корректности введенного значения
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

    //если действие не было опросом бита, выводим обновленное значение
    if (choice != 4) {
        binary = shortToBit(x);
        cout << "Обновленное двоичное представление числа: " << binary << endl;
        cout << "Обновленное число в десятичной системе: " << x << endl;
    }

    cout << "\nВведите число типа long long\n";
    cin >> y;

    cout << "Прямой код: " << longLongToBit(y) << endl;
    cout << "Обратный код: " << getInverseCode(y) << endl;
    cout << "Дополнительный код: " << getComplementaryCode(y) << endl;
    printMemoryDump(y);

    float aa;
    double bb;
    long double cc;
    //ввод числа типа float и вывод его dump
    cout << "\nВведите число типа float: ";
    cin >> aa;
    printMemoryDump(aa);

    //ввод числа типа double и вывод его dump
    cout << "\nВведите число типа double: ";
    cin >> bb;
    printMemoryDump(bb);

    //ввод числа типа long double и вывод его dump
    cout << "\nВведите число типа long double: ";
    cin >> cc;
    printMemoryDump(cc);

    cout << "______________________________________________________________________________";
    cout << "\n";
    cout << "\nРешето Эратосфена, дамы и господа!\n";

    int n = 1000000; //диапазон поиска простых чисел
    string filename = "primes.txt";

    sieveOfEratosthenes(n, filename);

    return 0;
    
}
