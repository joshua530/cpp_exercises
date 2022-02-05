#include "chess_pieces.cc"
#include "read_board.cc"

#ifndef __CHECK_FOR_CHECK_FUNCS
#define __CHECK_FOR_CHECK_FUNCS
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

void testBoardIsEmpty()
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
    vector<array<string, 8>> board2 = {
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
        {".", ".", ".", ".", ".", ".", ".", "."},
    };

    bool boardEmpty = boardIsEmpty(board);
    bool board2Empty = boardIsEmpty(board2);
    cout << "Boards empty\n";
    printTestMessage("Board 1", (!boardEmpty));
    printTestMessage("Board 2", (board2Empty));
}
#endif

// int main(int argc, char **argv)
// {
// testBoardIsEmpty();
// string chessStr = getFileContents("boards");
// vector<vector<array<string, 8>>> chessBoards =
//     chessBoardsFromString(chessStr);
// checkForChecks(chessBoards);
// }
