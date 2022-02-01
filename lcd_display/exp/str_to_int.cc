#include <cmath>
#include <iostream>
#include <string>

using std::cout;
using std::string;

int charToInt(char c)
{
    // c is not a valid integer
    if (int(c) < 48 || int(c) > 57)
        return INT8_MIN;

    return c - '0';
}

int strToInt(string toConvert)
{
    int total = 0;
    int multiplier = std::pow(10, toConvert.size() - 1);
    if (toConvert[0] == '-') {
        multiplier /= 10;
    }

    int currentI = 0;
    bool shouldNegate = false;

    for (const char &c : toConvert) {
        if (currentI == 0 && c == '-') {
            shouldNegate = true;
        } else {
            int charNum = charToInt(c);
            total += charNum * multiplier;
            multiplier /= 10;
        }
        ++currentI;
    }

    if (shouldNegate)
        total = -total;

    return total;
}

void testStrToInt()
{
    string a = "122", b = "", c = "-22";
    int expectedA = 122, expectedB = 0, expectedC = -22;
    int actualA = strToInt(a), actualB = strToInt(b), actualC = strToInt(c);

    cout << "A = ";
    if (actualA == expectedA)
        cout << " Passed";
    else
        cout << " Failed";
    cout << "\n";

    cout << "B = ";
    if (actualB == expectedB)
        cout << " Passed";
    else
        cout << " Failed";
    cout << "\n";

    cout << "C = ";
    if (actualC == expectedC)
        cout << " Passed";
    else
        cout << " Failed";
    cout << "\n";
}

void testCharToInt()
{
    cout << "0 = ";
    if (charToInt('0') == 0) {
        cout << " passed";
    } else {
        cout << " failed";
    }
    cout << "\n";

    cout << "b = ";
    if (charToInt('b') == INT8_MIN)
        cout << " passed";
    else
        cout << " failed";
    cout << "\n";
}

int main(int argc, char **argv)
{
    testStrToInt();
}
