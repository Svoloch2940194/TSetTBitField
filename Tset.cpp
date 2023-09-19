#include "Tset.h"

TSet::TSet()
{
	MaxPower = 0;
}

TSet::TSet(int np)
{
	MaxPower = np;
	TBitField x(np);
	BitField = x;
}

TSet::TSet(const TSet& s)
{
	MaxPower = s.GetMaxPower();
	TBitField x(MaxPower);
	BitField = x;
}

TSet::TSet(const TBitField& bf)
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower() const
{
	return MaxPower;
}

void TSet::InsElem(const int Elem)
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
	BitField.ClrBit(Elem);
}

int TSet::IsMember(const int Elem) const
{
	return BitField.GetBit(Elem) == 1;
}

int TSet::operator== (const TSet& s) const
{
	return MaxPower == s.GetMaxPower() && BitField == s.BitField;
}

int TSet::operator!= (const TSet& s) const
{
	return !(this->operator==(s));
}

TSet& TSet::operator=(const TSet& s)
{
	MaxPower = s.GetMaxPower();
	BitField = s.BitField;
	return *this;
}

TSet TSet::operator+(const int Elem)
{
	TSet x(MaxPower);
	for (int i = 0; i < MaxPower; ++i)
	{
		if (IsMember(i) || i == Elem) x.InsElem(i);
	}
	return x;
}

TSet TSet::operator- (const int Elem)
{
	TSet x(MaxPower);
	for (int i = 0; i < MaxPower; ++i)
	{
		if (IsMember(i) && i != Elem) x.InsElem(i);
	}
	return x;
}

TSet TSet::operator+ (const TSet& s)
{
	TSet x = s;
	x.BitField = this->BitField | s.BitField;
	return x;
}

TSet TSet::operator* (const TSet& s)
{
	TSet x = s;
	x.BitField = this->BitField & s.BitField;
	return x;
}

TSet TSet::operator~ (void)
{

	TSet x(MaxPower);
	for (int i = 0; i < MaxPower; ++i)
	{
		if (!IsMember(i)) x.InsElem(i);
	}
	return x;
}

istream& operator>> (istream& istr, TSet& bf)
{
	for (int i = 0; i < bf.MaxPower; ++i)
	{
		bool x;
		cin >> x;
		if (x) bf.InsElem(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& bf)
{
	for (int i = 0; i < bf.MaxPower; ++i)
	{
		if (bf.IsMember(i)) cout << 1;
		else cout << 0;
	}
	return ostr;
}