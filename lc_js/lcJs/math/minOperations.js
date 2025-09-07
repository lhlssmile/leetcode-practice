function prefix(n) {
    let ans = 0;
    let base = 1;
    let k = 1;
    
    while (true) {
        let nextBase = base * 4;
        let L = base;
        let R = nextBase - 1;
        if (n >= R) {
            ans += (R - L + 1) * k;
        } else {
            ans += (n - L + 1) * k;
            break;
        }
        base = nextBase;
        k++;
    }
    return ans;
}

function minOperations(queries) {
    let total = 0;
    for (let q of queries) {
        let l = q[0];
        let r = q[1];
        let S = prefix(r) - prefix(l - 1);
        total += Math.floor((S + 1) / 2);
    }
    return total;
}

// 测试函数
function testMinOperations() {
    console.log("=== LeetCode 最小操作数问题 ===");
    
    // 测试用例1
    const queries1 = [[1, 4], [2, 6], [3, 8]];
    const result1 = minOperations(queries1);
    console.log(`测试用例1: ${JSON.stringify(queries1)} -> 结果: ${result1}`);
    
    // 测试用例2
    const queries2 = [[1, 10], [5, 15]];
    const result2 = minOperations(queries2);
    console.log(`测试用例2: ${JSON.stringify(queries2)} -> 结果: ${result2}`);
    
    // 测试用例3
    const queries3 = [[1, 1], [2, 2], [3, 3]];
    const result3 = minOperations(queries3);
    console.log(`测试用例3: ${JSON.stringify(queries3)} -> 结果: ${result3}`);
    
    // 测试prefix函数
    console.log("\nprefix函数测试:");
    for (let i = 1; i <= 10; i++) {
        console.log(`prefix(${i}) = ${prefix(i)}`);
    }
}

// 如果在Node.js环境中运行
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { minOperations, prefix };
}

// 如果直接运行此文件
if (typeof window === 'undefined') {
    testMinOperations();
}

/*
算法说明:
1. prefix(n)函数计算从1到n的前缀和
2. 使用base和k来计算每个区间的贡献
3. 对于每个查询[l,r]，计算prefix(r) - prefix(l-1)
4. 最终结果是Math.floor((S+1)/2)

时间复杂度: O(Q * log(max(r)))，其中Q是查询数量
空间复杂度: O(1)

JavaScript特性:
1. 动态类型
2. 函数式编程支持
3. 原型继承
4. 事件驱动
5. 异步编程
*/