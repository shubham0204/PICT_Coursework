"""
function ZeroOneKnapSack(O, n, m) {
    sort objects O in decreasing order of profit-to-weight ratio
    W := 0
    P := 0
    knapsack := {}
    for i := 0 to n - 1 {
        if W + O[i].weight > m {
            break
        }
        knapsack += { O[i] }
        W += O[i].weight
        P += O[i].profit
    }
    
    print knapsack
    print P
}
"""

from dataclasses import dataclass

P = [10, 5, 15, 7, 6, 18, 3]
W = [2, 3, 5, 7, 1, 4, 1]
n = len(P)
m = 15

@dataclass
class Object:
    profit: int = 0
    weight: int = 0
    
O = [Object(pi, wi) for pi, wi in zip(P, W)]

def ZeroOneKnapSack(O, n, m):
    # sort objects in decreasing order of profit-to-weight ratio
    O = list(sorted(O, key=lambda obj: obj.profit / obj.weight, reverse=True))
    
    knapsack_weight = 0
    profit = 0
    knapsack = []
    for i in range(n):
        if knapsack_weight + O[i].weight > m:
            break
        knapsack.append(O[i])
        profit += O[i].profit
        knapsack_weight += O[i].weight
        
    return knapsack, profit

items, profit = ZeroOneKnapSack(O, n, m)
print(items)
print(profit)
    
        
    