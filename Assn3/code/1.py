def extended_gcd(a, b):
    """returns gcd(a, b), s, r s.t. a * s + b * r == gcd(a, b)"""
    s, old_s = 0, 1
    r, old_r = b, a
    while r:
        q = old_r // r
        old_r, r = r, old_r - q * r
        old_s, s = s, old_s - q * s
    return old_r, old_s, (old_r - old_s * a) // b if b else 0


def modinv(a, m):
    """returns the modular inverse of a w.r.t. to m, works when a and m are coprime"""
    g, x, _ = extended_gcd(a % m, m)
    return x % m if g == 1 else None


def binpow(a, n, m):
    res = 1
    while n > 0:
        if n % 2 != 0:
            res = res*a % m
        a = a*a % m
        n = n//2
    return res


p = 19807040628566084398385987581

a1 = 324
a2 = 2345
a3 = 9513

b1 = 11226815350263531814963336315
b2 = 9190548667900274300830391220
b3 = 4138652629655613570819000497


g, p1, p2 = extended_gcd(a2-a1, a3-a2)

print(p1,p2)

g = binpow(b2*modinv(b1, p) % p, p1, p) * \
    binpow(b3*modinv(b2, p) % p, p-1+p2, p) % p
passwd = b1*binpow(g, p-1-324, p) % p

print(g)
print(passwd)
assert (passwd * binpow(g, a1, p) % p == b1)
assert (passwd * binpow(g, a2, p) % p == b2)
assert (passwd * binpow(g, a3, p) % p == b3)
