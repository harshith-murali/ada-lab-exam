/* ================================================================ */
/* STRING MATCHING - NAIVE PATTERN MATCHING */
/* ================================================================ */

/*
Algorithm name: Naive String Matching
Problem it solves:
Finds every occurrence of a pattern inside a text by checking each possible
alignment from left to right.
Time complexity: O((n - m + 1) * m)
Space complexity: O(1)
*/

#include <stdio.h>
#include <string.h>

/* Prints all positions where pattern occurs in text. */
void naivePatternMatching(const char text[], const char pattern[]) {
    int textLength = (int)strlen(text);
    int patternLength = (int)strlen(pattern);
    int found = 0;

    printf("Text: \"%s\"\nPattern: \"%s\"\nMatches at indices: ", text, pattern);
    for (int start = 0; start <= textLength - patternLength; start++) {
        int matched = 0;
        while (matched < patternLength &&
               text[start + matched] == pattern[matched]) {
            matched++;
        }
        if (matched == patternLength) {
            printf("%d ", start);
            found = 1;
        }
    }
    if (!found) {
        printf("none");
    }
    printf("\n\n");
}

int main(void) {
    printf("Naive String Matching\n\n");
    naivePatternMatching("ABAAABCDBBABCDDEBCABC", "ABC");
    naivePatternMatching("AAAAA", "AA");
    naivePatternMatching("HELLO WORLD", "TEST");
    return 0;
}

/*
High-level idea:
The pattern is placed at every possible position in the text.
For each position, characters are compared one by one.
If all pattern characters match, the starting index is reported.
On the first test case, most alignments fail quickly. At index 4 the letters
A, B, and C all match, so 4 is printed; the same scan later finds 10 and 18.
*/
