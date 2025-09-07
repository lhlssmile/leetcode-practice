from typing import List
from collections import defaultdict

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        n = len(words)
        m = len(s)
        k = len(words[0])
        total_len = n * k
        ans = []
        
        if m < total_len:
            return ans
        
        # 需求表
        need = defaultdict(int)
        for w in words:
            need[w] += 1
        
        # 遍历起点：对齐方式
        for offset in range(k):
            left = offset
            window = defaultdict(int)
            count = 0  # 窗口内匹配的单词数
            
            # 枚举每个单词起点
            right = offset
            while right + k <= m:
                w = s[right:right + k]
                
                # 窗口右扩
                if w in need:
                    window[w] += 1
                    count += 1
                    
                    # 如果某个单词超频，收缩窗口
                    while window[w] > need[w]:
                        lw = s[left:left + k]
                        window[lw] -= 1
                        left += k
                        count -= 1
                    
                    # 如果窗口刚好包含n个单词
                    if count == n:
                        ans.append(left)
                        # 再往前收缩一步，准备找下一个
                        lw = s[left:left + k]
                        window[lw] -= 1
                        left += k
                        count -= 1
                else:
                    # 不在need中，清空窗口
                    window.clear()
                    count = 0
                    left = right + k
                
                right += k
        
        return ans

def main():
    sol = Solution()
    s = "barfoothefoobarman"
    words = ["foo", "bar"]
    
    result = sol.findSubstring(s, words)
    print(f"Result: {result}")

if __name__ == "__main__":
    main()