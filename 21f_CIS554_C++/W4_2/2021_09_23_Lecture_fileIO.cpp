
#include <iostream> //cin, cout
#include <fstream>
#include <string>

using namespace std;

int main() {
	int i{ 10 }, j{ 20 };
	string s {"CIS554"};
	cout << i << "  " << s << endl;
	cout <<  j << endl;

	ofstream out;
	out.open("data.txt");
	out << i << "  " << s << endl;
	out << j << endl;
	out.close();

	ifstream in("data.txt");
	in >> i >> s >> j;
	cout << i << "  " << s << endl;
	cout << j << endl;
	in.close();
	return 0;
}