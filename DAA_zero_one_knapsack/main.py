class KnapSack:
    def __init__(
        self,
        weight: int,
        profit: int,
    ):
        self.weight = weight
        self.profit = profit

    def __repr__(self) -> str:
        return f"KnapSack[ W = {self.weight} , P = {self.profit} ]"


max_profit = 0
max_profit_items = []


def solve(
    items: list[KnapSack],
    target_weight: int,
    curr_items: list[KnapSack],
    curr_index: int,
    curr_items_weight: int,
    max_profit: int,
    max_profit_items: list[KnapSack],
):
    if curr_items_weight > target_weight or curr_index >= len(items):
        return
    profit = sum([item.profit for item in curr_items])
    if profit > max_profit:
        max_profit = profit
        max_profit_items = curr_items
        print(max_profit)
    curr_items.append(items[curr_index])
    solve(
        items,
        target_weight,
        curr_items,
        curr_index,
        curr_items_weight + items[curr_index].weight,
        max_profit,
        max_profit_items,
    )
    curr_items.pop()
    solve(
        items,
        target_weight,
        curr_items,
        curr_index + 1,
        curr_items_weight,
        max_profit,
        max_profit_items,
    )


def select_greedy(
    items: list[KnapSack], target_weight: int
) -> tuple[int, list[KnapSack]]:
    max_profit = 0
    max_profit_items = []
    solve(items, target_weight, [], 0, 0, max_profit, max_profit_items)

    return max_profit, max_profit_items


items = [
    KnapSack(weight=10, profit=60),
    KnapSack(weight=20, profit=100),
    KnapSack(weight=30, profit=120),
]
print(select_greedy(items, 50))

# N = int(input( "Enter number of knapsacks: " ))
# items = []
# for i in range(N):
#     items.append(
#         KnapSack(
#             int(input(f"Enter weight of {i+1}th knapsack: ")) ,
#             int(input(f"Enter profit of {i+1}th knapsack: ")) ,
#         )
#     )
# target_weight = int(input("Enter target weight: "))
# net_profit , selected_items = select_greedy(items, target_weight )
# print( f"Totat profit: {net_profit}")
# print( "Selected items were: " )
# for item in selected_items:
#     print( item )
