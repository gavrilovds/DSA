#include <iostream>
#include <vector>

using namespace std;


vector<string> addresses = {"123 Main St", "456 Elm St", "789 Oak Ave", "10 Pine Rd", "11 Maple Ln", "12 Cedar Dr",
							"13 Birch Ct", "14 Walnut Blvd", "15 Chestnut Rd", "16 Spruce Ave", "17 Pine St",
							"18 Oak Rd", "19 Maple Ave", "20 Elm Dr", "21 Cedar Ln"};
vector<string> firstNames = {"Alice", "Bob", "Charlie", "David", "Emma", "Frank", "Grace", "Henry", "Isabella", "Jack",
							 "Kate", "Liam", "Mia", "Noah", "Olivia", "Peter", "Quinn", "Rose", "Sophia", "Thomas",
							 "Ursula", "Victoria", "William", "Xander", "Yvonne", "Zachary"};
vector<string> lastNames = {"Anderson", "Brown", "Carter", "Davis", "Edwards", "Fisher", "Garcia", "Harris", "Jackson",
							"Kim", "Lee", "Miller", "Nguyen", "Olsen", "Parker", "Quinn", "Robinson", "Smith", "Taylor",
							"Upton", "Vargas", "White", "Xu", "Young", "Zhang"};


struct BankAccount {
	string address;
	string FIO;
	int accountNumber;

	BankAccount(const string &address, const string &fio, int accountNumber) : address(address), FIO(fio),
																			   accountNumber(accountNumber) {}
};

vector<BankAccount *> accounts;

void printAccounts() {
	int i = 1;
	for (BankAccount *account: accounts) {
		cout << i++ << ". ";
		cout << "Номер счета: " << account->accountNumber << ", владелец: " << account->FIO
			 << ", адрес: " << account->address << "\n";
	}
}

void generateAccount() {
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		BankAccount *bankAccount = new BankAccount(addresses[rand() % 15],
												   firstNames[rand() % 15] + " " + lastNames[rand() % 15],
												   rand() % (9999999 - 1000000 + 1) + 10000000);
		accounts.push_back(bankAccount);
	}
	cout << "Сгенерированные счета:\n";
	printAccounts();
}

void printAccountInfo(BankAccount *account) {
	cout << "Номер счета: " << account->accountNumber << ", владелец: " << account->FIO
		 << ", адрес: " << account->address << "\n";
}


int TABLE_SIZE = 100;

class HashTable {
private:
	vector<BankAccount *> tableAccounts;

	int hash1(int key) {
		return key % TABLE_SIZE;
	}

	int hash2(int key) {
		key = ((key >> 16) ^ key) * 0x45d9f3b;
		key = ((key >> 16) ^ key) * 0x45d9f3b;
		key = (key >> 16) ^ key;
		return key % TABLE_SIZE;
	}

public:
	HashTable() {
		tableAccounts.resize(TABLE_SIZE);
		for (int i = 0; i < TABLE_SIZE; i++)
			tableAccounts[i] = nullptr;
	}

	~HashTable() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (tableAccounts[i] != nullptr)
				delete tableAccounts[i];
		}
	}

	void put(int key, BankAccount *bankAccount) {
		int hashVal = hash1(key);
		int stepSize = hash2(key);

		while (tableAccounts[hashVal] != nullptr && tableAccounts[hashVal]->accountNumber != key) {
			hashVal = (hashVal + stepSize) % TABLE_SIZE;
		}

		if (tableAccounts[hashVal] != nullptr) {
			delete tableAccounts[hashVal];
		}

		tableAccounts[hashVal] = bankAccount;
	}

	BankAccount *get(int key) {
		int hashVal = hash1(key);
		int stepSize = hash2(key);

		while (tableAccounts[hashVal] != nullptr && tableAccounts[hashVal]->accountNumber != key) {
			hashVal = (hashVal + stepSize) % TABLE_SIZE;
		}

		if (tableAccounts[hashVal] == nullptr) {
			return nullptr;
		} else {
			return tableAccounts[hashVal];
		}
	}

	void remove(int key) {
		int hashVal = hash1(key);
		int stepSize = hash2(key);

		while (tableAccounts[hashVal] != nullptr && tableAccounts[hashVal]->accountNumber != key) {
			hashVal = (hashVal + stepSize) % TABLE_SIZE;
		}

		if (tableAccounts[hashVal] != nullptr) {
			cout << "Счет: \n";
			printAccountInfo(tableAccounts[hashVal]);
			cout << "Удален.\n";
			delete tableAccounts[hashVal];
			tableAccounts[hashVal] = nullptr;
		} else {
			cout << "Счет не найден.\n";
		}
	}
};

int main() {
	cout << "Генерируем случайные счета...\n";
	generateAccount();
	int n;
	cout << "\nВведите кол-во записей, которые вы хотите добавить в HashTable (1-10):";
	while (true) {
		cin >> n;
		if (n < 1 || n > 10) {
			cout << "Введите число из диапазона 1-10:\n";
			continue;
		}
		break;
	}
	HashTable hashTable;
	cout << "Выберите " << n << " счетов из выборки (введите порядковый номер из списка):\n ";
	while (n > 0) {
		printAccounts();
		int a;
		cin >> a;
		if (a < 1 || a > accounts.size()) {
			cout << "Введите доступный порядковый номер:\n";
			continue;
		}
		hashTable.put(accounts[a - 1]->accountNumber, accounts[a - 1]);
		cout << "Счет с порядковым номер " << a << " добавлен в HashMap. Ключ - " << accounts[a - 1]->accountNumber
			 << "\n";
		accounts.erase(accounts.begin() + (a - 1));
		n--;
	}
	string command = "";
	while (true) {
		cout << "Введите команду (get/put/remove/exit): ";
		cin >> command;
		if (command == "exit")
			return 0;
		else if (command == "get") {
			cout << "Введите номер счета: ";
			int key;
			cin >> key;
			BankAccount *result = hashTable.get(key);
			if (result == nullptr) {
				cout << "Номер счета не найден.\n";
			} else {
				cout << "Счет найден: \n";
				printAccountInfo(result);
			}
		} else if (command == "remove") {
			int key;
			cout << "Введите номер счета: ";
			cin >> key;
			hashTable.remove(key);
		} else if (command == "put") {
			cout << "Доступные счета для добавления: \n";
			printAccounts();
			cout << "Введите порядковый номер счета для добавления: ";
			while (true) {
				int a;
				cin >> a;
				if (a < 1 || a > accounts.size()) {
					cout << "Введите доступный порядковый номер:\n";
					continue;
				}
				hashTable.put(accounts[a - 1]->accountNumber, accounts[a - 1]);
				cout << "Счет с порядковым номер " << a << " добавлен в HashMap. Ключ - "
					 << accounts[a - 1]->accountNumber
					 << "\n";
				accounts.erase(accounts.begin() + (a - 1));
				break;
			}
		} else {
			cout << "Недопустимая команда.\n";
		}
	}
}
