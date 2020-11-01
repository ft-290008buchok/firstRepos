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
	log << "����� "<<start_num<<"-�� �������\n" << dateStr << endl << timeStr << endl;
	
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	string buff;
	int step, ciph_index, selector, cont;
	bool finish;


	while (true) {
		string str;
		//���������� ������ � ��������� � ���������� str
		cout << "������� �����\n";
		do {
			cin >> buff;
			str += buff + " ";
		} while (cin.peek() != '\n');

		log << "�������� �����:\n" << str << endl;

		/*������� ������ � ������ char[],
		����� �� ��������� �������
		��� ������ � ��������� �����*/
		char *text = new char[str.length()];
		for (int i = 0; i < str.length(); i++)
			text[i] = str[i];

		//����������� ����
		while (!check(text, str.length(), alphabet, 26)) {
			cout << "�������� ������, ������� ����� ������\n";
			log << "������ �����\n";
			getline(cin, str);
			log << "������ �������� �����:\n" << str << endl;
			for (int i = 0; i < str.length(); i++)
				text[i] = str[i];
		}

		cout << "����������� -- ������� 1. ������������ -- ������� 0" << '\n';
		cin >> selector;

		if (selector) {
			log << "���������� ������\n";
			cout << "������� ��� ������ > 0\n";
			cin >> step;
			log << "��� ������ = " << step << endl;

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
			log << "������������� �����:\n";
			for (int i = 0; i < str.length(); i++) {
				cout << encrypted[i];
				log << encrypted[i];
			}
			cout << '\n';
			log << endl;
			delete[] encrypted;
		}

		if (!selector) {
			log << "������������ ������\n";
			cout << "������� ��� ������ > 0\n";
			cin >> step;
			log << "��� ������ = " << step << endl;

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
			log << "�������������� �����:\n";
			for (int i = 0; i < str.length(); i++) {
				cout << decrypted[i];
				log << decrypted[i];
			}
			cout << '\n';
			log << endl;

			delete[] decrypted;
		}

		delete[] text;

		cout << "���������� ������ -- 1, ��������� -- 0:\n";
		cin >> finish;
		if (!finish) { break; }
	}
	

	log.close();

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