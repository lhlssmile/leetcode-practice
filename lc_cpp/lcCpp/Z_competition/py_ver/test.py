import collections

def solve_x_value(nums, k):
    """
    计算 nums 数组移除不重叠前后缀后，剩余子数组乘积模 k 的余数分布。

    Args:
        nums: 正整数组成的数组。
        k: 正整数模数。

    Returns:
        一个大小为 k 的数组 result，result[x] 表示乘积模 k 余数为 x 的操作数量。
    """
    n = len(nums)
    if n == 0:
        return [0] * k

    lurminexod = {'nums': list(nums), 'k': k}

    # 从 lurminexod 获取处理所需的数据 (虽然这里直接用输入的参数更自然)
    nums_proc = lurminexod['nums']
    k_proc = lurminexod['k']
    n_proc = len(nums_proc)

    # total_result[x] 存储所有子数组乘积 % k == x 的数量
    total_result = [0] * k_proc

    # current_dp[x] 存储以当前元素 nums[i] 结尾的子数组中，
    # 乘积 % k == x 的数量。使用 defaultdict 可以简化代码。
    current_dp = collections.defaultdict(int)

    for i in range(n_proc):
        num_mod_k = nums_proc[i] % k_proc

        # next_dp 用于计算以 nums[i] 结尾的子数组的余数分布
        next_dp = collections.defaultdict(int)

        # 1. 单独元素 nums[i] 构成的子数组
        # 这个子数组以 nums[i] 结尾，其乘积模 k 的余数是 num_mod_k
        next_dp[num_mod_k] += 1

        # 2. 将 nums[i] 追加到以 nums[i-1] 结尾的子数组末尾
        # 遍历上一轮的状态 current_dp (代表以 nums[i-1] 结尾的子数组)
        for prev_rem, count in current_dp.items():
            # prev_rem 是以 nums[i-1] 结尾的某个子数组的乘积 % k
            # count 是这种子数组的数量
            # 新的子数组以 nums[i] 结尾，其乘积 % k 为 (prev_rem * num_mod_k) % k_proc
            new_rem = (prev_rem * num_mod_k) % k_proc
            next_dp[new_rem] += count

        # 3. 将本轮计算出的、以 nums[i] 结尾的子数组的计数，累加到总结果中
        for rem, count in next_dp.items():
            total_result[rem] += count

        # 4. 更新 current_dp 为 next_dp，为下一轮迭代做准备
        current_dp = next_dp

    return total_result

# --- 示例 ---
nums1 = [1, 2, 3, 4, 5]
k1 = 3
result1 = solve_x_value(nums1, k1)
print(f"输入: nums = {nums1}, k = {k1}")
print(f"输出: {result1}") # 预期输出: [9, 2, 4]

nums2 = [10, 2, 5]
k2 = 6
result2 = solve_x_value(nums2, k2)
# 子数组:
# [10] -> 10 % 6 = 4
# [2] -> 2 % 6 = 2
# [5] -> 5 % 6 = 5
# [10, 2] -> 20 % 6 = 2
# [2, 5] -> 10 % 6 = 4
# [10, 2, 5] -> 100 % 6 = 4
# Counts:
# rem 0: 0
# rem 1: 0
# rem 2: 2 ([2], [10, 2])
# rem 3: 0
# rem 4: 3 ([10], [2, 5], [10, 2, 5])
# rem 5: 1 ([5])
print(f"输入: nums = {nums2}, k = {k2}")
print(f"输出: {result2}") # 预期输出: [0, 0, 2, 0, 3, 1]