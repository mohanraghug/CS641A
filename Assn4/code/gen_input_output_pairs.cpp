#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int getRand(int l, int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void getinputs()
{
    uint64_t diff = 0x405c000004000000;

    ofstream fout("inputs.txt");
    int IP[] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7};

    uint64_t rdiff = 0;
    for (int i = 0; i < 64; i++)
    {
        uint64_t cur = ((diff >> (63 - i)) & 1);
        int to = IP[i];
        rdiff |= (cur << (64 - to));
    }

    int L = 1e5;
    for (int i = 0; i < L; i++)
    {
        uint64_t first = 0;
        string s = "";
        for (int j = 0; j < 16; j++)
        {
            int k = getRand(0, 15);
            first = (first << 4) + k;
            s += char('f' + k);
        }
        fout << s << endl;
        s = "";
        uint64_t second = (first ^ rdiff);
        for (int j = 0; j < 16; j++)
        {
            int num = 0;
            for (int k = 0; k < 4; k++)
            {
                int at = 4 * j + k;
                int cur = ((second >> (63 - at)) & 1);
                num += (cur << (3 - k));
            }
            s += char('f' + num);
        }
        fout << s << endl;
    }
}

void getoutputs()
{
    ifstream fin("inputs.txt");
    ofstream fout("cmds.txt");

    fout << "NULL" << endl;
    fout << "foobar268" << endl;
    fout << 4 << endl;

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
    system("grep --no-group-separator -A 1 \"Slowly, a new text starts appearing on the screen. It reads ...\" out | grep --no-group-separator -v \"Slowly, a new text starts appearing on the screen. It reads ...\" | tr -d \"\\t\" > outputs.txt");
    system("rm -rf out cmds.txt");
}

int main()
{

    getinputs();
    getoutputs();

    return 0;
}
