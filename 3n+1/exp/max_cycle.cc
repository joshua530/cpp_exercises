#include "get_cycle_len.cc"
#include <iostream>
#include <unordered_map>

using std::cout;
using std::unordered_map;

int maxCycle(int start, int end)
{
    unordered_map<int, int> calculatedCycles;

    int currentMax = INT32_MIN;
    for (int i = start; i <= end; ++i) {
        int numCycles = cycleLength(i, calculatedCycles);
        if (numCycles > currentMax)
            currentMax = numCycles;
    }

    return currentMax;
}

void testMaxCycle()
{
    int one_n_ten = maxCycle(1, 10);
    int one_hundred_n_200 = maxCycle(100, 200);
    int two_hundred_and_one_n_210 = maxCycle(200, 210);
    int nine_hundred_n_1000 = maxCycle(900, 1000);

    cout << "One and ten = ";
    if (one_n_ten == 20) {
        cout << "Success.";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "one_hundred_n_200 = ";
    if (one_hundred_n_200 == 125) {
        cout << "Success.";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "two_hundred_and_one_n_210 = ";
    if (two_hundred_and_one_n_210 == 89) {
        cout << "Success.";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "nine_hundred_n_1000 = ";
    if (nine_hundred_n_1000 == 174) {
        cout << "Success.";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

int main()
{
    testMaxCycle();
}
