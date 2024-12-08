"""
function BinomialCoefficient(n, k) {
    if k > n {
        return 0
    }
    if k == 0 || k == n {
        return 1
    }
    return BinomialCoefficient(n - 1, k - 1) + BinomialCoefficient(n - 1, k)
}
"""


def BinomialCoefficient(n, k):
    if k > n:
        return 0
    if k == 0 or k == n:
        return 1
    return BinomialCoefficient(n - 1, k - 1) + BinomialCoefficient(n - 1, k)
    
print(BinomialCoefficient(4, 2))
print(BinomialCoefficient(5, 3))