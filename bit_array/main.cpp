/*
����� �������� � ������� ��������: http://en.wikipedia.org/wiki/Bit_array.

������ ������������ ���������� �������� �������: http://www.boost.org/doc/libs/1_51_0/libs/dynamic_bitset/dynamic_bitset.html

������:
����������� ������� ������ � �������� ����������� (��. ������ ������������).
- ��������� ����������������� ��������� ����� ������ �� �����, ������������ � ������������ �����������.
- �������� ����-����� �� ��� ��������� ������ ������ � ������� ����� ������������������ ���������� (������������� Google Test Framework http://code.google.com/p/googletest/), ���� ��� ���� (�� ���������� �������������). ��������� � ������� �������� ���� ������� (������ ������� ���� ������ ����������� ���� �� ����� ������).
������������ ��������:
- ��� ��������� ���� ������ �������� ��������� �� ��������� �������������� �������� � ��������� �������, � ���������, �� ������������ ���������� �������. ������������ � �������������� ��������� ������ � ����� �������.
- �������������: ���������� ����� ������� �������������� �� �� ����������.
- �������������: ������� �������� ���������� ���������� ������. �������� � ����� �����������.

*/
#include "bitarray.h"
#include <limits.h>
#include <assert.h>

using namespace std;

void PrintArrays(BitArray a, BitArray b) {
    for (size_t i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    for (size_t i = 0; i < b.size(); i++) {
        cout << b[i] << " ";
    }
    cout << endl;
}

void PrintArray(BitArray a) {
    for (size_t i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    BitArray a(64, 7), b(64, 129);
    string c = a.to_string(), d = b.to_string();
    cout << c << endl << d << endl;
    BitArray e,f;
    // PrintArrays(a, b);
    return 0;
}
