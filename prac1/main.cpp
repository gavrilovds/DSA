#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <vector>


using namespace std;

void ex1A() {
	unsigned int x;
	unsigned char mask = 1;
	cout << "Введите число x: ";
	cin >> x;
	cout << "Двоичное представление числа x: ";
	cout << bitset<8>(x) << endl;
	x = x & (~(mask << 4));
	cout << "Двоичное представление числа x после обнуления 5-ого бита: ";
	cout << bitset<8>(x) << endl;
	cout << "Число x: ";
	cout << x << endl;
	cout << "////////////////////\n";
}

void ex1B() {
	unsigned int x;
	unsigned char mask = 1;
	cout << "Введите число x: ";
	cin >> x;
	cout << "Двоичное представление числа x: ";
	cout << bitset<8>(x) << endl;
	x = x | (mask << 6);
	cout << "Двоичное представление числа x после установки 1  7-ого бита: ";
	cout << bitset<8>(x) << endl;
	cout << "Число x: ";
	cout << x << endl;
	cout << "////////////////////\n";
}

void ex1C() {
	unsigned int x = 25;
	const int n = sizeof(int) * 8; // = 32 - кол-во разрядов в типе int
	unsigned mask = (1 << n - 1); // 1 старшем бите 32-разрядной сетки
	cout << "Начальный вид маски: " << bitset<n>(mask) << "\n";
	cout << "Начальный вид x: " << bitset<n>(x) << "\n";
	cout << "Результат: ";

	for (int i = 1; i <= n; i++) {
		cout << ((x & mask) >> (n - i)); // маска на каждой итерации обрубает число до определенного разряда, после чего
		// после чего происходит логическая конъюнкция текущих битов у x и mask (1 & 1 = 1 else = 0)
		mask = mask >> 1;
	}
	cout << "\n///////////////\n";
}

void ex1() {
	int n;
	cout << "Введите номер подзадания(1, 2, 3): ";
	cin >> n;
	switch (n) {
		case 1:
			ex1A();
			break;
		case 2:
			ex1B();
			break;
		case 3:
			ex1C();
			break;
		default:
			cout << "Неверный номер подзадания\n";
	}
}

void ex2A() {
	int n;
	unsigned char bits = 0;
	cout << "Введите кол-во чисел последовательности (<=8): ";
	cin >> n;
	if (n > 8) {
		cout << "Вы вышли за предел размерной сетки";
		return;
	}
	cout << "Введите " << n << " чисел (0<=x<=7): ";

	unsigned char mask = 1;
	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x < 0 || x > 7) {
			cout << "Вышли за пределы 0<=x<=7\n";
			i--;
			continue;
		}
		bits = bits | (mask << (7 - x));
	}
	cout << "Отсортированная последовательность: \n";
	mask = 128;
	for (int i = 0; i < 8; i++) {
		if (bits & mask)
			cout << i << " ";
		mask = mask >> 1;
	}
	cout << "\n/////////////////////\n";
}

void ex2B() {
	int n;
	unsigned long long bits = 0;
	cout << "Введите кол-во чисел последовательности (<=64): ";
	cin >> n;
	if (n > 64) {
		cout << "Вы вышли за предел размерной сетки";
		return;
	}
	cout << "Введите " << n << " чисел (0<=x<=63): ";

	unsigned long long mask = 1;
	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x < 0 || x > 63) {
			cout << "Вышли за пределы 0<=x<=63\n";
			i--;
			continue;
		}
		bits = bits | (mask << (63 - x));
	}
	cout << "Отсортированная последовательность: \n";
	mask = pow(2, 63);
	for (int i = 0; i < 63; i++) {
		if (bits & mask)
			cout << i << " ";
		mask = mask >> 1;
	}
	cout << "\n/////////////////////\n";
}

void ex2C() {
	int n;
	unsigned char bits[8];
	for (int i = 0; i < 8; i++)
		bits[i] = 0;
	cout << "Введите кол-во чисел последовательности (<=64): ";
	cin >> n;
	if (n > 64) {
		cout << "Вы вышли за предел размерной сетки";
		return;
	}
	cout << "Введите " << n << " чисел (0<=x<=63): ";
	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x < 0 || x > 63) {
			cout << "Вышли за пределы 0<=x<=63\n";
			i--;
			continue;
		}
		bits[x / 8] = bits[x / 8] | (1 << ((x / 8 * 8 + 7) - x));
	}
	cout << "Полученный линейный массив чисел типа unsigned char: ";
	for (int i = 0; i < 8; i++)
		cout << bitset<8>(bits[i]) << " ";
	cout << "\n";
	cout << "Отсортированная последовательность: \n";
	for (int i = 0; i < 8; i++) {
		for (int j = 7; j >= 0; j--) {
			if ((bits[i] >> j) & 1)
				cout << (i * 8 + 7 - j) << " ";
		}
	}
	cout << "\n/////////////////////\n";
}


void ex2() {
	int n;
	cout << "Введите номер подзадания(1, 2, 3): ";
	cin >> n;
	switch (n) {
		case 1:
			ex2A();
			break;
		case 2:
			ex2B();
			break;
		case 3:
			ex2C();
			break;
		default:
			cout << "Неверный номер подзадания\n";
	}
}

void fillFile() {
	ofstream out("/Users/mac/Code/СИАОД/prac1/input.txt");
	for (int i = 9999999; i >= 0; i--)
		out << i << "\n";
	out.close();
}

void ex3A() {
	//bool *bits = new bool[10000000];
	vector<bool> bits(10000000, false);
	cout << "Заполнение файла...\n";
	fillFile();
	cout << "Файл заполнен\n";
	ifstream in("/Users/mac/Code/СИАОД/prac1/input.txt");
	int a;
	cout << "Сортировка запущена...\n";
	clock_t start = clock();
	while (!in.eof()) {
		in >> a;
		bits[a] = 1;
	}
	ofstream out("/Users/mac/Code/СИАОД/prac1/output.txt");
	for (int i = 0; i < 10000000; i++)
		if (bits[i])
			out << i << " ";
	out.close();
	in.close();
	clock_t end = clock();
	double seconds = (double) (end - start) / CLOCKS_PER_SEC;
	cout << "Сортировка закончена\n";
	cout << "Затраченное время " << seconds << " секунд.\n";
	cout << "Затраченная память на массив bits: " << (double)sizeof(bool) * (double)bits.capacity() / (double)1024 / (double)1024 / (double)8  << "\n";
	cout << "/////////////////\n";
}


void ex3() {
	int n;
	cout << "Введите номер подзадания(1): ";
	cin >> n;
	switch (n) {
		case 1:
			ex3A();
			break;
		default:
			cout << "Неверный номер подзадания\n";
	}
}

int main() {
	int n;
	while (true) {
		cout << "Введите номер задания (1, 2, 3): ";
		cin >> n;
		switch (n) {
			case 1:
				ex1();
				break;
			case 2:
				ex2();
				break;
			case 3:
				ex3();
				break;
			default:
				cout << "Некорректный номер задания\n";
		}
	}
}