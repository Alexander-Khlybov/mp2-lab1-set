// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp): BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}
 
TSet::operator TBitField()
{
    TBitField temp(BitField);
    return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента из множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s)
    {
        MaxPower = s.GetMaxPower();
        BitField = s.BitField;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet b(BitField | s.BitField);
    return b;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < MaxPower)
    {
        TSet s(BitField);
        s.InsElem(Elem);
        return s;
    }
    else if (Elem > 0)
    {
        TSet s(Elem);
        s.BitField = s.BitField & BitField;
        s.InsElem(Elem);
        return s;
    }
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet s(BitField);
    s.DelElem(Elem);
    return s;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet b(BitField & s.BitField);
    return b;
}

TSet TSet::operator~(void) // дополнение
{
    TSet s(~BitField);
    return s;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int tmp;
    char c;
    do
    {
        istr >> c;
    } while (c != '{');
    do
    {
        istr >> tmp;
        s.InsElem(tmp);
        do
        {
            istr >> c;
        } while ((c != ',') && (c != '}'));
    } while (c != '}');
    return istr;
}                                                           //

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    char c = ' ';
    ostr << "{";
    int n = s.GetMaxPower();
    for (int i = 0; i < n; i++)
    {
        if (s.IsMember(i))
        {
            ostr << c << ' ' << i;
            c = ',';
        }
    }
    ostr << " }";
    return ostr;
}