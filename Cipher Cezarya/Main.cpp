#include <iostream>

using namespace std;

int main() {
	char text1[] = "hellow";
	int length = 0;
	for (char *let = text1; *let != '\0'; let++)
		length++;
	cout << text1 << '\n';
	cout << length << '\n';
	return 0;
}

