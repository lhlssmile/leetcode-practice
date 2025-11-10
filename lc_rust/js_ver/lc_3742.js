/**
 * @param {number[]} nums - 数组
 * @returns {number} - 最小span*2 or -1
 */
const minimumDistance = (nums) => {
    const n = nums.length;
    if (n < 3) return -1;

    // FP: reduce建pos Map<number, number[]>（enumerate-like）
    const pos = nums.reduce((map, val, i) => {  // i=索引像enumerate
        if (!map.has(val)) map.set(val, []);
        map.get(val).push(i);  // push下标
        return map;
    }, new Map());  // 初始空Map

    // FP核心：values() → filter >=3 → flatMap windows span*2 → reduce min
    const INF = 10 ** 18;
    const best = [...pos.values()]  // Array.from(values)
        .filter(idxs => idxs.length >= 3)
        .flatMap(idxs =>
            idxs.slice(0, -2)  // 前f-2个t，像range(f-2)
                .map((_, t) => (idxs[t + 2] - idxs[t]) * 2)  // span*2
        )
        .reduce((min, span) => Math.min(min, span), INF);

    return best === INF ? -1 : best;
};

// 测试（console跑）
console.log(minimumDistance([1, 2, 1, 3, 1]));  // 4 (1 at 0,2,4: (4-0)*2=8, (4-2)*2=4 →4)
console.log(minimumDistance([1, 2, 3]));  // -1 (无>=3)
console.log(minimumDistance([1]));  // -1 (n<3)