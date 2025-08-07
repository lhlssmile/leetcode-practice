//
// Created by 24276 on 2025/8/6.
//
#define ll long long
#include <vector>
#include <unordered_map>
ll gcd (ll a, ll b) {
    while(b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}
#include <string>
class interchangeable_rectangles {
public:
    ll interchangeableRectangles(std::vector<std::vector<int>>& rectangles) {
        ll res = 0;
        std::unordered_map<std::string, ll> cnt;
        for (auto rec : rectangles) {
            ll w = rec[0], h = rec[1];
            ll g = gcd(w, h); // 计算宽高比的最简形式
            w /= g; h /= g;
            std::string key = std::to_string(w) + "/" + std::to_string(h); // 用 w/h 作为 key
            cnt[key]++;
        }
        for (auto& [_, val] : cnt) {
            res += (val * (val - 1)) / 2;    //数论公式?
        }
        return res;
    }
};

int main() {
    std::vector<std::vector<int>> rectangles = {
        {4, 8}, {3, 6}, {10, 20}, {15, 30}
    };
    interchangeable_rectangles ps;
    ps.interchangeableRectangles(rectangles);
    return 0;
}
