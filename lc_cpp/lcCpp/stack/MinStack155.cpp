#include <bits/stdc++.h>
#include <vector>

using namespace std;


class minStack155{
public:
    vector<int> stack;      //常数时间找到最小的元素 用什么数据结构？ 堆？😅
    vector<int> minStack;
    minStack155(){
        //构造 函数?
    }
    void push(int val){
        stack.push_back(val);
        if(minStack.empty()){
            minStack.push_back(val);
        }else{
            minStack.push_back(min(val,minStack.back()));
        }
    }
    void pop(){
        stack.pop_back();
        minStack.pop_back();
        
    }
    int top(){
        return stack.back();
    }
    int getMin(){
        return minStack.back();
    }

};

int main(){
    auto* st = new minStack155();
    st->push(-2);
    st->push(0);
    st->push(-3);
    st->getMin();
    st->pop();
    st->top();
    st->getMin();
}