#include <cmath>
#include <iostream>

using std::cout;

double toNearestSecondDecimal(double n)
{
    n *= 100;
    n = round(n);
    n /= 100;
    return n;
}

void testToNearestSecondDecimal()
{
    double a = 12.225;
    double b = 0.02;
    double c = 0.035;

    double actualA = toNearestSecondDecimal(a);
    double actualB = toNearestSecondDecimal(b);
    double actualC = toNearestSecondDecimal(c);
    cout << "Test a: ";
    if (actualA == 12.23)
        cout << "Passed";
    else
        cout << "Failed";
    cout << "\n";

    cout << "Test b: ";
    if (actualB == 0.02)
        cout << "Passed";
    else
        cout << "Failed";
    cout << "\n";

    cout << "Test c: ";
    if (actualC == 0.04)
        cout << "Passed";
    else
        cout << "Failed";
    cout << "\n";
}

// int main(int argc, char **argv)
// {
//     testToNearestSecondDecimal();
// }
