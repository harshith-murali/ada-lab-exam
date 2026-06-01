/* ================================================================ */
/* RUSSIAN PEASANT MULTIPLICATION */
/* ================================================================ */

/*
Algorithm name: Russian Peasant Multiplication
Problem it solves:
Multiplies two non-negative integers using repeated halving, doubling, and
addition when the halved value is odd.
Time complexity: O(log a), where a is the first multiplier
Space complexity: O(1)
*/

#include <stdio.h>

/* Multiplies two integers using the Russian peasant method. */
long long russianPeasantMultiply(long long first, long long second) {
    long long result = 0;

    while (first > 0) {
        if (first % 2 == 1) {
            result += second;
        }
        first /= 2;
        second *= 2;
    }

    return result;
}

/* Prints the halving/doubling table for a test case. */
void runTest(long long first, long long second) {
    long long a = first;
    long long b = second;

    printf("Multiplying %lld * %lld\n", first, second);
    printf("a      b      action\n");
    while (a > 0) {
        printf("%-6lld %-6lld %s\n", a, b, (a % 2 == 1) ? "add b" : "skip");
        a /= 2;
        b *= 2;
    }
    printf("Product: %lld\n\n", russianPeasantMultiply(first, second));
}

int main(void) {
    printf("Russian Peasant Multiplication\n\n");
    runTest(18, 25);
    runTest(47, 13);
    runTest(0, 99);
    return 0;
}

/*
High-level idea:
One number is repeatedly halved and the other is repeatedly doubled.
Whenever the halved number is odd, the doubled number contributes to the sum.
This works because multiplication can be decomposed into powers of two.
For 18 * 25, the odd rows occur after halving reaches 9 and 1, so the matching
doubled values are added to produce 450.
*/
