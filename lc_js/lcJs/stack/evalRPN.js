// LeetCode 150: 逆波兰表达式求值
// 根据逆波兰表示法，求表达式的值

class Solution {
    evalRPN(tokens) {
        const stack = [];
        
        for (const token of tokens) {
            if (['+', '-', '*', '/'].includes(token)) {
                const b = stack.pop();  // 右操作数
                const a = stack.pop();  // 左操作数
                
                switch (token) {
                    case '+':
                        stack.push(a + b);
                        break;
                    case '-':
                        stack.push(a - b);
                        break;
                    case '*':
                        stack.push(a * b);
                        break;
                    case '/':
                        // JavaScript的除法需要向零截断
                        stack.push(Math.trunc(a / b));
                        break;
                }
            } else {
                stack.push(parseInt(token));
            }
        }
        
        return stack[0];
    }
}

// 函数式编程实现
function evalRPNFunctional(tokens) {
    return tokens.reduce((stack, token) => {
        if (['+', '-', '*', '/'].includes(token)) {
            const b = stack.pop();
            const a = stack.pop();
            
            const operations = {
                '+': (a, b) => a + b,
                '-': (a, b) => a - b,
                '*': (a, b) => a * b,
                '/': (a, b) => Math.trunc(a / b)
            };
            
            stack.push(operations[token](a, b));
        } else {
            stack.push(parseInt(token));
        }
        return stack;
    }, [])[0];
}

// 使用Map的实现
function evalRPNWithMap(tokens) {
    const stack = [];
    const operators = new Map([
        ['+', (a, b) => a + b],
        ['-', (a, b) => a - b],
        ['*', (a, b) => a * b],
        ['/', (a, b) => Math.trunc(a / b)]
    ]);
    
    for (const token of tokens) {
        if (operators.has(token)) {
            const b = stack.pop();
            const a = stack.pop();
            stack.push(operators.get(token)(a, b));
        } else {
            stack.push(parseInt(token));
        }
    }
    
    return stack[0];
}

// 箭头函数实现
const evalRPNArrow = (tokens) => {
    const stack = [];
    const ops = {
        '+': (a, b) => a + b,
        '-': (a, b) => a - b,
        '*': (a, b) => a * b,
        '/': (a, b) => Math.trunc(a / b)
    };
    
    tokens.forEach(token => {
        if (token in ops) {
            const [b, a] = [stack.pop(), stack.pop()];
            stack.push(ops[token](a, b));
        } else {
            stack.push(+token);  // 一元加号转换为数字
        }
    });
    
    return stack[0];
};

function testEvalRPN() {
    console.log("=== 逆波兰表达式求值测试 ===");
    
    const solution = new Solution();
    
    // 测试用例
    const testCases = [
        { tokens: ["2", "1", "+", "3", "*"], expected: 9 },  // ((2 + 1) * 3) = 9
        { tokens: ["4", "13", "5", "/", "+"], expected: 6 },  // (4 + (13 / 5)) = 6
        { tokens: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"], expected: 22 }  // 22
    ];
    
    testCases.forEach((testCase, index) => {
        const { tokens, expected } = testCase;
        
        const result1 = solution.evalRPN([...tokens]);
        const result2 = evalRPNFunctional([...tokens]);
        const result3 = evalRPNWithMap([...tokens]);
        const result4 = evalRPNArrow([...tokens]);
        
        console.log(`测试用例${index + 1}: [${tokens.map(t => `"${t}"`).join(', ')}]`);
        console.log(`类方法实现结果: ${result1}`);
        console.log(`函数式实现结果: ${result2}`);
        console.log(`Map实现结果: ${result3}`);
        console.log(`箭头函数实现结果: ${result4}`);
        console.log(`期望结果: ${expected}`);
        console.log(`所有实现正确: ${[result1, result2, result3, result4].every(r => r === expected)}`);
        console.log();
    });
    
    console.log("=== JavaScript特性说明 ===");
    console.log("1. 动态类型: 运行时类型检查");
    console.log("2. 数组方法: reduce、forEach等");
    console.log("3. 箭头函数: 简洁的函数语法");
    console.log("4. 解构赋值: 数组和对象解构");
    console.log("5. Map对象: 键值对集合");
}

// 导出模块
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        Solution,
        evalRPNFunctional,
        evalRPNWithMap,
        evalRPNArrow,
        testEvalRPN
    };
}

// 浏览器环境直接运行
if (typeof window !== 'undefined') {
    testEvalRPN();
}

// Node.js环境运行
if (typeof require !== 'undefined' && require.main === module) {
    testEvalRPN();
}

/*
JavaScript实现特点:

1. **动态特性**:
   - 动态类型系统
   - 运行时类型检查
   - 灵活的对象操作

2. **函数式编程**:
   - 一等函数
   - 高阶函数
   - 数组方法链

3. **现代语法**:
   - 箭头函数
   - 解构赋值
   - 模板字符串

4. **内置对象**:
   - Array数组方法
   - Map键值对集合
   - Math数学函数

5. **灵活性**:
   - 多种实现方式
   - 函数重载
   - 动态属性访问

算法复杂度:
- 时间复杂度: O(n)
- 空间复杂度: O(n)
*/