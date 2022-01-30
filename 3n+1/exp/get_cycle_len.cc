#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::array;
using std::cout;
using std::unordered_map;
using std::vector;

/**
 * @param calculatedCycles store for previously computed values
 */
int cycleLength(int n, unordered_map<int, int> &calculatedCycles)
{
    if (n < 1)
        return 0;

    unordered_map<int, int>::iterator i = calculatedCycles.find(n);

    int current = n;

    // we haven't calculated the number of cycles for n yet
    if (i == calculatedCycles.end()) {
        int cycleLen = 0;
        while (current != 1) {
            unordered_map<int, int>::iterator tmp =
                calculatedCycles.find(current);

            // for each number that we find, check whether the number of cycles
            // had already been calculated to avoid recomputation of the values
            if (tmp != calculatedCycles.end()) {
                cycleLen += tmp->second;
                break;
            }

            if (current % 2 == 0) {
                current /= 2;
            } else {
                current = (current * 3) + 1;
            }
            ++cycleLen;
        }
        // account for the last 1
        if (current == 1)
            ++cycleLen;

        calculatedCycles[n] = cycleLen;
    }

    return calculatedCycles[n];
}

void testCycleLen()
{
    int one = 1;
    int zero = 0;
    int five = 6;
    int ten = 7;

    unordered_map<int, int> calculatedCycles;

    int actualOne = cycleLength(1, calculatedCycles);
    int actualZero = cycleLength(0, calculatedCycles);
    int actualFive = cycleLength(5, calculatedCycles);
    int actualTen = cycleLength(10, calculatedCycles);
    int actualTwenty = cycleLength(20, calculatedCycles);
    int actualThirty = cycleLength(30, calculatedCycles);

    cout << "One = ";
    if (one == actualOne) {
        cout << "Passed";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Zero = ";
    if (zero == actualZero) {
        cout << "Passed";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Five = ";
    if (five == actualFive) {
        cout << "Passed";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Ten = ";
    if (ten == actualTen) {
        cout << "Passed";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}
