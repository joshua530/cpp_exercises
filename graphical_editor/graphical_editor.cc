#include "cmd.h"
#include <array>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using std::array;
using std::cin;
using std::cout;
using std::queue;
using std::string;
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

string trim(const string &s, const string &toTrim = " \n\t\r\f\v")
{
    return rtrim(ltrim(s, toTrim), toTrim);
}

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
    // 1,10,100,... according to the size of the string
    int multiplier = std::pow(10, toConvert.size() - 1);
    // the - sign takes up one place value, number is
    // therefore the length of the string - 1
    if (toConvert[0] == '-') {
        multiplier /= 10;
    }

    int currentIndex = 0;
    bool shouldNegate = false;

    for (const char &c : toConvert) {
        if (currentIndex == 0 && c == '-') {
            shouldNegate = true;
        } else {
            int charNum = charToInt(c);
            total += charNum * multiplier;
            multiplier /= 10;
        }
        ++currentIndex;
    }

    if (shouldNegate)
        total = -total;

    return total;
}

string getCommand()
{
    string command;
    cin >> command;
    // remove whitespace from beginning and end of command
    command = trim(command);
    return command;
}

string *splitCommand(string command)
{
    string *commandList = new string[MAX_COMMAND_SIZE];
    for (int i = 0; i < MAX_COMMAND_SIZE; ++i)
        commandList[i] = "NOT_CMD"; // TERMINATOR FOR COMMAND LIST

    string current = "";

    bool readingCmd = true;
    int currentIndex = 0;
    for (const char &c : command) {
        if (c == ' ') {
            readingCmd = false;
        }

        if (!readingCmd) {
            commandList[currentIndex] = current;
            current = "";
            readingCmd = true;
            ++currentIndex;
        } else {
            current += c;
        }
    }
    // append last command that was left out above
    commandList[currentIndex] = current;

    return commandList;
}

vector<vector<char>> createBitmap(int nrows, int ncols, char color)
{
    vector<vector<char>> bmp;
    if (nrows == 0 || ncols == 0) {
        return bmp;
    }

    // fill bitmap with color
    for (int i = 0; i < nrows; ++i) {
        vector<char> tmp;
        for (int j = 0; j < ncols; ++j) {
            tmp.push_back(color);
        }
        bmp.push_back(tmp);
    }

    return bmp;
}

/**
 * I M N
 * Create a new M × N image with all pixels initially colored white (O).
 *
 * @param cmdSegments split up command
 * @param bitmap bitmap to be manipulated
 */
void do_I(string *cmdSegments, vector<vector<char>> &bitmap)
{
    // input is valid ? redraw bitmap else keep bitmap
    int cols = strToInt(cmdSegments[1]);
    int rows = strToInt(cmdSegments[2]);

    if (cols == INT8_MIN || rows == INT8_MIN) // invalid input nums, keep bitmap
        return;

    bitmap = createBitmap(rows, cols, '0');
}

/**
 * C - Clear the table by setting all pixels white (O). The size remains
 * unchanged.
 *
 * @param bitmap bitmap to be manipulated
 * @param nrows number of rows in bitmap
 * @param ncols number of columns in bitmap
 */
void do_C(vector<vector<char>> &bitmap)
{
    int nrows = bitmap.size();
    int ncols = (nrows == 0) ? 0 : bitmap[0].size();
    for (int row = 0; row < nrows; ++row) {
        for (int col = 0; col < ncols; ++col) {
            bitmap[row][col] = '0';
        }
    }
}

/**
 * L X Y C - Colors the pixel (X, Y ) in color (C)
 *
 * @param cmdSegments split up command
 * @param bitmap bitmap to be manipulated
 */
void do_L(string *cmdSegments, vector<vector<char>> &bitmap)
{
    int col = strToInt(cmdSegments[1]) - 1;
    int row = strToInt(cmdSegments[2]) - 1;
    bitmap[row][col] = cmdSegments[3][0];
}

/**
 * V X Y1 Y2 C - Draw a vertical segment of color (C) in column X,
 * between the rows Y 1 and Y 2 inclusive.
 *
 * @param cmdSegments split up command
 * @param bitMap bitmap to be manipulated
 */
void do_V(string *cmdSegments, vector<vector<char>> &bitmap)
{
    int col = strToInt(cmdSegments[1]) - 1;
    int beginRow = strToInt(cmdSegments[2]) - 1;
    int endRow = strToInt(cmdSegments[3]) - 1;
    char color = cmdSegments[4][0];

    for (int i = beginRow; i <= endRow; ++i) {
        bitmap[i][col] = color;
    }
}

/**
 * H X1 X2 Y C - Draw a horizontal segment of color (C) in the row Y ,
 * between the columns X1 and X2 inclusive
 *
 * @param cmdSegments split up command
 * @param bitmap bitmap to be manipulated
 */
void do_H(string *cmdSegments, vector<vector<char>> &bitmap)
{
    int startCol = strToInt(cmdSegments[1]) - 1;
    int endCol = strToInt(cmdSegments[2]) - 1;
    int row = strToInt(cmdSegments[3]) - 1;
    char color = cmdSegments[4][0];

    for (int i = startCol; i <= endCol; ++i) {
        bitmap[row][i] = color;
    }
}

/**
 * K X1 Y1 X2 Y2 C - Draw a ﬁlled rectangle of color C, where (X1, Y 1)
 * is the upper-left and (X2, Y 2) the lower right corner.
 *
 * @param cmdSegments split up command
 * @param bitmap bitmap to be manipulated
 */
void do_K(string *cmdSegments, vector<vector<char>> &bitmap)
{
    int startCol = strToInt(cmdSegments[1]);
    int endCol = strToInt(cmdSegments[3]);
    int startRow = strToInt(cmdSegments[2]);
    int endRow = strToInt(cmdSegments[4]);
    char toFill = cmdSegments[5][0];

    for (int row = startRow; row <= endRow; ++row) {
        for (int col = startCol; col <= endCol; ++col) {
            bitmap[row][col] = toFill;
        }
    }
}

/**
 * @param curRowIndex zero based index of current row
 * @param curColIndex zero based index of current column
 */
vector<array<int, 2>> getNeighbours(int nrows, int ncols, int curRowIndex,
                                    int curColIndex)
{
    if ((curRowIndex < 0 || curRowIndex > nrows) || curColIndex < 0 ||
        curColIndex > ncols)
        return {};

    array<array<int, 2>, 4> allNeighbours = {
        {{{curRowIndex - 1, curColIndex}},
         {{curRowIndex, curColIndex - 1}},
         {{curRowIndex, curColIndex + 1}},
         {{curRowIndex + 1, curColIndex}}}};

    vector<array<int, 2>> validNeighbours;
    // validate the neighbours
    for (size_t i = 0; i < 4; ++i) {
        bool rowValid =
            (allNeighbours[i][0] >= 0 && allNeighbours[i][0] < nrows);
        bool colValid =
            (allNeighbours[i][1] >= 0 && allNeighbours[i][1] < ncols);

        if (rowValid && colValid) {
            validNeighbours.push_back(allNeighbours[i]);
        }
    }
    return validNeighbours;
}

/**
 * F X Y C - Fill the region R with the color C, where R is deﬁned as
 * follows. Pixel (X, Y ) belongs to R. Any other pixel which is the
 * same color as pixel (X, Y ) and shares a common side with any pixel
 * in R also belongs to this region.
 *
 * @param nrows number of rows in bitmap
 * @param ncols number of columns in bitmap
 * @param cmdSegments split up commands
 * @param bitmap bitmap to be manipulated
 */
void do_F(string *cmdSegments, vector<vector<char>> &bitmap)
{
    int nrows = bitmap.size();
    int ncols = (nrows == 0) ? 0 : bitmap[0].size();
    // keep track to avoid visiting a 'pixel' twice
    bool visited[nrows][ncols];
    // keep track to avoid placing 'pixel' twice in queue
    bool placedInQueue[nrows][ncols];

    for (int row = 0; row < nrows; ++row) {
        for (int col = 0; col < ncols; ++col) {
            visited[row][col] = false;
            placedInQueue[row][col] = false;
        }
    }

    int row = strToInt(cmdSegments[2]);
    int col = strToInt(cmdSegments[1]);
    char color = cmdSegments[3][0];

    queue<array<int, 2>> regionMembers;
    regionMembers.push({{row, col}});

    while (!regionMembers.empty()) {
        array<int, 2> current = regionMembers.front();
        int memberRow = current[0];
        int memberCol = current[1];
        vector<array<int, 2>> neighbours =
            getNeighbours(nrows, ncols, memberRow, memberCol);

        for (int i = 0; i < neighbours.size(); ++i) {
            int neighbourRow = neighbours[i][0];
            int neighbourCol = neighbours[i][1];
            // color is the same and not yet visited or added to queue
            // add neighbour to squares to be visited
            if (bitmap[neighbourRow][neighbourCol] ==
                    bitmap[memberRow][memberCol] &&
                !(visited[neighbourRow][neighbourCol]) &&
                !(placedInQueue[neighbourRow][neighbourCol])) {
                regionMembers.push({{neighbourRow, neighbourCol}});
                placedInQueue[neighbourRow][neighbourCol] = true;
            }
        }
        // change color
        bitmap[memberRow][memberCol] = color;
        // mark as visited
        visited[memberRow][memberCol] = true;
        regionMembers.pop();
    }
}

/**
 * splits string using a given separator
 */
vector<string> split(string toSplit, char separator)
{
    vector<string> segments;

    string current = "";
    for (const char &c : toSplit) {
        if (c == '.') {
            if (current != "")
                segments.push_back(current);
            current = "";
        } else {
            current += c;
        }
    }
    // part after last period
    if (current != "")
        segments.push_back(current);

    return segments;
}

/**
 * Convert a given filename to DOS 8.3 format
 *
 * @param fileName the file name to convert to DOS 8.3 format
 */
string toDOS_8_3(string fileName)
{
    vector<string> segments = split(fileName, '.');
    string name = segments[0];
    name = name.substr(0, 8);
    string extension = segments[1];
    extension = extension.substr(0, 3);

    string full = name + "." + extension;
    return full;
}

/**
 * Converts 'bitmap' image to a string
 */
string bitmapContents(vector<vector<char>> bitmap)
{
    string contents = "";
    int nrows = bitmap.size();
    int ncols = (nrows == 0) ? 0 : bitmap[0].size();

    for (int row = 0; row < nrows; ++row) {
        for (int col = 0; col < ncols; ++col) {
            contents += bitmap[row][col];
        }
        contents += "\n";
    }

    // trim extra newline
    return rtrim(contents);
}

/**
 * S Name - Write the ﬁle name in MSDOS 8.3 format followed by the
 * contents of the current image.
 *
 * @param cmdSegments split up command
 * @param bitmap the bitmap to print out
 * @param nrows number of rows in bitmap
 * @param ncols number of columns in bitmap
 */
string do_S(string *cmdSegments, vector<vector<char>> bitmap)
{
    string fileName = toDOS_8_3(cmdSegments[1]);
    string bitmapStr = bitmapContents(bitmap);
    string full = fileName + "\n" + bitmapStr;
    return full;
}

/**
 * Performs actions according to commands given
 *
 * @param command the given command
 * @param bitmap the bitmap to be manipulated
 */
void interpretCommand(const string command, vector<vector<char>> &bitmap,
                      const int nrows = 0, const int ncols = 0)
{
    string *cmdSegments = splitCommand(command);
    string validCommands[9] = {"I", "C", "L", "V", "H", "K", "F", "S", "X"};
    string mainCmd = cmdSegments[0];
    bool commandValid = false;

    for (int i = 0; i < 9; ++i) {
        if (mainCmd == validCommands[i]) {
            commandValid = true;
            break;
        }
    }

    // if command is not valid, ignore it
    if (commandValid) {
        if (mainCmd == "I") {
            do_I(cmdSegments, bitmap);
        }

        if (mainCmd == "C") {
            do_C(bitmap);
        }

        if (mainCmd == "L") {
            do_L(cmdSegments, bitmap);
        }

        if (mainCmd == "V") {
            do_V(cmdSegments, bitmap);
        }

        if (mainCmd == "H") {
            do_H(cmdSegments, bitmap);
        }

        if (mainCmd == "K") {
            do_K(cmdSegments, bitmap);
        }

        if (mainCmd == "F") {
            do_F(cmdSegments, bitmap);
        }

        if (mainCmd == "S") {
            cout << do_S(cmdSegments, bitmap) << "\n";
        }

        // X - Terminate the session
        if (mainCmd == "X") {
            cout << "Session terminated\n";
            delete[] cmdSegments;
            exit(0);
        }
    }
}

int main(int argc, char **argv)
{
    vector<vector<char>> bmp;
    string cmd;

    while (getline(cin, cmd)) {
        interpretCommand(cmd, bmp);
    }
}
