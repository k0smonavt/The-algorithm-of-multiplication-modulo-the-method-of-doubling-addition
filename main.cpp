#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

struct TableRow {
    int step;
    long long a_val;
    long long b_val;
    long long c_val;
};

long long MultiplyMod(long long a, long long b, long long m, vector<TableRow>& table)
{
    table.clear();

    long long result = 0;
    long long currentAdd = ((b % m) + m) % m;
    long long multiplier = ((a % m) + m) % m;

    // Шаг инициализации (i = 0)
    table.push_back({0, multiplier, currentAdd, result});

    int stepCount = 1;
    while (multiplier > 0)
    {
        if ((multiplier & 1) == 1)
        {
            result = (result + currentAdd) % m;
        }

        currentAdd = (currentAdd << 1) % m;
        multiplier >>= 1;

        // Добавляем шаг только если multiplier > 0
        if (multiplier > 0)
        {
            table.push_back({stepCount, multiplier, currentAdd, result});
            stepCount++;
        }
    }

    return result;
}

bool TryReadLong(const string& prompt, long long& value)
{
    value = 0;
    while (true)
    {
        cout << prompt;
        string input;
        getline(cin, input);

        // Проверяем, введена ли пустая строка
        if (input.empty())
        {
            cout << "Ошибка: введена пустая строка." << endl;
            continue;
        }

        // Пытаемся преобразовать строку в число
        try
        {
            size_t pos;
            value = stoll(input, &pos);

            // Проверяем, что вся строка была преобразована
            if (pos == input.length())
            {
                return true;
            }
            else
            {
                cout << "Ошибка: введено не число или оно слишком большое." << endl;
            }
        }
        catch (const exception&)
        {
            cout << "Ошибка: введено не число или оно слишком большое." << endl;
        }
    }
}

bool TryReadLongM(const string& prompt, long long& value)
{
    value = 0;
    while (true)
    {
        cout << prompt;
        string input;
        getline(cin, input);

        // Проверяем, введена ли пустая строка
        if (input.empty())
        {
            cout << "Ошибка: введена пустая строка." << endl;
            continue;
        }

        // Пытаемся преобразовать строку в число
        try
        {
            size_t pos;
            value = stoll(input, &pos);

            // Проверяем, что вся строка была преобразована и число > 0
            if (pos == input.length() && value > 0)
            {
                return true;
            }
            else
            {
                cout << "Ошибка: введено не число или число не больше нуля или оно слишком большое." << endl;
            }
        }
        catch (const exception&)
        {
            cout << "Ошибка: введено не число или число не больше нуля или оно слишком большое." << endl;
        }
    }
}

void PrintTable(const vector<TableRow>& table)
{
    cout << "\n╔════════╦════════════╦════════════╦════════════╗" << endl;
    cout << "║ Шаг    ║     a      ║     b      ║ c          ║" << endl;
    cout << "╠════════╬════════════╬════════════╬════════════╣" << endl;

    for (const auto& row : table)
    {
        cout << "║ " << setw(6) << left << row.step
             << " ║ " << setw(10) << left << row.a_val
             << " ║ " << setw(10) << left << row.b_val
             << " ║ " << setw(10) << left << row.c_val << " ║" << endl;
    }

    cout << "╚════════╩════════════╩════════════╩════════════╝" << endl;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU");

    cout << "=== Алгоритм умножения по модулю методом удвоения-сложения ===" << endl << endl;

    long long a, b, m;

    if (!TryReadLong("Введите число a: ", a))
        return 1;

    if (!TryReadLong("Введите число b: ", b))
        return 1;

    if (!TryReadLongM("Введите модуль m: ", m))
        return 1;

    // Сохраняем исходные значения для вывода результата
    long long originalA = a;
    long long originalB = b;
    // Если a больше b, меняем их местами (чисто визуально для таблицы)
    if (a > b)
    {
        long long temp = a;
        a = b;
        b = temp;
    }

    vector<TableRow> table;
    long long product = MultiplyMod(a, b, m, table);

    cout << "\nВычисление " << originalA << " * " << originalB << " (mod " << m << ")" << endl;
    PrintTable(table);

    cout << "\nРезультат: " << originalA << " * " << originalB << " = " << product << " (mod " << m << ")" << endl;

    return 0;
}