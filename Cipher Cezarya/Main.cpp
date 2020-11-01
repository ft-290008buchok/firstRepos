#include <iostream>
#include<fstream>
#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

bool check(char*, const int&, char*, const int&);

int main() {
	setlocale(LC_ALL, "rus");
	ofstream log_num_wr("log_num.txt", ios_base::app);
	log_num_wr << '1';
	log_num_wr.close();

	ifstream log_num_r("log_num.txt");
	log_num_r.seekg(0, ios_base::end);
	int start_num = log_num_r.tellg();
	log_num_r.close();

	ofstream log("log.txt", ios_base::app);
	
	char dateStr[9];
	char timeStr[9];
	_strdate_s(dateStr);
	_strtime_s(timeStr);
	log << "================================================\n";
	log << "Время "<<start_num<<"-го запуска\n" << dateStr << endl << timeStr << endl;
	
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	string buff;
	int step, ciph_index, selector, cont;
	bool finish;


	while (true) {
		string str;
		//Считывание строки с пробелами в переменную str
		cout << "Введите текст\n";
		do {
			cin >> buff;
			str += buff + " ";
		} while (cin.peek() != '\n');

		log << "Введённый текст:\n" << str << endl;

		/*Перевод строки в массив char[],
		чтобы не возникало проблем
		при работе с индексами строк*/
		char *text = new char[str.length()];
		for (int i = 0; i < str.length(); i++)
			text[i] = str[i];

		//Проверяющий цикл
		while (!check(text, str.length(), alphabet, 26)) {
			cout << "Неверный формат, введите текст заново\n";
			log << "Ошибка ввода\n";
			getline(cin, str);
			log << "Заново введённый текст:\n" << str << endl;
			for (int i = 0; i < str.length(); i++)
				text[i] = str[i];
		}

		cout << "Зашифровать -- введите 1. Расшифровать -- введите 0" << '\n';
		cin >> selector;

		if (selector) {
			log << "Шифрование текста\n";
			cout << "Введите шаг сдвига > 0\n";
			cin >> step;
			log << "Шаг сдвига = " << step << endl;

			//Шифрование текста
			char *encrypted = new char[str.length()];
			for (int i = 0; i < str.length(); i++) {
				//26 - это длина alphabet[]
				for (int j = 0; j < 26; j++) {
					if (alphabet[j] == text[i]) {
						ciph_index = j + step;
						/*Обеспечение циклического сдвига
						по массиву alphabet[] в случае, если
						индекс зашифрованного символа превосходит
						длину массива alphabet[]*/
						if (ciph_index > 25)
							ciph_index -= 26 * (ciph_index / 26);
						encrypted[i] = alphabet[ciph_index];
					}
				}
				//обработка пробела во входной строке
				if (text[i] == ' ')
					encrypted[i] = ' ';
			}
			cout << "Зашифрованный текст\n";
			log << "Зашифрованный текст:\n";
			for (int i = 0; i < str.length(); i++) {
				cout << encrypted[i];
				log << encrypted[i];
			}
			cout << '\n';
			log << endl;
			delete[] encrypted;
		}

		if (!selector) {
			log << "Дешифрование текста\n";
			cout << "Введите шаг сдвига > 0\n";
			cin >> step;
			log << "Шаг сдвига = " << step << endl;

			//Дешифрование текста
			char *decrypted = new char[str.length()];
			for (int i = 0; i < str.length(); i++) {
				for (int j = 0; j < 26; j++) {
					if (alphabet[j] == text[i]) {
						ciph_index = j - step;
						/*Обеспечение циклического сдвига
						по массиву alphabet[] в случае, если
						индекс расшифрованного символа
						меньше нуля*/
						if (ciph_index < 0)
							ciph_index -= 26 * (ciph_index / 26 - 1);
						decrypted[i] = alphabet[ciph_index];
					}
				}
				//Обработка пробела во входной строке
				if (text[i] == ' ')
					decrypted[i] = ' ';
			}
			cout << "Расшифрованный текст\n";
			log << "Расшифрованный текст:\n";
			for (int i = 0; i < str.length(); i++) {
				cout << decrypted[i];
				log << decrypted[i];
			}
			cout << '\n';
			log << endl;

			delete[] decrypted;
		}

		delete[] text;

		cout << "Продолжить работу -- 1, завершить -- 0:\n";
		cin >> finish;
		if (!finish) { break; }
	}
	

	log.close();

	return 0;
}

/*Функция обработки ошибок ввода
-----------------------------------------
Принимает на вход указатель на первый
элемент массива символов текста, который
необходимо проверить, длину этого массива 
и указатель на массив допустимых символов,
его длину*/
bool check(char* text, const int& t, char* alph, const int& a) {
	bool ch = false;
	for (int i = 0; i < t; i++) {
		ch = false;
		for (int j = 0; j < a; j++) {
			if (text[i] == alph[j]) {
				ch = true;
			}
			if (text[i] ==' ') {
				ch = true;
			}
		}
		/*Если текст содержит недопустимый символ,
		вернёт false*/
		if (!ch) { return  false;  break; }
	}
	//Если все символы корректны,вернёт true*
	return true;
}