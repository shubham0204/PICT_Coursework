"""
function ZeroOneKnapsack(P, W, n, m, dp) {
    for i := 1 to n {
        for j := 1 to m {
            if W[i - 1] <= j {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - W[i - 1]] + P[i - 1])
            }
            else {
                dp[i][j] = dp[i - 1][j]
            }
        }
    }
    return dp[n][m]
}

W = [2, 3, 4, 5]
P = [1, 2, 5, 6]
m = 8
n = 4
dp := zero-matrix with size n * m

max_profit = ZeroOneKnapsack(P, W, n, m, dp)
print max_profit
"""

W = [2, 3, 4, 5]
P = [1, 2, 5, 6]
m = 8
n = len(P)

dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]

def ZeroOneKnapsack(P, W, n, m):
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if W[i - 1] <= j:
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i - 1][j - W[i - 1]] + P[i - 1]
                )
            else:
                dp[i][j] = dp[i - 1][j]
    return dp[n][m]

print(ZeroOneKnapsack(P, W, n, m))