/* File: Sandpiles.cpp
 * Author: Derren Brown
 */
#include "Sandpiles.h"
#include "GUI/SimpleTest.h"
using namespace std;

// Function: Return the result of the sand-drop.
void dropSandOn(Grid<int>& world, int row, int col) {
    if (world.inBounds(row, col))
    {
        world[row][col]++;
        if (world[row][col] == 4)
        {
            world[row][col] = 0;
            dropSandOn(world, row - 1, col);
            dropSandOn(world, row + 1, col);
            dropSandOn(world, row, col - 1);
            dropSandOn(world, row, col + 1);
        }
    }
}






/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Dropping into an empty cell only changes that cell.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 1, 3 },
        { 3, 3, 3 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Non-chaining topples work.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0 },
        { 1, 3, 1 },
        { 0, 2, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 2, 0, 2 },
        { 0, 3, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Two topples chain.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 3, 3, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

STUDENT_TEST("Edge condition.")
{
    Grid<int> before = {
        { 3, 0, 0 },
        { 0, 0, 2 },
        { 0, 3, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 1, 0, 2 },
        { 0, 3, 0 }
    };

    dropSandOn(before, 0, 0);
    EXPECT_EQUAL(before, after);
}









