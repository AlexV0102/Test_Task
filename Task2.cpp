#include <iostream>
#include <vector>
#include <array>
#include <sstream>

std::vector<int> find_substruction(std::vector<int>& numbers) {
	std::vector<int> res(numbers.size(),0);
	for (size_t i = 0, j = 1; j < numbers.size(); i++, j++)
	{
		// Віднімання елементів послідовності
		res.push_back(numbers[j] - numbers[i]);
	}
	return res;
}
void fill_vector(std::string& nums_string, std::vector<int>& nums) {
	// Потік для зчитання рядка
	std::istringstream iss(nums_string);
	int number;
	while (iss >> number)
	{
		nums.push_back(number);
		// Пропускаємо пробіли 
		iss.ignore();
	}
}
std::string get_next_sequence(std::string& nums_string) {
		
	std::vector<int> numbers;
	// Перетворення стрічки у вектор чисел 
	fill_vector(nums_string, numbers);
	// Перевірка на розмір  
	if (numbers.size() < 2) {
		throw std::runtime_error("Sequence lenght must be bigger than 1!");
	}
	std::vector<int> result;
	std::vector<std::vector<int>> substrictions;
	// Знаходження різниць послідовності 
	substrictions.push_back(find_substruction(numbers));
	for (size_t i = 1; i < 3; i++)
	{
		substrictions.push_back(find_substruction(substrictions[i - 1]));
	}
	std::array<int, 3> sequence{};
	sequence[0] = substrictions[0].back() + substrictions[1].back() + substrictions[2].back();
	sequence[1] = sequence[0] + substrictions[1].back() + substrictions[2].back();
	sequence[2] = sequence[1] + substrictions[1].back() + substrictions[2].back();
	// Отримання трьох наступних елементів 
	int num1 = numbers.back() + sequence[0];
	int num2 = num1 + sequence[1];
	int num3 = num2 + sequence[2];
	result = { num1,num2,num3 };
	// Перетворення у стрічку
	std::string result_string;
	for (int num : result) {
		result_string += std::to_string(num) + " ";
	}
	result_string.pop_back();
	return result_string;

}	
// Тест 
bool compare_test(std::string& nums1, std::string& nums2) {
	std::string result = get_next_sequence(nums1);
	if (result == nums2) {
		return true;
	}
	else {
		return false;
	}

}
void fill_vector(std::vector<int>& num){}
int main() {
	// Тестові дані 
	std::vector<std::string> input_test = { "12 14 16 18 20", "15 32 57 90 131 180", "1 1 1 1 1" };
	std::vector<std::string> output_test= { "22 24 26", "237 302 375", "1 1 1"};
	// Перевірка тестів
	std::cout << "If you see 1, the test has succeeded" << std::endl;
	for (size_t i = 0; i < input_test.size(); i++)
	{
		std::cout << "Test " << i + 1 << " is " << compare_test(input_test[i], output_test[i]) << std::endl;
	}
	// Ввід свого тесту 
	std::cout << "Enter your test string with number sequence (for example 1 3 6 10):" << std::endl;
	std::string user_test;
	std::getline(std::cin, user_test);
	std::cout << "Result based on your test:\t" << get_next_sequence(user_test) << std::endl;
	return 0;
}