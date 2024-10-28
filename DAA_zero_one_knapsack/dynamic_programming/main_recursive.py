from dataclasses import dataclass


@dataclass
class KnapSack:
    weight: int
    profit: int


max_profit = 0
max_profit_items = []


def compute(
    items: list[KnapSack],
    target_weight: int,
    curr_items: list[KnapSack],
    curr_index: int,
    curr_weight: int,
):
    if curr_index == len(items) or curr_weight == target_weight:
        global max_profit
        global max_profit_items
        profit = sum(item.profit for item in curr_items)
        if profit > max_profit:
            max_profit = profit
            max_profit_items = curr_items.copy()
        return
    for i in range(curr_index, len(items)):
        if curr_weight + items[i].weight <= target_weight:
            curr_items.append(items[i])
            compute(
                items, target_weight, curr_items, i + 1, curr_weight + items[i].weight
            )
            curr_items.pop()


items = [
    KnapSack(weight=10, profit=60),
    KnapSack(weight=20, profit=100),
    KnapSack(weight=30, profit=120),
]
target_weight = 50

compute(items, target_weight, [], 0, 0)
print(f"Totat profit: {max_profit}")
print("Selected items were: ")
for item in max_profit_items:
    print(item)
