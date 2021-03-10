#include <bits/stdc++.h>

using namespace std;

using b64 = bitset<64>;
using b32 = bitset<32>;
using b48 = bitset<48>;
using b56 = bitset<56>;
using b28 = bitset<28>;

int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

int Inv_IP[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

b64 apply_ip(b64 in, bool inv = false)
{
    b64 out;
    for (int i = 63; i >= 0; i--)
    {
        int j = (inv ? Inv_IP[63 - i] : IP[63 - i]) - 1;
        out[i] = in[63 - j];
    }
    return out;
}

int main()
{

    ifstream fin("outputs.txt");
    ofstream fout("outbits.txt");

    string s;
    while (fin >> s)
    {
        assert((int)s.length() == 16);
        b64 bits = 0;
        for (int i = 0; i < 16; i++)
        {
            char c = s[i];
            int num = c - 'f';
            assert(num < 16 and num >= 0);
            bits = (bits << 4) | b64(num);
        }
        b64 actual = apply_ip(bits);

        fout << bitset<64>(actual) << endl;
    }

    return 0;
}