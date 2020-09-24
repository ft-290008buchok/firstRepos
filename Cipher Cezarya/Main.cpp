#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main() {
	char alphabet[] = " abcdefghijklmnopqrstuvwxyz";
	string str;
	getline(cin, str);
	cout << str.length();
	char *text = new char[str.length()];
	char *encrypted = new char[str.length()];
	for (int i = 0; i < str.length(); i++)
		text[i] = str[i];
	for (int i = 0; i < str.length(); i++) {
		for (int j = 0; j < 34; j++) {
			if (alphabet[j] == text[i]) {
				encrypted[i] = alphabet[j];
			}
		}
	}
	for (int i = 0; i < str.length(); i++) {
		cout << encrypted[i];
	}
	delete[] text;
	delete[] encrypted;
	return 0;
}

