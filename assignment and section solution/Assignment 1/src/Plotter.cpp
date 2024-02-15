// Author: Derren Brown
#include "Plotter.h"
#include "strlib.h"
using namespace std;

typedef struct
{
    double x;
    double y;
}coordinate;

bool penState(Vector<string> script);
PenStyle penStyleModify(Vector<string> script, PenStyle style);
coordinate draw(Vector<string> script, coordinate before, PenStyle style, bool ret);

void runPlotterScript(istream& input) {
    PenStyle style = {1, "black"};
    bool ret = false;
    coordinate now = {0, 0};
    for (string line; getline(input, line);)
    {
        Vector<string> script = stringSplit(line, " ");
        if (script.size() == 1)
        {
            ret = penState(script);
        }
        else if (script.size() == 2)
        {
            style = penStyleModify(script, style);
        }
        else if (script.size() == 3)
        {
            now = draw(script, now, style, ret);
        }
    }
}

bool penState(Vector<string> script)
{
    if (toLowerCase(script[0]) == "pendown")
    {
        return true;
    }
    return false;
}

PenStyle penStyleModify(Vector<string> script, PenStyle style)
{
    if (toLowerCase(script[0]) == "pencolor")
    {
        style.color = script[1];
    }
    else
    {
        style.width = stringToDouble(script[1]);
    }
    return style;
}

coordinate draw(Vector<string> script, coordinate before, PenStyle style, bool ret)
{
    coordinate after = {0, 0};
    if (toLowerCase(script[0]) == "moveabs")
    {
        after.x = stringToDouble(script[1]);
        after.y = stringToDouble(script[2]);
    }
    else
    {
        after.x = stringToDouble(script[1]) + before.x;
        after.y = stringToDouble(script[2]) + before.y;
    }
    if (ret)
    {
        drawLine(before.x, before.y, after.x, after.y, style);
    }
    return after;
}
