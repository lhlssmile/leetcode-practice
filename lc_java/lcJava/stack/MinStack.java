package stack;

import java.util.Stack;

class MinStack {
    private Stack<Integer> stack;
    private Stack<Integer> minStack;

    public MinStack() {
        stack = new Stack<Integer>();
        minStack = new Stack<Integer>();    
    }
    
    public void push(int val) {
        stack.push(val);
        if (minStack.isEmpty()){
            minStack.push(val);
        }else{
            minStack.push(Math.min(val,minStack.peek()));
        }
    }
    
    public void pop() {
        stack.pop();
        minStack.pop();
    }
    
    public int top() {
        return stack.peek();
    }
    
    public int getMin() {
        return minStack.peek();
    }

    public static void main(String[] args) {
        MinStack st = new MinStack();
        st.push(-1);
        st.push(2);
        st.pop();
        st.push(13);
        st.push(-22);
        st.push(22);
        System.out.println(st.getMin());
        System.out.println(st.top());
    }
}