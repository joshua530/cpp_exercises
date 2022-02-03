#include "utils.cc"
#include <iostream>

using std::cout;

#ifndef __RAM_FUNCTIONS
#define __RAM_FUNCTIONS

int *initializeRAM()
{
    int *RAM = new int[10];

    for (int i = 0; i < 10; ++i)
        RAM[i] = 0;

    return RAM;
}

void alterRAM(int location, int newValue, int *&ram)
{
    int value = newValue % 1000;
    if (value < 0)
        value = -value;
    ram[location] = value;
}

void testAlterRAM()
{
    int *expected = initializeRAM();
    // 1005 4
    expected[4] = 5;
    // below -3 7
    expected[7] = 3;
    // normal 2 8
    expected[2] = 8;
    int *actual = initializeRAM();
    alterRAM(4, 1005, actual);
    alterRAM(7, -3, actual);
    alterRAM(2, 8, actual);

    cout << "Alter RAM = ";
    if (equals(expected, actual)) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    delete[] expected;
    delete[] actual;
}

void testInitializeRAM()
{
    int *expected = new int[10];
    expected[0] = 0;
    expected[1] = 0;
    expected[2] = 0;
    expected[3] = 0;
    expected[4] = 0;
    expected[5] = 0;
    expected[6] = 0;
    expected[7] = 0;
    expected[8] = 0;
    expected[9] = 0;
    int *actual = initializeRAM();

    cout << "RAM initialization = ";

    if (equals(expected, actual)) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    delete[] expected;
    delete[] actual;
}

#endif

// int main(int argc, char **argv)
// {
//     testInitializeRAM();
//     testAlterRAM();
// }
