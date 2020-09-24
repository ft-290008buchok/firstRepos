#include <iostream>
#include <string>

using namespace std;

int main() {
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	string str;
	int step, ciph_index;
	getline(cin, str);
	cin >> step;
	cout << str.length()<<'\n';
	char *text = new char[str.length()];
	char *encrypted = new char[str.length()];
	for (int i = 0; i < str.length(); i++)
		text[i] = str[i];
	for (int i = 0; i < str.length(); i++) {
		for (int j = 0; j < 26; j++) {
			if (alphabet[j] == text[i]) {
				ciph_index = j + step;
				if (ciph_index > 25)
					ciph_index -= 26;
				encrypted[i] = alphabet[ciph_index];
			}
		}
		if (text[i] == ' ')
			encrypted[i] = ' ';
	}
	for (int i = 0; i < str.length(); i++) {
		cout << encrypted[i];
	}
	cout << '\n';
	delete[] text;
	delete[] encrypted;
	return 0;
}

