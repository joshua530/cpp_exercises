#include <array>
#include <vector>

using std::array;
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
