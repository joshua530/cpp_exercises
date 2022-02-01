#include "str_to_int.cc"
#include <array>
#include <fstream>
#include <iostream>
#include <string>

using std::array;
using std::cout;
using std::ifstream;
using std::string;

array<array<int, 2>, 3> readNumsFromFile(string fileName)
{
    array<array<int, 2>, 3> items;
    ifstream data("sample_input");

    string currentLine;
    int currentIndex = 0;
    while (getline(data, currentLine)) {
        int separatorIndex = currentLine.find(" ");

        string s = currentLine.substr(0, separatorIndex);
        string n = currentLine.substr(separatorIndex + 1);
        int s_int = strToInt(s);
        int n_int = strToInt(n);
        array<int, 2> tmp = {{s_int, n_int}};
        items[currentIndex] = tmp;
        ++currentIndex;
    }
    return items;
}

void testReadNumsFromFile()
{
    array<array<int, 2>, 3> nums = {{{{2, 12345}}, {{3, 67890}}, {{0, 0}}}};

    array<array<int, 2>, 3> actual = readNumsFromFile("sample_input");

    cout << "Read file: ";
    if (nums == actual) {
        cout << "Passed";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

// int main(int argc, char **argv)
// {
//     testReadNumsFromFile();
// }
