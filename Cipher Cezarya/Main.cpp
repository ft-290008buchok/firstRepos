#include <iostream>
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	string str;
	int step, ciph_index, selector;

	//Считывание строки с пробелами в переменную str
	cout << "Введите текст\n";
	getline(cin, str);

	/*Перевод строки в массив char[],
	чтобы не возникало проблем 
	при работе с индексами строк*/
	char *text = new char[str.length()];
	for (int i = 0; i < str.length(); i++)
		text[i] = str[i];

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
					размер массива alphabet[]*/
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
	return 0;
}

