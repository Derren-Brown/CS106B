#include "HumanPyramids.h"
#include "error.h"
#include "map.h"
#include "gridlocation.h"
using namespace std;

bool inBounds(GridLocation location, int pyramidHeight);
GridLocation createGridLocation(int row, int col);
Map<GridLocation, double> weightsOnBack;
double weightOnBackOf(int row, int col, int pyramidHeight) {
    if (!inBounds(createGridLocation(row, col), pyramidHeight))
    {
        error("Coordinates not in bounds.");
    }
    if (!row)
    {
        return 0;
    }
    else
    {
        double weight = 0;
        GridLocation lo1(row - 1, col - 1);
        if (inBounds(lo1, pyramidHeight))
        {
            if (!weightsOnBack.containsKey(lo1))
            {
                weightsOnBack.put(lo1, (weightOnBackOf(lo1.row, lo1.col, pyramidHeight) + 160) / 2);
            }
            weight += weightsOnBack[lo1];
        }
        GridLocation lo2(row - 1, col);
        if (inBounds(lo2, pyramidHeight))
        {
            if (!weightsOnBack.containsKey(lo2))
            {
                weightsOnBack.put(lo2, (weightOnBackOf(lo2.row, lo2.col, pyramidHeight) + 160) / 2);
            }
            weight += weightsOnBack[lo2];
        }
        return weight;
    }
}

bool inBounds(GridLocation location, int pyramidHeight)
{
    if (location.row > -1 && location.row < pyramidHeight)
    {
        if (location.col > -1 && location.col <= location.row)
        {
            return true;
        }
    }
    return false;
}

GridLocation createGridLocation(int row, int col)
{
    GridLocation location(row, col);
    return location;
}

/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */

STUDENT_TEST("Check the person in row 0.")
{
    EXPECT_EQUAL(weightOnBackOf(0,0,5), 0);
}

/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
