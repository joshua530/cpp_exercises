#include <array>
#include <iostream>
#include <unordered_map>

using std::array;
using std::cout;
using std::unordered_map;

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

/**
 * Find the biggest number between a given range
 */
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

int main(int argc, char **argv)
{
    array<int[2], 4> input = {{{1, 10}, {100, 200}, {201, 210}, {900, 1000}}};

    for (int i = 0; i < input.size(); ++i) {
        int start = input[i][0], end = input[i][1];
        cout << start << " " << end << " " << maxCycle(start, end) << "\n";
    }
}
