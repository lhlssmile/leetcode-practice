#include <bits/stdc++.h>
using namespace std;

bool ok(int x, int y, int z) {
    for (int i = 0; i < 30; i++) {
        int xi = (x >> i) & 1;
        int yi = (y >> i) & 1;
        int zi = (z >> i) & 1;
        int sum = xi + yi + zi;
        if (sum == 2) return false; // 两个1一个0 不可能
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int x, y, z;
        cin >> x >> y >> z;
        cout << (ok(x, y, z) ? "YES\n" : "NO\n");
    }
    return 0;
}
