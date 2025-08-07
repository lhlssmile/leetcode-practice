//
// Created by 24276 on 2025/8/7.
//
#include <vector>

class Union {
private:
    std::vector<int> parent;
    int count;
public:
    Union(int n) {
        parent.resize(n);
        count = n;
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if( rootX != rootY) {
            parent[rootX] = rootY;
            --count;
        }
    }
    int getCount() const {
        return count;
    }

};
class find_circle_num {
public:
    int findCircleNum (std::vector<std::vector<int>>& isConnected) {
        int n = isConnected.size();
        Union u(n);
        for (int i = 0; i < n;++i) {
            for(int j = i + 1; j < n;j++) {
                if (isConnected[i][j] == 1) {
                    u.unionSet(i, j);
                }
            }
        }
        return u.getCount();
    }
};

int main() {
    return 0;
}
