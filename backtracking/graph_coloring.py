"""
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
"""


n = 4
num_colors = 2
colors = [-1 for _ in range(n)]
graph = [
    [0, 1, 1, 1],
    [1, 0, 1, 0],
    [0, 1, 0, 1],
    [1, 0, 1, 0]
]

def isSafe(v, c):
    for n in range(len(graph)):
        if graph[v][n] == 1 and colors[n] == c:
            return False
    return True

def GraphColoring(v):
    if v == len(graph):
        return True
    
    for c in range(1, num_colors + 1):
        if isSafe(v, c):
            colors[v] = c
            if GraphColoring(v + 1):
                return True
            # backtrack
            colors[v] = 0
            
    return False

solved = GraphColoring(0)
if solved:
    print(colors)
else:
    print("Cannot be solved with backtracking")