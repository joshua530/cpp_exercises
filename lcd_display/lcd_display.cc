#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using std::array;
using std::cout;
using std::ifstream;
using std::pow;
using std::stack;
using std::string;
using std::unordered_map;
using std::vector;

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

string getPattern(unordered_map<string, unordered_map<int, string>> patterns,
                  string position, int num)
{
    string validPositions[7] = {"top",    "topLeft",    "topRight",
                                "middle", "bottomLeft", "bottomRight",
                                "bottom"};
    bool positionValid = false;
    bool numValid = (num >= 0 && num <= 9);

    for (int i = 0; i < 7; ++i) {
        if (validPositions[i] == position) {
            positionValid = true;
            break;
        }
    }
    if (!positionValid) {
        cout << "You have entered an invalid position: " << position << "\n";
        exit(1);
    }
    if (!numValid) {
        cout << "You ave entered an invalid number: " << num << "\n";
    }

    return patterns[position][num];
}

vector<int> splitNumber(int i)
{
    stack<int> theStack;
    vector<int> tmp;

    if (i == 0) {
        tmp.push_back(0);
        return tmp;
    }
    if (i < 1)
        i = -i;

    while (i != 0) {
        int x = i % 10;
        theStack.push(x);
        i -= x;
        i /= 10;
    }

    while (!theStack.empty()) {
        tmp.push_back(theStack.top());
        theStack.pop();
    }

    return tmp;
}

unordered_map<string, unordered_map<int, string>> getPatterns()
{
    unordered_map<int, string> top = {{1, " "}, {2, "-"}, {3, "-"}, {4, " "},
                                      {5, "-"}, {6, "-"}, {7, "-"}, {8, "-"},
                                      {9, "-"}, {0, "-"}};
    unordered_map<int, string> topLeft = {
        {1, " "}, {2, " "}, {3, " "}, {4, "|"}, {5, "|"},
        {6, "|"}, {7, " "}, {8, "|"}, {9, "|"}, {0, "|"}};
    unordered_map<int, string> topRight = {
        {1, "|"}, {2, "|"}, {3, "|"}, {4, "|"}, {5, " "},
        {6, " "}, {7, "|"}, {8, "|"}, {9, "|"}, {0, "|"}};
    unordered_map<int, string> middle = {{1, " "}, {2, "-"}, {3, "-"}, {4, "-"},
                                         {5, "-"}, {6, "-"}, {7, " "}, {8, "-"},
                                         {9, "-"}, {0, ""}};
    unordered_map<int, string> bottomLeft = {
        {1, " "}, {2, "|"}, {3, " "}, {4, " "}, {5, " "},
        {6, "|"}, {7, " "}, {8, "|"}, {9, " "}, {0, "|"}};
    unordered_map<int, string> bottomRight = {
        {1, "|"}, {2, " "}, {3, "|"}, {4, "|"}, {5, "|"},
        {6, "|"}, {7, "|"}, {8, "|"}, {9, "|"}, {0, "|"}};
    unordered_map<int, string> bottom = {{1, " "}, {2, "-"}, {3, "-"}, {4, " "},
                                         {5, "-"}, {6, "-"}, {7, " "}, {8, "-"},
                                         {9, "-"}, {0, "-"}};

    unordered_map<string, unordered_map<int, string>> patterns = {
        {"top", top},
        {"topLeft", topLeft},
        {"topRight", topRight},
        {"middle", middle},
        {"bottomLeft", bottomLeft},
        {"bottomRight", bottomRight},
        {"bottom", bottom}};

    return patterns;
}

/**
 * Gets 'top' portion of toFormat in 'LCD' display
 *
 * @param patterns the characters occupying the top,middle and bottom portions
 * of the 'LCD' display for the numbers 0-9
 * @param toFormat the number for which the top 'LCD' portion is to be obtained
 * @param size the size of the LCD display
 */
string getTop(unordered_map<string, unordered_map<int, string>> patterns,
              int toFormat, int size)
{
    string placeholder = "";

    if (toFormat == 0 || size == 0)
        return placeholder;

    vector<int> nums = splitNumber(toFormat);

    for (vector<int>::const_iterator i = nums.begin(); i != nums.end(); ++i) {
        placeholder += " ";
        for (int j = 0; j < size; ++j)
            placeholder += getPattern(patterns, "top", *i);
        placeholder += " ";
        placeholder += " ";
    }

    // remove space at the end of the string
    placeholder = placeholder.substr(0, (placeholder.size() - 1));

    return placeholder;
}

/**
 * Gets 'top left and top right' portion of toFormat in 'LCD' display
 *
 * @param patterns the characters occupying the top,middle and bottom portions
 * of the 'LCD' display for the numbers 0-9
 * @param toFormat the number for which the top 'LCD' portion is to be obtained
 * @param size the size of the LCD display
 */
string
getTopLeftAndRight(unordered_map<string, unordered_map<int, string>> patterns,
                   int toFormat, int size)
{
    if (toFormat == 0 || size == 0)
        return "";

    string placeholder = "";
    vector<int> nums = splitNumber(toFormat);

    for (int k = 0; k < size; ++k) {
        for (vector<int>::const_iterator i = nums.begin(); i != nums.end();
             ++i) {
            placeholder += getPattern(patterns, "topLeft", *i);
            for (int j = 0; j < size; ++j)
                placeholder += " ";
            placeholder += getPattern(patterns, "topRight", *i);
            placeholder += " ";
        }
        // remove extra space at the end
        placeholder = placeholder.substr(0, placeholder.size() - 1);
        placeholder += "\n";
    }
    // remove extra new line at the end
    placeholder = placeholder.substr(0, placeholder.size() - 1);

    return placeholder;
}

string getMiddle(unordered_map<string, unordered_map<int, string>> patterns,
                 int num, int size)
{
    if (num == 0 || size == 0)
        return "";

    string placeholder = "";
    vector<int> nums = splitNumber(num);

    for (vector<int>::const_iterator i = nums.begin(); i != nums.end(); ++i) {
        placeholder += " ";
        for (int j = 0; j < size; ++j)
            placeholder += getPattern(patterns, "middle", *i);
        placeholder += " ";
        placeholder += " ";
    }
    // delete extra space at the end
    placeholder = placeholder.substr(0, placeholder.size() - 1);
    return placeholder;
}

string getBottomLeftAndRight(
    unordered_map<string, unordered_map<int, string>> patterns, int num,
    int size)
{
    if (num == 0 || size == 0)
        return "";

    string placeholder = "";
    vector<int> nums = splitNumber(num);

    // get <size> rows
    for (int j = 0; j < size; ++j) {
        // get one row
        for (vector<int>::const_iterator i = nums.begin(); i != nums.end();
             ++i) {
            placeholder += getPattern(patterns, "bottomLeft", *i);
            // get <size> spaces
            for (int k = 0; k < size; ++k)
                placeholder += " ";
            placeholder += getPattern(patterns, "bottomRight", *i);
            placeholder += " ";
        }
        // remove extra space at the end
        placeholder = placeholder.substr(0, placeholder.size() - 1);
        placeholder += "\n";
    }
    // remove extra \n at the end
    placeholder = placeholder.substr(0, placeholder.size() - 1);
    return placeholder;
}

string getBottom(unordered_map<string, unordered_map<int, string>> patterns,
                 int num, int size)
{
    if (num == 0 || size == 0)
        return "";

    vector<int> nums = splitNumber(num);
    string placeholder = "";

    // get all of the row
    //   for each number
    for (vector<int>::const_iterator i = nums.begin(); i != nums.end(); ++i) {
        placeholder += " ";
        for (int j = 0; j < size; ++j)
            placeholder += getPattern(patterns, "bottom", *i);
        placeholder += " ";
        placeholder += " ";
    }
    // remove extra space at the end
    placeholder = placeholder.substr(0, placeholder.size() - 1);

    return placeholder;
}

string getLcd(unordered_map<string, unordered_map<int, string>> patterns, int n,
              int size)
{
    if (n == 0 || size == 0)
        return "";

    string top = getTop(patterns, n, size);
    string topLeftAndRight = getTopLeftAndRight(patterns, n, size);
    string middle = getMiddle(patterns, n, size);
    string bottomLeftAndRight = getBottomLeftAndRight(patterns, n, size);
    string bottom = getBottom(patterns, n, size);
    string lcd = top + "\n" + topLeftAndRight + "\n" + middle + "\n" +
                 bottomLeftAndRight + "\n" + bottom;
    return lcd;
}

int main(int argc, char **argv)
{
    unordered_map<string, unordered_map<int, string>> patterns = getPatterns();
    array<array<int, 2>, 3> nums = readNumsFromFile("sample_input");

    for (int i = 0; i < nums.size(); ++i) {
        int size = nums[i][0], number = nums[i][1];
        if (size == 0 || number == 0)
            break;

        cout << getLcd(patterns, number, size) << "\n";
    }
}
