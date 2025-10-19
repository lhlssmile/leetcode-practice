#include <bits/stdc++.h>
using namespace std;

bool isRXCY(const string& s) {
    if (s.size() < 4 || s[0] != 'R') return false;
    int posC = s.find('C');
    if (posC == string::npos) return false;
    for (int i = 1; i < posC; i++) if (!isdigit(s[i])) return false;
    for (int i = posC + 1; i < s.size(); i++) if (!isdigit(s[i])) return false;
    return true;
}

string colToStr(int c) {
    string res;
    while (c > 0) {
        c--;
        res.push_back('A' + (c % 26));
        c /= 26;
    }
    reverse(res.begin(), res.end());
    return res;
}

int strToCol(const string& s) {
    int c = 0;
    for (char ch : s) {
        c = c * 26 + (ch - 'A' + 1);
    }
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        if (isRXCY(s)) {
            // R23C55 → BC23
            int posC = s.find('C');
            int row = stoi(s.substr(1, posC - 1));
            int col = stoi(s.substr(posC + 1));
            cout << colToStr(col) << row << "\n";
        } else {
            // BC23 → R23C55
            int j = 0;
            while (isalpha(s[j])) j++;
            string letters = s.substr(0, j);
            int row = stoi(s.substr(j));
            cout << 'R' << row << 'C' << strToCol(letters) << "\n";
        }
    }
}
