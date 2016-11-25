#include "Call_class.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
/************************************************************************************************************************************/
//Name: default constructor
//Precondition: call_class is not defined
//Postcondition: call_class is defined
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record,
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	count = 0;
	size = 5;
	ifstream in;
	in.open("callstats_data.txt");
	call_DB = new call_record[size];

	while (!in.eof())
	{
		if (count >= size) {
			double_size();
		}
		cout << count << endl;
		in >> call_DB[count].firstname
			>> call_DB[count].lastname
			>> call_DB[count].cell_number
			>> call_DB[count].relays
			>> call_DB[count].call_length;
		count++;
		//NOTE: THE OTHER FIELDS (net_cost, tax_rate, call_tax, total_cost) WILL BE DETERMINE IN PROCESS....
	}
	in.close();

}

/***********************************************************************************************************************************/
//Name: is_empty
//Precondition: an instance of call_class is defined
//Postcondition: returns whether call_DB is empty
//Description: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full
//Precondition: an instance of call_class is defined
//Postcondition: returns whether call_DB is full
//Description: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	return count == size;
}

/************************************************************************************************************************************/
//Name: copy constructor
//Precondition: 
//Postcondition: 
//Decription: performs a deep copy.
/************************************************************************************************************************************/
call_class::call_class(const call_class & object)
{
	count = object.count;
	size = object.size;
	call_DB = new call_record[size];
	for (int i = 0; i < count; i++) {
		call_DB[i].firstname = object.call_DB[i].firstname;
		call_DB[i].lastname = object.call_DB[i].lastname;
		call_DB[i].cell_number = object.call_DB[i].cell_number;
		call_DB[i].relays = object.call_DB[i].relays;
		call_DB[i].call_length = object.call_DB[i].call_length;
		call_DB[i].net_cost = object.call_DB[i].net_cost;
		call_DB[i].tax_rate = object.call_DB[i].tax_rate;
		call_DB[i].call_tax = object.call_DB[i].call_tax;
		call_DB[i].total_cost = object.call_DB[i].total_cost;
	}
}



/**********************************************************************************************************************************/
//Name: search
//Precondition: 
//Postcondition: 
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key)
{
	for (int i = 0; i < count; i++) {
		if (call_DB[i].cell_number == key) {
			return i;
		}
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: add
//Precondition: instance of call_class has been defined
//Postcondition:
//Decription: adds a call_record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB. The user
//            is prompted to enter the firstname, lastname, cell number, relays and call length.
/********************************************************************************************************************************/
void call_class::add()
{
	if (is_full()) {
		double_size();
	}
	else {
		cout << "What is the name of the person who made this call? (first last)" << endl;
		cin >> call_DB[count].firstname >> call_DB[count].lastname;
		cout << "What was their phone number?" << endl;
		cin >> call_DB[count].cell_number;
		cout << "How many relays did this call take?" << endl;
		cin >> call_DB[count].relays;
		cout << "How long was this call? (in minutes)" << endl;
		cin >> call_DB[count].call_length;
		count++;
	}
	cout << "done" << endl;
}
/********************************************************************************************************************************/
//Name: remove
//Precondition:
//Postcondition:
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
void call_class::remove(const string key)
{
	int loc = search(key);
	if (loc != -1) {
		for (int i = loc; i < count - 1; i++) {
			cout << i << endl;
			call_DB[i] = call_DB[i + 1];
		}
		count--;
		call_record *temp = new call_record[size];
		for (int i = 0; i < count; i++)
		{
			temp[i] = call_DB[i];
		}
		delete[] call_DB;
		call_DB = temp;
		remove(key);
	}
}
/********************************************************************************************************************************/
//Name: operator-
//Precondition: 
//Postcondition: 
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
call_class & call_class::operator-(const string key)
{
	remove(key);
	return *this;
}


/******************************************************************************************************************************/
//Name: double_size
//Precondition: and instance of call_class has been defined
//Postcondition: size of call_Db is doubled
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: call_class has been defined
//Postcondition:
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
{
	for (int i = 0; i < count; i++) {
		call_DB[i].net_cost = call_DB[i].relays / 50.0 * .40 * call_DB[i].call_length;

		if (0 <= call_DB[i].relays && call_DB[i].relays <= 5) {
			call_DB[i].tax_rate = 0.01;
		}
		else if (6 <= call_DB[i].relays && call_DB[i].relays <= 11) {
			call_DB[i].tax_rate = 0.03;
		}
		else if (12 <= call_DB[i].relays && call_DB[i].relays <= 20) {
			call_DB[i].tax_rate = 0.05;
		}
		else if (21 <= call_DB[i].relays && call_DB[i].relays <= 50) {
			call_DB[i].tax_rate = 0.08;
		}
		else {
			call_DB[i].tax_rate = 0.12;
		}
		call_DB[i].call_tax = call_DB[i].tax_rate *call_DB[i].net_cost;

		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
	}

}

/****************************************************************************************************************************/
//Name: operator<<
//Precondition: 
//Postcondition: 
//Decription: Overloading operator<< as a friend function. Prints every field of every call_record in call_DB 
//                   formatted to the screen and a file called "stats7_output.txt".
/***************************************************************************************************************************/
ostream & operator<<(ostream & out, call_class & Org)
{
	for (int i = 0; i<Org.count; i++)
	{
		out << Org.call_DB[i].firstname << "  " << Org.call_DB[i].lastname
			<< "  " << Org.call_DB[i].relays << "  " << Org.call_DB[i].cell_number
			<< "  " << Org.call_DB[i].call_length << endl;
	}

	//Put code to OPEN and CLOSE an ofstream and print to the file "stats7_output.txt".


	return out;  //must have this statement
}

/****************************************************************************************************************************/
//Name: destructor
//Precondition: an instance of call class has been defined
//Postcondition: that instance will no longer be defined
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	delete[] call_DB;
}