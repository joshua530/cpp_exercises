#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using std::array;
using std::cout;
using std::ifstream;
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

string getFileContents(string fileName)
{
    stringstream buf;
    ifstream f(fileName);
    buf << f.rdbuf();
    f.close();
    return buf.str();
}

/**
 * creates a chess board from a given string representing a chess board
 */
vector<vector<array<string, 8>>> chessBoardsFromString(string boardString)
{
    boardString = trim(boardString);
    vector<vector<array<string, 8>>> boards;
    vector<string> individualBoards = splitString(boardString, "\n\n");

    for (int i = 0; i < individualBoards.size(); ++i) {
        vector<string> rows = splitString(individualBoards[i], "\n");
        vector<array<string, 8>> currentBoard;
        for (int j = 0; j < rows.size(); ++j) {
            std::vector<std::string> tmp = splitToChars(rows[j]);
            array<string, 8> rowPieces;
            std::copy(tmp.begin(), tmp.end(), rowPieces.begin());
            currentBoard.push_back(rowPieces);
        }
        boards.push_back(currentBoard);
    }
    return boards;
}

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

bool boardIsEmpty(vector<array<string, 8>> board)
{
    bool isEmpty = true;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != ".") {
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty)
            break;
    }
    return isEmpty;
}

bool isBlackPiece(string piece)
{
    char p = *(piece.c_str());
    return islower(p);
}

bool isWhitePiece(string piece)
{
    char p = *(piece.c_str());
    return isupper(p);
}

/**
 * doesn't take account for a piece being shielded by another
 * piece. ie a king not being in check despite being in an area checked
 * by another piece because a piece of the same color as it stands in
 * the way
 *
 */
void checkForChecks(vector<vector<array<string, 8>>> boards)
{
    int currentBoardIndex = 0;
    bool emptyBoardEncountered = false;

    while (!emptyBoardEncountered) {
        vector<array<string, 8>> board = boards[currentBoardIndex];
        if (boardIsEmpty(board)) {
            emptyBoardEncountered = true;
            continue;
        }
        array<int, 2> blackKingPos{INT8_MIN, INT8_MIN},
            whiteKingPos{INT8_MIN, INT8_MIN};
        bool checkedByWhite[8][8] = {false};
        bool checkedByBlack[8][8] = {false};
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < 8; ++j) {
                string piece = board[i][j];
                if (piece != ".") {
                    vector<array<int, 2>> accessibleSquares =
                        getAccessibleSquares(i, j, board);
                    // mark areas that are in check
                    for (auto iter = accessibleSquares.begin();
                         iter != accessibleSquares.end(); ++iter) {
                        int row = (*iter)[0], col = (*iter)[1];
                        if (isBlackPiece(piece))
                            checkedByBlack[row][col] = true;
                        else
                            checkedByWhite[row][col] = true;
                    }
                }

                // note the positions of the kings
                if (board[i][j] == "k")
                    blackKingPos = {i, j};
                else if (board[i][j] == "K")
                    whiteKingPos = {i, j};
            }

            // check whether one of the kings is in check
            if (blackKingPos[0] != INT8_MIN) {
                int bkrow = blackKingPos[0], bkcol = blackKingPos[1];
                if (checkedByWhite[bkrow][bkcol]) {
                    cout << "Game #" << (currentBoardIndex + 1)
                         << ": Black king in check\n";
                    break;
                }
            }
            if (whiteKingPos[0] != INT8_MIN) {
                int wkrow = whiteKingPos[0], wkcol = whiteKingPos[1];
                if (checkedByBlack[wkrow][wkcol]) {
                    cout << "Game #" << (currentBoardIndex + 1)
                         << ": White king in check\n";
                    break;
                }
            }
            // we've reached the end of the board and no king is in check
            if (i == (board.size() - 1)) {
                cout << "Game #" << (currentBoardIndex + 1)
                     << ": no king in check\n";
            }
        }
        ++currentBoardIndex;
    }
}

int main(int argc, char *argv[])
{
    string chessStr = getFileContents("boards");
    vector<vector<array<string, 8>>> chessBoards =
        chessBoardsFromString(chessStr);
    checkForChecks(chessBoards);
}
