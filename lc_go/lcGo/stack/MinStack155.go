package main

type MinStack struct {
    stack    []int
    minStack []int
}

func Constructor() MinStack {
    return MinStack{}
}

func (this *MinStack) Push(val int) {
    this.stack = append(this.stack, val)
    if len(this.minStack) == 0 {
        this.minStack = append(this.minStack, val)
    } else {
        minVal := this.minStack[len(this.minStack)-1]
        if val < minVal {
            this.minStack = append(this.minStack, val)
        } else {
            this.minStack = append(this.minStack, minVal)
        }
    }
}

func (this *MinStack) Pop() {
    this.stack = this.stack[:len(this.stack)-1]
    this.minStack = this.minStack[:len(this.minStack)-1]		//访问数组最后一个元素是：arr[len(arr)-1]
}

func (this *MinStack) Top() int {
    return this.stack[len(this.stack)-1]
}

func (this *MinStack) GetMin() int {
    return this.minStack[len(this.minStack)-1]
}


func main() {
    st := Constructor()
    st.Push(-2)
    st.Push(0)
    st.Push(-3)
    fmt.Println(st.GetMin()) // 输出: -3
    st.Pop()
    fmt.Println(st.Top())    // 输出: 0
    fmt.Println(st.GetMin()) // 输出: -2
}