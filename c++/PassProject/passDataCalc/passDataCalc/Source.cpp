/*
Author: Andy Cox V
Date: 7/19/2018
Programming Language: C++
Compiler: */

#include <iostream>
#include <math.h>
#include <string>
using namespace std;

#define ALPHABET_SIZE 95 //All english characters typable on the US-English Keyboard.
#define QUIT_STRING "quit"

/*
This function calculates the most significant bit that would be needed
to support a number with n digits/characters.
ceil(Log2(ALPHABET_SIZE^n)).
Change of base will be used for Log2.
*/
double numBits(unsigned long n)
{
	return ceil(log(pow(ALPHABET_SIZE, n)) / log(2));
}

//Get number input and exit here.
unsigned long getLong(string statment)
{
	string tempString = "";
	unsigned long tempLong = 0;

	while(true)
	{
		cout << endl << statment << " <TYPE 'quit' TO QUIT AND PRESS ENTER TO CONFIRM> ";
		cin >> tempString;
		cin.ignore();

		if (tempString.compare(QUIT_STRING) == 0)
			exit(0);

		try
		{
			tempLong = stol(tempString);
			break;
		}
		catch (...)
		{
			cout << "ERROR: Invalid input!\n";
		}

	}
	return tempLong;
}

//Yes no / true false return.
bool yesno(string statment)
{
	char input = 0;

	while (true)
	{
		cout << endl << statment << " [Y/N] <PRESS ENTER TO CONFIRM>? ";
		input = cin.get();
		cin.ignore();

		input |= 0x20; //Set the input always to lowercase ASCII.

		if (input == 'y')
			return true;
		if (input == 'n')
			return false;
	}
}

int main(void)
{

	unsigned long loop = 0;

	while (true)
	{
	cout 
		<< "\nAndy Cox V\tpassDataCalc\t7/19/2018\n"
		<< "This program was designed to calculate memory data for a password generator program.\n"
		<< "First Colum Number of Character Places\nSecond Colum Number of Possible Passwords\nThird Colum Bits of Memory Consumed\n";

		loop = getLong("Enter number of characters in password");

		if (yesno("Create list"))
			for (; loop > 0; loop--)
				cout << loop << "\t" << pow(ALPHABET_SIZE, loop) << "\t" << numBits(loop) << endl;
		else
			cout << loop << "\t" << pow(ALPHABET_SIZE, loop) << "\t" << numBits(loop) << endl;
	}
}