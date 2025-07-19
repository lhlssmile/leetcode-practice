'''
你是一位系统管理员，手里有一份文件夹列表 folder，你的任务是要删除该列表中的所有 子文件夹，并以 任意顺序 返回剩下的文件夹。

如果文件夹 folder[i] 位于另一个文件夹 folder[j] 下，那么 folder[i] 就是 folder[j] 的 子文件夹 。folder[j] 的子文件夹必须以 folder[j] 开头，后跟一个 "/"。例如，"/a/b" 是 "/a" 的一个子文件夹，但 "/b" 不是 "/a/b/c" 的一个子文件夹。

文件夹的「路径」是由一个或多个按以下格式串联形成的字符串：'/' 后跟一个或者多个小写英文字母。

例如，"/leetcode" 和 "/leetcode/problems" 都是有效的路径，而空字符串和 "/" 不是。


示例 1：

输入：folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
输出：["/a","/c/d","/c/f"]
解释："/a/b" 是 "/a" 的子文件夹，而 "/c/d/e" 是 "/c/d" 的子文件夹。
示例 2：

输入：folder = ["/a","/a/b/c","/a/b/d"]
输出：["/a"]
解释：文件夹 "/a/b/c" 和 "/a/b/d" 都会被删除，因为它们都是 "/a" 的子文件夹。
示例 3：

输入: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
输出: ["/a/b/c","/a/b/ca","/a/b/d"]


提示：

1 <= folder.length <= 4 * 104
2 <= folder[i].length <= 100
folder[i] 只包含小写字母和 '/'
folder[i] 总是以字符 '/' 起始
folder 每个元素都是 唯一 的

'''
from typing import List


class Solution:
    def removeSubfolders(self, folder: List[str]) -> List[str]:
        # 方法1: DFS + 字典树 (Trie)
        # 构建字典树
        trie = {}
            
        # 将所有文件夹路径插入字典树
        for path in folder:
            parts = path.split('/')[1:]  # 去掉第一个空字符串
            node = trie
            for part in parts:
                if part not in node:
                    node[part] = {}
                node = node[part]
            node['#'] = True  # 标记这是一个完整路径的结束
            
        result = []
            
        # DFS遍历字典树，收集根文件夹
        def dfs(node, path):
            # 如果当前节点是一个完整路径的结束
            if '#' in node:
                result.append(path)
                return  # 不再继续遍历子节点，因为子节点都是子文件夹
                
            # 继续遍历子节点
            for key, child in node.items():
                if key != '#':
                    dfs(child, path + '/' + key)
            
        # 从根节点开始DFS
        for key, child in trie.items():
            dfs(child, '/' + key)
            
        return result
        
    # 方法2: 简单排序法 (推荐)
    def simple_sort_solution(self, folder: List[str]) -> List[str]:
        # 排序后，子文件夹一定在父文件夹后面
        folder.sort()
        result = []
            
        for path in folder:
            # 如果result为空，或者当前路径不是result最后一个路径的子文件夹
            if not result or not path.startswith(result[-1] + '/'):
                result.append(path)
            
        return result
        
        # 方法3: DFS + 集合查找
    def dfs_set_solution(self, folder: List[str]) -> List[str]:
        folder_set = set(folder)
        result = []
            
        def is_subfolder(path):
            """检查path是否是某个已存在文件夹的子文件夹"""
            parts = path.split('/')
            # 从根路径开始，逐步构建父路径
            for i in range(1, len(parts)):
                parent_path = '/'.join(parts[:i+1])
                if parent_path in folder_set and parent_path != path:
                    return True
            return False
            
            # 对每个文件夹进行DFS检查
        for path in folder:
            if not is_subfolder(path):
                result.append(path)
            
        return result
        



# 测试用例
def test_solution():
    solution = Solution()
    
    # 测试用例1
    folder1 = ["/a", "/a/b", "/c/d", "/c/d/e", "/c/f"]
    result1 = solution.removeSubfolders(folder1)
    print(f"测试1: {folder1}")
    print(f"结果1: {result1}")  # 期望: ["/a", "/c/d", "/c/f"]
    print()
    
    # 测试用例2
    folder2 = ["/a", "/a/b/c", "/a/b/d"]
    result2 = solution.removeSubfolders(folder2)
    print(f"测试2: {folder2}")
    print(f"结果2: {result2}")  # 期望: ["/a"]
    print()
    
    # 测试用例3
    folder3 = ["/a/b/c", "/a/b/ca", "/a/b/d"]
    result3 = solution.removeSubfolders(folder3)
    print(f"测试3: {folder3}")
    print(f"结果3: {result3}")  # 期望: ["/a/b/c", "/a/b/ca", "/a/b/d"]
    print()
    
    # DFS思路解析
    print("=== DFS思路解析 ===")
    print("方法1 - 字典树DFS:")
    print("1. 构建字典树存储所有路径")
    print("2. DFS遍历，遇到完整路径就停止（避免遍历子文件夹）")
    print("3. 时间复杂度: O(N*M), 空间复杂度: O(N*M)")
    print()
    
    print("方法2 - 排序法（推荐）:")
    print("1. 排序后，子文件夹必定在父文件夹后面")
    print("2. 遍历时检查是否以前一个路径+'/'开头")
    print("3. 时间复杂度: O(N*logN), 空间复杂度: O(1)")
    print()
    
    print("方法3 - 集合DFS:")
    print("1. 对每个路径进行DFS检查是否为子文件夹")
    print("2. 逐步构建父路径，检查是否存在于集合中")
    print("3. 时间复杂度: O(N*M), 空间复杂度: O(N)")


if __name__ == "__main__":
    test_solution()