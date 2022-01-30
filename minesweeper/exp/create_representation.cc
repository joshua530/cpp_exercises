#include <array>
#include <iostream>
#include <vector>

using std::array;
using std::cout;
using std::string;
using std::vector;

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

    array<array<int, 2>, 8> allNeighbours = {
        {{{curRowIndex - 1, curColIndex - 1}},
         {{curRowIndex - 1, curColIndex}},
         {{curRowIndex - 1, curColIndex + 1}},
         {{curRowIndex, curColIndex - 1}},
         {{curRowIndex, curColIndex + 1}},
         {{curRowIndex + 1, curColIndex - 1}},
         {{curRowIndex + 1, curColIndex}},
         {{curRowIndex + 1, curColIndex + 1}}}};

    vector<array<int, 2>> validNeighbours;
    // validate the neighbours
    for (size_t i = 0; i < 8; ++i) {
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

vector<string> processInput(int numRowsAndCols[], vector<string> rowsAndCols)
{
    // for each square:
    //   if current square is not a mine:
    //     get neighbours
    //     among each neighbour, count the number of mines
    //     update the current square with the number of neighbouring mines
    // return the updated squares

    int numRows = numRowsAndCols[0];
    int numCols = numRowsAndCols[1];
    vector<string> output;

    // for each row
    for (int row = 0; row < numRows; ++row) {
        string currentRowOutput = "";

        // for each square
        for (int col = 0; col < numCols; ++col) {
            char currentSquareValue = rowsAndCols[row].at(col);
            // ensure the current square is not occupied by a mine
            if (currentSquareValue == '*') {
                currentRowOutput += '*';
                continue;
            }

            // count the number of bordering mines
            vector<array<int, 2>> neighbours;
            neighbours = getNeighbours(numRows, numCols, row, col);

            int numSurroundingMines = 0;
            for (int i = 0; i < neighbours.size(); ++i) {
                int neighbourRow = neighbours[i][0],
                    neighbourCol = neighbours[i][1];

                // get character occupying position
                char itemInSquare = rowsAndCols[neighbourRow].at(neighbourCol);
                if (itemInSquare == '*')
                    ++numSurroundingMines;
                // if mine, ++numSurroundingMines
            }
            currentRowOutput += numSurroundingMines + '0';
        }
        output.push_back(currentRowOutput);
    }

    return output;
}

void testProcessInput()
{
    int numRowsAndCols[][2] = {{4, 4}, {3, 5}, {0, 0}};
    vector<string> a{"*...", "....", ".*..", "...."};
    vector<string> b{"**...", ".....", ".*..."};
    vector<vector<string>> rowsAndCols{a, b};

    vector<string> expectedA{"*100", "2210", "1*10", "1110"};
    vector<string> expectedB{"**100", "33200", "1*100"};

    vector<string> actualA = processInput(numRowsAndCols[0], a);
    vector<string> actualB = processInput(numRowsAndCols[1], b);
    cout << "Test a ";
    if (actualA == expectedA) {
        cout << "passed";
    } else {
        cout << "failed";
    }
    cout << "\n";

    cout << "Test b ";
    if (actualB == expectedB) {
        cout << "passed";
    } else {
        cout << "failed";
    }
    cout << "\n";
}

void testGetNeighbours()
{
    int box[] = {3, 3};
    vector<array<int, 2>> a = {{0, 1}, {1, 0}, {1, 1}};

    vector<array<int, 2>> b = {{0, 0}, {0, 1}, {0, 2}, {1, 0},
                               {1, 2}, {2, 0}, {2, 1}, {2, 2}};

    vector<array<int, 2>> c = {{1, 1}, {1, 2}, {2, 1}};

    vector<array<int, 2>> d{};
    vector<array<int, 2>> actualA = getNeighbours(3, 3, 0, 0);
    vector<array<int, 2>> actualB = getNeighbours(3, 3, 1, 1);
    vector<array<int, 2>> actualC = getNeighbours(3, 3, 2, 2);
    vector<array<int, 2>> actualD = getNeighbours(3, 3, 30, 4);

    cout << "Test a = ";
    if (a == actualA) {
        cout << "Passed";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Test b = ";
    if (b == actualB) {
        cout << "Passed";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Test c = ";
    if (c == actualC) {
        cout << "Passed";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Test d = ";
    if (d == actualD) {
        cout << "Passed";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}
