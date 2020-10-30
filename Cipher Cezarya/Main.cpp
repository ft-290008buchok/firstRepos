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

	//���������� ������ � ��������� � ���������� str
	cout << "������� �����\n";
	getline(cin, str);

	/*������� ������ � ������ char[],
	����� �� ��������� �������
	��� ������ � ��������� �����*/
	char *text = new char[str.length()];
	for (int i = 0; i < str.length(); i++)
		text[i] = str[i];

	//����������� ����
	while (!check(text, str.length(), alphabet, 26)) {
		cout << "�������� ������, ������� ����� ������\n";
		getline(cin, str);
		for (int i = 0; i < str.length(); i++)
			text[i] = str[i];
	}

	cout << "����������� -- ������� 1. ������������ -- ������� 0" << '\n';
	cin >> selector;

	if (selector) {
		cout << "������� ��� ������ > 0\n";
		cin >> step;

		//���������� ������
		char *encrypted = new char[str.length()];
		for (int i = 0; i < str.length(); i++) {
			//26 - ��� ����� alphabet[]
			for (int j = 0; j < 26; j++) {
				if (alphabet[j] == text[i]) {
					ciph_index = j + step;
					/*����������� ������������ ������
					�� ������� alphabet[] � ������, ����
					������ �������������� ������� �����������
					����� ������� alphabet[]*/
					if (ciph_index > 25)
						ciph_index -= 26 * (ciph_index / 26);
					encrypted[i] = alphabet[ciph_index];
				}
			}
			//��������� ������� �� ������� ������
			if (text[i] == ' ')
				encrypted[i] = ' ';
		}
		cout << "������������� �����\n";
		for (int i = 0; i < str.length(); i++) {
			cout << encrypted[i];
		}
		cout << '\n';
		delete[] encrypted;
	}

	if (!selector) {
		cout << "������� ��� ������ > 0\n";
		cin >> step;

		//������������ ������
		char *decrypted = new char[str.length()];
		for (int i = 0; i < str.length(); i++) {
			for (int j = 0; j < 26; j++) {
				if (alphabet[j] == text[i]) {
					ciph_index = j - step;
					/*����������� ������������ ������
					�� ������� alphabet[] � ������, ����
					������ ��������������� �������
					������ ����*/
					if (ciph_index < 0)
						ciph_index -= 26 * (ciph_index / 26 - 1);
					decrypted[i] = alphabet[ciph_index];
				}
			}
			//��������� ������� �� ������� ������
			if (text[i] == ' ')
				decrypted[i] = ' ';
		}
		cout << "�������������� �����\n";
		for (int i = 0; i < str.length(); i++) {
			cout << decrypted[i];
		}
		cout << '\n';
		delete[] decrypted;
	}


	delete[] text;
	
	cout << "��� ���������� ������ ������� ����� �������";
	cin >> finish;

	return 0;
}

/*������� ��������� ������ �����
-----------------------------------------
��������� �� ���� ��������� �� ������
������� ������� �������� ������, �������
���������� ���������, ����� ����� ������� 
� ��������� �� ������ ���������� ��������,
��� �����*/
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
		/*���� ����� �������� ������������ ������,
		����� false*/
		if (!ch) { return  false;  break; }
	}
	//���� ��� ������� ���������,����� true*
	return true;
}