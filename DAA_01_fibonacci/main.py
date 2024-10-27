def _fibonacci_recur(i):
    if i <= 1:
        return i
    else:
        return _fibonacci_recur(i - 1) + _fibonacci_recur(i - 2)
    
def fibonacci_recur(n):
    for i in range(n):
        print(_fibonacci_recur(i), end=' ')
    print()
        
def fibonacci_iter(n):
    f_0 = 0
    f_1 = 1
    print(f_0, end=' ')
    print(f_1, end=' ')
    for i in range(n - 2):
        f_2 = f_0 + f_1
        f_0 = f_1
        f_1 = f_2
        print(f_2, end=' ')
    print()

while True:
    print("Enter the value of 'n':")
    n = int(input())
    print("Choose option:")
    print("0: Recursive")
    print("1: Iterative")
    print("2: Close")
    opt = int(input())
    if opt == 0:
        fibonacci_recur(n)
    elif opt == 1:
        fibonacci_iter(n)
    elif opt == 2:
        break