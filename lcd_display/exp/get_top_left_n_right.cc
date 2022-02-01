#include "patterns.cc"
#include "split_number.cc"

/**
 * Gets 'top left and top right' portion of toFormat in 'LCD' display
 *
 * @param patterns the characters occupying the top,middle and bottom portions
 * of the 'LCD' display for the numbers 0-9
 * @param toFormat the number for which the top 'LCD' portion is to be obtained
 * @param size the size of the LCD display
 */
string
getTopLeftAndRight(unordered_map<string, unordered_map<int, string>> patterns,
                   int toFormat, int size)
{
    if (toFormat == 0 || size == 0)
        return "";

    string placeholder = "";
    vector<int> nums = splitNumber(toFormat);

    for (int k = 0; k < size; ++k) {
        for (vector<int>::const_iterator i = nums.begin(); i != nums.end();
             ++i) {
            placeholder += getPattern(patterns, "topLeft", *i);
            for (int j = 0; j < size; ++j)
                placeholder += " ";
            placeholder += getPattern(patterns, "topRight", *i);
            placeholder += " ";
        }
        // remove extra space at the end
        placeholder = placeholder.substr(0, placeholder.size() - 1);
        placeholder += "\n";
    }
    // remove extra new line at the end
    placeholder = placeholder.substr(0, placeholder.size() - 1);

    return placeholder;
}

void testGetTopLeftAndRight()
{
    string expected_123456789_Size_1 =
        getPattern(patterns, "topLeft", 1) + " " +
        getPattern(patterns, "topRight", 1) + " " +
        getPattern(patterns, "topLeft", 2) + " " +
        getPattern(patterns, "topRight", 2) + " " +
        getPattern(patterns, "topLeft", 3) + " " +
        getPattern(patterns, "topRight", 3) + " " +
        getPattern(patterns, "topLeft", 4) + " " +
        getPattern(patterns, "topRight", 4) + " " +
        getPattern(patterns, "topLeft", 5) + " " +
        getPattern(patterns, "topRight", 5) + " " +
        getPattern(patterns, "topLeft", 6) + " " +
        getPattern(patterns, "topRight", 6) + " " +
        getPattern(patterns, "topLeft", 7) + " " +
        getPattern(patterns, "topRight", 7) + " " +
        getPattern(patterns, "topLeft", 8) + " " +
        getPattern(patterns, "topRight", 8) + " " +
        getPattern(patterns, "topLeft", 9) + " " +
        getPattern(patterns, "topRight", 9);
    string expected_123456789_Size_2_OneRow =
        getPattern(patterns, "topLeft", 1) + " " + " " +
        getPattern(patterns, "topRight", 1) + " " +
        getPattern(patterns, "topLeft", 2) + " " + " " +
        getPattern(patterns, "topRight", 2) + " " +
        getPattern(patterns, "topLeft", 3) + " " + " " +
        getPattern(patterns, "topRight", 3) + " " +
        getPattern(patterns, "topLeft", 4) + " " + " " +
        getPattern(patterns, "topRight", 4) + " " +
        getPattern(patterns, "topLeft", 5) + " " + " " +
        getPattern(patterns, "topRight", 5) + " " +
        getPattern(patterns, "topLeft", 6) + " " + " " +
        getPattern(patterns, "topRight", 6) + " " +
        getPattern(patterns, "topLeft", 7) + " " + " " +
        getPattern(patterns, "topRight", 7) + " " +
        getPattern(patterns, "topLeft", 8) + " " + " " +
        getPattern(patterns, "topRight", 8) + " " +
        getPattern(patterns, "topLeft", 9) + " " + " " +
        getPattern(patterns, "topRight", 9);
    string expected_123456789_Size_2 = expected_123456789_Size_2_OneRow + "\n" +
                                       expected_123456789_Size_2_OneRow;
    string expectedSize_0 = "";
    string expected_0 = "";

    string actual_123456789_Size_1 = getTopLeftAndRight(patterns, 123456789, 1);
    string actual_123456789_Size_2 = getTopLeftAndRight(patterns, 123456789, 2);
    string actualSize_0 = getTopLeftAndRight(patterns, 123456789, 0);
    string actual_0 = getTopLeftAndRight(patterns, 0, 2);

    cout << "123456789_Size_1 = ";
    if (actual_123456789_Size_1 == expected_123456789_Size_1)
        cout << "Success";
    else
        cout << "Failed";
    cout << "\n";

    cout << "123456789_Size_2 = ";
    if (actual_123456789_Size_2 == expected_123456789_Size_2)
        cout << "Success";
    else
        cout << "Failed";
    cout << "\n";

    cout << "Size_0 = ";
    if (actualSize_0 == expectedSize_0)
        cout << "Success";
    else
        cout << "Failed";
    cout << "\n";

    cout << "0 = ";
    if (actual_0 == expected_0)
        cout << "Success";
    else
        cout << "Failed";
    cout << "\n";
}

// int main(int argc, char **argv)
// {
//     testGetTopLeftAndRight();
// }
