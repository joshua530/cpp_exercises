#include <iostream>

using std::cout;
using std::string;

#ifndef __STR_TRIM_FUNCS
#define __STR_TRIM_FUNCS
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

string trim(const string &s, const string &toTrim = " \n\t\r\f\v")
{
    return rtrim(ltrim(s, toTrim), toTrim);
}

void testTrim()
{
    string toTrim = "xabcd";
    string trimmed = trim(toTrim, "xd");
    cout << "Trim = ";
    if (trimmed == "abc") {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}
#endif

// int main()
// {
//     testTrim();
// }
