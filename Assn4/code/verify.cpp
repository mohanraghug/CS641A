#include <bits/stdc++.h>

using namespace std;

int main()
{

    fstream fin("outputs.txt");
    string s;
    while (fin >> s)
    {
        for (char c : s)
        {
            assert(c >= 'f' and c <= 'u');
        }
    }

    return 0;
}