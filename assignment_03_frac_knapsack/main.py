
class KnapSack:

    def __init__(
        self , 
        weight: int , 
        profit: int , 
        frac: float = 1.0
    ):
        self.weight = weight
        self.profit = profit
        self.frac = frac

    def __repr__( self ) -> str:
        return f"KnapSack[ W = {self.weight} , P = {self.profit} , f = {self.frac} ]"

    
def select_greedy(
    items: list[KnapSack] , 
    target_weight: int
) -> tuple[int,list[KnapSack]]:
    # maximize profit, minimize weight to accomodate more items
    # hence, maximize profit/weight ratio
    profit_to_weight = [ item.profit / item.weight for item in items ]
    # associate ratios with respective items
    items_with_ratio = list(zip(profit_to_weight,items))
    items_with_ratio = list(sorted( items_with_ratio , key=lambda i: i[0] , reverse=True ))
    result = []
    total_weight = 0
    total_profit = 0
    for item in items_with_ratio:
        if total_weight + item[1].weight <= target_weight:
            # pick the whole item
            result.append( item[1] )
            total_weight += item[1].weight
            total_profit += item[1].profit
        else:
            remaining_weight_ratio = (target_weight - total_weight) / item[1].weight
            item[1].frac = round(remaining_weight_ratio , 2)
            result.append( item[1] )
            total_profit += (item[1].profit * remaining_weight_ratio)
    return total_profit , result


N = int(input( "Enter number of knapsacks: " ))
items = []
for i in range(N):
    items.append(
        KnapSack(
            int(input(f"Enter weight of {i+1}th knapsack: ")) ,
            int(input(f"Enter profit of {i+1}th knapsack: ")) ,
        )
    )
target_weight = int(input("Enter target weight: "))
net_profit , selected_items = select_greedy(items, target_weight )
print( f"Totat profit: {net_profit}")
print( "Selected items were: " )
for item in selected_items:
    print( item )
