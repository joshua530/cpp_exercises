#include "patterns.cc"
#include "split_number.cc"

/**
 * Gets 'top' portion of toFormat in 'LCD' display
 *
 * @param patterns the characters occupying the top,middle and bottom portions
 * of the 'LCD' display for the numbers 0-9
 * @param toFormat the number for which the top 'LCD' portion is to be obtained
 * @param size the size of the LCD display
 */
string getTop(unordered_map<string, unordered_map<int, string>> patterns,
              int toFormat, int size)
{
    string placeholder = "";

    if (toFormat == 0 || size == 0)
        return placeholder;

    vector<int> nums = splitNumber(toFormat);

    for (vector<int>::const_iterator i = nums.begin(); i != nums.end(); ++i) {
        placeholder += " ";
        for (int j = 0; j < size; ++j)
            placeholder += getPattern(patterns, "top", *i);
        placeholder += " ";
        placeholder += " ";
    }

    // remove space at the end of the string
    placeholder = placeholder.substr(0, (placeholder.size() - 1));

    return placeholder;
}

void testGetTop(unordered_map<string, unordered_map<int, string>> patterns)
{
    int num = 1234567890;
    string expected_123456789 =
        " " + (getPattern(patterns, "top", 1)) + " " + " " + " " +
        (getPattern(patterns, "top", 2)) + " " + " " + " " +
        (getPattern(patterns, "top", 3)) + " " + " " + " " +
        (getPattern(patterns, "top", 4)) + " " + " " + " " +
        (getPattern(patterns, "top", 5)) + " " + " " + " " +
        (getPattern(patterns, "top", 6)) + " " + " " + " " +
        (getPattern(patterns, "top", 7)) + " " + " " + " " +
        (getPattern(patterns, "top", 8)) + " " + " " + " " +
        (getPattern(patterns, "top", 9)) + " ";
    string expected_0 = "";
    string expectedSize_0 = "";

    string actual_123456789 = getTop(patterns, 123456789, 1);
    string actual_0 = getTop(patterns, 0, 1);
    string actualSize_0 = getTop(patterns, 123456789, 0);

    cout << "Top formatting 123456789 = ";
    if (expected_123456789 == actual_123456789) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Top formatting 0 = ";
    if (expected_0 == actual_0) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Top formatting with size 0 = ";
    if (expectedSize_0 == actualSize_0) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

// int main()
// {
//     testGetTop(patterns);
// }
