//
// Created by 24276 on 2025/10/16.
//
#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
int cost_for (int startAt, int moveCost, int pushCost, int m, int s) {
    char buf[5];
    sprintf(buf, "%02d%02d", m, s);
    string t = buf;
    int i = 0;
    while (i < 4 && t[i] == '0') i++;
    if (i == 4) t = "0";
    else t = t.substr(i);

    char cur = '0' + startAt;
    int cost = 0;
    for (char c : t) {
        if (c != cur) {
            cost += moveCost;
            cur = c;
        }
        cost += pushCost;
    }
    return cost;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(__nullptr);

    int startAt, moveCost, pushCost, targetSeconds;
    cin >> startAt >> moveCost >> pushCost >> targetSeconds;

    int mm = targetSeconds / 60;
    int ss = targetSeconds % 60;
    vector<pii> candidates;
    if (mm <= 99 && ss <= 99) {
        candidates.push_back({mm, ss});
    }
    if (mm > 0 && ss + 60 <= 99) {
        candidates.push_back({mm - 1, ss + 60});
    }
    int res = INT_MAX;
    for (auto [m ,s] : candidates) {
        res = min(res, cost_for(startAt, moveCost, pushCost, m, s));
    }
    return 0;
}
