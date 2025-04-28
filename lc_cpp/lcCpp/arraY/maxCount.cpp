#include <iostream>
#include <vector>
class MaxCountSolution{
public:
    int maxCount(int m,int n,std::vector<std::vector<int>>& ops){
        if(ops.empty()) return m * n;
        int min_a = m;
        int min_b = n;
        for(const auto& op : ops){
            min_a = std::min(min_a,op[0]);
            min_b = std::min(min_b,op[1]);
        }
        return min_a * min_b;
    }
};
int main() {
    MaxCountSolution ps;
    int m =39999,n = 39999;std::vector<std::vector<int>> ops = {{19999,19999}};
    std::cout << ps.maxCount(m,n,ops) << std::endl;
    return 0;
}
