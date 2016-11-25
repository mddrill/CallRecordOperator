/*

REMEMBER TO BREAK THIS FILE INTO 3 COMPONMENTS.
*/

#include <iostream>
#include <string>
#include <fstream>
#include "Call_class.h"

using namespace std;

//driver to test the functionality of your class.
int main()
{
	call_class MyClass;


	cout << MyClass << endl;

	call_class YourClass = MyClass;

	cout << "Test2: Testing add, double_size, process, and is_full() \n";
	MyClass.add();
	cout << "Finish TEST2\n\n\n\n";

	cout << "Test3: Testing operator-, serach, and is_empty\n";
	MyClass - "5617278899" - "9546321555" - "1234567890";
	cout << "Finish TEST3\n\n\n\n";

	cout << "Test4: Testing operator<<\n\n";
	ofstream stream("stats7_output.txt");
	stream << MyClass << endl;
	cout << MyClass << endl;
	cout << "Fist TEST4\n\n\n\n";
	char a;
	cin >> a;

	cout << "The destructor will be called automatically\n";


	cout << "YourClass" << endl;

	cout << YourClass << endl;
	char a;
	cin >> a;

	return 0;
}



