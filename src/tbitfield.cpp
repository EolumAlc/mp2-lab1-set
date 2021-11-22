// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len) {
    if (len < 0) {
        throw "Negative len in bf";
    }

    BitLen = len;
    MemLen = 1;
    MemLen = (BitLen % BITS_IN_ONE_MEM == 0) ? MemLen *= (BitLen / BITS_IN_ONE_MEM) : MemLen = MemLen * (BitLen /
                                                                                                         BITS_IN_ONE_MEM) +
                                                                                               1;
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
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n >= BitLen)) {
        throw "GetMemIndex";
    }
    return n / BITS_IN_ONE_MEM;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n >= BitLen)) {
        throw "GetMemMask";
    }
    return TELEM(1 << n);
//    return TELEM(1 << (n % BITS_IN_ONE_MEM - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen)) {
        throw "SetBit";
    }
    pMem[n / BITS_IN_ONE_MEM] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen)) {
        throw "ClrBit";
    }
    pMem[n / BITS_IN_ONE_MEM] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen)) {
        throw "GetBit";
    }
    return (pMem[n / BITS_IN_ONE_MEM] & GetMemMask(n)); //>> n;
}

// битовые операции

TBitField &TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.GetLength();
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    bool f = true;
    if (this != &bf) {
        if (GetLength() == bf.GetLength()) {
            f = true;
        } else {
            f = false;
        }
        if (f) {
            for (int i = 0; i < GetLength() && f; ++i) {
                if (GetBit(i) == bf.GetBit(i)) {
                    f = true;
                } else {
                    f = false;
                }
            }
        }
    }
    return f;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField tmp(1);
    if (MemLen > bf.MemLen){
        tmp = *this;
        for (int i = 0; i < bf.MemLen; ++i) {
            tmp.pMem[i] |= bf.pMem[i];
        }
    }
    else {
        tmp = bf;
        for (int i = 0; i < MemLen; ++i) {
            tmp.pMem[i] |= pMem[i];
        }
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField tmp(1);
//    if (MemLen > bf.MemLen){
    if (BitLen > bf.BitLen){
        tmp = *this;
        for (int i = 0; i < bf.MemLen; ++i) {
            tmp.pMem[i] &= bf.pMem[i];
        }
    }
    else {
        tmp = bf;
        for (int i = 0; i < MemLen; ++i) {
            tmp.pMem[i] &= pMem[i];
        }
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(this->BitLen);
    for (int i = 0; i < BitLen; ++i) {
        if (!GetBit(i)){
            tmp.SetBit(i);
        }
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.MemLen; ++i) {
        istr >> bf.pMem[i];
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.MemLen; ++i) {
        ostr << bf.pMem[i] << ' ';
    }
    return ostr;
}
