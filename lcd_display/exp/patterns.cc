#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::make_pair;
using std::string;
using std::unordered_map;

/*

            top
top left           top right
            middle
bottom left        bottom right
            bottom

*/
// create number patterns according to format above for each number from 0-9
// where top = - or space
// top left & top right = | or space
// middle = - or space
// bottom left & bottom right = | or space
// bottom = - or space

#ifndef __PATTERNS
#define __PATTERNS
unordered_map<int, string> top = {{1, " "}, {2, "-"}, {3, "-"}, {4, " "},
                                  {5, "-"}, {6, "-"}, {7, "-"}, {8, "-"},
                                  {9, "-"}, {0, "-"}};
unordered_map<int, string> topLeft = {{1, " "}, {2, " "}, {3, " "}, {4, "|"},
                                      {5, "|"}, {6, "|"}, {7, " "}, {8, "|"},
                                      {9, "|"}, {0, "|"}};
unordered_map<int, string> topRight = {{1, "|"}, {2, "|"}, {3, "|"}, {4, "|"},
                                       {5, " "}, {6, " "}, {7, "|"}, {8, "|"},
                                       {9, "|"}, {0, "|"}};
unordered_map<int, string> middle = {{1, " "}, {2, "-"}, {3, "-"}, {4, "-"},
                                     {5, "-"}, {6, "-"}, {7, " "}, {8, "-"},
                                     {9, "-"}, {0, ""}};
unordered_map<int, string> bottomLeft = {{1, " "}, {2, "|"}, {3, " "}, {4, " "},
                                         {5, " "}, {6, "|"}, {7, " "}, {8, "|"},
                                         {9, " "}, {0, "|"}};
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
#endif

#ifndef __FUNC_GET_PATTERN
#define __FUNC_GET_PATTERN
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
#endif
