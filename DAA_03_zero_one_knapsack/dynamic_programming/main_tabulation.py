"""
Solving the 0/1 knapsack problem using dynamic programming (tabulation method)
Reference:
https://youtu.be/nLmhmB6NzcM?feature=shared
"""
# zero-one knap-sack problem
weights = [2, 3, 4, 5]
profits = [1, 2, 5, 6]
M = 8
N = len(weights)

# maintain a table `dp` with dims N * M
# dp[i][j] = profit by selecting 'i' weighing 'j'
# j is the weight of the knapsack containing items 0..i
dp = [[0 for _ in range(M + 1)] for _ in range(N + 1)]

def solve():
    for i in range(1, N + 1):
        for j in range(1, M + 1):
            curr_item_weight = weights[i - 1]
            curr_item_profit = profits[i - 1]
            if curr_item_weight <= j:
                dp[i][j] = max(
                    dp[i - 1][j],                                  # current item not selected
                    dp[i - 1][j - curr_item_weight] + curr_item_profit # current item selected
                )
            else:
                dp[i][j] = dp[i - 1][j]
    
    total_max_profit = dp[N][M]
    selected_items = []
    i, j = N, M
    while i > 0 and j > 0:
        if dp[i][j] != dp[i - 1][j]:
            selected_items.append((weights[i - 1], profits[i - 1]))
            j -= weights[i - 1]
        i -= 1

    return selected_items, total_max_profit

selected_items, total_max_profit = solve()
print(selected_items)
print(total_max_profit)
