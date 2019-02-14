#include "HfmTree.h"
#include "HfmUtil.h"
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	int al;
	int fres[27];
	char chs[27];
	int num = 0;
	string con = "STAR_LIGHT_STAR_BRIGHT_FIRST_STAR_I_SEE_TONIGHT_I_WISH_I_MAY_I_WISH_I_MIGHT_GET_THE_WISH_I_WISH_TONIGHT";
	for (int i = 0; i < con.length(); i++) {
		int j;
		for (j = 0; j < num; j++) {
			if (chs[j] == con.at(i))
				break;
		}
		if (j == num){
			chs[num] = con.at(i);
			fres[num++] = 1;
		}
		else fres[j]++;
	}
	HfmTree<char>* tree = buildHfmTree<char>(makeForest<char>(fres, chs, num), num);
	tree->traverse();
	for (int i = 0; i < num; i++) {
		cout << chs[i] << " " << fres[i] << endl;
	}
	map<char, string> table = makeTable(tree);
	string enc = encode(con, table);
	cout << decode(enc, tree) << endl;
	/*
	for (int i = 0; i < 26; i++) {
		chs[i] = i + 65;
		fres[i] = rand() % 200;
	}
	fres[26] = rand() % 300;
	chs[26] = ' ';
	HfmTree<char>* tree = buildHfmTree<char>(makeForest<char>(fres, chs, 27), 27);
	tree->traverse();
	map<char, string> table = makeTable(tree);
	for (int i = 0; i < 26; i++){
		cout << char(i+65) << ": " << table[char(i+65)] << endl;
	}
	cout << "Space: " << table[' '] << endl;
	string test = "VISUAL STUDIO";
	string encoding = encode(test, table);
	cout << encoding << endl;
	string decoding = decode(encoding, tree);
	cout << decoding << endl;
	if (decoding == test) {
		cout << "成功！" << endl;
	}
	else if (decoding == "")
		cout << "解码错误！" << endl;
	*/
	/*
	for (int i = 0; i < 10; i++) {
		int length = rand() % 10 + 1;
		string src = "";
		for (int j = 0; j < length; j++) {
			char character = (rand() % 26) + 65;
			src += character;
		}
		string enc = encode(src, table);
		string dec = decode(enc, tree);
		if (dec == src) {
			cout << "第" << i+1 << "次成功！" << endl;
		}
		else cout << "第" << i+1 << "次失败！" << endl;
	}*/
	cin >> al;
	return 0;
}
