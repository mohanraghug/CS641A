#include <bits/stdc++.h>
using namespace std;

void prepare(string &s)
{
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        int x;
        if (s[i] >= '0' and s[i] <= '9')
        {
            x = s[i] - '0';
        }
        if (s[i] >= 'A' and s[i] <= 'F')
        {
            x = s[i] - 'A' + 10;
        }

        for (int j = 0; j < 4; j++)
        {
            if ((x & (1 << j)) != 0)
                ans += '1';
            else
                ans += '0';
        }
    }
    s = ans;
}

int main()
{
    string s = "6A6460690000000001018004666168EA6B6FE5ED666168EA010B8584666168EA000A058000000000010B8584666168EA6A6E65E9000000006A64606900000000";

    prepare(s);
    uint64_t final_state[5][5][64];

    assert(int(s.size()) == 512);

    for (int i = 0, cur = 0; cur < 512; i++)
    {
        for (int j = 0; j < 5 and cur < 512; j++)
        {
            for (int k = 0; k < 64 and cur < 512; k++)
            {
                final_state[i][j][k] = s[cur++] - '0';
            }
        }
    }

    uint64_t state[5][5][64], ans[5][5][64];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 64; k++)
                state[i][j][k] = ans[i][j][k] = 0;

    vector<int> adj[64];
    for (int i = 0, cur = 0; cur < 128; i++)
    {
        for (int j = 0; j < 5 and cur < 128; j++)
        {
            for (int k = 0; k < 64 and cur < 128; k++)
            {
                adj[k].push_back(i * 5 + j);
                cur++;
            }
        }
    }

    for (int kk = 0; kk < 64; kk++)
    {
        int nn = int(adj[kk].size());
        int cnt = 0;
        for (int mask = 0; mask < (1 << nn); mask++)
        {
            for (int i = 0; i < nn; i++)
            {
                if ((mask & (1 << i)) != 0)
                {
                    int ii = adj[kk][i] / 5;
                    int jj = adj[kk][i] % 5;
                    state[ii][jj][kk] = 1;
                    ans[ii][jj][kk] = 1;
                }
            }

            char hexa[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

            uint64_t b = 1600;
            uint64_t l = 512;
            uint64_t c = 1024;
            uint64_t r = 576;
            int rounds = 24;
            int i, j, k;

            uint64_t tempstate[5][5][64];

            uint64_t current_round = 0;
            uint64_t column_parity[5][64];

            while (current_round < rounds)
            {
                //theta operation
                for (i = 0; i < 5; ++i)
                {
                    for (k = 0; k < 64; ++k)
                    {
                        column_parity[i][k] = 0;
                        for (j = 0; j < 5; ++j)
                            column_parity[i][k] ^= state[i][j][k];
                    }
                }

                for (i = 0; i < 5; ++i)
                {
                    for (j = 0; j < 5; ++j)
                    {
                        for (k = 0; k < 64; ++k)
                        {
                            state[i][j][k] ^= column_parity[(i + 4) % 5][k] ^ column_parity[(i + 1) % 5][k];
                            tempstate[i][j][k] = state[i][j][k];
                        }
                    }
                }

                //pi operation
                for (i = 0; i < 5; ++i)
                    for (j = 0; j < 5; ++j)
                        for (k = 0; k < 64; ++k)
                            state[j][((2 * i) + (3 * j)) % 5][k] = tempstate[i][j][k];

                //chi operation
                for (i = 0; i < 5; ++i)
                    for (j = 0; j < 5; ++j)
                        for (k = 0; k < 64; ++k)
                            tempstate[i][j][k] = state[i][j][k];

                for (i = 0; i < 5; ++i)
                    for (j = 0; j < 5; ++j)
                        for (k = 0; k < 64; ++k)
                            state[i][j][k] = tempstate[i][j][k] ^ (~tempstate[i][(j + 1) % 5][k] & tempstate[i][(j + 2) % 5][k]);

                ++current_round;
            }

            bool ok = 1;

            for (i = 0; i < 5; i++)
                for (j = 0; j < 5; j++)
                {
                    int foo = i * 5 * 64 + j * 64 + kk;
                    if (foo >= 512)
                        break;
                    ok &= (final_state[i][j][kk] == state[i][j][kk]);
                }

            for (i = 0; i < 5; i++)
            {
                for (j = 0; j < 5; j++)
                {
                    state[i][j][kk] = 0;
                    if (!ok)
                        ans[i][j][kk] = 0;
                }
            }

            if (ok)
            {
                break;
            }
        }
    }

    string pass = "";
    for (int i = 0, cur = 0; cur < 128; i++)
    {
        for (int j = 0; j < 5 and cur < 128; j++)
        {
            for (int k = 0; k < 64 and cur < 128; k++)
            {
                pass += char('0' + ans[i][j][k]);
                cur++;
            }
        }
    }

    cout << "The password is ";
    for (int i = 0; i < pass.size(); i += 8)
    {
        int cur = 0;
        for (int j = i; j - i < 8; j++)
        {
            cur = (cur << 1) + (pass[j] - '0');
        }
        if (cur)
            cout << char(cur);
    }
    cout << endl;

    return 0;
}