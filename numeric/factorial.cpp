#include "big_integer.h"

#include <ctime>

#include <iostream>
using namespace std;

int main( )
{
    int N;
	big_integer x = 42;
	/*
	big_integer y = 73;
	string ch;
	cout << "input expression like '1 + 2' then Enter.\n"
		<< "if x==42 and  y==73 to exit.\n"
		<< "notice: need spaces in expression.\n";
	while (cin >> x >> ch >> y) {
		if (x == 42 && y == 73) break;
		if (ch == "+") {
			cout << x + y << endl;
		} else if (ch == "-") {
			cout << x - y << endl;
		} else if (ch == "*") {
			cout << x * y << endl;
		} else if (ch == "/") {
			cout << x / y << endl;
		} else if (ch == "%") {
			cout << x % y << endl;
		} else if (ch == "^") {
			cout << (x ^ y) << endl;
		} else {
			cout << "wrong input, please try again." << endl;
		}
	}//*/
	
	cout << "input number N than calculate N!\n"
		<< "notice: the digit of result must lessthan " 
		<< big_integer::limit_digits() << endl;

    while (cin >> N) {
        clock_t st = clock();
        x = 1;
        for (int i = 2; i <= N; ++i)
            x = x * i;
        clock_t et = clock();
		cout << x << endl;
		cout << "cost time " 
			<< (double)(et - st) / CLOCKS_PER_SEC
			<< "s." << endl;
    }//*/

    return 0;
}