#include "tbitfield.h"
#include "Tset.h"

int main()
{
	TBitField x(80);
	TBitField y(80);
	/*
	for (int i = 0; i < 80; ++i)
	{
		if (!(i % 2)) x.SetBit(i);
	}

	for (int i = 0; i < 80; ++i)
	{

		if (!(i % 2)) y.ClrBit(i);
		else y.SetBit(i);
	}
	*/
	TBitField z(80);

	TSet xx(80);

	for (int i = 0; i < 80; ++i)
	{
		if (!(i % 2)) xx.InsElem(i);
	}

	TSet yy = ~xx;

	//z = x | y;
	cout << xx << endl;
	cout << yy << endl;
	//cout << xx * yy << endl;
	//cout << xx << endl;
	cout << ~(xx * yy) << endl;
	cout << (xx == xx) << endl;
	//cout << y << endl;
	//cout << z << endl;
	//z = x & ~x;
	//cout << z << endl;
}