#include "tbitfield.h"

int TBitField::GetMemIndex(const int n) const 
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const
{
	return 1 << (n % (sizeof(TELEM) * 8));
}

TBitField::TBitField() noexcept
{
	BitLen = 0;
	MemLen = 0;
	pMem = nullptr;
}

TBitField::TBitField(int len)
{
	if (len < 0) throw out_of_range("Size should be greater than zero");
	if (len == 0) TBitField();
	BitLen = len;
	MemLen = GetMemIndex(BitLen) + 1 * (BitLen % (sizeof(TELEM) * 8) != 0);
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; ++i) pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf)
{
	BitLen = bf.GetLength();
	MemLen = GetMemIndex(BitLen) + 1 * (BitLen % (sizeof(TELEM) * 8) != 0); // optimisation
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; ++i) pMem[i] = 0;

	for (int i = 0; i < BitLen; ++i)
	{
		if (bf.GetBit(i)) pMem[GetMemIndex(i)] |= GetMemMask(i);
	}
}

TBitField::~TBitField()
{
	delete pMem;
}

int TBitField::GetLength() const 
{
	return BitLen;
}

void TBitField::SetBit(const int n)
{
	if (n < 0) throw out_of_range("index should be greater or eqals than zero");
	if (n >= GetLength()) throw out_of_range("index should be less than length of erray");
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
	if (n < 0) throw out_of_range("index should be greater or eqals than zero");
	if (n >= GetLength()) throw out_of_range("index should be less than length of erray");
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
	if (n < 0) throw out_of_range("index should be greater or eqals than zero");
	if (n >= GetLength()) throw out_of_range("index should be less than length of erray");
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

int TBitField::operator==(const TBitField& bf) const
{
	if (BitLen == bf.GetLength())
	{
		for (int i = 0; i < BitLen; ++i)
		{
			if (GetBit(i) != bf.GetBit(i)) return false;
		}
		return true;
	}
	return false;
}

int TBitField::operator!=(const TBitField& bf) const
{
	return !(this->operator==(bf));
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	BitLen = bf.GetLength();
	MemLen = BitLen / (sizeof(TELEM) * 8) + 1 * (BitLen % (sizeof(TELEM) * 8) != 0);

	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; ++i) pMem[i] = 0;

	for (int i = 0; i < BitLen; ++i)
	{
		if (bf.GetBit(i)) pMem[GetMemIndex(i)] |= GetMemMask(i);
	}

	return *this;
}

TBitField TBitField::operator|(const TBitField& bf)
{
	TBitField x(max(bf.GetLength(), this->GetLength()));

	if (x.GetLength() == this->GetLength()) x = *this;
	else x = bf;

	for (int i = 0; i < min(bf.GetLength(), this->GetLength()); ++i) if (bf.GetBit(i) || this->GetBit(i)) x.SetBit(i);

	return x;
}

TBitField  TBitField::operator&(const TBitField& bf)
{
	TBitField x(max(bf.GetLength(), this->GetLength()));

	for (int i = 0; i < min(bf.GetLength(), this->GetLength()); ++i)
	{
		if (bf.GetBit(i) && this->GetBit(i)) x.SetBit(i);
	}

	return x;
}

TBitField TBitField::operator~()
{
	TBitField x(this->GetLength());
	for (int i = 0; i < this->GetLength(); ++i)
	{
		if (!(this->GetBit(i))) x.SetBit(i);
	}

	return x;
}

istream& operator>> (istream& istr, TBitField& bf)
{
	for (int i = 0; i < bf.BitLen; ++i)
	{
		bool x;
		cin >> x;
		if (x) bf.SetBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf)
{
	for (int i = 0; i < bf.BitLen; ++i)
	{
		if (bf.GetBit(i)) cout << 1;
		else cout << 0;
	}
	return ostr;
}