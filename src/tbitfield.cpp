// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw 1;
	BitLen = len;
	MemLen = (len - 1) / F_SIZE + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;

	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= BitLen || n < 0)
		throw 1;
	return n / F_SIZE;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n >= BitLen || n < 0)
		throw 1;
	return 1 <<(n % F_SIZE);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= BitLen || n < 0)
		throw 1;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= BitLen || n < 0)
		throw 1;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen || n < 0)
		throw 1;
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;

	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;

	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return 0;
	}

	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;

	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return 1;
	}

	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len;
	TBitField res(0);
	if (BitLen > bf.BitLen)
	{
		res = *this;
		len = bf.MemLen;
	}
	else
	{
		res = bf;
		len = MemLen;
	}

	for (int i = 0; i < len; i++)
	{
		res.pMem[i] = pMem[i] | bf.pMem[i];
	}

	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	if (BitLen > bf.BitLen)
		len = BitLen;
	else
		len = bf.BitLen;
	TBitField res(len);

	if (MemLen < bf.MemLen)
		len = MemLen;
	else
		len = bf.MemLen;

	for (int i = 0; i < len; i++)
	{
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}

	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);

	for (int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = ~res.pMem[i];
	}

	if (res.BitLen % F_SIZE != 0)
	{
		TELEM x = 1;

		for (int i = 0; i < res.BitLen % F_SIZE - 1; i++)
		{
			x = x << 1;
			x += 1;
		}

		res.pMem[MemLen - 1] = res.pMem[MemLen - 1] & x;
	}

	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string in;
	istr >> in;
	TBitField res(in.size());

	for (int i = 0; i < res.GetLength(); i++)
	{
		if (in[i] == '0')
		{
			res.ClrBit(i);
		}
		else
		{
			res.SetBit(i);
		}
	}

	bf = res;

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
	{
		ostr << bf.GetBit(i);
	}

	return ostr;
}