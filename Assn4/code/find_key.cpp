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

pair<b32, b32> get_LR(b64 in)
{
    b32 L, R;
    for (int i = 63, j = 31; i >= 32; i--, j--)
    {
        L[j] = in[i];
        R[j] = in[i - 32];
    }
    return make_pair(L, R);
}

int E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

b48 apply_E(b32 in)
{
    b48 out;
    for (int i = 47; i >= 0; i--)
    {
        int j = E[47 - i] - 1;
        out[i] = in[31 - j];
    }
    return out;
}

int S1[4][16] = {
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};

int S2[4][16] = {
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};

int S3[4][16] = {
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};

int S4[4][16] = {
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};

int S5[4][16] = {
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};

int S6[4][16] = {
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};

int S7[4][16] = {
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};

int S8[4][16] = {
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

b32 apply_S(b48 in)
{
    b32 out;
    int i = 47, j = 31;
    for (auto S : {S1, S2, S3, S4, S5, S6, S7, S8})
    {
        int row = 0, col = 0;
        for (int k = i - 1; k > i - 5; k--)
        {
            col = col * 2 + in[k];
        }
        row = in[i] * 2 + in[i - 5];

        bitset<4> num = S[row][col];
        for (int k = j; k >= j - 3; k--)
        {
            out[k] = num[3 - (j - k)];
        }
        i -= 6;
        j -= 4;
    }
    return out;
}

int P[] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25};

int Inv_P[32];

void calc_Inv_P()
{
    for (int i = 0; i < 32; i++)
    {
        int to = P[i] - 1;
        Inv_P[to] = i + 1;
    }
}

b32 apply_P(b32 in, bool inv = false)
{
    b32 out;
    for (int i = 31; i >= 0; i--)
    {
        int j = (inv ? Inv_P[31 - i] : P[31 - i]) - 1;
        out[i] = in[31 - j];
    }
    return out;
}

using v64 = array<int, 64>;
using v32 = array<int, 32>;
using v48 = array<int, 48>;
using v56 = array<int, 56>;
using v28 = array<int, 28>;

int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

unsigned short shifts[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int PC2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};

vector<v48> keys(16);

void get_keys()
{
    v56 key;
    for (int i = 55; i >= 0; i--)
    {
        key[i] = 56 - i;
    }

    v28 C, D;
    for (int i = 55, j = 27; i >= 28; i--, j--)
    {
        C[j] = key[i];
        D[j] = key[i - 28];
    }

    for (int r = 0; r < 16; r++)
    {
        v28 rC, rD;
        int s = shifts[r];
        for (int i = 27; i >= 0; i--)
        {
            int to = (i + s) % 28;
            rC[to] = C[i];
            rD[to] = D[i];
        }
        C = rC, D = rD;

        for (int i = 47; i >= 0; i--)
        {
            int j = PC2[47 - i] - 1;
            j = 55 - j;
            if (j > 27)
            {
                keys[r][i] = C[j - 28];
            }
            else
            {
                keys[r][i] = D[j];
            }
        }
    }
}

void print(v48 key)
{
    for (int i = 47; i >= 0; i -= 6)
    {
        int num = 0;
        for (int j = i; j >= i - 5; j--)
        {
            num = num * 2 + key[j];
        }
        cout << setw(2) << setfill('0') << hex << num;
    }
    cout << " ";
}

b64 join(b32 L, b32 R)
{
    b64 out;
    for (int i = 31; i >= 0; i--)
    {
        out[i + 32] = L[i];
        out[i] = R[i];
    }
    return out;
}

b64 get(string s)
{
    assert(s.length() == 16);
    b64 ans = 0;
    for (int i = 0; i < 16; i++)
    {
        int foo = s[i] - 'f';
        ans = (ans << 4) | b64(foo);
    }
    return ans;
}

vector<b48> rkeys(16);
void get_keys2(vector<int> key)
{
    for (int r = 0; r < 16; r++)
    {
        for (int i = 47; i >= 0; i--)
        {
            int j = keys[r][i] - 1;
            rkeys[r][i] = key[55 - j];
        }
    }
}

int main()
{
    get_keys();
    b48 key_r6 = b48("101101110011100101001011110111000011010010100011");

    vector<int> key(56, -1);
    for (int i = 47, cur = 0; i >= 0; i -= 6, cur++)
    {
        if (cur == 2 or cur == 3)
            continue;
        for (int j = i; j >= i - 5; j--)
        {
            int k = keys[5][j] - 1;
            key[55 - k] = key_r6[j];
        }
    }

    auto doDES = [&](b64 in, bool inv = false) {
        b64 LR = apply_ip(in);
        auto [L, R] = get_LR(LR);
        for (int r = 0; r < 6; r++)
        {
            auto ER = apply_E(R);
            ER ^= (inv ? rkeys[5 - r] : rkeys[r]);
            auto SR = apply_S(ER);
            auto PR = apply_P(SR);
            auto nL = R, nR = L ^ PR;
            L = nL, R = nR;
        }
        auto O = join(R, L);
        auto out = apply_ip(O, true);
        return out;
    };

    vector<int> pos;
    int cnt = 0;
    for (int i = 55; i >= 0; i--)
    {
        if (key[i] == -1)
            pos.push_back(i);
        cnt += (key[i] == -1);
    }

    calc_Inv_P();

    b64 in = get("pjjjstpmigntlltf");
    b64 out = get("snmfqkhtsjoinofl");

    for (int i = 0; i < (1 << cnt); i++)
    {
        for (int j = 0; j < cnt; j++)
        {
            if ((i & (1 << j)) != 0)
            {
                key[pos[j]] = 1;
            }
            else
                key[pos[j]] = 0;
        }
        get_keys2(key);
        if (doDES(in) == out)
        {
            cout << "Found the key !!" << endl;
            for (int k = 55; k >= 0; k--)
            {
                cout << key[k];
            }
            cout << endl;
            break;
        }
    }

    b64 in21 = get("ountnlqktqortppn");
    b64 in22 = get("kkqqnrhipifmiigt");

    for (auto in2 : {in21, in22})
    {
        auto out2 = doDES(in2, true);
        for (int i = 63; i >= 0; i -= 8)
        {
            int num = 0;
            for (int j = i; j >= i - 7; j--)
            {
                num = num * 2 + out2[j];
            }
            cout << char(num);
        }
    }
    cout << endl;

    return 0;
}