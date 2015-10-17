// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
 
#include "tbitfield.h"

#define BpMem (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
    if (len < 1)
        throw
        length_error("Negative length");
    BitLen = len;
    MemLen = (len + BpMem - 1) / BpMem;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() // деструктор
{
    delete[]pMem;
    pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n >= BitLen))
        throw
        out_of_range("Out of range");
    return n / BpMem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n % BpMem);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen))
        throw
        out_of_range("Out of range");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen))
        throw
        out_of_range("Out of range");
    TELEM k = ~GetMemMask(n);
    pMem[GetMemIndex(n)] &= k;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen))
        throw
        out_of_range("Out of range");
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0) ? 0 : 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        delete[]pMem;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen; i++)
        if ((pMem[i]) != (bf.pMem[i]))
        {
            return 0;
        }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 1;
    
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 1;
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int i = 0, n = BitLen;
    if (n < bf.BitLen)
        n = bf.BitLen;
    TBitField tmp(n);
    for (i; i < MemLen; i++)
        tmp.pMem[i] = pMem[i];
    for (i = 0; i < bf.MemLen; i++)
        tmp.pMem[i] |= bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int i = 0, n = BitLen;
    if (n < bf.BitLen)
        n = bf.BitLen;
    TBitField tmp(n);
    for (i; i < MemLen; i++)
        tmp.pMem[i] = pMem[i];
    for (i = 0; i < bf.MemLen; i++)
        tmp.pMem[i] &= bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    int n = BitLen;
    TBitField tmp(n);
    for (int i = 0; i < MemLen - 1; i++)
        tmp.pMem[i] = ~pMem[i];
    TELEM f = 0;
    for (int i = 0; i < (BitLen % BpMem); i++)
        f |= GetMemMask(i);
    tmp.pMem[MemLen - 1] = (~pMem[MemLen - 1]) & f;
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int i = 0;
    char c;
    do
    {
        istr >> c;
    } while (c != ' ');
    while (1)
    {
        if (c == '0')
            bf.ClrBit(i++);
        else if (c == '1')
            bf.SetBit(i++);
        else
            break;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = bf.BitLen - 1; i >= 0; i--)
        if (bf.GetBit(i))
            ostr << "1";
        else
            ostr << "0";
    return ostr;
}
