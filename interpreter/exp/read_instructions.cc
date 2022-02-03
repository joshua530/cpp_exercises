#include "trim_string.cc"
#include "utils.cc"
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream;
using std::map;
using std::string;
using std::stringstream;
using std::vector;

#ifndef __READ_INSTRUCTIONS_FUNCS
#define __READ_INSTRUCTIONS_FUNCS

string readInstructions(string file)
{
    ifstream f(file);
    stringstream buf;
    buf << f.rdbuf();
    return buf.str();
}

vector<string> splitToChars(string toSplit)
{
    vector<string> chars;
    if (toSplit.size() == 0)
        chars.push_back("");

    for (int i = 0; i < toSplit.size(); ++i) {
        string s(1, toSplit[i]);
        chars.push_back(s);
    }
    return chars;
}

/**
 * splits a string using a provided delimiter
 *
 * if there are two delimiters following one another, both delimiters
 * will be excluded from the split segments
 */
vector<string> splitString(string toSplit, string delim)
{
    toSplit = trim(toSplit);

    if (delim == "")
        return splitToChars(toSplit);

    int lenDelim = delim.size();
    // for knowing whether we have encountered a full delimiter or not
    int delimPos = -1;
    string currentDelim = "";
    vector<string> strSegments;
    int posAfterLastSplit = 0;

    for (int i = 0; i < toSplit.size(); ++i) {
        if (toSplit[i] == delim[delimPos + 1]) {
            // build delimiter
            ++delimPos;
            currentDelim += toSplit[i];
        } else {
            // delimiter build failed
            // reset delimiter vars for next rebuild
            delimPos = -1;
            currentDelim = "";
        }

        if (currentDelim == delim) {
            // we have successfully built a delimiter, split the string
            int lastSplitToCurrent = (i - posAfterLastSplit);
            int lenSegment = (lastSplitToCurrent - lenDelim) + 1;
            string segment = toSplit.substr(posAfterLastSplit, lenSegment);
            // don't append empty substring due to a delimiter encountered
            // two times or more in succession
            if (segment != "")
                strSegments.push_back(segment);
            posAfterLastSplit = i + 1;
            // reset delimiter vars for next rebuild
            delimPos = -1;
            currentDelim = "";
        } else {
            // we have reached the end of the string without fully building a
            // delimiter(or another delimiter if there were others built
            // already), add the rest of the string from the last splitting
            // point to the segments we already have
            if (i == (toSplit.size() - 1)) {
                int lenSubstring = (toSplit.size() - posAfterLastSplit);
                string segment =
                    toSplit.substr(posAfterLastSplit, lenSubstring);
                strSegments.push_back(segment);
            }
        }
    }

    return strSegments;
}

map<string, vector<string>> splitInstructions(string instructions)
{
    string cmdSetSeparator = "\n\n\n"; // {{<num> <...instructions>},...}
    string cmdSeparator = "\n\n";      // {<num>, <...instructions>}
    vector<string> cmdSet = splitString(instructions, cmdSetSeparator);
    map<string, vector<string>> cmdMap;
    for (vector<string>::const_iterator i = cmdSet.begin(); i != cmdSet.end();
         ++i) {
        vector<string> numAndCmds = splitString(*i, cmdSeparator);
        vector<string> cmds = splitString(numAndCmds[1], "\n");
        map<string, vector<string>> tmp;
        // string foo = numAndCmds[0];
        cmdMap[numAndCmds[0]] = cmds;
        // cout << "";
    }
    return cmdMap;
}

map<string, vector<string>> instructionsFromFile(string file)
{
    string instructionString = readInstructions(file);
    map<string, vector<string>> parsedInstructions =
        splitInstructions(instructionString);
    return parsedInstructions;
}

void testInstructionsFromFile()
{
    map<string, vector<string>> expected;
    expected["one"] = {"two", "three", "four"};
    expected["two"] = {"two", "three", "four"};
    auto actual = instructionsFromFile("test");
    printTestMessage("Instructions from file", (expected == actual));
}

void testSplitToChars()
{
    string a = "abcd";
    string b = "";
    vector<string> e_a, e_b, a_a, a_b;
    e_a = {"a", "b", "c", "d"};
    e_b = {""};
    a_a = splitToChars(a);
    a_b = splitToChars(b);

    cout << "Split string to chars\n";
    printTestMessage("a", (e_a == a_a));
    printTestMessage("b", (e_b == a_b));
}

void testSplitString()
{
    string one = "abcxxxdefgxxhij";
    string two = "one\n\n\ntwo\n\n\nthree";
    string three = "abc";
    string four = "abc";
    string five = "abc";
    vector<string> e_1, e_2, e_3, e_4, e_5;
    e_1 = {"abc", "xdefg", "hij"};
    e_2 = {"one", "two", "three"};
    e_3 = {"ab"};
    e_4 = {"abc"};
    e_5 = {"a", "b", "c"};
    vector<string> a_1, a_2, a_3, a_4, a_5;
    a_1 = splitString(one, "xx");
    a_2 = splitString(two, "\n\n\n");
    a_3 = splitString(three, "c");
    a_4 = splitString(three, "f");
    a_5 = splitString(five, "");

    cout << "Split string\n";
    printTestMessage("one", (e_1 == a_1));
    printTestMessage("two", (e_2 == a_2));
    printTestMessage("three", (e_3 == a_3));
    printTestMessage("four", (e_4 == a_4));
    printTestMessage("five", (e_5 == a_5));
}

void testReadInstructions()
{
    string expected = "one\n\ntwo\nthree\nfour\n\n\ntwo\n\ntwo\nthree\nfour\n";
    string actual = readInstructions("test");
    printTestMessage("Read instructions", (expected == actual));
}

void testSplitInstructions()
{
    string str = "one\n\ntwo\nthree\nfour\n\n\nten\n\ntwo\nthree\nfour\nfive\n";
    map<string, vector<string>> expected;
    expected["one"] = {"two", "three", "four"};
    expected["ten"] = {"two", "three", "four", "five"};
    map<string, vector<string>> actual = splitInstructions(str);
    printTestMessage("Split instructions", (expected == actual));
}

#endif

// int main(int argc, char **argv)
// {
//     // testReadInstructions();
//     // testSplitString();
//     // testSplitToChars();
//     // testSplitInstructions();
//     // testInstructionsFromFile();
// }
