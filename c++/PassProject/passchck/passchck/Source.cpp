/*
Author: Andy Cox V
Date: 7/25/2018
Programming Language: C++
Compiler Used: Microsoft Visual C++ 2017
This is a lightweight userfriendly application used to run passcrck without having to use the command console and does evaluaitons.
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>
#include <conio.h> //Used for kbhit() unique to Microsoft Windows.

using namespace std;

//Returns 0 on success, returns 1 on error.
int main(void)
{
	FILE *pipe;
	string cmd = "passcrck.exe ";
	string inputString = "";
	unsigned long long dataSize = 0;
	unsigned int count = 0;
	unsigned int passwordLength = 0;
	double time = 0;

	cout << "passchck\tAndy Cox V\t7/25/2018\n"
		<< "This program evaluates passcrck's output and write the passcrck's status to stdout. "
		<< "Every new iteration will have listed the time in milliseconds, number of passwords generated, and the size in character of the passwords generated."
		<< "Every advancement occurs when all possible passwords for the standard US-English qwerty keyboard is generated. "
		<< "passchck retunrs 0 on successful termination and 1 on error. "
		<< "This specific executable was designed for the intent to run on Microsoft Windows\n\n"
		<< "Usage: Place this executable in the same directory as passcrck.\n";

	cout << "\nPlease specify passcrck memory.\nThe value of this number times 9 is the amount of character used in the password: ";
	getline(cin, inputString);

	dataSize = (unsigned __int64)strtoull(inputString.c_str(), NULL, 0); //Final argument of 0 lets stroull decide what base to use.

	if (!dataSize) //Occurs if dataSize = 0 or is an invalid string.
	{
		cout << "Invalid argument for memory size!\n";
		return 1;
	}

	if (fopen_s(&pipe, "passcrck.exe", "r"))
	{
		cout << "passcrck does not exist in this directory "
			<< "please place this executable in the same directory as passcrck.\n";
		return 1;
	}

	cmd.append(inputString);
	
	cout << "Instructions from console to passcrck: " << cmd << endl;

	pipe = _popen(cmd.c_str(), "rb");

	cout << "\nProcessing...\nPress <CTRL+C> to terminate." << endl << endl;
	chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now(); //Start computations clock.
	while(true) //Was going to use kbhit() that is Microsoft Windows specific, but polling is very very SLOW!
	{
		while (fgetc(pipe) != '\n')
			count++;

		if (count > passwordLength)
		{
			time = (double)chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - startTime).count();
			passwordLength = count;
			//Have to minus 1 because in reality it just started passwords of passwordLength size.
			cout
				<< "Milliseconds: " << time << endl
				<< "Passwords Generated: " << pow(95, passwordLength - 1) << endl
				<< "Password Size: " << passwordLength - 1 << endl << endl;
		}
		count = 0;
	}

	//_pclose(pipe); Will never reach here.
	
	return 0;
}