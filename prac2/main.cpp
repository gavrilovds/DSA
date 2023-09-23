#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

string names[] = {"Иван", "Петр", "Алексей", "Сергей", "Андрей", "Максим", "Дмитрий", "Никита", "Владимир", "Григорий"};
string surnames[] = {"Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов", "Федоров", "Михайлов", "Новиков", "Соколов",
					 "Волков"};
string patronymics[] = {"Иванович", "Петрович", "Алексеевич", "Сергеевич", "Андреевич", "Максимович", "Дмитриевич",
						"Никитич", "Владимирович", "Григорьевич"};
vector<string> russianLetters = {"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", "О", "П",
								 "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"};

int dataAmount = 50;

struct Student {
	string gradebookNumber;
	string groupNumber;
	string fullName;

	Student() {

	}

	Student(string gradebookNumber, string groupNumber, string fullName) {
		this->fullName = fullName;
		this->gradebookNumber = gradebookNumber;
		this->groupNumber = groupNumber;
	}
};

struct SearchTable {
	int key;
	long long position;

	SearchTable() {

	}

	SearchTable(string key, long long position) {
		this->key = stoi(key);
		this->position = position;
	}
};

bool compareByKey(const SearchTable &ob1, const SearchTable &ob2) {
	return ob1.key < ob2.key;
}

vector<SearchTable> searchTable;

void generateBinaryFile() {
	srand(time(0));
	ofstream out("/Users/mac/Code/СИАОД/prac2/students.dat", ios::out | ios::binary);

	for (int i = 0; i < dataAmount; i++) {
		string FIO = surnames[rand() % 10];
		string group = russianLetters[rand() % 33] + russianLetters[rand() % 33]
					   + russianLetters[rand() % 33] + russianLetters[rand() % 33]
					   + "-" + to_string(rand() % 10) + to_string(rand() % 10) + "-"
					   + to_string(rand() % 10) + to_string(rand() % 10);
		string gradebook = to_string(rand() % (9999 - 1000 + 1) + 1000);
		Student student(gradebook, group, FIO);
		out.write((char *) &student, sizeof(Student));
		searchTable.push_back(SearchTable(gradebook, sizeof(Student) * i));
		cout << gradebook << " " << group << "\n";
	}
	out.close();
}

void linearSearch() {
	string key;
	cout << "Введите ключ поиска (номер зачетной книжки): ";
	cin >> key;
	FILE *ptrFile = fopen("/Users/mac/Code/СИАОД/prac2/students.dat", "r");
	clock_t start = clock();
	for (int i = 0; i < dataAmount; i++) {
		fseek(ptrFile, sizeof(Student) * i, SEEK_SET);
		Student *student = new Student();
		fread(student, sizeof(Student), 1, ptrFile);
		if (student->gradebookNumber == key) {
			cout << "Студент найден: \n";
			cout << "Фамилия: " << student->fullName << "\n";
			cout << "Группа: " << student->groupNumber << "\n";
			cout << "Номер зачетной книжки: " << student->gradebookNumber << "\n";
			clock_t end = clock();
			cout << "Затрачено времени на поиск: " << (double) (end - start) / CLOCKS_PER_SEC << " c.\n";
			return;
		}
	}
	fclose(ptrFile);
	cout << "Студент не найден.\n";
	clock_t end = clock();
	cout << "Затрачено времени на поиск: " << (double) (end - start) / CLOCKS_PER_SEC << " c.\n";
}

void getStudent(long long position, double wastedTime) {
	Student *student = new Student();
	//cout << "pos : " << position << "\n";
	FILE *ptrFile = fopen("/Users/mac/Code/СИАОД/prac2/students.dat", "r");
	fseek(ptrFile, position, SEEK_SET);
	fread(student, sizeof(Student), 1, ptrFile);
	cout << "Студент найден: \n";
	cout << "Фамилия: " << student->fullName << "\n";
	cout << "Группа: " << student->groupNumber << "\n";
	cout << "Номер зачетной книжки: " << student->gradebookNumber << "\n";
	cout << "Затрачено времени на поиск: " << wastedTime << " c.\n";
	fclose(ptrFile);
}

void binarySearch(string key) {
	int intKey = stoi(key);
	sort(searchTable.begin(), searchTable.end(), compareByKey);
	clock_t start = clock();
	vector<int> sigmaTable(floor(log(dataAmount)) + 4);
	for (int j = 1; j <= floor(log(dataAmount)) + 3; j++) {
		sigmaTable[j] = floor((dataAmount + pow(2, j - 1)) / pow(2, j));
	}
	int j = 1;
	int m = sigmaTable[j];
	while (m != 0 && j<sigmaTable.size()) {
		if (searchTable[m].key == intKey) {
			clock_t end = clock();
			double time = (double) (end - start) / CLOCKS_PER_SEC;
			getStudent(searchTable[m].position, time);
			break;
		} else if (intKey > searchTable[m].key) {
			j++;
			m += sigmaTable[j];
		} else {
			j++;
			m -= sigmaTable[j];
		}
	}
	if (m == 0 || j>=sigmaTable.size())
		cout << "Не найдено!";
}


int main() {
	cout << "Введите количество записей в файле (100, 1000, 10000): ";
	cin >> dataAmount;
	cout << "Генерация бинарного файла с данными...\n";
	generateBinaryFile();
	cout << "Бинарный файл students.dat сгенерирован.\n";
	int n;
	cout << "Введите алгоритм поиска(1 - линейный поиск, 2 - однородный бинарный поиск"
		 << " с использованием таблицы смещений (13 вариант)): ";
	cin >> n;
	string key;
	switch (n) {
		case 1:
			linearSearch();
			break;
		case 2:
			cout << "Введите ключ для поиска: ";
			cin >> key;
			binarySearch(key);
			break;
		default:
			cout << "Неверный ввод";
	}
}


