#include "bitmap.cc"
#include "cmd.h"
#include "get_neighbours.cc"
#include "str_to_int.cc"
#include "trim_string.cc"
#include <iostream>
#include <queue>

using std::cin;
using std::queue;
using std::string;

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

void testSplitCommand()
{
    string cmd = "I A B C";
    string *cmds = new string[MAX_COMMAND_SIZE];
    cmds[0] = "I", cmds[1] = "A", cmds[2] = "B", cmds[3] = "C";

    for (int i = 4; i < MAX_COMMAND_SIZE; ++i)
        cmds[i] = "NOT_CMD";

    string *actual = splitCommand(cmd);

    cout << "Command splitting: ";
    if (*cmds == *actual) { // dereference so as to compare the values stored in
                            // memory addresses referred to by pointers
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    delete[] cmds;
    delete[] actual;
}

bool equals(vector<vector<char>> bitmapA, vector<vector<char>> bitmapB)
{
    return bitmapA == bitmapB;
}

void testInterpretCommand_I()
{
    vector<vector<char>> bitmap;
    vector<vector<char>> expected = createBitmap(3, 2, '0');
    interpretCommand("I 2 3", bitmap);

    cout << "I = ";
    if (equals(bitmap, expected))
        cout << "Success";
    else
        cout << "Failed";
    cout << "\n";
}

void testInterpretCommand_H()
{
    vector<vector<char>> tmp = createBitmap(3, 4, '0');
    tmp[0][0] = 'x';
    tmp[0][1] = 'x';
    tmp[0][2] = 'x';
    vector<vector<char>> bmp = createBitmap(3, 4, '0');
    interpretCommand("H 1 3 1 x", bmp);

    cout << "H = ";
    if (equals(tmp, bmp))
        cout << "Success";
    else
        cout << "Failed";
    cout << "\n";
}

void testInterpretCommand_C()
{
    vector<vector<char>> bmp = createBitmap(2, 2, '0');
    bmp[0][0] = 'B';
    bmp[0][1] = 'V';
    bmp[1][1] = 'A';
    vector<vector<char>> expected = createBitmap(2, 2, '0');
    interpretCommand("C", bmp, 2, 2);

    cout << "C = ";
    if (equals(bmp, expected))
        cout << "Success";
    else
        cout << "Failed";
    cout << "\n";
}

void testInterpretCommand_L()
{
    vector<vector<char>> tmp = createBitmap(3, 3, '0');
    tmp[1][0] = 'X';
    vector<vector<char>> bmp = createBitmap(3, 3, '0');

    interpretCommand("L 1 2 X", bmp, 3, 3);

    cout << "L = ";
    if (equals(tmp, tmp)) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

void testInterpretCommand_V()
{
    vector<vector<char>> tmp = createBitmap(3, 4, '0');
    tmp[0][1] = 'C';
    tmp[1][1] = 'C';

    vector<vector<char>> bmp = createBitmap(3, 4, '0');

    interpretCommand("V 2 1 2 C", bmp);

    cout << "V = ";
    if (equals(tmp, bmp)) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

void testInterpretCommand_K()
{
    vector<vector<char>> tmp = createBitmap(4, 4, '0');
    tmp[1][1] = 'x';
    tmp[1][2] = 'x';
    tmp[1][3] = 'x';
    tmp[2][1] = 'x';
    tmp[2][2] = 'x';
    tmp[2][3] = 'x';
    vector<vector<char>> bmp = createBitmap(4, 4, '0');
    interpretCommand("K 1 1 3 2 x", bmp);

    cout << "K = ";
    if (equals(tmp, bmp)) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

void testInterpretCommand_F()
{
    vector<vector<char>> bmp = createBitmap(5, 5, '0');
    bmp[1][1] = 'F';
    bmp[1][2] = 'F';
    bmp[1][3] = 'F';
    bmp[2][1] = 'F';
    bmp[2][2] = 'F';
    bmp[3][2] = 'F';
    bmp[3][3] = 'F';
    vector<vector<char>> tmp = createBitmap(5, 5, '0');
    tmp[1][1] = 'x';
    tmp[1][2] = 'x';
    tmp[1][3] = 'x';
    tmp[2][1] = 'x';
    tmp[2][2] = 'x';
    tmp[3][2] = 'x';
    tmp[3][3] = 'x';
    interpretCommand("F 1 1 x", bmp, 5, 5);

    cout << "F = ";
    if (equals(tmp, bmp)) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

void testToDOS_8_3()
{
    string a = "abcdefghi.ab";
    string b = "abc.abcd";
    string c = "abc.abcd.bar";
    string expected_a = "abcdefgh.ab";
    string expected_b = "abc.abc";
    string expected_c = "abc.abc";
    string actual_a = toDOS_8_3(a);
    string actual_b = toDOS_8_3(b);
    string actual_c = toDOS_8_3(c);

    cout << "a = ";
    if (actual_a == expected_a) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "b = ";
    if (actual_b == expected_b) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "c = ";
    if (actual_c == expected_c) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

void testBitmapContents()
{
    vector<vector<char>> bmp = createBitmap(3, 3, '$');
    string expected = "$$$\n$$$\n$$$";
    string actual = bitmapContents(bmp);

    vector<vector<char>> emptyBmp = createBitmap(0, 0, '3');

    cout << "Bitmap contents = ";
    if (expected == actual) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Bitmap contents empty = ";
    if (bitmapContents(emptyBmp) == "") {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

void testDo_S()
{
    vector<vector<char>> bmp = createBitmap(3, 2, 'V');
    string expected = "three.bmp\nVV\nVV\nVV";
    string *cmdSegments = new string[2];
    cmdSegments[0] = "S";
    cmdSegments[1] = "three.bmp";
    string actual = do_S(cmdSegments, bmp);

    cout << "Do_S = ";
    if (actual == expected) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

int main()
{
    testInterpretCommand_I();
    testInterpretCommand_C();
    testInterpretCommand_L();
    testInterpretCommand_V();
    testInterpretCommand_H();
    testInterpretCommand_K();
    testInterpretCommand_F();
    testToDOS_8_3();
    testBitmapContents();
    testDo_S();
}
