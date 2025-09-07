package main

import (
    "fmt"
    "strings"
)

// BFS解法
func removeInvalidParentheses(s string) []string {
    if s == "" {
        return []string{""}
    }
    
    var res []string
    visited := make(map[string]bool)
    queue := []string{s}
    visited[s] = true
    found := false
    
    for len(queue) > 0 {
        size := len(queue)
        for i := 0; i < size; i++ {
            cur := queue[0]
            queue = queue[1:]
            
            if isValid(cur) {
                res = append(res, cur)
                found = true
            }
            
            if found {
                continue
            }
            
            for j := 0; j < len(cur); j++ {
                if cur[j] != '(' && cur[j] != ')' {
                    continue
                }
                next := cur[:j] + cur[j+1:]
                if !visited[next] {
                    queue = append(queue, next)
                    visited[next] = true
                }
            }
        }
        if found {
            break
        }
    }
    return res
}

// DFS解法
func removeInvalidParenthesesDFS(s string) []string {
    var res []string
    leftRem, rightRem := countInvalid(s)
    dfs(s, 0, leftRem, rightRem, 0, "", &res)
    return res
}

func isValid(s string) bool {
    balance := 0
    for _, c := range s {
        if c == '(' {
            balance++
        } else if c == ')' {
            balance--
            if balance < 0 {
                return false
            }
        }
    }
    return balance == 0
}

func countInvalid(s string) (int, int) {
    left, right := 0, 0
    for _, c := range s {
        if c == '(' {
            left++
        } else if c == ')' {
            if left > 0 {
                left--
            } else {
                right++
            }
        }
    }
    return left, right
}

func dfs(s string, index, leftRem, rightRem, open int, path string, res *[]string) {
    if index == len(s) {
        if leftRem == 0 && rightRem == 0 && open == 0 {
            *res = append(*res, path)
        }
        return
    }
    
    c := s[index]
    
    // 删除当前字符
    if (c == '(' && leftRem > 0) || (c == ')' && rightRem > 0) {
        newLeftRem := leftRem
        newRightRem := rightRem
        if c == '(' {
            newLeftRem--
        } else {
            newRightRem--
        }
        dfs(s, index+1, newLeftRem, newRightRem, open, path, res)
    }
    
    // 保留当前字符
    newPath := path + string(c)
    if c != '(' && c != ')' {
        dfs(s, index+1, leftRem, rightRem, open, newPath, res)
    } else if c == '(' {
        dfs(s, index+1, leftRem, rightRem, open+1, newPath, res)
    } else if open > 0 {
        dfs(s, index+1, leftRem, rightRem, open-1, newPath, res)
    }
}

func main() {
    fmt.Println(removeInvalidParentheses("()())"))
    fmt.Println(removeInvalidParentheses("((("))
}