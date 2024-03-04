#include <bits/stdc++.h>

using namespace std;

pair<int, vector<int>> knapsack(vector<int> &weights, vector<int> &values, int V, vector<vector<int>> &dp)
{

    int n = weights.size();
    int max_value = 0;

    // Find the maximum value among all items
    for (int i = 0; i < n; ++i)
        max_value += values[i];

    // Base case: 0 weight needed to achieve value 0
    dp[0][0] = 0;

    // Fill the dp table
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= max_value; ++j)
        {
            if (j < values[i - 1])
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = min(dp[i - 1][j], weights[i - 1] + dp[i - 1][j - values[i - 1]]);
            }
        }
    }

    // Find the minimum weight needed to achieve value V or more
    int min_weight = 100000;
    int selected_value = 0;
    vector<int> selected_items;
    for (int j = V; j <= max_value; ++j)
    {
        if (dp[n][j] < min_weight)
        {
            min_weight = dp[n][j];
            selected_value = j;
        }
    }

    // Backtrack to find the selected items
    for (int i = n; i > 0 && selected_value > 0; --i)
    {
        if (dp[i][selected_value] != dp[i - 1][selected_value])
        {
            selected_items.push_back(i - 1);
            selected_value -= values[i - 1];
        }
    }

    return make_pair(min_weight, selected_items);
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, capacity;
    cin >> n >> capacity;

    vector<int> weights(n);
    vector<int> values(n);

    int max_value = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> values[i] >> weights[i];
        max_value += values[i];
    }
    cout<<"Original instance  : "<<endl;

    int usedweight = 0;
    int answerMain = 0;

    int vmax = *max_element(values.begin(), values.end());

    vector<vector<int>> dp(n + 1, vector<int>(max_value + 1, 100000));
    auto ans = knapsack(weights, values, max_value, dp);

    for (int i = max_value; i >= 0; i--)
    {
        if ((usedweight = dp[n][i]) <= capacity)
        {

            answerMain = i;
            cout<<"Answer : ";
            cout << i << endl;

            cout << "Indices : ";
            vector<int> selected_items = knapsack(weights, values, i, dp).second;
            for (int item : selected_items)
            {
                cout << item + 1 << " ";
            }
            break;
        }
    }
    cout << "\nUsed weight : " << usedweight << endl;





    vector<double> epsilons = {0.5, 0.2, 0.1, 0.05};
    for (auto epsilon : epsilons)
    {

        cout << "Rounded Instance with Eps : " << epsilon << "\n";
        //calculate scalinq factor
        double theta = (epsilon * vmax * 1.0 / (2 * n));
        cout << "theta : " << theta << endl;

        //calculate new values
        vector<int> new_values;
        int new_max_value = 0;
        for (int i = 0; i < n; i++)
        {
            new_max_value += ceil(1.0 * values[i] / theta);
            new_values.push_back(ceil(1.0 * values[i] / theta));
        }

        
        int new_usedweight;
        int answerOriginal = 0;
        vector<vector<int>> dp2(n + 1, vector<int>(new_max_value + 1, 100000));
        auto ans2 = knapsack(weights, new_values, max_value, dp2);

        for (int i = new_max_value; i >= 0; i--)
        {
            if ((new_usedweight = dp2[n][i]) <= capacity)
            {
                cout << "Answer of reduced instance : " << i << endl;
                cout << "Answer of reduced instance multiplied by theta : " << theta * i << endl;
                cout << "Indices : ";
                vector<int> selected_items = knapsack(weights, new_values, i, dp2).second;
                for (int item : selected_items)
                {
                    cout << item + 1 << " ";
                    answerOriginal += values[item];
                }
                break;
            }
        }
        cout << "Answer of original instance (Rounded up): " << answerOriginal << endl;

        cout << "used weight : ";
        cout << new_usedweight << endl;
        cout << "Ratio : ";
        cout<<(1.0*answerMain/answerOriginal)<<endl;
        cout<<"\n\n";
    }
}
