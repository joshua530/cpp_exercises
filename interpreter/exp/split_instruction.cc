#include "utils.cc"
#include <iostream>
#include <string>

using std::cout;
using std::string;

#ifndef __SPLIT_INSTRUCTION_FUNCS
#define __SPLIT_INSTRUCTION_FUNCS

char *splitInstruction(string instruction)
{
    char *instructionSegments = new char[3];

    int current = 0;
    for (const char &c : instruction) {
        instructionSegments[current] = c;
        ++current;
    }
    return instructionSegments;
}

void testSplitInstruction()
{
    string instruction = "abc";
    char *expected = new char[3];
    expected[0] = 'a';
    expected[1] = 'b';
    expected[2] = 'c';
    char *actual = splitInstruction("abc");

    cout << "Instruction splitting = ";
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

// int main(int argc, char *argv[])
// {
//     testSplitInstruction();
// }
