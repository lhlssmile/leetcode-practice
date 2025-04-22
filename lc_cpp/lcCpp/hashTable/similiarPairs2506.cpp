//mine thoughts
/**
 *
*去重字符：

将每个单词的字符去重确实是一个好主意。比如：
"aba" → "ab"
"aabb" → "ab"
"abcd" → "abcd"
"bac" → "abc"
"aabc" → "abc"
你提到的是对的，字符顺序不重要，只需要知道字符集合相同就行了。
相似性的判断：

你考虑用哈希表（比如 map<string, int>）存储去重后的字符集合，并统计出现的次数，这个方向是对的。
不需要用 vector 存储实际的单词，只需要统计出现频次就行，因为最后只要计算满足条件的对数。
计数方案：

如果某个字符集合出现了 count 次，那么这些单词两两组合能组成的相似对数是：
组合数 = [count * (count - 1)] / 2

这是一个 组合数学公式，代表从 count 个单词中选出 2 个单词的方法数。
 **/

#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;
class similiar_pairs2506 {
public:
  int similarPairs(vector<string>& words) {
   //map 键是words[i](处理后  值是出现频次
   unordered_map<int,int> map;
   for(auto const& word : words) {
    int mask = 0;
    for(auto const c : word) {
     //先做减法  然后向左移动1 差位 最后进行按位或运算
     mask |= 1 << (c - 'a');
       }
    map[mask]++;
   }
   int count = 0;
   //mask 是键 words[i] freq是出现频次
   for(auto& [mask,freq] : map) {
    count += (freq * (freq - 1)) / 2;
   }
   return count;
  }
};

int main() {
 similiar_pairs2506 ps;
 vector<string> words = {"aba","aabb","abcd","bac","aabc"};
 cout << ps.similarPairs(words) << endl;
#ifdef _MSC_VER
 std::cout << "MSVC Version: " << _MSC_VER << "\n";
#endif
 std::cout << "C++ Standard: " << __cplusplus << "\n";
 return 0;
}

