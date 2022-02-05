#include "string_funcs.cc"
#include "utils.cc"
#include <array>
#include <fstream>
#include <sstream>
#include <vector>

using std::array;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

#ifndef __READ_BOARD_FUNCS
#define __READ_BOARD_FUNCS
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

void testChessBoardsFromString()
{
    string theBoard = "..k.....\nppp.pppp\n........\n.R...B..\n........\n......"
                      "..\nPPPPPPPP\nK.......\n\nrnbqk.nr\nppp..ppp\n....p..."
                      "\n...p....\n.bPP....\n.....N..\nPP..PPPP\nRNBQKB.R\n";
    vector<vector<array<string, 8>>> expected = {
        {{{".", ".", "k", ".", ".", ".", ".", "."}},
         {{"p", "p", "p", ".", "p", "p", "p", "p"}},
         {{".", ".", ".", ".", ".", ".", ".", "."}},
         {{".", "R", ".", ".", ".", "B", ".", "."}},
         {{".", ".", ".", ".", ".", ".", ".", "."}},
         {{".", ".", ".", ".", ".", ".", ".", "."}},
         {{"P", "P", "P", "P", "P", "P", "P", "P"}},
         {{"K", ".", ".", ".", ".", ".", ".", "."}}},
        {{{"r", "n", "b", "q", "k", ".", "n", "r"}},
         {{"p", "p", "p", ".", ".", "p", "p", "p"}},
         {{".", ".", ".", ".", "p", ".", ".", "."}},
         {{".", ".", ".", "p", ".", ".", ".", "."}},
         {{".", "b", "P", "P", ".", ".", ".", "."}},
         {{".", ".", ".", ".", ".", "N", ".", "."}},
         {{"P", "P", ".", ".", "P", "P", "P", "P"}},
         {{"R", "N", "B", "Q", "K", "B", ".", "R"}}}};
    vector<vector<array<string, 8>>> actual = chessBoardsFromString(theBoard);
    printTestMessage("Chess boards from string", (expected == actual));
}
#endif

// int main(int argc, char **argv)
// {
//     testChessBoardsFromString();
// }
