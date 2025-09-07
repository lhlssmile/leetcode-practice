/**
 * @param {number[]} nums
 * @return {number}
 */
var singleNumber = function(nums) {
    let ans = 0;
    for (let i = 0; i < 32; i++) {
        let cnt1 = 0;
        for (let x of nums) {
            cnt1 += (x >> i) & 1;
        }
        ans |= (cnt1 % 3) << i;
    }
    return ans;
};

// 状态机解法
var singleNumberStateMachine = function(nums) {
    let ones = 0, twos = 0;
    for (let num of nums) {
        ones = (ones ^ num) & ~twos;
        twos = (twos ^ num) & ~ones;
    }
    return ones;
};

// 函数式编程解法
var singleNumberFunctional = function(nums) {
    return Array.from({length: 32}, (_, i) => i)
        .reduce((ans, i) => {
            const cnt1 = nums.reduce((count, x) => count + ((x >> i) & 1), 0);
            return ans | ((cnt1 % 3) << i);
        }, 0);
};

// 测试
function test() {
    console.assert(singleNumber([2, 2, 3, 2]) === 3);
    console.assert(singleNumber([0, 1, 0, 1, 0, 1, 99]) === 99);
    console.log("All tests passed!");
}

test();