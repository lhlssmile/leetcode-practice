'''
LeetCode 本地调试通用模板
作者: AI Assistant
用途: 帮助在本地环境中调试LeetCode题目
'''

import time
import traceback
from typing import List, Optional, Any

class LeetCodeDebugger:
    """LeetCode调试工具类"""
    
    def __init__(self, problem_name: str = "Unknown Problem"):
        self.problem_name = problem_name
        self.test_count = 0
        self.passed_count = 0
    
    def print_header(self, title: str):
        """打印标题"""
        print(f"\n{'='*60}")
        print(f"🧪 {title}")
        print(f"{'='*60}")
    
    def print_step(self, step: int, description: str, details: str = ""):
        """打印调试步骤"""
        print(f"\n步骤 {step}: {description}")
        if details:
            print(f"  {details}")
    
    def print_variable(self, var_name: str, value: Any, description: str = ""):
        """打印变量状态"""
        print(f"  📊 {var_name} = {value}")
        if description:
            print(f"      {description}")
    
    def print_result(self, expected: Any, actual: Any, test_case: str = ""):
        """打印测试结果"""
        self.test_count += 1
        
        if test_case:
            print(f"\n🧪 测试用例 {self.test_count}: {test_case}")
        
        print(f"  期望结果: {expected}")
        print(f"  实际结果: {actual}")
        
        if expected == actual:
            print(f"  ✅ 通过")
            self.passed_count += 1
        else:
            print(f"  ❌ 失败")
        
        print(f"  {'-'*40}")
    
    def print_summary(self):
        """打印测试总结"""
        print(f"\n📊 测试总结")
        print(f"总测试数: {self.test_count}")
        print(f"通过数: {self.passed_count}")
        print(f"失败数: {self.test_count - self.passed_count}")
        print(f"通过率: {self.passed_count/self.test_count*100:.1f}%" if self.test_count > 0 else "通过率: 0%")
    
    def measure_time(self, func, *args, **kwargs):
        """测量函数执行时间"""
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        execution_time = (end_time - start_time) * 1000  # 转换为毫秒
        print(f"⏱️  执行时间: {execution_time:.2f} ms")
        return result
    
    def safe_execute(self, func, *args, **kwargs):
        """安全执行函数，捕获异常"""
        try:
            return func(*args, **kwargs)
        except Exception as e:
            print(f"❌ 执行出错: {str(e)}")
            print(f"错误类型: {type(e).__name__}")
            traceback.print_exc()
            return None

# 示例：如何使用调试模板
class Solution:
    def example_function(self, nums: List[int]) -> int:
        """示例函数 - 找数组最大值"""
        if not nums:
            return 0
        
        max_val = nums[0]
        for num in nums[1:]:
            if num > max_val:
                max_val = num
        return max_val

class SolutionDebug(Solution):
    def __init__(self):
        self.debugger = LeetCodeDebugger("找数组最大值")
    
    def example_function_debug(self, nums: List[int]) -> int:
        """带调试信息的版本"""
        self.debugger.print_header(f"调试: example_function({nums})")
        
        # 步骤1: 检查输入
        self.debugger.print_step(1, "检查输入")
        self.debugger.print_variable("nums", nums, f"数组长度: {len(nums)}")
        
        if not nums:
            self.debugger.print_step(2, "数组为空，返回0")
            return 0
        
        # 步骤2: 初始化
        self.debugger.print_step(2, "初始化最大值")
        max_val = nums[0]
        self.debugger.print_variable("max_val", max_val, "初始化为第一个元素")
        
        # 步骤3: 遍历数组
        self.debugger.print_step(3, "遍历数组寻找最大值")
        for i, num in enumerate(nums[1:], 1):
            print(f"    检查 nums[{i}] = {num}")
            if num > max_val:
                print(f"      {num} > {max_val}, 更新最大值")
                max_val = num
            else:
                print(f"      {num} <= {max_val}, 保持不变")
            self.debugger.print_variable("当前max_val", max_val)
        
        # 步骤4: 返回结果
        self.debugger.print_step(4, "返回最终结果")
        self.debugger.print_variable("最终结果", max_val)
        
        return max_val

def run_debug_example():
    """运行调试示例"""
    solution = SolutionDebug()
    
    # 测试用例
    test_cases = [
        ([1, 3, 2, 5, 4], 5),
        ([10], 10),
        ([], 0),
        ([-1, -3, -2], -1),
        ([5, 5, 5, 5], 5)
    ]
    
    solution.debugger.print_header("LeetCode 调试示例")
    
    for nums, expected in test_cases:
        # 普通版本
        normal_result = solution.example_function(nums)
        
        # 调试版本
        debug_result = solution.example_function_debug(nums)
        
        # 验证结果
        solution.debugger.print_result(expected, debug_result, f"nums = {nums}")
    
    solution.debugger.print_summary()

def debugging_tips():
    """调试技巧说明"""
    print("\n🎯 LeetCode 本地调试技巧")
    print("=" * 40)
    
    tips = [
        "1. 创建调试版本的函数，添加详细的打印语句",
        "2. 可视化算法的每一步执行过程",
        "3. 打印关键变量的状态变化",
        "4. 测试边界条件和特殊情况",
        "5. 对比普通版本和调试版本的结果",
        "6. 使用断言验证中间结果",
        "7. 测量算法的执行时间",
        "8. 捕获和处理异常情况",
        "9. 准备多个测试用例，包括边界情况",
        "10. 分析时间和空间复杂度"
    ]
    
    for tip in tips:
        print(f"  {tip}")
    
    print("\n🔧 常用调试工具:")
    tools = [
        "print() - 最基本的调试工具",
        "assert - 验证假设条件",
        "pdb - Python调试器",
        "logging - 日志记录",
        "time.time() - 性能测量",
        "traceback - 异常追踪",
        "type() - 类型检查",
        "len() - 长度检查",
        "enumerate() - 索引和值",
        "zip() - 并行遍历"
    ]
    
    for tool in tools:
        print(f"  • {tool}")
    
    print("\n📝 调试模板使用步骤:")
    steps = [
        "1. 复制原始Solution类",
        "2. 创建SolutionDebug继承类",
        "3. 添加调试版本的函数",
        "4. 在关键位置添加打印语句",
        "5. 准备测试用例",
        "6. 运行并分析结果",
        "7. 根据调试信息修复问题"
    ]
    
    for step in steps:
        print(f"  {step}")

if __name__ == '__main__':
    # 运行调试示例
    run_debug_example()
    
    # 显示调试技巧
    debugging_tips()
    
    print("\n🚀 现在你可以使用这个模板来调试任何LeetCode题目了！")