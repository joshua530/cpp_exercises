#include "patterns.cc"
#include "split_number.cc"

string getBottom(unordered_map<string, unordered_map<int, string>> patterns,
                 int num, int size)
{
    if (num == 0 || size == 0)
        return "";

    vector<int> nums = splitNumber(num);
    string placeholder = "";

    // get all of the row
    //   for each number
    for (vector<int>::const_iterator i = nums.begin(); i != nums.end(); ++i) {
        placeholder += " ";
        for (int j = 0; j < size; ++j)
            placeholder += getPattern(patterns, "bottom", *i);
        placeholder += " ";
        placeholder += " ";
    }
    // remove extra space at the end
    placeholder = placeholder.substr(0, placeholder.size() - 1);

    return placeholder;
}

void testGetBottom()
{
    string bottom_1234567890_Size_1 =
        " " + getPattern(patterns, "bottom", 1) + " " + " " + " " +
        getPattern(patterns, "bottom", 2) + " " + " " + " " +
        getPattern(patterns, "bottom", 3) + " " + " " + " " +
        getPattern(patterns, "bottom", 4) + " " + " " + " " +
        getPattern(patterns, "bottom", 5) + " " + " " + " " +
        getPattern(patterns, "bottom", 6) + " " + " " + " " +
        getPattern(patterns, "bottom", 7) + " " + " " + " " +
        getPattern(patterns, "bottom", 8) + " " + " " + " " +
        getPattern(patterns, "bottom", 9) + " " + " " + " " +
        getPattern(patterns, "bottom", 0) + " ";
    string bottom_1234567890_Size_2 =
        " " + getPattern(patterns, "bottom", 1) +
        getPattern(patterns, "bottom", 1) + " " + " " + " " +
        getPattern(patterns, "bottom", 2) + getPattern(patterns, "bottom", 2) +
        " " + " " + " " + getPattern(patterns, "bottom", 3) +
        getPattern(patterns, "bottom", 3) + " " + " " + " " +
        getPattern(patterns, "bottom", 4) + getPattern(patterns, "bottom", 4) +
        " " + " " + " " + getPattern(patterns, "bottom", 5) +
        getPattern(patterns, "bottom", 5) + " " + " " + " " +
        getPattern(patterns, "bottom", 6) + getPattern(patterns, "bottom", 6) +
        " " + " " + " " + getPattern(patterns, "bottom", 7) +
        getPattern(patterns, "bottom", 7) + " " + " " + " " +
        getPattern(patterns, "bottom", 8) + getPattern(patterns, "bottom", 8) +
        " " + " " + " " + getPattern(patterns, "bottom", 9) +
        getPattern(patterns, "bottom", 9) + " " + " " + " " +
        getPattern(patterns, "bottom", 0) + getPattern(patterns, "bottom", 0) +
        " ";
    string bottom_0 = "";
    string bottom_Size_0 = "";
    string actualBottom_1234567890_Size_1 = getBottom(patterns, 1234567890, 1);
    string actualBottom_1234567890_Size_2 = getBottom(patterns, 1234567890, 2);
    string actualBottom_0 = getBottom(patterns, 0, 1);
    string actualBottom_Size_0 = getBottom(patterns, 1, 0);

    cout << "bottom_1234567890_Size_1 = ";
    if (bottom_1234567890_Size_1 == actualBottom_1234567890_Size_1) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "bottom_1234567890_Size_2 = ";
    if (bottom_1234567890_Size_2 == actualBottom_1234567890_Size_2) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "bottom_0 = ";
    if (bottom_0 == actualBottom_0) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "bottom_Size_0 = ";
    if (bottom_Size_0 == actualBottom_Size_0) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

// int main(int argc, const char *argv[])
// {
//     testGetBottom();
// }
