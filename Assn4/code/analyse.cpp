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
    ofstream fout("test_inputs.txt");

    int L = 1000;
    for (int i = 0; i < L; i++)
    {
        uint64_t first = 0;
        string s = "";
        for (int j = 0; j < 8; j++)
        {
            int k = getRand(0, 255);
            first = (first << 4) + k;
            s += char(k);
        }
        fout << s << endl;
    }
}

void getoutputs()
{
    ifstream fin("test_inputs.txt");
    ofstream fout("test_cmds.txt");

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

    system("ssh student@65.0.124.36 < test_cmds.txt > out");
    system("grep --no-group-separator -A 1 \"Slowly, a new text starts appearing on the screen. It reads ...\" out | grep --no-group-separator -v \"Slowly, a new text starts appearing on the screen. It reads ...\" | tr -d \"\\t\" > test_outputs.txt");
    system("rm -rf out test_cmds.txt");
}

void analyze()
{
    ifstream fin("test_outputs.txt");
    map<pair<char,char>, int> cnt;
    string s;
    while (fin >> s)
    {
        int n = s.size();
        for (int i = 0; i < n; i += 2)
        {
            cnt[make_pair(s[i], s[i + 1])]++;
        }
    }
    for (auto [c, _] : cnt)
    {
        cout << c.first << ' ' << c.second << endl;
    }
    cout << endl;
}

int main()
{

    getinputs();
    getoutputs();
    analyze();

    return 0;
}
