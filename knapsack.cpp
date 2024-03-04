#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int knapsack(vector<int>& weights, vector<int>& values, int V) {
    int n = weights.size();
    int max_value = 0;

    // Find the maximum value among all items
    for (int i = 0; i < n; ++i)
        max_value += values[i];

    // Initialize dp table
    vector<vector<int>> dp(n + 1, vector<int>(max_value + 1, INT_MAX));

    // Base case: 0 weight needed to achieve value 0
    dp[0][0] = 0;

    // Fill the dp table
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= max_value; ++j) {
            if (j < values[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = min(dp[i - 1][j], weights[i - 1] + dp[i - 1][j - values[i - 1]]);
            }
        }
    }

    // Find the minimum weight needed to achieve value V
    int min_weight = INT_MAX;
    for (int j = V; j <= max_value; ++j) {
        min_weight = min(min_weight, dp[n][j]);
    }

    return min_weight;
}

int main() {
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    int V = 8;
    cout << "Minimum weight needed to achieve value " << V << ": " << knapsack(weights, values, V) << endl;
    return 0;
}
