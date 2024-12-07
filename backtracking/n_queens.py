"""
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
"""



n = 4
X = [-1 for _ in range(n)]

def isSafe(i, k):
    for j in range(i):
        if X[j] == k or (abs(X[j] - k) == abs(j - i)):
            return False
    return True

def NQueens(i):
    if i == n:
        print(X)
        return
    
    for k in range(n):
        if isSafe(i, k):
            X[i] = k
            NQueens(i + 1)
            
NQueens(0)