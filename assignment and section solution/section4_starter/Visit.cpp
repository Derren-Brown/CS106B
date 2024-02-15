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
#include <cmath>
using namespace std;

double computeTravelTime(const GPoint p1, const GPoint p2);
bool canVisitAllSitesHelper(const Vector<GPoint>& sites, double travelTimeAvailable,
                            GPoint now, Set<GPoint>& left);
/*
 * Function: canVisitAllSites
 * ---------------------------
 * Write a function that takes as input a list of all the
 * sites you’d like to visit and an amount of free time
 * available to you and returns whether it’s possible to
 * visit all those sites in the allotted time (assume you’ve
 * already factored inthe cost of speaking at each site
 * and that you’re just concerned about the travel time.)
 */
bool canVisitAllSites(const Vector<GPoint>& sites, double travelTimeAvailable) {
    Set<GPoint> left;
    for (GPoint point: sites)
    {
        left.add(point);
    }
    return canVisitAllSitesHelper(sites, travelTimeAvailable, sites[0], left);
}

bool canVisitAllSitesHelper(const Vector<GPoint>& sites, double travelTimeAvailable,
                            GPoint now, Set<GPoint>& left)
{
    if (travelTimeAvailable < 0)
    {
        return false;
    }
    if (left.isEmpty())
    {
        return true;
    }
    Set<GPoint> leftCopy = left;
    for (GPoint point: leftCopy)
    {
        left.remove(point);
        if (canVisitAllSitesHelper(sites, travelTimeAvailable - computeTravelTime(now, point), point, left))
        {
            return true;
        }
        left += point;
    }
    return false;
}

double computeTravelTime(const GPoint p1, const GPoint p2)
{
    double deltaX = p1.x - p2.x, deltaY = p1.y - p2.y;
    double travelTime = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    return travelTime;
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Simple examples!") {
    Vector<GPoint> sites1 = {{0, 0}, {5, 5}};
    Vector<GPoint> sites2 = {{0, 0}, {2, 2}, {5, 5}};
    EXPECT_EQUAL(canVisitAllSites(sites1, 8), true);
    EXPECT_EQUAL(canVisitAllSites(sites2, 8), true);
}
