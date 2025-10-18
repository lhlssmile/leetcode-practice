/**
 * @param {string} s
 * @return {string[]}
 */
var letterCasePermutation = function(s) {
    const ans = [];
    const path = [];
    
    const dfs = (i) => {
        if (i === s.length) {
            ans.push(path.join(''));
            return;
        }
        
        const ch = s[i];
        if (/\d/.test(ch)) {
            path.push(ch);
            dfs(i + 1);
            path.pop();
        } else {
            // 小写
            path.push(ch.toLowerCase());
            dfs(i + 1);
            path.pop();
            
            // 大写
            path.push(ch.toUpperCase());
            dfs(i + 1);
            path.pop();
        }
    };
    
    dfs(0);
    return ans;
};

// 测试函数
function main() {
    // 测试用例1
    const s1 = "a1b2";
    const result1 = letterCasePermutation(s1);
    console.log(`Input: ${s1}`);
    console.log(`Output: ${JSON.stringify(result1)}`);
    
    // 测试用例2
    const s2 = "3z4";
    const result2 = letterCasePermutation(s2);
    console.log(`Input: ${s2}`);
    console.log(`Output: ${JSON.stringify(result2)}`);
}

main();

/*
算法思路：递归回溯生成所有可能的字母大小写排列
时间复杂度：O(2^n)，其中n是字符串中字母的数量
空间复杂度：O(n)，递归栈的深度和临时字符串的空间
*/