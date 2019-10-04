// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem >= MaxPower || Elem < 0)
		throw 1;
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem >= MaxPower || Elem < 0)
		throw 1;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem >= MaxPower || Elem < 0)
		throw 1;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;

	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField == s.BitField)
		return 1;
	return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField == s.BitField)
		return 0;
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField bf = BitField | s.BitField;

	TSet res(bf);

	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem >= MaxPower || Elem < 0)
		throw 1;
	TSet res(*this);

	res.InsElem(Elem);

	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem >= MaxPower || Elem < 0)
		throw 1;
	TSet res(*this);

	res.DelElem(Elem);

	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField bf = BitField & s.BitField;

	TSet res(bf);

	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(*this);

	res.BitField = ~BitField;

	return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	TBitField bf(s.GetMaxPower());

	istr >> bf;

	TBitField res(bf);

	s = res;

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		ostr << s.IsMember(i);
	}

	return ostr;
}
