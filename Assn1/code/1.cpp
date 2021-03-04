// Code used to correct the punctuation and print the frequencies

#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<string> a;
    {
        // taking the cipher text as input line by line.
        string s;
        while (getline(cin, s))
        {
            a.push_back(s);
        }
    }

    /*
        The punctuation doesn't seem to be correct for the given paragraph.
        For instance, the paragraph doesn't end with a punctuation mark(.) and there seems to be an 
        incomplete sentence in the end. Also the first letter of the Paragraph is not capitalised.
        some words start with a punctuation mark and there is also an exclamation mark in the middle of a word in line 4.
        Since identification of words is important for carrying out Frequency Analysis, we need to crct these errors.
        All these errors can be corrected by cyclically shifting the paragraph by 10 places which is done by the following piece of code.
    */

    vector<string> b = a;

    int n = int(a.size());
    for (int i = 0; i < n; i++)
    {
        int m = int(a[i].length());
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] == ' ')
                continue;
            int row = i, col = j;
            int cnt = 0;
            while (cnt < 10)
            {
                if (col + 1 < int(a[row].length()))
                    col++;
                else
                {
                    row = (row + 1) % n;
                    col = 0;
                }
                if (a[row][col] != ' ')
                    cnt++;
            }
            b[row][col] = a[i][j];
        }
    }

    for(auto& s:b)
        cout << s << endl;

    cout << endl
         << endl;

    {
        const int A = 26;

        vector<int> cnt(A);

        for (auto &s : b)
        {
            for (char c : s)
            {
                if (c >= 'A' and c <= 'Z')
                    cnt[c - 'A']++;
                if (c >= 'a' and c <= 'z')
                    cnt[c - 'a']++;
            }
        }

        vector<int> ord(A);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int x, int y) { return cnt[x] > cnt[y]; });

        cout << setprecision(3) << fixed;

        int tot = accumulate(cnt.begin(), cnt.end(), 0);

        for (int i : ord)
        {
            cout << char('A' + i) << "  " << cnt[i] << "  " << double(cnt[i] * 100) / tot << endl;
        }
    }

    return 0;
}

/*
INPUT:

wsam ie pjo ysgtm eyipbya .P axg niphay y, 
mey syw ahgm ewhrg tw hmysyam wh meyiepjo 
ys .Ag jygtmeyk pmys ie pjo ysavw kkoyjgsy 
whmy sy amwh rmephmewagh y!Me yigu ynay utg 
smew ajya apr ywap awjfkya no a mwmnmw 
ghiwfeyswhve wieuwr wm aepby oyyhae wtmy 
uox8 fkpiya. Me y fpaavgs uwa mxSrN03u wd 
dvwmegnmmey dngmya. Mew awameyt

*/

/*
OUTPUT:

Mewa wa mey twsam iepjoys gt mey ipbya. Pa 
xgn iph ayy, meysy wa hgmewhr gt whmysyam 
wh mey iepjoys. Agjy gt mey kpmys iepjoysa 
vwkk oy jgsy whmysyamwhr meph mewa ghy! Mey 
iguy nayu tgs mewa jyaapry wa p awjfky 
anoamwmnmwgh iwfeys wh vewie uwrwma epby 
oyyh aewtmyu ox 8 fkpiya. Mey fpaavgsu wa 
mxSrN03uwdd vwmegnm mey dngmya.


Y  36  13.953
M  28  10.853
A  27  10.465
W  25  9.690
E  22  8.527
G  14  5.426
P  13  5.039
S  13  5.039
H  12  4.651
I  9  3.488
J  7  2.713
O  7  2.713
N  7  2.713
T  6  2.326
U  6  2.326
K  5  1.938
R  5  1.938
V  4  1.550
F  4  1.550
X  3  1.163
D  3  1.163
B  2  0.775
Q  0  0.000
L  0  0.000
C  0  0.000
Z  0  0.000

*/

/*

DECRYPTED TEXT:

This is the first chamber of the caves. As 
you can see, there is nothing of interest 
in the chamber. Some of the later chambers 
will be more interesting than this one! The 
code used for this message is a simple 
substitution cipher in which digits have 
been shifted by 4 places. The password is 
tyRgU69diqq without the quotes.

*/