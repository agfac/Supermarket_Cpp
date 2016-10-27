#include "utils.h"


void clearScreen(){
	system("cmd /c cls");
}


unsigned short int readUnsignedShortInt(unsigned short int min, unsigned short int  max){

	int num;

	cin >> num;
	cin.clear();
	cin.ignore(1000, '\n');

	while (cin.fail() || num < min || num > max) {
		cout << " Please enter a valid menu option> ";
		cin >> num;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return num;
}


int readInteger(int min, int max){

	int num;

	cin >> num;
	cin.clear();
	cin.ignore(1000, '\n');

	while (cin.fail() || num < min || num > max) {
		cout << TAB << "Please enter a valid menu option> ";
		cin >> num;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return num;
}

bool fileExists(string filename) {

	bool exists = false;
	ifstream inputFile;
	inputFile.open(filename);
	if (inputFile.is_open()) {
		exists = true;
		inputFile.close();
	}
	return exists;
}

bool is_number(const string & s){

	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) 
		++it;
	return !s.empty() && it == s.end();
}

void verifyCorrectId(int &id, string type){

	while (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << " You enter a not valid " << type << " ID!" << endl;
		cout << " Please enter a valid " << type << " ID> ";
		cin >> id;
		cin.ignore(1000, '\n');
	}
}

void verifyCorrectPrice(float &price, string type) {

	while (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << " You enter a not valid " << type << " ID!" << endl;
		cout << " Please enter a valid " << type << " ID> ";
		cin >> price;
		cin.ignore(1000, '\n');
	}
}

void verifyIdExists(int &id, string type, string operation){

		cout << " The " << type << " ID you entered doesn't exists!" << endl;
		cout << " Please enter a valid " << type << " ID to " << operation << "> ";
		cin >> id;
		cin.ignore(1000, '\n');

		while (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << " You enter a not valid " << type << " ID!" << endl;
			cout << " Please enter a valid " << type << " ID> ";
			cin >> id;
			cin.ignore(1000, '\n');
		}
}

void verifyNameExists(string & name, string type){

	cout << " The " << type << " name you entered doesn't exists!" << endl;
	cout << " Please enter a valid " << type << " name> ";
	getline(cin, name);
}

void verifyStringIsNotEmptyAndNotANumber(string &name, string type){

	while (name.empty() || is_number(name)) {
		cout << " You enter a not valid " << type << " name!" << endl;
		cout << " Please enter a valid " << type << " name> ";
		getline(cin, name);
	}
}

multimap<int, int> flip_map(const map<int, int> & src) {

	multimap<int, int> dst;

	for (map<int, int>::const_iterator it = src.begin(); it != src.end(); ++it)
		dst.insert(pair<int, int>(it->second, it->first));

	return dst;
}