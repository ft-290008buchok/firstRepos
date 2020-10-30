#include <iostream>
#include <conio.h>
#include<fstream>
#include <string>

using namespace std;

bool check(char*, const int&, char*, const int&);

int main() {
	setlocale(LC_ALL, "rus");

	ofstream log("log.txt", ios_base::app);
	string mem = "Memory";
	log << mem;
	log.close();
	
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	string str;
	int step, ciph_index, selector, cont;
	char finish;

	//Считывание строки с пробелами в переменную str
	cout << "Введите текст\n";
	getline(cin, str);

	/*Перевод строки в массив char[],
	чтобы не возникало проблем
	при работе с индексами строк*/
	char *text = new char[str.length()];
	for (int i = 0; i < str.length(); i++)
		text[i] = str[i];

	//Проверяющий цикл
	while (!check(text, str.length(), alphabet, 26)) {
		cout << "Неверный формат, введите текст заново\n";
		getline(cin, str);
		for (int i = 0; i < str.length(); i++)
			text[i] = str[i];
	}

	cout << "Зашифровать -- введите 1. Расшифровать -- введите 0" << '\n';
	cin >> selector;

	if (selector) {
		cout << "Введите шаг сдвига > 0\n";
		cin >> step;

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
		for (int i = 0; i < str.length(); i++) {
			cout << encrypted[i];
		}
		cout << '\n';
		delete[] encrypted;
	}

	if (!selector) {
		cout << "Введите шаг сдвига > 0\n";
		cin >> step;

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
		for (int i = 0; i < str.length(); i++) {
			cout << decrypted[i];
		}
		cout << '\n';
		delete[] decrypted;
	}


	delete[] text;
	
	cout << "Для завершения работы нажмите любую клавишу";
	cin >> finish;

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