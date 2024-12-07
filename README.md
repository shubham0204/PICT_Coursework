# (Pseudo)code for algorithms/problems in DAA

## Greedy strategy


## Dynamic Programming


## Backtracking

### [N-Queens](backtracking/n_queens.py)

```
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

```
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

```
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