class Solution {
    // 位运算解法
    singleNumber(nums: number[]): number {
        let ans = 0;
        for (let i = 0; i < 32; i++) {
            let cnt1 = 0;
            for (const x of nums) {
                cnt1 += (x >> i) & 1;
            }
            ans |= (cnt1 % 3) << i;
        }
        return ans;
    }
    
    // 状态机解法
    singleNumberStateMachine(nums: number[]): number {
        let ones = 0, twos = 0;
        for (const num of nums) {
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }
        return ones;
    }
    
    // 泛型解法
    singleNumberGeneric<T extends number>(nums: T[]): T {
        let ans = 0 as T;
        for (let i = 0; i < 32; i++) {
            let cnt1 = 0;
            for (const x of nums) {
                cnt1 += (x >> i) & 1;
            }
            ans |= ((cnt1 % 3) << i) as T;
        }
        return ans;
    }
}

// 函数式编程解法
const singleNumberFunctional = (nums: number[]): number => {
    return Array.from({length: 32}, (_, i) => i)
        .reduce((ans, i) => {
            const cnt1 = nums.reduce((count, x) => count + ((x >> i) & 1), 0);
            return ans | ((cnt1 % 3) << i);
        }, 0);
};

// 测试
function test(): void {
    const sol = new Solution();
    console.assert(sol.singleNumber([2, 2, 3, 2]) === 3);
    console.assert(sol.singleNumber([0, 1, 0, 1, 0, 1, 99]) === 99);
    console.log("All tests passed!");
}

test();