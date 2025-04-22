#include <vector>
#include <string>
#include <iostream>
class maxProductSolution{
public:
    int maxProduct(std::vector<std::string>& words){
        int n = words.size();
        std::vector<int> bitmask(n,0);
        std::vector<int> wordLengths(n,0);
        for (int i = 0; i < n; ++i) {
            int mask = 0;
            for(auto c : words[i]){
                //差会设置32位int对应位置 为1
                mask |= (1 << (c - 'a'));
            }
            bitmask[i] = mask;
            wordLengths[i] = static_cast<int>(words[i].size());
        }
        int maxProduct = 0;
        for(int i = 0; i < n;++i){
            for (int j = i + 1; j < n; ++j) {

                if((bitmask[i] & bitmask[j]) == 0){
                    maxProduct = std::max(maxProduct,wordLengths[i] * wordLengths[j]);
                }
            }
        }
        return maxProduct;
    }
};
int main() {
    maxProductSolution ps;
    std::vector<std::string> words = {"abcw","baz","foo","bar","xtfn","abcdef"};
    std::cout << ps.maxProduct(words) << std::endl;
    for(auto const& word : words){
        std::cout << word << std::endl;
    }
    return 0;
}
