#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    // Step 1. 整体 gcd
    int g = a[0];
    for (int i = 1; i < n; i++) g = gcd(g, a[i]);

    for (int &x : a) x /= g;

    // Step 2. 筛出质数（sqrt(1e7)=3162）
    const int MAXP = 31623;
    vector<int> primes;
    vector<bool> is_comp(MAXP + 1);
    for (int i = 2; i <= MAXP; i++) {
        if (!is_comp[i]) {
            primes.push_back(i);
            if ((long long)i * i <= MAXP)
                for (int j = i * i; j <= MAXP; j += i)
                    is_comp[j] = true;
        }
    }

    // Step 3. 分解并检测质因数出现情况
    unordered_set<int> used;
    for (int x : a) {
        int tmp = x;
        for (int p : primes) {
            if ((long long)p * p > tmp) break;
            if (tmp % p == 0) {
                if (used.count(p)) {
                    cout << "NO\n";
                    return 0;
                }
                used.insert(p);
                while (tmp % p == 0) tmp /= p;
            }
        }
        if (tmp > 1) { // 可能剩下一个大质因数
            if (used.count(tmp)) {
                cout << "NO\n";
                return 0;
            }
            used.insert(tmp);
        }
    }

    cout << "YES\n";
    return 0;
}
