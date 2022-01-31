// get all students expenses
// average them to find the average cost
// money_moved_around = 0
// for each student
//   if the student_cost is greater than the average cost:
//      add student_cost - average_cost to money_moved_around
// return money_moved_around

#include "round_off.cc"
#include <iostream>

using std::cout;

double equalize(int numStudents, double *expenditure)
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

void testEqualize()
{

    double firstBatch[] = {10.00, 20.00, 30.00};
    double secondBatch[] = {15.00, 15.01, 3.00, 3.01};

    double firstResult = equalize(3, firstBatch);
    double secondResult = equalize(4, secondBatch);

    cout << "Test 1: ";
    if (firstResult == 10.00) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";

    cout << "Test 2: ";
    if (secondResult == 11.99) {
        cout << "Success";
    } else {
        cout << "Failed";
    }
    cout << "\n";
}

// int main(int argc, char **argv)
// {
//     testEqualize();
// }
