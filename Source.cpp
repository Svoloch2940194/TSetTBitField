#include "tbitfield.h"
#include "Tset.h"

int main()
{
	TSet x(100);
	try {
		x.DelElem(-1);
	}
	catch (out_of_range x) { cout << x.what() << endl; }
	for (int i = 0; i < 100; ++i) x.InsElem(i);
	x.DelElem(0);
	x.DelElem(1);
	for (int i = 0; i < 100; ++i)
	{
		if (x.IsMember(i))
		{
			for (int j = i * i; j < 100; j += i) x.DelElem(j);
		}
	}
	cout << x << endl;
}