
给你两个整数 `n` 和 `maxValue` ，用于描述一个 **理想数组** 。

对于下标从 **0** 开始、长度为 `n` 的整数数组 `arr` ，如果满足以下条件，则认为该数组是一个 **理想数组** ：

- 每个 `arr[i]` 都是从 `1` 到 `maxValue` 范围内的一个值，其中 `0 <= i < n` 。
- 每个 `arr[i]` 都可以被 `arr[i - 1]` 整除，其中 `0 < i < n` 。

返回长度为 `n` 的 **不同** 理想数组的数目。由于答案可能很大，返回对 `109 + 7` 取余的结果。

**示例 1：**

**输入：**n = 2, maxValue = 5
**输出：**10
**解释：**存在以下理想数组：
- 以 1 开头的数组（5 个）：[1,1]、[1,2]、[1,3]、[1,4]、[1,5]
- 以 2 开头的数组（2 个）：[2,2]、[2,4]
- 以 3 开头的数组（1 个）：[3,3]
- 以 4 开头的数组（1 个）：[4,4]
- 以 5 开头的数组（1 个）：[5,5]
共计 5 + 2 + 1 + 1 + 1 = 10 个不同理想数组。

**示例 2：**

**输入：**n = 5, maxValue = 3
**输出：**11
**解释：**存在以下理想数组：
- 以 1 开头的数组（9 个）：
   - 不含其他不同值（1 个）：[1,1,1,1,1] 
   - 含一个不同值 2（4 个）：[1,1,1,1,2], [1,1,1,2,2], [1,1,2,2,2], [1,2,2,2,2]
   - 含一个不同值 3（4 个）：[1,1,1,1,3], [1,1,1,3,3], [1,1,3,3,3], [1,3,3,3,3]
- 以 2 开头的数组（1 个）：[2,2,2,2,2]
- 以 3 开头的数组（1 个）：[3,3,3,3,3]
共计 9 + 1 + 1 = 11 个不同理想数组。

**提示：**

- `2 <= n <= 104`
- `1 <= maxValue <= 104`


### mine thoughts


given 2 integer n & maxValue,which are used to describe ideal array

**ideal array:**
1. **length must be equals n**
2. **0 <= arr[i] <= n **
3. **arr[i - 1] % arr[i] == 0?**


**?**
- 枚举maxValue -> {1,maxValue}  ? 可以 取重复值 例如 n个相同元素的ideal array?
- 能不能用数学的方法解决？ 
	- ex 当arr[0] = 1 后边的数全都能被1 整除？ - > 有**maxValue / 1**个选择 但这是长度为n(2) 如果n是一般的？
	- 找到最后一个位置(n)并且是当前开头数字 的 最大可被整除的积（且小于maxValue?) ex: 例一? 2开头 不论n为多少? 下标为n-1的位置值最大为 x % 2 == 0?
- dp？相当于是看{0,i}上可选的数字 有几种情况？
	- 选第i位上的数字 都有限制 arr[i] 会被arr[i - 1]限制 
		- 例2？1开头时候
			- [1,1,....] , [1,2,....] ?
			- [1,1,1],[1,1,2]   [1,2,2],[1,2,4] **越是后边选择越少**
