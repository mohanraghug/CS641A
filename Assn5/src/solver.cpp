#include <bits/stdc++.h>
using namespace std;

// breaks the cipher assuming A is lower triangular

using b7 = bitset<7>;
using b13 = bitset<13>;

#define endl '\n'

b13 mod = b13("10000011");

b7 add(b7 x, b7 y)
{
    x ^= y;
    return x;
}

b7 rem(b13 x)
{
    for (int i = 12; i >= 7; i--)
    {
        if (x[i] != 0)
        {
            x ^= (mod << (i - 7));
        }
    }

    for (int i = 12; i >= 7; i--)
    {
        assert(x[i] == 0);
    }

    b7 ans;
    for (int i = 0; i < 7; i++)
        ans[i] = x[i];

    return ans;
}

b7 mul(b7 x, b7 y)
{
    b13 res;
    res.reset();
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (x[i] == 1 and y[j] == 1)
                res[i + j] = res[i + j] ^ 1;
        }
    }
    return rem(res);
}

b7 power(b7 a, int n)
{
    b7 res = 1;
    while (n)
    {
        if (n & 1)
            res = mul(res, a);
        n >>= 1;
        a = mul(a, a);
    }
    return res;
}

b7 convert(char a, char b)
{
    int foo = ((a - 'f') << 4) + (b - 'f');
    assert(foo < 128);
    b7 res = foo;
    return res;
}

void geninput()
{
    ofstream fout("in.txt");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < 128; j++)
        {
            for (int r = 0; r < 8; r++)
            {
                if (r != i)
                    fout << "ff";
                else
                {
                    fout << char('f' + (j >> 4));
                    fout << char('f' + (j & 15));
                }
            }
            fout << endl;
        }
    }
}

void genoutput()
{
    ifstream fin("in.txt");
    ofstream fout("cmds.txt");

    fout << "NULL" << endl;
    fout << "foobar268" << endl;
    fout << 5 << endl;

    fout << "go" << endl;
    fout << "wave" << endl;
    fout << "dive" << endl;
    fout << "go" << endl;
    fout << "read" << endl;

    string s;
    while (fin >> s)
    {
        fout << s << endl;
        fout << 'c' << endl;
    }

    fout << "back" << endl;
    fout << "exit" << endl;

    fout.close();
    fin.close();

    system("ssh student@65.0.124.36 < cmds.txt > out");
    system("grep --no-group-separator -A 1 \"Slowly, a new text starts appearing on the screen. It reads ...\" out | grep --no-group-separator -v \"Slowly, a new text starts appearing on the screen. It reads ...\" | tr -d \"\\t\" > out.txt");
    system("rm -rf out cmds.txt");
}

int main()
{

    ios_base::sync_with_stdio(false), cin.tie(nullptr);

    geninput();
    genoutput();

    ifstream fin("out.txt");
    vector<pair<int, int>> adj[8];

    string in[8][128];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < 128; j++)
            fin >> in[i][j];
        for (int val = 0; val < 128; val++)
        {
            for (int e = 1; e <= 126; e++)
            {
                bool ok = 1;
                for (int j = 1; j < 128; j++)
                {
                    string s = in[i][j];
                    b7 res = convert(s[2 * i], s[2 * i + 1]);
                    b7 expected = mul(val, power(j, e));
                    expected = mul(val, power(expected, e));
                    expected = power(expected, e);
                    ok &= (res == expected);
                    if (!ok)
                        break;
                }
                if (ok)
                    adj[i].push_back({val, e});
            }
        }
    }

    vector<int> E(8);
    vector<vector<int>> A(8, vector<int>(8));

    for (int i = 1; i < 8; i++)
    {
        for (auto [a11, e1] : adj[i - 1])
        {
            for (auto [a22, e2] : adj[i])
            {
                for (int val = 0; val < 128; val++)
                {
                    bool ok = 1;
                    for (int j = 1; j < 128; j++)
                    {
                        string s = in[i - 1][j];
                        b7 foo = power(add(mul(val, power(mul(a11, power(j, e1)), e1)), mul(a22, power(mul(val, power(j, e1)), e2))), e2);
                        b7 got = convert(s[2 * i], s[2 * i + 1]);
                        ok &= (foo == got);
                    }
                    if (ok)
                    {
                        A[i - 1][i - 1] = a11;
                        A[i][i] = a22;
                        E[i - 1] = e1;
                        E[i] = e2;
                        A[i][i - 1] = val;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = i - 2; j >= 0; j--)
        {
            for (int val = 0; val < 128; val++)
            {
                A[i][j] = val;
                bool ok = 1;
                for (int x = 1; x < 128; x++)
                {
                    b7 foo = 0;
                    for (int k = j; k <= i; k++)
                    {
                        foo = add(foo, mul(A[i][k], power(mul(A[k][j], power(x, E[j])), E[k])));
                    }
                    foo = power(foo, E[i]);
                    b7 got = convert(in[j][x][2 * i], in[j][x][2 * i + 1]);
                    ok &= (foo == got);
                }
                if (ok)
                {
                    break;
                }
            }
        }
    }

    string password = "immlmokkmgisjsmljufkhkimhmflgkgp";

    for (int i = 0; i < 2; i++)
    {
        b7 out[8];
        for (int j = 16 * i; j < 16 * i + 16; j += 2)
        {
            out[(j - 16 * i) / 2] = convert(password[j], password[j + 1]);
        }
        b7 x[8];
        for (int r = 0; r < 8; r++)
        {
            for (int val = 0; val < 128; val++)
            {
                b7 xx[8];
                for (int k = 0; k < 8; k++)
                    xx[k] = x[k];
                x[r] = val;
                for (int _ = 0; _ < 2; _++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        x[j] = power(x[j], E[j]);
                    }
                    b7 y[8];
                    for (int j = 0; j < 8; j++)
                    {
                        y[j] = 0;
                        for (int k = 0; k < 8; k++)
                        {
                            y[j] = add(y[j], mul(A[j][k], x[k]));
                        }
                    }
                    for (int j = 0; j < 8; j++)
                    {
                        x[j] = y[j];
                    }
                }
                for (int j = 0; j < 8; j++)
                {
                    x[j] = power(x[j], E[j]);
                }
                bool ok = 1;
                for (int j = 0; j <= r; j++)
                {
                    ok &= (x[j] == out[j]);
                }
                for (int j = 0; j < 8; j++)
                {
                    x[j] = xx[j];
                }
                if (ok)
                {
                    x[r] = val;
                    break;
                }
            }
            cout << char(x[r].to_ullong());
        }
    }
    cout << endl;

    return 0;
}
