#include <string>
#include <vector>

using std::string;
using std::vector;

#ifndef __STRING_FUNCS
#define __STRING_FUNCS
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

/**
 * trims characters from the beginning and end of the string
 *
 * whitespace is trimmed by default
 */
string trim(const string &s, const string &toTrim = " \n\t\r\f\v")
{
    return rtrim(ltrim(s, toTrim), toTrim);
}

vector<string> splitToChars(string toSplit)
{
    vector<string> chars;
    if (toSplit.size() == 0)
        chars.push_back("");

    for (int i = 0; i < toSplit.size(); ++i) {
        string s(1, toSplit[i]);
        chars.push_back(s);
    }
    return chars;
}

/**
 * splits a string using a provided delimiter
 *
 * if there are two delimiters following one another, both delimiters
 * will be excluded from the split segments
 */
vector<string> splitString(string toSplit, string delim)
{
    toSplit = trim(toSplit);

    if (delim == "")
        return splitToChars(toSplit);

    int lenDelim = delim.size();
    // for knowing whether we have encountered a full delimiter or not
    int delimPos = -1;
    string currentDelim = "";
    vector<string> strSegments;
    int posAfterLastSplit = 0;

    for (int i = 0; i < toSplit.size(); ++i) {
        if (toSplit[i] == delim[delimPos + 1]) {
            // build delimiter
            ++delimPos;
            currentDelim += toSplit[i];
        } else {
            // delimiter build failed
            // reset delimiter vars for next rebuild
            delimPos = -1;
            currentDelim = "";
        }

        if (currentDelim == delim) {
            // we have successfully built a delimiter, split the string
            int lastSplitToCurrent = (i - posAfterLastSplit);
            int lenSegment = (lastSplitToCurrent - lenDelim) + 1;
            string segment = toSplit.substr(posAfterLastSplit, lenSegment);
            // don't append empty substring due to a delimiter encountered
            // two times or more in succession
            if (segment != "")
                strSegments.push_back(segment);
            posAfterLastSplit = i + 1;
            // reset delimiter vars for next rebuild
            delimPos = -1;
            currentDelim = "";
        } else {
            // we have reached the end of the string without fully building a
            // delimiter(or another delimiter if there were others built
            // already), add the rest of the string from the last splitting
            // point to the segments we already have
            if (i == (toSplit.size() - 1)) {
                int lenSubstring = (toSplit.size() - posAfterLastSplit);
                string segment =
                    toSplit.substr(posAfterLastSplit, lenSubstring);
                strSegments.push_back(segment);
            }
        }
    }

    return strSegments;
}
#endif
