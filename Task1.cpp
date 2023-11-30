

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <Windows.h>
#include <conio.h>
class Task_Solution {
public:
    Task_Solution() {}
    ~Task_Solution() = default;
    void Start() {
        Start_Tests();
        char exit;
        while (true) {
            std::cout << "Введіть Ваш тест [Наприклад: 1234 THISISTEST]" << std::endl;
            std::string user_test;
            std::getline(std::cin, user_test);
            std::cout << "Результат шифрування базуючись на ваших даних:\t" << Encrypt_String(user_test) << std::endl;
            std::cout << "Нажміть ESC, щоб вийти, або будь-яку іншу клавішу щоб ввести нові данні" << std::endl;
            exit = _getch();
            if (exit == 27) {
                std::cout << "Гарного дня!" << std::endl;
                break;
            }
        }
    }
private:
    std::string Encrypt_String(std::string& str) {
        std::string result;
        std::string keys;
        // Розбиття стрічки на ключі та слова
        Split_String(str, keys);
        std::vector<std::string> encrypted(keys.size());
        // Цикл по стрічці, який по черзі бере диграф та одну літеру
        // та додає їх у масив стрічок у відповідне місце згідню ключа
        for (int i = 0, j = 0; i < str.size();)
        {       
                // Диграф
                if (i + 1 < str.size()) {
                    encrypted[keys[j] - '0' - 1] += str.substr(i, 2);
                    i += 2;
                    j++;
                    if (j == keys.size()) {
                        j = 0; 
                    }
                }
                // Одна літера
                if (i < str.size()) {
                    encrypted[keys[j] - '0' - 1] += str[i];
                    i++;
                    j++;
                    if (j == keys.size()) {
                        j = 0; 
                    }
                }
        }
        // Об'єднаяння тексту у одну стрічку
        for (const std::string& s : encrypted)
        {
            result += s;
        }
        return result;

    }
    void Split_String(std::string& str, std::string& keys) {
        std::istringstream iss(str);
        // Потік задля розбитя стрічки у масив
        std::vector<std::string> tokens;
        while (iss >> str) {
            tokens.push_back(str);
        }
        if (tokens.size() < 2) {
            std::cout << "Невірно введені дані!\n";
            exit(1);
        }
        str.clear();
        for (size_t i = 0; i < tokens.size(); i++)
        {   // Перевірка на ключі
            if (std::isdigit(tokens[i][0])) {
                std::set<char> key(tokens[i].begin(), tokens[i].end());
                if (key.size() != tokens[i].size()) {
                    std::cout << "Ключ повинен містити лише унікальні числа!\n";
                    exit(1);
                }
                keys += tokens[i];
            }
            else {
                // Запис тексту у стрічку
                str += tokens[i];
            }
        }
    }
    void Start_Tests() {
        std::cout << "Запуск тестових данних..." << std::endl;
        for (size_t i = 0; i < in_test.size(); i++)
        {
            std::cout << "Test " << i + 1 << ":\t";
            if (Encrypt_String(in_test[i]) == out_test[i]) {
                std::cout << "Успішно" << std::endl;
            }
            else {
                std::cout << "Помилка" << std::endl;
            }
        }
    }
    std::vector<std::string> in_test = { "41325 INCOMPLETECOLUMNARWITHALTERNATINGSINGLELETTERSANDDIGRAPHS",
       "12 HELLOWORLD",
       "3412 THISISJUSTATEST",
       "165432 WORKSMARTNOTHARD",
       "231 LLOHE" };
    std::vector<std::string> out_test = { "CECRTEGLENPHPLUTNANTEIOMOWIRSITDDSINTNALINESAALEMHATGLRGR",
    "HELOORDLWL",
    "SITASTTHJUESIST",
    "WONOTARDMRKSHART",
    "HELLO" };
};
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Task_Solution solution = Task_Solution();
    solution.Start();
    return 0;
}
