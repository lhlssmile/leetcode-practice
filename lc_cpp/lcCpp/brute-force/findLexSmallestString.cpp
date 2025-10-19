
#include <bits/stdc++.h>
using namespace std;
int a, b;
string s;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> b >> s;
    string ans;
    unordered_set<string> seen;
    queue<string> q;
    q.push(s);
    while (!q.empty()) {
        string cur = q.front(); q.pop();
        ans = min(ans, cur);

        //opa
        string op1 = cur;
        for (int i = 1; i < cur.size(); i+= 2) {
            int d = (op1[i] - '0' + a ) % d;
            op1[i] = char(d + '0');
        }
        if (!seen.count(op1)) {
            seen.insert(op1);
            q.push(op1);
        }
        //opb
        string op2 = cur.substr(cur.size() - b) + cur.substr(0, cur.size() - b);
        if (!seen.count(op2)) {
            seen.insert(op2);
            q.push(op2);
        }
    }
    cout << ans << "\n";
    return 0;
}