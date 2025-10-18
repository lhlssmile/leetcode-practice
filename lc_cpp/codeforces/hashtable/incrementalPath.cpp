#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<ll, ll> runs;

void insert_pos(ll p) {
    auto it = runs.lower_bound(p);
    if (it != runs.end() && it->first == p) return; // already start
    if (it != runs.begin()) {
        auto pit = prev(it);
        if (pit->second >= p) return; // covered
    }
    ll l = p, r = p;
    // merge prev
    it = runs.lower_bound(p);
    if (it != runs.begin()) {
        auto pit = prev(it);
        if (pit->second + 1 == p) {
            l = pit->first;
            r = p;
            runs.erase(pit);
        }
    }
    // merge next
    it = runs.lower_bound(p);
    if (it != runs.end() && it->first == p + 1) {
        r = it->second;
        runs.erase(it);
    }
    runs[l] = r;
}

ll next_white(ll x) {
    auto it = runs.upper_bound(x);
    if (it == runs.begin()) return x + 1;
    --it;
    if (it->second >= x + 1) return it->second + 1;
    return x + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        vector<ll> init(m);
        for (auto& x : init) cin >> x;
        runs.clear();
        for (auto p : init) insert_pos(p);
        // first participant
        ll pos_prev_prev = 1LL;
        ll first_pos;
        if (s[0] == 'A') {
            first_pos = 2;
        } else {
            first_pos = next_white(1);
        }
        insert_pos(first_pos);
        ll pos_prev = first_pos;
        // now for i=2 to n
        for (int i = 2; i <= n; ++i) {
            char cmd_prev = s[i - 2];
            ll temp;
            if (cmd_prev == 'A') {
                temp = pos_prev_prev + 1;
            } else {
                temp = next_white(pos_prev);
            }
            char cmd_cur = s[i - 1];
            ll new_pos;
            if (cmd_cur == 'A') {
                new_pos = temp + 1;
            } else {
                new_pos = next_white(temp);
            }
            insert_pos(new_pos);
            pos_prev_prev = temp;
            pos_prev = new_pos;
        }
        // output
        vector<ll> ans;
        for (auto& pr : runs) {
            for (ll j = pr.first; j <= pr.second; ++j) {
                ans.push_back(j);
            }
        }
        cout << ans.size() << '\n';
        for (size_t j = 0; j < ans.size(); ++j) {
            cout << ans[j];
            if (j + 1 < ans.size()) cout << ' ';
            else cout << '\n';
        }
    }
    return 0;
}