/* ================================================================ */
/* HORNER'S RULE FOR POLYNOMIAL EVALUATION */
/* ================================================================ */

/*
Algorithm name: Horner's Rule
Problem it solves:
Evaluates a polynomial efficiently using nested multiplication.
Time complexity: O(n), where n is the degree
Space complexity: O(1)
*/

#include <stdio.h>

/* Evaluates coeffs[0]x^degree + ... + coeffs[degree]. */
int hornerEvaluate(const int coeffs[], int degree, int x) {
    int result = coeffs[0];
    for (int i = 1; i <= degree; i++) {
        result = result * x + coeffs[i];
    }
    return result;
}

/* Prints polynomial coefficients and evaluated result. */
void runTest(const int coeffs[], int degree, int x) {
    printf("Polynomial coefficients high-to-low: ");
    for (int i = 0; i <= degree; i++) {
        printf("%d ", coeffs[i]);
    }
    printf("\nx = %d\nValue: %d\n\n", x, hornerEvaluate(coeffs, degree, x));
}

int main(void) {
    int coeffs1[] = {2, -6, 2, -1};
    int coeffs2[] = {1, 0, -4, 4};
    int coeffs3[] = {3, 5, 0, -2, 7};

    printf("Horner's Rule\n\n");
    runTest(coeffs1, 3, 3);
    runTest(coeffs2, 3, 2);
    runTest(coeffs3, 4, -1);
    return 0;
}

/*
High-level idea:
A polynomial is rewritten in nested form.
For example, ax^3 + bx^2 + cx + d becomes ((a*x + b)*x + c)*x + d.
This avoids separately computing powers of x.
For 2x^3 - 6x^2 + 2x - 1 at x = 3, the result starts at 2, then repeatedly
multiplies by 3 and adds the next coefficient.
*/
