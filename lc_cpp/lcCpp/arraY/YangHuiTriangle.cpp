#include <iostream>
#include <vector>
#include <unordered_map>
class yangHuiTriangleSolution{
public:
    std::unordered_map<int,std::vector<int>> cache;
    //recursion
    std::vector<int> getRow(int rowIndex){
        //store previous index answer
        if (rowIndex == 0) return {1};
        if(cache.find(rowIndex) != cache.end()) return cache[rowIndex];
        std::vector<int> prev_row = getRow(rowIndex - 1);
        std::vector<int> current_row(rowIndex + 1,1);
        for (int i = 1; i < rowIndex; ++i) {
            current_row[i] = prev_row[i - 1] + prev_row[i];
        }
        cache[rowIndex] = current_row;
        return current_row;
    }
    //use dynamic programing
    std::vector<int> getRowDP(int rowIndex){
        std::vector<int> row(rowIndex + 1,0);
        row[0] = 1;
        for (int i = 1; i <= rowIndex; ++i) {
            for(int j = i;j > 0; --j){
                row[j] += row[j - 1];
            }
        }
        return row;
    }
};
int main() {
    yangHuiTriangleSolution ps;
    std::vector<int> row_vector =  ps.getRowDP(3);

    std::cout << "[" << std::endl;
    for (auto const& x: row_vector) {
        std::cout << x << ",";
    }
    std::cout << "]" << std::endl;
    return 0;
}
