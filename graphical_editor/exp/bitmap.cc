#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::vector;

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

void testCreateBitmap()
{
    vector<vector<char>> expected;
    vector<char> a{'0', '0', '0'};
    expected.push_back(a);
    expected.push_back(a);
    expected.push_back(a);
    vector<vector<char>> actual = createBitmap(3, 3, '0');
    vector<vector<char>> empty = createBitmap(0, 0, '0');
    vector<vector<char>> emptyV;

    cout << "Bitmap = ";
    if (expected == actual) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Empty bitmap = ";
    if (empty == emptyV) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

// int main()
// {
//     testCreateBitmap();
// }
