"""
Simple gradient descent implementation in Python
For explanation, refer https://en.wikipedia.org/wiki/Gradient_descent
"""

def f(x: float) -> float:
    return (x + 3) ** 2


def df_dx(x: float) -> float:
    return 2 * (x + 3)


x_0 = float(input("Enter initial value for 'x' (x_0): "))
n = int(input("Enter max. number of steps: "))
step_size = float(input("Enter step size: "))

x_t = x_0
for i in range(n):
    grad = df_dx(x_t)
    x_t += -step_size / df_dx(x_t)
    print(f"At step {i + 1}, f(x) = {f(x_t)} and df/dx(x) = {grad}")
