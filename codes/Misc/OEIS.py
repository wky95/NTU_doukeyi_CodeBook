from fractions import Fraction

def BerlekampMassey(a: list[Fraction]) -> list[Fraction]:
    def scale(v: list[Fraction], c: Fraction) -> list[Fraction]:
        return [x * c for x in v]

    s: list[Fraction] = []
    best: list[Fraction] = []
    bestPos = 0

    for i in range(len(a)):
        error: Fraction = a[i]
        for j in range(len(s)):
            error -= s[j] * a[i - 1 - j]
        if error == 0:
            continue

        if not s:
            s = [Fraction(0)] * (i + 1)
            bestPos = i
            best = [Fraction(1, error)]
            continue

        fix = scale(best, error)
        fix = [Fraction(0)] * (i - bestPos - 1) + fix

        if len(fix) >= len(s):
            best = scale(s, Fraction(-1, error))
            best.insert(0, Fraction(1, error))
            bestPos = i
            if len(s) < len(fix):
                s += [Fraction(0)] * (len(fix) - len(s))

        for j in range(len(fix)):
            s[j] += fix[j]

    return list(reversed(s))

n = int(input())
l = list(map(Fraction, input().split()))
for i in range(len(l)):
    coeffs = BerlekampMassey(l[:i+1])
    for x in coeffs:
        print(x, end=" ")
    print()