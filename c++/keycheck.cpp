#include <iostream>
using namespace std; //Keeps the programmer from having to use std:: every time.

//Use stty raw -echo to turn off buffering then use clear to clear the screen!

#define QUIT '`' //Character to quit the program with.

string consoleReturn(void)
{
	return "\r\n";
}

int main(void)
{
	char input = 0;
	string sampleString = "";
	double var = 0;

	cout << "Running: Press " << QUIT << " to quit." << consoleReturn();

	while((input = getchar()) != QUIT) //NOTE: getchar when stty raw -echo is executed acts like getch().
	{
		switch(input)
		{
			case '\r': //Process string.
				cout << consoleReturn() << "Size of String: " << sampleString.size() << consoleReturn();
				cout << "Returned String: " << sampleString << consoleReturn();

				try
				{
					var = stod(sampleString);
					cout << "The double is: " << var << consoleReturn();
				}
				catch(...)
				{
					cout << "The string is not a double!" << consoleReturn();
				}

				cout << consoleReturn();

				sampleString = "";
				break;

			default: //Default display input and store in string.
				sampleString += input;
				putchar(input);
				break;
		}
		fflush(stdout);
	}
	exit(0);
}