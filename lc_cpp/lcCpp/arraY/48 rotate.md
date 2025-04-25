给定一个 _n_ × _n_ 的二维矩阵 `matrix` 表示一个图像。请你将图像顺时针旋转 90 度。

你必须在 **[原地](https://baike.baidu.com/item/%E5%8E%9F%E5%9C%B0%E7%AE%97%E6%B3%95)** 旋转图像，这意味着你需要直接修改输入的二维矩阵。**请不要** 使用另一个矩阵来旋转图像。

**示例 1：**

![](https://assets.leetcode.com/uploads/2020/08/28/mat1.jpg)

**输入：**matrix = [[1,2,3],[4,5,6],[7,8,9]]
**输出：**[[7,4,1],[8,5,2],[9,6,3]]

**示例 2：**

![](https://assets.leetcode.com/uploads/2020/08/28/mat2.jpg)

**输入：**matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
**输出：**[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]




## 📒 旋转二维矩阵笔记（顺时针 90°）

### 🎯 目标

将一个 `n x n` 矩阵顺时针旋转 90°，并且**原地修改**（不使用额外矩阵）。

---

### ✅ 方法一：**转置 + 行反转法**（主流推荐）

1. **转置矩阵**：沿对角线翻转，即交换 `matrix[i][j]` 和 `matrix[j][i]`。
    
2. **每一行翻转**：对每一行 `reverse(matrix[i])`。
    

#### ✅ 代码（转置 + 翻转）：

```cpp
void rotate(vector<vector<int>>& matrix) {     
	int n = matrix.size();     
	for (int i = 0; i < n; ++i)         
		for (int j = i + 1; j < n; ++j)             
		swap(matrix[i][j], matrix[j][i]);      
		
		for (int i = 0; i < n; ++i)         
			reverse(matrix[i].begin(), matrix[i].end()); }
```

---

### ✅ 方法二：**按圈逐个旋转法（4点轮换）**

将每一圈的四个点进行“循环交换”：

- 每一组四个点：
```css
(i, j)         → (j, n-1-i) 
(j, n-1-i)     → (n-1-i, n-1-j)
(n-1-i, n-1-j) → (n-1-j, i) 
(n-1-j, i)     → (i, j)
```

#### ✅ 代码（一圈式）：


```cpp
void rotate(vector<vector<int>>& matrix) {     
	int n = matrix.size();     
	for (int layer = 0; layer < n / 2; ++layer) {         
	int first = layer;         
	int last = n - 1 - layer;         
		for (int i = first; i < last; ++i) {             
		int offset = i - first;              
		int top = matrix[first][i];             
		matrix[first][i] = matrix[last - offset][first];             
		matrix[last - offset][first] = matrix[last][last - offset];            
		matrix[last][last - offset] = matrix[i][last];             
		matrix[i][last] = top;         
		}     } }
```