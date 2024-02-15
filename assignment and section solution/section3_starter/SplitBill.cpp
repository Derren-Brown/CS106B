/*
 * CS106B Section Handout Test Harness: Section 3
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "set.h"
#include "error.h"
using namespace std;

/*
 * Function: listPossiblePayments
 * -------------------------------
 * Write a function that takes as input a total amount of money
 * to pay (in dollars) and a set of all the people who ordered
 * something, then lists off every possible way you could split
 * the bill, assuming everyone pays a whole number of dollars.
 */
void listPossiblePaymentsHelper(int total, const Vector<string>& people, int idx, Vector<int>& record);
void listPossiblePayments(int total, const Set<string>& people) {
    if (total < 0)
    {
        error("Total amount is negative.");
    }
    if (people.isEmpty())
    {
        error("No people");
    }
    Vector<string> peopleAfter;
    for (string person: people)
    {
        peopleAfter.add(person);
    }
    Vector<int> record;
    listPossiblePaymentsHelper(total, peopleAfter, 0, record);
    return;
}

void listPossiblePaymentsHelper(int total, const Vector<string>& people, int idx, Vector<int>& record)
{
    if (idx == people.size())
    {
        for (int i = 0; i < idx; i++)
        {
            cout << people[i] << ": $" << record[i] << " ";
        }
        cout << "" << endl;
        return;
    }
    for (int i = 0; i <= total; i++)
    {
        record.add(i);
        listPossiblePaymentsHelper(total - i, people, idx + 1, record);
        record.remove(idx);
    }
}
/* * * * * Provided Tests Below This Point * * * * */

/*
 * Since this is a void function, we don't have a return value to verify with.
 * We will instead just run your code to make sure there is no obvious error.
 */
PROVIDED_TEST("Provided Test: Run the provided example. There should be 15 entries.") {
    Set<string> s = {"A", "B", "C"};
    listPossiblePayments(4, s);
}
