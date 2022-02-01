#include "patterns.cc"
#include "split_number.cc"

string getMiddle(unordered_map<string, unordered_map<int, string>> patterns,
                 int num, int size)
{
    if (num == 0 || size == 0)
        return "";

    string placeholder = "";
    vector<int> nums = splitNumber(num);

    for (vector<int>::const_iterator i = nums.begin(); i != nums.end(); ++i) {
        placeholder += " ";
        for (int j = 0; j < size; ++j)
            placeholder += getPattern(patterns, "middle", *i);
        placeholder += " ";
        placeholder += " ";
    }
    // delete extra space at the end
    placeholder = placeholder.substr(0, placeholder.size() - 1);
    return placeholder;
}

void testGetMiddle()
{
    string expectedMid_123456789_Size_1 =
        " " + getPattern(patterns, "middle", 1) + " " + " " + " " +
        getPattern(patterns, "middle", 2) + " " + " " + " " +
        getPattern(patterns, "middle", 3) + " " + " " + " " +
        getPattern(patterns, "middle", 4) + " " + " " + " " +
        getPattern(patterns, "middle", 5) + " " + " " + " " +
        getPattern(patterns, "middle", 6) + " " + " " + " " +
        getPattern(patterns, "middle", 7) + " " + " " + " " +
        getPattern(patterns, "middle", 8) + " " + " " + " " +
        getPattern(patterns, "middle", 9) + " ";
    string expectedMid_123456789_Size_2 =
        " " + getPattern(patterns, "middle", 1) +
        getPattern(patterns, "middle", 1) + " " + " " + " " +
        getPattern(patterns, "middle", 2) + getPattern(patterns, "middle", 2) +
        " " + " " + " " + getPattern(patterns, "middle", 3) +
        getPattern(patterns, "middle", 3) + " " + " " + " " +
        getPattern(patterns, "middle", 4) + getPattern(patterns, "middle", 4) +
        " " + " " + " " + getPattern(patterns, "middle", 5) +
        getPattern(patterns, "middle", 5) + " " + " " + " " +
        getPattern(patterns, "middle", 6) + getPattern(patterns, "middle", 6) +
        " " + " " + " " + getPattern(patterns, "middle", 7) +
        getPattern(patterns, "middle", 7) + " " + " " + " " +
        getPattern(patterns, "middle", 8) + getPattern(patterns, "middle", 8) +
        " " + " " + " " + getPattern(patterns, "middle", 9) +
        getPattern(patterns, "middle", 9) + " ";
    string expectedMid_0 = "";
    string expectedMidSize_0 = "";

    string actualMid_123456789_Size_1 = getMiddle(patterns, 123456789, 1);
    string actualMid_123456789_Size_2 = getMiddle(patterns, 123456789, 2);
    string actualMid_0 = getMiddle(patterns, 0, 2);
    string actualMidSize_0 = getMiddle(patterns, 1, 0);

    cout << "Mid_123456789_Size_1 = ";
    if (expectedMid_123456789_Size_1 == actualMid_123456789_Size_1) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Mid_123456789_Size_2 = ";
    if (expectedMid_123456789_Size_2 == actualMid_123456789_Size_2) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Mid_0 = ";
    if (expectedMid_0 == actualMid_0) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "MidSize_0 = ";
    if (expectedMidSize_0 == actualMidSize_0) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

// int main()
// {
//     testGetMiddle();
// }
