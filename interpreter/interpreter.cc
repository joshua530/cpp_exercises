#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::ifstream;
using std::map;
using std::string;
using std::stringstream;
using std::vector;

/**
 * removes one character[s] from beginning of string
 *
 * Whitespace is trimmed by default
 *
 * @param s the string to trim
 * @param toTrim character set to remove from beginning
 */
string ltrim(const string &s, const string &toTrim = " \n\t\r\f\v")
{
    size_t firstPos = s.find_first_not_of(toTrim);
    return (firstPos == string::npos) ? "" : s.substr(firstPos);
}

/**
 * removes one character[s] from end of string
 *
 * Whitespace is trimmed by default
 *
 * @param s the string to trim
 * @param toTrim character set to remove from beginning
 */
string rtrim(const string &s, const string &toTrim = " \n\t\r\f\v")
{
    size_t end = s.find_last_not_of(toTrim);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

/**
 * trims characters from the beginning and end of the string
 *
 * whitespace is trimmed by default
 */
string trim(const string &s, const string &toTrim = " \n\t\r\f\v")
{
    return rtrim(ltrim(s, toTrim), toTrim);
}

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

int charToInt(char c)
{
    // c is not a valid integer
    if (int(c) < 48 || int(c) > 57)
        return INT8_MIN;

    return c - '0';
}

int *initializeRAM()
{
    int *RAM = new int[10];

    for (int i = 0; i < 10; ++i)
        RAM[i] = 0;

    return RAM;
}

void alterRAM(int location, int newValue, int *&ram)
{
    int value = newValue % 1000;
    if (value < 0)
        value = -value;
    ram[location] = value;
}

void interpretInstructions(string instruction, int *&ram)
{
    char *instructions = splitInstruction(instruction);
    int main = charToInt(instructions[0]);
    int num1 = charToInt(instructions[1]);
    int num2 = charToInt(instructions[2]);

    switch (main) {
        case 1: // 100 - halt(we assume session terminated)
            // delete[] ram;
            // delete[] instructions;
            // cout << "Session terminated\n";
            // exit(0);
            break;
        case 2: // 2dn - set register d to n
            alterRAM(num1, num2, ram);
            break;
        case 3: // 3dn - add n to register d
            alterRAM(num1, (num2 + ram[num1]), ram);
            break;
        case 4: // 4dn - multiply register d by n
            alterRAM(num1, (num2 * ram[num1]), ram);
            break;
        case 5: // 5ds - set register d to the value of register s
            alterRAM(num1, ram[num2], ram);
            break;
        case 6: // 6ds - add the value of register s to register d
            alterRAM(num1, (ram[num1] + ram[num2]), ram);
            break;
        case 7: // 7ds - multiply register d by the value of register s
            alterRAM(num1, (ram[num1] * ram[num2]), ram);
            break;
        case 8: // 8da - set register d to the value in RAM whose address is in
                // register a
            alterRAM(num1, ram[num2], ram);
            break;
        case 9: // 9sa - set the value in RAM whose address is in register a to
                // that of register s
            alterRAM(num2, ram[num1], ram);
            break;
        case 0: // 0ds - goto the location in register d unless register s
                // contains 0
            // assume goto d unless s contains 0
            if (ram[num2] == 0) {
                // goto s
            } else {
                // goto d
            }
            break;
    }

    delete[] instructions;
}

int main(int argc, char **argv)
{
    map<string, vector<string>> numAndInstructions =
        instructionsFromFile("input");

    int *ram = initializeRAM();
    for (map<string, vector<string>>::iterator i = numAndInstructions.begin();
         i != numAndInstructions.end(); ++i) {
        int currentCount = 0;
        vector<string> cmds = i->second;
        for (vector<string>::iterator j = cmds.begin(); j != cmds.end(); ++j) {
            ++currentCount;
            interpretInstructions(*j, ram);
        }
        cout << currentCount + 1
             << "\n"; // +1 is for the halt instruction(implicit for each case)
    }
    delete[] ram;
}
