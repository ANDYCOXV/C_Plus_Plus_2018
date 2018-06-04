#include <iostream>
#include <math.h>
using namespace std;

/*
Container class
Stores the name of the container and its volume.
*/
class Container
{
	private: string name = ""; //Name for the container.
	private: double volume = 0; //Volume of the container.

	public: void setName(string name)
	{
		this->name = name;
	}

	public: string getName(void)
	{
		return name;
	}

	public: void setVolume(double volume)
	{
		this->volume = volume;
	}

	public: double getVolume(void)
	{
		return volume;
	}
};

class Cube : public Container
{
	private: double edge = 0;

	public: string computeEdge(void)
	{
		edge = cbrt(getVolume());
		return "Edge computed!";
	}

	public: string computeEdge(double edge)
	{
		this->edge = cbrt(edge);
		return "Custom edge computed!";
	}

	public: double getEdge(void)
	{
		return edge;
	}
};

int main()
{
	Cube boxes[3];

	boxes[0].setVolume(64);
	boxes[0].setName("BOX#1");
	boxes[1].setVolume(512);
	boxes[1].setName("BOX#2");
	boxes[2].setVolume(8);
	boxes[2].setName("BOX#3");

	for(int i = 0 ; i < 3 ; i++)
	{
		cout << "Name of Container: " << boxes[i].getName() << endl;
		cout << "Volume of Container: " << boxes[i].getVolume() << endl;
		cout << "Variable Computation Status: " << boxes[i].computeEdge() << endl;
		cout << "Variable Size: " << boxes[i].getEdge() << endl << endl;
	}

	exit(0);
}