# (Pseudo)code for algorithms/problems in DAA

## Greedy strategy

### [Zero-One Knapsack](greedy/zero_one_knapsack.py)

```c
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
```

### [Job Scheduling](greedy/job_scheduling.py)

```c
function JobScheduling(J, n) {
    sort jobs 'J' in decreasing order of their profits
    
    slots := [false] * n
    schedule := [null] * n
    profit := 0
    
    for i := 0 to (n - 1) {
        for k := 0 to (J[i].deadline - 1) {
            if not slots[k] {
                schedule[k] = J[i]
                profit += J[i].profit
                slots[k] = true
            }
        }
    }
    
    return schedule, profit
}
```

### [Activity Selection Problem](greedy/activity_selection.py)

```c
function ActivitySelection(A, n) {
    sort activities 'A' in increasing order of their finish times
    S := { A[0] }
    f := A[0].finish_time
    for i := 0 to (n - 1) {
        if A[i].start_time >= f {
            S += { A[i] }
            f = A[i].finish_time
        }
    }
    print S
}
```

## Dynamic Programming

### [Binomial Coefficients](dynamic_programming/binomial_coefficient.py)

```c
function BinomialCoefficient(n, k) {
    if k > n {
        return 0
    }
    if k == 0 || k == n {
        return 1
    }
    return BinomialCoefficient(n - 1, k - 1) + BinomialCoefficient(n - 1, k)
}
```

### [Zero-One Knapsack](dynamic_programming/zero_one_knapsack.py)

```c
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
```

## Backtracking

### [N-Queens](backtracking/n_queens.py)

```c
function isSafe(i, k) {
    for j := 0 to i - 1 {
        if X[j] == k || (abs(X[j] - k)) == abs(j - i)) {
            return false
        }
    }
    return true
}

function NQueens(i, n, X) {
    if i == n {
        print X
        return
    }
    
    for k := 0 to n - 1 {
        if isSafe(i, k) {
            X[i] = k
            NQueens(i + 1, n, X)
        }
    }
}

n = 4
X := [-1 -1 -1 -1]
NQueens(0, n , X)
```

### [Graph Coloring](backtracking/graph_coloring.py)

```c
function isSafe(v, c) {
    for each neighbor 'n' of 'v' in graph {
        if colors[n] == c {
            return false
        }
    }
    return true
}

function GraphColoring(v, num_colors, num_nodes) {
    if v == num_nodes {
        return true
    }
    
    for c := 1 to num_colors {
        if isSafe(v, c) {
            colors[v] = c   // assign color 'c' to vertex 'v'
            if GraphColoring(v + 1, num_colors, num_nodes) {
                return true
            }
            colors[v] = 0   // remove color from vertex 'v'
        }
    }
    
    return false
}

GraphColoring(0, 2, 4)
```

### [Subset Sum](backtracking/subset_sum.py)

```c
function SubSetSum(i, C, CS, n, m) {
    if CS == m {
        print C             // solution
        return
    }
    
    if CS >= m or i >= n {
        return              // backtrack
    }
    
    C += { S[i] }
    SubSetSum(i + 1, C, CS + S[i], n, m)
    C \= { S[i] }
    SubSetSum(i + 1, C, CS, n, m)
}

SubSetSum(0, {}, 0, n, m)
```

## Branch and Bound