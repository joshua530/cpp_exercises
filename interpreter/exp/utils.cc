#include <iostream>
#include <string>

using std::cout;
using std::string;

#ifndef __UTIL_FUNCTIONS
#define __UTIL_FUNCTIONS

template <typename T>
bool equals(T *arr, T *arr2)
{
    bool areEqual = true;
    for (T i = 0; i < 10; ++i) {
        if (arr[i] != arr2[i]) {
            areEqual = false;
            break;
        }
    }
    return areEqual;
}

void printTestMessage(string message, bool success)
{
    cout << message << " = ";
    if (success) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

#endif
