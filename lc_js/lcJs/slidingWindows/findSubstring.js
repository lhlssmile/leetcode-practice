/**
 * @param {string} s
 * @param {string[]} words
 * @return {number[]}
 */
var findSubstring = function(s, words) {
    const n = words.length;
    const m = s.length;
    const k = words[0].length;
    const totalLen = n * k;
    const ans = [];
    
    if (m < totalLen) return ans;
    
    // 需求表
    const need = new Map();
    for (const w of words) {
        need.set(w, (need.get(w) || 0) + 1);
    }
    
    // 遍历起点：对齐方式
    for (let offset = 0; offset < k; offset++) {
        let left = offset;
        const window = new Map();
        let count = 0; // 窗口内匹配的单词数
        
        // 枚举每个单词起点
        for (let right = offset; right + k <= m; right += k) {
            const w = s.substring(right, right + k);
            
            // 窗口右扩
            if (need.has(w)) {
                window.set(w, (window.get(w) || 0) + 1);
                count++;
                
                // 如果某个单词超频，收缩窗口
                while (window.get(w) > need.get(w)) {
                    const lw = s.substring(left, left + k);
                    window.set(lw, window.get(lw) - 1);
                    left += k;
                    count--;
                }
                
                // 如果窗口刚好包含n个单词
                if (count === n) {
                    ans.push(left);
                    // 再往前收缩一步，准备找下一个
                    const lw = s.substring(left, left + k);
                    window.set(lw, window.get(lw) - 1);
                    left += k;
                    count--;
                }
            } else {
                // 不在need中，清空窗口
                window.clear();
                count = 0;
                left = right + k;
            }
        }
    }
    
    return ans;
};

// 测试函数
function main() {
    const s = "barfoothefoobarman";
    const words = ["foo", "bar"];
    
    const result = findSubstring(s, words);
    
    console.log("Result:", result);
}

// 如果在Node.js环境中运行
if (typeof module !== 'undefined' && module.exports) {
    module.exports = findSubstring;
    main();
}