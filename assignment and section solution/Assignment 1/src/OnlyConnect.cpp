/* File: OnlyConnect.cpp
 * Author: Derren Brown
 *
 * The file consists of a function that only remains the consonants in a string
 * and turns them into uppercase
 * as well as some tests.
 *
 * Puzzle: HRRYPTTR
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
#include "strlib.h"
#include <cctype>
using namespace std;

string onlyConnectize(string phrase) {
    phrase = toUpperCase(phrase);
    char ch = phrase[0];
    if(isalpha(ch))
    {
        if (ch != 'A' && ch != 'O' && ch != 'U' && ch != 'E' && ch != 'I')
        {
            if (phrase.length() == 1)
            {
                return phrase;
            }
            else
            {
                return  ch + onlyConnectize(phrase.substr(1));
            }
        }
    }
    if (phrase.length() > 1)
    {
        return onlyConnectize(phrase.substr(1));
    }
    else
    {
        return "";
    }
}






/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

STUDENT_TEST("Removes whitespace.")
{
    EXPECT_EQUAL(onlyConnectize("A B U"), "B");
}






