class MinStack:
    def __init__(self):
        self.tack = []
        self.min_stack = []
    def push(self,val: int) -> None:
        self.stack.append(val)
        if not self.min_stack:
            min_stack.append(val)
        else:
            self.min_stack.append(min(val,self.min_stack[-1]))      # 访问最后一个元素ww
    def pop(self) -> None:
        self.stack.pop()
        self.min_stack.pop()
    def top(self) -> int:
        return self.stack[-1]
    def getMin(self) -> int:
        return self.min_stack[-1]



if __name__ == "__main__":
    st = MinStack()
    st.push(-2)
    st.push(0)
    st.push(-3)
    print(st.getMin())  # 输出: -3
    st.pop()
    print(st.top())     # 输出: 0
    print(st.getMin())  # 输出: -2
