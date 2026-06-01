/* ================================================================ */
/* COIN PROBLEM - MINIMUM COINS USING DYNAMIC PROGRAMMING */
/* ================================================================ */

/*
Algorithm name: Coin Change using Dynamic Programming
Problem it solves:
Finds the minimum number of coins needed to make a target amount when coins
may be used repeatedly.
Time complexity: O(numCoins * amount)
Space complexity: O(amount)
*/

#include <stdio.h>
#include <limits.h>

#define MAX_AMOUNT 100
#define MAX_COINS 10

/* Computes minimum coins and remembers the last coin used for reconstruction. */
int minCoinsDP(const int coins[], int numCoins, int amount, int chosenCoin[]) {
    int dp[MAX_AMOUNT + 1];

    for (int value = 0; value <= amount; value++) {
        dp[value] = INT_MAX / 2;
        chosenCoin[value] = -1;
    }
    dp[0] = 0;

    for (int value = 1; value <= amount; value++) {
        for (int coin = 0; coin < numCoins; coin++) {
            if (coins[coin] <= value && dp[value - coins[coin]] + 1 < dp[value]) {
                dp[value] = dp[value - coins[coin]] + 1;
                chosenCoin[value] = coins[coin];
            }
        }
    }

    return dp[amount] >= INT_MAX / 2 ? -1 : dp[amount];
}

/* Prints one coin change instance and chosen coins. */
void runTest(const int coins[], int numCoins, int amount) {
    int chosenCoin[MAX_AMOUNT + 1];
    int result = minCoinsDP(coins, numCoins, amount, chosenCoin);

    printf("Coins: ");
    for (int i = 0; i < numCoins; i++) {
        printf("%d ", coins[i]);
    }
    printf("\nAmount: %d\n", amount);

    if (result == -1) {
        printf("No solution\n\n");
        return;
    }

    printf("Minimum coins: %d\nChosen coins: ", result);
    while (amount > 0) {
        printf("%d ", chosenCoin[amount]);
        amount -= chosenCoin[amount];
    }
    printf("\n\n");
}

int main(void) {
    int coins1[] = {1, 3, 4};
    int coins2[] = {2, 5, 10};
    int coins3[] = {1, 7, 10};

    printf("Coin Change using Dynamic Programming\n\n");
    runTest(coins1, 3, 6);
    runTest(coins2, 3, 17);
    runTest(coins3, 3, 14);
    return 0;
}

/*
High-level idea:
The table dp[value] stores the fewest coins needed for that value.
For every value, each coin is tried as the final coin.
The best previous solution plus one coin becomes the new best answer.
For amount 6 with coins 1, 3, and 4, dp[3] becomes 1, so dp[6] becomes 2 by
using two 3-value coins.
*/
