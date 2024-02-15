/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include "testing/SimpleTest.h"
#include "lexicon.h"
#include <string>
using namespace std;

int calculateSubString(const Lexicon& words, string word);
string mostXzibitWord(const Lexicon& words) {
    int max = 0;
    string mostWord;
    for (string word: words)
    {
        int num = calculateSubString(words, word);
        if (max < num)
        {
            max = num;
            mostWord = word;
        }
    }
    cout << "Most word: " << mostWord << "Max: " << max << endl;
    return mostWord;
}

int calculateSubString(const Lexicon& words, string word)
{
    Lexicon myWords;
    for (int i = 0; i < word.length(); i++)
    {
        for (int j = i; j < word.length(); j++)
        {
            string sub = word.substr(i, j - i + 1);
            if (words.contains(sub))
            {
                myWords.add(sub);
            }
        }
    }
    return myWords.size();
}

/* * * * * Provided Tests Below This Point * * * * */

static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Example from handout") {
    Lexicon& lex = sharedLexicon();
    EXPECT_EQUAL(mostXzibitWord(lex), "foreshadowers");
}
