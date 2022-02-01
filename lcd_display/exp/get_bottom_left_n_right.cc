#include "patterns.cc"
#include "split_number.cc"

string getBottomLeftAndRight(
    unordered_map<string, unordered_map<int, string>> patterns, int num,
    int size)
{
    if (num == 0 || size == 0)
        return "";

    string placeholder = "";
    vector<int> nums = splitNumber(num);

    // get <size> rows
    for (int j = 0; j < size; ++j) {
        // get one row
        for (vector<int>::const_iterator i = nums.begin(); i != nums.end();
             ++i) {
            placeholder += getPattern(patterns, "bottomLeft", *i);
            // get <size> spaces
            for (int k = 0; k < size; ++k)
                placeholder += " ";
            placeholder += getPattern(patterns, "bottomRight", *i);
            placeholder += " ";
        }
        // remove extra space at the end
        placeholder = placeholder.substr(0, placeholder.size() - 1);
        placeholder += "\n";
    }
    // remove extra \n at the end
    placeholder = placeholder.substr(0, placeholder.size() - 1);
    return placeholder;
}

void testGetBottomLeftAndRight()
{
    string bottomLeftAndRight_1234567890_Size_1 =
        getPattern(patterns, "bottomLeft", 1) + " " +
        getPattern(patterns, "bottomRight", 1) + " " +
        getPattern(patterns, "bottomLeft", 2) + " " +
        getPattern(patterns, "bottomRight", 2) + " " +
        getPattern(patterns, "bottomLeft", 3) + " " +
        getPattern(patterns, "bottomRight", 3) + " " +
        getPattern(patterns, "bottomLeft", 4) + " " +
        getPattern(patterns, "bottomRight", 4) + " " +
        getPattern(patterns, "bottomLeft", 5) + " " +
        getPattern(patterns, "bottomRight", 5) + " " +
        getPattern(patterns, "bottomLeft", 6) + " " +
        getPattern(patterns, "bottomRight", 6) + " " +
        getPattern(patterns, "bottomLeft", 7) + " " +
        getPattern(patterns, "bottomRight", 7) + " " +
        getPattern(patterns, "bottomLeft", 8) + " " +
        getPattern(patterns, "bottomRight", 8) + " " +
        getPattern(patterns, "bottomLeft", 9) + " " +
        getPattern(patterns, "bottomRight", 9) + " " +
        getPattern(patterns, "bottomLeft", 0) + " " +
        getPattern(patterns, "bottomRight", 0);
    string bottomLeftAndRight_1234567890_Size_2_OneRow =
        getPattern(patterns, "bottomLeft", 1) + " " + " " +
        getPattern(patterns, "bottomRight", 1) + " " +
        getPattern(patterns, "bottomLeft", 2) + " " + " " +
        getPattern(patterns, "bottomRight", 2) + " " +
        getPattern(patterns, "bottomLeft", 3) + " " + " " +
        getPattern(patterns, "bottomRight", 3) + " " +
        getPattern(patterns, "bottomLeft", 4) + " " + " " +
        getPattern(patterns, "bottomRight", 4) + " " +
        getPattern(patterns, "bottomLeft", 5) + " " + " " +
        getPattern(patterns, "bottomRight", 5) + " " +
        getPattern(patterns, "bottomLeft", 6) + " " + " " +
        getPattern(patterns, "bottomRight", 6) + " " +
        getPattern(patterns, "bottomLeft", 7) + " " + " " +
        getPattern(patterns, "bottomRight", 7) + " " +
        getPattern(patterns, "bottomLeft", 8) + " " + " " +
        getPattern(patterns, "bottomRight", 8) + " " +
        getPattern(patterns, "bottomLeft", 9) + " " + " " +
        getPattern(patterns, "bottomRight", 9) + " " +
        getPattern(patterns, "bottomLeft", 0) + " " + " " +
        getPattern(patterns, "bottomRight", 0);
    string bottomLeftAndRight_1234567890_Size_2 =
        bottomLeftAndRight_1234567890_Size_2_OneRow + "\n" +
        bottomLeftAndRight_1234567890_Size_2_OneRow;
    string bottomLeftAndRight_0 = "";
    string bottomLeftAndRight_Size_0 = "";

    string actualBottomLeftAndRight_1234567890_Size_1 =
        getBottomLeftAndRight(patterns, 1234567890, 1);
    string actualBottomLeftAndRight_1234567890_Size_2 =
        getBottomLeftAndRight(patterns, 1234567890, 2);
    string actualBottomLeftAndRight_0 = getBottomLeftAndRight(patterns, 0, 1);
    string actualBottomLeftAndRight_Size_0 =
        getBottomLeftAndRight(patterns, 1, 0);

    cout << "bottomLeftAndRight_1234567890_Size_1 = ";
    if (actualBottomLeftAndRight_1234567890_Size_1 ==
        bottomLeftAndRight_1234567890_Size_1) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "bottomLeftAndRight_1234567890_Size_2 = ";
    if (actualBottomLeftAndRight_1234567890_Size_2 ==
        bottomLeftAndRight_1234567890_Size_2) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "bottomLeftAndRight_0 = ";
    if (actualBottomLeftAndRight_0 == bottomLeftAndRight_0) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "bottomLeftAndRight_Size_0 = ";
    if (actualBottomLeftAndRight_Size_0 == bottomLeftAndRight_Size_0) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

// int main(int argc, char *argv[])
// {
//     testGetBottomLeftAndRight();
// }
