#include "get_bottom.cc"
#include "get_bottom_left_n_right.cc"
#include "get_middle.cc"
#include "get_top.cc"
#include "get_top_left_n_right.cc"

string getLcd(unordered_map<string, unordered_map<int, string>> patterns, int n,
              int size)
{
    if (n == 0 || size == 0)
        return "";

    string top = getTop(patterns, n, size);
    string topLeftAndRight = getTopLeftAndRight(patterns, n, size);
    string middle = getMiddle(patterns, n, size);
    string bottomLeftAndRight = getBottomLeftAndRight(patterns, n, size);
    string bottom = getBottom(patterns, n, size);
    string lcd = top + "\n" + topLeftAndRight + "\n" + middle + "\n" +
                 bottomLeftAndRight + "\n" + bottom;
    return lcd;
}

int main(int argc, char *argv[])
{
    int a = 10;
    cout << getLcd(patterns, a, 1) << "\n";
    cout << getLcd(patterns, 240, 2) << "\n";

    cout << "\n";
}
