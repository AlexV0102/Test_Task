#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <Windows.h>
#include <conio.h>
class Task_Solution {
public:
	Task_Solution() {};
	~Task_Solution() = default;
	void Start() {
		Start_Tests();
		char exit;
		while (true) {
			std::cout << "Введіть Ваш тест [ Наприклад: 1 3 6 10, максимальний розмір (M) 10]" << std::endl;
			std::string user_test;
			std::getline(std::cin, user_test);
			std::cout << "Наступні три числа заданої послідовності:\t" << Get_Next_Sequence(user_test) << std::endl;
			std::cout << "Нажміть ESC, щоб вийти, або будь-яку іншу клавішу щоб ввести нові данні" << std::endl;
			exit = _getch();
			if (exit == 27) {
				std::cout << "Гарного дня!" << std::endl;
				break;
			}
		}
	};

private:
	std::vector<int> Find_Substruction(std::vector<int>& numbers) {
		std::vector<int> res;
		for (auto it = numbers.begin(); std::next(it) != numbers.end(); ++it) {
			res.emplace_back(*(std::next(it)) - *it);
		}
		if (res.empty()) {
			res = { 0 };
		}
		return res;
	}
	std::string Get_Next_Sequence(std::string& nums_string) {

		std::vector<int> numbers;
		// Перетворення стрічки у вектор чисел 
		Fill_Vector(nums_string, numbers);

		std::vector<int> result;
		std::vector<std::vector<int>> substrictions;
		// Знаходження різниць послідовності 
		substrictions.push_back(Find_Substruction(numbers));
		for (size_t i = 1; i < 3; i++)
		{
			substrictions.push_back(Find_Substruction(substrictions[i - 1]));
		}
		std::array<int, 3> sequence{ 0,0,0 };
		Find_Sequence(substrictions, sequence);
		// Отримання трьох наступних елементів 
		int size = numbers.size();
		for (int i = 0; i < 3; i++)
		{
			// Формула для знаходження наступних трьох елементів
			// а(nі) = a0 + d_11*(n-1 + i) + d_21 * T(n) + d_31
			// Де: 1) а(nі) - шукані числа
			//	   2) і - лічильник для знаходження трьох елементів
			//	   3) d_11, d_21, d_31 числа взяті із різниць послідовності
			//	   4) T(n) - трикутне число, яке знаходиться за формолую T(n) = n*(n+1)/2, у коді додан лічильник і задля 
			//        знаходження всіх трьох наступних елементів
			// Примітка: d_31 є елементом з різниці послідовностей, які дорівнюють нулю
			int num = numbers.front() + sequence[0] * (size + i) + sequence[1] * ((size + i - 1) * (size + i) / 2);
			result.push_back(num);
		}
		// Перетворення у стрічку
		std::string result_string;
		for (int num : result) {
			result_string += std::to_string(num) + " ";
		}
		result_string.pop_back();
		return result_string;
	}
	void Fill_Vector(std::string& nums_string, std::vector<int>& nums) {
		std::istringstream iss(nums_string);
		int number;
		while (iss >> number)
		{
			nums.push_back(number);
			// Пропускаємо пробіли 
			iss.ignore();
		}
		// Перевірка на розмір  
		if (nums.empty()) {
			std::cout << "Невірно введені дані!" << std::endl;
			exit(1);
		}
		if (nums.size() < 2) {
			std::cout << "Довжина послідовності повинна бути більше за 2!" << std::endl;
			exit(1);
		}
		if (nums.size() > 10) {
			std::cout << "Максимальний розмір повинен бути менше за 10!" << std::endl;
			exit(1);
		}
	}
	void Find_Sequence(std::vector<std::vector<int>>& substrictions, std::array<int, 3>& result) {

		result[0] = substrictions[0].front();
		result[1] = substrictions[1].front();
		result[2] = substrictions[2].front();

	}
	void Start_Tests() {
		std::cout << "Запуск тестових данних..." << std::endl;
		for (size_t i = 0; i < in_test.size(); i++)
		{
			std::cout << "Тест " << i + 1 << ":\t";
			if (Get_Next_Sequence(in_test[i]) == out_test[i]) {
				std::cout << "Успішно" << std::endl;
			}
			else {
				std::cout << "Помилка" << std::endl;
			}
		}
	}
	std::vector<std::string> in_test = { "12 14 16 18 20", "15 32 57 90 131 180", "1 1 1 1 1" };
	std::vector<std::string> out_test = { "22 24 26", "237 302 375", "1 1 1" };
};
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Task_Solution solution = Task_Solution();
	solution.Start();
	return 0;
}