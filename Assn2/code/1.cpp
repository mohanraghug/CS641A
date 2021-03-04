#include <bits/stdc++.h>

using namespace std;

int main()
{

    vector<string> a;
    string _;
    while (getline(cin, _))
    {
        a.push_back(_);
    }

    vector<string> grid(5, string(5, ' '));

    string key = "SECURITY";

    char skip = 'J';

    vector<int> row(26, -1), col(26);

    for (int i = 0; i < 8; i++)
    {
        int r = i / 5, c = i % 5;
        grid[r][c] = key[i];
        row[key[i] - 'A'] = r;
        col[key[i] - 'A'] = c;
    }

    int cur = 8;

    for (int i = 0; i < 26; i++)
    {
        if (row[i] == -1 and skip != char('A' + i))
        {
            int r = cur / 5, c = cur % 5;
            grid[r][c] = char('A' + i);
            row[i] = r;
            col[i] = c;
            cur++;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }

    string S = "";

    for (auto &s : a)
    {
        for (char c : s)
        {
            if (c >= 'A' and c <= 'Z')
            {
                S += c;
            }
        }
    }

    int N = int(S.length());
    string T = S;

    for (int i = 0; i < N; i += 2)
    {
        int x = (S[i] - 'A');
        int y = (S[i + 1] - 'A');

        if (row[x] == row[y])
        {
            int cx = col[x];
            int cy = col[y];
            int r = row[x];
            T[i] = grid[r][(cx + 4) % 5];
            T[i + 1] = grid[r][(cy + 4) % 5];
        }
        else if (col[x] == col[y])
        {
            int rx = row[x];
            int ry = row[y];
            int c = col[x];
            T[i] = grid[(rx + 4) % 5][c];
            T[i + 1] = grid[(ry + 4) % 5][c];
        }
        else
        {
            int rx = row[x], cx = col[x], ry = row[y], cy = col[y];
            T[i] = grid[rx][cy];
            T[i + 1] = grid[ry][cx];
        }
    }

    cur = 0;

    for (auto &s : a)
    {
        for (char c : s)
        {
            if (c >= 'A' and c <= 'Z')
            {
                cout << T[cur++];
            }
            else
                cout << c;
        }
        cout << endl;
    }

    return 0;
}

/*

INPUT:
TR XYCB MH AFC MUVY EOHPTCS, AFCSS TE QCSI NTYIMS TNA AFCSC. 
EMRBH XAA VAFR MIUCQPUH "LMRL_CCETOT" FN HM AKUXAHK. OTA WANA
OTXT FFU EISCWNAF HME BFU MCVA UGTOTRE. BM HYLF IFU UVTY ANE 
HBSEI QYOQM OUVSF AM EAFTE PYHYS XNSKE IFUSC.

OUTPUT:
BE WARY OF THE NEXT CHAMBER, THERE IS VERY LITTLE IOY THERE. 
SPEAK OUT XTHE PASSWORD "OPEN_SESAME" TO GO THROUGH. MAY XYOU
HAVE THE STRENGTH FOR THE NEXT CHAMBER. TO FIND THE EXIT YOU 
FIRST WILXL NEXED TO UTTER MAGIC WORDS THERE.

*/