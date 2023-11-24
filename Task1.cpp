

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
// Розбиваємо стрічку на ключі та текст
void split_string(std::string& str, std::string& keys) {
    std::istringstream iss(str);
    // Потік задля розбитя стрічки у масив
    std::vector<std::string> tokens;
    while (iss >> str) {
        tokens.push_back(str);
    }
    str.clear();
    for (size_t i = 0; i < tokens.size(); i++)
    {   // Перевірка на ключі
        if (std::isdigit(tokens[i][0])) {
            std::set<char> key(tokens[i].begin(), tokens[i].end());
            if (key.size() != tokens[i].size()) {
                throw std::runtime_error("The key must consist of unique digits\n");
            }
            keys += tokens[i];
        }
        else {
            // Запис тексту у стрічку
            str += tokens[i];
        }
    }
}
std::string ecnrypt_string(std::string& str){
    std::string result;
    std::string keys;
    split_string(str, keys);
    size_t str_size = str.size();
    // Матриця для запису окремих символів тексту
    std::vector<std::vector<std::string>> matrix;
    size_t i = 0;
    std::vector<std::string> symbols;
    while(i < str_size)
    {  
        // Розбиття стрічки на диграфи
        if (i + 2 < str_size) {
            std::string digraph;
            digraph.push_back(str[i]);
            digraph.push_back(str[i + 1]);
            symbols.push_back(digraph);
            i += 2;     
        }
        else {
            symbols.push_back(str.substr(i));
            break;
            }
        // Одна літера
        if (i + 1 < str_size) {
            std::string symbol;
            symbol.push_back(str[i]);
            symbols.push_back(symbol);
            i++; 
            }       
    }
    size_t numColumns = (symbols.size() + keys.size() - 1) / keys.size();
    matrix.resize(numColumns);

    size_t j = 0, counter = 0;
    // Заповнення матриці
    for (size_t i = 0; i < symbols.size(); i++)
    {
        if (counter < keys.size()) {
            matrix[j].push_back(symbols[i]);
            counter++;
            if (counter == keys.size()) {
                counter = 0;  
                j++;
            }
        }
    }
    // Масив стрічок, необхідний для зберігання стовбців матриці, елементи яких об'єднуються у одну стрічку у відповідному порядку
    std::vector<std::string> encrypted(keys.size());
    for (size_t i = 0; i < keys.size(); i++)
    {
       
        int key = keys[i] - '0';
        std::string word;
        for (size_t j = 0; j < matrix.size(); j++)
        {
            if (i < matrix[j].size()) {
                word += matrix[j][i];
            }
        }
        encrypted[key - 1] = word;
    }
    // Об'єднаяння тексту у одну стрічку
    for (const std::string& s : encrypted)
    {
        result += s;
    }
    return result;
  
}
bool compare_string(std::string& str1, std::string& str2) {
    std::string result = ecnrypt_string(str1);
   
    // Порівняння результатів тесту
    int compare_result = result.compare(str2);
    if (compare_result == 0) {
        return true;
    }
    else {
        throw std::runtime_error("Encryption failed");
    }
}
int main()
{
    // Тестові данні
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
    // Запуск тестів
    std::cout << "If you see 1, the test has succeeded" << std::endl;
    for (size_t i = 0; i < in_test.size(); i++)
    {
        std::cout << "Test " << i + 1 << " is:\t" << compare_string(in_test[i], out_test[i]) << std::endl;
    }
    // Ввведення свого тесту
    std::cout << "Enter your test[EXAMPLE: 1234 THISISTEST]" << std::endl;
    std::string user_test;
    std::getline(std::cin, user_test);
    std::cout << "Result based on your test:\t" << ecnrypt_string(user_test) << std::endl;
    return 0;
}
