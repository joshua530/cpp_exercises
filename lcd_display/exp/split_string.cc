#include <iostream>
#include <string>

using std::cout;
using std::string;

int main()
{
    string name = "Joshua Omari";
    string separator = " ";
    int start = 0, end = name.find(separator);

    while (end != -1) {
        cout << name.substr(start, end - start) << "\n";
        start = end + separator.size();
        end = name.find(" ", start);
    }
    cout << name.substr(start) << "\n";
}
