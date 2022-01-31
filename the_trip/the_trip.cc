#include <cmath>
#include <iostream>
#include <vector>

using std::cout;
using std::vector;

double toNearestSecondDecimal(double n)
{
    n *= 100;
    n = round(n);
    n /= 100;
    return n;
}

double equalize(int numStudents, vector<double> expenditure)
{
    double total = 0.0;
    for (int i = 0; i < numStudents; ++i) {
        total += expenditure[i];
    }
    total = toNearestSecondDecimal(total);

    double average = total / numStudents;
    average = toNearestSecondDecimal(average);

    double moneyMovedAround = 0.0;
    for (int i = 0; i < numStudents; ++i) {
        double currentCost = expenditure[i];
        // if a student spent more than the average, then the
        // cost above the average should be contributed by someone
        // else. It will be 'moved around' when that happens
        if (currentCost > average) {
            moneyMovedAround += (currentCost - average);
        }
    }

    return moneyMovedAround;
}

int main(int argc, const char **argv)
{
    int numStudents[] = {3, 4, 0};
    vector<vector<double>> studentCosts{{10.00, 20.00, 30.00},
                                        {15.00, 15.01, 3.00, 3.01}};

    for (int i = 0; i < 3, numStudents[i] != 0; ++i) {
        printf("$%.2f\n", equalize(numStudents[i], studentCosts[i]));
    }
}
