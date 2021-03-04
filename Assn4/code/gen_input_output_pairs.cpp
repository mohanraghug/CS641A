#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int getRand(int l, int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

inline int64_t random_long(long long l, long long r)
{
    uniform_int_distribution<int64_t> generator(l, r);
    return generator(rng);
}

void getinputs()
{
    // todo generate inputs randomly
    ofstream fout("inputs.txt");
    fout << "password" << endl;
    fout << "password" << endl;
    fout << "foobar" << endl;
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
