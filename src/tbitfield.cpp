// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{                                                    // 
    if (len < 0)                                     // если длина битового поля отрицательна
        throw                                        // выбрасываем
        length_error("Negative length");             // ошибку из функции 
    BitLen = len;                                    //
    MemLen = (len + 15) >> 4;                        // pMem[i] содержит 4 байта (16 бит).
    pMem = new TELEM[MemLen];                        //
    for (int i = 0; i < MemLen; i++)                 //
        pMem[i] = 0;                                 //
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{                                                    //
    BitLen = bf.BitLen;                              //
    MemLen = bf.MemLen;                              //
    pMem = new TELEM[MemLen];                        //
    for (int i = 0; i < MemLen; i++)                 //
        pMem[i] = bf.pMem[i];                        //
}                                                    //

TBitField::~TBitField() // деструктор
{                                                    //
    delete[]pMem;                                    // удаляем массив
    pMem = NULL;                                     // зануляем указатель
}                                                    //

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{                                                    //
    if ((n < 0) || (n >= BitLen))                    // если n не принадлежит
        throw                                        // полуинтервалу [0, BitLen)
        out_of_range("Out of range");                // выбрасываем из функции ошибку
    return n >> 4;                                   // 
}                                                    //

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{                                                    //
    return 1 << (n);                                 // сдвиг 1 на n битов влево
}                                                    //

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{                                                    //
  return BitLen;                                     //
}                                                    //

void TBitField::SetBit(const int n) // установить бит
{                                                    //
    if ((n < 0) || (n >= BitLen))                    // если n не принадлежит
        throw                                        // полуинтервалу [0, BitLen)
        out_of_range("Out of range");                // выбрасываем из функции ошибку
    pMem[GetMemIndex(n)] |= GetMemMask(n);           //
}                                                    //

void TBitField::ClrBit(const int n) // очистить бит
{                                                    //
    if ((n < 0) || (n >= BitLen))                    // если n не принадлежит
        throw                                        // полуинтервалу [0, BitLen)
        out_of_range("Out of range");                // выбрасываем из функции ошибку
    TELEM k = ~GetMemMask(n);                        //
    pMem[GetMemIndex(n)] &= k;                       //
}                                                    //

int TBitField::GetBit(const int n) const // получить значение бита
{                                                    //
    if ((n < 0) || (n >= BitLen))                    // если n не принадлежит
        throw                                        // полуинтервалу [0, BitLen)
        out_of_range("Out of range");                // выбрасываем из функции ошибку
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) >> n;
}                                                    //

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{                                                    //
    if (this != &bf)                                 // проверка на присваивание себя
    {                                                //
        BitLen = bf.BitLen;                          //
        MemLen = bf.MemLen;                          //
        delete[]pMem;                                //
        pMem = new TELEM[MemLen];                    //
        for (int i = 0; i < MemLen; i++)             //
            pMem[i] = bf.pMem[i];                    //
    }                                                //
    return *this;                                    //
}                                                    //

int TBitField::operator==(const TBitField &bf) const // сравнение
{                                                    //
    int tmp = 1;                                     //
    if (BitLen == bf.BitLen)                         // если длины битовых полей равны
    {                                                //
        for (int i = 0; i < MemLen; i++)             // 
            if (pMem[i] != bf.pMem[i])               // проводим проверку равенства элементов массивов
            {                                        //
                tmp = 0;                             //
                break;                               //
            }                                        //
    }                                                //
    else                                             //
        tmp = 0;                                     // если длина битовых полей не равны, однозначно имеем разницу
    return tmp;                                      //
}                                                    //

int TBitField::operator!=(const TBitField &bf) const // сравнение
{                                                    //
    int tmp = 1;                                     //
    if (BitLen != bf.BitLen)                         //
        tmp = 1;                                     //
    else                                             //
    {                                                //
        int k = 0;                                   //
        for (int i = 0; i < MemLen; i++)             //
            if (pMem[i] == bf.pMem[i])               //
                k++;                                 //
        if (k == MemLen)                             //
            tmp = 0;                                 //
    }                                                //
  return tmp;                                        //
}                                                    //

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{                                                    //
    int i = 0, n = BitLen;                           //
    if (n < bf.BitLen)                               // используем максимальную длину битового поля
        n = bf.BitLen;                               // из двух указанных для создания конечного
    TBitField tmp(n);                                // битового поля
    for (i; i < MemLen; i++)                         // начальное заполнение конечного БП
        tmp.pMem[i] = pMem[i];                       //
    for (i = 0; i < bf.MemLen; i++)                  // дизъюнкция tmp и bf
        tmp.pMem[i] |= bf.pMem[i];                   //
    return tmp;                                      //
}                                                    //

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{                                                    //
    int i = 0, n = BitLen;                           //
    if (n < bf.BitLen)                               // используем максимальную длину битового поля
        n = bf.BitLen;                               // из двух указанных для создания конечного
    TBitField tmp(n);                                // битового поля
    for (i; i < MemLen; i++)                         // начальное заполнение конечного БП
        tmp.pMem[i] = pMem[i];                       //
    for (i = 0; i < bf.MemLen; i++)                  // конъюнкция tmp и bf
        tmp.pMem[i] &= bf.pMem[i];                   //
    return tmp;                                      //
}                                                    //

TBitField TBitField::operator~(void) // отрицание
{                                                    //
    int n = BitLen;                                  //
    TBitField tmp(n);                                //
    for (int i = 0; i < MemLen; i++)                 // поэлементная инвертация
        tmp.pMem[i] = ~pMem[i];                      // массива pMem
    return tmp;                                      //
}                                                    //

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{                                                    //
    int i = 0;                                       //
    char c;                                          //
    do                                               //
    {                                                //
        istr >> c;                                   //
    } while (c != ' ');                              //
    while (1)                                        //
    {                                                //
        if (c == '0')                                //
            bf.ClrBit(i++);                          //
        else if (c == '1')                           //
            bf.SetBit(i++);                          //
        else                                         //
            break;                                   //
    }                                                //
    return istr;                                     //
}                                                    //

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{                                                    //
    int n = bf.GetLength();                          //
    for (int i = n - 1; i >= 0; i--)                 //
        if (bf.GetBit(i))                            //
            ostr << "1";                             //
        else                                         //
            ostr << "0";                             //
    return ostr;                                     //
}                                                    //