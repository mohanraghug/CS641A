#!/usr/bin/python3
from fpylll import *

N = 84364443735725034864402554533826279174703893439763343343863260342756678609216895093779263028809246505955647572176682669445270008816481771701417554768871285020442403001649254405058303439906229201909599348669565697534331652019516409514800265887388539283381053937433496994442146419682027649079704982600857517093
C = 23701787746829110396789094907319830305538180376427283226295906585301889543996533410539381779684366880970896279018807100530176651625086988655210858554133345906272561027798171440923147960165094891980452757852685707020289384698322665347609905744582248157246932007978339129630067022987966706955482598869800151693
e = 5
padding = 0x596f7520736565206120476f6c642d42756720696e206f6e6520636f726e65722e20497420697320746865206b657920746f206120747265617375726520666f756e64206279


def value(p, x):
    return sum([x**i*p[i] for i in range(len(p))])


def add(poly1, poly2):
    length = max(len(poly1), len(poly2))
    res = [0] * length
    for i in range(length):
        if i < len(poly1):
            res[i] += poly1[i]
        if i < len(poly2):
            res[i] += poly2[i]
    return res


def mult(poly1, poly2):
    length = len(poly1) + len(poly2) - 1
    res = [0] * length
    for i in range(len(poly1)):
        for j in range(len(poly2)):
            res[i + j] += poly1[i] * poly2[j]
    return res


def power(poly, k):
    res = [1]
    while k > 0:
        if k % 2 == 1:
            res = mult(res, poly)
        poly = mult(poly, poly)
        k >>= 1
    return res


L = 72
K = (1 << L)
padding <<= L

f = add(power([padding, 1], e), [N - C])
f = [x % N for x in f]
for i in range(len(f)):
    f[i] = K**i * f[i]

d = 5
m = 3

Basis = []
for u in range(d):
    for v in range(m + 1):
        g = mult([N ** (m - v)], power(f, v))
        foo = [0] * (u + 1)
        foo[-1] = K ** u
        g = mult(g, foo)
        while len(g) < d * (m + 1):
            g.append(0)
        Basis.append(g)

A = IntegerMatrix(d*(m+1), d*(m+1))
for i in range(d * (m + 1)):
    for j in range(d * (m + 1)):
        A[i, j] = Basis[i][j]

LLL.reduction(A)

v = [0]*len(A[0])
for i in range(len(v)):
    v[i] = A[0][i] // (K**i)


lo = -K
hi = K

assert(value(v, lo) < 0 and value(v, hi) > 0)

ITERS = 100

for _ in range(ITERS):
    mid = (lo + hi) // 2
    mid_val = value(v, mid)
    if mid_val == 0:
        break
    if mid_val > 0:
        hi = mid
    else:
        lo = mid

root = (lo + hi)//2
padding += root
password = ""

while root > 0:
    password += chr(root % 256)
    root >>= 8

password = password[::-1]

print('Password is', password)


fulltext = ""
while padding > 0:
    fulltext += chr(padding % 256)
    padding >>= 8

print(fulltext[::-1])
