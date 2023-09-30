#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


void task1() {
	string text = "cat,dog,house,car,book,computer,dogich,phone,tree,sky,sapog,sun,moon,star,ocean,river,mountain,beach,flower,bird,fish,elephant,tiger,lion,giraffe,zebra,monkey,snake,butterfly,spider,ant";
	cout << "Исохдный текст: \n";
	cout << text;
	cout << "\nВведите строку подстроку, которая должная содержаться в конце слова: ";
	string search;
	cin >> search;
	vector<string> result;
	int cur = 0;
	int start = 0;
	for (int i = 0; i < text.size(); i++) {
		if (text[i] == ',') {
			cur = 0;
			start = i + 1;
			continue;
		}
		if (text[i] == search[cur]) {
			cur++;
			if (cur == search.size() && ((i + 1) == text.size() || text[i + 1] == ',')) {
				result.push_back(text.substr(start, i - start + 1));
				cur = 0;
			}
		}
	}
	if (result.empty()) {
		cout << "Подходящих слов не найдено";
		exit(0);
	}
	cout << "Слова, содержащие \"" << search << "\" в конце слова:\n";
	for (auto str: result)
		cout << str << " ";
	exit(0);
}

void task2() {
	ifstream in("/Users/mac/Code/СИАОД/prac4/input.txt");
	string search;
	in >> search;
	string text;
	in >> text;
	int result = 0;
	int m = search.size();
	int n = text.size();
	int searchHash = 0;
	int textHash = 0;
	int hash = 1;
	int i, j;
	for (i = 0; i < m - 1; i++)
		hash = (hash * 256) % INT_MAX;
	for (i = 0; i < m; i++) {
		searchHash = (searchHash * 256 + search[i]) % INT_MAX;
		textHash = (textHash * 256 + text[i]) % INT_MAX;
	}
	for (i = 0; i <= n - m; i++) {
		if (searchHash == textHash) {
			for (j = 0; j < m; j++) {
				if (text[i + j] != search[j])
					break;
			}
			if (j == m) {
				cout << "Подстрока найдена на индексе: " << i << '\n';
				++result;
			}
		}
		if (i < n - m) {
			textHash = (256 * (textHash - text[i] * hash) + text[i + m]) % INT_MAX;
			if (textHash < 0) {
				textHash += INT_MAX;
			}
		}
	}
	cout << "Всего найдено совпадений: " << result;
	exit(0);
}

int main() {
	int n;
	cout << "Введите номер задания (1, 2, 0 - выход): ";
	while (true) {
		cin >> n;
		switch (n) {
			case 1:
				task1();
				break;
			case 2:
				task2();
				break;
			case 0:
				return 0;
			default:
				cout << "Введите корректный номер задания: ";
				break;
		}
	}
}
