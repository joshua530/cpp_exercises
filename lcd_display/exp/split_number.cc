#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::stack;
using std::vector;

#ifndef __FUNC_SPLIT_NUMBER
#define __FUNC_SPLIT_NUMBER
vector<int> splitNumber(int i)
{
    stack<int> theStack;
    vector<int> tmp;

    if (i == 0) {
        tmp.push_back(0);
        return tmp;
    }
    if (i < 1)
        i = -i;

    while (i != 0) {
        int x = i % 10;
        theStack.push(x);
        i -= x;
        i /= 10;
    }

    while (!theStack.empty()) {
        tmp.push_back(theStack.top());
        theStack.pop();
    }

    return tmp;
}
#endif

#ifndef __FUNC_TEST_SPLIT_NUMBER
#define __FUNC_TEST_SPLIT_NUMBER
void testSplitNumber()
{
    vector<int> x = {1, 2, 3};
    int num = 123;
    vector<int> e_x = splitNumber(num);

    cout << "Split number = ";
    if (e_x == x) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}
#endif

// int main()
// {
//     testSplitNumber();
// }
