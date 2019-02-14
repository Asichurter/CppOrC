#include <map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	map<int, string> test;
	test[0] = "00";
	test[2] = "22";
	test[3] = "33";
	test[9] = "99";
	map<int, string>::iterator it;
	for (it = test.begin(); it != test.end(); it++) {
		cout << it->first << endl;
	}
	cin.get();
	return 0;
}