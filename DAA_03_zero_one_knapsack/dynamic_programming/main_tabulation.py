"""
Solving the 0/1 knapsack problem using dynamic programming (tabulation method)
Reference:
https://youtu.be/nLmhmB6NzcM?feature=shared
"""

from dataclasses import dataclass


@dataclass
class KnapSack:
    weight: int
    profit: int


def solve(items: list[KnapSack], target_weight: int) -> tuple[int, list[KnapSack]]:
    # dp[i][w] = maximum profit that can be obtained with weight <= w using items[0:i]
    N = len(items)
    dp = [[0 for _ in range(target_weight + 1)] for _ in range(N + 1)]
    for i in range(1, N + 1):
        for w in range(1, target_weight + 1):
            if items[i - 1].weight <= w:
                dp[i][w] = max(
                    dp[i - 1][w],  # not selecting the item
                    dp[i - 1][w - items[i - 1].weight]
                    + items[i - 1].profit,  # selecting the item
                )
            else:
                dp[i][w] = dp[i - 1][w]
    net_profit = dp[N][target_weight]

    # backtracking to find selected items
    selected_items = []
    i, w = N, target_weight
    while i > 0 and w > 0:
        if dp[i][w] != dp[i - 1][w]:
            selected_items.append(items[i - 1])
            w -= items[i - 1].weight
        i -= 1

    return net_profit, selected_items


items = [
    KnapSack(weight=10, profit=60),
    KnapSack(weight=20, profit=100),
    KnapSack(weight=30, profit=120),
]
target_weight = 50

net_profit, selected_items = solve(items, target_weight)
print(f"Totat profit: {net_profit}")
print("Selected items were: ")
for item in selected_items:
    print(item)
