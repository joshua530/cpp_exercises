#include "utils.cc"
#include <array>
#include <string>
#include <vector>

using std::array;
using std::string;
using std::vector;

#ifndef __CHES_PIECES_FUNCS
#define __CHESS_PIECES_FUNCS
void validateSquares(vector<array<int, 2>> &squares)
{
    for (int i = 0; i < squares.size(); ++i) {
        int row = squares[i][0], col = squares[i][1];
        if (row < 0 || row >= 8) {
            squares.erase(std::next(squares.begin(), i));
            i = -1; // reset counter to the first element so that invalid
                    // positions are not skipped
        } else if (col < 0 || col >= 8) {
            // or squares.erase(squares.begin()+i)
            squares.erase(std::next(squares.begin(), i));
            i = -1; // reset counter to the first element so that invalid
                    // positions are not skipped
        }
    }
}

vector<array<int, 2>> getSquaresAccessibleByWhitePawn(int curRow, int curCol)
{
    vector<array<int, 2>> squares;
    squares = {{curRow - 1, curCol - 1}, {curRow - 1, curCol + 1}};
    validateSquares(squares);

    return squares;
}

vector<array<int, 2>> getSquaresAccessibleByBlackPawn(int curRow, int curCol)
{
    vector<array<int, 2>> squares;
    squares = {{curRow + 1, curCol - 1}, {curRow + 1, curCol + 1}};
    validateSquares(squares);
    return squares;
}

vector<array<int, 2>> getSquaresAccessibleByKnight(int curRow, int curCol)
{
    vector<array<int, 2>> squares = {
        {curRow - 2, curCol - 1}, {curRow - 2, curCol + 1},
        {curRow - 1, curCol - 2}, {curRow - 1, curCol + 2},
        {curRow + 1, curCol - 2}, {curRow + 1, curCol + 2},
        {curRow + 2, curCol - 1}, {curRow + 2, curCol + 1}};
    validateSquares(squares);
    return squares;
}

vector<array<int, 2>> getDiagonalSquares(int row, int col)
{
    vector<array<int, 2>> squares;
    // upper right
    int r = row, c = col;
    for (int i = 1; i < 8; ++i) {
        r -= 1;
        c += 1;
        // ensure values don't go out of bounds
        if ((r < 0 || r >= 8) || (c < 0 || c >= 8)) {
            r = row;
            c = col;
            break;
        }
        squares.push_back({r, c});
    }
    // upper left
    for (int i = 1; i < 8; ++i) {
        r -= 1;
        c -= 1;
        if ((r < 0 || r >= 8) || (c < 0 || c >= 8)) {
            r = row;
            c = col;
            break;
        }
        squares.push_back({r, c});
    }
    // lower left
    for (int i = 1; i < 8; ++i) {
        r += 1;
        c -= 1;
        if ((r < 0 || r >= 8) || (c < 0 || c >= 8)) {
            r = row;
            c = col;
            break;
        }
        squares.push_back({r, c});
    }
    // lower right
    for (int i = 1; i < 8; ++i) {
        r += 1;
        c += 1;
        if ((r < 0 || r >= 8) || (c < 0 || c >= 8)) {
            r = row;
            c = col;
            break;
        }
        squares.push_back({r, c});
    }
    return squares;
}

vector<array<int, 2>> getVerticalSquares(int row, int col)
{
    vector<array<int, 2>> squares;
    int r = row;
    // vertical
    for (int i = 0; i < 8; ++i) {
        r -= 1;
        if (r < 0 || r >= 8) {
            r = row;
            break;
        }
        squares.push_back({r, col});
    }
    for (int i = 0; i < 8; ++i) {
        r += 1;
        if (r < 0 || r >= 8)
            break;
        squares.push_back({r, col});
    }
    return squares;
}

vector<array<int, 2>> getHorizontalSquares(int row, int col)
{
    vector<array<int, 2>> squares;
    int c = col;
    // horizontal
    for (int i = 0; i < 8; ++i) {
        c -= 1;
        if (c < 0 || c >= 8) {
            c = col;
            break;
        }
        squares.push_back({row, c});
    }
    for (int i = 0; i < 8; ++i) {
        c += 1;
        if (c < 0 || c >= 8)
            break;
        squares.push_back({row, c});
    }
    return squares;
}

vector<array<int, 2>> getSquaresAccessibleByBishop(int row, int col)
{
    return getDiagonalSquares(row, col);
}

vector<array<int, 2>> getSquaresAccessibleByQueen(int row, int col)
{
    vector<array<int, 2>> squares;
    vector<array<int, 2>> v = getVerticalSquares(row, col);
    vector<array<int, 2>> h = getHorizontalSquares(row, col);
    vector<array<int, 2>> d = getDiagonalSquares(row, col);
    squares.insert(squares.end(), v.begin(), v.end());
    squares.insert(squares.end(), h.begin(), h.end());
    squares.insert(squares.end(), d.begin(), d.end());
    return squares;
}

vector<array<int, 2>> getSquaresAccessibleByRook(int row, int col)
{
    vector<array<int, 2>> v = getVerticalSquares(row, col);
    vector<array<int, 2>> h = getHorizontalSquares(row, col);
    vector<array<int, 2>> squares;
    squares.insert(squares.end(), v.begin(), v.end());
    squares.insert(squares.end(), h.begin(), h.end());
    return squares;
}

vector<array<int, 2>> getSquaresAccessibleByKing(int row, int col)
{
    vector<array<int, 2>> squares = {{row - 1, col - 1}, {row - 1, col},
                                     {row - 1, col + 1}, {row, col - 1},
                                     {row, col + 1},     {row + 1, col - 1},
                                     {row + 1, col},     {row + 1, col + 1}};
    validateSquares(squares);
    return squares;
}

vector<array<int, 2>> getSquaresAccessibleByPiece(string piece, int curRow,
                                                  int curCol)
{
    char lowerCasePiece = tolower(*piece.c_str());
    vector<array<int, 2>> squares;
    switch (lowerCasePiece) {
        case 'n':
            squares = getSquaresAccessibleByKnight(curRow, curCol);
            break;
        case 'b':
            squares = getSquaresAccessibleByBishop(curRow, curCol);
            break;
        case 'q':
            squares = getSquaresAccessibleByQueen(curRow, curCol);
            break;
        case 'r':
            squares = getSquaresAccessibleByRook(curRow, curCol);
            break;
        case 'k':
            squares = getSquaresAccessibleByKing(curRow, curCol);
            break;
    }
    return squares;
}

/**
 * finds accessible squares for a chess piece
 *
 * black pieces are lowercase and white pieces are uppercase
 *
 * white side will always be at the bottom of the board while the black side
 * will always be at the top
 *
 * p - pawn
 * n - knight
 * b - bishop
 * r - rook
 * q - queen
 * k - king
 *
 * @param row zero based index of row
 * @param col zero based index of column
 */
vector<array<int, 2>> getAccessibleSquares(int row, int col,
                                           vector<array<string, 8>> board)
{
    vector<array<int, 2>> squares;
    string piece = board[row][col];

    if (piece == "P" || piece == "p") {
        if (isupper(*piece.c_str())) { // white pieces
            squares = getSquaresAccessibleByWhitePawn(row, col);
        } else { // black pieces
            squares = getSquaresAccessibleByBlackPawn(row, col);
        }
    } else {
        squares = getSquaresAccessibleByPiece(piece, row, col);
    }

    return squares;
}

void testGetAccessibleSquares_pawn()
{
    vector<array<string, 8>> board = {
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", "p", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {"P", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", "", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
    };
    vector<array<int, 2>> expected_p = {{2, 0}, {2, 2}};
    vector<array<int, 2>> expected_P = {{4, 1}};
    vector<array<int, 2>> actual_p = getAccessibleSquares(1, 1, board);
    vector<array<int, 2>> actual_P = getAccessibleSquares(5, 0, board);
    cout << "Pawns\n";
    printTestMessage("p", (expected_p == actual_p));
    printTestMessage("P", (expected_P == actual_P));
}

void testGetAccessibleSquares_knight()
{
    vector<array<string, 8>> board = {
        {"n", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", "N", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
    };
    vector<array<int, 2>> expected_n = {{1, 2}, {2, 1}};
    vector<array<int, 2>> expected_N = {{2, 2}, {2, 4}, {3, 1}, {3, 5},
                                        {5, 1}, {5, 5}, {6, 2}, {6, 4}};
    vector<array<int, 2>> actual_n = getAccessibleSquares(0, 0, board);
    vector<array<int, 2>> actual_N = getAccessibleSquares(4, 3, board);
    cout << "Knights\n";
    printTestMessage("n", (expected_n == actual_n));
    printTestMessage("N", (expected_N == actual_N));
}

void testGetAccessibleSquares_king()
{
    vector<array<string, 8>> board = {
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", "k", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "K"},
    };

    vector<array<int, 2>> expected_k = {{3, 2}, {3, 3}, {3, 4}, {4, 2},
                                        {4, 4}, {5, 2}, {5, 3}, {5, 4}};
    vector<array<int, 2>> expected_K = {{6, 6}, {6, 7}, {7, 6}};

    vector<array<int, 2>> actual_k = getAccessibleSquares(4, 3, board);
    vector<array<int, 2>> actual_K = getAccessibleSquares(7, 7, board);
    cout << "King\n";
    printTestMessage("k", (expected_k == actual_k));
    printTestMessage("K", (expected_K == actual_K));
}

void testGetAccessibleSquares_rook()
{
    vector<array<string, 8>> board = {
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", "r", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
    };
    // vector<array<int, 2>> vertical = {{3, 3}, {2, 3}, {1, 3}, {0, 3},
    //                                   {5, 3}, {6, 3}, {7, 3}};
    // vector<array<int, 2>> horizontal = {{4, 2}, {4, 1}, {4, 0}, {4, 4},
    //                                     {4, 5}, {4, 6}, {4, 7}};
    vector<array<int, 2>> expected = {{3, 3}, {2, 3}, {1, 3}, {0, 3}, {5, 3},
                                      {6, 3}, {7, 3}, {4, 2}, {4, 1}, {4, 0},
                                      {4, 4}, {4, 5}, {4, 6}, {4, 7}};

    vector<array<int, 2>> actual = getAccessibleSquares(4, 3, board);
    printTestMessage("Rook", (expected == actual));
}

void testGetAccessibleSquares_bishop()
{
    vector<array<string, 8>> board = {
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", "B", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
    };
    vector<array<int, 2>> expected = {{3, 4}, {2, 5}, {1, 6}, {0, 7}, {3, 2},
                                      {2, 1}, {1, 0}, {5, 2}, {6, 1}, {7, 0},
                                      {5, 4}, {6, 5}, {7, 6}};
    vector<array<int, 2>> actual = getAccessibleSquares(4, 3, board);
    printTestMessage("Bishop", (expected == actual));
}

void testGetAccessibleSquares_queen()
{
    vector<array<string, 8>> board = {
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", "q", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
    };
    // vector<array<int, 2>> vertical = {{3, 3}, {2, 3}, {1, 3}, {0, 3},
    //                                   {5, 3}, {6, 3}, {7, 3}};
    // vector<array<int, 2>> horizontal = {{4, 2}, {4, 1}, {4, 0}, {4, 4},
    //                                     {4, 5}, {4, 6}, {4, 7}};
    // vector<array<int, 2>> diagonal = {{3, 4}, {2, 5}, {1, 6}, {0, 7}, {3, 2},
    //                                   {2, 1}, {1, 0}, {5, 2}, {6, 1}, {7, 0},
    //                                   {5, 4}, {6, 5}, {7, 6}};
    vector<array<int, 2>> expected = {
        {3, 3}, {2, 3}, {1, 3}, {0, 3}, {5, 3}, {6, 3}, {7, 3}, {4, 2}, {4, 1},
        {4, 0}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {3, 4}, {2, 5}, {1, 6}, {0, 7},
        {3, 2}, {2, 1}, {1, 0}, {5, 2}, {6, 1}, {7, 0}, {5, 4}, {6, 5}, {7, 6}};

    vector<array<int, 2>> actual = getAccessibleSquares(4, 3, board);
    printTestMessage("Queen", (expected == actual));
}
#endif
// int main(int argc, char *argv[])
// {
//     // testGetAccessibleSquares_pawn();
//     // testGetAccessibleSquares_knight();
//     // testGetAccessibleSquares_bishop();
//     // testGetAccessibleSquares_queen();
//     // testGetAccessibleSquares_rook();
//     // testGetAccessibleSquares_king();
// }
