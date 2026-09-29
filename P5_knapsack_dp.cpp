//  TIME & SPACE COMPLEXITY (0/1 Knapsack - DP)
//  Build DP Table : O(n*W) time | O(n*W) space
//  Backtrack      : O(n) time   | O(n) space
//  n = items, W = capacity

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n = 4;
    int capacity = 8;

    int profit[] = {1, 2, 5, 6};
    int weight[] = {2, 3, 4, 5};

    // DP table: dp[i][w] = max profit using first i items with capacity w
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Build DP table -> O(n * capacity) time, O(n * capacity) space
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weight[i - 1] > w) {
                // Item doesn't fit, carry forward previous best
                dp[i][w] = dp[i - 1][w];
            } else {
                // Max of (skip item) vs (take item)
                dp[i][w] = max(
                    dp[i - 1][w],
                    profit[i - 1] + dp[i - 1][w - weight[i - 1]]
                );
            }
        }
    }

    // Print DP table
    cout << "DP Table:\n\n";
    cout << "Item/Weight\t";
    for (int w = 0; w <= capacity; w++) cout << w << "\t";
    cout << endl;

    for (int i = 0; i <= n; i++) {
        cout << i << "\t\t";
        for (int w = 0; w <= capacity; w++) cout << dp[i][w] << "\t";
        cout << endl;
    }

    cout << "\nMaximum Profit = " << dp[n][capacity] << endl;

    // Backtrack once to find selected items, total weight, and total profit
    // -> O(n) time (single pass instead of two separate traversals)
    vector<int> selectedItems;
    int totalWeight = 0;
    int w = capacity;

    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(i);
            totalWeight += weight[i - 1];
            w -= weight[i - 1];
        }
    }

    cout << "Selected Items: ";
    for (int item : selectedItems) cout << item << " ";
    cout << endl;

    cout << "Total Weight = " << totalWeight << endl;

    return 0;
}
