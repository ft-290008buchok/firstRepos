#include <iostream>
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	string str;
	int step, ciph_index, selector;

	//���������� ������ � ��������� � ���������� str
	cout << "������� �����\n";
	getline(cin, str);

	/*������� ������ � ������ char[],
	����� �� ��������� ������� 
	��� ������ � ��������� �����*/
	char *text = new char[str.length()];
	for (int i = 0; i < str.length(); i++)
		text[i] = str[i];

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
					������ ������� alphabet[]*/
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
	return 0;
}

