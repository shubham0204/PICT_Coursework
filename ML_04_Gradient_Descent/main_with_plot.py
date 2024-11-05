"""
Simple gradient descent implementation in Python
For explanation, refer https://en.wikipedia.org/wiki/Gradient_descent
"""
import matplotlib.pyplot as plt

def f(x: float) -> float:
    return (x + 3) ** 2


def df_dx(x: float) -> float:
    return 2 * (x + 3)

curve = []

x_0 = float(input("Enter initial value for 'x' (x_0): "))
n = int(input("Enter max. number of steps: "))
step_size = float(input("Enter step size: "))
curve.append((x_0, f(x_0)))

x_t = x_0
for i in range(n):
    grad = df_dx(x_t)
    x_t += -step_size * df_dx(x_t)
    print(f"At step {i + 1}, f(x) = {f(x_t)} and df/dx(x) = {grad}")
    curve.append((x_t, f(x_t)))
    
# plot the curve to show the convergence (optional)
x, y = zip(*curve)
plt.scatter(x, y)
plt.show()