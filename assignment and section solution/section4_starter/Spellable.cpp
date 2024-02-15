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
#include <string>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "set.h"
#include "strlib.h"
using namespace std;

/*
 * Function: isElementSpellable
 * -----------------------------
 * Write a function that accepts as input a string and a Set<string>
 * containing all element symbols (stored with the proper
 * capitalization), then returns whether that string can be
 * written using only element symbols.
 */
bool isElementSpellableHelper(const string& text, const Set<string>& symbols, int idx, string& result);
bool isElementSpellable(const string& text, const Set<string>& symbols) {
    string result;
    bool val = isElementSpellableHelper(text, symbols, 0, result);
    cout << result << endl;
    return val;
}

bool isElementSpellableHelper(const string& text, const Set<string>& symbols, int idx, string& result)
{
    if (idx == text.length())
    {
        return true;
    }
    for (string symbol: symbols)
    {
        /* Roughly screening.
         * If not, the program will be very slow and in my computer it crashed.
         */
        if (tolower(symbol[0]) != tolower(text[idx]))
        {
            continue;
        }

        if (equalsIgnoreCase(text.substr(idx, symbol.length()),symbol))
        {
            result += symbol;
            if (isElementSpellableHelper(text, symbols, idx + symbol.length(), result))
            {
                return true;
            }
            result.erase(result.length() - symbol.length());
        }
    }
    return false;
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Verify that the solution works on examples from the handout.") {
  Set<string> symbols = {
    "H", "He", "Li", "Be", "B",
    "C", "N", "O", "F", "Ne", "Na",
    "Mg", "Al", "Si", "P", "S", "Cl",
    "Ar", "K", "Ca", "Sc", "Ti", "V",
    "Cr", "Mn", "Fe", "Co", "Ni",
    "Cu", "Zn", "Ga", "Ge", "As",
    "Se", "Br", "Kr", "Rb", "Sr",
    "Y", "Zr", "Nb", "Mo", "Tc",
    "Ru", "Rh", "Pd", "Ag", "Cd",
    "In", "Sn", "Sb", "Te", "I",
    "Xe", "Cs", "Ba", "La", "Ce",
    "Pr", "Nd", "Pm", "Sm", "Eu",
    "Gd", "Tb", "Dy", "Ho", "Er",
    "Tm", "Yb", "Lu", "Hf", "Ta",
    "W", "Re", "Os", "Ir", "Pt",
    "Au", "Hg", "Tl", "", "Pb",
    "Bi", "Po", "At", "Rn", "Fr",
    "Ra", "Ac", "Th", "Pa", "U",
    "Np", "Pu", "Am", "Cm", "Bk",
    "Cf", "Es", "Fm", "Md", "No",
    "Lr", "Rf", "Db", "Sg", "Bh",
    "Hs", "Mt", "Ds", "Rg", "Cn",
    "Nh", "Fl", "Mc", "Lv", "Ts",
    "Og"
  };
  EXPECT_EQUAL(isElementSpellable("feline", symbols), true);

  EXPECT_EQUAL(isElementSpellable("interesting", symbols), false);
  // NOTE that the original version of the test answer is wrong and we need to revise it.
  EXPECT_EQUAL(isElementSpellable("Chemowizardry", symbols), false);
  EXPECT_EQUAL(isElementSpellable("Chemowizrdy", symbols), true);
}
