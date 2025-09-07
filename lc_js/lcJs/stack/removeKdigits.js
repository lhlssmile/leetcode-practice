/**
 * @param {string} num
 * @param {number} k
 * @return {string}
 */
var removeKdigits = function(num, k) {
    const stack = [];
    
    for (const digit of num) {
        // 当栈不为空，还有删除次数，且栈顶元素大于当前数字时，删除栈顶
        while (stack.length > 0 && k > 0 && stack[stack.length - 1] > digit) {
            stack.pop();
            k--;
        }
        stack.push(digit);
    }
    
    // 如果还没删完，从后面删
    while (k > 0 && stack.length > 0) {
        stack.pop();
        k--;
    }
    
    // 去掉前导零
    const result = stack.join('').replace(/^0+/, '');
    return result || '0';
};

// 函数式编程版本
const removeKdigitsFunctional = (num, k) => {
    // 使用reduce进行状态累积
    const [stack, remainingK] = [...num].reduce(
        ([stack, k], digit) => {
            // 移除比当前数字大的栈顶元素
            while (stack.length > 0 && k > 0 && stack[stack.length - 1] > digit) {
                stack.pop();
                k--;
            }
            stack.push(digit);
            return [stack, k];
        },
        [[], k]
    );
    
    // 如果还有剩余删除次数，从后面删除
    const finalStack = remainingK > 0 
        ? stack.slice(0, stack.length - remainingK)
        : stack;
    
    // 去掉前导零
    const result = finalStack.join('').replace(/^0+/, '');
    return result || '0';
};

// 使用现代JavaScript特性的版本
const removeKdigitsModern = (num, k) => {
    const processDigit = (acc, digit) => {
        const [stack, remainingK] = acc;
        
        // 移除比当前数字大的栈顶元素
        while (stack.length > 0 && remainingK > 0 && stack.at(-1) > digit) {
            stack.pop();
            remainingK--;
        }
        
        stack.push(digit);
        return [stack, remainingK];
    };
    
    // 使用数组解构和扩展运算符
    const [resultStack, remainingK] = [...num].reduce(processDigit, [[], k]);
    
    // 处理剩余删除次数
    const trimmed = remainingK > 0 
        ? resultStack.slice(0, -remainingK || undefined)
        : resultStack;
    
    // 链式操作去掉前导零
    return trimmed
        .join('')
        .replace(/^0+/, '')
        .pipe(result => result || '0');
};

// 添加pipe方法到String原型（函数式编程风格）
if (!String.prototype.pipe) {
    String.prototype.pipe = function(fn) {
        return fn(this);
    };
}

// 使用生成器的版本（展示高级JavaScript特性）
function* digitProcessor(num, k) {
    const stack = [];
    let remainingK = k;
    
    for (const digit of num) {
        // 移除比当前数字大的栈顶元素
        while (stack.length > 0 && remainingK > 0 && stack[stack.length - 1] > digit) {
            const removed = stack.pop();
            remainingK--;
            yield { action: 'remove', digit: removed, stack: [...stack] };
        }
        
        stack.push(digit);
        yield { action: 'add', digit, stack: [...stack] };
    }
    
    // 如果还有剩余删除次数，从后面删除
    while (remainingK > 0 && stack.length > 0) {
        const removed = stack.pop();
        remainingK--;
        yield { action: 'trim', digit: removed, stack: [...stack] };
    }
    
    return stack;
}

const removeKdigitsGenerator = (num, k) => {
    const processor = digitProcessor(num, k);
    let result = processor.next();
    let finalStack = [];
    
    // 执行所有步骤
    while (!result.done) {
        finalStack = result.value.stack;
        result = processor.next();
    }
    
    // 去掉前导零
    const resultStr = finalStack.join('').replace(/^0+/, '');
    return resultStr || '0';
};

// 使用Promise的异步版本（展示异步编程）
const removeKdigitsAsync = async (num, k) => {
    return new Promise((resolve) => {
        setTimeout(() => {
            const result = removeKdigits(num, k);
            resolve(result);
        }, 0);
    });
};

// 测试函数
function testAllVersions() {
    const testCases = [
        ["1432219", 3],  // "1219"
        ["10200", 1],    // "200"
        ["10", 2],       // "0"
        ["9", 1],        // "0"
        ["112", 1]       // "11"
    ];
    
    console.log("=== 标准版本 ===");
    testCases.forEach(([num, k]) => {
        const result = removeKdigits(num, k);
        console.log(`removeKdigits('${num}', ${k}) = '${result}'`);
    });
    
    console.log("\n=== 函数式版本 ===");
    testCases.forEach(([num, k]) => {
        const result = removeKdigitsFunctional(num, k);
        console.log(`removeKdigitsFunctional('${num}', ${k}) = '${result}'`);
    });
    
    console.log("\n=== 现代JavaScript版本 ===");
    testCases.forEach(([num, k]) => {
        const result = removeKdigitsModern(num, k);
        console.log(`removeKdigitsModern('${num}', ${k}) = '${result}'`);
    });
    
    console.log("\n=== 生成器版本 ===");
    testCases.forEach(([num, k]) => {
        const result = removeKdigitsGenerator(num, k);
        console.log(`removeKdigitsGenerator('${num}', ${k}) = '${result}'`);
    });
    
    console.log("\n=== 异步版本 ===");
    Promise.all(
        testCases.map(async ([num, k]) => {
            const result = await removeKdigitsAsync(num, k);
            console.log(`removeKdigitsAsync('${num}', ${k}) = '${result}'`);
        })
    );
}

// 如果在Node.js环境中运行
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        removeKdigits,
        removeKdigitsFunctional,
        removeKdigitsModern,
        removeKdigitsGenerator,
        removeKdigitsAsync
    };
    testAllVersions();
}

/*
JavaScript高级特性说明：

1. **解构赋值**:
   - const [stack, k] = reduce(...) - 数组解构
   - 简化多返回值的处理

2. **扩展运算符**:
   - [...num] - 将字符串转换为字符数组
   - [...stack] - 创建数组的浅拷贝

3. **Array.at()方法**:
   - stack.at(-1) - 获取数组最后一个元素
   - 比stack[stack.length - 1]更简洁

4. **链式操作**:
   - 方法链调用，提高代码可读性
   - 自定义pipe方法实现函数式管道

5. **生成器函数**:
   - function* - 定义生成器
   - yield - 产生值并暂停执行
   - 适用于步骤化处理和调试

6. **Promise和async/await**:
   - 异步编程模式
   - Promise.all - 并发执行多个异步操作

7. **模板字符串**:
   - 使用反引号和${}进行字符串插值
   - 比字符串拼接更清晰

8. **箭头函数**:
   - 简洁的函数语法
   - 自动绑定this上下文

9. **可选链和空值合并**:
   - ?. - 安全访问对象属性
   - ?? - 空值合并操作符

10. **正则表达式**:
    - /^0+/ - 匹配前导零
    - replace方法进行字符串替换
*/