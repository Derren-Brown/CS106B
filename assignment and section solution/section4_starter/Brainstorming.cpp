/*
 * CS106B Section Handout Test Harness: Section 4
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
#include "map.h"
using namespace std;

/*
 * Function: matches
 * ------------------
 * Your task is to write a function that takes as input a
 * string and a pattern, then returns whether that string
 * matches the pattern.
 */
bool matchesHelper(const string& text, int idx1, const string& pattern, int idx2);
bool matches(const string& text, const string& pattern) {
    return matchesHelper(text, 0, pattern, 0);
}

bool matchesHelper(const string& text, int idx1, const string& pattern, int idx2)
{
    if (idx1 == text.size())
    {
        return true;
    }
    switch(pattern[idx2]) {
    case '*':
        if (matchesHelper(text, idx1 + 1, pattern, idx2))
        {
            return true;
        }break;
    case '.':
        if (isalpha(text[idx1]))
        {
            if (matchesHelper(text, idx1 + 1, pattern, idx2 + 1))
            {
                return true;
            }
        }break;
    case '?':
        if (matchesHelper(text, idx1, pattern, idx2 + 1))
        {
            return true;
        }
        else if (isalpha(text[idx1]))
        {
            if (matchesHelper(text, idx1 + 1, pattern, idx2 + 1))
            {
                return true;
            }
        }break;
    default:
        if (text[idx1] == pattern[idx2])
        {
            if (matchesHelper(text, idx1 + 1, pattern, idx2 + 1))
            {
                return true;
            }
        }break;
    }
    return false;
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Testing *") {
    EXPECT_EQUAL(matches("apple", "a*"), true);
    EXPECT_EQUAL(matches("apply", "a*"), true);
    EXPECT_EQUAL(matches("apoplexy", "a*"), true);
    EXPECT_EQUAL(matches("Amicus", "a*"), false);
    EXPECT_EQUAL(matches("banana", "a*"), false);
}

PROVIDED_TEST("Provided Test: Testing .") {
    EXPECT_EQUAL(matches("three", "th..."), true);
    EXPECT_EQUAL(matches("threshold", "th..."), false);
}

PROVIDED_TEST("Provided Test: Testing ?") {
    EXPECT_EQUAL(matches("color", "colo?r"), true);
    EXPECT_EQUAL(matches("colour", "colo?r"), true);
    EXPECT_EQUAL(matches("colouxr", "colo?r"), false);
}
