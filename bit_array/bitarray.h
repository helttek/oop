﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

class BitArray {
private:
    std::vector<unsigned char> arr;

    int numBits;

    int numBytes;

    //Calculates the number of bytes needed to store n bits.
    static int CalcBytes(int n);

    //Returns the lesser of the two numbers.
    static int Min(int a, int b);

    //Counts the amount of "1"s in a byte
    static int CountOnes(unsigned char a, int end);

    //Converts byte to string
    static std::string ByteToString(unsigned char a, int n);
public:
    //Constructs an empty bit array
    BitArray();

    //Does nothing because vector is destroyed automatically.
    ~BitArray();

    //Конструирует массив, хранящий заданное количество бит.
    //Первые sizeof(long) бит можно инициализровать с помощью параметра value.
    explicit BitArray(int num_bits, unsigned long value = 0);

    //Creates a copy of bit array b.
    BitArray(const BitArray& b);


    //Обменивает значения двух битовых массивов.
    void swap(BitArray& b);

    //Initializes with bit array "b", if the sizes of the arrays are equal.
    BitArray& operator=(const BitArray& b);


    //Изменяет размер массива. В случае расширения, новые элементы
    //инициализируются значением value.
    void resize(int num_bits, bool value = false);

    //Очищает массив.
    void clear();

    //Добавляет новый бит в конец массива. В случае необходимости
    //происходит перераспределение памяти.
    void push_back(bool bit);


    //Битовые операции над массивами.
    //Работают только на массивах одинакового размера.
    //Обоснование реакции на параметр неверного размера входит в задачу.
    BitArray& operator&=(const BitArray& b);

    BitArray& operator|=(const BitArray& b);

    BitArray& operator^=(const BitArray& b);

    //Битовый сдвиг с заполнением нулями.
    BitArray& operator<<=(int n);

    BitArray& operator>>=(int n);

    BitArray operator<<(int n) const;

    BitArray operator>>(int n) const;


    //Устанавливает бит с индексом n в значение val.
    BitArray& set(int n, bool val = true);

    //Заполняет массив истиной.
    BitArray& set();

    //Устанавливает бит с индексом n в значение false.
    BitArray& reset(int n);

    //Заполняет массив ложью.
    BitArray& reset();

    //true, если массив содержит истинный бит.
    bool any() const;

    //true, если все биты массива ложны.
    bool none() const;

    //Битовая инверсия
    BitArray operator~() const;

    //Подсчитывает количество единичных бит.
    int count() const;


    //Возвращает значение бита по индексу i.
    bool operator[](int i) const;

    int size() const;

    bool empty() const;

    //Возвращает строковое представление массива.
    std::string to_string() const;
};

bool operator==(const BitArray& a, const BitArray& b);

bool operator!=(const BitArray& a, const BitArray& b);

BitArray operator&(const BitArray& b1, const BitArray& b2);

BitArray operator|(const BitArray& b1, const BitArray& b2);

BitArray operator^(const BitArray& b1, const BitArray& b2);