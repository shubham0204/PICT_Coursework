"""
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
"""


S = [5, 10, 12, 13, 15, 18]
n = len(S)
m = 30

def compute(i, curr_elements, curr_sum):
    if curr_sum == m:
        # check for success state
        print(curr_elements)
        return True
    
    if curr_sum > m or i >= n:
        # check for invalid state
        return False
    
    curr_elements += [S[i]]
    res_taken = compute(i + 1, curr_elements, curr_sum + S[i])
    curr_elements.pop()
    res_not_taken = compute(i + 1, curr_elements, curr_sum)
    
    return res_taken or res_not_taken
    
solutions = []
solved = compute(0, [], 0)
if not solved:
    print("Not solvable by backtracking")