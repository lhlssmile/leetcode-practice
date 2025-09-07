function canThreePartsEqualSum(arr: number[]): boolean {
    let sum: number = 0;
    for (const v of arr) {
        sum += v;
    }
    if (sum % 3 !== 0) {
        return false;
    }
    
    let part: number = 0;
    let currentSum: number = 0;
    
    for (const x of arr) {
        currentSum += x;
        if (currentSum === Math.floor(sum / 3)) {
            currentSum = 0;
            part++;
        }
    }
    return part >= 3;
}

// 类实现
class Solution {
    canThreePartsEqualSum(arr: number[]): boolean {
        let sum: number = 0;
        for (const v of arr) {
            sum += v;
        }
        if (sum % 3 !== 0) {
            return false;
        }
        
        let part: number = 0;
        let currentSum: number = 0;
        
        for (const x of arr) {
            currentSum += x;
            if (currentSum === Math.floor(sum / 3)) {
                currentSum = 0;
                part++;
            }
        }
        return part >= 3;
    }
}

// 测试函数
function testCanThreePartsEqualSum(): void {
    const solution = new Solution();
    
    console.log("=== LeetCode 1013: 将数组分成和相等的三个部分 ===");
    
    // 测试用例1
    const arr1: number[] = [0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1];
    const result1: boolean = canThreePartsEqualSum(arr1);
    const result1Class: boolean = solution.canThreePartsEqualSum(arr1);
    console.log(`测试用例1: ${JSON.stringify(arr1)} -> 结果: ${result1} (类方法: ${result1Class})`);
    
    // 测试用例2
    const arr2: number[] = [0, 2, 1, -6, 6, 6, 7, 9, -1, 2, 0, 1];
    const result2: boolean = canThreePartsEqualSum(arr2);
    const result2Class: boolean = solution.canThreePartsEqualSum(arr2);
    console.log(`测试用例2: ${JSON.stringify(arr2)} -> 结果: ${result2} (类方法: ${result2Class})`);
    
    // 测试用例3
    const arr3: number[] = [3, 3, 3];
    const result3: boolean = canThreePartsEqualSum(arr3);
    const result3Class: boolean = solution.canThreePartsEqualSum(arr3);
    console.log(`测试用例3: ${JSON.stringify(arr3)} -> 结果: ${result3} (类方法: ${result3Class})`);
    
    // 测试用例4
    const arr4: number[] = [1, 1, 1, 1];
    const result4: boolean = canThreePartsEqualSum(arr4);
    const result4Class: boolean = solution.canThreePartsEqualSum(arr4);
    console.log(`测试用例4: ${JSON.stringify(arr4)} -> 结果: ${result4} (类方法: ${result4Class})`);
    
    // 测试用例5
    const arr5: number[] = [0, 0, 0, 0];
    const result5: boolean = canThreePartsEqualSum(arr5);
    const result5Class: boolean = solution.canThreePartsEqualSum(arr5);
    console.log(`测试用例5: ${JSON.stringify(arr5)} -> 结果: ${result5} (类方法: ${result5Class})`);
    
    // 验证结果一致性
    console.log("\n验证结果一致性:");
    console.log(`函数式 vs 类方法 - 测试1: ${result1 === result1Class ? '✓' : '✗'}`);
    console.log(`函数式 vs 类方法 - 测试2: ${result2 === result2Class ? '✓' : '✗'}`);
    console.log(`函数式 vs 类方法 - 测试3: ${result3 === result3Class ? '✓' : '✗'}`);
    console.log(`函数式 vs 类方法 - 测试4: ${result4 === result4Class ? '✓' : '✗'}`);
    console.log(`函数式 vs 类方法 - 测试5: ${result5 === result5Class ? '✓' : '✗'}`);
}

// 导出
export { canThreePartsEqualSum, Solution };

// 如果直接运行此文件
if (typeof window === 'undefined' && typeof process !== 'undefined') {
    testCanThreePartsEqualSum();
}

/*
算法说明:
1. 首先计算数组总和，如果不能被3整除则返回false
2. 遍历数组，累加当前和
3. 当累加和等于目标值(Math.floor(sum/3))时，重置累加和并增加部分计数
4. 最终检查是否找到至少3个部分

时间复杂度: O(n)
空间复杂度: O(1)

TypeScript特性:
1. 静态类型检查
2. 接口和类型定义
3. 类和继承
4. 模块系统
5. 编译时错误检查
*/