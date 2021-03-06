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

int main(int argc, char **argv)
{
    int numRowsAndCols[][2] = {{4, 4}, {3, 5}, {0, 0}};
    vector<string> a{"*...", "....", ".*..", "...."};
    vector<string> b{"**...", ".....", ".*..."};
    vector<string> items[] = {a, b};

    for (int i = 0; i < 3; ++i) {
        if (numRowsAndCols[i][0] != 0 || numRowsAndCols[i][1] != 0) {
            cout << "Field #" << (i + 1) << "\n";
            vector<string> current = processInput(numRowsAndCols[i], items[i]);
            for (vector<string>::const_iterator i = current.begin();
                 i != current.end(); ++i) {
                cout << *i << "\n";
            }
            cout << "\n";
        }
    }
}
