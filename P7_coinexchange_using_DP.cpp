#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ================== GREEDY APPROACH ==================
// Picks the largest coin <= remaining amount, repeatedly.
// NOTE: Greedy does NOT guarantee the optimal (minimum coin) answer
// for arbitrary coin systems - only for "canonical" coin systems
// (like standard currency 1,2,5,10...). {1,5,6,9} is NOT canonical.
vector<int> coinExchangeGreedy(vector<int> coins, int amount)
{
    // Sort descending so we always try the biggest coin first
    sort(coins.rbegin(), coins.rend());

    vector<int> usedCoins;
    int remaining = amount;

    for (int c : coins)
    {
        while (remaining >= c)
        {
            usedCoins.push_back(c);
            remaining -= c;
        }
    }
    return usedCoins; // if remaining != 0 at the end, amount was not fully achievable
}

// ================== DYNAMIC PROGRAMMING APPROACH ==================
// dp[i] = minimum number of coins needed to make amount i
// Recurrence (matches your board):
//      dp[i] = min( dp[i], dp[i - coin] + 1 )   for every coin <= i
// Base case: dp[0] = 0 (zero coins needed to make amount 0)
void coinExchangeDP(vector<int> &coins, int amount)
{
    // dp[i] holds min coins to make amount i. Init to "infinity" (unreachable).
    vector<int> dp(amount + 1, INT_MAX);
    vector<int> lastCoinUsed(amount + 1, -1); // to reconstruct which coins were used
    dp[0] = 0;

    // ---------- Table exactly like your whiteboard ----------
    // rows = coins (processed one at a time, cumulative),
    // cols = amounts 0..amount
    vector<vector<int>> table(coins.size(), vector<int>(amount + 1, -1));

    for (size_t row = 0; row < coins.size(); row++)
    {
        int coin = coins[row];

        for (int i = 0; i <= amount; i++)
        {
            if (i == 0)
            {
                dp[i] = 0;
            }
            else if (coin <= i && dp[i - coin] != INT_MAX)
            {
                // Try using this coin: dp[i - coin] + 1
                if (dp[i - coin] + 1 < dp[i])
                {
                    dp[i] = dp[i - coin] + 1;
                    lastCoinUsed[i] = coin;
                }
            }
            table[row][i] = (dp[i] == INT_MAX ? -1 : dp[i]);
        }
    }

    // ---------- Print the DP table (same shape as your board) ----------
    cout << "\nDP Table (rows = coins used so far, cols = amount):\n\n";
    cout << "Coin\\Amt";
    for (int i = 0; i <= amount; i++)
        cout << "\t" << i;
    cout << "\n";

    for (size_t row = 0; row < coins.size(); row++)
    {
        cout << coins[row];
        for (int i = 0; i <= amount; i++)
        {
            if (table[row][i] == -1)
                cout << "\t-";
            else
                cout << "\t" << table[row][i];
        }
        cout << "\n";
    }

    // ---------- Print result ----------
    cout << "\nMinimum coins needed for amount " << amount << ": ";
    if (dp[amount] == INT_MAX)
    {
        cout << "Not possible with given coins\n";
        return;
    }
    cout << dp[amount] << "\n";

    // ---------- Reconstruct which coins were actually used ----------
    vector<int> usedCoins;
    int remaining = amount;
    while (remaining > 0)
    {
        int c = lastCoinUsed[remaining];
        usedCoins.push_back(c);
        remaining -= c;
    }

    cout << "Coins used: { ";
    for (int c : usedCoins)
        cout << c << " ";
    cout << "}\n";
}

int main()
{
    vector<int> coins = {1, 5, 6, 9};
    int amount = 11;

    cout << "Coins available : { ";
    for (int c : coins) cout << c << " ";
    cout << "} (unlimited supply)\n";
    cout << "Amount to make   : " << amount << "\n";

    // ---------------- GREEDY ----------------
    auto greedyStart = high_resolution_clock::now();
    vector<int> greedyResult = coinExchangeGreedy(coins, amount);
    auto greedyEnd = high_resolution_clock::now();
    auto greedyTime = duration_cast<nanoseconds>(greedyEnd - greedyStart);

    cout << "\n========== GREEDY APPROACH ==========\n";
    cout << "Coins used ("<< greedyResult.size() <<"): { ";
    for (int c : greedyResult) cout << c << " ";
    cout << "}\n";
    cout << "Time Taken: " << greedyTime.count() << " ns\n";

    // ---------------- DYNAMIC PROGRAMMING ----------------
    cout << "\n========== DYNAMIC PROGRAMMING APPROACH ==========\n";
    auto dpStart = high_resolution_clock::now();
    coinExchangeDP(coins, amount);
    auto dpEnd = high_resolution_clock::now();
    auto dpTime = duration_cast<nanoseconds>(dpEnd - dpStart);

    cout << "Time Taken: " << dpTime.count() << " ns\n";

    return 0;
}
