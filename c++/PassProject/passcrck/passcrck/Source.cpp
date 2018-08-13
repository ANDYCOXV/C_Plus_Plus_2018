/*
Author: Andy Cox V
Date: 7/23/2018
Programming Language: C++
Compiler Used: Microsoft Visual C++ 2017
This program uses an algorithm I designed to crack passwords.
I made sure to not have any variables that need to constantly have memory allocated when it came to the actual computations.
You wont find any for(unsigned __int64... they will be a predefined variable.
This version of C++ does not support inline assembly I was planning on pushing and poping magintude before the while loop.
Below are segments of old code.
const unsigned __int64 lookup[9] = { 95, 9025, 857375, 81450625, 7737809375, 735091890625, 69833729609375, 6634204312890625, 630249409724609375 };
magnitude = 1; //Leave this here unknow error when set after if statment.
Cannot take log of zero and log(1) = 0 issue with magnitude! Therefore bitwise OR by 2.
Bitwise ORing by two prevents a change in magnitude by addition and allows 0 and 1 to be valid inputs.
if (number) //Will not run if number = 0.
	magnitude += (unsigned __int64)(log(number) * LN95); //Aquire number of digits in the number NOTE: log(x) = LN(x).
auto startTime = chrono::high_resolution_clock::now(); //Start computations clock.
if (number == 9025)
{
cout << (long)chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - startTime).count();
cout << "\nMAG: " << magnitude << endl;
getchar();
exit(0);
}
#define LN95 0.219593112375185938907641221455835648102908705918071285967 //1/(Natural Log of 95) used in change of base.
*/

#include <iostream>
using namespace std;

#define ALPHABET_SIZE 95 //Number of digits in this base.
#define ASCII_CONVERT 0x20 //' ' Space character first printable ASCII character.
#define MAX64_ALPHABET 630249409724609375 //95^9 the largest number with a power of 95 that can fit into a 64-bit number.4

/*Exit returns:
	0=Success
	1=Out of memory error
	2=Invalid argument error*/
int main(int argc, char* argv[])
{
	unsigned __int64 *data;; //Holds a string of 64-bit unsigned integers for memory use.
	unsigned __int64 number = 0; //Used as temporary storage.
	unsigned __int64 dataSize = 0; //Stores number of variables that can be used to crack passwords.
	unsigned __int64 magnitude = 1; //Determines how many digits will be used to represent a number.
	unsigned __int64 element = 0; //Represents current element in the data array.
	unsigned __int64 power = ALPHABET_SIZE; //Used as temporary storage like a lookup table.
	unsigned __int64 elementLoop = 0; //Used for the for loops to save time so temp vars would not have to be allocated.
	unsigned __int64 printLoop = 0; //Used in a while loop for printing the strings.

	if (argc != 2) //argc will always be 1 because the executbale name is an argument.
	{
		cout << "\npasscrck\tAndy Cox V\t7/23/2018\n"
			<< "This program uses a heuristic algorithm to compute password combinations. "
			<< "It will cycle through all 95 typable characters on the US-English qwerty keyboard until all allocated memory is exausted. "
			<< "ARGUMENT is an unsigned 64-bit integer which specifies the ammount of memory to allocate for passcrck. "
			<< "Each unit of memory that is specified by ARGUMENT allocates nine characters of memory. "
			<< "For example, if ARGUMENT was set to 2, every password between 1-18 characters would be generated. "
			//<< "The ASCII character 0x0A is used as a break between the generated passwords.\n"
			<< "Standard out is flushed (fflush(stdout)) after each password is generated.\n"
			<< "Exit Codes:\n"
			<< "\t* 0 - Exit on success and completion\n"
			<< "\t* 1 - Exit on \"Not enough memory allocatable!\" error\n"
			<< "\t* 2 - Exit on \"Invalid argument!\" error\n"
			<< "Usage: passcrck <ARGUMENT>\n";
		return 0; //Using returns in main are equivelent to using exit().
	}

	dataSize = (unsigned __int64)strtoull(argv[1], NULL, 0); //Final argument of 0 lets stroull decide what base to use.

	if (!dataSize) //Occurs if dataSize = 0 or is an invalid string.
	{
		cout << "Invalid argument!\n";
		return 2;
	}

	data = (unsigned __int64*)calloc(dataSize, sizeof(unsigned __int64)); //Set aside required memory and set to zero.

	if (!data) //Occurs if a continous block of memory cannot be allocated to passcrck.
	{
		cout << "Not enough memory allocatable!\n";
		return 1;
	}

	while (element < dataSize)
	{
		for (elementLoop = 0; elementLoop <= element ; elementLoop++) //Password gets processed and printed here.
		{
			number = data[elementLoop]; //Done to prevent having to reaccess an array throught the loop.

			if (power <= number)
			{
				power *= ALPHABET_SIZE;
				magnitude++;
			}

			printLoop = magnitude;
			while(printLoop--)
			{
				putchar((number % ALPHABET_SIZE) + ASCII_CONVERT); //Add 0x20 to make it into an ASCII character
				number /= ALPHABET_SIZE;
			}
		}
		putchar('\n'); //Used to represent a break before the next password also flushes line buffered outputs.

		//Magic happens here with the increcement of the password.
		data[0]++;

		if (data[0] == MAX64_ALPHABET) //Used to save on cycles from for loop.
			for (elementLoop = 0; elementLoop < dataSize; elementLoop++)
				if (data[elementLoop] == MAX64_ALPHABET)
				{
					data[elementLoop] = 0;
					if (element == elementLoop)
					{
						element++;
						if(element == dataSize)
							goto jump1; //goto's are bad, but I belive this one will save on execution time.
					}
					data[elementLoop + 1]++; //Keep this here. The above goto will also protect from reaching out of the calloc array.
				}
		jump1:;
	}

	free(data);
	return 0;
}