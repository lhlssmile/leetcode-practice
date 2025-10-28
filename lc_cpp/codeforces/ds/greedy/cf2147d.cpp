//
// Created by 24276 on 2025/10/26.
//
#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define fi first
#define se second
#define V vector
#define SORT(v) sort(ALL(v))

using umpii = unordered_map<int, int>;
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
int t, n;
int main() {
    cin >> t;
    For(_, t) {
        cin >> n;
        map<int, int> freq;
        int s = 0, sum = 0;
        For(i, n) {
            int x; cin >> x;
            if (x % 2) freq[x]++, s += x - 1;
            else s += x;
            sum += x;
        }
        int A = s/2;;
        vector<int>b;
        for(auto [u,v] : freq)b.push_back(v);
        sort(b.rbegin(),b.rend());
        for(int i = 0;i<b.size();i+=2)A+=b[i];
        cout<<A<<" "<<sum-A<<endl;
    }

    return 0;
}